// Wegschreiben eines LangTextes zu einem PBD-Beschreibungssatz
// File: MPUTTX.C

#include "trias02p.hxx"

#include <ctype.h>
#include <idtdb.h>

// allgemeine Schnittstelle zum Schreiben eines Langtextes --------------------
long FUNCTYPE EXPORT02 mputtx (HPROJECT hPr, short Typ, long Satz, char *pText) 
{
	switch (tolower (Typ)) {
	case 'i':
		return mputtxi (hPr, Satz, pText);
	case 'm':
		return mputtxm (hPr, Satz, pText);
	case 'r':
		return mputtxr (hPr, Satz, pText);
	case 'w':
		return mputtxw (hPr, Satz, pText);
	default:
		return db_error (S_BADTYP, RC_MPUTTXT);
	}
}

// Schreiben des Langtextes für einen IdententifikatorSatz --------------------
long FUNCTYPE mputtxi (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MID;
	dba.rec_no = Rec;
	return mputtxt (&dba, Text);
}


// Schreiben des Langtextes für einen MerkmalsSatz ----------------------------
long FUNCTYPE mputtxm (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MMK;
	dba.rec_no = Rec;
	return mputtxt (&dba, Text);
}

// Schreiben des Langtextes für einen RelationsSatz ---------------------------
long FUNCTYPE mputtxr (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MRL;
	dba.rec_no = Rec;
	return mputtxt (&dba, Text);
}

long FUNCTYPE mputtxw (HPROJECT hPr, long Rec, char *Text) 
{
DB_ADDR dba (hPr);

	dba.file_no = MMW;
	dba.rec_no = Rec;
	return mputtxt (&dba, Text);
}


// Die Struktur der Beschreibungssätze (Identifikator-, Merkmals- und 
// Relations-Beschreibungssätze) in Bezug auf Kurz- und Langtext ist identisch.
// Es wird daher an dieser Stelle der Einfachheit halber ein wenig getrickst.

long FUNCTYPE mputtxt (DB_ADDR *pDBA, char *Text) 
{
DB_ADDR dbaF(pDBA -> db_no), dba(pDBA -> db_no);
char inBuff[140];			// max. Größe der Beschreibungsätze
struct fdesc fBuff;			// FortSetzungsSatz
struct desc *pDesc = (struct desc *)inBuff;	// Zeiger auf allg. Struktur
struct desc_001 *pDesc001 = (struct desc_001 *)inBuff;
ErrCode RC;
long Prev;
int Len, WrittenLen;
long PBDVersion = GetDBVersion (pDBA -> db_no);
int fTextLen;

// wenn Text nicht gegeben ist, dann wieder raus
	if (Text == NULL) return S_OKAY;

// Satz aus PBD einlesen
	__Read (*pDBA, *pDesc);

// erste 76 Bytes des LangTextes einkopieren
	if (PBDVersion <= PBDVERSION03000001) {
		memset (pDesc001 -> LText, '\0', 76);
		strncpy (pDesc001 -> LText, Text, 76);
		pDesc001 -> Next = 0;
		fTextLen = 120;
	} else if (PBDVersion >= PBDVERSION03000002) {
		memset (pDesc -> LText, '\0', 76);
		strncpy (pDesc -> LText, Text, 76);
		pDesc -> Next = 0;
		fTextLen = 136;
	}

	Len = strlen (Text);
	WrittenLen = (Len > 76) ? 76 : Len;
	DBASSERT (z_writerec (pDBA, pDesc));

	if (Len > WrittenLen) {
	// ersten Fortsetzungssatz anlegen
		memset (fBuff.FLText, '\0', fTextLen);
		dbaF.file_no = pDBA -> file_no +1;	// FortsetzungsSatz
		strncpy (fBuff.FLText, &Text[WrittenLen], fTextLen);
		if (PBDVersion <= PBDVERSION03000001) {
			((struct fdesc_001 *)&fBuff) -> FNext = 0;
			__New (dbaF, fBuff);
			pDesc001 -> Next = dbaF.rec_no;
			DBASSERT (z_writerec (pDBA, pDesc001));
		} else if (PBDVersion >= PBDVERSION03000002) {
			fBuff.FNext = 0;
			__New (dbaF, fBuff);
			pDesc -> Next = dbaF.rec_no;
			DBASSERT (z_writerec (pDBA, pDesc));
		}
		Prev = dbaF.rec_no;

	// Länge des behandelten Strings berechnen
		WrittenLen = min (WrittenLen + fTextLen, Len);
	}

// weitere Fortsetzungsätze nach Bedarf schreiben
	dba.file_no = dbaF.file_no;
	while (Len > WrittenLen) {
	// nächster Satz
	long lNext = 0;

		memset (fBuff.FLText, '\0', fTextLen);
		strncpy (fBuff.FLText, &Text[WrittenLen], fTextLen);
		if (PBDVersion <= PBDVERSION03000001)
			((struct fdesc_001 *)&fBuff) -> FNext = 0;
		else if (PBDVersion >= PBDVERSION03000002)
			fBuff.FNext = 0;
		__New (dbaF, fBuff);
		lNext = dbaF.rec_no;

	// vorherigen Satz komplettieren
		dba.rec_no = Prev;
		Prev = lNext;
		__Read (dba, fBuff);
		if (PBDVersion <= PBDVERSION03000001)
			((struct fdesc_001 *)&fBuff) -> FNext = dbaF.rec_no;
		else if (PBDVersion >= PBDVERSION03000002)
			fBuff.FNext = dbaF.rec_no;
		__Write (dba, fBuff);

	// Länge des behandelten Strings neu berechnen
		WrittenLen = min (WrittenLen + fTextLen, Len);
	}

return S_OKAY;
}
