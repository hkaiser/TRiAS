// Loeschen der Geometrie eines Linienobjektes --------------------------------
// File: DELGIL.C

#include "trias02p.hxx"

#define RoutCD	2050

extern "C" long EXPORT02 FUNCTYPE delgil (HPROJECT hPr, long ON) 
{
struct obl OBLSatz;
struct vol VOLSatz;
DB_ADDR_OBL dbaOBL(hPr);
DB_ADDR dbaVOL(hPr);
ErrCode RC;	// FehlerCode

// Objektsatz einlesen
//	dbaOBL.file_no = OBL;
	dbaOBL.rec_no = ON;
	__Read (dbaOBL, OBLSatz);

// VerbindungsListe Objekt -> Kante
	dbaVOL.file_no = VOL;
	dbaVOL.rec_no = OBLSatz.zovol;

// Rückverkettung auflösen, Kantenfolge zerlegen
	while (dbaVOL.rec_no != 0) {
		__Read (dbaVOL, VOLSatz);		// VerbindungsSatz lesen
	// Kante löschen
		DBASSERT (delkan (hPr, labs (VOLSatz.zvolk), ON));
	// VerbindungsSatz freigeben
		__Dispose (dbaVOL);
	// nächste Kante
		dbaVOL.rec_no = VOLSatz.znvol;
	}

// ObjektSatz korrigieren
	OBLSatz.zovol = 0;	// keine Geometrie mehr
	__Write (dbaOBL, OBLSatz);

return S_OKAY;
}
