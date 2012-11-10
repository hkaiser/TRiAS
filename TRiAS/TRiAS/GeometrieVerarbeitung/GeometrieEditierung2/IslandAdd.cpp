// Definitionen: Innenkontur hinzufügen
// File: IslandAdd.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "IslandAdd.h"



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CIslandAdd::CIslandAdd (void)
{
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    m_NewCP = CURSPOS_UNKNOWN;
    m_OldCP = CURSPOS_UNKNOWN;
    m_LeftButtonSem = false;	// linke Maustaste bzw.
    m_RightButtonSem = false;	// rechte Maustaste noch nicht gedrückt
    m_iGrabCnt = 0;				// Anzahl der hintereinander gegrabten Punkte
    m_pGrabPktX = NULL;			// die in m_iGrabCnt gezählten GrabPunkte
    m_pGrabPktY = NULL;
    m_bIsPaint = false;			// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
    							// GEOVIEWEVT_ViewPainted ausgelöst) wird nicht gezeichnet

    m_pCT = new CoordTransX();	// KoordinatenTransformation

    if (! m_pCT)
    {
    	DEX_Error (RC_IslandAdd, EC_NOMEMORY);
    	return;
    }
}


// --------------------------------------------------------------------------------------------
// Destruktor
CIslandAdd::~CIslandAdd (void)
{
  	DELETE_OBJ (m_pCT);
	DELETE_VEC (m_pGrabPktX);
	DELETE_VEC (m_pGrabPktY);
    m_wDragObj.Assign (NULL);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur CObjectModify-Klasse über das Interface IModifyClassSite herstellen;
// es wird also von der Klasse CIslandAdd KEINE (!!) direkte Verbindung zu TRiAS über Interface
// ITriasExtension hergestellt
STDMETHODIMP CIslandAdd::SetModifyClassSite (IEditExtensionSite* pIEdExSite,
    										 IModifyClassSite*)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));

    		m_wEdExSite = pIEdExSite;
    		// die nachfolgende Zeile ist erforderlich, damit nach dem Zerlegen des Menüs, in
    		// dem diese Routine aufgerufen wurde, nicht der STERN- oder TRENNER-Cursor
    		// angezeigt wird (bei Aufruf des Menüs hat der Cursor diese Form)
    		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

    	WEnumObjektGeometrie wGrabObjs (CLSID_EnumObjektGeometrie);

    		m_wGrabObjs = wGrabObjs;
    	}
    	else
    	{
    		// Cursor wieder auf die Standard-Form "PFEIL" zurücksetzen
    		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
    		m_wTopObjs.Assign (NULL);	// freigeben
    		m_wEdExSite.Assign (NULL);	// freigeben
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // SetModifyClassSite


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::LineElongation (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CIslandAdd::LineElongation");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::AreaPartition (long, POINT)
{
    ATLTRACENOTIMPL("CIslandAdd::AreaPartition");
}


// --------------------------------------------------------------------------------------------
// die pBelowObjs-Objekte sind die Flächenobjekte, die bei Aufruf dieser Routine unter der
// Mausspitze lagen
STDMETHODIMP CIslandAdd::IslandAddition (IEnumObjektGeometrie* pBelowObjs)
{
	try
	{
		m_wBelowObjs = pBelowObjs;		// mit implizitem QueryInterface
	}
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // IslandAddition


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::Rectangularity (long, int, long, double, double, double,
    									 IEnumObjectsByNumber**)
{
    ATLTRACENOTIMPL("CIslandAdd::Rectangularity");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::MakeCommonBorder (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CIslandAdd::MakeCommonBorder");
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CIslandAdd::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CIslandAdd::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CIslandAdd::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
STDMETHODIMP CIslandAdd::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
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
    		break;

		case GEOVIEWEVT_ScrollingHorz:
			if (m_wDragObj.IsValid() &&			// es befindet sich ein DragLineObject im Aufbau
				SUCCEEDED (VariantChangeType (&vData, &vData, NULL, VT_I4)))
			{
			long lOffset = V_I4 (&vData);

				m_wDragObj->EditWithScrolling (lOffset, true);
				m_FirstPt.X() += lOffset;
				m_LastPt.X() += lOffset;
			}
    		break;

		case GEOVIEWEVT_ScrollingVert:
			if (m_wDragObj.IsValid() &&
				SUCCEEDED (VariantChangeType (&vData, &vData, NULL, VT_I4)))
			{
			long lOffset = V_I4 (&vData);

				m_wDragObj->EditWithScrolling (lOffset, false);
				m_FirstPt.Y() -= lOffset;
				m_LastPt.Y() -= lOffset;
			}
			break;
    }

    return S_OK;	// immer weiterleiten

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CIslandAdd::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    ATLTRACE("CIslandAdd::GeoObjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CIslandAdd::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CIslandAdd::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CIslandAdd::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CIslandAdd::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CIslandAdd::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
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
HRESULT CIslandAdd::KeyDown (WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste gedrückt, um Grabben auszuschalten
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);										  

    	if (CURSFORM_FANGEN == CF)	// Cursor hat FANGEN-Form
    	{
    	HRESULT hr;

    		if (! m_wIsland.IsValid())	// noch nicht mit Inselaufbau begonnen
    			hr = m_wTopObjs->CursorInSomeTopObjects (m_wBelowObjs, true, &m_NewCP);
    		else				// mit Inselaufbau schon begonnen
    			hr = m_wTopObjs->CursorInSomeTopObjects (m_wAndArea, true, &m_NewCP);

    		if (FAILED(hr)) return hr;

    		if (m_NewCP == m_OldCP) return S_OK;
    		m_OldCP = m_NewCP;				// CursorPosition retten

    		if (CURSPOS_OBJECT == m_NewCP)	// Cursor innerhalb eines ausgewählten Objektes
    			return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);	// CursorForm für Editierung
    		return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);		// Normalform
    	}
    }

    return S_OK;

} // KeyDown


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CIslandAdd::KeyUp (WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste losgelassen, um Grabben wieder zu ermöglichen
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);

    	if (CURSFORM_PFEIL == CF || CURSFORM_CROSS == CF)
    	{
    	// Cursor kann beim KeyUp() innerhalb einer Stützpunktmarkierung stehen, was aber durch
    	// das KeyDown() nicht abgetestet wurde; deshalb hier erneut eine Testung der
    	// CursorPosition
    	HRESULT hr;

    		if (! m_wIsland.IsValid())	// noch nicht mit Inselaufbau begonnen
    		{
    			if (S_OK != IsGrabAllowableForIslandAdd (m_wBelowObjs))	// Grabben nicht erlaubt
    				return S_FALSE;
    			hr = m_wTopObjs->CursorForIslandAdd (m_wBelowObjs, true, &m_NewCP);
    		}
    		else				// mit Inselaufbau schon begonnen
    		{
    			// als Parameter für IsGrabAllowableForIslandAdd() wird bewußt m_wModObjs und
    			// nicht m_wAndArea verwendet, da m_wModObjs-Inseln bei m_wAndArea zur
    			// Außenkontur gehören können
    			if (S_OK != IsGrabAllowableForIslandAdd (m_wModObjs))	// Grabben nicht erlaubt
    				return S_FALSE;
    			hr = m_wTopObjs->CursorForIslandAdd (m_wAndArea, true, &m_NewCP);
    		}

    		if (FAILED(hr)) return hr;

    		if (m_NewCP == m_OldCP) return S_OK;
    		m_OldCP = m_NewCP;		// CursorPosition retten

    		if (CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    			return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
    	}
    }

    return S_OK;
    
} // KeyUp


// --------------------------------------------------------------------------------------------
// Maus wurde bewegt
HRESULT CIslandAdd::MouseMove (HWND hWnd, LPARAM lParam)
{
	if (m_LeftButtonSem || m_RightButtonSem)	// wenn linke oder rechte Maustaste gedrückt
	 	return S_FALSE;							// ist, dann keine weitere Bearbeitung

    if (m_wDragObj.IsValid())
    {
    Point SPt = BSPoint (lParam);	// BS-Punkt der Mausspitze
	BOOL bTopIsPaint;	// wird in CTopicalObjects der Hintergrund gezeichnet?

    	m_wTopObjs->IsPaint (&bTopIsPaint);

    	// Hilfslinie, die auf dem Bildschirm die editierte Fläche immer gleich zuzieht,
    	// einmalig löschen
    	if (!m_bIsPaint && !bTopIsPaint && m_bCloseLineDelete)
    	{
    		DrawLine (m_FirstPt, m_LastPt, m_pVWnd);
    		m_bCloseLineDelete = false;
    	}

    	m_wDragObj->SetEndPoint ((POINT&)SPt, m_bIsPaint || bTopIsPaint, TRUE);

    	AktuelleWerteAnzeigen (SPt);	// aktuelle Werte in Statuszeile anzeigen
    }

HRESULT hr;

    if (! m_wIsland.IsValid())	// noch nicht mit Inselaufbau begonnen
    {
    	if (GetKeyState (VK_SHIFT) >= 0 &&	//  SHIFT-Taste nicht gedrückt, d.h. Grabben
    		S_OK == IsGrabAllowableForIslandAdd (m_wBelowObjs))	// Grabben erlaubt
    		hr = m_wTopObjs->CursorForIslandAdd (m_wBelowObjs, true, &m_NewCP);
    	else
    		hr = m_wTopObjs->CursorInSomeTopObjects (m_wBelowObjs, true, &m_NewCP);
    }

    else			// mit Inselaufbau schon begonnen
    {
    	// als Parameter für IsGrabAllowableForIslandAdd() wird bewußt m_wModObjs und nicht
    	// m_wAndArea verwendet, da m_wModObjs-Inseln bei m_wAndArea zur Außenkontur gehören
    	// können
    	if (GetKeyState (VK_SHIFT) >= 0 &&	//  SHIFT-Taste nicht gedrückt, d.h. Grabben
    		S_OK == IsGrabAllowableForIslandAdd (m_wModObjs))	// Grabben erlaubt
    		hr = m_wTopObjs->CursorForIslandAdd (m_wAndArea, true, &m_NewCP);
    	else
    		hr = m_wTopObjs->CursorInSomeTopObjects (m_wAndArea, true, &m_NewCP);
    }

    if (FAILED(hr)) return hr;

    if (m_NewCP == m_OldCP) return S_OK;
    m_OldCP = m_NewCP;				// CursorPosition retten

    if (CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    	return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
    if (CURSPOS_OBJECT == m_NewCP)	// Cursor innerhalb eines zulässigen Bereiches
    	return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);	// CursorForm für Editierung
    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);		// Normalform

} // MouseMove


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde für Hinzufügen einer neuen Insel gedrückt
HRESULT CIslandAdd::LeftMouseDown (LPARAM lParam)
{
    if (CURSPOS_VERTEX == m_NewCP || CURSPOS_OBJECT == m_NewCP)
    {
    	m_LeftButtonSem = true;			// linke Maustaste wurde gedrückt
    	m_LastPt = BSPoint (lParam);	// BS-Punkt, bei dem linke Maustaste gedrückt wurde
    	m_LastPkt = DBKoordinaten (m_LastPt);

    	if (! m_wModObjs.IsValid())
    	{
    		BuildModObjects();
    		m_pVWnd->MouseTrap (TRUE);
    	}

    	return S_OK;
    }

    // akustisches Signal, wenn Punkt außerhalb der m_wAndArea-Fläche, innerhalb derer die
    // Insel nur gebildet werden kann, liegt und somit nicht verwendet werden kann
    MessageBeep (MB_ICONEXCLAMATION);
    return S_FALSE;

} // LeftMouseDown


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde für Hinzufügen einer neuen Insel losgelassen
HRESULT CIslandAdd::LeftMouseUp (void)
{
    if (!m_LeftButtonSem)	// linke Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_LeftButtonSem = false;		// linke Maustaste wurde losgelassen

HRESULT hr = NewIslandObject();

    if (FAILED (hr))
    {
    	m_wDragObj->DragTerminate();
    	m_wDragObj.Assign (NULL);
    	return hr;
    }

    // Verbindung zum CDragMultiLine-Objekt über dessen Interface IDragObject herstellen
    try
    {
    WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    	m_wDragObj.Assign (NULL);
    	m_wDragObj = wDragObj;
    	m_wDragObj->AddStartPoint ((POINT&)m_FirstPt);
    	if (m_lInSize > 1)
    		m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
    	m_wDragObj->ConstructDragLines();
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    // wenn die aktuell editierte Kontur zusammen mit dem soeben hinzugekommenen Punkt aus
    // wenigstens 3 Stützpunkten besteht, dann die Hilfslinie, die diesen letzten Punkt mit dem
    // ersten Punkt dieser Kontur verbindet, beim nächsten MouseMove() löschen
    if (m_lInSize >= 3)
    	m_bCloseLineDelete = true;
    else
    	m_bCloseLineDelete = false;

    return S_OK;

} // LeftMouseUp


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde für Hinzufügen einer neuen Insel gedrückt
void CIslandAdd::RightMouseDown (LPARAM lParam)
{
    if (CURSPOS_VERTEX == m_NewCP || CURSPOS_OBJECT == m_NewCP)
    {
    	m_RightButtonSem = true;		// rechte Maustaste wurde gedrückt
    	m_LastPt = BSPoint (lParam);	// BS-Punkt, bei dem rechte Maustaste gedrückt wurde
    	m_LastPkt = DBKoordinaten (m_LastPt);

    	if (! m_wModObjs.IsValid()) BuildModObjects();
    }

    else
    // akustisches Signal, wenn Punkt außerhalb der m_wAndArea-Fläche, innerhalb derer die
    // Insel nur gebildet werden kann, liegt und somit nicht verwendet werden kann
    MessageBeep (MB_ICONEXCLAMATION);

} // RightMouseDown


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde für Hinzufügen einer neuen Insel losgelassen
HRESULT CIslandAdd::RightMouseUp (void)
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

HRESULT hr = NewIslandObject();

    if (FAILED (hr)) return hr;

ulong ulIdent = (ulong)-1;	// Objektklassenschlüssel für PropertyPage "CEditBaseDlg"

    SetObjectClassKey (m_wModObjs, ulIdent);

    // nach dem Hintergrundzeichnen nach einer möglichen Fehlermeldung wird wieder der
    // vorhergehende Cursor eingeschaltet; da das auch der GrabCursor sein kann, wird hier
    // einfach vorgebeugt
    m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);

ResString resCapt (ResID (IDS_CAPTISLANDADD, pRF), 40);
ulong ulCnt = 1;	// Anzahl der IObjektGeometrie'n
int iResult;		// Resultat der DialogBedienung

    m_wEdExSite->ShowEditDialog (resCapt.Addr(), g_cbGeoEditIslandAdd, ulCnt,
    							 (IUnknown**)&m_wIsland, &m_iGrabCnt, m_pGrabPktX, m_pGrabPktY,
    							 m_hrComBorder, m_lComONr, 0, NULL, NULL, &iResult);

    // m_wIsland würde erst durch den Destruktor ~CIslandAdd zerlegt werden; damit aber mehrere
    // Inseln editiert werden können, ohne das zwischendurch ~CIslandAdd gerufen wird, erfolgt
    // hier bei OK bzw. Cancel ein zwangsweises Zerlegen von m_wIsland
    if (IDOK == iResult || IDCANCEL == iResult)
    {
    	if (IDOK == iResult)
    		AddIsland (ulIdent);

		// Durchschnittsfläche der m_wModObjs-Flächen wieder löschen, wenn sie denn angelegt
		// worden ist; die nachfolgenden Zeilen waren schon einmal aus einem unbekannten Grund
		// heraus kommentiert, sie werden aber doch gebraucht (15.07.99)
		if (m_ulModCnt > 1 && m_lAndONr > 0)
		{
			DEX_DeleteObject (m_lAndONr);
			m_lAndONr = 0;
    		m_wAndArea.Assign (NULL);
		}
    	m_wIsland.Assign (NULL);

/* Können die nachfolgenden Zeilen wegen des am 24.02.99 in CGeoEditExtension::WindowsNotification
   (GeoEdit.cpp) eingefügten "case WM_MOUSEMOVE:" jetzt wegfallen ????????
	CursForm CF;	// wieder Erläuterung der aktuellen CursorForm in Statuszeile

		m_wEdExSite->GetCursor (&CF);
   		m_wEdExSite->SetCursor (CF, TRUE);
*/
		// über eine PostMessage wird CObjectModify mitgeteilt, daß das CIslandAdd-Objekt
		// wieder zerlegt werden kann
		PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);
    	return S_OK;
    }
    else if (IDB_CONTINUE == iResult)
    {
    	// Hintergrund nach Zerlegen des Dialogs sofort zeichnen, weil sonst ZUERST die neuen
    	// DragLine's gezeichnet werden, die dann durch das spätere Hintergrundzeichnen
    	// gelöscht werden; beim Löschen dieser DragLine's (durch invertiertes Zeichnen)
    	// während MouseMove() blieben sie dann unschönerweise stehen
    	m_pVWnd->Update();
    	hr = ContinueButtonAction();
    	if (FAILED (hr)) return hr;
    }
    else if (IDB_ISLAND == iResult)
    	IslandButtonAction (ulIdent);

    // Hilfslinie beim nächsten MouseMove() löschen (s. a. LeftMouseUp);
    // da der DeleteButton (mehrmals) gedrückt worden sein konnte, wird m_lInSize aktualisiert
    if (m_wIsland.IsValid())
    {
    	m_wIsland->GetCnt (&m_lInSize);

    	if (m_lInSize >= 3)
    		m_bCloseLineDelete = true;
    	else
    		m_bCloseLineDelete = false;
    }

    return S_OK;

} // RightMouseUp


// --------------------------------------------------------------------------------------------
// Doppelklick auf linke Maustaste
HRESULT CIslandAdd::LeftDoubleClick (void)
{
// Zeichenoperation beenden
    if (m_wDragObj.IsValid())
	{
		m_wDragObj->DragTerminate();
		m_wDragObj.Assign (NULL);
	}

    m_pVWnd->MouseTrap (FALSE);

// edititiertes Objekt (Fläche OHNE Innenkontur) (evtl.) noch schließen
KoOrd* plXK; KoOrd* plYK;
long lCnt;

	m_wIsland->GetX ((void**)&plXK);
	m_wIsland->GetY ((void**)&plYK);
	m_wIsland->GetCnt (&lCnt);

	if (lCnt >= 2 &&
		(plXK[0] != plXK[lCnt-1] ||	// Objekt ist noch nicht
		plYK[0] != plYK[lCnt-1]))	//  zugezogen
		m_wIsland->AddPunkt (plXK[0], plYK[0], -1, 0);	// zuziehen

// neue Innenkontur zu den m_wModObjs-Flächen hinzufügen
ulong ulIdent = (ulong)-1;	// Objektklassenschlüssel für AddIsland()

    SetObjectClassKey (m_wModObjs, ulIdent);

HRESULT hrRet = AddIsland (ulIdent);

// Bereich neu zeichnen
Rectangle Rec;	// umschließendes Rechteck des aktuell editierten Objektes

    m_wIsland->RectangleToDraw ((RECT*)&Rec);
    DEX_RePaintRectWait (Rec);
    m_pVWnd->Update();		// sofort zeichnen
   	m_wIsland.Assign (NULL);

/* Können die nachfolgenden Zeilen wegen des am 24.02.99 in CGeoEditExtension::WindowsNotification
   (GeoEdit.cpp) eingefügten "case WM_MOUSEMOVE:" jetzt wegfallen ????????
CursForm CF;	// wieder Erläuterung der aktuellen CursorForm in Statuszeile

    m_wEdExSite->GetCursor (&CF);
   	m_wEdExSite->SetCursor (CF, TRUE);
*/
	// über eine PostMessage wird CObjectModify mitgeteilt, daß das CIslandAdd-Objekt wieder
	// zerlegt werden kann
	PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);

	return hrRet;

} // LeftDoubleClick


// --------------------------------------------------------------------------------------------
// die m_wModObjs-Flächenobjekte, zu denen eine Innenkontur hinzugefügt werden soll, sind eine
// Untermenge von pBelowObjs und werden mit dem 1. LeftMouseDown() bzw. RightMouseDown()
// ermittelt; diese Unterscheidung ist notwendig, da IslandAddition() über ein Menü gerufen
// werden kann, das an einem gemeinsamen Konturabschnitt zweier sich nicht überlappender
// Flächen gebildet wurde; beide Flächen sind somit pBelowObjs-Objekte, aber logischerweise
// gibt es keine Innenkontur, die gleichzeitig in diesen beiden Flächen liegen kann
HRESULT CIslandAdd::BuildModObjects (void)
{
    if (m_wModObjs.IsValid())
    	return S_FALSE;		// es ist schon alles erledigt

    _ASSERTE (m_wBelowObjs.IsValid());

HRESULT hrRet = m_wTopObjs->NewVertexWithGrab ((POINT*)&m_LastPt, NULL, &m_LastPkt.X(),
											   &m_LastPkt.Y(), NULL);

Posit posLage;
WUnknown Unk;
short iOT;

    try
    {
    WEnumObjektGeometrie wModObjs (CLSID_EnumObjektGeometrie);

		for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

			wObj->GetObjTyp (&iOT);
    		if (OT_FLAECHE != iOT) continue;

    		wObj->Position (m_LastPkt.X(), m_LastPkt.Y(), false, &posLage);
    		if (INNERH == posLage || KONTUR == posLage)
    			wModObjs->AddItem (wObj);	// Inselbeginn innerhalb des wObj-Objektes
    	}

    	wModObjs->GetCount(&m_ulModCnt);
    	m_wModObjs = wModObjs;
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    BuildAndArea();		// Durchschnittsfläche aller wModObjs-Flächen ermitteln

    return S_OK;

} // BuildModObjects


// --------------------------------------------------------------------------------------------
// Durchschnittsfläche m_wAndArea aller wModObjs-Flächen ermitteln (wird für Anzeige des
// CROSS-Cursors benötigt)
HRESULT CIslandAdd::BuildAndArea (void)
{
ulong ulIdent;			// Objektklassenschlüssel für Durchschnittsfläche m_wAndArea
WObjektGeometrie wObj;	// ObjektGeometrie des lAndONr-Objektes
WUnknown Unk;

	m_lAndONr = 0;

    try
    {
    WEnumObjektGeometrie wAndArea (CLSID_EnumObjektGeometrie);

    	if (1 == m_ulModCnt)		// Insel nur für 1 Fläche
    	{
    		m_wModObjs->Reset();

    	HRESULT hr = m_wModObjs->Next (1, Unk.ppi(), NULL);

    		if (S_OK != hr) return hr;	// 05.03.99
			wObj = Unk;
    	}

    	else if (m_ulModCnt > 1)	// Insel für mehrere Flächen
    	{
    	WUnknown wObjOper;

    		// IExtendObjOper-Interface zuschalten
    		THROW_FAILED_HRESULT (m_wEdExSite->ObjOperInterface (wObjOper.ppi()));

    	WEnumLONG welAndArea (CLSID_EnumObjectsByNumber);
//    	WEnumObjektGeometrie welAndArea (CLSID_EnumObjektGeometrie);    noch nicht !!!!!!
		long lAndONr;	// Objektnummer für Durchschnittsfläche m_wAndArea

//			wObj->GetONr (&lAndONr);
//    		ulIdent = DEX_GetUnknownIdentEx (DEX_GetObjectProject (lAndONr));

		WEnumLONG wModObjs (CLSID_EnumObjectsByNumber);
		long lONr;
		WUnknown Unk;

			for (m_wModObjs->Reset(); S_OK == m_wModObjs->Next (1, Unk.ppi(), NULL); )
			{
			WObjektGeometrie wObj (Unk);

				wObj->GetONr (&lONr);

				_ASSERTE (lONr != 0);
				_ASSERTE (lONr != -1);

	    		((IEnum<LONG>*)(IEnumLONG*)wModObjs)->AddItem (lONr);
    		}

			// ulIdent ist eigentlich beliebig, da die Durchschnittsflächen nur temporär
			// erzeugt werden
    		ulIdent = DEX_GetUnknownIdentEx (DEX_GetObjectProject (lONr));

    		((WExtendObjOper)wObjOper)->AndArea (wModObjs, ulIdent, SFORM_TEMP,
												 welAndArea.ppi());

    	ulong ulAndCnt;	// Anzahl der Durchschnittsflächen

    		if (welAndArea.IsValid())
    			ulAndCnt = ((IEnum<LONG>*)(IEnumLONG*)welAndArea)->Count();
    		else
    		{
    		ResString resText (ResID (IDS_OBJOPERERR, pRF), 250);
    		ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    			
    			MessageBox (__hWndM, resText.Addr(), resCapt.Addr(),
							MB_ICONEXCLAMATION | MB_OK);
    			return E_UNEXPECTED;	// keine Durchschnittsfläche gebildet
    		}

    		if (1 == ulAndCnt)	// nur eine Durchschnittsfläche
    		{
    			welAndArea->Reset();

    		HRESULT hr = welAndArea->Next (1, &lAndONr, NULL);

		      	if (S_OK != hr) return hr;	// 05.03.99

    		WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

   				THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lAndONr));
   				wObj = wIObj;
  			}

    		// wenn es mehrere Durchschnittsflächen gibt, dann diejenige suchen, innerhalb
    		// derer der Punkt m_LastPkt liegt
    		else if (ulAndCnt > 1)
    		{
    		Posit posLage;
    		WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);
    		HRESULT hr;

    			for (welAndArea->Reset(); S_OK == (hr = welAndArea->Next (1, &lAndONr, NULL)); )
    			{
    				THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lAndONr));

    				wObj = wIObj;
//				for (welAndArea->Reset(); S_OK == (hr = welAndArea->Next (1, Unk.ppi(), NULL)); )
//				{
//	    		WObjektGeometrie wObj (Unk);	// ObjektGeometrie einer Durchschnittsfläche

    				wObj->Position (m_LastPkt.X(), m_LastPkt.Y(), false, &posLage);
    				if (INNERH == posLage || KONTUR == posLage)
					{
						m_lAndONr = lAndONr;
    					break;
					}
    			}

    			_ASSERTE (S_OK == hr);
    		}

    		_ASSERTE (ulAndCnt >= 1);
    	}

    	_ASSERTE (m_ulModCnt >= 1);

    	if (wObj.IsValid())
    	{
    		THROW_FAILED_HRESULT (wAndArea->AddItem (wObj));
    		m_wAndArea = wAndArea;
    		VisalAndArea (ulIdent);	// Durchschnittsfläche visualisieren
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // BuildAndArea


// --------------------------------------------------------------------------------------------
// Durchschnittsfläche visualisieren
void CIslandAdd::VisalAndArea (ulong ulIdent)
{
    if (1 == m_ulModCnt)
    	return;

// "ungefüllte" Flächenfüllung, damit die Durchschnittsfläche nicht gesehen wird
HANDLEVISINFO HVI;
FVISINFO FVI;

    INITSTRUCT (HVI, HANDLEVISINFO);
	memset (&FVI, '\0', sizeof (FVISINFO));
#if _TRiAS_VER >= 0x0300
	FVI.m_VI.dwSize = sizeof (tagFVISINFO);
#endif

    HVI.m_lIdent = ulIdent;
    HVI.m_iVTyp = VTFlaeche;		// VisInfoTyp
    HVI.m_pVI = &FVI.m_VI;			// generischer Pointer auf VisInfo
    // beschreibender Text (HVI.m_pDesc = NULL) und Name der aktuellen Sicht
    // (HVI.m_pView = NULL) wurden durch INITSTRUCT (HVI, HANDLEVISINFO) gesetzt
    
    // Füllmode "ungefüllt" (FVI.m_VI.m_Style = 0), niedrigste Zeichenpriorität
    // (FVI.m_VI.m_Priority = 0), Konturfarbe "schwarz" (FVI.m_VI.m_C = RGB (0, 0, 0)) und
    // Konturbreite (FVI.m_iWidth = 0) werden durch memset (&FVI, ...) gesetzt 
    
    DEX_ModIdentVisInfo (HVI);

} // VisalAndArea


// --------------------------------------------------------------------------------------------
// Test, ob Grab-Funktion möglich ist; dann return-Wert S_OK, sonst E_FAIL;
// Ein einmaliges Grabben der neu editierten Innenkontur ist mit jeder anderen Kontur erlaubt.
HRESULT CIslandAdd::IsGrabAllowableForIslandAdd (IEnumObjektGeometrie* pIEnumOG)
{
// 1. Ist die Anzahl der Berührungen für alle Konturen == 0 ? ja -> S_OK
// 2. nein: Ist Cursor in irgend einem Marker? nein -> S_OK
// 3. ja: Von welcher Kontur-Nr ?
//    Ist von dieser Kontur die Anzahl der Berührungen == 0 ? ja -> S_OK
//    nein -> E_FAIL

// Die Anzahl der Berührungen wird in L/RMouseDown inkrementiert.
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// neue Innenkontur erst einmal als separates Flächenobjekt m_wIsland editieren
HRESULT CIslandAdd::NewIslandObject (void)
{
// m_LastPkt evtl. durch Grabben noch modifizieren und alle Linien- bzw. Flächenobjekte der
// ausgewählten Objekte in wActGrabObjs einsammeln, die den (falls vorhanden) GrabPunkt als
// Stützpunkt besitzen
//WEnumObjectsByNumber wActGrabObjs;
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
    		m_pGrabPktX = new KoOrd [iComCnt];	// iComCnt ist in EditKonst.h definiert
    		m_pGrabPktY = new KoOrd [iComCnt];
    		if (!m_pGrabPktX || !m_pGrabPktY)
    		{
	 			DELETE_VEC (m_pGrabPktX);
    			DEX_Error (RC_NewLine, EC_NOMEMORY);
    			return false;
    		}
    	}

    	m_lComONr = 0;	// Objektnummer des Objektes, von dem die gemeinsamen Stützpunkte bei
    					// CommonBorder übernommen werden können

    	m_hrComBorder = IsCommonBorderAllowable (m_iGrabCnt, wActGrabObjs, m_wGrabObjs,
    											 m_lComONr);

		if (0 != m_lComONr && -1 != m_lComONr)
		{
		int iOT = DEX_GetObjectType (m_lComONr);

			if (OT_FLAECHE == iOT && m_iGrabCnt > 3)
			{
				m_pGrabPktX[0] = m_pGrabPktX[1];
				m_pGrabPktY[0] = m_pGrabPktY[1];
				m_pGrabPktX[1] = m_pGrabPktX[2];
				m_pGrabPktY[1] = m_pGrabPktY[2];
				m_iGrabCnt--;
			}
			else if (OT_KANTE == iOT && m_iGrabCnt > 2)
			{
				m_pGrabPktX[0] = m_pGrabPktX[1];
				m_pGrabPktY[0] = m_pGrabPktY[1];
				m_iGrabCnt--;
			}
		}

		_ASSERTE (m_iGrabCnt <= iComCnt);

    	m_pGrabPktX[m_iGrabCnt-1] = m_LastPkt.X();
		m_pGrabPktY[m_iGrabCnt-1] = m_LastPkt.Y();

    	// es wurde gegrabt, deshalb m_dAktDreieck korrigieren
    	m_dAktDreieck = DreieckInhalt (m_LastPt, m_FirstPkt, m_LastPkt, m_pCT);
    }

    if (! m_wIsland.IsValid())	// aus dem 1. editierten Stützpunkt Anfang einer Insel aufbauen
    {						
    	SetStartingContents();	// Gesamtflächeninhalt initialisieren
    	m_dAktInsel = 0.0;

    HRESULT hr = CreateInterfaceOG (m_wIsland.ppi(), m_LastPkt.X(), m_LastPkt.Y(),
    								OT_FLAECHE);
    	if (FAILED(hr)) return hr;

    	m_FirstPkt = m_LastPkt;
    	m_FirstPt = m_LastPt;

    	m_lInSize = 1;		// Größe der aktuell editierten Insel
    }

    else			// weitere Stützpunkte wurden editiert
    {
    HRESULT hr = m_wIsland->AddPunkt (m_LastPkt.X(), m_LastPkt.Y(), -1, 0);

    	if (FAILED (hr)) return hr;

    	m_dAktInsel += m_dAktDreieck;
    	m_lInSize++;		// Größe der aktuell editierten Insel
    }

    return S_OK;

} // NewIslandObject


// --------------------------------------------------------------------------------------------
// ContinueButton in der PropertySheet gedrückt
HRESULT CIslandAdd::ContinueButtonAction (void)
{
// Das Drücken eines Buttons bzw. die Korrektur des letzten Koordinatenpaars durch den Anwender
// kann den Punkt, an dem fortgesetzt werden soll, verändern. Deshalb ist dieser Punkt neu zu
// ermitteln. Außerdem ist der Gesamtflächeninhalt neu zu berechnen.
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    m_wIsland->GetCnt (&lCnt);
    m_wIsland->GetX ((void**)&plXK);
    m_wIsland->GetY ((void**)&plYK);

    SetStartingContents();	// Gesamtflächeninhalt neu berechnen

double dAktInsel;			// Flächeninhalt der aktuellen Insel

    AreaSize (plXK, plYK, 0, lCnt-1, m_pCT, &dAktInsel);
    m_dAktGesFlaeche -= dAktInsel;
    m_dAktInsel = 0.;
    m_dAktDreieck = 0.;

    m_LastPt = BSKoordinaten (plXK[lCnt-1], plYK[lCnt-1]);
    m_LastPkt.X() = plXK[lCnt-1];
    m_LastPkt.Y() = plYK[lCnt-1];

    try
    {
    WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    	m_wDragObj.Assign (NULL);
    	m_wDragObj = wDragObj;
    	m_wDragObj->AddStartPoint ((POINT&)m_FirstPt);
    	if (m_lInSize > 1)
    		m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
    	m_wDragObj->ConstructDragLines();
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    m_pVWnd->MouseTrap (TRUE);

    return S_OK;

} // ContinueButtonAction


// --------------------------------------------------------------------------------------------
// IslandButton in der PropertySheet gedrückt;
// zu den m_wModObjs-Objekten wird die m_wIsland-Innenkontur sofort hinzugefügt und
// anschließend der Aufbau einer weiteren m_wIsland-Innenkontur vorbereitet
void CIslandAdd::IslandButtonAction (ulong ulIdent)
{
    AddIsland (ulIdent);

int iMarkGr;	// Markergröße
Rectangle Rec;	// umschließendes Rechteck der aktuell editierten Insel

    m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
    m_wIsland->RectangleToDraw2 ((RECT*)&Rec, iMarkGr);
    DEX_RePaintRectWait (Rec);
    m_pVWnd->Update();		// sofort zeichnen

    m_wIsland.Assign (NULL);

/* Können die nachfolgenden Zeilen wegen des am 24.02.99 in CGeoEditExtension::WindowsNotification
   (GeoEdit.cpp) eingefügten "case WM_MOUSEMOVE:" jetzt wegfallen ????????
CursForm CF;	// wieder Erläuterung der aktuellen CursorForm in Statuszeile

	m_wEdExSite->GetCursor (&CF);
   	m_wEdExSite->SetCursor (CF, TRUE);
*/
} // IslandButtonAction


// --------------------------------------------------------------------------------------------
// das editierte m_wIsland-Flächenobjekt als Innenkontur zu m_wModObjs-Flächen hinzufügen
HRESULT CIslandAdd::AddIsland (ulong ulIdent)
{
long lInCnt;		// Parameter der neuen Insel
KoOrd* plInX; KoOrd* plInY;

    m_wIsland->GetCnt (&lInCnt);
    m_wIsland->GetX ((void**)&plInX);
    m_wIsland->GetY ((void**)&plInY);

short iOT;
WUnknown Unk;

    try
    {
		for (m_wModObjs->Reset(); S_OK == m_wModObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

			wObj->GetObjTyp (&iOT);
    		if (OT_FLAECHE != iOT) continue;
    		wObj->AddKante (plInX, plInY, lInCnt, -1);

    		StoreAreaWithNewIsland (wObj, ulIdent);
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // AddIsland


// --------------------------------------------------------------------------------------------
// Objekt, zu dem eine neue Insel hinzugefügt wurde, abspeichern 
HRESULT CIslandAdd::StoreAreaWithNewIsland (IObjektGeometrie* pIOG, ulong ulIdent)
{
ulong ulNewIdent = DEX_GetLastIdent();

#if _TRiAS_VER < 0x0300
	if (0 == DEX_GetROMode())					// Datenbank nicht schreibgeschützt (R/W-Modus)
#else
	if (0 == DEX_GetROModeIdent (ulNewIdent))	// Objektklasse nicht schreibgeschützt
#endif // _TRiAS_VER < 0x0300

    	// OGModObject:     Geometrie des Objektes ersetzen
    	// OGAskWhenError:  im Fehlerfall wird Anwender vor dem Abspeichern noch einmal gefragt
    	// OGAddToView:     (evtl. veränderten) Identifikator zur Sicht hinzufügen
    	pIOG->SetFlags (OGModObject | OGAskWhenError | OGAddToView);
    else
    	// OGTempObject:	temporäres Objekt
    	pIOG->SetFlags (OGTempObject);

    if (ulIdent != ulNewIdent)
    	pIOG->SetIdent (ulNewIdent);

#if _TRiAS_VER < 0x0300
HRESULT hrRet = pIOG->GeometrieAnTRiAS (true, NULL);
#else
INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulNewIdent));
HRESULT hrRet = pIOG->GeometrieAnTRiASEx (hPr, true, NULL);
#endif // _TRiAS_VER < 0x0300
	
    // wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Hinzunahme der Insel
    // rückgängig machen
    if (S_OK != hrRet)
    	pIOG->SubKante (1, -1);

int iMarkGr;	// Markergröße
Rectangle Rec;	// rechteckiger Bereich, der gezeichnet werden soll

	m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
	pIOG->RectangleToDraw2 ((RECT*)&Rec, iMarkGr);
	DEX_RePaintRectWait (Rec);

	return hrRet;

} // StoreAreaWithNewIsland


// --------------------------------------------------------------------------------------------
// Gesamtflächeninhalt initialisieren; wenn nur eine Fläche mit einer Innenkontur ergänzt
// werden soll, dann noch den bisherigen Flächeninhalt hinzurechnen
HRESULT CIslandAdd::SetStartingContents (void)
{
    m_dAktGesFlaeche = 0.0;

    if (m_ulModCnt > 1) return S_FALSE;

    m_wModObjs->Reset();

WUnknown Unk;
HRESULT hrRet = m_wModObjs->Next (1, Unk.ppi(), NULL);

	if (S_OK != hrRet) return hrRet;	// 05.03.99

WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes

    try
    {
    	wObj = Unk;
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    GetInhalt (wObj, m_pCT, &m_dAktGesFlaeche);	// Gesamtflächeninhalt berechnen

    return S_OK;

} // SetStartingContents


// --------------------------------------------------------------------------------------------
// aktuellen Flächeninhalt in Statuszeile anzeigen
bool CIslandAdd::AktuelleWerteAnzeigen (Point Pt)
{
    if (! m_wIsland.IsValid())	// der 1. Punkt der zu editierenden Insel ist noch nicht gesetzt
    	return false;	// deshalb keinen aktuellen Flächeninhalt anzeigen

    m_dAktDreieck = DreieckInhalt (Pt, m_FirstPkt, m_LastPkt, m_pCT);

string sOutBuff = ResString (ResID (IDS_AKTINSEL, pRF), 40);

    FlInhaltNormieren (fabs(m_dAktInsel + m_dAktDreieck), sOutBuff);
    sOutBuff += ";  ";

    // die aktuell editierte Insel wird nur zu EINEM Flächenobjekt hinzugefügt
    if (1 == m_ulModCnt)
    {
    // aktueller Zwischenstand des Flächeninhalts
    double dZwFlInh = m_dAktGesFlaeche - fabs(m_dAktInsel + m_dAktDreieck);

    	sOutBuff += ResString (ResID (IDS_GESAMTINHALT, pRF), 40);

    	FlInhaltNormieren (dZwFlInh, sOutBuff);
    }

    // wenn die aktuell editierte Insel gleichzeitig mehreren Flächenobjekten hinzugefügt
    // werden soll, kann der ursprüngliche Flächeninhalt nicht automatisch hinzugenommen werden
    else
    {
    	sOutBuff += "ursprünglicher Flächeninhalt - ";
    	FlInhaltNormieren (fabs(m_dAktInsel + m_dAktDreieck), sOutBuff);
    }

    DEX_SetMessageStringNoKickIdle (sOutBuff.c_str());

    return true;

} // AktuelleWerteAnzeigen
