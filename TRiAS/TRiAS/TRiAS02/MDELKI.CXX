// Loeschen eines Identifikatoreintrages aus der PBD
// File: MDELKI.C

#include "trias02p.hxx"

#include <idtdb.h>

long FUNCTYPE mdelki (HPROJECT hPr, long rec) 
{
ErrCode RC;
DB_ADDR dbaIDL (hPr);
long Next;
long PBDVersion = GetDBVersion (hPr);

	dbaIDL.file_no = MID;
	dbaIDL.rec_no = rec;

	if (PBDVersion <= PBDVERSION03000001) {
	struct mid_001 MID001Satz;

		__Read (dbaIDL, MID001Satz);
		Next = MID001Satz.zntxti;
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct mid MIDSatz;

		__Read (dbaIDL, MIDSatz);
		Next = MIDSatz.zntxti;
	}

// Satz mit TextFolgeSätzen freigeben 
	__Dispose (dbaIDL);
	DBASSERT (FreeText (hPr, MIF, Next));

return S_OKAY;
}


