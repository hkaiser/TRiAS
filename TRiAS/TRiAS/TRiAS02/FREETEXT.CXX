// Freigeben der FolgeSätze eines LangTextes
// File: FREETEXT.C

#include "trias02p.hxx"

#include <idtdb.h>

// Freigeben der FolgeSätze eines LangTextes ----------------------------------
long FUNCTYPE FreeText (HPROJECT hPr, short FileNo, long RecNo) 
{
struct fdesc FSatz;
struct fdesc_001 F001Satz;
DB_ADDR dba (hPr);
ErrCode RC;
long PBDVersion = GetDBVersion(hPr);

	dba.file_no = FileNo;
	if (PBDVersion <= PBDVERSION03000001) {
		while (RecNo != 0) {
			dba.rec_no = RecNo;
			__Read (dba, F001Satz);
			RecNo = F001Satz.FNext;
			__Dispose (dba);
		}
	} else if (PBDVersion >= PBDVERSION03000002) {
		while (RecNo != 0) {
			dba.rec_no = RecNo;
			__Read (dba, FSatz);
			RecNo = FSatz.FNext;
			__Dispose (dba);
		}
	}

return S_OKAY;
}

