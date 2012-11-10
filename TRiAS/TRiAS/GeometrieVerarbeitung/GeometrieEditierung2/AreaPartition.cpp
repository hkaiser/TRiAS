// Definitionen: Flächenobjekt teilen
// File: AreaPartition.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "IntersectLineDlg.h"	// CIntersectionLineDlg

#include "AreaPartition.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CAreaPartition::CAreaPartition (void)
{
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    m_NewCP = CURSPOS_UNKNOWN;
    m_OldCP = CURSPOS_UNKNOWN;
    m_LeftButtonSem = false;	// linke Maustaste bzw.
    m_RightButtonSem = false;	// rechte Maustaste noch nicht gedrückt
    m_bIsPaint = false;			// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
    							// GEOVIEWEVT_ViewPainted ausgelöst) wird nicht gezeichnet
}


// --------------------------------------------------------------------------------------------
// Destruktor
CAreaPartition::~CAreaPartition (void)
{
    m_wDragObj.Assign (NULL);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur CObjectModify-Klasse über das Interface IModifyClassSite herstellen;
// es wird also von der Klasse CAreaPartition KEINE (!!) direkte Verbindung zu TRiAS über
// Interface ITriasExtension hergestellt
STDMETHODIMP CAreaPartition::SetModifyClassSite (IEditExtensionSite* pIEdExSite,
    											 IModifyClassSite*)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));

    		m_wEdExSite = pIEdExSite;
    		m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);
    	}
    	else
    	{
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
STDMETHODIMP CAreaPartition::LineElongation (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CAreaPartition::LineElongation");
}


// --------------------------------------------------------------------------------------------
// Schnittlinie für Teilung der lONr-Fläche aufbauen; bei PTRM wurde die rechte Maustaste
// gedrückt, hier beginnt also die Schnittlinie
STDMETHODIMP CAreaPartition::AreaPartition (long lONr, POINT PTRM)
{
    if (OT_FLAECHE != DEX_GetObjectType (lONr))
    	return E_UNEXPECTED;

    m_lONr = lONr;

EPunkt LastPkt;	// Punkt auf der Außenkontur der lONr-Fläche, der aus dem PTRM-Point, bei dem
    			// die rechte Maustaste gedrückt wurde, gebildet wurde

    try
    {
    WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

    	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

    	m_wAreaObj = wIObj;
    	m_wAreaObj->GetX ((void**)&m_plX);
    	m_wAreaObj->GetY ((void**)&m_plY);
    	m_wAreaObj->GetLPCnt (&m_plCnt);

	long lPInd, lSInd;	// Parameter von NearestPointToObject(); werden hier nicht ausgewertet
	EPunkt PktRM = DBKoordinaten ((Point&)PTRM);

    	LastPkt = NearestPointToObject (PktRM, m_wAreaObj, 0, m_plCnt[0]-1, true, &lPInd,
										&lSInd);
    	m_LastPt = BSKoordinaten (LastPkt.X(), LastPkt.Y());

    // Verbindung zum CDragMultiLine-Objekt über dessen Interface IDragObject herstellen
    WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    	m_wDragObj.Assign (NULL);
    	m_wDragObj = wDragObj;
    	m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
    	m_wDragObj->ConstructDragLines();
    }

    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

// mit dem auf die Außenkontur gezogenen Punkt die Schnittlinie beginnen
HRESULT hr = CreateInterfaceOG (m_wSectLine.ppi(), LastPkt.X(), LastPkt.Y(), OT_KANTE);

    if (FAILED(hr)) return hr;

    return S_OK;

} // AreaPartition


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::IslandAddition (IEnumObjektGeometrie*)
{
    ATLTRACENOTIMPL("CAreaPartition::IslandAddition");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::Rectangularity (long, int, long, double, double, double,
    										 IEnumObjectsByNumber**)
{
    ATLTRACENOTIMPL("CAreaPartition::Rectangularity");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::MakeCommonBorder (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CAreaPartition::MakeCommonBorder");
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CAreaPartition::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CAreaPartition::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CAreaPartition::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
STDMETHODIMP CAreaPartition::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
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
STDMETHODIMP CAreaPartition::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CAreaPartition::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    ATLTRACE("CAreaPartition::GeoObjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CAreaPartition::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CAreaPartition::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaPartition::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CAreaPartition::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CAreaPartition::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
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
    		MouseMove (lParam);
			break;

    	case WM_LBUTTONDOWN:
    		LeftMouseDown (lParam);
			break;

    	case WM_LBUTTONUP:
    		LeftMouseUp ((HWND)hWnd);
			break;

    	case WM_RBUTTONDOWN:
    		RightMouseDown (lParam);
    		break;

    	case WM_RBUTTONUP:
    		RightMouseUp ((HWND)hWnd);
    }

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde gedrückt
HRESULT CAreaPartition::KeyDown (WPARAM wParam)
{
    if (VK_SHIFT == wParam)		// SHIFT-Taste gedrückt, um Grabben auszuschalten
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);										  

    	if (CURSFORM_FANGEN == CF)	// Cursor hat FANGEN-Form
    		return m_wEdExSite->SetCursor (CURSFORM_STERN, TRUE);
    }
    return S_OK;

} // KeyDown


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CAreaPartition::KeyUp (WPARAM wParam)
{
    if (VK_SHIFT == wParam)			// SHIFT-Taste losgelassen
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);

    	if (CURSFORM_STERN == CF &&		// Cursor hat noch STERN-Form
    		CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    		return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
    }

    return S_OK;

} // KeyUp


// --------------------------------------------------------------------------------------------
// Maus wurde bewegt
HRESULT CAreaPartition::MouseMove (LPARAM lParam)
{
    if (m_LeftButtonSem || m_RightButtonSem)	// wenn linke oder rechte Maustaste gedrückt
    	return S_FALSE;							// ist, dann keine weitere Bearbeitung

    if (m_wDragObj.IsValid())
    {
	Point SPt = BSPoint (lParam);	// BS-Punkt der Mausspitze
	BOOL bTopIsPaint;	// wird in CTopicalObjects der Hintergrund gezeichnet?

    	m_wTopObjs->IsPaint (&bTopIsPaint);
    	m_wDragObj->SetEndPoint ((POINT&)SPt, m_bIsPaint || bTopIsPaint, TRUE);
    }

HRESULT hr = m_wTopObjs->CursorForAreaPartition (m_wAreaObj, &m_NewCP, &m_lGrabX, &m_lGrabY);

    if (FAILED(hr)) return hr;

    if (m_NewCP == m_OldCP) return S_OK;

    m_OldCP = m_NewCP;	// bisherige CursorPosition retten

    if (CURSPOS_VERTEX == m_NewCP)	// Cursor in einer Stützpunktmarkierung
    {
    	if (GetKeyState (VK_SHIFT) >= 0)	//  SHIFT-Taste nicht gedrückt
    		return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
    	return m_wEdExSite->SetCursor (CURSFORM_STERN, TRUE);
    }
    if (CURSPOS_LINE == m_NewCP)	// Cursor in der Nähe einer Strecke
    	return m_wEdExSite->SetCursor (CURSFORM_TRENNER, TRUE);
    if (CURSPOS_OBJECT == m_NewCP)	// Cursor innerhalb des zu teilenden Objektes
    	return m_wEdExSite->SetCursor (CURSFORM_CROSS, TRUE);	// CursorForm für Editierung
    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);		// Normalform

    return S_OK;
} // MouseMove


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde bei der Schnittlinienbildung gedrückt
HRESULT CAreaPartition::LeftMouseDown (LPARAM lParam)
{
    if (CURSPOS_VERTEX == m_NewCP || CURSPOS_LINE == m_NewCP || CURSPOS_OBJECT == m_NewCP)
    {
    	m_LeftButtonSem = true;			// linke Maustaste wurde gedrückt
	 	m_LastPt = BSPoint (lParam);	// BS-Punkt, bei dem linke Maustaste gedrückt wurde

	EPunkt LastPkt = DBKoordinaten (m_LastPt);	// DB-Punkt

    	THROW_FAILED_HRESULT (m_wSectLine->AddPunkt (LastPkt.X(), LastPkt.Y(), -1, -1));

    	// Verbindung zum CDragMultiLine-Objekt über dessen Interface IDragObject herstellen
    	try
    	{
    	WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    		m_wDragObj.Assign (NULL);
    		m_wDragObj = wDragObj;
    		m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
    		m_wDragObj->ConstructDragLines();
    	}
    	catch (_com_error& e)
    	{
    		return _COM_ERROR (e);
    	}

    	// eigentlich reicht ein MouseTrap(TRUE) nach dem ERSTEN LeftMouseDown()
    	m_pVWnd->MouseTrap (TRUE);
    	return S_OK;
    }

	// akustisches Signal, wenn Punkt außerhalb der zu teilenden Fläche liegt und damit für
    // die Schnittlinie nicht verwendet wird
    MessageBeep (MB_ICONEXCLAMATION);
    return S_FALSE;

} // LeftMouseDown


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde bei der Schnittlinienbildung losgelassen
HRESULT CAreaPartition::LeftMouseUp (HWND hWnd)
{
    if (!m_LeftButtonSem)	// linke Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_LeftButtonSem = false;		// linke Maustaste wurde losgelassen
    return S_OK;

} // LeftMouseUp


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde bei der Schnittlinienbildung gedrückt
void CAreaPartition::RightMouseDown (LPARAM lParam)
{
    m_RightButtonSem = true;	// rechte Maustaste wurde gedrückt

	m_LastPt = BSPoint (lParam);	// BS-Punkt, bei dem rechte Maustaste gedrückt wurde

    // wenn sich Cursor in einer Stützpunktmarkierung oder "in der Nähe" der Außenkontur
	// befindet, gilt der gesetzte Punkt immer als innerhalb der zu teilenden Fläche liegend,
    // da der Cursor nicht umgestellt wird, falls er "in die Nähe" einer Innenkontur gerät
    if (CURSPOS_VERTEX == m_OldCP || CURSPOS_LINE == m_OldCP)
    	return;

    if (CURSPOS_VERTEX != m_NewCP && CURSPOS_LINE != m_NewCP && CURSPOS_OBJECT != m_NewCP)
    {
	 	// akustisches Signal, wenn Punkt außerhalb der zu teilenden Fläche liegt und damit
    	// für die Schnittlinie nicht verwendet wird
    	MessageBeep (MB_ICONEXCLAMATION);

    	// dieser Fall ist gleichbedeutend mit "rechte Maustaste nicht gedrückt"
    	m_RightButtonSem = false;
    }

} // RightMouseDown


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde bei der Schnittlinienbildung losgelassen
HRESULT CAreaPartition::RightMouseUp (HWND hWnd)
{
    if (CURSPOS_OUTSIDE == m_OldCP)
    {
    	m_RightButtonSem = false;
    	return S_FALSE;
    }

    return SectionDialog();

} // RightMouseUp


// --------------------------------------------------------------------------------------------
// Dialog bei Drücken der rechten Maustaste
HRESULT CAreaPartition::SectionDialog (void)
{
    _ASSERTE (m_wSectLine.IsValid());

    if (! m_wSectLine.IsValid()) return E_POINTER;

EPunkt LastPkt;		// letzter editierter bzw. rangezogener Punkt in DB-Koordinaten
long lPInd, lSInd;	// Parameter von NearestPointToObject(); werden hier nicht ausgewertet

	// editierten Punkt VOR Abschluß der Bildung der Schnittlinie ermitteln
   	LastPkt = DBKoordinaten (m_LastPt);	// diese Zeile wird jetzt immer gebraucht
										// wegen NearestPointToObject()  (07.01.99)
	// editierten Punkt NACH Beendigung der Bildung der Schnittlinie ermitteln
    if (CURSPOS_VERTEX == m_OldCP)
    {
    CursForm CF;	// aktuelle CursorForm

    	m_wEdExSite->GetCursor (&CF);										  

    	if (CURSFORM_FANGEN == CF)	// Cursor hat FANGEN-Form
    	{
    		LastPkt.X() = m_lGrabX;
    		LastPkt.Y() = m_lGrabY;
    	}
    	else
    		LastPkt = NearestPointToObject (LastPkt, m_wAreaObj, 0, m_plCnt[0]-1, true,
											&lPInd, &lSInd);
    }

    else if (CURSPOS_LINE == m_OldCP)
    	LastPkt = NearestPointToObject (LastPkt, m_wAreaObj, 0, m_plCnt[0]-1, true, &lPInd,
										&lSInd);

// letzten editierten bzw. rangezogenen Punkt hinzufügen
HRESULT hr = m_wSectLine->AddPunkt (LastPkt.X(), LastPkt.Y(), -1, -1);

    if (S_OK != hr) return hr;

EPunkt EP1 = DBKoordinaten (m_LastPt);	// der letzte unkorrigierte editierte Stützpunkt

    // wenn der letzte editierte Stützpunkt noch korrigiert wurde, dann die letzte Strecke auch
    // auf dem Bildschirm korrigieren
    if (EP1.X() != LastPkt.X() || EP1.Y() != LastPkt.Y())
    {
    EPunkt EP2;		// manuell editierte Stützpunkte
    long lCnt;
    KoOrd* plXK; KoOrd* plYK;

    	m_wSectLine->GetCnt (&lCnt);
    	m_wSectLine->GetX ((void**)&plXK);
    	m_wSectLine->GetY ((void**)&plYK);

    	EP2.X() = plXK[lCnt-2];	//  der vorletzte manuell editierte Stützpunkt
    	EP2.Y() = plYK[lCnt-2];
    	DrawLine (EP2, EP1, false, m_pVWnd);		// Linie auf Bildschirm löschen
    	DrawLine (EP2, LastPkt, false, m_pVWnd);	// Linie neu zeichnen
    }

CIntersectionLineDlg ILDlg (m_wSectLine);
    	
// DialogCaption modifizieren
ResString resCapt (ResID (IDS_FLTEILEN, pRF), 40);

    ILDlg.SetCaption (resCapt.Addr());

// Text des OKButtons modifizieren
// VOR Abschluß der Bildung der Schnittlinie: OKButton wird zum ContinueButton
ResString resText (ResID (IDS_CONTBUTTON, pRF), 20);
bool bTeilen = false;	// OKButton ist nicht Teilen-Button

    // NACH Beendigung der Bildung der Schnittlinie: OKButton wird zum Teilen-Button
    if (CURSPOS_VERTEX == m_OldCP || CURSPOS_LINE == m_OldCP)
    {
    	resText = ResString (ResID (IDS_SPLITBUTTON, pRF), 20);
    	bTeilen = true;		// OKButton ist Teilen-Button
    }
    else
    	_ASSERTE (CURSPOS_OBJECT == m_OldCP);

    ILDlg.SetOKButtonText (resText.Addr());

    m_pVWnd->MouseTrap (FALSE);

// Position dieses Dialoges bestimmen und positionieren
Point Pt = DialogPosition (m_wSectLine, ILDlg.GetSize());

    ILDlg.ChangePosition (Pt);
    ILDlg.Show();
    
AktNeu Erg = (AktNeu) ILDlg.Result(); // Rückgabewert der Aktion im ILDlg-DialogFenster

    if (OK == Erg)
    {                                                                                     
    	if (bTeilen)
		{
    	HRESULT hr = AreaSplitting();

			// über eine PostMessage wird CModifyObject mitgeteilt, daß das CAreaPartition-Objekt
			// wieder zerlegt werden kann
			PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);
			return hr;
		}

    	// Hintergrund nach Zerlegen des Dialogs sofort zeichnen, weil sonst ZUERST die neue
    	// DragLine gezeichnet wird, die dann durch das spätere Hintergrundzeichnen gelöscht
    	// wird
    	m_pVWnd->Update();
    	return ContinueButtonAction();
    }

	PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);

	if (ABBRECHEN == Erg)
    {
    Rectangle Rec;	// rechteckiger Bereich, der gezeichnet werden soll

    	m_wSectLine->RectangleToDraw ((RECT*)&Rec);	// Schnittlinie auf Bildschirm löschen
    	DEX_RePaintRectWait (Rec);
    	return S_FALSE;
    }

    _ASSERTE (false);
    return E_UNEXPECTED;

} // SectionDialog


// --------------------------------------------------------------------------------------------
// ContinueButton gedrückt
HRESULT CAreaPartition::ContinueButtonAction (void)
{
// Das Drücken des DeleteButtons bzw. die Korrektur des letzten Koordinatenpaars durch den
// Anwender kann den Punkt, an dem fortgesetzt werden soll, verändern. Deshalb ist dieser Punkt
// neu zu ermitteln.
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    m_wSectLine->GetCnt (&lCnt);
    m_wSectLine->GetX ((void**)&plXK);
    m_wSectLine->GetY ((void**)&plYK);

    m_LastPt = BSKoordinaten (plXK[lCnt-1], plYK[lCnt-1]);

    try
    {
    WDragObject wDragObj (CLSID_DragMultiLine);	// throws_com_error

    	m_wDragObj.Assign (NULL);
    	m_wDragObj = wDragObj;
    	m_wDragObj->AddStartPoint ((POINT&)m_LastPt);
    	m_wDragObj->ConstructDragLines();
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    // wurde beim RightMouseDown(), das dem Dialog voraus geht, auf "true" gestzt
    m_RightButtonSem = false;

    m_pVWnd->MouseTrap (TRUE);

    return S_OK;

} // ContinueButtonAction


// --------------------------------------------------------------------------------------------
// Flächenobjekt teilen
HRESULT CAreaPartition::AreaSplitting (void)
{
WUnknown wObjOper;

// IExtendObjOper-Interface zuschalten
HRESULT hrRet = m_wEdExSite->ObjOperInterface (wObjOper.ppi());

    if (FAILED (hrRet))
	{
	// Schnittlinie auf Bildschirm wieder löschen
    Rectangle Rec;	// rechteckiger Bereich, der gezeichnet werden soll

    	m_wSectLine->RectangleToDraw ((RECT*)&Rec);	// Schnittlinie auf Bildschirm löschen
    	DEX_RePaintRectWait (Rec);
		return hrRet;
	}

//	m_wAreaObj-Fläche mit Objektnummer m_lONr teilen
WEnumLONG wEnum;	// Objektnummern der Teilflächen

    ((WExtendObjOper)wObjOper)->SectionLineObj_Geom (m_wSectLine, m_lONr, wEnum.ppi());

int iAnzTFl = 0;	// Anzahl der erzeugten Teilflächen

    if (wEnum.IsValid())
    	iAnzTFl = (int) wEnum->Count();	// Anzahl der erzeugten Teilflächen
    else
    {
    ResString resText (ResID (IDS_OBJOPERERR, pRF), 250);
    ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    	
    	MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
    	return E_FAIL;	// keine Teilflächen gebildet
    }

    if (iAnzTFl > 0)	// Flächenteilung war erfolgreich
    {
    // Objektnummern der Teilflächen aus wEnum auslesen
    long* plNeuONr = new long [iAnzTFl];

    	if (! plNeuONr)
    	{
    		DEX_Error (RC_AreaPartition, EC_NOMEMORY);
    		return E_OUTOFMEMORY;
    	}
    	
    	wEnum->Reset();
    	hrRet = wEnum->Next (iAnzTFl, plNeuONr, NULL);

    	_ASSERTE (hrRet == S_OK);

    	if (S_OK != hrRet)
    	{
			DELETE_VEC (plNeuONr);
    		return hrRet;
    	}

    POINT PT;	 	// linker unterer Eckpunkt des Recherchefensters

    	PT.x = PT.y = 5;
    	RechWindowForNewObjects (ResString (ResID(IDS_PARTIALAREAS,pRF),70), PT, plNeuONr,
								 iAnzTFl);	// Recherchefenster
	 	DELETE_VEC (plNeuONr);
    }
    else						// Flächenteilung ist nicht gelungen
    {
    ResString resText (ResID (IDS_NOTEILUNG, pRF), 150);
    ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    		
    	MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);

    Rectangle Rec;	// rechteckiger Bereich, der gezeichnet werden soll

    	m_wSectLine->RectangleToDraw ((RECT*)&Rec);	// Schnittlinie auf Bildschirm löschen
    	DEX_RePaintRectWait (Rec);
    	hrRet = E_FAIL;
    }

    return hrRet;

} // AreaSplitting
