/* Bestimmen der Laenge eines HeaderSatzes			 */
/* File: GETHDLEN.C                                              */

#include "trias01p.hxx"
#include "syncdb.hxx"

extern "C" int FUNCTYPE EXPORT01 gethdlen (HPROJECT hPr, long *key, short *len) 
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

struct head head;
struct fhead headf;
DB_ADDR dba(hPr);
register short text_len;

	*len = 0;
/* Satz suchen */
        dba.file_no = HEAD;
        if (z_keyfind (&dba, HDIDN, key) != S_OKAY) 
                return (db_status);

/* 1. Satz einlesen */
        if (z_readrec (&dba, &head) != S_OKAY) 
		return (db_status);
        text_len = strlen (head.text);
/* weitere Saetze einlesen */
        dba.file_no = FHEAD;
        dba.rec_no = head.zntext;
        while (dba.rec_no != 0) {
                if (z_readrec (&dba, &headf) != S_OKAY) 
			return (db_status);
                text_len += strlen (headf.textf);
                dba.rec_no = headf.ztextf;
        }
	*len = text_len;

return (db_status = S_OKAY);
}
