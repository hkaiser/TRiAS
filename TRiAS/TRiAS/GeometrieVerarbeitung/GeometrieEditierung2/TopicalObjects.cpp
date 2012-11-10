// Definitionen: Implementation of CTopicalObjects
// File: TopicalObjects.cpp
// H. Kaiser, W. Mörtl


#include "GeoEditP.h"

#include <registrx.hxx>		// CCurrentUser

#include "TopicalObjects.h"
#include "Strecke.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG


#if _MSC_VER >= 1100
#include <new>
using std::bad_alloc;
#endif // _MSC_VER >= 1100


///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// die schon selektierten Objekte einsammeln und in m_TopObjs eintragen
BOOL _GEOEDIT_EXPORT FAR PASCAL SelectedObjects (long lONr, BOOL, void* pvSelObjs)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

    if (0 != lONr && -1 != lONr)
    {
    	((CGeoObjs*)pvSelObjs)->AddObject (lONr);
    	return true;
    }
    return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// CTopicalObjects

// Konstruktor
CTopicalObjects::CTopicalObjects (void) : m_TopObjs(reinterpret_cast<ITopicalObjects *>(this))
{
    m_dwCookie = 0L;

    m_bMarkVis = false;			// Stützpunktmarkierungen (noch) nicht sichtbar machen
    m_bIsPaint = false;			// Hintergrund (durch GEOVIEWEVT_PaintingView ausgelöst) wird
    							//  augenblicklich nicht gezeichnet

Window Wnd(__hWndM);				// TRiAS-Hauptfenster
Dimension MWDim = Wnd.GetSize();	// Größe (im Point-Format) des Hauptfensters (eigentlich
    								// würde TRiAS-ViewFenster ausreichen)
	m_rcHintergrund.left = 0;
	m_rcHintergrund.right = MWDim.Width();
	m_rcHintergrund.bottom = 0;
	m_rcHintergrund.top = MWDim.Height();

CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathEdit);

// Pixelanzahl für Markierungsquadrat aus der RegDB entnehmen
ResString UMarkGroesse (ResID (IDS_UMARKGROESSE, pRF), 30);	
ResString OMarkGroesse (ResID (IDS_OMARKGROESSE, pRF), 30);	
DWORD dwUWert, dwOWert;

    if (cuExtConfig.GetDWORD (UMarkGroesse.Addr(), dwUWert))
    	m_iUMarkGr = (int)dwUWert;
    else
    	m_iUMarkGr = iUGr;

    if (cuExtConfig.GetDWORD (OMarkGroesse.Addr(), dwOWert))
    	m_iOMarkGr = (int)dwOWert;
    else
    	m_iOMarkGr = iOGr;

// Vorgabe in der Registry vorerst doch in Pixel (NICHT in Millimeter), da bei den Anwendern
// die Registry-Einträge schon auf Pixel ausgerichtet sind; dessen ungeachtet wären Millimeter
// wegen der verschiedenen Bildschirmauflösungen sinnvoller; vielleicht gehe ich dann doch noch
// auf Millimeter, wenn ich den schon lange gewünschten Dialog anbiete (10.06.98)
//Dimension dimDots = GetDotsPerMM (NULL); // Pixel pro Millimeter für den Bildschirm

//	m_iUMarkGr *= dimDots.Width();
//	m_iOMarkGr *= dimDots.Width();


// Farbe für Markierungsquadrat aus der RegDB entnehmen
ResString resMarkColor (ResID (IDS_MARKCOLOR, pRF), 30);
ResString resMarkColorBegin (ResID (IDS_MARKCOLORBEGIN, pRF), 30);
ResString resMarkColorEnd (ResID (IDS_MARKCOLOREND, pRF), 30);
ResString resMarkBoundThick (ResID (IDS_MARKBOUNDTHICK, pRF), 30);
DWORD dwColor0, dwColor1, dwColor2, dwThickness;

    if (cuExtConfig.GetDWORD (resMarkColor.Addr(), dwColor0))
    	m_FillMC = Color (GetRValue(dwColor0), GetGValue(dwColor0), GetBValue(dwColor0));
    else
    	m_FillMC = Color (GetRValue(ulGW0), GetGValue(ulGW0), GetBValue(ulGW0));

    if (cuExtConfig.GetDWORD (resMarkColorBegin.Addr(), dwColor1))
    	m_FirstMC = Color (GetRValue(dwColor1), GetGValue(dwColor1), GetBValue(dwColor1));
    else
    	m_FirstMC = Color (GetRValue(ulGW1), GetGValue(ulGW1), GetBValue(ulGW1));

    if (cuExtConfig.GetDWORD (resMarkColorEnd.Addr(), dwColor2))
    	m_LastMC = Color (GetRValue(dwColor2), GetGValue(dwColor2), GetBValue(dwColor2));
    else
    	m_LastMC = Color (GetRValue(ulGW2), GetGValue(ulGW2), GetBValue(ulGW2));

    if (cuExtConfig.GetDWORD (resMarkBoundThick.Addr(), dwThickness))
    	m_iThick = (int)dwThickness;
    else
    	m_iThick = iThick;
}


// --------------------------------------------------------------------------------------------
// Stützpunkte des pIOG-Objektes durch Markierungen optisch sichtbar machen (bVisible == true)
// bzw. diese Markierungen löschen
HRESULT CTopicalObjects::MarkerVisibility (IObjektGeometrie* pIOG, bool bVisible)
{
    _ASSERTE (pIOG != NULL);

Window Wnd(__hWndM);	// TRiAS-Hauptfenster
CEierUhr Wait (&Wnd);
HRESULT hrRet = S_OK;	// return-Wert dieser Routine
int iMarkGr;
Marker* pMk = NULL;
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    GetMarkerSizeBS (&iMarkGr);
    pIOG->GetCnt (&lCnt);
    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);

short iKontNr;	// für Routine IndexTest(); werden
long lInd;		//  hier nicht ausgewertet
IndPos IP = NICHTS;
short iOT;

	pIOG->GetObjTyp (&iOT);

	for (long i = lCnt - 1; i >= 0; i--)
	{
    Point BSPt = BSKoordinaten (plXK[i], plYK[i]);
    			
    	if (bVisible) {			// Markierung setzen

    		if (m_bIsPaint &&	// Nachzeichnen des Hintergrundes
    			(BSPt.X() < m_rcHintergrund.left || m_rcHintergrund.right < BSPt.X() ||
    			 BSPt.Y() < m_rcHintergrund.bottom || m_rcHintergrund.top < BSPt.Y()))
    			continue;	// Markierung nicht im Hintergrundsbereich

    		if (OT_FLAECHE == iOT)
    			pIOG->IndexTest (i, &iKontNr, &lInd, &IP);

    		// Markierungsquadrates des 1. und bei Kanten auch des letzten Stützpunktes
			// hervorheben (ulGW0, ulGW1 bzw. ulGW2 sind in EditKonst.h definiert)
    		if (OT_KANTE == iOT && i == lCnt-1)
    			pMk = new Marker (m_FillMC, m_LastMC, m_iThick, BSPt, iMarkGr);
    		else if (0 == i || ERSTER == IP)
    			pMk = new Marker (m_FillMC, m_FirstMC, m_iThick, BSPt, iMarkGr);
    		else 
    			pMk = new Marker (m_FillMC, m_FillMC, m_iThick, BSPt, iMarkGr);

    		if (! pMk)
    		{
    			DEX_Error (RC_SelObjects, EC_NOMEMORY);
    			hrRet = E_OUTOFMEMORY;
    			break;
    		}
    		g_pTE->MVWind()->Draw (pMk);
			DELETE_OBJ (pMk);
    	}

    	else	// Markierung löschen
		{
    	CoOrd hmg = iMarkGr/2 + 1;	// halbe Markergröße; "+ 1" ist eine Sicherheitszugabe für
    								//  das Zeichnen
    	// Markierungsquadrat mit Sicherheitszugabe
    	Rectangle Rec (BSPt.Y()+hmg, BSPt.X()-hmg, BSPt.Y()-hmg, BSPt.X()+hmg);

    		DEX_RePaintRectWait (Rec);
    	}
    }
    return hrRet;

} // MarkerVisibility


// --------------------------------------------------------------------------------------------
// TRiASNotificationSink bei TRiAS wieder abmelden
HRESULT CTopicalObjects::DisconnectFromServer (void)
{
// künstliches AddRef, da uns nachfolgendes AtlUnadvise freigeben kann
WUnknown Unk ((ITopicalObjects *)this);

    AtlUnadvise (m_Site, IID_ITRiASNotificationSink, m_dwCookie); 
    
    m_Site.Assign (NULL);		// freigeben von TRiAS
    m_dwCookie = 0L;
    return S_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// *** interface ITopicalObjects 

// Speichern des TRiAS-Kontextes und registrieren beim ConnectionPoint
STDMETHODIMP CTopicalObjects::SetXtensionSite (IUnknown *pISite)
{
    try
    {
    	if (pISite != NULL)
    	{
    		if (0L != m_dwCookie)	// Anmelden
    			_com_issue_error (E_UNEXPECTED);	// darf noch nicht angemeldet sein
    		m_Site = pISite;		// throws_com_error
    		THROW_FAILED_HRESULT(AtlAdvise (m_Site, (ITRiASNotificationSink *)this,
    										IID_ITRiASNotificationSink, &m_dwCookie));
    		THROW_FAILED_HRESULT(InitWithSelectedObjects());
    	}
    	else if (0 != m_dwCookie)	// Abmelden
    		THROW_FAILED_HRESULT(DisconnectFromServer());	// gibt uns u.u. frei

    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }
    return S_OK;

} // SetXtensionSite


// --------------------------------------------------------------------------------------------
// die schon (in allen Recherchefenstern) selektierten Objekte einsammeln und in m_TopObjs
// eintragen
STDMETHODIMP CTopicalObjects::InitWithSelectedObjects (void)
{
	m_TopObjs.DeleteObjects();

ENUMLONGKEY ELK;

    ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
    ELK.eFcn = (ENUMLONGKEYPROC) SelectedObjects;
    ELK.ePtr = (void*)&m_TopObjs;
    DEX_EnumSelectedObjects (ELK);

    return S_OK;

} // InitWithSelectedObjects


// --------------------------------------------------------------------------------------------
// die "von außen" vorgebbaren pIEnum-Objekte in m_TopObjs eintragen
STDMETHODIMP CTopicalObjects::InitWithExternalObjects (IEnumObjectsByNumber* pIEnum)
{
    _ASSERTE (pIEnum != NULL);

long lONr = 0;

    for (pIEnum->Reset(); S_OK == pIEnum->Next (1, &lONr, NULL); )
    {
		_ASSERTE (lONr != 0);
		_ASSERTE (lONr != -1);

		RETURN_FAILED_HRESULT (m_TopObjs.AddObject (lONr));
    }

    return S_OK;

} // InitWithExternalObjects


// --------------------------------------------------------------------------------------------
// pIOG-Objekte in m_TopObjs eintragen
STDMETHODIMP CTopicalObjects::AddTopicalObjectGeometry (IUnknown* pIOG)
{
    return m_TopObjs.AddObject ((IObjektGeometrie*)pIOG);
}


// --------------------------------------------------------------------------------------------
// Rückgabe der ausgewählten Objekte
STDMETHODIMP CTopicalObjects::GetEnumTopicalObjects (IEnumObjectsByNumber** ppIEnum)
{
    return m_TopObjs.GetEnumObjectsByNumber (ppIEnum);
}


// --------------------------------------------------------------------------------------------
// Rückgabe der ausgewählten Objekte
// bAll == TRUE:  alle Objekte
// bAll == FALSE: nur die temporären Objekte
STDMETHODIMP CTopicalObjects::GetEnumTopicalObjectsGeometry (BOOL bAll,
															 IEnumObjektGeometrie** ppIEnum)
{
    return m_TopObjs.GetEnumObjektGeometrie (ppIEnum, bAll);
}


// --------------------------------------------------------------------------------------------
// Test, ob sich lONr-Objekt in der m_TopObjs-Liste befindet, dann *pbContain == true
STDMETHODIMP CTopicalObjects::IsTopicalObject (long lONr, BOOL* pbContain)
{
    return m_TopObjs.IsObject (lONr, pbContain);
}


// --------------------------------------------------------------------------------------------
// Test, ob sich pIOG-Objekt in der m_TopObjs-Liste befindet, dann *pbContain == true
STDMETHODIMP CTopicalObjects::IsTopicalObjectGeometry (IUnknown* pIOG, BOOL* pbContain)
{
    return m_TopObjs.IsObject ((IObjektGeometrie*)pIOG, pbContain);
}


// --------------------------------------------------------------------------------------------
// entfernt das lONr-Objekt aus der m_TopObjs-Liste
STDMETHODIMP CTopicalObjects::DeleteTopicalObject (long lONr)
{
    return m_TopObjs.DeleteObject (lONr);
}


// --------------------------------------------------------------------------------------------
// entfernt das pIOG-Objekt aus der m_TopObjs-Liste
STDMETHODIMP CTopicalObjects::DeleteTopicalObjectGeometry (IUnknown* pIOG)
{
    return m_TopObjs.DeleteObject ((IObjektGeometrie*)pIOG);
}


// --------------------------------------------------------------------------------------------
// entfernt Objekte aus der m_TopObjs-Liste
// bAll == TRUE:  alle Objekte
// bAll == FALSE: nur die temporären Objekte
STDMETHODIMP CTopicalObjects::DeleteTopicalObjects (BOOL bAll)
{
    return m_TopObjs.DeleteObjects (bAll);
}


// --------------------------------------------------------------------------------------------
// liefert das kleinste umschreibende Rechteck von Objekten aus der Liste;
// bAll == TRUE:  alle Objekte
// bAll == FALSE: nur die temporären Objekte
STDMETHODIMP CTopicalObjects::GetTopicalObjectsRectangle (BOOL bAll, LONG* plXmin,
													  LONG* plXmax, LONG* plYmin, LONG* plYmax)
{
    return m_TopObjs.GetObjectsRectangle (plXmin, plXmax, plYmin, plYmax, bAll);
}


// --------------------------------------------------------------------------------------------
// Anzahl der ausgewählten Objekte zurückgeben
STDMETHODIMP CTopicalObjects::GetCount (long* plCnt)
{
    *plCnt = m_TopObjs.Count();
    return S_OK;

} // GetCount


// --------------------------------------------------------------------------------------------
// liefert Type(en) der ausgewählten Objekte;
// unter den ausgewählten Objekten befindet sich mindestens ein
//   Punktobjekt (Bit 0 gesetzt)
//   Linienobjekt (Bit 1 gesetzt)
//   Flächenobjekt (Bit 2 gesetzt)
STDMETHODIMP CTopicalObjects::GetObjTypes (int* piAllOT)
{
    _ASSERTE (piAllOT != NULL);

    *piAllOT = 0;	// Rückgabewert

WEnumUnknown wEnum;

	RETURN_FAILED_HRESULT (m_TopObjs.GetEnumObjects (wEnum.ppi()));

HRESULT hrRet = S_OK;
short iOT;

    try
    {
	WUnknown Unk;

    	for (wEnum->Reset(); S_OK == wEnum->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		wObj->GetObjTyp (&iOT);
    		if (OT_PUNKT == iOT)
    			*piAllOT |= OTPunkt;
    		else if (OT_KANTE == iOT)
    			*piAllOT |= OTLinie;
    		else if (OT_FLAECHE == iOT)
    			*piAllOT |= OTFlaeche;
    		else 
    		{
    			_ASSERTE (iOT == OT_PUNKT || iOT == OT_KANTE || iOT == OT_FLAECHE);
    			hrRet = E_UNEXPECTED;	// sonst nur weitermachen
    		}
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }	

    return hrRet;

} // GetObjTypes


// --------------------------------------------------------------------------------------------
// Größe eines Markers in BS-Koordinaten bestimmen
STDMETHODIMP CTopicalObjects::GetMarkerSizeBS (int* piMS)
{
double dQuot = 1.;	// Quotient von Bezugsmaßstab und Darstellungsmaßstab
    				// (hängt vom Zoom-Zustand ab)

    if (!DEX_GetActiveScaling (dQuot))
		dQuot = 1.;

    if (dQuot <= 0.)
    {
    	_ASSERTE (dQuot > 0.);
    	*piMS = m_iUMarkGr;   // um Division durch Null vorzubeugen
    	return S_FALSE;
    }

int iMG = (int) (m_iUMarkGr / dQuot / 2. + 0.5);	// "2" ist ein heuristischer Wert

    if (iMG < m_iUMarkGr) iMG = m_iUMarkGr;	// untere Grenze
    if (iMG > m_iOMarkGr) iMG = m_iOMarkGr;	// obere Grenze

    *piMS = iMG;
    return S_OK;

} // GetMarkerSizeBS


// --------------------------------------------------------------------------------------------
// Stützpunkte aller ausgewählten, d. h. aller in m_TopObjs befindlichen Objekte markieren
STDMETHODIMP CTopicalObjects::VerticesIndicate (void)
{
KoOrd lXmin, lXmax, lYmin, lYmax;	// Koordinaten des wObjGeom-Containers
WEnumUnknown wEnum;

	RETURN_FAILED_HRESULT (m_TopObjs.GetEnumObjects (wEnum.ppi()));

    try
    {
	WUnknown Unk;

    	for (wEnum->Reset(); S_OK == wEnum->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		wObj->GetCont (&lXmin, &lXmax, &lYmin, &lYmax);

    	Point PLU = BSKoordinaten (lXmin, lYmin);
    	Point PRO = BSKoordinaten (lXmax, lYmax);

	 		// Objektcontainer hat mindestens einen Punkt mit dem Hintergrundsbereich gemeinsam
    		if (!m_bIsPaint ||	// Markierungen erstmalig zeichnen
    			//  bzw. Markierungen im Hintergrundsbereich nachzeichnen
    			(PLU.X() <= m_rcHintergrund.right && m_rcHintergrund.left <= PRO.X() &&
    			PLU.Y() <= m_rcHintergrund.top && m_rcHintergrund.bottom <= PRO.Y()))
    			THROW_FAILED_HRESULT (MarkerVisibility (wObj, true));
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // VerticesIndicate


// --------------------------------------------------------------------------------------------
// Stützpunktmarkierungen aller in m_TopObjs befindlichen Objekte löschen
STDMETHODIMP CTopicalObjects::VerticesUnIndicate (void)
{
WEnumUnknown wEnum;

	RETURN_FAILED_HRESULT (m_TopObjs.GetEnumObjects (wEnum.ppi()));

    try
    {
	WUnknown Unk;

    	for (wEnum->Reset(); S_OK == wEnum->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		THROW_FAILED_HRESULT (MarkerVisibility (wObj, false));
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // VerticesUnIndicate


// --------------------------------------------------------------------------------------------
// Funktion ermittelt die CursorPosition pCP bez. aller ausgewählten m_TopObjs-Objekte sowie
// (wenn ppBelowObjs != NULL) die Objekte ppBelowObjs, die unter der Mausspitze liegen;
// außerdem wird in pbSpezCP angezeigt, ob für die CursorPosition einer der Spezialfälle
// CURSPOS_FIRST_VERTEX, CURSPOS_LAST_VERTEX, CURSPOS_INBORDER_VERTEX bzw. CURSPOS_INBORDER
// zutrifft, da diese Information für den Menüaufbau in ObjectModify benötigt wird
// Rückgabewerte der CursorPosition pCP sind: CURSPOS_VERTEX, CURSPOS_LINE und CURSPOS_UNKNOWN
STDMETHODIMP CTopicalObjects::CursorAtTopicalObjects (CursPos* pCP, BOOL* pbSpezCP,
							  long* plGrabX, long* plGrabY, IEnumObjektGeometrie** ppBelowObjs)
{
    m_GrabPkt.X() = 0;					// falls es keinen GrabPunkt gibt
    m_GrabPkt.Y() = 0;
    if (pbSpezCP) *pbSpezCP = false;	// für den Fehlerfall
    *pCP = CURSPOS_UNKNOWN;

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Point Pt;		// Position in BS-Koordinaten und
EPunkt Pkt;		//  in DB-Koordinaten

    if (!GetCursorCoordinates (Pt, Pkt)) return E_FAIL;

    MarkerInDBCoords (Pt);

WEnumUnknown wEnum;

	RETURN_FAILED_HRESULT (m_TopObjs.GetEnumObjects (wEnum.ppi()));

CursPos CP;				// CursorPosition

// nachfolgender Parameter ist für den Fall erforderlich, daß bei mehreren wEnum-Objekten
// manchmal *pbSpezCP = true, aber auch manchmal *pbSpezCP = false werden müßte; in diesem
// Fall wird *pbSpezCP = false gesetzt (03.07.98)
bool bSpezCP = true;

    try
    {
    // Objektgeometrie'n, die evtl. zurückgegeben werden
	WEnumObjektGeometrie wOutObjs (CLSID_EnumObjektGeometrie);
	WUnknown Unk;

    	for (wEnum->Reset(); S_OK == wEnum->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		wObj->CursorPositionAtObject (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2, m_lEpsilon,
    									  true, &CP, &m_GrabPkt.X(), &m_GrabPkt.Y());

    		if (CURSPOS_VERTEX == CP || CURSPOS_FIRST_VERTEX == CP ||
    			CURSPOS_LAST_VERTEX == CP || CURSPOS_OUTBORDER_VERTEX == CP ||
    			CURSPOS_INBORDER_VERTEX == CP || CURSPOS_LINE == CP ||
    			CURSPOS_OUTBORDER == CP || CURSPOS_INBORDER == CP)
    		{
    			if ((CURSPOS_FIRST_VERTEX != CP && CURSPOS_LAST_VERTEX != CP &&
    				CURSPOS_INBORDER_VERTEX != CP && CURSPOS_INBORDER != CP))
    				bSpezCP = false;
    				

    			if (CURSPOS_VERTEX == CP ||
    				CURSPOS_FIRST_VERTEX == CP || CURSPOS_LAST_VERTEX == CP ||
    				CURSPOS_OUTBORDER_VERTEX == CP || CURSPOS_INBORDER_VERTEX == CP)
   					*pCP = CURSPOS_VERTEX;
    			else if (CURSPOS_LINE == CP ||
    					 CURSPOS_OUTBORDER == CP || CURSPOS_INBORDER == CP)
    			{
    				if (CURSPOS_VERTEX != *pCP)
    					*pCP = CURSPOS_LINE;
    				else
    					continue;
    			}

    			if (plGrabX) *plGrabX = m_GrabPkt.X();
    			if (plGrabY) *plGrabY = m_GrabPkt.Y();

    			if (ppBelowObjs)
					wOutObjs->AddItem (wObj);

    		} // if
    	} // for

    	if (pbSpezCP) *pbSpezCP = bSpezCP;	// 03.07.98

    	if (ppBelowObjs)
    		*ppBelowObjs = wOutObjs.detach();
    } // try

    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_FALSE;

} // CursorAtTopicalObjects


// --------------------------------------------------------------------------------------------
// Funktion ermittelt die CursorPosition pCP bez. der pIObj-Objekte;
// Rückgabewerte sind: CURSPOS_OBJECT und CURSPOS_OUTSIDE
STDMETHODIMP CTopicalObjects::CursorInSomeTopObjects (IEnumObjektGeometrie* pIObj,
	 												  BOOL bInBorder, CursPos* pCP)
{
    _ASSERTE (pCP != NULL);

    *pCP = CURSPOS_OUTSIDE;

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Point Pt;		// Position in BS-Koordinaten und
EPunkt Pkt;		//  in DB-Koordinaten

    if (!GetCursorCoordinates (Pt, Pkt)) return E_FAIL;

    MarkerInDBCoords (Pt);

CursPos CP;		// CursorPosition (CURSPOS_OBJECT bzw. CURSPOS_OUTSIDE)

    try
    {
	WUnknown Unk;

    	for (pIObj->Reset(); S_OK == pIObj->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		THROW_FAILED_HRESULT (wObj->CursorInObject (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2,
    													m_lEpsilon, bInBorder, &CP));

    		if (CURSPOS_OBJECT == CP)
    		{
    			*pCP = CURSPOS_OBJECT;
    			return S_OK;
    		}
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_FALSE;

} // CursorInSomeTopObjects


// --------------------------------------------------------------------------------------------
// Funktion ermittelt die CursorPosition pCP bez. der Marker der pIObj-Objekte;
// Rückgabewerte sind: CURSPOS_VERTEX und CURSPOS_UNKNOWN
STDMETHODIMP CTopicalObjects::CursorInMarkerSomeTopObjects (IEnumObjektGeometrie* pIObj,
    														CursPos* pCP)
{
    if (NULL == pIObj)
    	return S_FALSE;

    _ASSERTE (pCP != NULL);

    m_GrabPkt.X() = 0;			// falls es keinen GrabPunkt gibt
    m_GrabPkt.Y() = 0;
    *pCP = CURSPOS_UNKNOWN;

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Point Pt;		// Position in BS-Koordinaten und
EPunkt Pkt;		//  in DB-Koordinaten

    if (!GetCursorCoordinates (Pt, Pkt)) return E_FAIL;

    MarkerInDBCoords (Pt);

BOOL bInMark;			// Cursor nicht/in einem Marker (false/true)
WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes

    try
    {
	WUnknown Unk;

    	for (pIObj->Reset(); S_OK == pIObj->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		wObj->CursorInMarker (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2, &bInMark,
    							  &m_GrabPkt.X(), &m_GrabPkt.Y());

    		if (bInMark)	// Cursor in einem Marker
    		{
    			*pCP = CURSPOS_VERTEX;
    			return S_OK;
    		}
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_FALSE;

} // CursorInMarkerSomeTopObjects


// --------------------------------------------------------------------------------------------
// Funktion ermittelt die CursorPosition pCP bei der Flächenteilung;
// bShift: SHIFT-Taste nicht/gedrückt (false/true)
// Rückgabewerte sind: CURSPOS_VERTEX, VERTEX_LINE, CURSPOS_OBJECT und CURSPOS_OUTSIDE
STDMETHODIMP CTopicalObjects::CursorForAreaPartition (IUnknown* pIOG, CursPos* pCP,
    												  long* plGrabX, long* plGrabY)
{
    m_GrabPkt.X() = 0;			// falls es keinen GrabPunkt gibt
    m_GrabPkt.Y() = 0;
    *pCP = CURSPOS_OUTSIDE;

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Point Pt;		// Position in BS-Koordinaten und
EPunkt Pkt;		//  in DB-Koordinaten

    if (!GetCursorCoordinates (Pt, Pkt)) return E_FAIL;

    MarkerInDBCoords (Pt);

CursPos CP;		// CursorPosition

    ((IObjektGeometrie*)pIOG)->CursorPositionAtObject (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2,
    								   m_lEpsilon, false, &CP, &m_GrabPkt.X(), &m_GrabPkt.Y());

    if (plGrabX) *plGrabX = m_GrabPkt.X();
    if (plGrabY) *plGrabY = m_GrabPkt.Y();

    if (CURSPOS_VERTEX == CP ||
    	CURSPOS_FIRST_VERTEX == CP || CURSPOS_LAST_VERTEX == CP ||
    	CURSPOS_OUTBORDER_VERTEX == CP || CURSPOS_INBORDER_VERTEX == CP)
    {
    	*pCP = CURSPOS_VERTEX;
    	return S_OK;
    }

    if (CURSPOS_LINE == CP || CURSPOS_OUTBORDER == CP || CURSPOS_INBORDER == CP)
    {
    	*pCP = CURSPOS_LINE;
    	return S_OK;
    }

    ((IObjektGeometrie*)pIOG)->CursorInObject (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2,
    										   m_lEpsilon, false, &CP);

    if (CURSPOS_OBJECT == CP)
    	*pCP = CURSPOS_OBJECT;

    return S_OK;

} // CursorForAreaPartition


// --------------------------------------------------------------------------------------------
// Funktion ermittelt die CursorPosition pCP bez. aller ausgewählten m_TopObjs-Objekte
// (CURSPOS_VERTEX) sowie der pIObj-Objekte (CURSPOS_OBJECT und CURSPOS_OUTSIDE);
// Rückgabewerte sind: CURSPOS_VERTEX, CURSPOS_OBJECT und CURSPOS_OUTSIDE
STDMETHODIMP CTopicalObjects::CursorForIslandAdd (IEnumObjektGeometrie* pIObj, BOOL bInBorder,
    											  CursPos* pCP)
{
	_ASSERTE (pIObj != NULL);
    _ASSERTE (pCP != NULL);

    m_GrabPkt.X() = 0;			// falls es keinen GrabPunkt gibt
    m_GrabPkt.Y() = 0;
    *pCP = CURSPOS_OUTSIDE;

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Point Pt;		// Position in BS-Koordinaten und
EPunkt Pkt;		//  in DB-Koordinaten

    if (!GetCursorCoordinates (Pt, Pkt)) return E_FAIL;

    MarkerInDBCoords (Pt);

WEnumObjektGeometrie wEnum;

	RETURN_FAILED_HRESULT (m_TopObjs.GetEnumObjektGeometrie (wEnum.ppi()));

CursPos CP;				// CursorPosition (CURSPOS_OBJECT bzw. CURSPOS_OUTSIDE)
BOOL bInMark;			// Cursor nicht/in einem Marker (false/true)
WUnknown Unk;
WObjektGeometrie wObj;


    try
    {
    	for (wEnum->Reset(); S_OK == wEnum->Next (1, Unk.ppi(), NULL); )
		{
			wObj = Unk;
    		wObj->CursorInMarker (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2, &bInMark,
    							  &m_GrabPkt.X(), &m_GrabPkt.Y());

    		if (bInMark)	// Cursor in einem Marker
    		{
    			*pCP = CURSPOS_VERTEX;
// Die nachfolgende return-Zeile habe ich aus einem nicht mehr nachvollziehbarem Grund einmal
// herauskommentiert und dafür die break-Zeile eingefügt. Dies hat aber zur Folge, daß das Ergebnis "Cursor
// innerhalb einer Markierung" durch "*pCP = CURSPOS_OUTSIDE;" wieder eliminiert werden kann (08.04.99)
				return S_OK;
//    			break;
    		}
    	}

    	for (pIObj->Reset(); S_OK == pIObj->Next (1, Unk.ppi(), NULL); )
		{
			wObj = Unk;
    		THROW_FAILED_HRESULT (wObj->CursorInObject (Pkt.X(), Pkt.Y(), m_lMBX/2, m_lMBY/2,
    													m_lEpsilon, bInBorder, &CP));
    		if (CURSPOS_OBJECT == CP)
    		{
    			if (CURSPOS_VERTEX != *pCP)
    				*pCP = CURSPOS_OBJECT;
    			return S_OK;
    		}
    	}

    	*pCP = CURSPOS_OUTSIDE;
    }

    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_FALSE;

} // CursorForIslandAdd


// --------------------------------------------------------------------------------------------
// Mausspitze pMPT auf den Stützpunkt m_GrabPkt ziehen, der in (plGrabX, plGrabY) zurückgegeben
// wird, wenn die SHIFT-Taste nicht gedrückt wurde.
// Wenn ppBelowObjs != NULL gilt, werden in ppBelowObjs die Objektnummern der Objekte
// zurückgegeben, die den GrabPkt als Stützpunkt besitzen.
// return-Wert der Routine, wenn nicht/gegrabt wurde: S_FALSE / S_OK 
STDMETHODIMP CTopicalObjects::NewVertexWithGrab (POINT* pMPT, IDragObject* pDragObj,
    						  long* plGrabX, long* plGrabY, IEnumObjektGeometrie** ppBelowObjs)
{
    if (GetKeyState (VK_SHIFT) < 0)	//  SHIFT-Taste gedrückt
    	return S_FALSE;	// es wird nicht gegrabt, da SHIFT-Taste gedrückt ist

    if (m_GrabPkt.X() <= 0 || m_GrabPkt.Y() <= 0)
    	return S_FALSE;		// es kann nicht gegrabt werden, da es keinen GrabPunkt gibt

    if (plGrabX && plGrabY)
    {
    	*plGrabX = m_GrabPkt.X();
    	*plGrabY = m_GrabPkt.Y();

    Point MPt = BSKoordinaten (m_GrabPkt.X(), m_GrabPkt.Y());

	 	*pMPT = (POINT&)MPt;	// gegrabten BS-Punkt zurückgeben
    }

    if (pDragObj)	// wird z.B. ein Punktobjekt editiert, ist pDragObj == NULL
    {
    	// Strecke mit ungegrabtem pMPT löschen
    	pDragObj->SetEndPoint (*pMPT, m_bIsPaint, TRUE);
    	// Strecke mit gegrabtem pMPT neu zeichnen
    	pDragObj->SetEndPoint (*pMPT, m_bIsPaint, TRUE);
    }

    if (ppBelowObjs)
    	GetBelowObjects (ppBelowObjs);

    return S_OK;	// es wurde gegrabt

} // NewVertexWithGrab


// --------------------------------------------------------------------------------------------
// Liefert alle ausgewählten Linien- und Flächenobjekte, die den GrabPunkt als Stützpunkt
// besitzen
HRESULT CTopicalObjects::GetBelowObjects (IEnumObjektGeometrie** ppBelowObjs)
{
    _ASSERTE (ppBelowObjs != NULL);

WEnumObjektGeometrie wEnum;

	RETURN_FAILED_HRESULT (m_TopObjs.GetEnumObjektGeometrie (wEnum.ppi()));

WObjektGeometrie wObj;	// ObjektGeometrie eines einzelnen wEnum-Objektes
short iOT;				// Objekttyp des wObj-Objektes
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    try
    {
    // Objektgeometrie'n, die evtl. zurückgegeben werden
    WEnumObjektGeometrie wOutObjs (CLSID_EnumObjektGeometrie);
	WUnknown Unk;

    	for (wEnum->Reset(); S_OK == wEnum->Next (1, Unk.ppi(), NULL); )
    	{
			wObj = Unk;

    		wObj->GetObjTyp (&iOT);
	  		if (OT_KANTE != iOT && OT_FLAECHE != iOT)
    			continue;	// nur Linien- bzw. Flächenobjekte berücksichtigen

    		wObj->GetCnt (&lCnt);
    		wObj->GetX ((void**)&plXK);
    		wObj->GetY ((void**)&plYK);

    		for (long j = 0; j < lCnt; j++)
    			if (plXK[j] == m_GrabPkt.X() && plYK[j] == m_GrabPkt.Y())
    			{
					wOutObjs->AddItem (wObj);
    				break;
    			}
    	}

    	*ppBelowObjs = wOutObjs.detach();
    }

    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // GetBelowObjects


// --------------------------------------------------------------------------------------------
// Test, ob Grab-Funktion möglich ist; dann Rückgabe von S_OK, sonst E_FAIL;
// Grabben ist mit "sich selbst" nur eingeschränkt möglich: bei Linienobjekten zwischen den
// beiden Endpunkten und bei Flächenobjekten, nur dann mit einer anderen Kontur, wenn es nicht
// schon einen Berührungspunkt gibt;
// (lStartPktX,lStartPktY) ist der Punkt, bei dem die Objektmodifikation begann;
// (lEndPktX,lEndPktY) ist der Punkt, bei dem die Objektmodifikation abgeschlossen werden soll;
// in pStBelowObjs sind die Objektnummern der Objekte enthalten, die bei Beginn der
// Objektmodifikation, in pAbBelowObjs die Objekte, die beim Abschluß unter der Mausspitze lagen
// lEpsilon >= 0 wird bei StützpunktHinzufügen für den Test auf Nähe zu einer Strecke
// benötigt; deshalb muß bei StützpunktVerschieben lEpsilon < 0 sein
STDMETHODIMP CTopicalObjects::IsGrabAllowable (long lStartPktX, long lStartPktY, long lEndPktX,
											 long lEndPktY, IEnumObjektGeometrie* pStBelowObjs,
											 IEnumObjektGeometrie* pAbBelowObjs, long lEpsilon)
{
    _ASSERTE (pStBelowObjs != NULL);
    _ASSERTE (pAbBelowObjs != NULL);

long lStONr;	// eine Objektnummer der pStBelowObjs-Objekte
long lActONr;	// eine Objektnummer der pAbBelowObjs-Objekte
short iKIndS;	// Konturindex für Punkt (lStartPktX,lStartPktY)
short iKIndE;	// Konturindex für Punkt (lEndPktX,lEndPktY)

    try
    {
    // neue IObjektGeometrie erzeugen und initialisieren
	WUnknown Unk;

    	for (pStBelowObjs->Reset(); S_OK == pStBelowObjs->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

			wObj->GetONr (&lStONr);

	    	for (pAbBelowObjs->Reset(); S_OK == pAbBelowObjs->Next (1, Unk.ppi(), NULL); )
    		{
			WObjektGeometrie wActObj (Unk);

				wActObj->GetONr (&lActONr);

    			if (lStONr != lActONr) continue;

    		// Grabben mit "sich selbst" ist eingeschränkt möglich
    		int iOT = DEX_GetObjectType (lStONr);

    			if (OT_KANTE != iOT && OT_FLAECHE != iOT) return E_FAIL;

    			// bei einer Linie ist das Grabben zwischen den beiden Endpunkte möglich
    			if (OT_KANTE == iOT)
    			{
    				if (! GrabToClosedLine (wObj, lStartPktX, lStartPktY, lEndPktX, lEndPktY))
    					return E_FAIL;
    			}

    			// bei einer Fläche ist das Angrabben an eine andere Kontur dieser Fläche einmal
    			// möglich
    			else
    			{
    			bool bSt = KonturIndex (lStartPktX, lStartPktY, wObj, lEpsilon, iKIndS);
    			bool bEnd = KonturIndex (lEndPktX, lEndPktY, wObj, lEpsilon, iKIndE);

    				if (bSt && bEnd)
    				{
    					if (iKIndS == iKIndE)
    						return E_FAIL;	// Angrabben an die gleiche Kontur ist nicht erlaubt

    					// Test, ob zwischen der iKIndS- und der iKIndE-Kontur schon EINE
    					// Berührung existiert
    					if (IsAlreadyContact (wObj, iKIndS, iKIndE))
    						return E_FAIL;	// ein zweites Angrabben ist nicht mehr möglich
    				}
    			}
    		} // for
    	} // for
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // IsGrabAllowable


// --------------------------------------------------------------------------------------------
// Größe eines Markers von BS- in Datenbankkoordinaten umrechnen
void CTopicalObjects::MarkerInDBCoords (Point Pt)
{
int iMarkGr;

    GetMarkerSizeBS (&iMarkGr);

// linker oberer Eckpunkt bzw. rechter unterer Eckpunkt eines gedachten Markers um die aktuelle
// CursorPosition Pt (in BS-Koordinaten)
Point P1 (Pt.X() - iMarkGr/2, Pt.Y() + iMarkGr/2);
Point P2 (Pt.X() + iMarkGr/2, Pt.Y() - iMarkGr/2);
    									
EPunkt PLO = DBKoordinaten (P1);	// dto. in DB-Koordinaten
EPunkt PRU = DBKoordinaten (P2);

    m_lMBX = PRU.X() - PLO.X();	// Größe eines Markers (in DB-Koordinaten) in x- bzw.
    if (m_lMBX < 2) m_lMBX = 2; 
    m_lMBY = PLO.Y() - PRU.Y();	//  y-Richtung
    if (m_lMBY < 2) m_lMBY = 2; 
//	m_lEpsilon = (m_lMBX + m_lMBY) / 6;
	m_lEpsilon = (m_lMBX + m_lMBY) / 4;	// #WM030509
    if (m_lEpsilon < 1) m_lEpsilon = 1; 

} // MarkerInDBCoords


// --------------------------------------------------------------------------------------------
// Stützpunktmarkierungen nach Zeichnen eines Hintergrundbereiches nachzeichnen
STDMETHODIMP CTopicalObjects::MarkerTracing (void)
{
    if (m_bMarkVis)
    {
    	if (m_TopObjs.Count() > 0)	// mindestens 1 ausgewähltes Objekt
    		VerticesIndicate();		// Markierungen erneut zeichnen

    	m_bIsPaint = false;	// Hintergrund wurde gezeichnet (darf nicht vor VerticesIndicate()
    						// gesetzt werden !!!)
    	return S_OK;
    }
    	
    m_bIsPaint = false;	// Hintergrund wurde gezeichnet

// .... hier kommt noch etwas hin ....

    return S_OK;

} // MarkerTracing


// --------------------------------------------------------------------------------------------
// Stützpunktmarkierungen des lONr-Objektes anzeigen (bVisible == true) oder löschen
// (bVisible == false), wenn eine EditierWerkzeug aktiviert ist;
// return-Werte sind:
//  S_OK      im fehlerfreien Fall
//  S_FALSE   es ist kein EditierWerkzeug aktiviert
STDMETHODIMP CTopicalObjects::MarkerUpToDate (long lONr, bool bVisible)
{
    if (m_bMarkVis)
    {
    	try
    	{
    	WObjektGeometrie wObjGeom;	// leeres Objekt anlegen

    		// wObjGeom füllen
    		THROW_FAILED_HRESULT (CreateInterfaceOG (wObjGeom.ppi(), lONr));
    		THROW_FAILED_HRESULT (MarkerVisibility (wObjGeom, bVisible));
    	}
    	catch (_com_error& e)
    	{
    		return _COM_ERROR (e);
    	}	

    	return S_OK;
    }

    return S_FALSE;

} // MarkerUpToDate


// --------------------------------------------------------------------------------------------
// Test, ob das Grabben bei einem Linienobjekt zwischen den beiden Endpunkten erfolgt
// (return-Wert: true) oder nicht (false)
bool CTopicalObjects::GrabToClosedLine (IObjektGeometrie* pIOG, KoOrd lStartPktX,
    									KoOrd lStartPktY, KoOrd lEndPktX, KoOrd lEndPktY)
{
    _ASSERTE (pIOG != NULL);

short iOT;

    pIOG->GetObjTyp (&iOT);

    if (OT_KANTE != iOT) return false;

long lCnt;
KoOrd* plXK; KoOrd* plYK;

    pIOG->GetCnt (&lCnt);
    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);

    if (lStartPktX == plXK[0] && lStartPktY == plYK[0] &&
    	lEndPktX == plXK[lCnt-1] && lEndPktY == plYK[lCnt-1])
    	return true;	// Anfangspunkt wird auf Endpunkt gezogen

    if (lStartPktX == plXK[lCnt-1] && lStartPktY == plYK[lCnt-1] &&
    	lEndPktX == plXK[0] && lEndPktY == plYK[0])
    	return true;	// Endpunkt wird auf Anfangspunkt gezogen

    return false;	// alle anderen Fälle erlauben kein Grab

} // GrabToClosedLine


// --------------------------------------------------------------------------------------------
// Index der Flächenkontur in iKInd zurückgeben, in deren lEpsilon-Nähe der Punkt (x,y) liegt;
// ist lONr keine Fläche bzw. liegt (x,y) nicht in der lEpsilon-Nähe, wird false zurückgebene,
// sonst true
bool CTopicalObjects::KonturIndex (KoOrd x, KoOrd y, IObjektGeometrie* pIOG, long lEpsilon,
    							   short& iKInd)
{
    _ASSERTE (pIOG != NULL);

short iObjTyp;
    
    pIOG->GetObjTyp (&iObjTyp);
    if (iObjTyp != OT_FLAECHE) return false;	// keine Fläche		

long lInd;		// Index des Punktes (x,y) innerhalb von wObj

    if (lEpsilon < 0)	// Stützpunktindex bei StützpunktVerschieben
    {
    	if (pIOG->GetVertexIndex (x, y, &lInd) != S_OK)
    		return false;
    }
    else				// Streckenindex bei StützpunktHinzufügen
    {
    	if (pIOG->GetLineIndex (x, y, lEpsilon, &lInd) != S_OK)
    		return false;
    }

long lIndex;	// für Routine IndexTest(); werden
IndPos IP;		//  hier nicht ausgewertet

    pIOG->IndexTest (lInd, &iKInd, &lIndex, &IP);

    return true;

} // KonturIndex


// --------------------------------------------------------------------------------------------
// Test, ob sich die beiden Konturen mit den Indizes iKInd1 und iKInd2 schon einmal berühren;
// dann Rückgabe von true, sonst false
bool CTopicalObjects::IsAlreadyContact (IObjektGeometrie* pIOG, int iKInd1, int iKInd2)
{
    _ASSERTE (pIOG != NULL);

short iObjTyp;
    
    pIOG->GetObjTyp (&iObjTyp);

   	_ASSERTE (iObjTyp == OT_FLAECHE);		// keine Fläche		

KoOrd* plXK; KoOrd* plYK;
short iKCnt;				// Anzahl der Konturen von pIOG 
long* plCnt;				// Anzahl der Stützpunkte in den Konturen

    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);
    pIOG->GetKCnt (&iKCnt);
    pIOG->GetLPCnt (&plCnt);

    _ASSERTE (iKInd1 <= iKCnt);
    _ASSERTE (iKInd2 <= iKCnt);

long lFirstInd1 = 0;	// 1. Index der Kontur iKInd1
long lFirstInd2 = 0;	// 1. Index der Kontur iKInd2
int i = 0;

    do
    {
    	if (i < iKInd1) lFirstInd1 += plCnt[i];
    	if (i < iKInd2) lFirstInd2 += plCnt[i];
    	i++;
    }
    while (i < iKInd1 || i < iKInd2);

long lKL1 = plCnt[iKInd1];	// Länge der Kontur iKInd1
long lKL2 = plCnt[iKInd2];	// Länge der Kontur iKInd2

    for (long i1 = lFirstInd1; i1 < lFirstInd1 + lKL1 - 1; i1++)
    	for (long i2 = lFirstInd2; i2 < lFirstInd2 + lKL2 - 1; i2++)
    		if (plXK[i1] == plXK[i2] && plYK[i1] == plYK[i2])
    			return true;	// eine Berührung

    return false;

} // IsAlreadyContact



///////////////////////////////////////////////////////////////////////////////////////////////
// *** interface ITRiASNotificationSink: Events von TRiAS abfangen

STDMETHODIMP CTopicalObjects::ServerEvent (SERVEREVT se)
{
    switch (se) {
    case SERVEREVT_ServerToClose:		// das letzte vom Tage
    // Verbindung beim ConnectionPoint abmelden
    	if (0 != m_dwCookie) 
    		DisconnectFromServer();
    	break;
    }
    return S_OK;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CTopicalObjects::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    switch (ve)
    {
    	case GEOVIEWEVT_PaintingView:	// DEX_ERASEBKGND
    		m_bIsPaint = true;		// Hintergrund wird gezeichnet
    		break;

    	case GEOVIEWEVT_ViewPainted:	// DEX_PAINTTOPLAYER
    		DEX_GetExposedArea (m_rcHintergrund);	// Hintergrundbereich bestimmen
    		MarkerTracing();		// hier kommt u.a. m_bIsPaint = false
    		break;
    }

    return S_OK;	// immer weiterleiten
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CTopicalObjects::GeoClassEvent not implemented");
	return S_OK;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    switch (oe)
	{
		case GEOOBJECTEVT_ObjectSelected:
		{
    		m_TopObjs.AddObject (lONr);

		HRESULT hr = MarkerUpToDate (lONr);

    		if (FAILED(hr))
			    ATLTRACE("failure in CTopicalObjects::GeoObjectEvent");
    		break;
		}

		case GEOOBJECTEVT_ObjectUnSelected:
		{
    		m_TopObjs.RemoveObject (lONr);

		HRESULT hr = MarkerUpToDate (lONr, false);

    		if (FAILED(hr))
			    ATLTRACE("failure in CTopicalObjects::GeoObjectEvent");
    		break;
		}

		case GEOOBJECTEVT_ObjectDeleted:
    		break;

		case GEOOBJECTEVT_DeletingObject:
    		m_TopObjs.DeleteObject (lONr);
    		break;

		case GEOOBJECTEVT_GeometryChanged:		// Objektgeometrie wurde verändert
    		m_TopObjs.ChangeObject (lONr);
    		break;
    }

    return S_OK;	// immer weiterleiten
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CTopicalObjects::GeoFeatureEvent not implemented");
	return S_OK;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CTopicalObjects::GeoRelationEvent not implemented");
	return S_OK;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CTopicalObjects::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    switch (oe)
	{
		case OBJWNDEVT_WindowCreated:
    		break;

		case OBJWNDEVT_WindowDestroyed:
    		break;

		case OBJWNDEVT_GotFocus:
    		break;

		case OBJWNDEVT_LostFocus:
    		break;

		default:
    		_ASSERTE (false);
    		break;
    }
    return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Liste von IObjektGeometrien

// liefert Enumerator mit allen derzeit gespeicherten ObjektGeometrie'n
HRESULT CGeoObjs::GetEnumObjects (IEnumUnknown **ppIEnum)
{
	try {
	WEnumObjektGeometrie Enum (CLSID_EnumObjektGeometrie);
	
		for (CObjectMap::iterator it = m_Objs.begin(); 
    		 it != m_Objs.end(); ++it)
		{
    		Enum -> AddItem ((*it).second.GetObject());
		}

	WEnumUnknown EnumUnk(Enum);

		*ppIEnum = EnumUnk.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// liefert Enumerator mit den Objektnummern aller derzeit gespeicherten ObjektGeometrie'n
HRESULT CGeoObjs::GetEnumObjectsByNumber (IEnumObjectsByNumber** ppIEnum)
{
    try
    {
    WEnumObjectsByNumber wObjNr (CLSID_EnumObjectsByNumber);

    	for (CObjectMap::iterator it = m_Objs.begin(); it != m_Objs.end(); ++it) {
			if (0 != (*it).first)	// Objektnummer
    			wObjNr->AddItem ((*it).first);
		}
    	*ppIEnum = wObjNr.detach();

    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // GetEnumObjectsByNumber


// --------------------------------------------------------------------------------------------
// liefert Enumerator mit den derzeit gespeicherten ObjektGeometrie'n
HRESULT CGeoObjs::GetEnumObjektGeometrie (IEnumObjektGeometrie** ppIEnum, bool bAll)
{
    try
    {
    WEnumObjektGeometrie wOGeom (CLSID_EnumObjektGeometrie);

    	for (CObjectMap::iterator it = m_Objs.begin(); it != m_Objs.end(); ++it)
		{
			if ((*it).second.GetObject() &&	// Objektgeometrie
				(bAll || (*it).second.GetTemporary()))
   				wOGeom->AddItem ((*it).second.GetObject());
		}
    	*ppIEnum = wOGeom.detach();

    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // GetEnumObjektGeometrie


// --------------------------------------------------------------------------------------------
// Test, ob lONr-Objekt in der Liste enthalten ist, wenn ja, dann pbContain == true
HRESULT CGeoObjs::IsObject (long lONr, BOOL* pbContain)
{
CObjectMap::iterator it = m_Objs.find (lONr);

    (it != m_Objs.end()) ? (*pbContain = true) : (*pbContain = false);
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// Test, ob pIOG-Objekt in der Liste enthalten ist, wenn ja, dann pbContain == true
HRESULT CGeoObjs::IsObject (IObjektGeometrie *pIOG, BOOL* pbContain)
{
CObjectMap::iterator it = m_Objs.find (reinterpret_cast<LONG>(pIOG));

    (it != m_Objs.end()) ? (*pbContain = true) : (*pbContain = false);
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// fügt ein neues Objekte zur Liste hinzu (bzw. erhöht Zähler)
HRESULT CGeoObjs::AddObject (LONG lONr)
{
// testen, ob Objekt bereits vertreten ist, wenn nicht hinzufügen
CObjectMap::iterator it = m_Objs.find (lONr);

    if (it == m_Objs.end()) {
    	try {
    	pair<CObjectMap::iterator, bool> p =
    		 m_Objs.insert (lONr, CTopicalObject(lONr));	// throws_com_error
    	
    		it = p.first;		// zeigt auf neues Element 

    	} catch (_com_error& e) {
    		return _COM_ERROR (e);
    	} catch (bad_alloc) {
    		return E_OUTOFMEMORY;
    	}
    }

// Zähler erhöhen
    (*it).second.Select();
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// fügt ein neues Objekte zur Liste hinzu (bzw. erhöht Zähler)
HRESULT CGeoObjs::AddObject (IObjektGeometrie *pIOG)
{
ulong uuu = reinterpret_cast<LONG>(pIOG);
CObjectMap::iterator it;

    try {
    pair<CObjectMap::iterator, bool> p =
    	 m_Objs.insert (reinterpret_cast<LONG>(pIOG), CTopicalObject(pIOG));	// throws_com_error
    
    	it = p.first;			// zeigt auf neues Element 
		_ASSERTE(p.second);

    } catch (_com_error& e) {
    	return _COM_ERROR (e);
    } catch (bad_alloc) {
    	return E_OUTOFMEMORY;
    }

// Zähler erhöhen
    (*it).second.Select();
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// erniedrigt Zähler eines Objektes und entfernt dieses aus der Liste, wenn der Zähler auf 0
// gegangen ist
HRESULT CGeoObjs::RemoveObject (LONG lONr)
{
// testen, ob Objekt überhaupt vertreten ist, wenn nicht, aufhören
CObjectMap::iterator it = m_Objs.find (lONr);

    if (it == m_Objs.end())
    	return E_FAIL;

// wenns der letzte war, dann S_OK liefern, ansonsten S_FALSE
    if ((*it).second.UnSelect() > 0)
    	return S_FALSE;
    
    m_Objs.erase (it);		// aus Liste herausnehmen
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// erniedrigt Zähler eines Objektes und entfernt dieses aus der Liste, wenn der Zähler auf 0
// gegangen ist
HRESULT CGeoObjs::RemoveObject (IObjektGeometrie *pIOG)
{
// testen, ob Objekt überhaupt vertreten ist, wenn nicht, aufhören
CObjectMap::iterator it = m_Objs.find (reinterpret_cast<LONG>(pIOG));

    if (it == m_Objs.end())
    	return E_FAIL;

// wenns der letzte war, dann S_OK liefern, ansonsten S_FALSE
    if ((*it).second.UnSelect() > 0)
    	return S_FALSE;
    
    m_Objs.erase (it);		// aus Liste herausnehmen
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// entfernt ein Objekt aus der Liste, unabhängig davon, ob der Zähler bereits 0 ist oder nicht
HRESULT CGeoObjs::DeleteObject (LONG lONr)
{
// testen, ob Objekt überhaupt vertreten ist, wenn nicht, aufhören
CObjectMap::iterator it = m_Objs.find (lONr);

    if (it == m_Objs.end())
    	return E_FAIL;

    m_Objs.erase (it);		// in jedem Fall aus Liste herausnehmen
    return S_OK;
}


// --------------------------------------------------------------------------------------------
HRESULT CGeoObjs::DeleteObject (IObjektGeometrie *pIOG)
{
// testen, ob Objekt überhaupt vertreten ist, wenn nicht, aufhören
CObjectMap::iterator it = m_Objs.find (reinterpret_cast<LONG>(pIOG));

    if (it == m_Objs.end())
    	return E_FAIL;

    m_Objs.erase (it);		// in jedem Fall aus Liste herausnehmen
    return S_OK;
}


// --------------------------------------------------------------------------------------------
// entfernt Objekte aus der Liste;
// bAll == TRUE:  alle Objekte
// bAll == FALSE: nur die temporären Objekte
HRESULT CGeoObjs::DeleteObjects (bool bAll)
{
bool bDel = false;	// es wurde (noch) kein Objekt aus der Liste herausgenommen

	// alle Objekte aus der Liste herausnehmen
	if (bAll)
		while (m_Objs.size() > 0)
		{
		CObjectMap::iterator it = m_Objs.begin();

    		m_Objs.erase (it);	// Objekt aus Liste herausnehmen
			bDel = true;		// es wurde mindestens ein Objekt herausgenommen
		}

	// nur die temporären Objekte aus der Liste herausnehmen
	else
	{
	long lSize = m_Objs.size();
	CObjectMap::iterator it = m_Objs.begin();

		while (lSize > 0)
		{
			if ((*it).second.GetTemporary())
			{
	    		m_Objs.erase (it);
				bDel = true;
			}
			else
				++it;
			lSize--;
		}
	}

	if (bDel)
		return S_OK;
	return S_FALSE;
}


// --------------------------------------------------------------------------------------------
// liefert das kleinste umschreibende Rechteck von Objekten aus der Liste
HRESULT CGeoObjs::GetObjectsRectangle (KoOrd* plXmin, KoOrd* plXmax, KoOrd* plYmin,
									   KoOrd* plYmax, bool bAll)
{
	_ASSERTE (plXmin != NULL);
	_ASSERTE (plXmax != NULL);
	_ASSERTE (plYmin != NULL);
	_ASSERTE (plYmax != NULL);

KoOrd lXmin, lXmax, lYmin, lYmax;	// einzelnes Rechteck

	*plXmin = MAXKOORD;
	*plXmax = -1;
	*plYmin = MAXKOORD;
	*plYmax = -1;

    for (CObjectMap::iterator it = m_Objs.begin(); it != m_Objs.end(); ++it)
	{
		if ((*it).second.GetObject() &&	// Objektgeometrie
			(bAll || (*it).second.GetTemporary()))
		{
		WObjektGeometrie wObj = (*it).second.GetObject();

   			wObj->GetCont (&lXmin, &lXmax, &lYmin, &lYmax);
			*plXmin = min (lXmin, *plXmin);
			*plXmax = max (lXmax, *plXmax);
			*plYmin = min (lYmin, *plYmin);
			*plYmax = max (lYmax, *plYmax);
		}
	}

	if (*plXmax >= 0)
		return S_OK;

	*plXmin = 0;
	*plXmax = 0;
	*plYmin = 0;
	*plYmax = 0;

	return S_FALSE;		// keine passenden Objekte vorhanden
}


// --------------------------------------------------------------------------------------------
// Objektgeometrie aus TRiAS neu einlesen
HRESULT CGeoObjs::ChangeObject (LONG lONr)
{
// testen, ob Objekt überhaupt vertreten ist, wenn nicht, aufhören
CObjectMap::iterator it = m_Objs.find (lONr);

    if (it == m_Objs.end())
    	return E_FAIL;

    // Geometrie von TRiAS neu holen	
    try
    {
    WInitObjektGeometrie wIObj ((*it).second.GetObject());

    	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // ChangeObject
