// Definitionen: Editierung eines neuen Punktobjektes
// File: NewPoint.cpp
// W. Mörtl


#include "GeoEditP.h"
//#include <stdio.h>		// sprintf() für OutputDebugString

#include "NewPoint.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CNewPoint::CNewPoint (void)
{
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    m_bIsPaint = false;			// Hintergrund wird augenblicklich nicht gezeichnet
    m_RightButtonSem = false;	// rechte Maustaste noch nicht gedrückt
    m_NewCP = CURSPOS_UNKNOWN;
    m_OldCP = CURSPOS_UNKNOWN;
    m_lParamOld = 0;			// letzte Mausposition
	m_PTCur.x = 0;
	m_PTCur.y = 0;
	m_bMessBox = false;			// keine MessageBox angezeigt
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur GeoEdit-Erweiterung über deren Interface IEditExtensionSite herstellen
STDMETHODIMP CNewPoint::SetEditExtensionSite (IEditExtensionSite* pIEdExSite)
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
    				_com_issue_error (E_UNEXPECTED);	// darf noch nicht angemeldet sein

    			m_Site = wISite;			// throws_com_error
    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASNotificationSink*)this,
    								  IID_ITRiASNotificationSink, &m_dwCookieN));

    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASSysNotificationSink*)this,
    								  IID_ITRiASSysNotificationSink, &m_dwCookieSN));
    		}

    		m_wEdExSite = pIEdExSite;
    		m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);
    		THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, m_wAllTObjs.ppi()));

			// Stützpunkte der ausgewählten Objekte	werden markiert
    		m_wTopObjs->SetMarkVis (true);
    	}
    	else
    	{
    		// Stützpunktmarkierungen der ausgewählten Objekte werden gelöscht
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
// TRiASSysNotificationSink bei TRiAS wieder abmelden
HRESULT CNewPoint::DisconnectFromServer (void)
{
// künstliches AddRef, da uns nachfolgendes AtlUnadvise freigeben kann
WUnknown Unk ((IEditOperation*)this);

    AtlUnadvise (m_Site, IID_ITRiASNotificationSink, m_dwCookieN); 
    AtlUnadvise (m_Site, IID_ITRiASSysNotificationSink, m_dwCookieSN); 
    
    m_Site.Assign (NULL);		// freigeben von TRiAS
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    return S_OK;

} // DisconnectFromServer


// --------------------------------------------------------------------------------------------
// GeoEdit informiert die IEditOperation über den aktuellen Zustand der
// Konstruktionshilfslinien
STDMETHODIMP CNewPoint::InformRestrictLinesState (IRestrictLine* pRestrLine1,
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
// Löschen des Cursors für Editierung auf einer Konstruktionshilfslinie in der
// this-EditierOperation
STDMETHODIMP CNewPoint::DeleteRestrictedCursor (void)
{
   	if (m_wRestrictCursor.IsValid()) m_wRestrictCursor->UnDraw();
	return S_OK;

} // DeleteRestrictedCursor


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CNewPoint::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CNewPoint::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewPoint::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CNewPoint::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
STDMETHODIMP CNewPoint::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
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
    		break;

		case GEOVIEWEVT_ScrollingHorz:
    		break;

		case GEOVIEWEVT_ScrollingVert:
			break;
    }

    return S_OK;	// immer weiterleiten

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewPoint::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CNewPoint::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewPoint::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
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
			    ATLTRACE("throw-failure in CNewPoint::GeoObjectEvent");
			}
			break;
		}
	}

    return S_OK;	// immer weiterleiten

}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewPoint::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CNewPoint::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewPoint::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CNewPoint::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CNewPoint::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CNewPoint::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CNewPoint::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
    switch (uiMsg)
    {
    	case WM_KEYDOWN:
    		KeyDown (wParam);
    		break;
    	
    	case WM_KEYUP:
    		KeyUp (wParam);
    		break;

    	case WM_MOUSEMOVE:
    		MouseMove ((HWND)hWnd, lParam);
    		break;

    	case WM_RBUTTONDOWN:
    		RightMouseDown (lParam);
    		break;

    	case WM_RBUTTONUP:
    		RightMouseUp();
    		break;

		case WM_LBUTTONDBLCLK:
    		LeftDoubleClick (lParam);
    }

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde gedrückt
HRESULT CNewPoint::KeyDown (WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste gedrückt, um Grabben auszuschalten
    	return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);
    return S_OK;

} // KeyDown


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CNewPoint::KeyUp (WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste losgelassen, um Grabben wieder zu ermöglichen
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);

    	if (CURSFORM_CROSS == CF &&	// Cursor hat noch CROSS-Form,
    		CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    		return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
    }

    return S_OK;
    
} // KeyUp


// --------------------------------------------------------------------------------------------
// Maus wurde bewegt
HRESULT CNewPoint::MouseMove (HWND hWnd, LPARAM lParam)
{
	if (NULL == g_pTE->MVWind())	// Projekt wird geschlossen oder kein Projekt geöffnet
    	return S_FALSE;				// NICHT "if (NULL == m_pVWnd)" !!!!

	if (lParam == m_lParamOld)		// keine Mausbewegung
    	return S_OK;

	m_lParamOld = lParam;

BOOL bTopIsPaint;	// wird in CTopicalObjects der Hintergrund gezeichnet?

    m_wTopObjs->IsPaint (&bTopIsPaint);

	// keine Konstruktionshilfslinien
	if (!m_wRestrLine1.IsValid() && !m_wRestrLine2.IsValid())
	{
	HRESULT hr = m_wTopObjs->CursorInMarkerSomeTopObjects (m_wAllTObjs, &m_NewCP);

		if (FAILED(hr)) return hr;

		if (m_NewCP == m_OldCP) return S_OK;

		m_OldCP = m_NewCP;	// bisherige CursorPosition retten

		if (CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    		return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
	    return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);
	}

	// Konstruktionshilfslinien sind vorgegeben
	if (!m_wRestrLine1.IsValid() || !m_wRestrLine2.IsValid())	// genau 1 Konstruktionshilfslinie
	{
		// wenn der return-Wert von CursorTo1RestrictLine() "S_FALSE" ist, befindet sich die
		// Mausspitze genau im Mittelpunkt einer kreisförmigen Hilfslinie; in diesem Fall wird
		// keine Cursorposition berechnet
		if (m_wRestrLine1.IsValid() &&
			S_FALSE == m_wRestrLine1->CursorTo1RestrictLine (lParam, &m_PTCur))
			return S_FALSE;
		if (m_wRestrLine2.IsValid() &&
			S_FALSE == m_wRestrLine2->CursorTo1RestrictLine (lParam, &m_PTCur))
			return S_FALSE;
	}
	else									// 2 Konstruktionshilfslinien
		// wenn der return-Wert von CursorTo2RestrictLines() "S_FALSE" ist, wurde eine
		// MessageBox angezeigt
		if (!m_bIsPaint && !bTopIsPaint &&
			!m_bMessBox &&					// keine MessageBox angezeigt
			S_FALSE == m_wRestrLine1->CursorTo2RestrictLines (lParam, m_wRestrLine2, &m_PTCur))
		{
			m_bMessBox = true;
			return S_FALSE;
		}

    if (m_wRestrictCursor.IsValid())
		m_wRestrictCursor->SetPoint (m_PTCur, m_bIsPaint || bTopIsPaint);

#ifdef DEX_SetShownCoords
	DEX_SetShownCoords (m_PTCur.x, m_PTCur.y);
#endif

	return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

} // MouseMove


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde gedrückt
void CNewPoint::RightMouseDown (LPARAM lParam)
{
    m_RightButtonSem = true;	// rechte Maustaste wurde gedrückt
	m_lParam = lParam;

} // RightMouseDown


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde losgelassen
HRESULT CNewPoint::RightMouseUp (void)
{
    if (!m_RightButtonSem)	// rechte Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_RightButtonSem = false;		// rechte Maustaste wurde losgelassen

Point Pt;	// Parameter von EPunktAtCursor(); wird hier nicht weiter benötigt
EPunkt CurPkt;

	if (S_FALSE == EPunktAtCursor (m_lParam, m_wRestrLine1, m_wRestrLine2, Pt, CurPkt))
		return S_FALSE;

	Grabbing (CurPkt.X(), CurPkt.Y());

	RETURN_FAILED_HRESULT (CreateInterfaceOG (m_wObj.ppi(), CurPkt.X(), CurPkt.Y(), OT_PUNKT));

HRESULT hr = ShowDialogForPoint();

	RETURN_FAILED_HRESULT (hr);
	if (S_FALSE == hr) {
	// erzeugen abgebrochen
		if (m_wRestrictCursor.IsValid()) 
			m_wRestrictCursor->SetFirstFlag (TRUE);
		return S_OK;
	}

	m_pVWnd->Update();		// Hintergrund des Dialogs sofort zeichnen
	DrawObjBackground();	// Hintergrund des Objektes neu zeichnen
	if (m_wRestrictCursor.IsValid()) 
		m_wRestrictCursor->SetFirstFlag (TRUE);

    return S_OK;

} // RightMouseUp


// --------------------------------------------------------------------------------------------
// Doppelklick auf linke Maustaste
HRESULT CNewPoint::LeftDoubleClick (LPARAM lParam)
{
Point Pt;	// Parameter von EPunktAtCursor(); wird hier nicht weiter benötigt
EPunkt CurPkt;

	if (S_FALSE == EPunktAtCursor (lParam, m_wRestrLine1, m_wRestrLine2, Pt, CurPkt))
		return S_FALSE;

	Grabbing (CurPkt.X(), CurPkt.Y());

	RETURN_FAILED_HRESULT (CreateInterfaceOG (m_wObj.ppi(), CurPkt.X(), CurPkt.Y(), OT_PUNKT));

ulong ulLastIdent = DEX_GetLastIdent();

	if (0 != ulLastIdent && (ulong)-1 != ulLastIdent)	// in der Projekt-INI steht ein gültiger Identifikator
	{
	// Identifikator sowie Objektname hinzufügen und neues Objekt speichern
   		m_wObj->SetIdent (ulLastIdent);

	BSTR bsObjName = A2BSTR("");	// noch leerer Objektname  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	HRESULT hr = m_wEdExSite->StoreNewObject (m_wObj, bsObjName);

		if (S_OK != hr)
			return hr;
	}
	else {					// in der Projekt-INI steht kein gültiger Identifikator
	HRESULT hr = ShowDialogForPoint();

		RETURN_FAILED_HRESULT (hr);
		if (S_FALSE == hr) {
		// erzeugen abgebrochen
			if (m_wRestrictCursor.IsValid()) 
				m_wRestrictCursor->SetFirstFlag (TRUE);
   			m_wObj.Assign (NULL);
			return S_OK;
		}
	}

	DrawObjBackground();	// Hintergrund des Objektes neu zeichnen
	if (m_wRestrictCursor.IsValid()) 
		m_wRestrictCursor->SetFirstFlag (TRUE);

   	m_wObj.Assign (NULL);

	return S_OK;

} // LeftDoubleClick


// --------------------------------------------------------------------------------------------
// (PktX,PktY) evtl. durch Grabben noch modifizieren, wenn ohne Konstruktionshilfslinien
// editiert wird
// return-Wert:	S_OK      es wurde gegrabt
//				S_FALSE   es wurde nicht gegrabt
HRESULT CNewPoint::Grabbing (KoOrd& PktX, KoOrd& PktY)
{
	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
		return S_FALSE;		// es ist wenigstens 1 Konstruktionshilfslinie vorgegeben

POINT PT;	// Parameter für NewVertexWithGrab(); wird hier nicht weiter benötigt

	return m_wTopObjs->NewVertexWithGrab (&PT, NULL, &PktX, &PktY, NULL);

} // Grabbing


// --------------------------------------------------------------------------------------------
// EditierDialog anzeigen und Objekt (evtl.) abspeichern
HRESULT CNewPoint::ShowDialogForPoint (void)
{
ResString resCapt (ResID (IDS_NEWPOINT, pRF), 40);
ulong ulCnt = 1;	// Anzahl der IObjektGeometrie'n
int iResult;		// Resultat der DialogBedienung

HRESULT hrRet = m_wEdExSite->ShowEditDialog (resCapt.Addr(), g_cbGeoEditNewPoint, ulCnt,
    					 (IUnknown**)&m_wObj, NULL, NULL, NULL, 0, 0, 0, NULL, NULL, &iResult);

    // m_wObj würde erst durch den Destruktor ~CNewPoint zerlegt werden; damit aber mehrere
    // Punktobjekte editiert werden können, ohne das zwischendurch ~CNewPoint gerufen wird,
    // erfolgt hier ein zwangsweises Zerlegen von m_wObj
    m_wObj.Assign (NULL);

	return hrRet;

} // ShowDialogForPoint


// --------------------------------------------------------------------------------------------
// Hintergrund des neu gebildeten Objektes zeichnen
void CNewPoint::DrawObjBackground (void)
{
	if (!m_wObj.IsValid() && !m_wRestrictCursor.IsValid())
		return;		// Hintergrund des Objektes wurde schon in ShowEditDialog() gezeichnet

Rectangle RecObj,	// umschließendes Rechteck des aktuell editierten Objektes bzw.
		  RecCur,	// des kreuzförmigen Cursors auf Konstruktionshilfslinien
		  Rec;		// zu zeichnendes Rechteck

    if (m_wObj.IsValid()) m_wObj->RectangleToDraw ((RECT*)&RecObj);
	if (m_wRestrictCursor.IsValid()) m_wRestrictCursor->GetBoundingBox ((RECT*)&RecCur);

	if (m_wObj.IsValid() && m_wRestrictCursor.IsValid())
		Rec = RecObj.Union(RecCur);
	else if (m_wObj.IsValid())
		Rec = RecObj;
	else	// m_wRestrictCursor != NULL
		Rec = RecCur;

	Rec.Left() -= iZug;
	Rec.Right() += iZug;
	Rec.Top() += iZug;
	Rec.Bottom() -= iZug;

    DEX_RePaintRectWait (Rec);
    m_pVWnd->Update();		// sofort zeichnen

	if (m_wRestrLine1.IsValid()) m_wRestrLine1->Draw();
	if (m_wRestrLine2.IsValid()) m_wRestrLine2->Draw();

} // DrawObjBackground
