/* Schreiben eines Datensatzes in den DB-Header                 */
/* File: PUTHD_F.C                                              */

#include "trias01p.hxx"
#include "syncdb.hxx"

#ifdef vms
#include "vmstypes.h"
#endif

#ifdef unix
EXPORT INT
puthd_ (s_text, len, key, l_text)
char *key, *s_text;
long l_text;
long *len;              /* Laenge des Textes */
#endif

#if defined(msdos) || defined(_WINDOWS)
extern "C" 
long FUNCTYPE EXPORT01 puthd_ (HPROJECT hPr, char *s_text, int l_text, long *len, long *key, long lFlags)
#endif

#ifdef vms
EXPORT INT
puthd_ (s_text, len, s_key)
struct str_par *s_key, *s_text;
long *len;              /* Laenge des Textes */
#endif
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

INT_FUNC *s_ntfnd, *dummy;
register char *cptr;
DB_ADDR dba(hPr);
char *text;
#ifdef vms
char *key = s_key->str;
#endif

	if ((text = new char [*len+1]) == NULL) 
		return (db_error (S_NOMEMORY, GETHD_F));

#if defined(msdos) || defined(_WINDOWS)
	strncpy (text, s_text, (int)*len);
	text[strlen(s_text)] = '\0';
#endif
#ifdef unix
	strncpy (text, s_text, (int)*len);
#endif
#ifdef vms
	strncpy (text, s_text->str, (int)*len);
#endif

	if ((cptr = strrlchr (text, ' ')) != NULL) *cptr = '\0';

/* Fehlermeldung ignorieren */
	err_install (S_NOTFOUND, E_IGNORE, &s_ntfnd);
	dba.file_no = HEAD;
	if (z_keyfind (&dba, HDIDN, key) != S_OKAY) {
		if (db_status == S_NOTFOUND) {
		/* Schluessel existiert noch nicht --> Neueinspeichern */
			if (store_head (hPr, key, *len, text, lFlags) != S_OKAY) {
				delete text;
				err_install (S_NOTFOUND, s_ntfnd, &dummy);
				return ((INT)db_status);
			}
		} else {
			delete text;
			return ((INT)db_status);
		}
	} else {
	/* Schluessel existiert bereits */
	/* alten Satz loeschen */
		if (delete_head ((char *)key, &dba) != S_OKAY ||
				store_head (hPr, key, *len, text, lFlags) != S_OKAY) {
			delete text;
			err_install (S_NOTFOUND, s_ntfnd, &dummy);
			return ((INT)db_status);
		}
	}
	err_install (S_NOTFOUND, s_ntfnd, &dummy);
	delete text;

return ((INT)(db_status = S_OKAY));
}

int FUNCTYPE store_head (HPROJECT hPr, long *key, long len, char *text, long lFlags)
{
short dbhead, dbheadf;
struct head head;
struct fhead headf;
DB_ADDR dba(hPr);
long satznr;
register FLAG first;
register long text_len;

	dba.file_no = HEAD;
	dba.rec_no = 0;
	dbhead = record_table[HEAD].rt_file;
	dbheadf = record_table[FHEAD].rt_file;

/* ersten Satz anfordern */
	if (db_pzalloc (dbhead, &satznr) != S_OKAY) return (db_status);
	dba.rec_no = satznr;

/* Satz bereitstellen */        
	if (z_readrec (&dba, &head) != S_OKAY) return (db_status);

/* Informationen einkopieren */
	memcpy (head.hdidn, key, sizeof(head.hdidn));
	strncpy (head.text, text, sizeof(head.text)-1);
	first = TRUE;
	head.hdrflags = lFlags;

	text_len = sizeof(head.text)-1;
	if (text_len < len) {
	/* Fortsetzungstexte notwendig */
		if (db_pzalloc (dbheadf, &satznr) != S_OKAY) return (db_status);
			if (first) {
			/* ersten Satz wegschreiben */
				head.zntext = satznr;
				if (z_writerec (&dba, &head) != S_OKAY) return (db_status);
				first = FALSE;
				dba.rec_no = 0;
			}
		} else {
			head.zntext = 0;
			if (z_writerec (&dba, &head) != S_OKAY) return (db_status);
			return (db_status = S_OKAY);
		}
  
		dba.file_no = FHEAD;
		while (text_len < len) {
		/* fuer gesamten Text */
			if (dba.rec_no != 0) {
			/* naechsten Satz anfordern */
				if (db_pzalloc (dbheadf, &satznr) != S_OKAY) return (db_status);
			
			/* vorhergehenden Satz wegschreiben */
				headf.ztextf = satznr;
				if (z_writerec (&dba, &headf) != S_OKAY) return (db_status);
			} 
		
		/* aktuellen Satz bereitstellen und beschreiben */
		dba.rec_no = satznr;
		if (z_readrec (&dba, &headf) != S_OKAY) return (db_status);
		strncpy (headf.textf, &text[text_len], sizeof(headf.textf)-1);
		text_len += sizeof(headf.textf)-1;
	}

/* letzten Satz wegschreiben */
	headf.ztextf = 0;       /* kein Folgesatz mehr */
	if (z_writerec (&dba, &headf) != S_OKAY) return (db_status);

return (db_status = S_OKAY);
}



