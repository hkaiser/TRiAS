// Einspeichern eines Merkmalssatzes in die IDENTSDB
// File: MPUTKM.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

extern "C" 
long FUNCTYPE mputkm (HPROJECT hPr, long MCode, short MTyp, long WF, 
		      long *von, long *bis, long *RecNo) 
{
DB_ADDR dbaMMK (hPr);
long RC;
long PBDVersion = GetDBVersion (hPr);

	dbaMMK.file_no = MMK;
	*RecNo = 0;	// für alle Fälle

	{
	ErrInstall EI (WC_NOTFOUND);	// Fehler unterdrücken
	
		if ((RC = z_keyfind (&dbaMMK, MKS, &MCode)) == S_OKAY) {
		// Satz existiert schon
	
			DBASSERT (mdelkm (hPr, dbaMMK.rec_no));	// alten Satz löschen
		} else if (RC != S_NOTFOUND)	// Fehler beim suchen des MKSatzes
			return RC;		
	}
	
	if (PBDVersion <= PBDVERSION03000001) {
	// neuen Satz generieren
	struct mmk_001 MMK001Satz;

		memset (&MMK001Satz, '\0', sizeof(MMK001Satz));
		MMK001Satz.mks = MCode;
		MMK001Satz.wfakm = WF;
		MMK001Satz.mtyp[0] = (char)MTyp;
		memcpy (&MMK001Satz.wvon, von, sizeof(long)*2);
		memcpy (&MMK001Satz.wbis, bis, sizeof(long)*2);
		__New (dbaMMK, MMK001Satz);
	} else if (PBDVersion >= PBDVERSION03000002) {
	// neuen Satz generieren
	struct mmk MMKSatz;

		memset (&MMKSatz, '\0', sizeof(MMKSatz));
		MMKSatz.mks = MCode;
		MMKSatz.wfakm = WF;
		memcpy (MMKSatz.mtyp, &MTyp, sizeof(short));
		memcpy (&MMKSatz.wvon, von, sizeof(long)*2);
		memcpy (&MMKSatz.wbis, bis, sizeof(long)*2);
		__New (dbaMMK, MMKSatz);
	}

// Resultat setzen
	*RecNo = dbaMMK.rec_no;

return S_OKAY;
}
