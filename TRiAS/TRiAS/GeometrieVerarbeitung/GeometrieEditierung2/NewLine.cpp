// Definitionen: Editierung eines neuen Linienobjektes
// File: NewLine.cpp
// W. Mörtl


#include "GeoEditP.h"

#include <stdio.h>		// sprintf() für OutputDebugString

#include "DragMultiLine.h"	// SetEndPoint(), ...
#include "NewLine.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor / Destruktor
CNewLine::CNewLine (void)
{
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    m_NewCP = CURSPOS_UNKNOWN;
    m_OldCP = CURSPOS_UNKNOWN;
    m_bIsPaint = false;			// Hintergrund wird augenblicklich nicht gezeichnet
    m_LeftButtonSem = false;	// linke Maustaste bzw.
    m_RightButtonSem = false;	// rechte Maustaste noch nicht gedrückt
    m_lParamOld = 0;			// letzte Mausposition
    m_iGrabCnt = 0;				// Anzahl der hintereinander gegrabten Punkte
    m_pGrabPktX = NULL;			// die in m_iGrabCnt gezählten GrabPunkte
    m_pGrabPktY = NULL;
	m_bMessBox = false;			// keine MessageBox angezeigt
	m_bWithDel = true;			// beim Zeichnen einer nachgezogenen Linie die alte Lage löschen

    m_pCT = new CoordTransX();	// KoordinatenTransformation
    if (! m_pCT)
    {
    	DEX_Error (RC_NewLine, EC_NOMEMORY);
    	return;
    }
}


// --------------------------------------------------------------------------------------------
CNewLine::~CNewLine (void)
{
	DELETE_OBJ (m_pCT);
	DELETE_VEC (m_pGrabPktX);
	DELETE_VEC (m_pGrabPktY);
    m_wDragObj.Assign (NULL);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur GeoEdit-Erweiterung über deren Interface IEditExtensionSite herstellen
STDMETHODIMP CNewLine::SetEditExtensionSite (IEditExtensionSite* pIEdExSite)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    	WUnknown wISite;

    		// Verbindung zu TRiAS über Interface ITriasExtension herstellen
    		THROW_FAILED_HRESULT (pIEdExSite->GetXtensionSite (wISite.ppi()));
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));

    		if (wISite.IsValid()) 		// in TRiAS reinhängen
    		{
    			if (m_dwCookieN != 0L || m_dwCookieSN != 0L)	// anmelden
    				_com_issue_error (E_UNEXPECTED);		// darf noch nicht angemeldet sein

    			m_Site = wISite;			// throws_com_error
    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASNotificationSink*)this,
    								  IID_ITRiASNotificationSink, &m_dwCookieN));

    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASSysNotificationSink*)this,
    								  IID_ITRiASSysNotificationSink, &m_dwCookieSN));
    		}

    		m_wEdExSite = pIEdExSite;
    		m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);
    		THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, m_wAllTObjs.ppi()));
    		m_wTopObjs->SetMarkVis (true);	// Stützpunkte der ausgewählten Objekte sollen
    										//  markiert werden
    	WEnumObjektGeometrie wGrabObjs (CLSID_EnumObjektGeometrie);

    		m_wGrabObjs = wGrabObjs;
    	}
    	else
    	{
			if (m_wObj.IsValid())
			{
			int iActTool = DEX_GetActiveTool();

				// wenn NewLine "richtig" verlassen wird (also nicht bloß zum Parken), dann das
				// aktuell editierte (temporäre) Objekt wieder aus den ausgewählten Objekten
				// herausnehmen
				if (ID_TOOL_DESIGN != iActTool)
				{
				Rectangle Rec = GetDeleteRectangle (m_wObj, m_wTopObjs, m_wRestrictCursor, m_LastPt);

					DEX_RePaintRectWait (Rec);	// OHNE nachfolgendes Update() !!!
					m_wTopObjs->DeleteTopicalObjectGeometry (m_wObj);
   					m_wObj.Assign (NULL);
				}

				// NewLine wird bloß zum Parken verlassen; dann hier die letzte Strecke, die zum
				// DesignTool führt, zu löschen
				else if (m_wDragObj.IsValid())
				{
				BOOL bTopIsPaint;	// wird in CTopicalObjects der Hintergrund gezeichnet?

					m_wTopObjs->IsPaint (&bTopIsPaint);
				    m_wDragObj->DeleteLastSituation (m_bIsPaint || bTopIsPaint);
					m_bWithDel = false;
				}
			}

    		// Stützpunktmarkierungen der ausgewählten Objekte sollen gelöscht werden
    		m_wTopObjs->SetMarkVis (false);

    		// Cursor wieder auf die Standard-Form "PFEIL" zurücksetzen
    		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

    		if (m_dwCookieN != 0L || m_dwCookieSN != 0L)	// abmelden
    			THROW_FAILED_HRESULT (DisconnectFromServer());	// gibt uns u.u. frei

		   	if (m_wRestrictCursor.IsValid())
			{
				m_wRestrictCursor->UnDraw();
   				m_wRestrictCursor.Assign (NULL);
			}
			m_wRestrLine1.Assign (NULL);
			m_wRestrLine2.Assign (NULL);
    		m_wTopObjs.Assign (NULL);
    		m_wEdExSite.Assign (NULL);

			m_bMessBox = false;			// keine MessageBox angezeigt
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // SetEditExtensionSite


// --------------------------------------------------------------------------------------------
// TRiASNotificationSink und TRiASSysNotificationSink bei TRiAS wieder abmelden
HRESULT CNewLine::DisconnectFromServer (void)
{
// künstliches AddRef, da uns nachfolgendes AtlUnadvise freigeben kann
WUnknown Unk ((IEditOperation*)this);

    AtlUnadvise (m_Site, IID_ITRiASNotificationSink, m_dwCookieN); 
    AtlUnadvise (m_Site, IID_ITRiASSysNotificationSink, m_dwCookieSN); 
    
    m_Site.Assign (NULL);	// freigeben von TRiAS
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    return S_OK;

} // DisconnectFromServer


// --------------------------------------------------------------------------------------------
// GeoEdit informiert die IEditOperation über den aktuellen Zustand der Konstruktionslinien
STDMETHODIMP CNewLine::InformRestrictLinesState (IRestrictLine* pRestrLine1,
												 IRestrictLine* pRestrLine2)
{
	m_wRestrLine1.Assign (NULL);
	m_wRestrLine2.Assign (NULL);
	m_wRestrLine1 = pRestrLine1;
	m_wRestrLine2 = pRestrLine2;

   	m_wRestrictCursor.Assign (NULL);

	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
		try
		{
		// Verbindung zum CRestrictCursor-Objekt über dessen Interface IRestrictCursor herstellen
		WRestrictCursor wRestrictCursor (CLSID_RestrictCursor);	// throws_com_error

    		m_wRestrictCursor = wRestrictCursor;
    		THROW_FAILED_HRESULT (m_wRestrictCursor->ConstructRestrictCursor());
		}
		catch (_com_error& e)
		{
    		return _COM_ERROR (e);
		}

	return S_OK;

} // InformRestrictLinesState


// --------------------------------------------------------------------------------------------
// Löschen einer Konstruktionshilfslinie in der this-EditierOperation
STDMETHODIMP CNewLine::DeleteRestrictedCursor (void)
{
   	if (m_wRestrictCursor.IsValid()) m_wRestrictCursor->UnDraw();
	return S_OK;

} // DeleteRestrictedCursor


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CNewLine::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CNewLine::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewLine::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CNewLine::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
// hPr: HPROJECT
STDMETHODIMP CNewLine::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    switch (ve)
    {
    	case GEOVIEWEVT_PaintingView:	// kommt vor dem Zeichnen des Hintergrundes
    									// (entspr. DEX_ERASEBKGND)
    		m_bIsPaint = true;		// Hintergrund wird gezeichnet
    		break;

    	case GEOVIEWEVT_ViewPainted:	// kommt nach dem Zeichnen des Hintergrundes
    									// (entspr. DEX_PAINTTOPLAYER)
    		m_bIsPaint = false;		// Hintergrund wurde gezeichnet
			if (m_wRestrLine1.IsValid()) m_wRestrLine1->Draw();
			if (m_wRestrLine2.IsValid()) m_wRestrLine2->Draw();
			if (m_wRestrictCursor.IsValid()) m_wRestrictCursor->SetFirstFlag (TRUE);

			if (m_wObj.IsValid())
			{
				DrawTemporaryObject (m_wObj, m_pVWnd);
				if (m_wDragObj.IsValid())
				{
				BOOL bTopIsPaint;	// wird in CTopicalObjects der Hintergrund gezeichnet?

					m_wTopObjs->IsPaint (&bTopIsPaint);

				Point pStartPt[1];

					pStartPt[0] = BSKoordinaten (m_pStartPkt[0].X(), m_pStartPkt[0].Y());
					m_wDragObj->ModStartPoints ((POINT*)pStartPt, 1);
			    	m_wDragObj->SetEndPoint ((POINT&)m_LastPt, bTopIsPaint, FALSE);
				}
			}

    		break;

		case GEOVIEWEVT_ScrollingHorz:
			if (m_wDragObj.IsValid() &&	// es befindet sich ein DragLineObject im Aufbau
				SUCCEEDED (VariantChangeType (&vData, &vData, NULL, VT_I4)))
			{
			long lOffset = V_I4 (&vData);

				m_wDragObj->EditWithScrolling (lOffset, true);
				m_LastPt.X() += lOffset;
			}
    		break;

		case GEOVIEWEVT_ScrollingVert:
			if (m_wDragObj.IsValid() &&
				SUCCEEDED (VariantChangeType (&vData, &vData, NULL, VT_I4)))
			{
			long lOffset = V_I4 (&vData);

				m_wDragObj->EditWithScrolling (lOffset, false);
				m_LastPt.Y() -= lOffset;
			}
			break;
    }

    return S_OK;	// immer weiterleiten

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewLine::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CNewLine::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewLine::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    switch (oe)
	{
		case GEOOBJECTEVT_ObjectSelected:
	    case GEOOBJECTEVT_ObjectUnSelected:
	    case GEOOBJECTEVT_ObjectDeleted:
		{
			try
			{
    			THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, m_wAllTObjs.ppi()));
			}
			catch (_com_error&)
			{
			    ATLTRACE("throw-failure in CNewLine::GeoObjectEvent");
			}
			break;
		}
	}

    return S_OK;	// immer weiterleiten

}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewLine::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CNewLine::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewLine::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CNewLine::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewLine::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CNewLine::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CNewLine::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
    switch (uiMsg)
    {
    	case WM_KEYDOWN:
    		KeyDown ((HWND)hWnd, wParam);
    		break;
    	
    	case WM_KEYUP:
    		KeyUp (wParam);
    		break;

    	case WM_MOUSEMOVE:
    		MouseMove (lParam);
    		break;

    	case WM_LBUTTONDOWN:
    		LeftMouseDown (lParam);
    		break;

    	case WM_LBUTTONUP:
    		LeftMouseUp();
    		break;

    	case WM_RBUTTONDOWN:
    		RightMouseDown (lParam);
    		break;

    	case WM_RBUTTONUP:
    		RightMouseUp();
    		break;

		case WM_LBUTTONDBLCLK:
    		LeftDoubleClick();
    }

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde gedrückt
HRESULT CNewLine::KeyDown (HWND hWnd, WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste gedrückt, um Grabben auszuschalten
    	return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);
    else
    	ScrollTest (hWnd, wParam);

    return S_OK;

} // KeyDown


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CNewLine::KeyUp (WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste losgelassen, um Grabben wieder zu ermöglichen
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);

    	if (CURSFORM_CROSS == CF &&		// Cursor hat noch CROSS-Form und
    		CURSPOS_VERTEX == m_NewCP)	// ist in einer Stützpunktmarkierung
    		return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
    }

    return S_OK;
    
} // KeyUp


// --------------------------------------------------------------------------------------------
// Maus wurde bewegt
HRESULT CNewLine::MouseMove (LPARAM lParam)
{
	if (NULL == g_pTE->MVWind())	// Projekt wird geschlossen oder kein Projekt geöffnet
    	return S_FALSE;				// NICHT "if (NULL == m_pVWnd)" !!!!

    if (lParam == m_lParamOld)		// keine neue Mausposition
    	return S_OK;

    m_lParamOld = lParam;

    // wenn linke oder rechte Maustaste gedrückt bzw. augenblicklich Hintergrund gezeichnet
    // wird, dann keine weitere Bearbeitung
    if (m_LeftButtonSem || m_RightButtonSem || m_bIsPaint)
    	return S_FALSE;

BOOL bTopIsPaint;	// wird in CTopicalObjects der Hintergrund gezeichnet?

    m_wTopObjs->IsPaint (&bTopIsPaint);

HRESULT hrRet = S_OK;

	if (!m_wRestrLine1.IsValid() && !m_wRestrLine2.IsValid())	// keine Konstruktionshilfslinien
		hrRet = MouseMoveWithoutRestrictLines (lParam);
	else									// mit Konstruktionshilfslinien
		hrRet = MouseMoveWithRestrictLines (lParam, bTopIsPaint);

    if (m_wDragObj.IsValid())
    {
    	m_wDragObj->SetEndPoint ((POINT&)m_LastPt, m_bIsPaint || bTopIsPaint, m_bWithDel);
		if (! m_bWithDel) m_bWithDel = true;
    	AktuelleWerteAnzeigen (m_LastPt);	// aktuelle Länge in Statuszeile anzeigen
    }
	
	return hrRet;

} // MouseMove


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde gedrückt
void CNewLine::LeftMouseDown (LPARAM lParam)
{
    m_LeftButtonSem = true;			// linke Maustaste wurde gedrückt
	m_lParam = lParam;

	// Maus einfangen, damit die Maus-Messages auch dann weiterhin empfangen werden können,
	// wenn sich der Cursor außerhalb des Anwendungsbereiches (d.h. über einem anderen Fenster)
	// befindet
    // eigentlich reicht ein MouseTrap(TRUE) nach dem ERSTEN LeftMouseDown()
//	m_pVWnd->MouseTrap (TRUE);

} // LeftMouseDown


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde losgelassen
HRESULT CNewLine::LeftMouseUp (void)
{
    if (!m_LeftButtonSem)	// linke Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_LeftButtonSem = false;		// linke Maustaste wurde losgelassen

	if (S_FALSE == EPunktAtCursor (m_lParam, m_wRestrLine1, m_wRestrLine2, m_LastPt, m_LastPkt))
    	return S_FALSE;

HRESULT hr;

    if (FAILED (hr = NeueKante()))
    {
    	m_wDragObj->DragTerminate();
    	m_wDragObj.Assign (NULL);
    	return hr;
    }

	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
		DEX_ChangeActiveTool (ID_TOOL_DESIGNSTOP);	// DesignMode beenden

    // Verbindung zum CDragMultiLine-Objekt über dessen Interface IDragObject herstellen
    try
    {
    WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    	m_wDragObj.Assign (NULL);
    	m_wDragObj = wDragObj;
    	m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
		m_pStartPkt[0] = DBKoordinaten (m_LastPt);
    	m_wDragObj->ConstructDragLines();
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // LeftMouseUp


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde gedrückt
void CNewLine::RightMouseDown (LPARAM lParam)
{
    m_RightButtonSem = true;		// rechte Maustaste wurde gedrückt
	m_lParam = lParam;

} // RightMouseDown


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde losgelassen
HRESULT CNewLine::RightMouseUp (void)
{
    if (!m_RightButtonSem)	// rechte Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_RightButtonSem = false;		// rechte Maustaste wurde losgelassen

    if (m_wDragObj.IsValid())
	{
		m_wDragObj->DragTerminate();
		m_wDragObj.Assign (NULL);
	}

    m_pVWnd->MouseTrap (FALSE);

	if (S_FALSE == EPunktAtCursor (m_lParam, m_wRestrLine1, m_wRestrLine2, m_LastPt, m_LastPkt))
    	return S_FALSE;

    RETURN_FAILED_HRESULT (NeueKante());

	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())		// 08.07.99
		DEX_ChangeActiveTool (ID_TOOL_DESIGNSTOP);	// DesignMode beenden

    // nach dem Hintergrundzeichnen nach einer möglichen Fehlermeldung wird wieder der
    // vorhergehende Cursor eingeschaltet; da das auch der GrabCursor sein kann, wird hier
    // einfach vorgebeugt
    m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);

	return ShowDialogForLine();

} // RightMouseUp


// --------------------------------------------------------------------------------------------
// Doppelklick auf linke Maustaste
void CNewLine::LeftDoubleClick (void)
{
// Zeichenoperation beenden
    if (m_wDragObj.IsValid())
	{
		m_wDragObj->DragTerminate();
		m_wDragObj.Assign (NULL);
	}

    m_pVWnd->MouseTrap (FALSE);

// Bereich neu zeichnen vorbereiten
int iMarkGr;	// Markergröße
Rectangle Rec;	// umschließendes Rechteck des aktuell editierten Objektes

    m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
    m_wObj->RectangleToDraw2 ((RECT*)&Rec, iMarkGr);

ulong ulLastIdent = DEX_GetLastIdent();

	if (0 != ulLastIdent && (ulong)-1 != ulLastIdent)	// in der Projekt-INI steht ein gültiger Identifikator
	{
	// Identifikator sowie Objektname hinzufügen und neues Objekt speichern
   		m_wObj->SetIdent (ulLastIdent);

	BSTR bsObjName = A2BSTR("");	// noch leerer Objektname  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		m_wEdExSite->StoreNewObject (m_wObj, bsObjName);
	}
	else 					// in der Projekt-INI steht kein gültiger Identifikator
		ShowDialogForLine();

// Bereich neu zeichnen
	m_wTopObjs->DeleteTopicalObjectGeometry (m_wObj);
   	m_wObj.Assign (NULL);	// muß VOR Update() kommen
    DEX_RePaintRectWait (Rec);
    m_pVWnd->Update();		// sofort zeichnen

	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
		DEX_ChangeActiveTool (ID_TOOL_DESIGNSTOP);	// DesignMode beenden

/* Können die nachfolgenden Zeilen wegen des am 24.02.99 in CGeoEditExtension::WindowsNotification
   (GeoEdit.cpp) eingefügten "case WM_MOUSEMOVE:" jetzt wegfallen ????????
CursForm CF;	// wieder Erläuterung der aktuellen CursorForm in Statuszeile

    m_wEdExSite->GetCursor (&CF);
   	m_wEdExSite->SetCursor (CF, TRUE);
*/
} // LeftDoubleClick


// --------------------------------------------------------------------------------------------
// EditierDialog anzeigen und Objekt (evtl.) abspeichern
HRESULT CNewLine::ShowDialogForLine (void)
{
ResString resCapt (ResID (IDS_NEWLINE, pRF), 40);
ulong ulCnt = 1;	// Anzahl der IObjektGeometrie'n
int iResult;		// Resultat der DialogBedienung

HRESULT hrRet = m_wEdExSite->ShowEditDialog (resCapt.Addr(), g_cbGeoEditNewLine, ulCnt,
    							 (IUnknown**)&m_wObj, &m_iGrabCnt, m_pGrabPktX, m_pGrabPktY,
    							 m_hrComBorder, m_lComONr, 0, NULL, NULL, &iResult);

    // m_wObj würde erst durch den Destruktor ~CNewLine zerlegt werden; damit aber mehrere
    // Linienobjekte editiert werden können, ohne das zwischendurch ~CNewLine gerufen wird,
    // erfolgt hier bei OK bzw. Cancel ein zwangsweises Zerlegen von m_wObj
    if (IDOK == iResult || IDCANCEL == iResult)
	{
		m_wTopObjs->DeleteTopicalObjectGeometry (m_wObj);
    	m_wObj.Assign (NULL);

		if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
			DEX_ChangeActiveTool (ID_TOOL_DESIGNSTOP);	// DesignMode beenden

/* Können die nachfolgenden Zeilen wegen des am 24.02.99 in CGeoEditExtension::WindowsNotification
   (GeoEdit.cpp) eingefügten "case WM_MOUSEMOVE:" jetzt wegfallen ????????
    CursForm CF;	// wieder Erläuterung der aktuellen CursorForm in Statuszeile

    	m_wEdExSite->GetCursor (&CF);
   		m_wEdExSite->SetCursor (CF, TRUE);
*/
	}
    else if (IDB_CONTINUE == iResult)
    {
    	// Hintergrund nach Zerlegen des Dialogs sofort zeichnen, weil sonst ZUERST die neue
    	// DragLine gezeichnet wird, die dann durch das spätere Hintergrundzeichnen gelöscht
    	// wird
    	m_pVWnd->Update();

		hrRet = ContinueButtonAction();
    	if (FAILED(hrRet)) return hrRet;
    }

	return hrRet;

} // ShowDialogForLine


// --------------------------------------------------------------------------------------------
// neue Kante editieren
HRESULT CNewLine::NeueKante (void)
{
	// m_LastPkt evtl. durch Grabben noch modifizieren, wenn ohne Konstruktionshilfslinien
	// editiert wird
	RETURN_FAILED_HRESULT (Grabbing());

    if (! m_wObj.IsValid())	// aus dem 1. editierten Stützpunkt Kantenanfang aufbauen
    {						
    	m_dAktGesLaenge = 0.0;

    	RETURN_FAILED_HRESULT (CreateInterfaceOG (m_wObj.ppi(), m_LastPkt.X(), m_LastPkt.Y(),
												  OT_KANTE));

		m_wTopObjs->AddTopicalObjectGeometry (m_wObj);
    }

    else				// weitere Stützpunkte wurden editiert
    {
    	RETURN_FAILED_HRESULT (m_wObj->AddPunkt (m_LastPkt.X(), m_LastPkt.Y(), -1, -1));

    	m_dAktGesLaenge += m_dAktLaenge;
    }

    return S_OK;

} // NeueKante


// --------------------------------------------------------------------------------------------
// Grabben des letzten editierten Punktes;
// return-Wert:	S_OK            es wurde gegrabt
//				S_FALSE         es wurde nicht gegrabt
//				E_OUTOFMEMORY   dynamischer Speicher nicht ausreichend
HRESULT CNewLine::Grabbing (void)
{
	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
		return S_FALSE;		// es ist wenigstens 1 Konstruktionshilfslinie vorgegeben

// m_LastPkt evtl. durch Grabben noch modifizieren und alle Linien- bzw. Flächenobjekte der
// m_wAllTObjs-Objekte in wActGrabObjs einsammeln, die den (falls vorhanden) GrabPunkt als
// Stützpunkt besitzen
WEnumObjektGeometrie wActGrabObjs;
HRESULT hrRet = m_wTopObjs->NewVertexWithGrab ((POINT*)&m_LastPt, m_wDragObj, &m_LastPkt.X(),
											   &m_LastPkt.Y(), wActGrabObjs.ppi());

    if (S_OK != hrRet)	// es wurde nicht gegrabt
    {
    	m_iGrabCnt = 0;
    	m_hrComBorder = S_FALSE;
    }

    else				// es wurde gegrabt
    {
    	if (0 == m_iGrabCnt)	// der 1. von mehreren hintereinander editierten GrabPunkten
    	{
	 		DELETE_VEC (m_pGrabPktX);
	 		DELETE_VEC (m_pGrabPktY);
    		m_pGrabPktX = new KoOrd[iComCnt];	// iComCnt ist in EditKonst.h definiert
    		m_pGrabPktY = new KoOrd[iComCnt];
    		if (!m_pGrabPktX || !m_pGrabPktY)
    		{
	 			DELETE_VEC (m_pGrabPktX);
    			DEX_Error (RC_NewLine, EC_NOMEMORY);
    			return E_OUTOFMEMORY;
    		}
    	}

    	m_lComONr = 0;	// Objektnummer des Objektes, von dem die gemeinsamen Stützpunkte bei
    					// CommonBorder übernommen werden können

    	m_hrComBorder = IsCommonBorderAllowable (m_iGrabCnt, wActGrabObjs, m_wGrabObjs,
    											 m_lComONr);
		if (0 != m_lComONr && -1 != m_lComONr)
		{
		int iOT = DEX_GetObjectType (m_lComONr);

			if ((OT_FLAECHE == iOT || S_OK == IsClosedLine (m_lComONr)) && m_iGrabCnt > 3)
			{
				m_pGrabPktX[0] = m_pGrabPktX[1];
				m_pGrabPktY[0] = m_pGrabPktY[1];
				m_pGrabPktX[1] = m_pGrabPktX[2];
				m_pGrabPktY[1] = m_pGrabPktY[2];
				m_iGrabCnt--;
			}
			else if (OT_KANTE == iOT && S_FALSE == IsClosedLine (m_lComONr) && m_iGrabCnt > 2)
			{
				m_pGrabPktX[0] = m_pGrabPktX[1];
				m_pGrabPktY[0] = m_pGrabPktY[1];
				m_iGrabCnt--;
			}
		}

		_ASSERTE (m_iGrabCnt <= iComCnt);

    	m_pGrabPktX[m_iGrabCnt-1] = m_LastPkt.X();
    	m_pGrabPktY[m_iGrabCnt-1] = m_LastPkt.Y();


		// Korrektur von m_AktLaenge (seit 26.03.99 an dieser Stelle)
		if (m_wObj.IsValid())
		{
		long lCnt;	//  Gesamtanzahl der Stützpunkte der editierten Linie 

    		m_wObj->GetCnt (&lCnt);

			if (lCnt >= 2)
			{
			KoOrd* plXK; KoOrd* plYK;	//  Feld der x- bzw. y-Koordinaten der editierten Linie

    			m_wObj->GetX ((void**)&plXK);
    			m_wObj->GetY ((void**)&plYK);

			DoublePair DEP;	// Punkt, auf den gegrabt wurde (im ASC-Format)
			DoublePair DAP;	// der vorhergehende Punkt

    			m_pCT->UnScale (m_LastPkt.X(), m_LastPkt.Y(), &DEP.X(), &DEP.Y());
    			m_pCT->UnScale (plXK[lCnt-2], plYK[lCnt-2], &DAP.X(), &DAP.Y());

    			m_dAktLaenge = m_pCT->CoordTransDistance (&DAP, &DEP);
			}
		}
    }

	return hrRet;

} // Grabbing


// --------------------------------------------------------------------------------------------
// ContinueButton in der PropertySheet gedrückt
HRESULT CNewLine::ContinueButtonAction (void)
{
// Das Drücken eines Buttons bzw. die Korrektur des letzten Koordinatenpaars durch den Anwender
// kann den Punkt, an dem fortgesetzt werden soll, verändern. Deshalb ist dieser Punkt neu zu
// ermitteln. Außerdem ist die Gesamtlänge neu zu berechnen.
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    m_wObj->GetCnt (&lCnt);
    m_wObj->GetX ((void**)&plXK);
    m_wObj->GetY ((void**)&plYK);

DoublePair DAP, DEP;	// Stützpunkte im ASC-Format

    m_dAktGesLaenge = 0.0;		// Gesamtlänge neu berechnen
    for (long i = 0; i < lCnt-1; i++)
    {
    	m_pCT->UnScale (plXK[i], plYK[i], &DAP.X(), &DAP.Y());
    	m_pCT->UnScale (plXK[i+1], plYK[i+1], &DEP.X(), &DEP.Y());
    	m_dAktGesLaenge += m_pCT->CoordTransDistance (&DAP, &DEP);
    }

    m_LastPt = BSKoordinaten (plXK[lCnt-1], plYK[lCnt-1]);
    m_LastPkt.X() = plXK[lCnt-1];
    m_LastPkt.Y() = plYK[lCnt-1];

    try
    {
    WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    	m_wDragObj.Assign (NULL);
    	m_wDragObj = wDragObj;
    	m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
		m_pStartPkt[0] = DBKoordinaten (m_LastPt);
    	m_wDragObj->ConstructDragLines();
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // ContinueButtonAction


// --------------------------------------------------------------------------------------------
// aktuelle Länge in Statuszeile anzeigen
bool CNewLine::AktuelleWerteAnzeigen (Point Pt)
{
    if (! m_wObj.IsValid())	// der 1. Punkt der zu editierenden Linie ist noch nicht
    	return false;		//  gesetzt, deshalb keine aktuelle Länge anzeigen

string sOutBuff = ResString (ResID (IDS_AKTSTRECKE, pRF), 40);
char pcKonvBuff[40] = { '\0' };	// Konvertierungspuffer
DoublePair DEP = BSInASCKoord (Pt, m_pCT);	// aktueller Punkt an der Mausspitze

    m_pCT->UnScale (m_LastPkt, &m_DAP.X(), &m_DAP.Y());

    // Länge der aktuell editierten Strecke ermitteln
    m_dAktLaenge = m_pCT->CoordTransDistance (&m_DAP, &DEP);

    DtoA (pcKonvBuff, "%1.0f", m_dAktLaenge);
    sOutBuff += pcKonvBuff;
    sOutBuff += " m";		// "Meter" anfügen

    sOutBuff += ResString (ResID (IDS_GESAMTLAENGE, pRF), 40);
    DtoA (pcKonvBuff, "%1.0f", m_dAktGesLaenge + m_dAktLaenge);
    sOutBuff += pcKonvBuff;
    sOutBuff += " m";

    DEX_SetMessageStringNoKickIdle (sOutBuff.c_str());
    return true;

} // AktuelleWerteAnzeigen


// --------------------------------------------------------------------------------------------
// MouseMove ohne Konstruktionshilfslinien
HRESULT CNewLine::MouseMoveWithoutRestrictLines (LPARAM lParam)
{
	if (m_wDragObj.IsValid()) m_LastPt = BSPoint (lParam);

HRESULT hr = m_wTopObjs->CursorInMarkerSomeTopObjects (m_wAllTObjs, &m_NewCP);

	if (FAILED(hr)) return hr;

	if (m_NewCP == m_OldCP) return S_OK;

	m_OldCP = m_NewCP;	// bisherige CursorPosition retten

	if (CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    	return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
	return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);

} // MouseMoveWithoutRestrictLines


// --------------------------------------------------------------------------------------------
// MouseMove mit Konstruktionshilfslinien
HRESULT CNewLine::MouseMoveWithRestrictLines (LPARAM lParam, BOOL bTopIsPaint)
{
	if (!m_wRestrLine1.IsValid() && !m_wRestrLine2.IsValid())
		return E_UNEXPECTED;	// keine Konstruktionshilfslinie 

	if (!m_wRestrLine1.IsValid() || !m_wRestrLine2.IsValid())	// genau 1 Konstruktionshilfslinie
	{
		// wenn der return-Wert von CursorTo1RestrictLine() "S_FALSE" ist, befindet sich die
		// Mausspitze genau im Mittelpunkt einer kreisförmigen Hilfslinie; in diesem Fall wird
		// keine Cursorposition berechnet
		if (m_wRestrLine1.IsValid() &&
			S_FALSE == m_wRestrLine1->CursorTo1RestrictLine (lParam, &(POINT&)m_LastPt))
			return S_FALSE;
		if (m_wRestrLine2.IsValid() &&
			S_FALSE == m_wRestrLine2->CursorTo1RestrictLine (lParam, &(POINT&)m_LastPt))
			return S_FALSE;
	}
	else									// 2 Konstruktionshilfslinien
		// wenn der return-Wert von CursorTo2RestrictLines() "S_FALSE" ist, wurde eine
		// MessageBox angezeigt
		if (!m_bIsPaint && !bTopIsPaint &&
			!m_bMessBox &&					// keine MessageBox angezeigt
			S_FALSE == m_wRestrLine1->CursorTo2RestrictLines (lParam, m_wRestrLine2,
															  &(POINT&)m_LastPt))
		{
			m_bMessBox = true;
			return S_FALSE;
		}

    if (m_wRestrictCursor.IsValid())
		m_wRestrictCursor->SetPoint ((POINT&)m_LastPt, m_bIsPaint || bTopIsPaint);

#ifdef DEX_SetShownCoords
	DEX_SetShownCoords (m_LastPt.X(), m_LastPt.Y());
#endif

	return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

} // MouseMoveWithRestrictLines
