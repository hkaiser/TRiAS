/* Lesen eines Datensatzes des DB-Headers                       */
/* File: GETHD_F.C                                              */

#include "trias01p.hxx"
#include "syncdb.hxx"

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

struct head head;
struct fhead headf;
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
	if (z_readrec (&dba, &head) != S_OKAY) return ((INT)db_status);

	if (NULL != pFlags) 
		*pFlags = head.hdrflags;		// Flags kopieren

	if ((text_len = strlen (head.text)) > *len) {
	/* Feld zu klein, wenigstens Anfang kopieren */
		strncpy (text, head.text, (int)*len);
		return ((INT)db_error (S_BADLEN, GETHD_F));
	}
	strncpy (text, head.text, (int)*len);
        
/* weitere Saetze einlesen */
	dba.file_no = FHEAD;
	dba.rec_no = head.zntext;

	while (dba.rec_no != 0) {
		if (z_readrec (&dba, &headf) != S_OKAY) return ((INT)db_status);
		if ((unsigned int)(text_len + strlen (headf.textf)) > (unsigned int)(*len)) {
		/* Feld zu klein, wenigstens voll machen */
			strncpy (&text[text_len], headf.textf, (int)(*len-text_len));
			return (db_error (S_BADLEN, GETHD_F));
		}
		strncpy (&text[text_len], headf.textf, strlen (headf.textf));
		text_len = strlen (text);
		dba.rec_no = headf.ztextf;
	}

/* Feld mit Leerzeichen auffuellen */
	if (*len > text_len+1)
		memset (&text[text_len], ' ', (int)(*len-text_len));

return ((INT)(db_status = S_OKAY));
}
