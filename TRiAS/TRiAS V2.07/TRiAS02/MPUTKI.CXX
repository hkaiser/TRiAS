// Einspeichern eines Identifikatorsatzes in die IDENTSDB
// File: MPUTKI.C

#include "trias02p.hxx"

#include <idtdb.h>

extern "C" 
long FUNCTYPE mputki (HPROJECT hPr, long Ident, long *RecNo) 
{
DB_ADDR dbaMID (hPr);
ErrCode RC;
long PBDVersion = GetDBVersion (hPr);

	dbaMID.file_no = MID;
	*RecNo = 0;	// für alle Fälle
	{
	ErrInstall EI (WC_NOTFOUND);
	
		if ((RC = (ErrCode)z_keyfind (&dbaMID, IDS, &Ident)) == S_OKAY) {
		// Satz existiert schon

			DBASSERT (mdelki (hPr, dbaMID.rec_no));	// alten Satz löschen
		} else if (RC != S_NOTFOUND) // Fehler beim suchen des IDSatzes
			return RC;		
	}

	if (PBDVersion <= PBD030000001) {
	struct mid_001 MID001Satz;

	// neuen Satz generieren
		memset (&MID001Satz, '\0', sizeof(MID001Satz));
		MID001Satz.ids = Ident;
		__New (dbaMID, MID001Satz);
	} else if (PBDVersion >= PBD030000002) {
	struct mid MIDSatz;

	// neuen Satz generieren
		memset (&MIDSatz, '\0', sizeof(MIDSatz));
		MIDSatz.ids = Ident;
		__New (dbaMID, MIDSatz);
	}

// Resultat setzen
	*RecNo = dbaMID.rec_no;

return S_OKAY;
}
