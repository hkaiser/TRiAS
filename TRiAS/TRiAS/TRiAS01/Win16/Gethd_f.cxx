/* Lesen eines Datensatzes des DB-Headers                       */
/* File: GETHD_F.C                                              */

#include "trias01p.hxx"
#include "syncdb.hxx"

#include <pshpack1.h>

typedef union tagHEADER {
	struct head head;
	struct fhead headf;
} HEADER;

#include <poppack.h>

#ifdef unix
EXPORT INT
gethd_ (text, len, key, l_text)
long l_text;
char *text;
INT *key;              /* Schluessel */
long *len;              /* Laenge des Textes */
#endif

#if defined(msdos) || defined(_WINDOWS)
extern "C" 
long FUNCTYPE EXPORT01 gethd_ (HPROJECT hPr, char *text, int l_text, long *len, long *key, long *pFlags)
#endif
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

HEADER h;
DB_ADDR dba(hPr);
register long text_len;

#if defined(msdos) || defined(_WINDOWS)
// Feld ausnullen
	memset (text, '\0', l_text);
#endif
/* Satz suchen */
	dba.file_no = HEAD;
	if (z_keyfind (&dba, HDIDN, key) != S_OKAY) 
		return ((INT)db_status);

/* 1. Satz einlesen */
	if (z_readrec (&dba, &h.head) != S_OKAY) return ((INT)db_status);

	if (NULL != pFlags) 
		*pFlags = h.head.hdrflags;		// Flags kopieren

	if ((text_len = strlen (h.head.text)) > *len) {
	/* Feld zu klein, wenigstens Anfang kopieren */
		strncpy (text, h.head.text, (int)*len);
		return ((INT)db_error (S_BADLEN, GETHD_F));
	}
	strncpy (text, h.head.text, (int)*len);
        
/* weitere Saetze einlesen */
	dba.file_no = FHEAD;
	dba.rec_no = h.head.zntext;

	while (dba.rec_no != 0) {
		if (z_readrec (&dba, &h.headf) != S_OKAY) return ((INT)db_status);
		if ((unsigned int)(text_len + strlen (h.headf.textf)) > (unsigned int)(*len)) {
		/* Feld zu klein, wenigstens voll machen */
			strncpy (&text[text_len], h.headf.textf, (int)(*len-text_len));
			return (db_error (S_BADLEN, GETHD_F));
		}
		strncpy (&text[text_len], h.headf.textf, strlen (h.headf.textf));
		text_len = strlen (text);
		dba.rec_no = h.headf.ztextf;
	}

/* Feld mit Leerzeichen auffuellen */
	if (*len > text_len+1)
		memset (&text[text_len], ' ', (int)(*len-text_len));

return ((INT)(db_status = S_OKAY));
}
