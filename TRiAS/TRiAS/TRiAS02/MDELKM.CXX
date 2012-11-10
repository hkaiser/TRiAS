// Loeschen eines Merkmalseintrages aus der PBD
// File: MDELKM.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

extern "C" 
long FUNCTYPE mdelkm (HPROJECT hPr, long rec) 
{
long RC;
DB_ADDR dbaMMK (hPr);
long Next;
long iWBis0, iWBis1;
short iTyp;
long PBDVersion = GetDBVersion (hPr);

	dbaMMK.file_no = MMK;
	dbaMMK.rec_no = rec;

	if (PBDVersion <= PBDVERSION03000001) {
	struct mmk_001 MMK001Satz;

		__Read (dbaMMK, MMK001Satz);
		Next = MMK001Satz.zntxtm;
		iTyp = MMK001Satz.mtyp[0];
		iWBis0 = MMK001Satz.wbis.iwbis[0];
		iWBis1 = MMK001Satz.wbis.iwbis[1];
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct mmk MMKSatz;

		__Read (dbaMMK, MMKSatz);
		Next = MMKSatz.zntxtm;
		iTyp = MMKSatz.mtyp[0];
		iWBis0 = MMKSatz.wbis.iwbis[0];
		iWBis1 = MMKSatz.wbis.iwbis[1];
	}

// Satz mit TextFolgeSätzen und evtl. MerkmalsWertFolgesätzen freigeben 
	if (iTyp == 'i' && iWBis0 == -1) {
	// solange MerkmalswertFolgesätze vorhanden 
	long NextM;
	DB_ADDR dbaMMW (hPr);

		NextM = iWBis1;			// erster WerteFolgeSatz
		dbaMMW.file_no = MMW;

		if (PBDVersion <= PBDVERSION03000001) {
		struct mmw_001 MMW001Satz;

			while (NextM != 0) {
				dbaMMW.rec_no = NextM;
				__Read (dbaMMW, MMW001Satz);
	
			// TextFolgeSätze freigeben
				DBASSERT (FreeText (hPr, MMF, MMW001Satz.zntxtw));

			// nächster WerteFolgeSatz
				NextM = MMW001Satz.znwert;
				__Dispose (dbaMMW);		// Satz freigeben
			}
		} else if (PBDVersion >= PBDVERSION03000002) {
		struct mmw MMWSatz;

			while (NextM != 0) {
				dbaMMW.rec_no = NextM;
				__Read (dbaMMW, MMWSatz);
	
			// TextFolgeSätze freigeben
				DBASSERT (FreeText (hPr, MMF, MMWSatz.zntxtw));

			// nächster WerteFolgeSatz
				NextM = MMWSatz.znwert;
				__Dispose (dbaMMW);		// Satz freigeben
			}
		}

	}
	__Dispose (dbaMMK);
	DBASSERT (FreeText (hPr, MKF, Next));

return S_OKAY;
}

