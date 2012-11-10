// Definitionen: Abschnitt eines schon existierenden Objektes (Linien oder Flächenkontur) durch
//				 einen Abschnitt eines anderen Objektes ersetzen

// File: CommonBorder.cpp
// W. Mörtl


#include "GeoEditP.h"

#include <registrx.hxx>		// CCurrentUser

#include "CommonBorder.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CCommonBorder::CCommonBorder (void)
{
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
	m_lXMin = MAXKOORD;
	m_lXMax = -1;
	m_lYMin = MAXKOORD;
	m_lYMax = -1;
	m_bFirstModObj = true;
}


// --------------------------------------------------------------------------------------------
// Destruktor
CCommonBorder::~CCommonBorder (void)
{
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur CObjectModify-Klasse über das Interface IModifyClassSite herstellen;
// es wird also von der Klasse CCommonBorder KEINE (!!) direkte Verbindung zu TRiAS über
// Interface ITriasExtension hergestellt
STDMETHODIMP CCommonBorder::SetModifyClassSite (IEditExtensionSite* pIEdExSite,
												IModifyClassSite*)
{
    COM_TRY
    {
    	if (NULL != pIEdExSite)
    	{
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));
    		m_wEdExSite = pIEdExSite;
    	}
    	else
    	{
    		m_wTopObjs.Assign (NULL);	// freigeben
    		m_wEdExSite.Assign (NULL);	// freigeben
    	}
    }
    COM_CATCH;

    return S_OK;

} // SetModifyClassSite


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::LineElongation (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CCommonBorder::LineElongation");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::AreaPartition (long, POINT)
{
    ATLTRACENOTIMPL("CCommonBorder::AreaPartition");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::IslandAddition (IEnumObjektGeometrie*)
{
    ATLTRACENOTIMPL("CCommonBorder::IslandAddition");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::Rectangularity (long, int, long, double, double, double,
    										 IEnumObjectsByNumber**)
{
    ATLTRACENOTIMPL("CCommonBorder::Rectangularity");
}


// --------------------------------------------------------------------------------------------
// Übernahme eines Linienabschnittes für die pModObjs-Objekte
//   pModObjs:  die zu modifizierenden Objekte, die bei Aufruf des Menüs unter der Mausspitze
//              lagen
//   lRMX,lRMY:	Punkt, bei dem das Menü gerufen wurde
STDMETHODIMP CCommonBorder::MakeCommonBorder (IEnumObjektGeometrie* pModObjs, long lRMX,
											  long lRMY)
{
	_ASSERTE(NULL != pModObjs);

	m_lRMX = lRMX;
	m_lRMY = lRMY;

    COM_TRY
    {
		m_wModObjs = pModObjs;	// mit implizitem QueryInterface

		m_wTopObjs->GetEpsilon (&m_lCursEps);
		m_wTopObjs->GetMarkerSizeBS (&m_iMarkGr);

	// das Quell-Objekt, von dem ein Linienabschnitt übernommen werden soll, ermitteln
	HRESULT hrRet;
	WObjektGeometrie wSrcObj;

		THROW_FAILED_HRESULT (hrRet = DetermineSourceObject (wSrcObj.ppi()));
		if (S_OK != hrRet) return hrRet;

	// ein zu modifizierendes Objekt ermitteln
	WObjektGeometrie wModObj;

		THROW_FAILED_HRESULT (DetermineAModifyObject (wModObj.ppi()));

	// die beiden Endpunkte des zu übernehmenden Linienabschnittes ermitteln
		hrRet = DetermineBorderEndPoints (wModObj, wSrcObj);

		if (S_OK != hrRet)
		{
		ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
		ResString resText (ResID (IDS_NOSOURCEOBJECT, pRF), 200);

    		MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
			PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);
			return hrRet;
		}
	}
	COM_CATCH;


	// Soll der Abschnitt aus einer Flächenkontur bzw. geschlossenen Kante übernommen werden?
	if (m_bIsSrcClosed)
	{
	// bei einem geschlossenen Linienzug den gewünschten Abschnitt durch den Anwender
	// interaktiv auswählen lassen
	CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathEdit);
	ResString resMarkColor (ResID (IDS_MARKCOLOR, pRF), 30);
	DWORD dwColor;

		if (cuExtConfig.GetDWORD (resMarkColor.Addr(), dwColor))
   			m_colFill = Color (GetRValue(dwColor), GetGValue(dwColor), GetBValue(dwColor));
		else
   			m_colFill = Color (GetRValue(ulGW0), GetGValue(ulGW0), GetBValue(ulGW0));

		m_colInkFill = Color (255 - m_colFill.Red(), m_colFill.Green(), m_colFill.Blue());
		m_colBound = m_colFill;
		m_iBoundWidth = floor(m_iMarkGr / 4.);

		FindShortestSection();
		InkMarker();
		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

	ResString rsText (ResID (IDS_KEYBOARDINPUT, pRF), 200);
		
		DEX_SetMessageStringNoKickIdle (rsText.Addr());
	}

	// Übernahme von einer offenen Kante; deshalb ist die Auswahl des Abschnitts mit der
	// TAB-Taste und die eigentliche Übernahme mit der ENTER-Taste nicht erforderlich
	else
	{
		m_lSrcFromInd = min (m_lSrcInd1, m_lSrcInd2);
		m_lSrcToInd = max (m_lSrcInd1, m_lSrcInd2);
		ReplaceLinePart();
	}

    return S_OK;

} // MakeCommonBorder


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CCommonBorder::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CCommonBorder::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CCommonBorder::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
// hPr: HPROJECT
STDMETHODIMP CCommonBorder::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    switch (ve)
    {
    	case GEOVIEWEVT_PaintingView:	// kommt vor dem Zeichnen des Hintergrundes
    									// (entspr. DEX_ERASEBKGND)
    		break;

    	case GEOVIEWEVT_ViewPainted:	// kommt nach dem Zeichnen des Hintergrundes
    									// (entspr. DEX_PAINTTOPLAYER)
		{
			InkMarker();	// Sondermarkierungen erneut zeichnen
			m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

		ResString rsText (ResID (IDS_KEYBOARDINPUT, pRF), 200);
		
			DEX_SetMessageStringNoKickIdle (rsText.Addr());
    		break;
		}
	}

    return S_OK;	// immer weiterleiten

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CCommonBorder::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    ATLTRACE("CCommonBorder::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CCommonBorder::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CCommonBorder::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CCommonBorder::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CCommonBorder::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CCommonBorder::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
    switch (uiMsg)
    {
    	case WM_KEYUP:
    		KeyUp (wParam);
			break;

		case WM_CHAR:
    		WMChar (wParam);
	}

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CCommonBorder::KeyUp (WPARAM wParam)
{
	switch (wParam)
	{
		case VK_TAB:	// TAB-Taste wurde losgelassen
			break;

		case VK_RETURN:	// ENTER-Taste wurde losgelassen
			break;
	}

    return S_OK;
}


// --------------------------------------------------------------------------------------------
// eine bestimmte Taste der Tastatur wurde gedrückt
HRESULT CCommonBorder::WMChar (WPARAM wParam)
{
	switch (wParam)
	{
		case VK_TAB:	// TAB-Taste wurde gedrückt
			// bei einem geschlossenen Linienzug den anderen möglichen Abschnitt farblich hervorheben
			if (m_bIsSrcClosed)
			{
				swap (m_lSrcFromInd, m_lSrcToInd);
				InkMarker();
			}
			break;

		case VK_RETURN:	// ENTER-Taste gedrückt
			ReplaceLinePart();
			break;

		case VK_ESCAPE:	// ESC-Taste gedrückt
			m_wTopObjs->VerticesIndicate();
			PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);	// CCommonBorder-Objekt zerlegen
			break;
	}

    return S_OK;
}


// --------------------------------------------------------------------------------------------
// Ermittlung des Quell-Objektes, d.h. des Objektes, von dem ein Linienabschnitt zu übernehmen ist
HRESULT CCommonBorder::DetermineSourceObject (IObjektGeometrie** ppSrcObj)
{
int iSrcObjCnt = 0;	// Zähler für Quell-Objekte
CursPos CP;			// CursorPosition (CURSPOS_OBJECT bzw. CURSPOS_OUTSIDE)
KoOrd lX, lY;		// Rückgabeparameter von CursorPositionAtObject(); werden hier nicht genutzt
long lMBX, lMBY;	// Größe der Stützpunktmarkierung (in DB-Koordinaten)
short iOT;
short iCCnt;		// Anzahl der Flächenkonturen

	m_wTopObjs->GetMarkerSizeDB (&lMBX, &lMBY);

	COM_TRY
	{
	// alle ausgewählten, d.h. markierten Objekte geben lassen
	WEnumObjektGeometrie wAllSelObjs;

		THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, wAllSelObjs.ppi()));
	
	WUnknown Unk;

		for (wAllSelObjs->Reset(); S_OK == wAllSelObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

			wObj->GetObjTyp (&iOT);
			if (OT_KANTE != iOT && OT_FLAECHE != iOT) continue;
			
			bool bAllContours = false;	// Parameter für CursorPositionAtObject()

				if (OT_FLAECHE == iOT)
				{
					wObj->GetKCnt (&iCCnt);
					if (iCCnt > 1) bAllContours = true;
				}

	  			THROW_FAILED_HRESULT (wObj->CursorPositionAtObject (m_lRMX, m_lRMY, lMBX/2,
											lMBY/2, m_lCursEps, bAllContours, &CP, &lX, &lY));

   			if (CURSPOS_OUTSIDE == CP)
			{
				iSrcObjCnt++;
				if (iSrcObjCnt > 1) break;
				*ppSrcObj = wObj.detach();
			}
		}
	}
	COM_CATCH;

	if (1 == iSrcObjCnt)
		return S_OK;	// genau ein Quell-Objekt gefunden

ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (0 == iSrcObjCnt)
	{
	ResString resText (ResID (IDS_NOSOURCEOBJECT, pRF), 200);

   		MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
	char pcBuffer[_MAX_PATH];
	ResString resText (ResID (IDS_OBJECTNOTUNIQUE, pRF), sizeof(pcBuffer));

		wsprintf (pcBuffer, resText.Addr(), iSrcObjCnt);
   		MessageBox (__hWndM, pcBuffer, resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
	}

	PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);
	return S_FALSE;	

} // DetermineSourceObject


// --------------------------------------------------------------------------------------------
// Ermittlung eines zu modifizierenden Objektes, d.h. eines Objektes, das von dem Quell-Objekt
// einen Linienabschnitt übernehmen soll
HRESULT CCommonBorder::DetermineAModifyObject (IObjektGeometrie** ppModObj)
{
short iOT;

	m_lModNextInd = -1;	// der nächste Stützpunktindex des zu modifizierenden Objektes nach
						// dem Menü-Klick-Punkt (m_lRMX,m_lRMY)

	COM_TRY
	{
	WUnknown Unk;

		for (m_wModObjs->Reset(); S_OK == m_wModObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

			wObj->GetObjTyp (&iOT);
			if (OT_KANTE != iOT && OT_FLAECHE != iOT) continue;

    		// Index m_lNextInd des nächsten Stützpunktes bzgl. des Punktes (m_lRMX,m_lRMY)
    		if (S_OK == wObj->GetLineIndex (m_lRMX, m_lRMY, m_lCursEps, &m_lModNextInd))
			{
				*ppModObj = wObj.detach();
				break;
			}
		}
	}
	COM_CATCH;

	if (m_lModNextInd < 0)
	{
		DEX_Error (RC_CommonBorder, EC_NOINDEX);
		PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);
    	return E_UNEXPECTED;
	}

	return S_OK;

} // DetermineAModifyObject


// --------------------------------------------------------------------------------------------
// Die beiden Endpunkte des zu übernehmenden Linienabschnittes ermitteln.
//   pModObj:  ein Objekt, das den Linienabschnitt übernehmen soll
//   pSrcObj:  Objekt, von dem ein Linienabschnitt übernommen werden soll
// return: S_OK    (es gibt mindestens 2 gemeinsame Stützpunkte)
//         S_FALSE (es gibt nur einen bzw. keinen gemeinsamen Stützpunkt)

HRESULT CCommonBorder::DetermineBorderEndPoints (IObjektGeometrie* pModObj,
												 IObjektGeometrie* pSrcObj)
{
	_ASSERTE(NULL != pModObj);
	_ASSERTE(NULL != pSrcObj);

HRESULT hrRet = S_FALSE;	// Rückkehrwert dieser Routine
long lInd; 					// Rückgabeparameter für IndexTest(); werden
IndPos IP;					//  hier nicht ausgewertet


// Geometrie holen
short iModOT;					// Objekttyp
KoOrd* plModX; KoOrd* plModY;	// Stützpunkte eines zu modifizierenden Objektes
long lSrcCnt, lModCnt;			// Gesamtanzahl der Stützpunkte
short iSrcCCnt;					// Anzahl der Konturen des Quell-Objektes
long* plSrcCnt;					// Anzahl der Stützpunkte pro Kontur des Quell-Objektes

	pSrcObj->GetObjTyp(&m_iSrcOT);
	pSrcObj->GetCnt (&lSrcCnt);
	pSrcObj->GetX ((void**)&m_plSrcX);
	pSrcObj->GetY ((void**)&m_plSrcY);

	m_bIsSrcClosed = true;	// pSrcObj ist eine Fläche bzw. geschlossene Kante

	if (OT_KANTE == m_iSrcOT)
	{
		if (m_plSrcX[0] != m_plSrcX[lSrcCnt-1] ||
			m_plSrcY[0] != m_plSrcY[lSrcCnt-1])
			m_bIsSrcClosed = false;	// pSrcObj ist eine offene Kante
	}	
	else if (OT_FLAECHE == m_iSrcOT)
	{
		pSrcObj->GetKCnt (&iSrcCCnt);
		pSrcObj->GetLPCnt (&plSrcCnt);
	}

	pModObj->GetObjTyp(&iModOT);
	pModObj->GetCnt (&lModCnt);
	pModObj->GetX ((void**)&plModX);
	pModObj->GetY ((void**)&plModY);

	
	m_lSrcInd1 = -1;	// für den Fall, dass die beiden Objekte nicht
	m_lSrcInd2 = -1;	//  mindestens 2 Stützpunkte gemeinsam haben
	m_iSrcCInd = -1;


// Vergleich von pSrcObj- und pModObj-Objekt
	m_lSrcAnfInd = 0;			// 1. Index bzw.
	m_lSrcEndInd = lSrcCnt - 1;	//  letzter Index der pSrcObj-Kante bzw. -Kontur

bool bIsModClosed = true;		// pModObj-Objekt ist eine Fläche bzw. geschlossene Kante

	// das pModObj-Objekt ist ein Kante
	if (OT_KANTE == iModOT)
	{
		if (plModX[0] != plModX[lModCnt-1] ||
			plModY[0] != plModY[lModCnt-1])
			bIsModClosed = false;	// pModObj ist eine offene Kante

		m_lModAnfInd = 0;			// 1. Index bzw.
		m_lModEndInd = lModCnt - 1;	//  letzter Index der pModObj-Kante

		// den 1. gemeinsamen Punkt suchen
		hrRet = GetEndPoint1 (m_lModNextInd, plModX, plModY, bIsModClosed);
		if (S_OK != hrRet)
			return hrRet;

		if (OT_FLAECHE == m_iSrcOT)	// das Quell-Objekt pSrcObj ist eine Fläche
		{
			// Nummer der Flächenkontur ermitteln, zu der der 1. gemeinsame Punkt gehört
			pSrcObj->IndexTest (m_lSrcInd1, &m_iSrcCInd, &lInd, &IP);

			for (int i = 0; i < m_iSrcCInd; ++i)
				m_lSrcAnfInd += plSrcCnt[i];

			m_lSrcEndInd = m_lSrcAnfInd + plSrcCnt[m_iSrcCInd] - 1;
		}
	}


	// das pModObj-Objekt ist ein Fläche
	else
	{
		_ASSERTE(OT_FLAECHE == iModOT);

	short iModCCnt;	// Anzahl der Konturen
	long* plModCnt;

		pModObj->GetKCnt (&iModCCnt);
		pModObj->GetLPCnt (&plModCnt);

		m_iModCInd = -1;

		pModObj->IndexTest (m_lModNextInd, &m_iModCInd, &lInd, &IP);

		m_lModAnfInd = 0;
		for (int i = 0; i < m_iModCInd; ++i)
			m_lModAnfInd += plModCnt[i];

		m_lModEndInd = m_lModAnfInd + plModCnt[m_iModCInd] - 1;

		// den 1. gemeinsamen Punkt suchen
		hrRet = GetEndPoint1 (m_lModNextInd, plModX, plModY, bIsModClosed);
		if (S_OK != hrRet)
			return hrRet;

		if (OT_FLAECHE == m_iSrcOT)	// das Quell-Objekt pSrcObj ist eine Fläche
		{
			// Nummer der Flächenkontur ermitteln, zu der der 1. gemeinsame Punkt gehört
			pSrcObj->IndexTest (m_lSrcInd1, &m_iSrcCInd, &lInd, &IP);

			for (int i = 0; i < m_iSrcCInd; ++i)
				m_lSrcAnfInd += plSrcCnt[i];

			m_lSrcEndInd = m_lSrcAnfInd + plSrcCnt[m_iSrcCInd] - 1;
		}
	}

	// den 2. gemeinsamen Punkt suchen
	hrRet = GetEndPoint2 (m_lModNextInd, plModX, plModY, bIsModClosed);
	if (S_OK != hrRet)
		return hrRet;

	if (m_lSrcInd1 == m_lSrcInd2)
		return S_FALSE;		// die beiden gefundenen Punkte sind identisch
	return S_OK;

} // DetermineBorderEndPoints


// --------------------------------------------------------------------------------------------
// Ermittlung eines evtl. vorhandenen gemeinsamen Punktes zwischen 2 Objekten
//   lStartInd:      Stützpunktindex , ab dem auf dem zu modifizierenden Objekt die Suche
//                   AUFWÄRTS erfolgt
//   plModX, plModY: Koordinaten des 1. Objektes (zu modifizierendes Objekt)
//   bIsModClosed:   das zu modifizierende Objekt ist geschlossen/offen (true/false)
// Das 2. Objekt ist das Quell-Objekt.
// Return:
//   S_OK:    es gibt einen gemeinsamen Punkt
//   S_FALSE: es gibt keinen gemeinsamen Punkt
HRESULT CCommonBorder::GetEndPoint1 (long lStartInd, KoOrd* plModX, KoOrd* plModY,
									 bool bIsModClosed)
{
	_ASSERTE(NULL != plModX);
	_ASSERTE(NULL != plModY);

	for (long lMod = lStartInd; lMod <= m_lModEndInd && -1 == m_lSrcInd1; ++lMod)
		for (long lSrc = m_lSrcAnfInd; lSrc <= m_lSrcEndInd; ++lSrc)
			if (plModX[lMod] == m_plSrcX[lSrc] &&
				plModY[lMod] == m_plSrcY[lSrc])
			{
				m_EndPkt1.X() = m_plSrcX[lSrc];
				m_EndPkt1.Y() = m_plSrcY[lSrc];
				m_lSrcInd1 = lSrc;
				m_lModInd1 = lMod;
				break;
			}

	if (-1 == m_lSrcInd1)
	{
		if (!bIsModClosed)
			return S_FALSE;	// für offenes zu modifizierendes Objekt keinen gemeinsamen
							//  Stützpunkt mit Quell-Objekt gefunden

		// bei geschlossenem zu modifizierenden Objekt noch weiter suchen
		for (long lMod = m_lModAnfInd+1; lMod < lStartInd && -1 == m_lSrcInd1; ++lMod)
			for (long lSrc = m_lSrcAnfInd; lSrc <= m_lSrcEndInd; ++lSrc)
				if (plModX[lMod] == m_plSrcX[lSrc] &&
					plModY[lMod] == m_plSrcY[lSrc])
				{
					m_EndPkt1.X() = m_plSrcX[lSrc];
					m_EndPkt1.Y() = m_plSrcY[lSrc];
					m_lSrcInd1 = lSrc;
					m_lModInd1 = lMod;
					break;
				}
	}

	if (-1 == m_lSrcInd1)
		return S_FALSE;	// kein gemeinsamer Stützpunkt mit Quell-Objekt gefunden

	return S_OK;	// erster gemeinsamer Stützpunkt gefunden

} // GetEndPoint1


// --------------------------------------------------------------------------------------------
// Ermittlung eines evtl. zweiten gemeinsamen Punktes zwischen 2 Objekten
//   lStartInd:      Stützpunktindex , ab dem auf dem zu modifizierenden Objekt die Suche
//                   ABWÄRTS erfolgt
//   plModX, plModY: Koordinaten des 1. Objektes (zu modifizierendes Objekt)
//   bIsModClosed:   das zu modifizierende Objekt ist geschlossen/offen (true/false)
// Das 2. Objekt ist das Quell-Objekt.
// return:
//   S_OK:    es gibt einen weiteren gemeinsamen Punkt
//   S_FALSE: es gibt keinen weiteren gemeinsamen Punkt
HRESULT CCommonBorder::GetEndPoint2 (long lStartInd, KoOrd* plModX, KoOrd* plModY,
									 bool bIsModClosed)
{
	_ASSERTE(NULL != plModX);
	_ASSERTE(NULL != plModY);

	for (long lMod = lStartInd-1; lMod >= m_lModAnfInd && -1 == m_lSrcInd2; --lMod)
		for (long lSrc = m_lSrcAnfInd; lSrc <= m_lSrcEndInd; ++lSrc)
			if (plModX[lMod] == m_plSrcX[lSrc] &&
				plModY[lMod] == m_plSrcY[lSrc])
			{
				m_EndPkt2.X() = m_plSrcX[lSrc];
				m_EndPkt2.Y() = m_plSrcY[lSrc];
				m_lSrcInd2 = lSrc;
				m_lModInd2 = lMod;
				break;
			}

	if (-1 == m_lSrcInd2)
	{
		if (!bIsModClosed)
			return S_FALSE;	// für offenes zu modifizierendes Objekt keinen zweiten gemeinsamen
							//  Stützpunkt mit Quell-Objekt gefunden

		// bei geschlossenem zu modifizierenden Objekt noch weiter suchen
		for (long lMod = m_lModEndInd-1; lMod >= lStartInd && -1 == m_lSrcInd2; --lMod)
			for (long lSrc = m_lSrcAnfInd; lSrc <= m_lSrcEndInd; ++lSrc)
				if (plModX[lMod] == m_plSrcX[lSrc] &&
					plModY[lMod] == m_plSrcY[lSrc])
				{
					m_EndPkt2.X() = m_plSrcX[lSrc];
					m_EndPkt2.Y() = m_plSrcY[lSrc];
					m_lSrcInd2 = lSrc;
					m_lModInd2 = lMod;
					break;
				}
	}

	if (-1 == m_lSrcInd2)
		return S_FALSE;	// keinen zweiten gemeinsamen Stützpunkt mit Quell-Objekt gefunden

	return S_OK;	// zweiten gemeinsamer Stützpunkt gefunden

} // GetEndPoint2


// --------------------------------------------------------------------------------------------
// Für die erste Sondermarkierung den kürzesten Abschnitt ermitteln
void CCommonBorder::FindShortestSection (void)
{
KoOrd lLength1 = 0, lLength2 = 0;

	m_lSrcFromInd = min (m_lSrcInd1, m_lSrcInd2);
	m_lSrcToInd = max (m_lSrcInd1, m_lSrcInd2);

	for (long l = m_lSrcAnfInd; l < m_lSrcEndInd; ++l)
	{
		lLength1 += AbstandPktPktM (m_plSrcX[l], m_plSrcY[l], m_plSrcX[l+1], m_plSrcY[l+1]);
		if (m_lSrcFromInd <= l && l < m_lSrcToInd)
			lLength2 += AbstandPktPktM (m_plSrcX[l], m_plSrcY[l], m_plSrcX[l+1], m_plSrcY[l+1]);
	}

	if (lLength2 > lLength1/2.)
		swap (m_lSrcFromInd, m_lSrcToInd);
}


// --------------------------------------------------------------------------------------------
// Stützpunktmarkierungen des Quell-Objektes zwischen den Stützpunktindizes m_lSrcFromInd und
// m_lSrcToInd durch eine Sonderfarbe hervorheben
void CCommonBorder::InkMarker (void)
{
	if (m_lSrcFromInd <= m_lSrcToInd)
		for (long l = m_lSrcAnfInd; l <= m_lSrcEndInd; ++l)
		{
		Point BSPt = BSKoordinaten (m_plSrcX[l], m_plSrcY[l]);			

			if (l >= m_lSrcFromInd && l <= m_lSrcToInd)	// besonders gefärbte Markierung
			{
			Marker Mk = Marker (m_colInkFill, m_colBound, m_iBoundWidth, BSPt, m_iMarkGr);

	    		m_pVWnd->Draw (&Mk);
			}
			else									// "normale" Markierung
			{
			Marker Mk = Marker (m_colFill, m_colFill, 0, BSPt, m_iMarkGr);

	    		m_pVWnd->Draw (&Mk);
			}
		}
		
	else
		for (long l = m_lSrcAnfInd; l <= m_lSrcEndInd; ++l)
		{
		Point BSPt = BSKoordinaten (m_plSrcX[l], m_plSrcY[l]);			

			if (l >= m_lSrcFromInd || l <= m_lSrcToInd)	// besonders gefärbte Markierung
			{
			Marker Mk = Marker (m_colInkFill, m_colBound, m_iBoundWidth, BSPt, m_iMarkGr);

	    		m_pVWnd->Draw (&Mk);
			}
			else									// "normale" Markierung
			{
			Marker Mk = Marker (m_colFill, m_colFill, 0, BSPt, m_iMarkGr);

	    		m_pVWnd->Draw (&Mk);
			}
		}
} // InkMarker


// --------------------------------------------------------------------------------------------
// Linienabschnitt aller zu modifizierenden Objekte durch einen Linienabschnitt des
// Quell-Objektes ersetzen
HRESULT CCommonBorder::ReplaceLinePart (void)
{
short iModOT;		// Objekttyp und 
KoOrd* plModX;		//  Stützpunkte des
KoOrd* plModY;		//  aktuell bearbeiteten Objektes

long lModNextInd = -1;	// der nächste Stützpunktindex von wModObj nach dem Punkt (m_lRMX,m_lRMY)
long lModFromInd;	// Anfangs- und Endindex (gerichtet) des zu korrigierenden
long lModToInd;		//  Linienabschnittes
long lToSubCnt;		// Anzahl der Stützpunkte, die vor dem lModToInd-Stützpunkt gelöscht wurden

long lModAnfInd;	// 1. Index bzw.
long lModEndInd;	//  letzter Index der zu modifizierenden Kante bzw. -Kontur
short iModCInd;		// Index der Kontur, von der ein Abschnitt modifiziert werden soll
					//  (für Kante gilt: -1)

    COM_TRY
    {
	WUnknown Unk;

		for (m_wModObjs->Reset(); S_OK == m_wModObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wModObj (Unk);

			wModObj->GetObjTyp (&iModOT);
			if (OT_KANTE != iModOT && OT_FLAECHE != iModOT) continue;

			wModObj->GetX ((void**)&plModX);
			wModObj->GetY ((void**)&plModY);

			// Indizes für das aktuell zu modifizierende Objekt ermitteln
			THROW_FAILED_HRESULT (DetermineIndices (wModObj, plModX, plModY, iModOT, lModAnfInd,
								  lModEndInd, lModFromInd, lModToInd, lModNextInd, iModCInd));

			// Test, ob bei einer Fläche die entscheidenden Indizes auf der gleichen Kontur liegen
			if (OT_FLAECHE == iModOT &&		// zu modifizierendes Objekt ist eine Fläche
				!IsSameContour (lModAnfInd, lModEndInd, lModFromInd, lModToInd, lModNextInd))
					continue;	// nächstes zu modifizierendes Objekt

			// Löschen des zu modifizierenden Abschnitts
			THROW_FAILED_HRESULT (SubModifyPoints (wModObj, plModX, plModY, lModAnfInd,
										  lModEndInd, lModFromInd, lModToInd, iModCInd, lToSubCnt));

			// Hinzufügen des zu übernehmenden Abschnitts vor dem lModToInd-Punkt		
			THROW_FAILED_HRESULT (AddModifyPoints (wModObj, lModToInd, lToSubCnt, iModCInd));

			// modifiziertes Objekt abspeichern
			THROW_FAILED_HRESULT (StoreCommonBorder (wModObj));
		}
    }
    COM_CATCH;

	DrawScreenRectangle();	// Bereich neu zeichnen

	// über eine PostMessage wird CModifyObject mitgeteilt, dass das CCommonBorder-Objekt
	// wieder zerlegt werden kann
	PostMessage (__hWndM, WM_WM_OBJMODIFYEND, 0, 0);

	return S_OK;

} // ReplaceLinePart


// --------------------------------------------------------------------------------------------
// Für das das zu modifizierende Objekt pModObj Indizes ermitteln
//   lModAnfInd, lModEndInd: Anfangs- und Endindex der Flächenkontur
//   lModFromInd, lModToInd: (gerichtete) Von-Bis-Indizes des zu modifizierenden Linienabschnittes
//   lModNextInd:            der Index des Stützpunktes, der auf den Menü-Klick-Punkt folgt
//   iModCInd:               Index der Flächenkontur (bei Kante: -1)
HRESULT CCommonBorder::DetermineIndices (IObjektGeometrie* pModObj, KoOrd* plModX,
					   KoOrd* plModY, short iModOT, long& lModAnfInd, long& lModEndInd,
					   long& lModFromInd, long& lModToInd, long& lModNextInd, short& iModCInd)
{
long lInd1;	// Indizes (ohne Richtung) der beiden Endpunkte des zu ersetzenden
long lInd2;	//  Abschnittes bezgl. des aktuell bearbeiteten Objektes

	// bei dem 1. zu modifizierenden Objekt sind einige Indizes schon durch die bisher
	// abgearbeiteten Routinen ermittelt worden
	if (m_bFirstModObj)
	{
		lModNextInd = m_lModNextInd;
		iModCInd = m_iModCInd;
		lInd1 = m_lModInd1;
		lInd2 = m_lModInd2;
		lModAnfInd = m_lModAnfInd;
		lModEndInd = m_lModEndInd;

		m_bFirstModObj = false;
	}

	// ab dem 2. zu modifizierenden Objekt sind noch ein paar Indizes zu ermitteln
	else
	{
		_ASSERT(NULL != pModObj);
		_ASSERT(NULL != plModX);
		_ASSERT(NULL != plModY);

	long lModCnt;	// Gesamtanzahl der Stützpunkte

		pModObj->GetCnt (&lModCnt);

		lInd1 = -1;
		lInd2 = -1;

		// Indizes der beiden Endpunkte  ermitteln
		for (long l = 0; l < lModCnt; ++l)
		{
			if (plModX[l] == m_EndPkt1.X() &&
				plModY[l] == m_EndPkt1.Y())
				lInd1 = l;

			if (plModX[l] == m_EndPkt2.X() &&
				plModY[l] == m_EndPkt2.Y())
				lInd2 = l;

			if (lInd1 >= 0 && lInd2 >= 0)
				break;
		}

		// Index lModNextInd des nächsten Stützpunktes bzgl. des Punktes (m_lRMX,m_lRMY)
		RETURN_FAILED_HRESULT (pModObj->GetLineIndex (m_lRMX, m_lRMY, m_lCursEps, &lModNextInd));

		lModAnfInd = 0;				// 1. Index bzw.
		lModEndInd = lModCnt - 1;	//  letzter Index der zu modifizierenden Kante bzw. -Kontur
		iModCInd = -1;				// Index der Kontur, von der ein Abschnitt modifiziert werden
									//  soll (für Kante gilt: -1)

		if (OT_FLAECHE == iModOT)	// zu modifizierendes Objekt ist eine Fläche
		{
		short iModCCnt;		// Anzahl der Konturen
		long* plModCnt;		// Anzahl der Stützpunkte pro Kontur
	
			pModObj->GetLPCnt (&plModCnt);
			pModObj->GetKCnt (&iModCCnt);

		long lInd;			// Rückgabeparameter von Routine IndexTest(): werden hier
		IndPos IP;			//  nicht ausgewertet

			pModObj->IndexTest (lModNextInd, &iModCInd, &lInd, &IP);

			_ASSERTE(iModCInd < iModCCnt);

			for (int i = 0; i < iModCInd; ++i)
				lModAnfInd += plModCnt[i];

			lModEndInd = lModAnfInd + plModCnt[iModCInd] - 1;
		}
	}


	// Wenn lModNextInd mit einem Randindex übereinstimmt, ist bei Flächenkonturen der zu
	// modifizierende Abschnitt nicht eindeutig.
	if (OT_FLAECHE == iModOT &&	// zu modifizierendes Objekt ist eine Fläche
		(lModNextInd == lInd1 || lModNextInd == lInd2))
		(lModNextInd > lModAnfInd) ? (lModNextInd--) : (lModNextInd = lModEndInd - 1);

	// Anfangs- und Endindex (gerichtet) des zu korrigierenden Linienabschnittes ermitteln
	if (lInd1 <= lModNextInd && lModNextInd <= lInd2)
	{
		lModFromInd = lInd1;
		lModToInd = lInd2;
	}
	else if (lInd1 >= lModNextInd && lModNextInd >= lInd2)
	{
		lModFromInd = lInd2;
		lModToInd = lInd1;
	}
	else
	{
		lModFromInd = max (lInd1, lInd2);
		lModToInd = min (lInd1, lInd2);
	}

	return S_OK;

} // DetermineIndices


// --------------------------------------------------------------------------------------------
// Test, ob bei zu modifizierenden Flächenobjekten die beiden Endpunkte und der durch den
// Menüaufruf gegebene Punkt auf der gleichen Kontur liegen
bool CCommonBorder::IsSameContour (long lModAnfInd, long lModEndInd, long lInd1, long lInd2,
								   long lModNextInd)
{
	if (lModAnfInd <= lInd1 && lInd1 <= lModEndInd &&
		lModAnfInd <= lInd2 && lInd2 <= lModEndInd &&
		lModAnfInd <= lModNextInd && lModNextInd <= lModEndInd)
		return true;

ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
ResString resText (ResID (IDS_NOTSAMECONTOUR, pRF), 250);
    	
	MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
   	return false;	// die 3 Punkte gehören nicht alle zur gleichen Kontur

} // IsSameContour


// --------------------------------------------------------------------------------------------
// Löschen des zu modifizierenden Abschnitts
HRESULT CCommonBorder::SubModifyPoints (IObjektGeometrie* pModObj, KoOrd* plModX,
										KoOrd* plModY, long lModAnfInd, long lModEndInd,
										long lModFromInd, long lModToInd, short iModCInd, long& lToSubCnt)
{
	_ASSERTE(NULL != pModObj);
	_ASSERTE(NULL != plModX);
	_ASSERTE(NULL != plModY);

short iCInd;	// Rückgabeparameter von Routine SubPunkt(): wird hier nicht ausgewertet
long lSubCnt;	// Anzahl aller gelöschten Stützpunkte

	if (lModFromInd <= lModToInd)
	{
		BuildScreenRectangle1 (plModX, plModY, lModFromInd, lModToInd);
		lSubCnt = lToSubCnt = lModToInd - lModFromInd - 1;	// Löschen OHNE die beiden Randpunkte
		RETURN_FAILED_HRESULT (pModObj->SubPunkt (lSubCnt, lModFromInd+1, false, &iCInd));
	}

	else	// ist nur bei geschlossenen Objekten möglich
	{
	KoOrd lLockX = plModX[lModFromInd];	// Koordinaten des neuen "Konturschlosses"
	KoOrd lLockY = plModY[lModFromInd];

		BuildScreenRectangle1 (plModX, plModY, lModFromInd, lModEndInd);
		lSubCnt = lModEndInd - lModFromInd;	// Löschen OHNE den Anfangspunkt
		RETURN_FAILED_HRESULT (pModObj->SubPunkt (lSubCnt, lModFromInd+1, false, &iCInd));

		BuildScreenRectangle1 (plModX, plModY, lModAnfInd, lModToInd);
		lToSubCnt = lModToInd;					// Löschen OHNE den Endpunkt
		RETURN_FAILED_HRESULT (pModObj->SubPunkt (lToSubCnt, lModAnfInd, false, &iCInd));

		// "Konturschloss" bei lModFromInd-Punkt wieder vervollständigen
		RETURN_FAILED_HRESULT (pModObj->AddPunkt (lLockX, lLockY, lModAnfInd, iModCInd));
		lToSubCnt--;			// wegen AddPunkt()
	}

	return S_OK;

} // SubModifyPoints


// --------------------------------------------------------------------------------------------
// Hinzufügen des zu übernehmenden Abschnitts vor dem lModToInd-Punkt		
HRESULT CCommonBorder::AddModifyPoints (IObjektGeometrie* pModObj, long lModToInd, long lToSubCnt,
										short iModCInd)
{
	_ASSERTE(NULL != pModObj);
	
KoOrd* plModX; KoOrd* plModY;	// Stützpunkte

	pModObj->GetX ((void**)&plModX);	// wegen des Löschens nochmals
	pModObj->GetY ((void**)&plModY);	//  erforderlich
	lModToInd -= lToSubCnt;				// neuen lModToInd-Index ermitteln

	if (m_lSrcFromInd <= m_lSrcToInd)
	{
		// die beiden To-Punkte sind identisch
		if (plModX[lModToInd] == m_plSrcX[m_lSrcToInd] &&
			plModY[lModToInd] == m_plSrcY[m_lSrcToInd])
		{
			for (long l = m_lSrcToInd-1; l > m_lSrcFromInd; --l)
				RETURN_FAILED_HRESULT (InsertPoint (pModObj, l, lModToInd, iModCInd));
		}
		else
		{
			for (long l = m_lSrcFromInd+1; l < m_lSrcToInd; ++l)
				RETURN_FAILED_HRESULT (InsertPoint (pModObj, l, lModToInd, iModCInd));
		}
	}
	else	// Übernahme aus geschlossener Quell-Kante über "Konturschloss" hinweg
	{
		if (plModX[lModToInd] == m_plSrcX[m_lSrcToInd] &&
			plModY[lModToInd] == m_plSrcY[m_lSrcToInd])
		{
			for (long l = m_lSrcToInd-1; l >= m_lSrcAnfInd; --l)
				RETURN_FAILED_HRESULT (InsertPoint (pModObj, l, lModToInd, iModCInd));

				for (l = m_lSrcEndInd-1; l > m_lSrcFromInd; --l)
				RETURN_FAILED_HRESULT (InsertPoint (pModObj, l, lModToInd, iModCInd));
		}
		else
		{
			for (long l = m_lSrcFromInd+1; l < m_lSrcEndInd; ++l)
				RETURN_FAILED_HRESULT (InsertPoint (pModObj, l, lModToInd, iModCInd));

				for (l = m_lSrcAnfInd; l < m_lSrcToInd; ++l)
					RETURN_FAILED_HRESULT (InsertPoint (pModObj, l, lModToInd, iModCInd));
		}
	}

	return S_OK;

} // AddModifyPoints


// --------------------------------------------------------------------------------------------
// Einen neuen CommonBorder-Punkt aus dem Quell-Objekt zu dem zu modifizierenden Objekt
// hinzufügen.
HRESULT CCommonBorder::InsertPoint (IObjektGeometrie* pModObj, long l, long lModToInd,
									int iModCInd)
{
	_ASSERTE(NULL != pModObj);
	
	BuildScreenRectangle2 (m_plSrcX[l], m_plSrcY[l]);
	return pModObj->AddPunkt (m_plSrcX[l], m_plSrcY[l], lModToInd, iModCInd);
}


// --------------------------------------------------------------------------------------------
// ein modifiziertes Objekt abspeichern
HRESULT CCommonBorder::StoreCommonBorder (IObjektGeometrie* pModObj)
{
ulong ulIdent;

	pModObj->GetIdent (&ulIdent);

	if (0 == DEX_GetROModeIdent (ulIdent))	// Objektklasse nicht schreibgeschützt
		// OGModObject:     Geometrie des Objektes ersetzen
   		// OGAskWhenError:  im Fehlerfall wird Anwender vor dem Abspeichern noch einmal gefragt
   		// OGAddToView:     (evtl. veränderten) Identifikator zur Sicht hinzufügen
    	pModObj->SetFlags (OGModObject | OGAskWhenError | OGAddToView);
	else
    	// OGTempObject:	temporäres Objekt
    	pModObj->SetFlags (OGTempObject);

INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulIdent));	// Handle der Datenquelle

	return pModObj->GeometrieAnTRiASEx (hPr, true, NULL);

} // StoreCommonBorder


// --------------------------------------------------------------------------------------------
// Bildschirmausschnitt für Neuzeichnen mit den Koordinaten eines zu modifizierenden Objektes
// ermitteln
void CCommonBorder::BuildScreenRectangle1 (KoOrd* plModX, KoOrd* plModY, long lModFromInd,
										   long lModToInd)
{
	_ASSERTE(NULL != plModX);
	_ASSERTE(NULL != plModY);

	for (long l = lModFromInd; l <= lModToInd; ++l)
		BuildScreenRectangle2 (plModX[l], plModY[l]);

} // BuildScreenRectangle1


// --------------------------------------------------------------------------------------------
// Bildschirmausschnitt für Neuzeichnen mit den Koordinaten des Quell-Objektes ermitteln
void CCommonBorder::BuildScreenRectangle2 (KoOrd lX, KoOrd lY)
{
	if (lX < m_lXMin) m_lXMin = lX;
	if (lX > m_lXMax) m_lXMax = lX;
	if (lY < m_lYMin) m_lYMin = lY;
	if (lY > m_lYMax) m_lYMax = lY;

} // BuildScreenRectangle2


// --------------------------------------------------------------------------------------------
// Bildschirmausschnitt neu zeichnen
void CCommonBorder::DrawScreenRectangle (void)
{
Rectangle DrawRec;	// neu zu zeichnender Bildschirmausschnitt
Point PLO, PRU;		// linker oberer bzw. rechter unterer Eckpunkt des Bildschirmausschnitts

	PLO = BSKoordinaten (m_lXMin, m_lYMax);
	PRU = BSKoordinaten (m_lXMax, m_lYMin);
	DrawRec.Left() = PLO.X() - m_iMarkGr;	// zu bildendes Rechteck noch um die
	DrawRec.Top() = PLO.Y() + m_iMarkGr;	//  Größe des Markierungsquadrates vergrößern
	DrawRec.Right() = PRU.X() + m_iMarkGr;
	DrawRec.Bottom() = PRU.Y() - m_iMarkGr;

    DEX_RePaintRectWait (DrawRec);
	m_pVWnd->Update();		// sofort zeichnen

} // DrawScreenRectangle
