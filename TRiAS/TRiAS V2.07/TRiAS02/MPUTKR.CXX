// Einspeichern eines Relationssatzes in die IDENTSDB
// File: MPUTKR.C

#include "trias02p.hxx"

#include <idtdb.h>

extern "C" 
long FUNCTYPE mputkr (HPROJECT hPr, long RCode, short reltyp, long *RecNo) 
{
DB_ADDR dbaMRL (hPr);
long RC;
long PBDVersion = GetDBVersion (hPr);

	dbaMRL.file_no = MRL;
	*RecNo = 0;	// für alle Fälle

	{
	ErrInstall EI (WC_NOTFOUND);
	
		if ((RC = z_keyfind (&dbaMRL, PRIREL, &RCode)) == S_OKAY) {
		// Satz existiert schon
			DBASSERT (mdelkr (hPr, dbaMRL.rec_no));	// alten Satz löschen
		} else if (RC != S_NOTFOUND)
		// Fehler beim Suchen des RelSatzes
			return RC;		
	}
	
	if (PBDVersion <= PBD030000001) {
	struct mrl_001 MRL001Satz;

		memset (&MRL001Satz, '\0', sizeof(MRL001Satz));
	// neuen Satz generieren
		MRL001Satz.prirel = RCode;
		MRL001Satz.reltyp = reltyp;
		__New (dbaMRL, MRL001Satz);
	} else if (PBDVersion >= PBD030000002) {
	struct mrl MRLSatz;

		memset (&MRLSatz, '\0', sizeof(MRLSatz));
	// neuen Satz generieren
		MRLSatz.prirel = RCode;
		MRLSatz.reltyp = reltyp;
		__New (dbaMRL, MRLSatz);
	}

// Resultat setzen
	*RecNo = dbaMRL.rec_no;

return S_OKAY;
}
