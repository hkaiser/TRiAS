// Bestimmen der Laenge eines Langtextes in einem Beschreibungssatz der PBD
// File: MGETL.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

extern "C" 
long FUNCTYPE mgetl (HPROJECT hPr, short Typ, long Satz, long *pLen) 
{
DB_ADDR dba (hPr), dbaF (hPr);
long RC;
long Next;
long PBDVersion = GetDBVersion (hPr);

	dba.rec_no = Satz;
	switch (tolower (Typ)) {
	case 'i':
		dba.file_no = MID;
		dbaF.file_no = MIF;
		break;
	case 'm':
		dba.file_no = MMK;
		dbaF.file_no = MKF;
		break;
	case 'r':
		dba.file_no = MRL;
		dbaF.file_no = MRF;
		break;
	case 'w':
		dba.file_no = MMW;
		dbaF.file_no = MMF;
		break;
	default:
		return (long)db_error (S_BADTYP, RC_MGETL);
	}

	if (PBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;
	struct fdesc_001 DBF001Satz;

		__Read (dba, DB001Satz);
		Next = DB001Satz.Next;
		DB001Satz.Next = 0;	// Stringende sicher ausnullen

		*pLen = strlen (DB001Satz.LText);

		while (Next != 0) {
			__Read (dbaF, DBF001Satz);
			Next = DBF001Satz.FNext;
			DBF001Satz.FNext = 0;	// Stringende sicher ausnullen
			*pLen += strlen (DBF001Satz.FLText);
		}	
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct desc DBSatz;
	struct fdesc DBFSatz;

		__Read (dba, DBSatz);

		Next = DBSatz.Next;
		DBSatz.Next = 0;	// Stringende sicher ausnullen

		*pLen = strlen (DBSatz.LText);

		while (Next != 0) {
			dbaF.rec_no = Next;
			__Read (dbaF, DBFSatz);
			Next = DBFSatz.FNext;
			DBFSatz.FNext = 0;	// Stringende sicher ausnullen
			*pLen += strlen (DBFSatz.FLText);
		}	
	}

return S_OKAY;
}

