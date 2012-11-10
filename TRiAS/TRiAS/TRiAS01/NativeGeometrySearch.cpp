// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 07/25/1998 12:47:01 PM
//
// @doc
// @module NativeGeometrySearch.cpp | GeometrieSuchroutinen für TRiAS-Datenbanken

#include "trias01p.hxx"

#include <ospace/std/set>
#include <ospace/utility/autoptr.h>

#include <float.h>

#include <ActDB.h>
#include <ErrInst.hxx>
#include <DBTypes.h>
#include <NativeObject.h>
#include <HeaderEntry.h>
#include <ScaleHeader.h>

#include "syncdb.hxx"
#include "ConnectFilterWrappers.h"
#include "ObjectGiST.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen
HRESULT QtWindow (HPROJECT Pr, double *pdWindow, QTWINDOWACTIONPROC action, long iKeyIndex, UINT_PTR dwData);
HRESULT HtWindow (HPROJECT hPr, double *pdWindow, HTWINDOWACTIONPROC action, long iKeyIndex, UINT_PTR dwData);

namespace trias_nativeobject {

///////////////////////////////////////////////////////////////////////////////
// hier verwendete Datentypen
typedef set<INT_PTR> CObjectHandleMap;

///////////////////////////////////////////////////////////////////////////////
// lokale Funktionen

long FindKante (HPROJECT hPr, DB_ADDR *pdbakal, double *pdWindow, BOOL *pfFound);
BOOL PointInContainer (double ix1, double iy1, double ix2, double iy2, double ixc1, double iyc1, double ixc3, double iyc3);
long FindMasche (HPROJECT hPr, DB_ADDR *pdbamal, double *pdWindow, BOOL *pfFound);
HRESULT PointInPolygon (HPROJECT hPr, double xp, double yp, long lONr, long *plPktLage);
#if defined(_FORCE_LEGACY_CODE)
long PunktLage (double dXp, double dYp, double *x, double *y, long lCnt);
#else
HRESULT PunktLage (double dXp, double dYp, double *x, double *y, long lCnt, bool &rbInner);
#endif // _FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// 
inline int sign (double a) { return (a < 0) ? -1 : 1; }
inline int ARITHIF(double x) { 	return (x > 0.0) ? 1 : ((x < 0.0) ? -1 : 0); }

#define	EKAMA	(-209L)		// FehlerCode

///////////////////////////////////////////////////////////////////////////////
// Enumerieren aller Objekte, die mit einem gegebenen Bereich in Berührung kommen
/* static */
HRESULT CNativeObject::EnumObjectsInWindow (
	HPROJECT hPr, LPCSTR pcName, double *pdWindow, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData, BOOL fExact)
{
	if (NULL == pdWindow) 
		return E_INVALIDARG;

	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB(hPr);

// Fenster skalieren
	TX_ASSERT(TIsValidAddress (pdWindow, 4*sizeof(double), false));

CScaleHeader Hdr (hPr);
double dWind[4];

	Hdr.Scale (pdWindow[0], pdWindow[2], &dWind[0], &dWind[2]);
	Hdr.Scale (pdWindow[1], pdWindow[3], &dWind[1], &dWind[3]);
	
// zuerst den Punktbaum, dann den Kantenbaum durchsuchen lassen
	RETURN_FAILED_HRESULT(QtSearch (hPr, pcName, dWind, pFcn, dwData));
	RETURN_FAILED_HRESULT(HtSearch (hPr, pcName, dWind, pFcn, dwData, fExact));

	return S_OK;
}

// Punktbaum nach allen das Fenster berührenden Objekten absuchen
long __cdecl QtTestRecord (DB_ADDR *pdbapol, double *pdWind, UINT_PTR dwData);

/* static */
HRESULT CNativeObject::QtSearch (
	HPROJECT hPr, LPCSTR pcName, double *pdWindow, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
{
// alle betreffenden Objekte aufsammeln
CObjectHandleMap Map;

	RETURN_FAILED_HRESULT(QtWindow (hPr, pdWindow, (QTWINDOWACTIONPROC)QtTestRecord, KPKRD, (UINT_PTR)&Map));

// und enumerieren
HRESULT hr = S_OK;

	for (CObjectHandleMap::iterator it = Map.begin(); it != Map.end(); ++it) {
		hr = trias_connectfilter::EnumObjectsWrapper(hPr, (*it), pFcn, dwData);
		if (S_OK != hr) 
			break;	// abgebrochen oder Fehler
	}
	return hr;
}

// Kantenbaum nach allen das Fenster berührenden Objekten absuchen
long __cdecl HtTestRecord (DB_ADDR *pdbapol, double *pdWind, UINT_PTR dwData);
long __cdecl HtTestRecordApprox (DB_ADDR *pdbapol, double *pdWind, UINT_PTR dwData);
long HtTestRecordExact (DB_ADDR *pdbapol, double *pdWind, UINT_PTR dwData, BOOL fExact);

/* static */
HRESULT CNativeObject::HtSearch (
	HPROJECT hPr, LPCSTR pcName, double *pdWindow, 
	HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData, BOOL fExact)
{
// alle betreffenden Objekte aufsammeln
CObjectHandleMap Map;
HTWINDOWACTIONPROC Fcn = fExact ? (HTWINDOWACTIONPROC)HtTestRecord : (HTWINDOWACTIONPROC)HtTestRecordApprox;

	RETURN_FAILED_HRESULT(HtWindow (hPr, pdWindow, Fcn, KCONT, (UINT_PTR)&Map));

// und enumerieren
HRESULT hr = S_OK;

	for (CObjectHandleMap::iterator it = Map.begin(); it != Map.end(); ++it) {
		hr = trias_connectfilter::EnumObjectsWrapper(hPr, (*it), pFcn, dwData);
		if (S_OK != hr) 
			break;	// abgebrochen oder Fehler
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Funktion wird bei de GeometrieRecherche für jeden gefundenen Punktsatz gerufen
long __cdecl QtTestRecord (DB_ADDR *pdbapol, double *pdWind, UINT_PTR dwData)
{
DB_ADDR dbavgo(pdbapol->db_no);
ErrCode RC;
struct pol pol;
struct vgo vgo;

// Anfangswerte:
	dbavgo.file_no = VGO;

// Punktobjekt gefunden: 
	__Read (*pdbapol, pol);
	dbavgo.rec_no = pol.zpvgo;

// Objektnummern ins dynamische Feld speichern
	do {
		__Read (dbavgo, vgo);
		reinterpret_cast<CObjectHandleMap *>(dwData) -> insert(vgo.zvgoo);
//		DBASSERT (GetKomplexObjects (pdbapol->db_no, vgo.zvgoo, fenr.feon));
#pragma MESSAGE("TODO: Komplexobjekte bei der Geometrierecherche (Punkte) behandeln!")
	} while ((dbavgo.rec_no = vgo.znvgo) > 0);
	return EC_OKAY;
} 

///////////////////////////////////////////////////////////////////////////////
// Funktion wird bei de GeometrieRecherche für jeden gefundenen Kantensatz gerufen
long __cdecl HtTestRecord (DB_ADDR *pDBA, double *pdWind, UINT_PTR dwData)
{
	return HtTestRecordExact (pDBA, pdWind, dwData, TRUE);
}

long __cdecl HtTestRecordApprox (DB_ADDR *pDBA, double *pdWind, UINT_PTR dwData)
{
	return HtTestRecordExact (pDBA, pdWind, dwData, FALSE);
}

long __cdecl HtTestRecordExact (DB_ADDR *pDBA, double *pdWind, UINT_PTR dwData, BOOL fExact)
{
BOOL fFound = FALSE;
DB_ADDR dbavgo(pDBA->db_no);
ErrCode RC;
struct vgo vgo;

// Kante oder Masche (Fläche) gefunden: Kante 
	if (pDBA -> file_no == KAL) {
	struct kal kal;

		__Read (*pDBA, kal);
		if (kal.zkvgo == 0) 
			return EC_OKAY;	// Kante gehört zu Flächenumrandung

	// Container umschließt völlig Kantencontainer
		if ((pdWind[XMIN] <= kal.kcont.kxmin) && (pdWind[XMAX] >= kal.kcont.kxmax) && 
		    (pdWind[YMIN] <= kal.kcont.kymin) && (pdWind[YMAX] >= kal.kcont.kymax)) 
		{
			fFound = TRUE;
		}

	// FNDKA rufen
		if (!fFound) 
		{
			DBASSERT (FindKante (pDBA->db_no, pDBA, pdWind, &fFound));
		} 

		if (fFound) {
			dbavgo.file_no = VGO;
			dbavgo.rec_no = kal.zkvgo;

		// Objektnummern der Kante ins dynamische Feld speichern
			do {
				__Read (dbavgo, vgo);
				reinterpret_cast<CObjectHandleMap *>(dwData) -> insert(vgo.zvgoo);
//				DBASSERT (GetKomplexObjects (pDBA->db_no, vgo.zvgoo, fenr.feon));
#pragma MESSAGE("TODO: Komplexobjekte bei der Geometrierecherche (Kante) behandeln!")
			} while ((dbavgo.rec_no = vgo.znvgo) > 0);
		}
		return EC_OKAY;		/* Ende Kante */

	} else if (pDBA -> file_no == MAL) {		/* Masche */
	struct mal mal;

		if (fExact) {
		// nur wenn exakt gesucht werden soll
			DBASSERT (FindMasche (pDBA->db_no, pDBA, pdWind, &fFound));
		} else
			fFound = TRUE;

		if (fFound) {
		// gefundene Objektnummer ins Feld einspeichern
			__Read (*pDBA, mal);
			reinterpret_cast<CObjectHandleMap *>(dwData) -> insert(mal.zmvgo);
//			DBASSERT (GetKomplexObjects (pDBA->db_no, mal.zmvgo, fenr.feon));
#pragma MESSAGE("TODO: Komplexobjekte bei der Geometrierecherche (Fläche) behandeln!")
		}
		return EC_OKAY;		/* Ende Masche (Flaeche) */
	
	} else 	// falsche Liste
		return (long)db_error ((short)EKAMA, 3023);
	
	return EC_OKAY;
} 

///////////////////////////////////////////////////////////////////////////////
// Prüfen, ob Kante in Fenster liegt
long FindKante (HPROJECT hPr, DB_ADDR *pdbakal, double *pdWindow, BOOL *pfFound)
{
bool fLast = false;
DB_ADDR dbakpl(hPr), dbaspl(hPr);
struct kal kal;
struct kpl kpl;
ErrCode RC;

// Anfangswerte setzen
	TX_ASSERT(pdbakal -> file_no == KAL);
	dbakpl.file_no = KPL;
	*pfFound = FALSE;

// Beginn der Kante, Kantensatz einlesen
	__Read(*pdbakal, kal);

long zspl = kal.zksp;		// Verweis auf Stützpunktliste
	
// Koordinaten von ZAP
	dbakpl.rec_no = kal.zap;
	__Read(dbakpl, kpl);

double ix1 = kpl.pkrd.kpx;	// erster Stützpunkt (Knotenpunkt)
double iy1 = kpl.pkrd.kpy;

	if (VERSION05000010 <= LocGetDBVersion(hPr)) {
	struct longspl SPLSatz;

		dbaspl.file_no = SPL_NEW;
		do {
			if (zspl > 0) {		// SPL
				dbaspl.rec_no = zspl;
				__Read (dbaspl, SPLSatz);

				for (long i = 0; i < NUMSPLCOORDS; i++) {
					if (0 == SPLSatz.spxl[i] && 0 == SPLSatz.spyl[i]) {
						TX_ASSERT(i > 0);				// wenigstens eine Koordinate muß in diesem Satz sein
						TX_ASSERT(0 == SPLSatz.znspl);	// muß der letzte der Kette sein
						break;	/* for */				// SPLSatz nicht vollständig gefüllt
					}

				double ix2 = SPLSatz.spxl[i];
				double iy2 = SPLSatz.spyl[i];

				// Prüfen, ob Stützpunktstrecke im Container
					*pfFound = PointInContainer (ix1, iy1, ix2, iy2, pdWindow[XMIN], pdWindow[YMIN], pdWindow[XMAX], pdWindow[YMAX]);
					if (*pfFound) return EC_OKAY;	// Objekt im Container

					ix1 = ix2;	// neuer erster Punkt
					iy1 = iy2;
				}
				zspl = SPLSatz.znspl;
			}
			else {				// ZEP
				dbakpl.rec_no = kal.zep;
				__Read (dbakpl, kpl);

			// Prüfen, ob Stützpunktstrecke im Container
				*pfFound = PointInContainer (ix1, iy1, kpl.pkrd.kpx, kpl.pkrd.kpy, pdWindow[XMIN], pdWindow[YMIN], pdWindow[XMAX], pdWindow[YMAX]);
				if (*pfFound) return EC_OKAY;	// Objekt im Container 

				fLast = true;		// Ende der Kante erreicht, do ... while abbrechen
			}

		} while (!fLast);	// noch weitere Punkte vorhanden
		
		return EC_OKAY;
	}
	
// ansonsten mit alter Struktur arbeiten
// Beginn Kante, Koordinaten des nächsten Stützpunktes bzw. des ZEP
struct spl spl;

	dbaspl.file_no = SPL_OLD;
	do {
	double ix2, iy2;

		if (zspl > 0) {		/* SPL */
			dbaspl.rec_no = zspl;
			__Read (dbaspl, spl);
			ix2 = spl.spx;
			iy2 = spl.spy;
			zspl = spl.znsp;
		}
		else {			/* ZEP */
			dbakpl.rec_no = kal.zep;
			__Read (dbakpl, kpl);
			ix2 = kpl.pkrd.kpx;
			iy2 = kpl.pkrd.kpy;
			fLast = true;		/* Ende Kante */
		}

	// Prüfen, ob Stützpunktstrecke im Container
		*pfFound = PointInContainer (ix1, iy1, ix2, iy2, pdWindow[XMIN], pdWindow[YMIN], pdWindow[XMAX], pdWindow[YMAX]);
		if (*pfFound) return EC_OKAY;	// Objekt im Container

		ix1 = ix2;
		iy1 = iy2;

	} while (!fLast);	// noch weitere Punkte vorhanden

	return EC_OKAY;
}

BOOL PointInContainer (
	double ix1, double iy1, double ix2, double iy2, 
	double ixc1, double iyc1, double ixc3, double iyc3)
{
double idx, idy;
double rdx, rdxa, rdxb, rdy, rdya, rdyb, rpa, rpb;

// ein Streckenendpunkt im Container ?
	if ((ix1 >= ixc1) && (ix1 <= ixc3) && (iy1 >= iyc1) && (iy1 <= iyc3))
		return TRUE;	// AnfangsPunkt auf Rand oder im Container

	if ((ix2 >= ixc1) && (ix2 <= ixc3) && (iy2 >= iyc1) && (iy2 <= iyc3))
		return TRUE;	// EndPunkt auf Rand oder im Container 

// beide Streckenendpunkte links, rechts, oberhalb, unterhalb Container ?
	if ((ix1 < ixc1) && (ix2 < ixc1))
		return FALSE;	// X der Strecke < X des Containers

	if ((ix1 > ixc3) && (ix2 > ixc3)) 
		return FALSE;	// X der Strecke > X des Containers

	if ((iy1 < iyc1) && (iy2 < iyc1))
		return FALSE;	// Y der Strecke < Y des Containers

	if ((iy1 > iyc3) && (iy2 > iyc3))
		return FALSE;	// Y der Strecke > Y des Containers
	
	idx = ix2 - ix1;
	idy = iy2 - iy1;

// Fall, wenn DX oder DY = 0 (Strecke senkrecht bzw. waagerecht)
	if ((idx == 0) || (idy == 0))
		return TRUE;	// Strecke auf Rand oder durch Container

// Strecke schneidet Teilstueck des Containers ab oder nicht
// Pinzip: gegenseitige Lage eines Punktepaares und einer Geraden,
//         die durch 2 Punkte bestimmt ist !
	rdx = idx;
	rdy = idy;
	if (sign(idx) == sign(idy)) {
		rdxa = ixc3 - ix1;
		rdya = iyc1 - iy1;
		rdxb = ixc1 - ix1;
		rdyb = iyc3 - iy1;
	}
	else {
		rdxa = ixc1 - ix1;
		rdya = iyc1 - iy1;
		rdxb = ixc3 - ix1;
		rdyb = iyc3 - iy1;
	}
	rpa = rdx*rdya - rdy*rdxa;
	rpb = rdx*rdyb - rdy*rdxb;
	if(rpa == 0.0 || rpb == 0.0)
		return TRUE;	// Strecke auf Eckpunkt des Containers

	if (sign(rpa) == sign(rpb))
		return FALSE;	// Strecke außerhalb des Containers

	return TRUE;		// Strecke durch Container
}

///////////////////////////////////////////////////////////////////////////////
// Prüfen, ob Kante in Fenster liegt
long FindMasche (HPROJECT hPr, DB_ADDR *pdbamal, double *pdWind, BOOL *pfFound)
{
DB_ADDR dbakal(hPr), dbakfm(hPr);
ErrCode RC;
struct kal kal;
struct kfm kfm;
struct mal mal;

// Anfangswerte setzen
	*pfFound = FALSE;
	dbakfm.file_no = KFM;
	dbakal.file_no = KAL;

// Prüfung, ob Container völlig Flächencontainer umschließt
	__Read (*pdbamal, mal);
	if ((pdWind[XMIN] <= mal.mcont.mxmin) && (pdWind[XMAX] >= mal.mcont.mxmax) && 
		(pdWind[YMIN] <= mal.mcont.mymin) && (pdWind[YMAX] >= mal.mcont.mymax)) 
	{
		*pfFound = TRUE;
		return EC_OKAY;
	}

// Prüfung, ob Flächenumrandung Container schneidet
	dbakfm.rec_no = mal.zmkfm;
	do {
		__Read (dbakfm, kfm);
		dbakal.rec_no = labs (kfm.zkfmk);	// Zeiger auf KAL (+oder-)
		__Read (dbakal, kal);

	// Container umschließt völlig Kantencontainer
		if ((pdWind[XMIN] <= kal.kcont.kxmin) && (pdWind[XMAX] >= kal.kcont.kxmax) && 
		    (pdWind[YMIN] <= kal.kcont.kymin) && (pdWind[YMAX] >= kal.kcont.kymax)) 
		{
			*pfFound = TRUE;
			return EC_OKAY;
		}

	// Bearbeitung einer Kante
		DBASSERT (FindKante (hPr, &dbakal, pdWind, pfFound));
		if (*pfFound) return EC_OKAY;

	} while ((dbakfm.rec_no = kfm.znkfm) != 0);	/* Zeiger wieder auf KFM */

// Prüfung, ob 1 Eckpunkt des Containers in Flächenumrandung
long lPktLage;

	DBASSERT (PointInPolygon (hPr, pdWind[XMIN], pdWind[YMIN], mal.zmvgo, &lPktLage));
	if (lPktLage == 0)
		*pfFound = TRUE;

	return EC_OKAY;
} 

HRESULT PointInPolygon (HPROJECT hPr, double xp, double yp, long lONr, long *plPktLage)
{
HRESULT hr = S_OK;
vector<double> vX, vY;
vector<unsigned long> vKnt;
CNativeObject Object (hPr, lONr);

	if (!Object) return E_UNEXPECTED;
	RETURN_FAILED_HRESULT(hr = Object.GetAreaGeometry ("Geometry", vX, vY, vKnt));

	ASSERT(vX.size() == vY.size());
	ASSERT(vKnt.size() > 0);

size_t j = 0;

	for (size_t iKCnt = 0; iKCnt < vKnt.size(); ++iKCnt) {
	// alle Konturen separat behandeln
#if defined(_FORCE_LEGACY_CODE)
	long lResult = PunktLage (xp, yp, &vX[j], &vY[j], vKnt[iKCnt]);

		j += vKnt[iKCnt];	// nächste Kontur
		if (0 == iKCnt) {
		// Außenkontur
			if (lResult < 0) {
				*plPktLage = 1;		// Punkt außerhalb äußerer Umrandung
				return S_OK;
			} else
				*plPktLage = 0;		// Punkt innerhalb äußerer Umrandung
		} else if (lResult > 0) {
		// Innenkontur
			*plPktLage = -1L;		// Punkt im Loch
			return S_OK;
		}
#else
	bool fInner = false;
	HRESULT hr = PunktLage (xp, yp, &vX[j], &vY[j], vKnt[iKCnt], fInner);

		j += vKnt[iKCnt];	// nächste Kontur
		if (0 == iKCnt) {
		// Außenkontur
			if (!fInner) {
				*plPktLage = 1;		// Punkt außerhalb äußerer Umrandung
				return S_OK;
			} else
				*plPktLage = 0;		// Punkt innerhalb äußerer Umrandung
		} else if (fInner) {
		// Innenkontur
			*plPktLage = -1L;		// Punkt im Loch
			return S_OK;
		}
#endif // defined(_FORCE_LEGACY_CODE)
	} 
	return S_OK;
} 

#if defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// das das folgende nochmal passieren mußte !
inline long Lage (double px, double py, double ax, double ay, double ex, double ey)
{
	return ARITHIF((px - ax) * (ay - ey) + (py - ay) * (ex - ax));
}

long PunktLage (double dXp, double dYp, double *x, double *y, long lCnt)
{
long int i = 0, idi, igptnl_v, j;
long int idf = 0, idx = 0, igpth = 0;

double nx;
double x0 = 0, xs0 = 0,	xs1 = 0, xs2 = 0, xv = 0;
double y0 = 0, ys0 = 0,	ys1 = 0, ys2 = 0, yv = 0;

long ist = 2;	// da hier keiner durchblickt diese Festlegung

	if (ist >= 0L) {
		igptnl_v = -1L;		// X-Komponente naechstgelegener SP
		idx = 0x7FFFFFFF;	// Index naechstgelegener SP 
		idi = 0L;		// Index aktueller SP 
	}
		
	if (ist < 0L) {
	// Polygonzug nachgeladen
		igptnl_v = igpth;
		if (y0 - dYp < 0L)  goto L_100;
		if (y0 - dYp > 0L)  goto L_300;
		if (x0 - dXp < 0L)  goto L_600;
		if (x0 - dXp == 0L) goto L_700;
		if (x0 >= idx)      goto L_600;

	// P0 neuer naechstliegender SP
		idx = x0;

	// Flag SP ermittelt setzen 
		idf = 1L;
		xs0 = xv;
		ys0 = yv;
		xs1 = x0;
		ys1 = y0;
		xs2 = x[0L];
		ys2 = y[0L];
	}

L_600:
	if (++i > lCnt) goto L_500;	// Endetest 
	
// Lagetest EP(I) zur x-achsenparallelen Geraden gx 
L_601:
	switch (ARITHIF(y[i - 1L] - dYp)){
	case -1: goto L_100;
	case  0: goto L_200;
	case  1: goto L_300;
	}


/* -- unterhalb gx */
L_100:
	if (++i > lCnt) goto L_500;	// Endetest

// Lagetest EP(I) zu gx 
	switch (ARITHIF(y[i - 1L] - dYp)){
	case -1: goto L_100;
	case  0: goto L_200;
	case  1: goto L_400;
	}

// EP(I) auf gx, Lagetest EP(I) auf Strahl, Lagetest EP(I) zu XP 
L_200:
	switch (ARITHIF(x[i - 1L] - dXp)){
	case -1: goto L_600;
	case  0: goto L_700;
	case  1: goto L_201;
	}

// SP rechts von IDI
L_201:
	if (x[i - 1L] >= idx) goto L_600;
	if (ist <= 0L) {
		idf = 1L;	// Flag SP gefunden setzen
		if (i <= 1L) {
			if(ist >= 0L)
				idf = 2L;	// XS0, YS0 nicht belegt
			else {
				xs0 = x0;
				ys0 = y0;
			}
		}
		else {
			xs0 = x[i - 2L];
			ys0 = y[i - 2L];
		}
		xs1 = x[i - 1L];
		ys1 = y[i - 1L];
		xs2 = x[i];
		ys2 = y[i];
	}

// SP(I) neuer naechstgelegener SP
	idx = x[i - 1L];
	idi = i;
	goto L_600;

// oberhalb gx
L_300:
	if (++i > lCnt) goto L_500;	// Endetest

// Lagetest EP(I) zu gx
	switch (ARITHIF (y[i - 1L] - dYp)) {
	case -1: goto L_400;
	case  0: goto L_200;
	case  1: goto L_300;
	}

// Schnitt mit gx, Lagetest SP auf Strahl, Y(I-1)#YP#Y(I)
L_400:
	if (i > 1) {
		if (x[i - 2L] < x[i - 1L]) {
		// SP nicht naechstgel.
			if (x[i - 1L] <= dXp || x[i - 2L] >= idx)
				goto L_601;
		}
		else {
		///  SP nicht naechstgel.
			if (x[i - 2L] < dXp || x[i - 1L] > idx)
				goto L_601;
		}

	// SP berechnen und Lagetest, Y(I)#Y(I-1)
		nx = (x[i - 2L] * (y[i - 1L] - dYp) - x[i - 1L] * (y[i - 2L] - dYp)) / (y[i - 1L] - y[i - 2L]);
	}
	else {
		if (x0 < x[0L]) {
		// SP nicht naechstgel.
			if (x[0L] <= dXp || x0 >= idx)
				goto L_601;
		}
		else {
		// SP nicht naechstgel.
			if (x0 < dXp || x[0L] > idx)
				goto L_601;
		}

	// SP berechnen und Lagetest, Y(1)#Y0 
		nx = (x0 * (y[0L] - dYp) - x[0L] * (y0 - dYp)) / (y[0L] - y0);
	}
	switch (ARITHIF(nx - dXp)) {
	case -1: goto L_601;
	case  0: goto L_700;
	case  1: goto L_401;
	}

// SP rechts von IDI
L_401:
	if (nx >= idx) goto L_601;
	if (ist <= 0L) {
		idf = 1L;	// Flag SP gefunden setzen
		if (i <= 1L) {
			if (ist >= 0L)
				idf = 2L;	// XS0,YS0 nicht belegt
			else {
				xs0 = x0;
				ys0 = y0;
			}
		}
		else {
			xs0 = x[i - 2L];
			ys0 = y[i - 2L];
		}
		xs1 = x[i - 1L];
		ys1 = y[i - 1L];
		xs2 = x[i];
		ys2 = y[i];
	}

// SP ist neuer naechstgelegener SP
	idx = nx;
	idi = i;
	goto L_601;

// abschließender Inzidenztest
L_500:
	if (ist <= -2L) {
		ist = 0L;
	
		if(idf <= 0L)	goto L_799;	// kein SP
		if(idf >= 2L) {
		// PS belegen 
			xs0 = x[lCnt - 2L];
			ys0 = y[lCnt - 2L];
		}
	
		if (ys1 != dYp) {
		// SP kein Polygoneckpunkt
			igptnl_v = Lage (dXp, dYp, xs0, ys0, xs1, ys1);
			goto L_799;
		}

	// Lage P zu STR(I-1,I)
		i = Lage (dXp, dYp, xs0, ys0, xs1, dYp);

	// Lage P zu STR(I,I+1)
		igptnl_v = Lage (dXp, dYp, xs1, dYp, xs2, ys2);
		if (Lage (xs2, ys2, xs0, ys0, xs1, dYp) >= 0L) {
		// konvexe Ecke
			if (i < igptnl_v) igptnl_v = i;
		}
		else {
		// konkave Ecke */
			if (i > igptnl_v) igptnl_v = i;
		}
		goto L_799;
	}
	if (ist <= 0L) {
		ist = -1L;
		xv = x[lCnt - 2L];
		yv = y[lCnt - 2L];
		x0 = x[lCnt - 1L];
		y0 = y[lCnt - 1L];
		goto L_799;
	}

// keine Inzidenz Strahl - Polygonflaeche 
	if (idi <= 0L) goto L_799;

// SP kein Polygoneckpunkt
	if (y[idi - 1L] != dYp) {
		igptnl_v = Lage (dXp, dYp, x[idi - 2L], y[idi - 2L], x[idi - 1L], y[idi - 1L]);
		goto L_799;
	}
	j = idi - 1L;

// SP ist Polygonendpunkt
	if (j <= 0L) j = lCnt - 1;

// Lage P zu STR(I-1,I)
	i = Lage (dXp, dYp, x[j - 1L], y[j - 1L], x[idi - 1L], dYp);

// Lage P zu STR(I,I+1)
	igptnl_v = Lage (dXp, dYp, x[idi - 1L], dYp, x[idi], y[idi]);

	if(Lage (x[idi], y[idi], x[j - 1L], y[j - 1L], x[idi - 1L], dYp) >= 0L) 
	{
	// konvexe Ecke
		if (i < igptnl_v) igptnl_v = i;
	}
	else {
	// konkave Ecke 
		if (i > igptnl_v) igptnl_v = i;
	}
	goto L_799;

// SP auf Polygonzug
L_700:
	igptnl_v = 0L;
	if (ist < 0L) ist = 0L;

L_799:
	igpth = igptnl_v;
	return( igptnl_v );
}

#else

// PunktLage: tribute to Wolfgang Moertl

// Lage des Punktes (x,y) bezüglich des geschlossenen Polygonzuges (pX, pY) der Länge lCnt;
// für bInner == true, liegt der Punkt innerhalb der eingeschlossenen Fläche bzw. auf deren Kontur
// return-Werte sind
//   S_OK     Entscheidung konnte getroffen werden
//   E_FAIL   Polygonzug ist entartet bzw. nicht geschlossen (bInner unbestimmt)

HRESULT PunktLage (double x, double y, double* pX, double* pY, long lCnt, bool& bInner)
{
	bInner = false;
	if (NULL == pX || NULL == pY)
		return E_POINTER;

	if (lCnt <= 3 ||								// Polygonzug ist entartet
		pX[0] != pX[lCnt-1] || pY[0] != pY[lCnt-1])	// Polygonzug ist nicht geschlossen
	{
		return E_FAIL;
	}

// Koordinaten der waagerechten Testlinie
double xa = x, ya = y, xe = DBL_MAX, ye = y;

long lCutCnt = 0;	// Zähler für echte Schnitte der Testlinie mit dem Polygonzug
long j = lCnt - 2;	// Index des letzten Polygonpunktes, von dem bekannt ist, daß
					// er nicht auf der Testlinie liegt

	while (0 == TurnDirection (xa, ya, xe, ye, pX[j], pY[j])) {
		if (--j < 0)
			return E_FAIL;	// entarteter Polygonzug, d.h. alle Punkte liegen auf einer Geraden,
	}						// die mit der Trägergeraden der Testlinie identsch ist

int iTD1, iTD2, iTD3;		// return-Werte von TurnDirection()

	for (long k = 0; k < lCnt-1; k++) {
	// Test, ob Punkt auf der Kontur der eingeschlossenen Fläche liegt
		if (0 == TurnDirection (pX[k], pY[k], pX[k+1], pY[k+1], x, y))
		{
			bInner = true;
			return S_OK;	// Punkt liegt auf der Kontur
		}

	// Im nachfolgenden if-Zweig wird der Fall behandelt, daß der nächste Punkt P[k] nicht auf
	// der waagerechten Testlinie liegt.
	// Liegt P[k] auf der Testlinie (else-Zweig), wird P[k] i.a. ignoriert.
	// Liegt jedoch der zu testende Punkt im Dreieck P[k-1], P[k], P[k+1], ergibt sich durch das
	// Weglassen von P[k] eine Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
		if (0 != TurnDirection (xa, ya, xe, ye, pX[k], pY[k])) {
		// Zähler lCutCnt inkrementieren, wenn echter Schnitt vorliegt, d. h. P[k] und P[j]
		// auf verschiedenen Seiten der Testlinie liegen
			if (Intersection (pX[k], pY[k], pX[j], pY[j], xa, ya, xe, ye))
				lCutCnt++;
			j = k;
		}
		else {	// P[k] liegt auf der Testlinie
			iTD1 = TurnDirection (pX[k], pY[k], pX[k+1], pY[k+1], x, y);

			if (k > 0) {
				iTD2 = TurnDirection (pX[k-1], pY[k-1], pX[k], pY[k], x, y);
				iTD3 = TurnDirection (pX[k+1], pY[k+1], pX[k-1], pY[k-1], x, y);
			}
			else {   // k == 0
				iTD2 = TurnDirection (pX[lCnt-2], pY[lCnt-2], pX[0], pY[0], x, y);
				iTD3 = TurnDirection (pX[1], pY[1], pX[lCnt-2], pY[lCnt-2], x, y);
			}

			if (iTD1 >= 0 && iTD2 >= 0 && iTD3 >= 0) {	// konvexe Ecke des Polygonzuges:
				bInner = true;							// Punkt liegt innerhalb
				return S_OK;
			}

			if (iTD1 <= 0 && iTD2 <= 0 && iTD3 <= 0) {	// konkave Ecke des Polygonzuges:
				bInner = false;							// Punkt liegt außerhalb
				return S_OK;
			}
		}
	}

	// ungerade Schnittanzahl bedeutet Enthaltensein
	if (lCutCnt % 2) 
		bInner = true;

	return S_OK;
} // PunktLage

///////////////////////////////////////////////////////////////////////////////
// das Gleiche nochmal, aber für ConnectionFilter
HRESULT PunktLage (double x, double y, CONNECTFILTEREX *pFilter, bool& bInner)
{
	bInner = false;
	if (NULL == pFilter)
		return E_POINTER;

// Koordinaten der waagerechten Testlinie
double xa = x, ya = y, xe = DBL_MAX, ye = y;
double *pX = pFilter->m_pX;
double *pY = pFilter->m_pY;
long lCnt = pFilter->m_lCnt;

	using namespace trias_gist;

long lCutCnt = 0;	// Zähler für echte Schnitte der Testlinie mit dem Polygonzug
GiSTcursor *cursor = pFilter->m_prsTree->Search(xa, xe, ya, ye);
auto_ptr<GiSTentry> entry (cursor->Next());

	while (NULL != entry.get()) {
	// für alle betroffenen Stützstrecken
	GiSTpage k = entry->Ptr();

	// Test, ob Punkt auf der Kontur der eingeschlossenen Fläche liegt
		if (0 == TurnDirection (pX[k-1], pY[k-1], pX[k], pY[k], x, y)) {
			bInner = true;
			return S_OK;	// Punkt liegt auf der Kontur
		}

	// Test, ob Schnitt vorliegt, oder sich lediglich die Container der 
	// zu untersuchenden Kante und des Teststrahls überlappen und die Kante
	// nicht direkt auf dem Teststrahl liegt
		if (Intersection (pX[k-1], pY[k-1], pX[k], pY[k], xa, ya, xe, ye) &&
			(pY[k-1] != y || pY[k] != y)) 
		{
		// wenn genau ein Endpunkt der zu untersuchenden Kante über dem 
		// Teststrahl liegt, dann wird der Schnitt gezählt
			if ((pY[k-1] > y && pY[k] <= y) || (pY[k-1] <= y && pY[k] > y))
				++lCutCnt;
		}

	// der Nächste bitte
		entry = auto_ptr<GiSTentry>(cursor->Next());
	}

	// ungerade Schnittanzahl bedeutet Enthaltensein
	if (lCutCnt % 2) 
		bInner = true;

	return S_OK;
} // PunktLage

#endif // _FORCE_LEGACY_CODE

} // namespace trias_nativeobject
