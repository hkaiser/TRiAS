// Definitionen: Design-Funktionen
// File: Designing.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "DesignDlg.h"			// CDesignDlg
#include "SingleDesignDlg.h"	// CSingleDesignDlg
#include "FixPointsDlg.h"		// CFixPointsDlg

#include "Designing.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor / Destruktor
CDesigning::CDesigning (void)
{
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    
    m_pCT = new CoordTransX();	// KoordinatenTransformation

    if (! m_pCT)
    {
    	DEX_Error (RC_Designing, EC_NOMEMORY);
    	return;
    }

	m_NewCP = CURSPOS_UNKNOWN;
    m_OldCP = CURSPOS_UNKNOWN;
    m_RightButtonSem = false;	// rechte Maustaste noch nicht gedrückt
    m_lParamOld = 0;			// letzte Mausposition
    m_bIsPaint = false;			// Hintergrund wird augenblicklich nicht gezeichnet
	m_ResType = RESTRTYPE_STRECKE;
	m_bRightAngle = true;
	m_dRelAngle = 0.0;
	m_dLength = 10.0;
}


// --------------------------------------------------------------------------------------------
CDesigning::~CDesigning (void)
{
	DELETE_OBJ (m_pCT);
    m_wRestrLine.Assign (NULL);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur GeoEdit-Erweiterung über deren Interface IEditExtensionSite herstellen
STDMETHODIMP CDesigning::SetEditExtensionSite (IEditExtensionSite* pIEdExSite)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    	WUnknown wISite;

    		// Verbindung zu TRiAS über Interface ITriasExtension herstellen
    		THROW_FAILED_HRESULT (pIEdExSite->GetXtensionSite (wISite.ppi()));

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

    		THROW_FAILED_HRESULT (m_wEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));
    		m_wTopObjs->SetMarkVis (true);	// Stützpunkte der ausgewählten Objekte sollen
    										// (bald - hier noch nicht) markiert werden
    		THROW_FAILED_HRESULT (m_wEdExSite->GetRestrictLine (m_wRestrLine.ppi()));
    	}
    	else
    	{
    		// Stützpunktmarkierungen der ausgewählten Objekte werden gelöscht
    		m_wTopObjs->SetMarkVis (false);

    		if (m_dwCookieN != 0L || m_dwCookieSN != 0L)	// abmelden
    			THROW_FAILED_HRESULT (DisconnectFromServer());	// gibt uns u.u. frei

    		m_wTopObjs.Assign (NULL);	// freigeben
    		m_wEdExSite.Assign (NULL);	// freigeben
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
HRESULT CDesigning::DisconnectFromServer (void)
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
STDMETHODIMP CDesigning::InformRestrictLinesState (IRestrictLine*, IRestrictLine*)
{
    ATLTRACENOTIMPL("CDesigning::InformRestrictLinesState");
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::DeleteRestrictedCursor (void)
{
    ATLTRACENOTIMPL("CDesigning::DeleteRestrictedCursor");
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CDesigning::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CDesigning::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CDesigning::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
STDMETHODIMP CDesigning::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    switch (ve)
    {
    	case GEOVIEWEVT_PaintingView:	// kommt vor dem Zeichnen des Hintergrundes
    									// (entspr. DEX_ERASEBKGND)
    		m_bIsPaint = true;			// Hintergrund wird gezeichnet
    		break;

    	case GEOVIEWEVT_ViewPainted:	// kommt nach dem Zeichnen des Hintergrundes
    									// (entspr. DEX_PAINTTOPLAYER)
			RepaintTemporaryObjects();	// temporäre Objekte erneut zeichnen
    		m_bIsPaint = false;			// Hintergrund wurde gezeichnet
    		break;

		case GEOVIEWEVT_ScrollingHorz:
    		break;

		case GEOVIEWEVT_ScrollingVert:
			break;
    }

    return S_OK;	// immer weiterleiten

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CDesigning::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    ATLTRACE("CDesigning::GeoObjectEvent not implemented");
    return S_OK;	// immer weiterleiten

}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CDesigning::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CDesigning::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CDesigning::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CDesigning::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CDesigning::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
    switch (uiMsg)
    {
    	case WM_MOUSEMOVE:
    		MouseMove (lParam);
    		break;

    	case WM_RBUTTONDOWN:
    		RightMouseDown (lParam);
    		break;

    	case WM_RBUTTONUP:
    		RightMouseUp();
    		break;
    }

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// Maus wurde bewegt
HRESULT CDesigning::MouseMove (LPARAM lParam)
{
	if (NULL == g_pTE->MVWind())	// Projekt wird geschlossen oder kein Projekt geöffnet
    	return S_FALSE;				// NICHT "if (NULL == m_pVWnd)" !!!!

    if (lParam == m_lParamOld)	// keine neue Mausposition
    	return S_OK;

    m_lParamOld = lParam;

    // wenn rechte Maustaste gedrückt bzw. augenblicklich Hintergrund gezeichnet wird, dann
	// keine weitere Bearbeitung
    if (m_RightButtonSem || m_bIsPaint)
    	return S_FALSE;

	return RefreshCursorForm();	// aktuelle CursorPosition ermitteln

} // MouseMove


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde gedrückt
void CDesigning::RightMouseDown (LPARAM lParam)
{
    m_RightButtonSem = true;		// rechte Maustaste wurde gedrückt
	m_ptRM = BSPoint (lParam);		// BS-Punkt, bei dem rechte Maustaste gedrückt wurde

} // RightMouseDown


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde losgelassen
HRESULT CDesigning::RightMouseUp (void)
{
    if (!m_RightButtonSem)	// rechte Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_RightButtonSem = false;		// rechte Maustaste nicht mehr gedrückt

	return DesignRestrictLine();

} // RightMouseUp


// --------------------------------------------------------------------------------------------
// Dialog anzeigen und Konstruktionshilfslinie bilden
HRESULT CDesigning::DesignRestrictLine (void)
{
	if (CURSPOS_VERTEX != m_NewCP && CURSPOS_LINE != m_NewCP)
    	return S_FALSE;		// Cursor nicht in einer Stützpunktmarkierung und nicht
							// "in der Nähe" einer Strecke

ulong ulBelowCnt;	// Anzahl der Objekte, die unter der Mausspitze lagen

	m_wBelowObjs->GetCount(&ulBelowCnt);

	if (ulBelowCnt > 1)
	{
	ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

		MessageBox (__hWndM, "Unter der Mausspitze darf beim Klick nur EIN Objekt liegen.", resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
    	return S_FALSE;
	}

WObjektGeometrie wObj;	// ObjektGeometrie des lRegONr-Bezugsobjektes

    try
    {
	WUnknown Unk;

   		m_wBelowObjs->Reset();

	HRESULT hr = m_wBelowObjs->Next (1, Unk.ppi(), NULL);

    	if (S_OK == hr) wObj = Unk;
//		else return hr;
		else _com_issue_error (hr);
    }
    catch (_com_error& e)
    {
		return _COM_ERROR (e);
    }


long lCnt;			// Stützpunktanzahl des lRegONr-Bezugsobjektes
long lPInd = -1;	// Index des lRegONr-Stützpunktes, dem FixPkt am nächsten liegt
long lSInd = -1;	// Index der lRegONr-Strecke, dem FixPkt am nächsten liegt

	wObj->GetCnt (&lCnt);

EPunkt APkt = DBKoordinaten (m_ptRM);

	m_FixPkt = NearestPointToObject (APkt, wObj, 0, lCnt-1, false, &lPInd, &lSInd);

KoOrd x0, y0, x1, y1;		// Koordinaten der pIOG-Strecke, bez. der die Hilfslinie errichtet
							// werden soll
bool bWithAngle = false;	// Winkel in der 1. Page deaktivieren
short iOT;					// Objekttyp des Bezugsobjektes

	wObj->GetObjTyp (&iOT);

// die letzte Innenkontur hat bisher nur einen Punkt und dieser wurde als Bezugspunkt für die
// Hilfslinie ausgewählt (true)
bool bOPI = OnePointInline (wObj, iOT, lCnt, lPInd);

	if (OT_PUNKT != iOT &&	// Bezugsobjekt ist kein Punktobjekt und
		lCnt >= 2 &&		// mindestes 2 Stützpunkte wurden schon editiert
		!bOPI)				// keine Ein-Punkt-Innenkontur
	{
		// Hilfslinie durch einen Stützpunkt, der nicht der erste und auch nicht der letzte
		// eines offenen Linienobjektes ist
		if (IsRestrictLineAtVertex (wObj, iOT, lCnt, lPInd))
			return S_FALSE;

		if (!RegardingCoordinates (wObj, lCnt, lPInd, lSInd, x0, y0, x1, y1))
			return S_FALSE;
		bWithAngle = true;
	}
	else
	{
		x0 = m_FixPkt.X();
		y0 = m_FixPkt.Y();
		x1 = m_FixPkt.X();
		y1 = m_FixPkt.Y();
	}


// Hilfslinien-Dialog anzeigen
CDesignDlg shDesignDlg (m_ptRM);
CSingleDesignDlg pgSingleDlg (m_ResType, m_bRightAngle, m_dRelAngle, m_dLength, bWithAngle);
CFixPointsDlg pgFixDlg (m_FixPkt.X(), m_FixPkt.Y(), x0, y0, x1, y1);

	shDesignDlg.AddPage (&pgSingleDlg);		// 1. Page einfügen
	if (OT_PUNKT != iOT && lCnt >= 2 && !bOPI)
		shDesignDlg.AddPage (&pgFixDlg);	// 2. Page einfügen
    shDesignDlg.Show();

    // Hintergrund nach Zerlegen des Hilfslinien-Dialogs sofort zeichnen, weil sonst ZUERST die
    // Hilfslinie gezeichnet wird, die dann durch das spätere Hintergrundzeichnen gelöscht wird
	m_pVWnd->Update();

	if (IDCANCEL == shDesignDlg.Result())	// CancelButton
	{
		// über eine PostMessage wird CGeoEdit mitgeteilt, daß das CDesigning-Objekt wieder
		// zerlegt werden kann
		PostMessage (__hWndM, WM_WM_DESIGNBUILDEND, 0, 0);
		return S_FALSE;
	}

	// !!!!!!!!!!!  Das Retten der aktuellen Einstellung bringt an dieser Stelle noch nichts da die
	// CDesigning-Klasse vor der Bildung einer neuen Hilfslinie zerlegt wird. Deshalb müßten die Member in
	// GeoEdit.h zwischengespeichert und von dort wieder geholt werden.   !!!!!!!!!!!!!!!!!!!!!!
	m_ResType = pgSingleDlg.GetRestrTyp();
	m_bRightAngle = pgSingleDlg.GetAngleTyp();
	m_dRelAngle = pgSingleDlg.GetRelAngle();
	m_dLength = pgSingleDlg.GetLength();
	m_FixPkt = pgFixDlg.GetFixPoint();


double dAngle = 0.;	// der an BuildRestrictLine() übergebene Winkel

	if (OT_PUNKT != iOT && lCnt >= 2 && !bOPI)
	{
		m_dpUF = UmrechnungsFaktor (x0, y0, x1, y1, m_pCT);

		// bei den nachfolgenden Hilfslinienformen ist eine Winkel vorgegeben
		if (RESTRTYPE_STRECKE == m_ResType || RESTRTYPE_GERADE == m_ResType)
			dAngle = GradientAngle (x0, y0, x1, y1);
	}
	else					// Bezugsobjekt ist eine Punktobjekt
	{
	KoOrd* plXK; KoOrd* plYK;

		wObj->GetX ((void**)&plXK);
		wObj->GetY ((void**)&plYK);

		m_dpUF = UmrechnungsFaktor (plXK[0], plYK[0], plXK[0], plYK[0], m_pCT);
	}


HRESULT hrRet = S_OK;

    try
    {
    // Verbindung zum CRestrictLine-Objekt über dessen Interface IRestrictLine herstellen
	WRestrictLine wRestrLine (CLSID_RestrictLine);	// throws_com_error

    	m_wRestrLine.Assign (NULL);
    	m_wRestrLine = wRestrLine;
    	m_wRestrLine->BuildRestrictLine (m_FixPkt.X(), m_FixPkt.Y(), m_ResType, dAngle,
										 m_dLength, m_dpUF.X(), m_dpUF.Y());

    // Objektnummer des Bezugsobjektes und dazugehörige Konstruktionshilfslinie an GeoEdit
	// übergeben
	long lRegONr;

		wObj->GetONr (&lRegONr);
    	m_wEdExSite->SetRestrictLine (lRegONr, m_wRestrLine);

		// über eine PostMessage wird CGeoEdit mitgeteilt, daß ein WRestrictLine-Objekt
		// erzeugt wurde und damit das CDesigning-Objekt zerlegt werden kann (Bedeutung des 3.
		// und 4. Parameter ist mir unbekannt !!!!)
		PostMessage (__hWndM, WM_WM_DESIGNBUILDEND, 0, 0);
    }
    catch (_com_error& e)
    {
		hrRet = _COM_ERROR (e);
    }

	return hrRet;

} // DesignRestrictLine


// --------------------------------------------------------------------------------------------
// Hilfsroutine für DesignRestrictLine();
// es wird getestet, ob die Hilfslinie in dem ersten und bis jetzt einzigen Stützpunkt einer
// Innenkontur erreichtet werden soll; wenn ja Rückgabe von "true"
bool CDesigning::OnePointInline (IObjektGeometrie* pIOG, int iOT, long lCnt, long lPInd)
{
	if (lPInd < 0)
		return false;			// Hilfslinie nicht in einem Stützpunkt

	if (OT_FLAECHE != iOT)
		return false;			// überhaupt keine Fläche

short iKCnt;

	pIOG->GetKCnt (&iKCnt);
	if (iKCnt <= 1)
		return false;			// keine Innenkonturen

long* plCnt;

	pIOG->GetLPCnt (&plCnt);
	if (1 == plCnt[iKCnt-1] &&	// die letzte Innenkontur hat bisher nur einen Punkt und
		lPInd == lCnt - 1)		// dieser wurde als Bezugspunkt für die Hilfslinie ausgewählt
		return true;

	return false;				// sonst

} // OnePointInline


// --------------------------------------------------------------------------------------------
// die CursorForm aktualisieren
HRESULT CDesigning::RefreshCursorForm (void)
{
	if (FAILED (m_wTopObjs->CursorAtTopicalObjects (&m_NewCP, NULL, NULL, NULL,
													m_wBelowObjs.ppi())))
	    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

    if (m_NewCP == m_OldCP)
	{
		if (CURSPOS_UNKNOWN == m_NewCP)
		    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
		return S_OK;
	}

    m_OldCP = m_NewCP;	// bisherige CursorPosition retten

    if (CURSPOS_VERTEX == m_NewCP ||	// Cursor im Marker eines Stützpunktes bzw.
		CURSPOS_LINE == m_NewCP)		// Cursor "in der Nähe" einer Strecke
    	return m_wEdExSite->SetCursor (CURSFORM_TRENNER, TRUE);
    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

} // RefreshCursorForm


// --------------------------------------------------------------------------------------------
// Testen, ob die Konstruktionshilfslinie EXAKT in einem Stützpunkt einer Flächenkontur bzw.
// eines geschlossenen Linienobjektes errichtet werden soll; dann return-Wert "true" sonst
// "false"
bool CDesigning::IsRestrictLineAtVertex (IObjektGeometrie* pIOG, int iOT, long lCnt,
										 long lPInd)
{
	if (OT_KANTE != iOT && OT_FLAECHE != iOT)
		return false;

	if (-1 == lPInd)
		return false;	// Konstruktionshilfslinie nicht in einem Stützpunkt

bool bRet = false;

	if (OT_KANTE == iOT)
	{
		_ASSERTE (lCnt > 0);

		if (1 == lCnt)
			return false;

		if (lPInd > 0 && lPInd < lCnt - 1)
			bRet = true;		// kein Randstützpunkt
		else
		{
		KoOrd* plXK; KoOrd* plYK;

			pIOG->GetX ((void**)&plXK);
			pIOG->GetY ((void**)&plYK);

			if (plXK[0] == plXK[lCnt-1] && plYK[0] == plYK[lCnt-1])
				bRet = true;	// Randstützpunkt, aber geschlossene Linie
		}
	}
	else	// OT_FLAECHE == iOT
		bRet = true;		// Flächenkontur

	if (bRet)
	{
	ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
	ResString resText (ResID (IDS_LINEATVERTEX, pRF), 200);

		MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
	}

	return bRet;

} // IsRestrictLineAtVertex


// --------------------------------------------------------------------------------------------
// Koordinaten der Bezugsstrecke ermitteln
bool CDesigning::RegardingCoordinates (IObjektGeometrie* pIOG, long lCnt, long lPInd,
									   long lSInd, KoOrd& x0, KoOrd& y0, KoOrd& x1, KoOrd& y1)
{
	if (lCnt < 2)
		return false;

KoOrd* plXK; KoOrd* plYK;

    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);

	if (0 == lPInd)			// Hilfslinie durch einen Randstützpunkt
	{
		x0 = plXK[0];
		y0 = plYK[0];
		x1 = plXK[1];
		y1 = plYK[1];
	}
	else if (lPInd == lCnt - 1)
	{
		x0 = plXK[lCnt-1];
		y0 = plYK[lCnt-1];
		x1 = plXK[lCnt-2];
		y1 = plYK[lCnt-2];
	}
	else if (-1 != lSInd)	// Hilfslinie durch eine Strecke
	{
		x0 = plXK[lSInd];
		y0 = plYK[lSInd];
		x1 = plXK[lSInd+1];
		y1 = plYK[lSInd+1];
	}
	else
	{
		_ASSERTE (lPInd != -1 || lSInd != -1);

		return false;
 	}

	return true;

} // RegardingCoordinates


// --------------------------------------------------------------------------------------------
// Anstiegswinkel der Hilfslinie im Bogenmaß (bezogen auf die Horizontale);
// Koordinaten als "double", weil atan() ein double-Argument verlangt
double CDesigning::GradientAngle (double x0, double y0, double x1, double y1)
{
double dAngle = 0.;	// Anstiegswinkel zuerst der Strecke (x0,y0)-(x1,y1), danach der Hilfslinie
					// (im Bogenmaß)
	if (x0 != x1)
		// Winkel liegt im Bereich von -Pi/2 bis Pi/2
		dAngle = atan ((y1 - y0) / (x1 - x0) * m_dpUF.X()/m_dpUF.Y());
	else
		dAngle = Pi/2.;

	// jetzt wird dAngle zum Anstiegswinkel der Hilfslinie (bezogen auf die Horizontale)
	if (m_bRightAngle)
		dAngle += Pi/2;
	else
		dAngle += m_dRelAngle*Pi/180.;

	return dAngle;

} // GradientAngle


// --------------------------------------------------------------------------------------------
// temporäre Objekte erneut zeichen
HRESULT CDesigning::RepaintTemporaryObjects (void)
{
WEnumObjektGeometrie wTempObjs;	// die ausgewählten temporären Objekte

	try
	{
    	THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (FALSE,
																		 wTempObjs.ppi()));
	WUnknown Unk;

    	for (wTempObjs->Reset(); S_OK == wTempObjs->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

			DrawTemporaryObject (wObj, m_pVWnd);
    	}
	}
	catch (_com_error& e)
	{
    	return _COM_ERROR (e);
	}

	return S_OK;

} // RepaintTemporaryObjects
