// Wegschreiben eines KurzTextes zu einem PBD-Beschreibungssatz
// File: MPUTKT.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

// allgemeine Schnittstelle zum schreiben eines Kurztextes --------------------
extern "C" 
long FUNCTYPE mputkt (HPROJECT hPr, short Typ, long Satz, char *pText) 
{
	switch (tolower (Typ)) {
	case 'i':
		return mputkti (hPr, Satz, pText);
	case 'm':
		return mputktm (hPr, Satz, pText);
	case 'r':
		return mputktr (hPr, Satz, pText);
	default:
		return db_error (S_BADTYP, RC_MPUTKT);
	}
}

// KurzText für IdentifikatorSatz schreiben -----------------------------------
long FUNCTYPE mputkti (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MID;
	dba.rec_no = Rec;
	return mputktxt (&dba, Text);
}

// Kurztext für MerkmalsSatz schreiben ----------------------------------------
long FUNCTYPE mputktm (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MMK;
	dba.rec_no = Rec;
	return mputktxt (&dba, Text);
}

// Kurztext für Relationssatz schreiben ---------------------------------------
long FUNCTYPE mputktr (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MRL;
	dba.rec_no = Rec;
	return mputktxt (&dba, Text);
}


// Die Struktur der Beschreibungssätze (Identifikator-, Merkmals- und 
// Relations-Beschreibungssätze) in Bezug auf Kurz- und Langtext ist identisch.
// Es wird daher an dieser Stelle der Einfachheit halber ein wenig getrickst.

long FUNCTYPE mputktxt (DB_ADDR *pDBA, char *Text) 
{
char inBuff[140];			// max. Größe der Beschreibungsätze
struct desc *pDesc = (struct desc *)inBuff;	// Zeiger auf allg. Struktur
ErrCode RC;
long PBDVersion = GetDBVersion (pDBA -> db_no);

// Satz aus PBD einlesen
	__Read (*pDBA, *pDesc);

// KurzText einkopieren
	if (PBDVersion <= PBD030000001) 
		strncpy (pDesc -> SText, Text, 16);
	else if (PBDVersion >= PBD030000002) 
		strncpy (pDesc -> SText, Text, 32);

	return z_writerec (pDBA, pDesc);	// Satz wieder wegschreiben
}
