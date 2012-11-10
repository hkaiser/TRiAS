// Loeschen der Geometrie einer Kante einer Flaeche ---------------------------
// File: DELKANF.C

#include "trias02p.hxx"

#define RoutCD	2065

long FUNCTYPE delkanf (HPROJECT hPr, long Kante, long FNo) 
{
struct kal KALSatz;
DB_ADDR dbaKAL(hPr);
ErrCode RC;	// FehlerCode
long *pFirst, *pSecond;

// KantenSatz einlesen
	dbaKAL.file_no = KAL;
	dbaKAL.rec_no = labs (Kante);
	__Read (dbaKAL, KALSatz);

// Unterscheidung linke/rechte Fläche
	if (Kante > 0) {
		pFirst = &KALSatz.zlm;
		pSecond = &KALSatz.zrm;
	} else if (Kante < 0) {
		pFirst = &KALSatz.zrm;
		pSecond = &KALSatz.zlm;
	} else
		return db_error (S_SYSERR, RoutCD);

// FlächenSatz aus Verbindung der MaschenListen (linke/rechte) löschen 
	if ((RC = (ErrCode)DelLink (hPr, VZO, pFirst, FNo)) != S_OKAY) {
	// Falls nichts gefunden wurde, dann kann es sein, daß die Fläche 
	// (Loch) falsch orientiert ist (ohne Verschnitt geladen). Daher 
	// versuchen wir es eben von hinten.
		if (RC == S_NOTFOUND) {
		long *ptmp = pFirst;

			pFirst = pSecond;
			pSecond = ptmp;
			DBASSERT (DelLink (hPr, VZO, pFirst, FNo));
		} else
			return RC;
	}
	if (*pFirst != 0) {
	// war nicht die letzte Fläche
		__Write (dbaKAL, KALSatz);
	} else if (*pSecond != 0) {
	// die Kante mißbraucht einer von der anderen Seite
		__Write (dbaKAL, KALSatz);
	} else if (KALSatz.zkvgo != 0) {
	// Kante wird von LinienObjekt benutzt
		__Write (dbaKAL, KALSatz);
	} else {
	// Kante muß gelöscht werden, Stützpunktfolge löschen
		DBASSERT (DeletePoints (hPr, KALSatz.zksp));
	// Anfangs und Endpunkt der Kante behandeln
		DBASSERT (DeleteNode (hPr, KALSatz.zap, labs (Kante)));
		DBASSERT (DeleteNode (hPr, KALSatz.zep, labs (Kante)));
	// KantenSatz freigeben 
		__Dispose (dbaKAL);
	}

return S_OKAY;
}

