// Generieren eines LinienObjektes 
// File: PUTLOBJ.C

#include "trias02p.hxx"

#include <math.h>

// Generiert ein neues Linienobjekt --------------------------------------------
extern "C" 
long EXPORT02 FUNCTYPE PutLineObject (
	HPROJECT hPr, long *pOBL, long Ident, long *pX, long *pY, long iNum) 
{
struct obl OBLSatz;
DB_ADDR_OBL dbaOBL(hPr);
ErrCode RC;                 // FehlerVariable
long newON = -1L;
long Kante = 0L;	// neue KantenNummer

	DEX_SetDirtyGeoDB (true);

// Objektsatz generieren
//	dbaOBL.file_no = OBL;
	if (*pOBL <= 0) {
	// neuen ObjektSatz generieren
		memset (&OBLSatz, '\0', sizeof (OBLSatz));

		if (VERSION0500000E <= GetDBVersion (hPr))	// evtl. GUID generieren
			CoCreateGuid (&OBLSatz.guid);

		__New (dbaOBL, OBLSatz);
		newON = dbaOBL.rec_no;

	// Identifikator bei Bedarf in IDL eintragen
		DBASSERT (PutIdent (hPr, newON, Ident, TPLinie, &OBLSatz.zoid));
	} else {
	// bestehenden ObjektSatz einlesen
		newON = dbaOBL.rec_no = *pOBL;
		__Read (dbaOBL, OBLSatz);

	// IdentifikatorSatz richten
		DBASSERT(VerifyIdent(hPr, newON, OBLSatz.zoid, TPLinie));

	// evtl. existierende LinienGeometrie löschen
		if (OBLSatz.zovol) {
			DBASSERT (delgil (hPr, *pOBL));
			OBLSatz.zovol = 0;
		}
	}

// neuen KantenSatz generieren
	DBASSERT (PutKante (hPr, pX, pY, iNum, &Kante, NULL));
	DBASSERT (LinkKante (hPr, newON, Kante, &OBLSatz.zovol));
	
	__Write (dbaOBL, OBLSatz);	// ObjektSatz nochmal wegschreiben

// ObjektNummer liefern
	*pOBL = newON;
	return S_OKAY;
}


// Schreibt KantenSatz mit allgemeiner Information ----------------------------
extern "C" 
long FUNCTYPE PutKante (
	HPROJECT hPr, long *pX, long *pY, long iNum, long *pKNr, struct kcont *pCont)
{
ErrCode RC;
struct kal KALSatz;
DB_ADDR dbaKAL(hPr);

// KantenSatz anlegen
	dbaKAL.file_no = KAL;
	memset (&KALSatz, '\0', sizeof (struct kal));
	__New (dbaKAL, KALSatz);

	KALSatz.kcont.kxmin = MAXKOORD;
	KALSatz.kcont.kymin = MAXKOORD;

// Anfangs-/Endpunkt der Kante anlegen
	DBASSERT (PutKnoten (hPr, pX[0], pY[0], dbaKAL.rec_no, &KALSatz.zap));
	UpdateContainer (&KALSatz.kcont, pX[0], pY[0]);
	if (pX[0] != pX[iNum-1] || pY[0] != pY[iNum-1]) {
		DBASSERT (PutKnoten (hPr, pX[iNum-1], pY[iNum-1], -dbaKAL.rec_no, &KALSatz.zep));
		UpdateContainer (&KALSatz.kcont, pX[iNum-1], pY[iNum-1]);
	} else {
		DBASSERT (ChainKnoten (hPr, KALSatz.zap, -dbaKAL.rec_no));
		KALSatz.zep = KALSatz.zap;
	}

// Stützpunktliste anlegen
	DBASSERT (PutPoints (hPr, &pX[1], &pY[1], iNum-2, &KALSatz.zksp, &KALSatz.kcont));

// Anzahl der Stützpunkte und Winkel schreiben
	KALSatz.asp = iNum-2;
	KALSatz.wi = Winkel (pX[iNum-1], pY[iNum-1], pX[iNum-2], pY[iNum-2]);

// erstmal wegschreiben
	__Write (dbaKAL, KALSatz);
	*pKNr = dbaKAL.rec_no;

// evtl. Container kopieren
	if (pCont) 
		memcpy (pCont, &KALSatz.kcont, sizeof (KALSatz.kcont));
	return (long)S_OKAY;
}


// Generiert einen neuen KnotenPunktSatz --------------------------------------
long FUNCTYPE PutKnoten (HPROJECT hPr, long x, long y, long zKPL, long *pKAL)
{
ErrCode RC;
struct kpl KPLSatz;
DB_ADDR dbaKPL(hPr);

	*pKAL = 0;		// ausnullen für alle Fälle

// Satz in der KPL neu anlegen
	dbaKPL.file_no = KPL;
	memset (&KPLSatz, '\0', sizeof (struct kpl));

	KPLSatz.pkrd.kpx = x;
	KPLSatz.pkrd.kpy = y;
	DBASSERT (PutLink (hPr, KFK, &KPLSatz.zkpkfk, zKPL));

	__New (dbaKPL, KPLSatz);	// Knoten anlegen

	*pKAL = dbaKPL.rec_no;	// neuer KnotenPunkt
	return (long)S_OKAY;
}


// Fall geschlossene Kontur (zap == zep) --------------------------------------
long FUNCTYPE ChainKnoten (HPROJECT hPr, long lKPL, long lKante)
{
ErrCode RC;
struct kpl KPLSatz;
DB_ADDR dbaKPL(hPr);

// KnotenpunktSatz einlesen
	dbaKPL.file_no = KPL;
	dbaKPL.rec_no = lKPL;
	__Read (dbaKPL, KPLSatz);

// letzten Knoten zusätzlich verketten
	DBASSERT (PutLink (hPr, KFM, &KPLSatz.zkpkfk, lKante));
	__Write (dbaKPL, KPLSatz);
	return S_OKAY;
}


// Anlegen der Stützpunktfolge einer Kante ------------------------------------
extern "C" 
long FUNCTYPE PutPoints (
	HPROJECT hPr, long *pX, long *pY, long iNum, long *pKAL, struct kcont *pCont)
{
ErrCode RC;

// ausnullen des ersten Zeigers
	*pKAL = 0;

	if (VERSION05000010 <= GetDBVersion(hPr)) {
	DB_ADDR dbaSPL(hPr);

	// Neuen Satz in die StützpunktFolge am Anfang einfügen
	// (Koordinaten von hinten bearbeiten)
		dbaSPL.file_no = SPL_NEW;

		for (long i = iNum -1; i >= 0; /**/) {
		struct longspl SPLSatz;

			for (long lCnt = i % NUMSPLCOORDS; lCnt >= 0; lCnt--, i--) {
				SPLSatz.spxl[lCnt] = pX[i];
				SPLSatz.spyl[lCnt] = pY[i];
				UpdateContainer (pCont, pX[i], pY[i]);
			}
			SPLSatz.znspl = *pKAL;

			__New (dbaSPL, SPLSatz);
			*pKAL = dbaSPL.rec_no;
		}
		return S_OKAY;
	}

// ansonsten mit alter Struktur arbeiten
	for (long i = iNum -1; i >= 0; i--) {
		DBASSERT (PutPoint (hPr, pX[i], pY[i], pKAL));
		UpdateContainer (pCont, pX[i], pY[i]);
	}
	return S_OKAY;
}

// Anlegen eines StützPunktSatzes mit Rückverkettung --------------------------
long FUNCTYPE PutPoint (HPROJECT hPr, long x, long y, long *pSPL)
{
ErrCode RC;
struct spl SPLSatz;
DB_ADDR dbaSPL(hPr);

// Neuen Satz in die StützpunktFolge am Anfang einfügen
	dbaSPL.file_no = SPL_OLD;

	SPLSatz.spx = x;
	SPLSatz.spy = y;
	SPLSatz.znsp = *pSPL;
	__New (dbaSPL, SPLSatz);

	*pSPL = dbaSPL.rec_no;
	return S_OKAY;
}

// Generieren der Verkettung einer Kante vom und zum Objekt -------------------
long FUNCTYPE LinkKante (HPROJECT hPr, long lONr, long lKante, long *povol)
{
ErrCode RC;
struct kal KALSatz;
DB_ADDR dbaKAL(hPr);

// Generieren der Verbindung Objekt -> Kante
	DBASSERT (PutLink (hPr, VOL, povol, lKante));

// Generieren der Verkettung Kante -> Objekt
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = labs (lKante);
	__Read (dbaKAL, KALSatz);

	DBASSERT (PutLink (hPr, VGO, &KALSatz.zkvgo, lONr));
	__Write (dbaKAL, KALSatz);

return S_OKAY;
}


// Container aufbauen ---------------------------------------------------------
void FUNCTYPE UpdateContainer (struct kcont *pCont, long x, long y)
{
	if (pCont -> kxmin > x) pCont -> kxmin = x;
	if (pCont -> kxmax < x) pCont -> kxmax = x;
	if (pCont -> kymin > y) pCont -> kymin = y;
	if (pCont -> kymax < y) pCont -> kymax = y;
}


// Winkel zwischen AnfangsPunkt und 2. Punkt einer Kante berechnen ------------
long FUNCTYPE Winkel (long x1, long y1, long x2, long y2)
{
double rwin;

	if (x2 == x1 && y2 == y1) 
		return 16000L;		// per Definition ist Winkel 0

	rwin = 1.0 + 
	       ((double)(x2 - x1) / (double)(labs (x2 - x1) + labs (y2 - y1)));

return (long)fabs (rwin * 16000.0);
} 

