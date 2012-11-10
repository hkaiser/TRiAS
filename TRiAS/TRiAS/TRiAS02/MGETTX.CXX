// Einlesen eines Langtextes in einem Beschreibungssatz der PBD
// File: MGETTX.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

extern "C" 
long FUNCTYPE mgettx (HPROJECT hPr, short Typ, long Satz, char *pText) 
{
DB_ADDR dba (hPr), dbaF (hPr);
long RC;
long Next;
short ReadLen;
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
		return (long)db_error (S_BADTYP, RC_MGETTX);
	}

	if (PBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;
	struct fdesc_001 DBF001Satz;

		__Read (dba, DB001Satz);
		Next = DB001Satz.Next;
		DB001Satz.Next = 0;	// Stringende sicher ausnullen

		strcpy (pText, DB001Satz.LText);
		ReadLen = 76;

		while (Next != 0) {
			__Read (dbaF, DBF001Satz);
			Next = DBF001Satz.FNext;
			DBF001Satz.FNext = 0;	// Stringende sicher ausnullen
			strcpy (&pText[ReadLen], DBF001Satz.FLText);
			ReadLen += 120;
		}
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct desc DBSatz;
	struct fdesc DBFSatz;

		__Read (dba, DBSatz);
		Next = DBSatz.Next;
		DBSatz.Next = 0;	// Stringende sicher ausnullen
	
		strcpy (pText, DBSatz.LText);
		ReadLen = 76;

		while (Next != 0) {
			dbaF.rec_no = Next;
			__Read (dbaF, DBFSatz);
			Next = DBFSatz.FNext;
			DBFSatz.FNext = 0;	// Stringende sicher ausnullen
			strcpy (&pText[ReadLen], DBFSatz.FLText);
			ReadLen += 136;
		}
	}

return S_OKAY;
}

