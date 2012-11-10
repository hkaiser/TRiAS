// Funktionen für Erweiterungs-DLL "Geometrie-Editierung"
// Modifizieren existierender Objekte
// File: GEOMODIF.CXX
// W. Mörtl


#include "geoeditp.hxx"

#include <hdrentrx.hxx>	// HeaderEntryX

#include <stdio.h>		// sprintf() für OutputDebugString
#include <limits.h>		// LONG_MAX
#include <defattr.h>	// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)

#include "strecke.hxx"	// LotPktStrecke
#include "spmoddlg.hxx"	// VertexModifyDlg

#include "geoeditr.h"	// IDS_LONGCLASSNAME

#include "SmartInterfaces.h"
#include <initguid.h>	// zum Linken von IID_* und CLSID_* erforderlich
#include "reinguid.h"	// CLSID_GeometrieBereinigung, IID_IExtendGeoRein
#include "operguid.h"	// CLSID_GeometrieOperationen, IID_IExtendObjOper

#include "geoedit.hxx"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



#ifdef WIN32
#define _DEBUG_HEAP
#if defined(_DEBUG_HEAP)
//debughilfe
#include <malloc.h>
bool HEAPCHECK (void)
{
int iStatus = _heapchk();

	if (iStatus != _HEAPOK) 
	{
		TX_ASSERT (iStatus == _HEAPOK);
		return false;	// hierauf den Breakpoint setzen; bei Fehler wird hier angehalten !!!!!
	}

return true;
}
#else
#define HEAPCHECK()
#endif
#else
#define HEAPCHECK()
#endif





//---------------------------------------------------------------------------------------------
// globale Konstanten
extern ResourceFile* pRF;
extern bool Mess;		// Flag für Ausgabe im DebugWindow (wird in InitExtension gesetzt)


//---------------------------------------------------------------------------------------------
extern "C"
{
	// Anzahl der plONrSel-Objekte ermitteln, die gleichzeitig ein aktiviertes (blinkendes)
	// Objekt sind, sowie die Objektnummer eines dieser aktivierten Objektes zurückgeben.
	// (Da eine sinnvolle Weiterverarbeitung nur dann erfolgt, wenn genau eins der aktivierten
	// Objekte auch ein plONrSel-Objekt ist, wird eben genau dessen Objektnummer zurückgegeben.)
	BOOL _GEOEDIT_EXPORT FAR PASCAL AnzahlAktObjekt (LONG hWnd, BOOL, void* pData)
	{
	long lONr = DEX_GetActiveObject (hWnd);	// Objektnummer eines aktivierten (blinkenden) Objektes
	long* plONrSel = ((MultiVtx*)pData)->plONrSel;
	short iIndSel = ((MultiVtx*)pData)->iIndSel;

		for (register short i = 0; i < iIndSel; i++)
			if (plONrSel[i] == lONr)
			{
				(((MultiVtx*)pData)->iAnz)++;
				((MultiVtx*)pData)->lAktObj = plONrSel[i];
			}
		return TRUE;
	}


	// Geometrie des lONr-Objektes in GeometrieBaum m_pGB eintragen
	BOOL _GEOEDIT_EXPORT FAR PASCAL ObjektInBaum (long lONr, BOOL, void*)
	{
		TX_ASSERT (lONr > 0);
		TX_ASSERT ((GeoEditExtension*)g_pTE != NULL);

		((GeoEditExtension*)g_pTE)->GeometrieInBaum (lONr);
		return TRUE;
	}

} // extern "C"



// ------------------------------------------------------------------------------------------------
// Stützpunkte aller selektierten, d. h. aller im GeometrieBaum befindlichen Objekte markieren
bool GeoEditExtension :: StuetzpunkteMarkieren (void)
{
	// es kann m_pGB == NULL gelten, wenn z.B. noch 1 Recherchefenster geöffnet ist, aber das
	// Projekt geschlossen werden soll; in DEX_PROJECTCLOSE wird DELETE (m_pGB) ausgeführt
	if (! m_pGB) return true;

bool bRet = true;
CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}

	IObjektGeometrie* pIOG = NULL;
	HRESULT hr = kl->GetIOG (&pIOG);

		if (SUCCEEDED(hr))
		{
		KoOrd lXmin, lXmax, lYmin, lYmax;

			pIOG->GetCont (&lXmin, &lXmax, &lYmin, &lYmax);

		Point PLU = BSKoordinaten (lXmin, lYmin);
		Point PRO = BSKoordinaten (lXmax, lYmax);

			// Objektcontainer hat mindestens einen Punkt mit dem Hintergrundsbereich gemeinsam
			if (!m_bHgrZeichnen1 ||	// Markierungen erstmalig zeichnen
				//  bzw. Markierungen im Hintergrundsbereich nachzeichnen
				(PLU.X() <= m_rcHintergrund.right && m_rcHintergrund.left <= PRO.X() &&
				PLU.Y() <= m_rcHintergrund.top && m_rcHintergrund.bottom <= PRO.Y()))
				bRet = MarkierungenBearbeiten (pIOG);
			if (pIOG) pIOG->Release();	// 14.4.97
		}
	}

	return bRet;
} // StuetzpunkteMarkieren


// -----------------------------------------------------------------------------------------------
// Stützpunkte des pIOG-Objektes durch Markierungen optisch sichtbar machen (bSetz == true) bzw. Löschen
bool GeoEditExtension :: MarkierungenBearbeiten (IObjektGeometrie* pIOG, bool bSetz)
{
CEierUhr Wait (MVWind());

	TX_ASSERT (pIOG);

short iMarkGr = GroesseMarkQuadrat ();
bool bRet = true;		// Rückgabewert dieser Routine
Marker* pMk = NULL;
long lAnz;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	for (long i = 0; i < lAnz; i++)
	{
	Point BSPt = BSKoordinaten (plXK [i], plYK [i]);
				
		if (bSetz)				// Markierung setzen
		{
			if (m_bHgrZeichnen1 &&	// Nachzeichnen des Hintergrundes
				(BSPt.X() < m_rcHintergrund.left || m_rcHintergrund.right < BSPt.X() ||
				BSPt.Y() < m_rcHintergrund.bottom || m_rcHintergrund.top < BSPt.Y()))
				continue;	// Markierung nicht im Hintergrundsbereich
			
		short iKontNr;	// für Routine IndexTest(); wird
		long lInd;		//  hier nicht ausgewertet
		IndPos IP = NICHTS;
		short iOT;

			pIOG->GetObjTyp (&iOT);

			if (iOT == OT_FLAECHE)
				pIOG->IndexTest (i, &iKontNr, &lInd, &IP);

			// Markierungsquadrates des 1. Stützpunktes (jeder Kontur) hervorheben (GW bzw. GW1
			// sind in edikonst.hxx definiert)
			if (i == 0 || (iOT == OT_FLAECHE && (IP == ERSTER || IP == LETZTER)))
				pMk = new Marker (BSPt, iMarkGr, GW1);
			else
				pMk = new Marker (BSPt, iMarkGr, GW);
	
			if (! pMk)
			{
				DEX_Error (RC_geomodif, EC_NOMEMORY);
				bRet = false;
				break;
			}
			MVWind()->Draw (pMk);
			DELETE (pMk);
		}

		else					// Markierung löschen
		{
		CoOrd hmg = iMarkGr/2 + 1;	// halbe Markergröße, "+ 1" ist eine Sicherheitszugabe
										//  für das Zeichnen
		Rectangle Rec (BSPt.Y()+hmg, BSPt.X()-hmg, BSPt.Y()-hmg, BSPt.X()+hmg);	// Markierungsquadrat mit Sicherheitszugabe

			DEX_RePaintRectWait (Rec);
		}
	}
	return bRet;
} // MarkierungenBearbeiten


// -----------------------------------------------------------------------------------------------
// Testen, ob Pt innerhalb eines Stützpunktes der selektierten Objekte liegt, dann Rückgabe von
// true, sonst false; der fortlaufende Index des pIOG-Objektes (d.h. ohne Berücksichtigung von
// Konturen) wird in lInd zurückgegeben
bool GeoEditExtension :: StuetzpunkteTesten (Point Pt, IObjektGeometrie** ppIOG, long& lInd)
{
	if (! m_pGB) return false;	// m_pGB wird bei DEX_PROJECTCLOSE gelöscht

Punkt Pkt = DBKoordinaten (Pt);

	MarkerInDBK (Pt);	// Markergröße in DB-Koordinaten

CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}
	
		if (*ppIOG) (*ppIOG)->Release();
		*ppIOG = NULL;

	HRESULT hr = kl->GetIOG (ppIOG);

		if (SUCCEEDED(hr) &&
			MarkierungenTesten (Pkt, *ppIOG, lInd))
			return true;
	}

	return false;
} // StuetzpunkteTesten


// -----------------------------------------------------------------------------------------------
// Testen, ob Pt innerhalb eines Stützpunktes der selektierten Objekte liegt (ausgenommen m_pIOG),
// dann Rückgabe von true, sonst false
bool GeoEditExtension :: StuetzpunkteTestenGrab (Point Pt)
{
	TX_ASSERT (m_pGB != NULL);

	if (! m_pGB) return false;

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Punkt Pkt = DBKoordinaten (Pt);

	MarkerInDBK (Pt);	// Markergröße in DB-Koordinaten

IObjektGeometrie* pIOGSave = NULL;	// Zwischenspeicher

CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}
	
	bool bRet = false;
	HRESULT hr = kl->GetIOG (&pIOGSave);

		if (SUCCEEDED(hr))
			bRet = MarkierungenTestenGrab (Pkt, pIOGSave);	// 14.4.97

		if (pIOGSave) pIOGSave->Release();	// AddRef() in GetIOG()

		if (bRet) return true;
	}

	return false;

} // StuetzpunkteTestenGrab


// -----------------------------------------------------------------------------------------------
// Testen, ob Pkt1 innerhalb eines Stützpunktes weiterer selektierter Objekte liegt (d.h.
// ausgenommen m_pIOG und evtl. Objekt, an das angegrabt werden soll), dann diesen nach Pkt2
// verschieben;
// Rückgabe von true, wenn wenigstens ein modifiziertes Objekt nach TRiAS gespeichert wird
bool GeoEditExtension :: WeitereObjekteTesten (Punkt& Pkt1, Punkt& Pkt2, Rectangle& Rec)
{
	TX_ASSERT (m_pGB);

	if (! m_pGB) return false;

bool bRet = false;	// Rückkehrwert dieser Routine
IObjektGeometrie* pIOGSave = NULL;	// Zwischenspeicher
CTable tab (*m_pGB);
long lONr1;	// Objektnummer von m_pIOG
long lONr2;	// Nummer des aktuell gelockten Objektes

	m_pIOG->GetONr (&lONr1);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}
	
	HRESULT hr = kl->GetIOG (&pIOGSave);

		pIOGSave->GetONr (&lONr2);
		if (FAILED(hr) ||
			lONr2 == lONr1 ||		// kein Test "bei sich selbst"
			lONr2 == m_lGrabONr)	// kein Test mit dem Objekt, an das angegrabt wurde
		{
			if (pIOGSave) pIOGSave->Release();	// AddRef() in GetIOG()	 14.4.97
			continue;
		}

	long lInd;	// Index von pIOGSave, bei dem evtl. Übereinstimmung mit Pkt vorliegt

		if (SUCCEEDED(hr) &&
			StuetzpunkteTesten2 (Pkt1, pIOGSave, lInd))
		{
		Rectangle Rec1;

			if (StuetzpunktVerschieben2 (Pkt2, pIOGSave, lInd, Rec1))	// modifiz. Geometrie abgespeichert
				bRet = true;
			Rec = Rec.Union(Rec1);
		}

		if (pIOGSave) pIOGSave->Release();	// 14.4.97
	}

	return bRet;
} // WeitereObjekteTesten


// ------------------------------------------------------------------------------------------------
// Testen, ob Pt (in BS-Koordinaten) innerhalb eines Stützpunkt-Markers, "in der Nähe" einer
// Strecke oder innerhalb eines der selektierten Objekte liegt mit Rückgabe der Cursorposition;
// der fortlaufende Index des pIOG-Objektes (d.h. bei Flächenobjekten ohne Berücksichtigung von
// Konturen) wird in lInd zurückgegeben
CursPosit GeoEditExtension :: CursorpositionGesamtTest (IObjektGeometrie** ppIOG, long& lInd)
{
	// es kann m_pGB == NULL gelten, wenn z.B. noch 1 Recherchefenster geöffnet ist, aber das
	// Projekt geschlossen werden soll; in DEX_PROJECTCLOSE wird DELETE (m_pGB) ausgeführt
	if (! m_pGB) return KEIN_BEZUG;

POINT PT;

#if defined(WIN32)
	if (! GetCursorPos (&PT))	// Funktion hat einen bool-Rückkehrwert
		TX_ASSERT (false);
#else
	GetCursorPos (&PT);			// Funktion hat keinen Rückkehrwert
#endif // WIN32

HWND hCtrl = MVWind()->Handle(API_WINDOW_HWND);
Rectangle CRc = MVWind()->CanvasRect();

	ScreenToClient (hCtrl, &PT);	// Bildschirmkoordinaten in Fensterkoordinaten konvertieren

Point Pt;

	Pt.X() = PT.x;
	// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
	// konform zu gehen !!!!!!!!!!!!
	Pt.Y() = CRc.Top() - CRc.Bottom() - 1 - PT.y;	// y-Koordinate drehen

// Umrechnung des Punktes, auf den der Cursor zeigt, von BS- in DB-Koordinaten
Punkt Pkt = DBKoordinaten (Pt);

	MarkerInDBK (Pt);

//	if (! m_pGB) return KEIN_BEZUG;		nach oben gerutscht

CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;		// kein Zugriff möglich
		}

		if (*ppIOG) (*ppIOG)->Release();
		*ppIOG = NULL;

	CursPosit CP = KEIN_BEZUG;
	HRESULT hr = kl->GetIOG (ppIOG);

		if (SUCCEEDED(hr))
			CP = CursorpositionTest (Pkt, *ppIOG, lInd);

		if (CP != KEIN_BEZUG)
			return CP;
	}

	return KEIN_BEZUG;
} // CursorpositionGesamtTest


// -----------------------------------------------------------------------------------------------
// es wird getestet, ob der durch die linke Maustaste angezeigte Punkt Pkt innerhalb eines
// Markierungsquadrates liegt, dann Rückgabe von true, sonst bzw. bei unzureichendem dynamischen
// Speicher false; der fortlaufende Index des pIOG-Objektes (d.h. bei Flächenobjekten ohne
// Berücksichtigung von Konturen) wird in lInd zurückgegeben
bool GeoEditExtension :: MarkierungenTesten (Punkt Pkt, IObjektGeometrie* pIOG, long& lInd)
{
	TX_ASSERT (pIOG);

short iMarkGr = GroesseMarkQuadrat ();
long lSPAnz;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lSPAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	for (long i = 0; i < lSPAnz; i++)
	{
	KoOrd x0 = plXK [i];
	KoOrd y0 = plYK [i];

		if (PunktInMarker (Pkt, x0, y0))
		{
		Point BSPt = BSKoordinaten (x0, y0);
		long lONr;

			pIOG->GetONr (&lONr);

			TX_ASSERT (lONr > 0 );

			DELETE (m_pMk);
			m_pMk = new Marker (BSPt, iMarkGr, GW, lONr);	// aktuellen Marker bestimmen
			if (! m_pMk)
			{
				DEX_Error (RC_geomodif, EC_NOMEMORY);
				return false;
			}
			m_pMk->ChangeRop (ROP_Invert);	// das von m_pMk überzeichnete Gebiet wird invertiert

			lInd = i;	// Index zurückgeben
			m_GrabPkt.X() = x0;
			m_GrabPkt.Y() = y0;
			return true;
		}
	}
	return false;
} // MarkierungenTesten


// -----------------------------------------------------------------------------------------------
// für das Graben bei Stützpunkt-Verschieben wird getestet, ob der durch die linke Maustaste
// angezeigte Punkt Pkt innerhalb eines Markierungsquadrates des pIOG-Objektes liegt; dann Rückgabe
// von true und Abspeicherung dieses Stützpunktes in m_GrabPkt
bool GeoEditExtension :: MarkierungenTestenGrab (Punkt& Pkt, IObjektGeometrie* pIOG)
{
	TX_ASSERT (pIOG);

long lONr1;		// Objektnummer von m_pIOG
long lONr2;		//  bzw. von pIOG
short iOT;

	m_pIOG->GetONr (&lONr1);
	pIOG->GetONr (&lONr2);
	m_pIOG->GetObjTyp (&iOT);

	if (lONr1 == lONr2 && iOT != OT_FLAECHE)
		return false;	// kein Test mit "sich selbst", ausgenommen bei einer Fläche

long lSPAnz;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lSPAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	m_lGrabONr = 0;		// Objektnummer des Objektes, an das angegrabt wird
	for (long i = 0; i < lSPAnz; i++)
		if (PunktInMarker (Pkt, plXK [i], plYK [i]))
		{
			// bei einer Fläche ist das Angraben an eine andere Kontur der gleichen Fläche
			// einmal möglich; deshalb Test, ob i und m_lInd zur gleichen Kontur gehören
			if (lONr1 == lONr2 && OT_FLAECHE == iOT)
			{
			short iKInd1 = -1;	// Index der Kontur, zu der m_lInd
			short iKInd2 = -1;	//  bzw. i gehört
			long lInd; 	// für Routine IndexTest(); wird
			IndPos IP;	//  hier nicht ausgewertet

				m_pIOG->IndexTest (m_lInd, &iKInd1, &lInd, &IP);
				m_pIOG->IndexTest (i, &iKInd2, &lInd, &IP);

				if (iKInd1 == iKInd2)
					return false;	// Angraben an die gleiche Kontur ist nicht erlaubt
			}

			m_GrabPkt.X() = plXK [i];
			m_GrabPkt.Y() = plYK [i];
			pIOG->GetONr (&m_lGrabONr);	// Objektnummer des Objektes, an das angegrabt wird
			return true;
		}

	return false;
} // MarkierungenTestenGrab


// -----------------------------------------------------------------------------------------------
// es wird getestet, ob der verschobene Punkt Pkt mit dem Stützpunkt eines weiteren markierten
// Objektes übereinstimmt, dann Rückgabe von true, sonst false;
// der fortlaufende Index des pIOG-Objektes (d.h. bei Flächenobjekten ohne Berücksichtigung von
// Konturen) wird in lInd zurückgegeben
bool GeoEditExtension :: StuetzpunkteTesten2 (Punkt& Pkt, IObjektGeometrie* pIOG, long& lInd)
{
	TX_ASSERT (pIOG);

long lSPAnz;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lSPAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	for (long i = 0; i < lSPAnz; i++)
		if (Pkt.X() == plXK[i] && Pkt.Y() == plYK[i])
		{
			lInd = i;	// Index zurückgeben
			return true;
		}

	return false;
} // StuetzpunkteTesten2


// -----------------------------------------------------------------------------------------------
// Größe eines Markers von BS- in Datenbankkoordinaten umrechnen
void GeoEditExtension :: MarkerInDBK (Point Pt)
{
short iMarkGr = GroesseMarkQuadrat ();
Point P1 (Pt.X() - iMarkGr/2, Pt.Y() + iMarkGr/2);	// linker oberer Eckpunkt bzw.
Point P2 (Pt.X() + iMarkGr/2, Pt.Y() - iMarkGr/2);	// rechter unterer Eckpunkt eines gedachten Markers um die
										
// aktuelle Cursorposition (in BS-Koordinaten)
Punkt PLO = DBKoordinaten (P1);	// dto. in DB-Koordinaten
Punkt PRU = DBKoordinaten (P2);

	m_lMBX = PRU.X() - PLO.X();	// Größe eines Markers (in DB-Koordinaten) in x- bzw.
	if (2 > m_lMBX) m_lMBX = 2; 
	m_lMBY = PLO.Y() - PRU.Y();	//  y-Richtung
	if (2 > m_lMBY) m_lMBY = 2; 
	m_lEpsilon = (m_lMBX + m_lMBY) / 6;
	if (1 > m_lEpsilon) m_lEpsilon = 1; 
} // MarkerInDBK


// -----------------------------------------------------------------------------------------------
// es wird getestet, ob der durch die linke Maustaste angezeigte Punkt Pkt (in DB-Koordinaten)
// innerhalb eines Stützpunkt-Markers oder "in der Nähe" einer Strecke liegt, dann Rückgabe von true,
// sonst bzw. bei unzureichendem dynamischen Speicher false;
// der fortlaufende Index des pIOG-Objektes (d.h. bei Flächenobjekten ohne Berücksichtigung von
// Konturen) wird in lInd zurückgegeben
CursPosit GeoEditExtension :: CursorpositionTest (Punkt& Pkt, IObjektGeometrie* pIOG, long& lInd)
{
	TX_ASSERT (pIOG);

	if (! pIOG)
		return KEIN_BEZUG;

long lONr, lSPAnz;
KoOrd* plXK; KoOrd* plYK;
	
	pIOG->GetONr (&lONr);
	pIOG->GetObjTyp (&m_iOT);
	pIOG->GetCnt (&lSPAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	lInd = -1;		// wenn kein echter Index ermittelt wird

	DELETE (m_pMarkObj);

	switch (m_iOT)
	{
		case OT_PUNKT:
			return CursorpositionTestPunkt (plXK, plYK, Pkt, lONr, lInd);

		case OT_KANTE:
			return CursorpositionTestKante (plXK, plYK, lSPAnz, Pkt, lONr, lInd);

		case OT_FLAECHE:
			return CursorpositionTestFlaeche (pIOG, plXK, plYK, lSPAnz, Pkt, lONr, lInd);

		default:
			break;	// alle anderen Typen (OT_TEXT, ...)
	}
	return KEIN_BEZUG;
} // CursorpositionTest


// -----------------------------------------------------------------------------------------------
// Hilfsroutine für CursorpositionTest()
CursPosit GeoEditExtension :: CursorpositionTestPunkt (KoOrd* plXK, KoOrd* plYK, Punkt& Pkt,
													 long lONr, long& lInd)
{
	TX_ASSERT (plXK);
	TX_ASSERT (plYK);

KoOrd x0 = plXK [0];
KoOrd y0 = plYK [0];

	m_pMarkObj = new Punkt (x0, y0);

	if (! m_pMarkObj)
	{
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		return KEIN_BEZUG;
	}

	if (PunktInMarker (Pkt, x0, y0))
	{
	short iMarkGr = GroesseMarkQuadrat ();
	Point BSPt = BSKoordinaten (x0, y0);

		lInd = 0;	// Index zurückgeben
		DELETE (m_pMk);
		m_pMk = new Marker (BSPt, iMarkGr, GW, lONr);	// aktuellen Marker bestimmen
		if (! m_pMk)
		{
			DEX_Error (RC_geomodif, EC_NOMEMORY);
			return KEIN_BEZUG;
		}
		m_pMk->ChangeRop (ROP_Invert);	// das von m_pMk überzeichnete Gebiet wird invertiert

#if defined(_DRAGDROP)
		return IN_OBJEKT;	// IN_PUNKT würde kein Kopieren ermöglichen
#else
		return IN_PUNKT;
#endif // _DRAGDROP
	}

	return KEIN_BEZUG;

} // CursorpositionTestPunkt


// -----------------------------------------------------------------------------------------------
// Hilfsroutine für CursorpositionTest()
CursPosit GeoEditExtension :: CursorpositionTestKante (KoOrd* plXK, KoOrd* plYK, long lSPAnz,
													 Punkt& Pkt, long lONr, long& lInd)
{
	TX_ASSERT (plXK);
	TX_ASSERT (plYK);

	m_pMarkObj = new Kante (plXK, plYK, lSPAnz);

	if (! m_pMarkObj)
	{
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		return KEIN_BEZUG;
	}

short iMarkGr = GroesseMarkQuadrat ();

	for (long i = 0; i < lSPAnz; i++)
	{
	KoOrd x0 = plXK [i];
	KoOrd y0 = plYK [i];

		if (PunktInMarker (Pkt, x0, y0))
		{
		Point BSPt = BSKoordinaten (x0, y0);

			lInd = i;	// Index zurückgeben
			DELETE (m_pMk);
			m_pMk = new Marker (BSPt, iMarkGr, GW, lONr);	// aktuellen Marker bestimmen
			if (! m_pMk)
			{
				DEX_Error (RC_geomodif, EC_NOMEMORY);
				return KEIN_BEZUG;
			}
			m_pMk->ChangeRop (ROP_Invert);	// das von m_pMk überzeichnete Gebiet wird invertiert
			return IN_PUNKT;
		}

		if (i == lSPAnz - 1)
			return KEIN_BEZUG;	// PunktAnStrecke-Test setzt noch mind. 2 Stützpunkte voraus

	KoOrd x1 = plXK [i+1];
	KoOrd y1 = plYK [i+1];
	KoOrd lAbst;	// Abstand des Punktes Pkt von Strecke (x1, y1, x2, y2) in Maximum-Norm
	bool bLot = PunktAnStrecke (Pkt, x0, y0, x1, y1, lAbst);

		if (bLot && lAbst >= m_lEpsilon && lAbst < 2*m_lEpsilon)
		{
			lInd = i + 1;	// Index zurückgeben
			return AUF_STRECKE;
		}

#if defined(_DRAGDROP)
		if (bLot && lAbst < m_lEpsilon)
			return IN_OBJEKT;
#endif // _DRAGDROP
	}

	return KEIN_BEZUG;

} // CursorpositionTestKante


// -----------------------------------------------------------------------------------------------
// Hilfsroutine für CursorpositionTest()
CursPosit GeoEditExtension :: CursorpositionTestFlaeche (IObjektGeometrie* pIOG, KoOrd* plXK,
									KoOrd* plYK, long lSPAnz, Punkt& Pkt, long lONr, long& lInd)
{
	TX_ASSERT (pIOG);
	TX_ASSERT (plXK);
	TX_ASSERT (plYK);

short iMarkGr = GroesseMarkQuadrat ();
long* plK;

	pIOG->GetLPCnt (&plK);

short j = 0;			// Konturindex
long lSumm = plK [0];	// Teilsumme der Stützpunktanzahlen der Konturen

//	for (long i = 0; i < lSPAnz-1; i++)
	for (long i = 0; i < lSPAnz; i++)	// 14.2.97
	{			
	KoOrd x0 = plXK [i];
	KoOrd y0 = plYK [i];

		if (PunktInMarker (Pkt, x0, y0))
		{
		Point BSPt = BSKoordinaten (x0, y0);

			lInd = i;	// Index zurückgeben
			DELETE (m_pMk);
			m_pMk = new Marker (BSPt, iMarkGr, GW, lONr);
			if (! m_pMk)
			{
				DEX_Error (RC_geomodif, EC_NOMEMORY);
				return KEIN_BEZUG;
			}
			m_pMk->ChangeRop (ROP_Invert);	// das von m_pMk überzeichnete Gebiet wird invertiert
			return IN_PUNKT;
		}

		if (0 == i) continue;	// Abfrage erforderlich, damit erst BEIDE Stützpunkte einer
								// Strecke getestet worden sind, bevor die Nähe zur Strecke
								// selbst getestet wird (24.1.97)

		// wenn sich gerade ein "Messer" für Flächenschnitt im Aufbau befindet, wird nur
		//  getestet, ob sich die Maus "in der Nähe" der Außenkontur befindet
//		if (NULL != m_pMesser && i >= plK[0]-2)
//		if (NULL != m_pMesser && i >= plK[0]-1)		// 14.2.97
		if (NULL != m_pMesser && i >= plK[0])		// 22.7.97
			return KEIN_BEZUG;

		// Strecke zwischen dem letzten Stützpunkt einer Kontur und dem 1. der nächsten Kontur
		// natürlich nicht testen
		if (i == lSumm)		// i steht auf dem Ende einer Kontur: siehe weiter oben (24.1.97)
		{
			j++;
			lSumm += plK [j];
			continue;		// nächstes i in der for-Schleife
		}

	KoOrd x1 = plXK [i-1];	// siehe weiter oben (24.1.97)
	KoOrd y1 = plYK [i-1];
	KoOrd lAbst;	// Abstand des Punktes Pkt von Strecke (x0, y0, x1, y1) in Maximum-Norm

		if (PunktAnStrecke (Pkt, x0, y0, x1, y1, lAbst) && lAbst < m_lEpsilon)
		{
			lInd = i;		// Index zurückgeben: siehe weiter oben (24.1.97)
			return AUF_STRECKE;
		}
	}

#if defined(_DRAGDROP)
// Test, ob sich Maus innerhalb der Außenkontur der Fläche befindet
short iKAnz;

	pIOG->GetKCnt (&iKAnz);

	m_pMarkObj = new Kante (plXK, plYK, plK[0]);

	if (! m_pMarkObj)
	{
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		return KEIN_BEZUG;
	}

Posit posLage = Pkt.Position ((Kante*)m_pMarkObj);

	if (posLage == INNERH)	// Pkt innerhalb der Außenkontur
		return IN_OBJEKT;
#endif // _DRAGDROP

	return KEIN_BEZUG;

} // CursorpositionTestFlaeche


// -----------------------------------------------------------------------------------------------
// der Punkt Pt, auf den die linke Maustaste zeigt, liegt in einem Markierungsquadrat pMk
// einschließlich dessen Rand (true), sonst false
bool GeoEditExtension :: PointInMarker (Point Pt, Marker* pMk)
{
	TX_ASSERT (pMk);

CoOrd xmin = pMk->RecPoint().X();
CoOrd xmax = pMk->RecPoint().X() + pMk->RecDim().Width();
CoOrd ymin = pMk->RecPoint().Y();
CoOrd ymax = pMk->RecPoint().Y() + pMk->RecDim().Height();

	return (xmin <= Pt.X() && Pt.X() <= xmax && ymin <= Pt.Y() && Pt.Y() <= ymax);
} // PointInMarker


// -----------------------------------------------------------------------------------------------
// der Punkt Pkt (in DB-Koordinaten), auf den die linke Maustaste zeigt, liegt in einem
// Markierungsquadrat (Kantenlänge in x- bzw. y-Richtung von m_lMBX bzw. m_lMBY) um den Punkt(XK, YK)
// einschließlich dessen Rand (true), sonst false
bool GeoEditExtension :: PunktInMarker (Punkt& Pkt, KoOrd XK, KoOrd YK)
{
KoOrd xmin = XK - m_lMBX/2;
KoOrd xmax = XK + m_lMBX/2;
KoOrd ymin = YK - m_lMBY/2;
KoOrd ymax = YK + m_lMBY/2;

	return (xmin <= Pkt.X() && Pkt.X() <= xmax && ymin <= Pkt.Y() && Pkt.Y() <= ymax);
} // PunktInMarker


// -----------------------------------------------------------------------------------------------
// Test, wo sich der Punkt Pkt (in DB-Koordinaten), auf den die linke Maustaste zeigt, bzgl. der
// Strecke (P1, P2) liegt; in lAbst wird der Abstand nach Maximum-Norm zurückgegeben; läßt sich
// von Pkt auf die Strecke das Lot fällen, wird true zurückgegeben, sonst false
// true, sonst false
bool GeoEditExtension :: PunktAnStrecke (Punkt& Pkt, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
										   KoOrd& lAbst)
{
Punkt LPkt;	// für Routine LotPktStrecke(): wird hier aber nicht ausgewertet

	return Strecke(x1, y1, x2, y2).LotPktStrecke (Pkt, lAbst, LPkt);
} // PunktAnStrecke


// -----------------------------------------------------------------------------------------------
// Verschieben eines Markierungsquadrates
void GeoEditExtension :: MoveMarker (Point Pt)
{
	TX_ASSERT (m_pMk);

	if (! m_pMk)
		return;
		
	MVWind()->Draw (m_pMk);// bisherige Position löschen (das allererste Mal wurde die Markierung
							// durch Routine MarkierungenBearbeiten() gezeichnet
	m_pMk->Process (Pt);	// neue Position einstellen
	MVWind()->Draw (m_pMk);// neue Position zeichnen

short iOT;

	m_pIOG->GetObjTyp (&iOT);

	if (iOT != OT_PUNKT)
		Banding (Pt);	// angrenzende Strecken als "Gummiband" mitziehen
} // MoveMarker


// -----------------------------------------------------------------------------------------------
// linke Maustaste wurde für Modifizierung einer vorhandenen Geometrie gedrückt
bool GeoEditExtension :: LeftMouseDownModify (Point Pt)
{
bool bRet = true;	// Rückkehrwert

	// aktuell wird ein "Messer" für Flächenteilung aufgebaut
	if (m_pMesser)
	{
	Punkt EPkt = DBKoordinaten (Pt);	// aktuell editierter Punkt in DB-Koordinaten

		TX_ASSERT (m_pFT);

		// Test, ob der soeben editierte "Messer"-Punkt EPkt innerhalb der zu zerschneidenten Fläche
		// m_pFT liegt, erfolgt nur mit der Außenkontur von m_pFT, da "Messer" durchaus durch eine
		// Insel hindurchgehen kann
		if (EPkt.Position (&((Masche*)m_pFT)->KA(0)) == INNERH)
		{
			if (m_pMesser->AddPunkt (EPkt.X(), EPkt.Y(), -1, -1) != S_OK)
				bRet = false;
			LRMouseButtonDn (Pt);
		}
		else
			// akustisches Signal, wenn Punkt außerhalb der zu teilenden Fläche liegt und damit
			// für das "Messer" nicht verwendet wird
			MessageBeep (MB_ICONEXCLAMATION);

		return bRet;
	}

	// aktuell wird ein Linienobjekt verlängert
	if (m_pVerlLin)
		return LeftMouseDownNew (Pt);
	
	// wurde beim Drücken der linken Maustaste kein	Marker oder keine Kante getroffen bzw.
	// befindet sich der Cursor nicht innerhalb eines selektierten (markierten) Objektes,
	// gilt dies wie "linke Maustaste nicht gedrückt"
	if (false == CursorUeberMarkObjekt (Pt))
	{
		_LeftButtonSem = false;
		bRet = false;
	}
	return bRet;
} // LeftMouseDownModify


// -----------------------------------------------------------------------------------------------
// linke Maustaste wurde für Modifizierung einer vorhandenen Geometrie gedrückt;
// Rückgabe von true, wenn sich Cursor innnerhalb eines Markers oder "in der Nähe" einer Strecke
// des selektierten (markierten) Objektes bzw. innerhalb des markierten Objektes befindet, sonst
// false
bool GeoEditExtension :: CursorUeberMarkObjekt (Point Pt)
{
	TX_ASSERT (m_pIOG != NULL);

	if (! m_pIOG) return false;

short iOT;

	m_pIOG->GetObjTyp (&iOT);

	switch (m_CurForm)
	{
		case STERN:		// Cursor befindet sich innerhalb eines Markers, d.h. Stützpunkt getroffen
						//  und Ctrl-Taste nicht gedrückt, d.h. Stützpunkt verschieben
		case TRENNER:	// Cursor befindet sich in der Nähe einer Strecke
			if (iOT != OT_PUNKT)
			{
			// Indizes des vorhergehenden bzw. nachfolgenden Stützpunktes vom zu verschiebenden
			// bzw. neu zu setztenden Stützpunkt ermitteln
			long lIndv = m_lInd - 1;	// führt bei Kante zu einem einkalkulierten Indexfehler
			long lIndn;

				if (m_CurForm == STERN)	// Stützpunkt verschieben
				{
					lIndn = m_lInd + 1;	// führt bei Kante zu einem einkalkulierten Indexfehler
					// ist m_pIOG eine Fläche, wird hier evtl. noch eine Korrektur an lIndv und/oder
					// lIndn vorgenommen
					if (iOT == OT_FLAECHE)
						m_pIOG->IndexVorNach (m_lInd, &lIndv, &lIndn);
				}
				else					// Stützpunkt neu setzen
				{
					lIndn = m_lInd;
					// ist m_pIOG eine Fläche, wird hier evtl. noch eine Korrektur an lIndv vorgenommen
					if (iOT == OT_FLAECHE)
						m_pIOG->IndexVor (m_lInd, &lIndv);	
				}

			// BS-Koordinaten des vorhergehenden bzw. nachfolgenden Punktes zum verschobenen bzw.
			// neu zu setzenden Punkt
			KoOrd* plXK; KoOrd* plYK;

				m_pIOG->GetX ((void**)&plXK);
				m_pIOG->GetY ((void**)&plYK);
				_PV = BSKoordinaten (plXK [lIndv], plYK [lIndv]);
				_PN = BSKoordinaten (plXK [lIndn], plYK [lIndn]);

			bool bVor = true;		// es gibt einen vorhergehenden Punkt
			bool bNach = true;		// es gibt einen nachfolgenden Punkt
			long lSPA;

				m_pIOG->GetCnt (&lSPA);
				if (iOT == OT_KANTE)	// Sonderfall am Kantenende
				{
					if (m_lInd == 0) bVor = false;	// 1. Stützpunkt
					if (m_lInd == lSPA-1 &&			// letzter Stützpunkt und
						m_CurForm == STERN)			//  Stützpunkt verschieben
						bNach = false;				// dann nur "halbes" Banding
				}

				BandingStart (bVor, bNach);		// Start für Mitziehen der anliegenden Strecken
			}
	
			MVWind()->MouseTrap (On);	// Maus einfangen
			return true;


		case KREUZ:		// Cursor befindet sich innerhalb eines Markers, d.h. Stützpunkt getroffen
						//  und Ctrl-Taste gedrückt, d.h. Stützpunkt soll gelöscht werden
			return true;


		case INOBJEKT:	// Cursor befindet sich innerhalb eines selektierten (markierten) Objektes
			m_StartPt = Pt;		// Startpunkt retten
			return true;

		default:		// Cursor befindet sich weder auf Marker noch in der Nähe einer Strecke
			return false;
	}
} // CursorUeberMarkObjekt


// -----------------------------------------------------------------------------------------------
// linke Maustaste wurde für Modifizierung einer vorhandenen Geometrie losgelassen
void GeoEditExtension :: LeftMouseUpModify (Point Pt)
{
	// Während der Modifizierung (Verschieben, Löschen bzw. Neusetzen) eines Stützpunktes (einschl.
	// Geometrietest und Neuzeichnen) sollen keine WM_MOUSEMOVE-Messages empfangen werden
	UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);		// kein Interesse an Mausbewegung

	// Maus freigeben, wodurch die Maus-Messages nicht empfangen werden, wenn sich der
	// Cursor außerhalb des Anwendungsbereiches (d.h. über einem anderen Fenster) befindet
	MVWind()->MouseTrap (Off);

short iOT;

	m_pIOG->GetObjTyp (&iOT);

	switch (m_CurForm)
	{
		case STERN:
			// "Gummiband" beenden, d.h. DELETE von _DRO1 und _DRO2 aus BandingStart()
			if (iOT != OT_PUNKT)
				BandingStop ();
			StuetzpunktVerschieben();
			break;

		case TRENNER:
			if (iOT != OT_PUNKT)
				BandingStop ();		// "Gummiband" beenden
			StuetzpunktHinzufuegen (Pt);
			break;

		case KREUZ:
			StuetzpunktLoeschen();
			break;

		case FANGEN:
			if (m_CurFormOld == STERN)
			{
				if (iOT != OT_PUNKT)
					BandingStop ();
				StuetzpunktVerschieben ();
			}

			if (m_CurFormOld == TRENNER)
			{
				if (iOT != OT_PUNKT)
					BandingStop ();
				StuetzpunktHinzufuegen (Pt);
			}
			break;
	}
	RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir, ob Maus bewegt wurde?

	CursorWechselMod();
} // LeftMouseUpModify


// -----------------------------------------------------------------------------------------------
// rechte Maustaste wurde für Modifizierung einer vorhandenen Geometrie gedrückt
bool GeoEditExtension :: RightMouseDownModify (void)
{
	// aktuell wird ein "Messer" für Flächenteilung aufgebaut
	if (m_pMesser)
	{
		TX_ASSERT (m_pFT);

		// wenn Cursor STERN- oder TRENNER-Form hat, gilt der gesetzte Punkt immer als
		// innerhalb der zu teilenden Fläche liegend, da der Cursor nicht umgestellt wird, falls
		// er "in die Nähe" einer Innenkontur gerät
		if (m_CurForm == STERN || m_CurForm == TRENNER)
			return true;

	Punkt EPkt = DBKoordinaten (_ptRM);	// aktuell editierter Punkt in DB-Koordinaten

		// Test erfolgt nur mit der Außenkontur von m_pFT
		if (INNERH != EPkt.Position (&((Masche*)m_pFT)->KA(0)))
		{
			// akustisches Signal, wenn Punkt außerhalb der zu teilenden Fläche liegt und damit
			// für das "Messer" nicht verwendet wird
			MessageBeep (MB_ICONEXCLAMATION);

			// dieser Fall ist gleichbedeutend mit "rechte Maustaste nicht gedrückt"
			_RightButtonSem = false;
			return false;
		}
	}

	return true;
} // RightMouseDownModify


// -----------------------------------------------------------------------------------------------
// rechte Maustaste wurde für Modifizierung einer vorhandenen Geometrie losgelassen
bool GeoEditExtension :: RightMouseUpModify (Point Pt)
{
	MVWind()->MouseTrap (Off);	// Maus freigeben (Erläuterung s. geoedit.cxx)

	if (!m_pVerlLin && !m_pMesser)
	{
		if (! EindeutigesObjekt()) return false; 

	// y-Koordinate zurückdrehen, da für Anzeige des Menüs Windows(???)-Koordinaten
	// benötigt werden; außerdem die Markerbreite als "Zugabe" hinzufügen
	Point Pnt;
	Rectangle CRc = MVWind()->CanvasRect();

		Pnt.X() = Pt.X();
		// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
		// konform zu gehen !!!!!!!!!!!!
		Pnt.Y() = CRc.Top() - CRc.Bottom() - 1 - Pt.Y();

	short iOT;

		m_pIOG->GetObjTyp (&iOT);

		switch (iOT)
		{
			case OT_PUNKT:
			{
//			int iPixX, iPixY;	// Größe eines Punktsymbols in BS-Pixel

//				if (PunktSymbolGroesse (m_pIOG, iPixX, iPixY))
//				{
//					Pnt.X() = Pt.X() - iPixX/2;	// halbe Symbolhöhe noch abziehen, damit Menü
//					Pnt.Y() += iPixY/2;			//  am linken unteren Symbolpunkt ansetzt
//				}
				ObjectModifyMenu (MWind(), Pnt, IDR_MODMENUE1);
				break;
			}

			case OT_KANTE:
//			{
//			short iMarkGr = GroesseMarkQuadrat ();

//				Pnt.X() = Pt.X() + iMarkGr;
				ObjectModifyMenu (MWind(), Pnt, IDR_MODMENUE2);
				break;
//			}

			case OT_FLAECHE:
//			{
//			short iMarkGr = GroesseMarkQuadrat ();

//				Pnt.X() = Pt.X() + iMarkGr;
				ObjectModifyMenu (MWind(), Pnt, IDR_MODMENUE3);
				break;
//			}
		}
	}
	else
	{
		if (m_pVerlLin)
			RightMouseUpNew (Pt);

		if (m_pMesser)
			FlaechenteilungsDialog ();
	}

	m_bHgrZeichnen2 = true;
	MVWind()->Update();		// Hintergrund nach Zerlegen des Menüs sofort zeichnen, um z.B.
	m_bHgrZeichnen2 = false;	//  dem Zeichnen des "Messers" zuvorzukommen

	// bei Click mit der linken Maustaste neben das Menü würde ohne nachfolgende Cursorumstellung
	// der aktuelle Stützpunkt verschoben werden; durch die Umstellung auf den PFEIL-Cursor
	// bewirkt der besagte Click nichts
	NeuerCursor ();

	return true;
} // RightMouseUpModify


// -----------------------------------------------------------------------------------------------
// Zuordnung eines Menüs oder Dialogs, das durch den rechte-Maus-Klick erzeugte wird, ist
// trotzdem eindeutig, auch wenn Cursor auf einen Stützpunkt zeigt, der zu mehreren selektierten
// Objekten gehört (Rückgabe: true), sonst false; evtl. werden m_pIOG und m_lInd modifiziert
bool GeoEditExtension :: EindeutigesObjekt (void)
{
	if (! m_pIOG || m_lInd < 0)
		return true;	// keine Zuordnung zu einem selektierten Objekt

// Zeigt Cursor auf einen Stützpunkt, der zu mehreren selektierten (markierten) Objekten
// gehört?
short iAnzSel = (short) m_pGB->Count();	// Anzahl der selektierten Objekte

	if (1 == iAnzSel) return true;			// hier ist nichts weiter zu klären

long* plONrSel = new long [iAnzSel];		// Objektnummern der Objekte, die den Stützpunkt
											//  besitzen, auf den der Cursor zeigt
	if (! plONrSel)
	{
    	DEX_Error (RC_geomodif, EC_NOMEMORY);
		return false;
	}

short iIndSel = 0;	// laufender Index von plONrSel
long lSPAnz;		// Gesamtstützpunktanzahl von m_pIOG
KoOrd* plXK; KoOrd* plYK;

	m_pIOG->GetCnt (&lSPAnz);

//	TX_ASSERT (m_lInd >= lSPAnz);	was soll das? 25.03.97
	if (m_lInd >= lSPAnz) return true;

	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);

KoOrd xC = plXK[m_lInd], yC = plYK[m_lInd];	// Koordinaten des Stützpunktes, auf den Cursor zeigt
Punkt Pkt (xC, yC);	// für MarkierungenTesten() erforderlich
long lInd;			// für MarkierungenTesten() erforderlich; wird hier nicht weiter ausgewertet

CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}

	IObjektGeometrie* pIOG = NULL;
	HRESULT hr = kl->GetIOG (&pIOG);

		if (SUCCEEDED(hr) &&
			MarkierungenTesten (Pkt, pIOG, lInd))
		{
		long lONr;

			pIOG->GetONr (&lONr);
			plONrSel [iIndSel] = lONr;
			iIndSel++;
		}
		if (pIOG) pIOG->Release();
	}

	if (1 == iIndSel)
	{
		DELETE_VEC (plONrSel);
		return true;	// Stützpunkt gehört zu genau einem selektierten Objekt
	}
	
// Ist genau eines der betroffenen Objekte ein aktiviertes (blinkendes) Objekt?
struct MultiVtx Dat;	// in edikonst.hxx definiert

	Dat.plONrSel = plONrSel;
	Dat.iIndSel = iIndSel;
	Dat.iAnz = 0;		// Anzahl der plONrSel-Objekte, die gleichzeitig ein aktiviertes
						// (blinkendes) Objekt sind
	Dat.lAktObj = -1;	// Objektnummer eines dieser aktivierten Objekte

ENUMNOKEYLONG ENKL;

	memset (&ENKL, '\0', sizeof (ENUMNOKEYLONG));
	ENKL.eFcn = (ENUMNOKEYLONGPROC) AnzahlAktObjekt;
	ENKL.ePtr = (void*) &Dat;
	DEX_EnumORWindows (ENKL);

	DELETE_VEC (plONrSel);

	if (Dat.iAnz != 1)
	{
	ResString Text1 (ResID (IDS_AKTOBJEKT, pRF), 250);
	ResString Text2 (ResID (IDS_LONGCLASSNAME, pRF), 50);

		MessageBox (hWnd(), Text1.Addr(), Text2.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return false;	// nicht genau eines der betroffenen Objekte ein aktiviertes Objekt 
	}

// Ist m_pIOG dieses aktivierte Objekt?
long lONr;					// Objektnummer von m_pIOG
long lAktObj = Dat.lAktObj;	// Objektnummer des aktivierten Objektes

	m_pIOG->GetONr (&lONr);
	if (lONr == lAktObj) return true;	// ja

// m_pIOG und m_lInd mit den Parametern dieses aktivierten Objektes modifizieren

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}
	
		if (m_pIOG) m_pIOG->Release();
		m_pIOG = NULL;

	HRESULT hr = kl->GetIOG (&m_pIOG);

		if (SUCCEEDED(hr))
		{
		long lON;

			m_pIOG->GetONr (&lON);
			if (lON == lAktObj) break;
		}
	}

// m_lInd neu bestimmen
long lSPA;	// Gesamtstützpunktanzahl des neuen m_pIOG

	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);
	m_pIOG->GetCnt (&lSPA);

	for (long l = 0; l < lSPA; l++)
		if (plXK[l] == xC && plYK[l] == yC)
			m_lInd = l;

	return true;
} // EindeutigesObjekt


// -----------------------------------------------------------------------------------------------
// Cursor bei Mausbewegung entsprechend der Bildschirmposition wechseln. Cursorposition
// - auf einem markierten Stützpunkt: Cursor bekommt STERN-Form
// - ist zusätzlich die CTRL-Taste gedrückt: Cursor bekommt KREUZ-Form
// - "in der Nähe" einer Strecke: Cursor bekommt TRENNER-Form
// - innerhalb eines Objektes: Cursor bekommt INNERHALB-Form
// - weder/noch: Cursor bekommt PFEIL-Form.
void GeoEditExtension :: CursorWechselMod (void)
{
	if (0 == DEX_ActiveObjectsCount())	// kein Recherchefenster geöffnet
		return;

CursPosit CP = CursorpositionGesamtTest (&m_pIOG, m_lInd);

	switch (CP)
	{
		case IN_PUNKT:							// Cursor in einem Marker 
			if (GetKeyState (VK_CONTROL) < 0)	//    CTRL-Taste gedrückt
			{
			short iOT;

				m_pIOG->GetObjTyp (&iOT);
//				if (KREUZ != m_CurForm)		//			noch nicht die KREUZ-Form	27.02.97
				{
					NeuerCursor (KREUZ, m_KreuzCursor);
					RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);		// sage mir, ob l.M-down?
					UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// kein Interesse an r.M-down
				}
			}
			else								//    CTRL-Taste nicht gedrückt
			{
//				if (STERN != m_CurForm)			//      noch nicht die STERN-Form	27.02.97
				{
					NeuerCursor (STERN, m_SternCursor);
					RegisterNotificationM (WM_KEYDOWN, false, _KD);			// sage mir, ob Tastatur-down?
					RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);		// sage mir, ob l.M-down?
					RegisterNotificationM (WM_RBUTTONDOWN, false, _RD);		// sage mir, ob r.M-down?
				}
			}
			return;


		case AUF_STRECKE:						// Cursor in der Nähe einer Strecke
//			if (TRENNER != m_CurForm)			//    noch nicht TRENNER-Form	27.02.97
			{
				NeuerCursor (TRENNER, m_TrennCursor);
				RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);		// sage mir, ob l.M-down?
				RegisterNotificationM (WM_RBUTTONDOWN, false, _RD);		// sage mir, ob r.M-down?
			}
			return;

		case IN_OBJEKT:							// Cursor innerhalb eines selektierten (markierten) Objektes
#if defined(_DRAGDROP)
//			if (INOBJEKT != m_CurForm)			//  noch nicht INOBJEKT-Form	27.02.97
			{
				NeuerCursor (INOBJEKT, m_InnerhCursor);
				RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);		// sage mir, ob l.M-down?
				RegisterNotificationM (WM_RBUTTONDOWN, false, _RD);		// sage mir, ob r.M-down?
			}
#endif // _DRAGDROP
			return;

		case KEIN_BEZUG:						// Cursor weder in einem Marker noch in der Nähe einer Strecke
//			if (PFEIL != m_CurForm)				//    noch nicht PFEIL-Form		27.02.97
			{
				NeuerCursor ();
				if (m_pVerlLin || m_pMesser)
					RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);		// sage mir, ob l.M-down?
				else
					UnRegisterNotificationM (WM_LBUTTONDOWN, false, _LD);	// kein Interesse an l.M-down
			}
			return;
	}
} // CursorWechselMod


// -----------------------------------------------------------------------------------------------
// Cursor bei Stützpunkt-Modifikation zum Angraben entsprechend der Bildschirmposition wechseln.
// Steht der Cursor auf einem markierten Stützpunkt, muß er die FANGEN-Form haben, ansonsten hat er
// die vorhergehende Form CurForm STERN bzw. TRENNER.
void GeoEditExtension :: CursorWechselModGrab (Point Pt, Curs CurForm, Pointer* pCursor)
{
	if (0 == DEX_ActiveObjectsCount())	// kein Recherchefenster geöffnet
		return;

	if (StuetzpunkteTestenGrab (Pt))	// Cursor im Marker eines anderen selektierten (markierten) Objektes
	{
	bool bShift = GetKeyState (VK_SHIFT) < 0;	// SHIFT-Taste nicht/gedrückt (false/true)

		RegisterNotificationM (WM_KEYDOWN, false, _KD);		// sage mir, ob Tastatur-down?

		if (m_CurForm != FANGEN &&	// noch nicht FANGEN-Form		doch nicht 27.02.97
			bShift == false)		// SHIFT-Taste nicht gedrückt
		{
			NeuerCursor (FANGEN, m_FangCursor);
			return;
		}
		if (m_CurForm == FANGEN &&	// schon FANGEN-Form			doch nicht 27.02.97
			bShift)					// SHIFT-Taste gedrückt
			NeuerCursor (CurForm, pCursor);
		return;
	}

	// Cursor nicht in einem Marker
//	if (m_CurForm != CurForm)			// noch nicht die vorhergehende Form	27.02.97
		NeuerCursor (CurForm, pCursor);
} // CursorWechselModGrab


// -----------------------------------------------------------------------------------------------
// rechte Maustaste bei Editierung eines "Messers" für Flächenteilung liefert Dialog
bool GeoEditExtension :: FlaechenteilungsDialog (void)
{
	TX_ASSERT (m_pMesser);

	if (! m_pMesser) return false;

long lSPA;

	m_pMesser->GetCnt (&lSPA);

VertexModifyDlg* pVMDlg = new VertexModifyDlg (MVWind(), m_pMesser, lSPA-1);
		
	if (! pVMDlg)
	{                                                                      
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		return false;
	}

// DialogCaption modifizieren
ResString Capt (ResID (IDS_FLTEILEN, pRF), 40);

	pVMDlg->SetCaption (Capt.Addr());


	// Modifikation vor Abschluß der "Messer-Bildung"
	if (m_CurForm == PFEIL)
	{
	ResString Text (ResID (IDS_BUTTONTEXT2, pRF), 20);

		pVMDlg->SetAbschlussButtonText (Text.Addr());	// Abschluß-Button wird zum Fortsetzen-Button

	Punkt EPkt = DBKoordinaten (_ptRM);	// letzten editierter Punkt in DB-Koordinaten

		if (m_pMesser->AddPunkt (EPkt.X(), EPkt.Y(), -1, -1) != S_OK)	// letzten editierten Punkt hinzufügen
			return false;
	}

	// Modifikation nach Beendigung der "Messer-Bildung"
	if (m_CurForm == STERN || m_CurForm == TRENNER)
	{
	ResString Text (ResID (IDS_BUTTONTEXT1, pRF), 20);

		pVMDlg->SetAbschlussButtonText (Text.Addr());	// Abschluß-Button wird zum Teilen-Button

	Punkt EPkt = PunktAufKontur (_ptRM);

		if (m_pMesser->AddPunkt (EPkt.X(), EPkt.Y(), -1, -1) != S_OK)	// Lotpunkt vom letzten editierten Punkt hinzufügen
			return false;
	}

ObjContainer OC;	// Containers von m_pIOG

	m_pMesser->GetCont (&OC.XMin(), &OC.XMax(), &OC.YMin(), &OC.YMax());

Point Pt = DialogPosit (&OC, pVMDlg->GetSize());

	pVMDlg->ChangePosition (Pt);

	pVMDlg->Show ();						
	
AktNeu Erg = (AktNeu) pVMDlg->Result (); // Rückgabewert der Aktion im pVMDlg-DialogFenster
										     
	switch (Erg)
	{                                                                                     
		case BEENDEN:
			// Bezug zur Erweiterung "Objektoperationen" herstellen, wenn noch m_bObjOper == false
			if (! m_bObjOper)
			{
			HRESULT hr = 0;

				if (m_pXtnSite)
					hr = m_pXtnSite->GetXtension (CLSID_GeometrieOperationen, IID_IExtendObjOper,
												    (LPVOID*)&m_pIObjOper);

				if (FAILED (hr) ||	// Fehler, z.B. objoper.ext nicht verfügbar
					! m_pXtnSite)
				{
				ResString Text1 (ResID (IDS_NOOBJOPER, pRF), 250);
				ResString Text2 (ResID (IDS_LONGCLASSNAME, pRF), 50);

					MessageBox (hWnd(), Text1.Addr(), Text2.Addr(), MB_ICONEXCLAMATION | MB_OK);
					break;
				}
				m_bObjOper = true;
			}

			FlaecheTeilen ();
			break;
			
		case VERWERFEN:
			BereichZeichnen (m_pMesser);	// Linienzug des "Messers" (für Teilung von
											//  Flächenobjekten) wieder löschen
			if (m_pMesser)
			{
				m_pMesser->Release();	// Objekt (Kante) für Teilung von Flächenobjekten
				m_pMesser = NULL;
			}
			DELETE (m_pFT);			// zu teilende Fläche
			break;
				
		case FORTSETZEN:	// entspr. inhaltlich dem "linke Maustaste gedrückt"
		{
		long lSPA;	// bisherige "Messer"-Länge
		KoOrd* plXK; KoOrd* plYK;

			m_pMesser->GetCnt (&lSPA);
			m_pMesser->GetX ((void**)&plXK);
			m_pMesser->GetY ((void**)&plYK);

		KoOrd x = plXK [lSPA-1];	// letzter Stützpunkt
		KoOrd y = plYK [lSPA-1];	//  des "Messers"
		Point Pt = BSKoordinaten (x, y);

			if (Pt.X() > 0) Pt.X()--;	// wegen Fehler bei Hartmut notwendig
			if (Pt.Y() > 0) Pt.Y()--;	// eine Korrektur bei ihm hätte zu große Folgen an anderen Stellen
			LRMouseButtonDn (Pt);
		}
			break;
	}

	DELETE (pVMDlg);

	return true;
} // FlaechenteilungsDialog


// -----------------------------------------------------------------------------------------------
// Stützpunkt verschieben
void GeoEditExtension :: StuetzpunktVerschieben (void)
{
	TX_ASSERT (m_pIOG != NULL);
	TX_ASSERT (m_pMk != NULL);

	if (!m_pIOG || !m_pMk) return;

CEierUhr Wait (MVWind());	// Verschieben, Test, Zeichnen ... kann länger dauern

Point newPt = m_pMk->GetMPoint();	// Mittelpunkt des Markierungsquadrates = neuer Stützpunkt

// Objektgeometrie korrigieren
Punkt Pkt = NeuerPunktMitGrab (newPt);	// DB-Koordinaten des neuen Stützpunktes (mit Grab-Funktion)
KoOrd* plXK; KoOrd* plYK;

	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);

// alte Koordinaten des zu verschiebenden Punktes retten
Punkt ModPkt;

	ModPkt.X() = plXK [m_lInd];
	ModPkt.Y() = plYK [m_lInd];

	m_pIOG->ModPunkt (Pkt.X(), Pkt.Y(), m_lInd);	// Punkt in m_pIOG modifizieren

Rectangle Rec1, Rec2;	// Bereiche für Neuzeichnen nach Geometrie-Modifikation

#if defined(WIN32)	// Undo für WIN32
bool bRet1 = ModObjSpeicherung (m_pIOG, ModPkt, m_lInd, VORRUECK, Rec1);

	// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Verschiebung rückgängig machen
	if (! bRet1)
		m_pIOG->ModPunkt (ModPkt.X(), ModPkt.Y(), m_lInd);

	// Test, ob es noch weitere markierte Objekte mit dem alten Stützpunkt ModPkt gibt, damit dieser
	// Stützpunkt auch nach Pkt verschoben werden kann
	Rec2 = Rec1;	// für den Fall, daß keine weiteren markierten Objekte existieren

bool bRet2 = WeitereObjekteTesten (ModPkt, Pkt, Rec2);

	// Ausschnitt nach Geometrie-Modifikation neu zeichnen
	DEX_RePaintRectWait (Rec1.Union(Rec2));
	
#else

	// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Verschiebung rückgängig machen
	if (ModObjSpeicherung (m_pIOG, ModPkt, m_lInd, VORRUECK, Rec1) == false)
		m_pIOG->ModPunkt (ModPkt.X(), ModPkt.Y(), m_lInd);

	// Test, ob es noch weitere markierte Objekte mit dem alten Stützpunkt ModPkt gibt, damit dieser
	// Stützpunkt auch nach Pkt verschoben werden kann
	Rec2 = Rec1;	// für den Fall, daß keine weiteren markierten Objekte existieren
	WeitereObjekteTesten (ModPkt, Pkt, Rec2);

// Ausschnitt nach Geometrie-Modifikation neu zeichnen
Rectangle Rec = Rec1.Union(Rec2);

	DEX_RePaintRectWait (Rec);
	
#endif // WIN32

	MVWind()->Update();		// sofort zeichnen
} // StuetzpunktVerschieben


// -----------------------------------------------------------------------------------------------
// koordinatengleichen Stützpunkt eines weiteren markierten Objektes verschieben;
// Rückgabe von true, wenn Einspeicherung der modifizierten Objektgeometrie in TRiAS erfolgt ist
bool GeoEditExtension :: StuetzpunktVerschieben2 (Punkt& Pkt, IObjektGeometrie* pIOG, long lInd,
												  Rectangle& Rec)
{
	TX_ASSERT (pIOG != NULL);

	if (! pIOG) return false;

CEierUhr Wait (MVWind());	// Verschieben, Test ... kann länger dauern

// Objektgeometrie korrigieren
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

// alte Koordinaten des zu verschiebenden Punktes retten
Punkt ModPkt;

	ModPkt.X() = plXK [lInd];
	ModPkt.Y() = plYK [lInd];

	pIOG->ModPunkt (Pkt.X(), Pkt.Y(), lInd);	// Punkt in pIOG modifizieren

	// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Verschiebung rückgängig machen
bool bRet = ModObjSpeicherung (pIOG, ModPkt, lInd, VORRUECK, Rec);

	if (! bRet)
		pIOG->ModPunkt (ModPkt.X(), ModPkt.Y(), lInd);

	return bRet;
} // StuetzpunktVerschieben2


// -----------------------------------------------------------------------------------------------
// Stützpunkt löschen
void GeoEditExtension :: StuetzpunktLoeschen (void)
{
	TX_ASSERT (m_pIOG != NULL);

	if (! m_pIOG) return;

CEierUhr Wait (MVWind());	// Löschen, Test, Zeichnen ... kann länger dauern

KoOrd* plXK; KoOrd* plYK;

	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);

// zu löschenden Punkt für Rückgängigmachen retten
Punkt ModPkt;

	ModPkt.X() = plXK [m_lInd];
	ModPkt.Y() = plYK [m_lInd];

short iKontInd;	// nur für Flächenobjekte: Index der Kontur, aus der der Stützpunkt gelöscht wird

	m_pIOG->SubPunkt (m_lInd, &iKontInd);

Rectangle Rec;	// Ausschnitt für Neuzeichnen nach Geometrie-Modifikation

	// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Löschen rückgängig machen
	if (ModObjSpeicherung (m_pIOG, ModPkt, m_lInd, RUECKW, Rec) == false)
		m_pIOG->AddPunkt (ModPkt.X(), ModPkt.Y(), m_lInd, iKontInd);

	// Ausschnitt nach Geometrie-Modifikation neu zeichnen
	DEX_RePaintRectWait (Rec);
	MVWind()->Update();		// sofort zeichnen
} // StuetzpunktLoeschen


// -----------------------------------------------------------------------------------------------
// Stützpunkt neu setzen
void GeoEditExtension :: StuetzpunktHinzufuegen (Point newPt)
{
	TX_ASSERT (m_pIOG != NULL);

	if (! m_pIOG) return;

short iOT;

	m_pIOG->GetObjTyp (&iOT);

	// zu einem Punktobjekt kann kein weiterer Stützpunkt hinzugefügt werden
	if (iOT != OT_KANTE && iOT != OT_FLAECHE) return;

CEierUhr Wait (MVWind());	// Einfügen, Test, Zeichnen ... kann länger dauern
Punkt ModPkt = NeuerPunktMitGrab (newPt);	// DB-Koordinaten des einzufügenden Punktes (mit Grab-Funktion)
short iKontInd = -1;	// nur für Flächenobjekt: Index der Kontur, in der neuer Punkt eingefügt wird

	if (iOT == OT_FLAECHE)
	{
	long lInd; 	// wird  hier nicht ausgewertet
	IndPos IP;	// wird  hier nicht ausgewertet (nur für Flächenobjekte: Position des Index m_lInd
				//  innerhalb der betreffenden Kontur)

		m_pIOG->IndexTest (m_lInd, &iKontInd, &lInd, &IP);
	}

	m_pIOG->AddPunkt (ModPkt.X(), ModPkt.Y(), m_lInd, iKontInd);

Rectangle Rec;	// Ausschnitt für Neuzeichnen nach Geometrie-Modifikation

	// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Hinzufügen rückgängig machen
	if (ModObjSpeicherung (m_pIOG, ModPkt, m_lInd, VORRUECK, Rec) == false)
		m_pIOG->SubPunkt (m_lInd, &iKontInd);

	// Ausschnitt nach Geometrie-Modifikation neu zeichnen
	DEX_RePaintRectWait (Rec);
	MVWind()->Update();		// sofort zeichnen
} // StuetzpunktHinzufuegen


// -----------------------------------------------------------------------------------------------
// Hilfsroutine für StuetzpunktVerschieben(), StuetzpunktVerschieben2(), StuetzpunktLoeschen() und
// StuetzpunktHinzufuegen();
// es wird true zurückgegeben, wenn Objekt gespeichert wurde, sonst false
bool GeoEditExtension :: ModObjSpeicherung (IObjektGeometrie* pIOG, Punkt& ModPkt, long& lInd,
											TestRicht trRicht, Rectangle& Rec)
{
	TX_ASSERT (pIOG != NULL);


// mit Schlüssel "GeoFehlerTest" in den projektbezogenen Einträgen des DB-Headers testen,
// ob vor Abspeicherung des pIOG-Objektes nach TRiAS auf Geometriefehler getestet werden
// soll (ja) oder nicht (nein)
// Entartung bereinigt werden soll (Bit 4 = 1) oder nicht (Bit 4 = 0)
ResString Schluessel (ResID (IDS_GEOFEHLERTEST, pRF), 30);	
HeaderEntryX HE (Schluessel);
char pcInPuffer[20] = { "\0" };	// Wert des Schlüssels "GeoFehlerTest"

	if (HE.Status() != HE_INVALID)	// Schlüssel "GeoFehlerTest" existiert im DB-Header
		strcpy (pcInPuffer, HE.EntryText());

HRESULT hrQA = S_OK;	// Rückkehrwert der Routine ShortAnalysis() 
bool bGeoRein = true;	// georein soll angeworfen werden
bool bSpei = true;		// modifiziertes Objekt wird in TRiAS nicht/gespeichert (false/true)

	if (pcInPuffer[0] != 'n' && pcInPuffer[0] != 'N')
	{
	short iOT;
	long lONr;

		// wenn Objekt schon von vornherein fehlerbehaftet ist (Eintrag im Merkmal
		// "Geometriefehler"), dann kommt nur eine vollständige Geometrieprüfung in Betracht;
		// andererseits reicht eine Kurzanalyse aus (Unterscheidung in dem OGGeometryIsChecked-
		// Flag)
		pIOG->GetObjTyp (&iOT);
		pIOG->GetONr (&lONr);
		if ((iOT == OT_KANTE || iOT == OT_FLAECHE) &&
			FehlerhaftesObjekt (lONr) != S_OK)
		{
			GeoReinInterface ();	// (wenn noch nicht, dann) GeoReinInterface für
									//  ShortAnalysis() zuschalten
			if (m_pIGeoRein)
			{
//				hrQA = m_pIGeoRein->ShortAnalyse (&pIOG, trRicht, lInd);
				hrQA = m_pIGeoRein->ShortAnalysis (pIOG, trRicht, &lInd);		// 05.11.97

				if (S_OK == hrQA)		// Analyse ergab keinen Geometriefehler
					bGeoRein = false;	// georein nicht anwerfen
				else					// Analyse ergab Geometriefehler (hrQA == E_FAIL) 
				{
				// Warnung, weil bei Stützpunktmanipulation ein Geometriefehler entstanden ist
				// und deshalb das Objekt nicht abgespeichert wird
				ResString Text1 (ResID (IDS_GEOFEHLERMOD, pRF), 150);
				ResString Text2 (ResID (IDS_LONGCLASSNAME, pRF), 150);
				
					MessageBox (hWnd(), Text1.Addr(), Text2.Addr(), MB_ICONEXCLAMATION | MB_OK);
					bSpei = false;
				}
			}
		}
	}
	else
		bGeoRein = false;	// georein nicht anwerfen

	Rec = AusschnittFuerZeichnen (pIOG, ModPkt, lInd);	// Ausschnitt für Neuzeichnen nach Geometrie-Modifikation

	if (S_OK == hrQA)	// modifiziertes Objekt wird nach TRiAS gespeichert
	{
		// OGModObject gesetzt heißt, daß die Geometrie des Objektes ersetzt werden soll
		// OGForceGeometry gesetzt heißt, daß auch außerhalb des aktuellen DBConts abgespeichert wird
		// OGGeometryIsChecked gesetzt heißt, daß georein nicht angeworfen werden soll
		if (bGeoRein)
			pIOG->SetFlags (OGModObject | OGForceGeometry);
		else
			pIOG->SetFlags (OGModObject | OGForceGeometry | OGGeometryIsChecked);

		// die Message DEX_OBJECTCHANGED (Objektgeometrie wurde verändert) soll kurzzeitig nicht
		// abgefragt werden, da das in GeometrieAnTRiAS() enthaltene DEX_ModObjGeometrie() diese
		// Message aussendet, wodurch es dann bei GeometrieAusBaum() zu einer Lock-Assertion kommt
		UnRegisterNotification (DEX_OBJECTCHANGED);

	HRESULT hr = pIOG->GeometrieAnTRiAS (true, (RECT*)&Rec);	// 1. Parameter besagt, daß Undo möglich ist

		RegisterNotification (DEX_OBJECTCHANGED);

		if (hr != S_OK)
			bSpei = false;
	}
	return bSpei;
} // ModObjSpeicherung

			 
// -----------------------------------------------------------------------------------------------
// Linienobjekt am 1. bzw. letzten Stützpunkt verlängern
bool GeoEditExtension :: LinienobjektVerlaengern (void)
{
long lONr;
short iOT;
ulong ulIdent;
long lSPAnz;
KoOrd* plXK; KoOrd* plYK;

	m_pIOG->GetONr (&lONr);
	m_pIOG->GetObjTyp (&iOT);
	m_pIOG->GetIdent (&ulIdent);
	m_pIOG->GetCnt (&lSPAnz);
	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);

	TX_ASSERT (iOT == OT_KANTE);
	TX_ASSERT (0 == m_lInd || lSPAnz-1 == m_lInd);

	if (iOT != OT_KANTE ||
		(0 != m_lInd && lSPAnz-1 != m_lInd))
		return false;
	
	TX_ASSERT (m_pVerlLin == NULL);

	if (FAILED(CreateInterfaceOG (&m_pVerlLin, lONr)))
		return false;

	// Parameter wie für Neueditierung setzen (der hinzuzunehmende Linienteil wird als
	// Neueditierung behandelt)
	_OTyp = OT_KANTE;
	_pEO = NULL;
	(0 == m_lInd) ? (m_bAnf = true) : (m_bAnf = false);

	// Objektnamen der zu verlängernden Linie für Anzeige im Dialog schon einmal lesen
	if (false == MerkmalLesen (lONr, DEX_GetObjNameMCode(ulIdent), _pcONText, maxTextLaenge))
		return false;	// nicht genügend dynamischer Speicher

	// Identifikator der zu verlängernden Linie für Anzeige im Dialog TRiAS-weit bekanntgeben
	DEX_SetLastIdent (ulIdent);

Point Pt = BSKoordinaten (plXK[m_lInd], plYK[m_lInd]);

	if (Pt.X() > 0) Pt.X()--;	// wegen Fehler bei Hartmut notwendig
	if (Pt.Y() > 0) Pt.Y()--;	// eine Korrektur bei ihm hätte zu große Folgen an anderen Stellen

	LeftMouseDownNew (Pt);

	return true;
} // LinienobjektVerlaengern


// -----------------------------------------------------------------------------------------------
// Speichern-Button im Dialog gedrückt (bei Linienverlängerung)
bool GeoEditExtension :: idb_SpeichernLinienVerl (NeuEditDlg* pNED)
{
	TX_ASSERT (pNED);
	TX_ASSERT (_pEO);
	TX_ASSERT (m_pVerlLin);

	if (!pNED || !_pEO || !m_pVerlLin ||
		OT_KANTE != _OTyp)
		return false;

CEierUhr Wait (MVWind());

long lLvIOG;	// Stützpunktanzahl von m_pVerlLin vor der Linienverlängerung

	m_pVerlLin->GetCnt (&lLvIOG);

long lSPAnz = ((Kante*)_pEO)->ASP ();
KoOrd* plX = new KoOrd [lSPAnz];
KoOrd* plY = new KoOrd [lSPAnz];

	if (!plX || !plY)
	{
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		DELETE_VEC (plX);
		if (m_pVerlLin)
		{
			m_pVerlLin->Release();
			m_pVerlLin = NULL;
		}
		return false;
	}

	if (m_bAnf)
	{
		((Kante*)_pEO)->OrientDreh();
		((Kante*)_pEO)->GetKante (plX, plY, lSPAnz);
		m_pVerlLin->AddPunkt (plX, plY, lSPAnz-1, 0, -1);
	}
	else
	{
		((Kante*)_pEO)->GetKante (plX, plY, lSPAnz);
		m_pVerlLin->AddPunkt (plX, plY, lSPAnz, -1, -1);
	}

	DELETE_VEC (plX);
	DELETE_VEC (plY);

ulong ulIdent = pNED->GetIdent ();	// Identifikator und
SpForm sfSForm = pNED->GetForm ();	//  Speicherform abfragen

	m_pVerlLin->SetIdent (ulIdent);
	if (SFORM_PERM == sfSForm)
		m_pVerlLin->SetFlags (OGModObject | OGForceGeometry);
	else
		m_pVerlLin->SetFlags (OGModObject | OGForceGeometry | OGTempObject);

HRESULT hr = m_pVerlLin->GeometrieAnTRiAS (true, NULL);

	// wenn Objekt in DB eingespeichert wurde, dann evtl. noch Objektname korrigieren
	if (S_OK == hr)
	{
	long lONr;

		m_pVerlLin->GetONr (&lONr);

		// Objektname eintragen
		MerkmalSchreiben (TT_Objekt, lONr, DEX_GetObjNameMCode(ulIdent), _pcONText); // Objektname wegschreiben
		DELETE (_pcONText);
		_pcONText = new char [maxTextLaenge+1];      // maxTextLaenge in geohilfe.hxx definiert
		if (! _pcONText)
		{                                                                      
			DEX_Error (RC_geomodif, EC_NOMEMORY);
			if (m_pVerlLin)
			{
				m_pVerlLin->Release();
				m_pVerlLin = NULL;
			}
			return false;
		}
		_pcONText [0] = '\0';
	}
	else    // wenn Geometrie fehlerhaft, dann keine Einspeicherung in DB
	{
	ResString rsText1 (ResID (IDS_GEOFEHLERNEU, pRF), 100);
	ResString rsText2 (ResID (IDS_LONGCLASSNAME, pRF), 100);

		MessageBox (hWnd(), rsText1.Addr(), rsText2.Addr(), MB_ICONEXCLAMATION | MB_OK);

	short iKontInd;	// KonturIndex, aus dem die Punkte gelöscht wurden (ist bei Kante -1)
	long lLnIOG;	// Stützpunktanzahl von m_pVerlLin nach der Linienverlängerung

		m_pVerlLin->GetCnt (&lLnIOG);		// Stützpunktanzahl nach der Linienverlängerung

		// die Linienverlängerung wieder rückgängig machen
		if (m_bAnf)
			for (long i = 0; i < lLnIOG - lLvIOG; i++)
				m_pVerlLin->SubPunkt (0, &iKontInd);	// (lLnIOG-lLvIOG)-mal den 0. Punkt löschen
		else
			for (long i = lLnIOG - 1; i >= lLvIOG; i--)
				m_pVerlLin->SubPunkt (i, &iKontInd);
	}

	// Bereich, in dem die Linienverlängerung liegt, neu zeichnen
	ObjektZeichnen ();              
	DELETE (_pEO);  // Objekt wird gelöscht (_pEO wurde noch in ObjektZeichnen() benötigt)

	if (m_pVerlLin)
	{
		m_pVerlLin->Release();
		m_pVerlLin = NULL;
	}

	return true;

} // idb_SpeichernLinienVerl


// -----------------------------------------------------------------------------------------------
// Schnittlinie für Flächenteilung aufbauen
bool GeoEditExtension :: SchnittlinieBilden (void)
{
	TX_ASSERT (m_pIOG != NULL);

Punkt EPkt = PunktAufKontur (_ptRM);	// aktuell editierter Punkt auf Kontur ziehen

	_ptRM = BSKoordinaten (EPkt.X(), EPkt.Y());	// _ptRM für Zeichnen auf Bildschirm korrigieren

	MVWind()->MouseTrap (On);	// Erklärung s. geoedit.cxx

short iKAnz;
KoOrd* plXK; KoOrd* plYK;
long* plK;

	m_pIOG->GetKCnt (&iKAnz);
	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);
	m_pIOG->GetLPCnt (&plK);
	m_pFT = MaschenBildung (iKAnz, plXK, plYK, plK);
								   												 
	TX_ASSERT (m_pMesser == NULL);

	if (FAILED(CreateInterfaceOG (&m_pMesser, EPkt.X(), EPkt.Y(), OT_KANTE)))
		return false;

	LRMouseButtonDn (_ptRM);
	return true;
} // SchnittlinieBilden


// -----------------------------------------------------------------------------------------------
// Insel löschen
bool GeoEditExtension :: InselLoeschen (void)
{
	TX_ASSERT (m_pIOG != NULL);

	if (! m_pIOG) return false;

bool bRet;	// Rückgabewert
short iOT, iKAnz;

	m_pIOG->GetObjTyp (&iOT);
	m_pIOG->GetKCnt (&iKAnz);

	if (OT_FLAECHE != iOT || 1 == iKAnz)	
		return false;

long* plK;

	m_pIOG->GetLPCnt (&plK);

short iKontInd = -1;	// Index der Kontur, auf der sich der Cursor befindet
long lInd; 				// wird  hier nicht ausgewertet
IndPos IP;				// wird  hier nicht ausgewertet

	m_pIOG->IndexTest (m_lInd, &iKontInd, &lInd, &IP);

long lKL = plK[iKontInd];	// Länge der zu löschenden Innenkontur
KoOrd* plXI = new KoOrd [lKL];
KoOrd* plYI = new KoOrd [lKL];

	if (! plXI || ! plYI)
	{
		DELETE_VEC (plXI);
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		return false;
	}

// Ausschnitt für Neuzeichnen nach Löschen der Insel sowie die Koordinatenvektoren
// plXI, plYI ermitteln
Rectangle Rec = InselParameter (iKontInd, plXI, plYI);

	if (S_OK == m_pIOG->SubKante (1, iKontInd))
	{
		if (S_OK == InselLoeschenSpeicherung (Rec))
		{
			DEX_RePaintRectWait (Rec);	// Ausschnitt nach Löschen der Insel neu zeichnen
			MVWind()->Update();		// sofort zeichnen
			bRet = true;
		}
		else
		{
			// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Löschen
			// rückgängig machen
			m_pIOG->AddKante (plXI, plYI, lKL, iKontInd);
			bRet = false;
		}
	}
	else
		bRet = false;

	DELETE_VEC (plXI);
	DELETE_VEC (plYI);
	return bRet;

} // InselLoeschen


// -----------------------------------------------------------------------------------------------
// Bildschirmbereich ermitteln, in dem die zu löschende Insel liegt, sowie Koordinatenvektoren
// für die zulöschende Insel in plXI, plYI zurückgeben
Rectangle GeoEditExtension :: InselParameter (short iKontInd, KoOrd* plXI, KoOrd* plYI)
{
	TX_ASSERT (plXI);
	TX_ASSERT (plYI);

KoOrd* plXK; KoOrd* plYK;
long* plK;

	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);
	m_pIOG->GetLPCnt (&plK);

long lSPAvor = 0;	// Anzahl der Stützpunkte vor der gelöschten Insel

	for (register short i = 0; i < iKontInd; i++)
		lSPAvor += plK[i];

KoOrd xmin = MAXKOORD;
KoOrd xmax = 0;
KoOrd ymin = MAXKOORD;
KoOrd ymax = 0;

	// der letzte Punkt der Insel braucht nicht mit getestet zu werden
	for (long l = lSPAvor; l < lSPAvor+plK[iKontInd]-1; l++)
	{
		if (plXK[l] < xmin) xmin = plXK[l];
		if (plXK[l] > xmax) xmax = plXK[l];
		if (plYK[l] < ymin) ymin = plYK[l];
		if (plYK[l] > ymax) ymax = plYK[l];
		plXI[l-lSPAvor] = plXK[l];	// Rückgabe der Koordinaten der
		plYI[l-lSPAvor] = plYK[l];	//  zu löschenden Insel
	}

	plXI[l-lSPAvor] = plXK[lSPAvor];	// letzter Punkt gleich
	plYI[l-lSPAvor] = plYK[lSPAvor];	// erstem Punkt

Point PLO = BSKoordinaten (xmin, ymax);
Point PRU = BSKoordinaten (xmax, ymin);

short iKorr = GroesseMarkQuadrat() / 2 + 2;	// Wert für "leichte" Vergrößerung des Rechtecks

	PLO.X() -= iKorr; 
	PLO.Y() += iKorr;
	PRU.X() += iKorr;
	PRU.Y() -= iKorr;

	return Rectangle (PLO, PRU);

} // InselParameter


// -----------------------------------------------------------------------------------------------
// Fläche nach Löschen einer Insel speichern
HRESULT GeoEditExtension :: InselLoeschenSpeicherung (Rectangle Rec)
{
	// OGModObject gesetzt heißt, daß die Geometrie des Objektes ersetzt werden soll
	m_pIOG->SetFlags (OGModObject);

	// die Message DEX_OBJECTCHANGED (Objektgeometrie wurde verändert) soll kurzzeitig nicht
	// abgefragt werden, da das in GeometrieAnTRiAS() enthaltene DEX_ModObjGeometrie() diese
	// Message aussendet, wodurch es dann bei GeometrieAusBaum() zu einer Lock-Assertion kommt
	UnRegisterNotification (DEX_OBJECTCHANGED);

HRESULT hr = m_pIOG->GeometrieAnTRiAS (true, (RECT*)&Rec);
																
	RegisterNotification (DEX_OBJECTCHANGED);

	return hr;

} // InselLoeschenSpeicherung


// -----------------------------------------------------------------------------------------------
// Objekt löschen
void GeoEditExtension :: ObjektLoeschen (void)
{
long lONr;
short iOT;
int iPixX, iPixY;	// Größe eines Punktsymbols in BS-Pixel

	m_pIOG->GetONr (&lONr);
	m_pIOG->GetObjTyp (&iOT);

	if (iOT == OT_PUNKT)
		PunktSymbolGroesse (m_pIOG, iPixX, iPixY);

#if defined(WIN32)	// Undo für WIN32

ResString Text (ResID (IDS_DELOBJECT, pRF), 50);

	DEX_BeginUndoLevel (Text.Addr());	// dieser Text wird tatsächlich verwendet
	if (! DEX_DeleteObjectEx (lONr))
		DEX_CancelUndoLevel (true);
	else
		DEX_EndUndoLevel ();

#else				// WIN16

	DEX_DeleteObjectEx (lONr);

#endif // WIN32

	if (iOT == OT_PUNKT)	// Punktsymbol auf BS löschen
	{	// 5 ist Sicherheitszugabe
	Rectangle Rec (_ptRM.Y()+iPixY/2+5, _ptRM.X()-iPixX/2-5,
				   _ptRM.Y()-iPixY/2-5, _ptRM.X()+iPixX/2+5);

		DEX_RePaintRectWait (Rec);
		MVWind()->Update();		// sofort zeichnen
	}
} // ObjektLoeschen


// -----------------------------------------------------------------------------------------------
// Flächenobjekt teilen
bool GeoEditExtension :: FlaecheTeilen (void)
{
	DELETE (m_pFT);		// zu teilende Fläche

//	m_pIOG-Fläche teilen
IEnumLONG* pIEnum = NULL;

	if (m_pIObjOper)
	{
	long lONr;

		m_pIOG->GetONr (&lONr);

		m_pIObjOper->SectionLineObj_Geom (m_pMesser, lONr, &pIEnum);
	}

short iAnzTFl = 0;	// Anzahl der erzeugten Teilflächen

	if (pIEnum)
		iAnzTFl = (short) pIEnum->Count();	// Anzahl der erzeugten Teilflächen

	if (iAnzTFl > 0)	// Flächenteilung war erfolgreich
	{
	// Objektnummern der Teilflächen aus pIEnum auslesen
	HRESULT hrRet;		// Rückkehrwert von pIEnum->Next()
	long* lpNeuONr = new long [iAnzTFl];

		if (! lpNeuONr)
		{
			DEX_Error (RC_geomodif, EC_NOMEMORY);
			return false;
		}
		
		pIEnum->Reset();
		hrRet = pIEnum->Next (iAnzTFl, lpNeuONr, NULL);

		TX_ASSERT (hrRet == S_OK);

		if (hrRet != S_OK)
			return false;

		BereichZeichnen (m_pMesser);	// Linienzug des "Messers" löschen

	POINT pt;	 	// linker unterer Eckpunkt des Recherchefensters

		pt.x = pt.y = 5;
		FensterNeueObjekte (pt, lpNeuONr, iAnzTFl);	// Recherchefenster
		DELETE (lpNeuONr);
	}
	else						// Flächenteilung ist nicht gelungen
	{
	ResString Text1 (ResID (IDS_NOTEILUNG, pRF), 150);
	ResString Text2 (ResID (IDS_LONGCLASSNAME, pRF), 50);
			
		MessageBox (hWnd(), Text1.Addr(), Text2.Addr(), MB_ICONEXCLAMATION | MB_OK);

		BereichZeichnen (m_pMesser);	// Linienzug des "Messers" löschen
	}

	if (pIEnum)
		pIEnum->Release ();

	if (m_pMesser)
	{
		m_pMesser->Release();
		m_pMesser = NULL;
	}
	return false;
} // FlaecheTeilen


// --------------------------------------------------------------------------------------------
// Pt in DB-Koordinaten umrechnen und auf den nächstgelegenen Punkt der Außenkontur von m_pIOG
// ziehen; i.d.R. wird das ein Punkt sein, der auf der Verbindungsstrecke zwischen
// 2 m_pIOG-Stützpunkten liegt
Punkt GeoEditExtension :: PunktAufKontur (Point Pt)
{
	TX_ASSERT (m_pIOG != NULL);

short iOT, iFlags;
KoOrd* plXK; KoOrd* plYK;
long* plK;

	m_pIOG->GetObjTyp (&iOT);
	m_pIOG->GetFlags (&iFlags);
	m_pIOG->GetX ((void**)&plXK);
	m_pIOG->GetY ((void**)&plYK);
	m_pIOG->GetLPCnt (&plK);

	TX_ASSERT (iOT == OT_FLAECHE);
	TX_ASSERT ((iFlags & OGConverted) == false);	// Koordinaten im KoOrd-Format

Punkt Pkt =	DBKoordinaten (Pt);

long lSPAnz = plK [0];		// Stützpunktanzahl der Außenkontur
KoOrd MinAbst1 = LONG_MAX;	// kleinster Abstand von Pkt zu den Strecken der m_pIOG-Außenkontur
KoOrd MinAbst2 = LONG_MAX;	// kleinster Abstand von Pkt zu den Punkten der m_pIOG-Außenkontur
KoOrd Abst1;				// Abstand zur Strecke Str
KoOrd Abst2;				// Abstand zum Punkt P1
Punkt LPkt;					// Lotpunkt von Pkt auf die m_pIOG-Strecken mit MinAbst1
long lInd1;					// Index der m_pIOG-Strecke, dem der Rückgabe-Punkt am nächsten
							//  liegt
long lInd2;					// Index des m_pIOG-Stützpunktes, dem der Rückgabe-Punkt am
							//  nächsten liegt

	for (long i = 0; i < lSPAnz-1; i++)
	{
	Punkt P1 (plXK[i], plYK[i]);
	Punkt P2 (plXK[i+1], plYK[i+1]);
	Strecke Str (P1, P2);
	Punkt LP;	// Lotpunkt von Pkt auf eine m_pIOG-Strecke

		if (Str.LotPktStrecke (Pkt, Abst1, LP) &&	// Abst1 gilt echt für die Strecke Str (nicht
			Abst1 < MinAbst1)						//  für deren Trägergerade)
		{
			if (Abst1 == 0)		// Pkt liegt auf der Strecke Str
				return Pkt;

			lInd1 = i;
			MinAbst1 = Abst1;
			LPkt = LP;
		}

		Abst2 = AbstandPktPktM (Pkt, P1);
		if (Abst2 < MinAbst2)
		{
			lInd2 = i;
			MinAbst2 = Abst2;
		}
	}

	// Pkt liegt nicht auf der m_pIOG-Außenkontur, ist aber der m_pIOG-Strecke (lInd1, lInd1+1)
	// näher als jedem Stützpunkt
	if (MinAbst1 < MinAbst2)
	{
	Punkt PA (plXK[lInd1], plYK[lInd1]);
	Punkt PE (plXK[lInd1+1], plYK[lInd1+1]);

		// es muß jedoch garantiert sein, daß LPkt (bedingt durch die Rundung der
		// LPkt-Koordinaten auf ganzzahlige Werte) nicht innerhalb von m_pIOG liegt
		if (-1 == BewegRicht (PA, LPkt, PE))	// LPkt liegt innerhalb von m_pIOG
		{
			LPkt.X()++;
			if (-1 == BewegRicht (PA, LPkt, PE))
			{
				LPkt.X() = LPkt.X() - 2;
				if (-1 == BewegRicht (PA, LPkt, PE))
				{
					LPkt.X()++;
					LPkt.Y()++;
					if (-1 == BewegRicht (PA, LPkt, PE))
					{
						LPkt.Y() = LPkt.Y() - 2;
						if (-1 == BewegRicht (PA, LPkt, PE))
							TX_ASSERT (false);	// bis hierhin dürfte keiner mehr kommen
					}
				}
			}
		}
		return LPkt;		// Lotpunkt von Pkt auf Strecke (lInd1, lInd1+1)
	}

	// Pkt ist dem lInd2-ten Stützpunkt näher als jeder m_pIOG-Strecke
	return Punkt (plXK[lInd2], plYK[lInd2]);

} // PunktAufKontur


// -----------------------------------------------------------------------------------------------
// Recherchefenster für neu erzeugte Objekte generieren
void GeoEditExtension :: FensterNeueObjekte (POINT pt, long* plNeuObjNr, short iAnzNeuObj)
{
ResString Text (ResID (IDS_NEUEOBJEKTE, pRF), 70);
CREATEOBJEKTINFO COI;	// Struktur für Recherchefenster
	
	INITSTRUCT (COI, CREATEOBJEKTINFO);
	COI.lpCaption = (char*) Text.Addr();	// Fensterüberschrift
	COI.plObjs = plNeuObjNr;				// Objektnummern, die angezeigt werden sollen
	COI.iNumObjs = iAnzNeuObj;				// Anzahl der Objektnummern
	COI.cMColor = RGB (160,60,180);			// Markierungsfarbe (rot, grün, blau)
	COI.pntPos = pt;						// Position des Recherchefensters im Hauptfenster

	// Recherchefenster anzeigen
	DEX_CreateObjektInfo (COI);
} // FensterNeueObjekte


// -----------------------------------------------------------------------------------------------
// rechteckiger Ausschnitt neu zeichnen, in dem der modifizierte Teil des Objektes pIOG liegt
Rectangle GeoEditExtension :: AusschnittFuerZeichnen (IObjektGeometrie* pIOG, Punkt& ModPkt,
													  long lInd)
{
double dQuot;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab

	DEX_GetActiveScaling (dQuot);

	if (dQuot > 0) dQuot *= 100.;	
	else
	{
		TX_ASSERT (dQuot > 0);
		dQuot = 1.;   // um Division durch Null vorzubeugen
	}

short iMarkGr = GroesseMarkQuadrat ();

short iOT;
ulong ulIdent;

	m_pIOG->GetObjTyp (&iOT);
	m_pIOG->GetIdent (&ulIdent);

Point PLO, PRU;	// linker oberer (PLO) bzw. rechter unterer Eckpunkt (PRU) des neu zu zeichnenden Ausschnitts im Point-Format
HANDLEVISINFO HVI;

	INITSTRUCT (HVI, HANDLEVISINFO);	// Initialisierung
	HVI.m_lIdent = ulIdent;				// Identifikator
	HVI.m_pDesc = NULL;					// beschreibender Text
	HVI.m_pView = NULL;					// SichtName (aktuelle Sicht: NULL)

	switch (iOT)
	{
		case OT_PUNKT:
		{
		PVISINFO PVI;
		SIZE sizePG;
				
			HVI.m_iVTyp = VTPunkt;		// VisInfoTyp
			HVI.m_pVI = &(PVI.m_VI);	// generischer Pointer auf VisInfo
			if (!DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
			{
				sizePG.cx = DEF_SIZE_PUNKT_X;
				sizePG.cy = DEF_SIZE_PUNKT_Y;
			}
			else
				sizePG = PVI.m_Size;   // Punktgröße (Eintrag aus der VisInfo)

		int ixpix = (int) (sizePG.cx * m_dimDots.Width() / dQuot);	// Größe des Punktsymbols in BS-Pixel (x-Richtung)
		int iypix = (int) (sizePG.cy * m_dimDots.Height() / dQuot);	//  bzw. y-Richtung
		
			AusschnittErmitteln (pIOG, ModPkt, lInd, PLO, PRU);					    
			PLO = Point (PLO.X() - ixpix/2 - zug, PLO.Y() + iypix/2 + zug);
			PRU = Point (PRU.X() + ixpix/2 + zug, PRU.Y() - iypix/2 - zug);
		}
			break;
			
		case OT_KANTE:
		{
		LVISINFO LVI;
		short iLinBr;

			HVI.m_iVTyp = VTLinie;		// VisInfoTyp
			HVI.m_pVI = &(LVI.m_VI);	// generischer Pointer auf VisInfo
			if (!DEX_GetIdentVisInfo (HVI))		// RückkehrCode ausgewertet
				iLinBr = DEF_WIDTH_LINIE;
			else
				iLinBr = LVI.m_Width;		// LinienBreite (Eintrag aus der Visualisierungsinformation)

		// Maximum aus Linienbreite und Größe eines Markers in x- bzw. y-Richtung
		int xzug = (int) max (iLinBr * m_dimDots.Width() / dQuot + zug, iMarkGr);
		int yzug = (int) max (iLinBr * m_dimDots.Height() / dQuot + zug, iMarkGr);
		
		
			AusschnittErmitteln (pIOG, ModPkt, lInd, PLO, PRU);					    
			PLO.X() -= xzug;	// zu bildendes Rechteck noch um Maximun aus Linienbreite
			PLO.Y() += yzug;	//  bzw. Marker-Größe vergrößern
			PRU.X() += xzug;
			PRU.Y() -= yzug;
		}
			break;
			
		case OT_FLAECHE:
		{
		FVISINFO FVI;
		short iKontBr;
				
			HVI.m_iVTyp = VTFlaeche;		// VisInfoTyp
			HVI.m_pVI = &(FVI.m_VI);		// generischer Pointer auf VisInfo
			if (!DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
				iKontBr = DEF_WIDTH_FRAME;
			else
			{
			// m_Style ist ein 16-Bit-Wort mit mehreren Informationen; wenn das 16. Bit ausgeblendet
			// und der Rest durch 100 dividiert wird, liefert das ganzzahligen Divisionsergebnis
			// die Konturbreite in 0.01 mm, d.h. den Eintrag aus der Visualisierungsinformation
				iKontBr = ((FVI.m_VI.m_Style) & 0x7FFF) / 100;
			}

		// Maximum aus Konturbreite und Größe eines Markers in x- bzw. y-Richtung
		int xzug = (int) max (iKontBr * m_dimDots.Width() / dQuot + zug, iMarkGr);
		int yzug = (int) max (iKontBr * m_dimDots.Height() / dQuot + zug, iMarkGr);
		
			AusschnittErmitteln (pIOG, ModPkt, lInd, PLO, PRU);					    
			PLO.X() -= xzug;	// zu bildendes Rechteck noch um das Maximum aus Konturbreite
			PLO.Y() += yzug;	//   bzw. Marker-Größe vergrößern
			PRU.X() += xzug;
			PRU.Y() -= yzug;
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
	 
	return Rectangle (PLO, PRU);
} // AusschnittFuerZeichnen


// -----------------------------------------------------------------------------------------------
// Bereich ermitteln, in dem das Objekt pIOG modifiziert wurde, um diesen Ausschnitt neu zu zeichnen;
// ist pIOG Fläche, wird dafür ein achsenparalleles Rechteck aus der alten, der neuen Stützpunktposition
// und aus dem vorhergehenden und nachfolgenden Stützpunkt der entsprechenden Kontur gebildet;
// ist pIOG eine Linie, entfällt für Rechteckbildung der vorhergehende oder nachfolgende Stützpunkt,
// wenn der verschobene Stützpunkt der erste bzw. letzte gewesen ist;
// ist pIOG ein Punkt wird  der rechteckige Bereich nur aus der alten und der neuen Stützpunktposition
// gebildet;
// Rückgabe des linken oberen (PLO) bzw. rechten unteren Punktes (PRU) dieses Rechteckbereiches

void GeoEditExtension :: AusschnittErmitteln (IObjektGeometrie* pIOG, Punkt& ModPkt, long lInd,
											  Point& PLO, Point& PRU)
{
	TX_ASSERT (pIOG);
	if (!pIOG) return;

short iOT;
long lSPA;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetObjTyp (&iOT);
	pIOG->GetCnt (&lSPA);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	if (lInd >= lSPA)	// passiert bei Löschen des letzten Stützpunktes
		lInd = lSPA - 1;

KoOrd x = plXK [lInd];				// neue x- bzw.
KoOrd y = plYK [lInd];				//  y-Koordinate des modifizierten Stützpunktes
KoOrd xmin = min (x, ModPkt.X());	// Vergleich mit den alten Koordinaten des
KoOrd xmax = max (x, ModPkt.X());	//  modifizierten Punktes
KoOrd ymin = min (y, ModPkt.Y());
KoOrd ymax = max (y, ModPkt.Y());

	switch (iOT)
	{
		case OT_PUNKT:
			break;
			
		case OT_KANTE:
			if (lInd > 0)		// es wurde nicht der 1. Stützpunkt modifiziert, deshalb
			{					//  Einbeziehung des vorhergehenden Stützpunktes
				xmin = min (xmin, plXK [lInd-1]);
				xmax = max (xmax, plXK [lInd-1]);
				ymin = min (ymin, plYK [lInd-1]);
				ymax = max (ymax, plYK [lInd-1]);
			}
			if (lInd < lSPA-1)	// es wurde nicht der letzte Stützpunkt modifiziert,
			{					//  deshalb Einbeziehung des nachfolgenden Stützpunktes
				xmin = min (xmin, plXK [lInd+1]);
				xmax = max (xmax, plXK [lInd+1]);
				ymin = min (ymin, plYK [lInd+1]);
				ymax = max (ymax, plYK [lInd+1]);
			}
			break;
			
		case OT_FLAECHE:
		{
		long lIndv, lIndn;	// Indizes des vorhergehenden bzw. nachfolgenden Stützpunktes
		
			pIOG->IndexVorNach (lInd, &lIndv, &lIndn);	
			
			xmin = min (xmin, plXK [lIndv]);
			xmax = max (xmax, plXK [lIndv]);
			ymin = min (ymin, plYK [lIndv]);
			ymax = max (ymax, plYK [lIndv]);
			
			xmin = min (xmin, plXK [lIndn]);
			xmax = max (xmax, plXK [lIndn]);
			ymin = min (ymin, plYK [lIndn]);
			ymax = max (ymax, plYK [lIndn]);
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
	
	PLO = BSKoordinaten (xmin, ymax);
	PRU = BSKoordinaten (xmax, ymin);
} // AusschnittErmitteln


// -----------------------------------------------------------------------------------------------
// Größe eines Punktsymbols in BS-Pixel ermitteln; Rückgabe in iPixX bzw. iPixY;
// wird false zurückgegeben, sind iPixX und iPixY unbestimmt
bool GeoEditExtension :: PunktSymbolGroesse (IObjektGeometrie* pIOG, int& iPixX, int& iPixY)
{
	iPixX = 0;		// für Fehlerfall
	iPixY = 0;

	TX_ASSERT (pIOG);

	if (! pIOG) return false;

short iOT;

	pIOG->GetObjTyp (&iOT);
	if (iOT != OT_PUNKT) return false;

double dQuot;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab

	DEX_GetActiveScaling (dQuot);
	if (dQuot > 0) dQuot *= 100.;	
	else
	{
		TX_ASSERT (dQuot > 0);
		dQuot = 1.;   // um Division durch Null vorzubeugen
	}

ulong ulIdent;

	pIOG->GetIdent (&ulIdent);

Point PLO, PRU;	// linker oberer (PLO) bzw. rechter unterer Eckpunkt (PRU) des umschreibenden
				//  Rechtecks des Punktsymbols
HANDLEVISINFO HVI;

	INITSTRUCT (HVI, HANDLEVISINFO);	// Initialisierung
	HVI.m_lIdent = ulIdent;				// Identifikator
	HVI.m_pDesc = NULL;					// beschreibender Text
	HVI.m_pView = NULL;					// SichtName (aktuelle Sicht: NULL)

PVISINFO PVI;
SIZE sizePG;
				
	HVI.m_iVTyp = VTPunkt;				// VisInfoTyp
	HVI.m_pVI = &(PVI.m_VI);			// generischer Pointer auf VisInfo

	if (!DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
	{
		sizePG.cx = DEF_SIZE_PUNKT_X;
		sizePG.cy = DEF_SIZE_PUNKT_Y;
	}
	else
		sizePG = PVI.m_Size;   // Punktgröße (Eintrag aus der VisInfo)

	iPixX = (int) (sizePG.cx * m_dimDots.Width() / dQuot);	// Größe des Punktsymbols in BS-Pixel (x-Richtung)
	iPixY = (int) (sizePG.cy * m_dimDots.Height() / dQuot);	//  bzw. y-Richtung
	return true;
} // PunktSymbolGroesse


// -----------------------------------------------------------------------------------------------
// Stützpunktmarkierungen aller Objekte im GeometrieBaum löschen
bool GeoEditExtension :: StuetzpunkteDeMarkieren (void)
{
	TX_ASSERT (m_pGB);

	if (! m_pGB) return false;

bool bRet = true;
CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
	    	DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}

	IObjektGeometrie* pIOG = NULL;
	HRESULT hr = kl->GetIOG (&pIOG);

		if (SUCCEEDED(hr))
		{
			bRet = MarkierungenBearbeiten (pIOG, false);
			if (pIOG) pIOG->Release();	// AddRef() in GetIOG()
		}
	}

	return bRet;
} // StuetzpunkteDeMarkieren


// -----------------------------------------------------------------------------------------------
// Geometrie des selektierten (markierten) lONr-Objektes in Baum eintragen
bool GeoEditExtension :: GeometrieInBaum (long lONr)
{
	TX_ASSERT (lONr > 0);

	return m_pGB->InsertK (lONr);	// lONr-Objekt in Baum eintragen
} // GeometrieInBaum


// -----------------------------------------------------------------------------------------------
// Geometrie des soeben deselektierten Objektes aus Baum austragen
bool GeoEditExtension :: GeometrieAusBaum (long lONr)
{
	TX_ASSERT (lONr > 0);

	return m_pGB->DeleteK (lONr);
} // GeometrieAusBaum


// -----------------------------------------------------------------------------------------------
// evtl. weitere ObjektGeometrien in GeometrieBaum einfügen
void GeoEditExtension :: GeometrienErgaenzen (void)
{
// selektierte Objekte (wenn noch nicht eingetragen) in GeometrieBaum m_pGB eintragen
ENUMLONGKEY ELK;

	ELK.eKey = (DWORD) 0;	// Handle aller geöffneten Recherchefenster
	ELK.eFcn = (ENUMLONGKEYPROC) ObjektInBaum;
	DEX_EnumSelectedObjects (ELK);
} // GeometrienErgaenzen


// -----------------------------------------------------------------------------------------------
// m_iAnz aller Objekte im GeometrieBaum zurücksetzen
void GeoEditExtension :: AnzRuecksetzen (void)
{
	TX_ASSERT (m_pGB != NULL);

	if (! m_pGB) return;

CTable tab (*m_pGB);

	for (tab.First(); tab.Valid(); tab.Next())
	{
	GeometrieKnotenLock kl (tab);

		if (! kl)
		{
    		DEX_Error (RC_geomodif, EC_SYSERROR);
			continue;
		}
		kl->SetAnz ();
	}
} // AnzRuecksetzen


// -----------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "GeometrieBereinigung" herstellen, wenn noch m_bGeoRein == false
void GeoEditExtension :: GeoReinInterface (void)
{
	if (! m_bGeoRein)
	{
	HRESULT hr = 0;

		if (m_pXtnSite)
			hr = m_pXtnSite->GetXtension (CLSID_GeometrieBereinigung, IID_IExtendGeoRein,
										  (LPVOID*)&m_pIGeoRein);

		if (FAILED (hr) ||	// Fehler, z.B. georein.ext nicht verfügbar
			! m_pXtnSite)
		{
		ResString Text1 (ResID (IDS_NOGEOREIN, pRF), 250);
		ResString Text2 (ResID (IDS_LONGCLASSNAME, pRF), 150);
			
			MessageBox (hWnd(), Text1.Addr(), Text2.Addr(), MB_ICONEXCLAMATION | MB_OK);
			return;
		}
		m_bGeoRein = true;
	}
} // GeoReinInterface   


// -----------------------------------------------------------------------------------------------
// Größe der Markierungsquadrate bestimmen
short GeoEditExtension :: GroesseMarkQuadrat (void)
{
double dQuot;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab (hängt vom Zoom-Zustand ab)

	DEX_GetActiveScaling (dQuot);

	if (0 >= dQuot) return iUGr;   // um Division durch Null vorzubeugen

short iMG = (short) DtoL (m_iUMarkGr / dQuot / 2.);	// "5" ist ein heuristischer Wert

	if (iMG < iUGr) iMG = m_iUMarkGr;	// untere Grenze
	if (iMG > iOGr) iMG = m_iOMarkGr;	// obere Grenze
	return iMG;
} // GroesseMarkQuadrat


// --------------------------------------------------------------------------------------------
// Merkmal eines Objektes lesen;
// bei Rückgabe von false konnte die für das Lesen notwendige Struktur wegen fehlendem freiem
// dynamischen Speicher nicht aufgebaut werden
bool GeoEditExtension :: MerkmalLesen (long lONr, long lMerkCode, char* pcMText, short iPLaeng)
{
	TX_ASSERT (lONr > 0);
	TX_ASSERT (lMerkCode > 0);
	TX_ASSERT (pcMText != NULL);
	TX_ASSERT (iPLaeng > 0);

	if (lONr <= 0)
		return false;
	
TARGETMERKMAL TM;

	memset (&TM, '\0', sizeof (TARGETMERKMAL)); // Initialisierung
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = lMerkCode;		// MerkmalsCode
	TM.imaxLen = maxTextLaenge; // max. Textlänge (muß hier gesetzt werden, wird aber
								//  durch DEX_GetTextMerkmal modifiziert
	TM.pMText = new char [maxTextLaenge];	// zu liefernder Merkmalstext
	if (! TM.pMText)
	{
		DEX_Error (RC_geomodif, EC_NOMEMORY);
		return false;
	}
	TM.iTTyp = TT_Objekt;       // Objektmerkmal
	DEX_GetTextMerkmal (TM);	// setzt Textlänge TM.imaxLen neu
	if (TM.imaxLen > 0)			// ein ungenutztes Merkmal hat Textlänge = -1
	{
		TX_ASSERT (strlen(TM.pMText) < (size_t)iPLaeng);
		strncpy (pcMText, TM.pMText, iPLaeng - 1);
	}
	else
		pcMText[0] = '\0';
	DELETE_VEC (TM.pMText);
	return true;
} // MerkmalLesen


// --------------------------------------------------------------------------------------------
// Merkmal eines Objektes schreiben
bool GeoEditExtension :: MerkmalSchreiben (short iTTyp, long lONr, long lMCode, const char* pcText)
{
// bei Löschen eines Merkmals ist pcText == NULL
	TX_ASSERT (lONr > 0);
	TX_ASSERT (lMCode > 0);

	if (lONr <= 0 || lMCode <= 0) return false;

TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = (LPARAM)lONr;
	TM.lMCode = lMCode;
	TM.imaxLen = pcText != NULL ? strlen (pcText) : 0;
	TM.pMText = (char*) pcText;
	TM.iTTyp = iTTyp;
	if (EC_OKAY != DEX_ModTextMerkmal (TM))
		return false;
	return true;

} // MerkmalSchreiben

/*
// --------------------------------------------------------------------------------------------
// Texte der Merkmalscodes des lONr1-GeoObjektes werden zum lONr2-GeoObjekt kopiert; in pcErg
// kann noch eine Ergänzung übergeben werden, die an das Ende des UniqueIdent des
// lONr1-Objektes angehangen wird;
// der Merkmalstext wird überschrieben/angehangen (bUeber == true/false);
// der Merkmalstext von "Geometriefehler" wird nicht/kopiert bei bGeoErr == false/true;
// analoges gilt für "Bereinigter Geometriefehler" mit bClear und "Verschnitt" mit bSect
bool GeoEditExtension :: MerkmaleKopieren (long lONr1, long lONr2, char* pcErg, bool bUeber,
										   bool bGeoErr, bool bClear, bool bSect)
{
	TX_ASSERT (lONr1 > 0);
	TX_ASSERT (lONr2 > 0);
	TX_ASSERT (pcErg != NULL);

struct DatKop Dat;	// in opdeklar.hxx definiert

	Dat.lONr1 = lONr1;
	Dat.lONr2 = lONr2;
//	TX_ASSERT (strlen(pcErg) < 30);	// Puffergröße von Dat.pcEr ist 30 !!!!!!!!!!!!!!!!!!!!
//	strncpy (Dat.pcEr, pcErg, 29);
	Dat.sUIErg = pcErg;
	Dat.bUeber = bUeber;
	Dat.bGeoErr = bGeoErr;
	Dat.bClear = bClear;
	Dat.bSect = bSect;

// alle Merkmalscodes des lONr1-Objektes bereitstellen
ENUMLONGKEY ELK;

	ELK.eKey = lONr1;
	ELK.eFcn = (ENUMLONGKEYPROC) AlleMerkmale;
	ELK.ePtr = (void*) &Dat;
	return DEX_EnumObjektMerkmale (ELK);	// Enumeration der Merkmalscodes eines Objektes

} // MerkmaleKopieren
*/