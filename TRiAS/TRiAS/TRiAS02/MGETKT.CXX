// Einlesen des Kurztextes zu einem Beschreibungssatz 
// File: MGETKT.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

// allgemeine Schnittstelle zum Lesen eines KurzTextes ------------------------
extern "C" 
long FUNCTYPE mgetkt (HPROJECT hPr, short Typ, long Satz, char *pText) 
{
	switch (tolower (Typ)) {
	case 'i':
		return mgetktall (hPr, Satz, pText, MID);
	case 'm':
		return mgetktall (hPr, Satz, pText, MMK);
	case 'r':
		return mgetktall (hPr, Satz, pText, MRL);
	default:
		return db_error (S_BADTYP, RC_MGETKT);
	}
}

// Einlesen des Kurztextes zu einem Identifikatorsatz -------------------------
long FUNCTYPE mgetktall (HPROJECT hPr, long Satz, char *pText, short FileNo) 
{
DB_ADDR dba (hPr);
long RC;
long PBDVersion = GetDBVersion (hPr);

// gesuchten Satz einlesen
	dba.file_no = FileNo;
	dba.rec_no = Satz;

	if (PBDVersion <= PBDVERSION03000001) {
	struct desc_001 DB001Satz;

		__Read (dba, DB001Satz);
	// Daten kopieren
		if (pText) {
			strncpy (pText, DB001Satz.SText, 16);
			pText[16] = '\0';
		}
	} else if (PBDVersion >= PBDVERSION03000002) {
	struct desc DBSatz;

		__Read (dba, DBSatz);
	// Daten kopieren
		if (pText) {
			strncpy (pText, DBSatz.SText, 32);
			pText[32] = '\0';
		}
	}

return S_OKAY;
} 

