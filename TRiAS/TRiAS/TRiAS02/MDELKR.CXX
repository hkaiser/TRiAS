// Loeschen eines Relationseintrages aus der PBD
// File: MDELKR.CXX

#include "trias02p.hxx"

#include <idtdb.h>

extern "C" 
long FUNCTYPE mdelkr (HPROJECT hPr, long rec) 
{
long RC;
DB_ADDR dbaREL (hPr);
long Next;
long PBDVersion = GetDBVersion (hPr);
ErrInstall EI ((ErrCode)S_INVADDR);

	dbaREL.file_no = MRL;
	dbaREL.rec_no = rec;

	if (PBDVersion <= PBDVERSION03000001) {
	struct mrl_001 MRL001Satz;

		if ((RC = z_readrec (&dbaREL, &MRL001Satz)) != S_OKAY) {
		// LeseFehler
		long EC = RC;

			if (EC == S_INVADDR) 
				return db_error (S_BADRECREL, RC_MDELKR);
			return EC;
		}
		Next = MRL001Satz.zntxtr;
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct mrl MRLSatz;

		if ((RC = z_readrec (&dbaREL, &MRLSatz)) != S_OKAY) {
		// LeseFehler
		long EC = RC;

			if (EC == S_INVADDR) 
				return db_error (S_BADRECREL, RC_MDELKR);
			return EC;
		}
		Next = MRLSatz.zntxtr;
	}

// Satz mit TextFolgeSätzen freigeben 
	__Dispose (dbaREL);
	DBASSERT (FreeText (hPr, MRF, Next));

return S_OKAY;
}

