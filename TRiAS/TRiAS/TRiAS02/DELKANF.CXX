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

// Unterscheidung linke/rechte Fl�che
	if (Kante > 0) {
		pFirst = &KALSatz.zlm;
		pSecond = &KALSatz.zrm;
	} else if (Kante < 0) {
		pFirst = &KALSatz.zrm;
		pSecond = &KALSatz.zlm;
	} else
		return db_error (S_SYSERR, RoutCD);

// Fl�chenSatz aus Verbindung der MaschenListen (linke/rechte) l�schen 
	if ((RC = (ErrCode)DelLink (hPr, VZO, pFirst, FNo)) != S_OKAY) {
	// Falls nichts gefunden wurde, dann kann es sein, da� die Fl�che 
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
	// war nicht die letzte Fl�che
		__Write (dbaKAL, KALSatz);
	} else if (*pSecond != 0) {
	// die Kante mi�braucht einer von der anderen Seite
		__Write (dbaKAL, KALSatz);
	} else if (KALSatz.zkvgo != 0) {
	// Kante wird von LinienObjekt benutzt
		__Write (dbaKAL, KALSatz);
	} else {
	// Kante mu� gel�scht werden, St�tzpunktfolge l�schen
		DBASSERT (DeletePoints (hPr, KALSatz.zksp));
	// Anfangs und Endpunkt der Kante behandeln
		DBASSERT (DeleteNode (hPr, KALSatz.zap, labs (Kante)));
		DBASSERT (DeleteNode (hPr, KALSatz.zep, labs (Kante)));
	// KantenSatz freigeben 
		__Dispose (dbaKAL);
	}

return S_OKAY;
}

