/* Loeschen eines Datensatzes des DB-Headers                    */
/* File: DELHD_F.C                                              */

#include "trias01p.hxx"
#include "syncdb.hxx"

extern "C" 
long FUNCTYPE EXPORT01 delhd_ (HPROJECT hPr, long *key)
// INT *key;              /* Schluessel */
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

DB_ADDR dba(hPr);

	dba.file_no = HEAD;
	if (z_keyfind (&dba, HDIDN, key) != S_OKAY) 
		return ((INT)db_status);
/* Schluessel existiert --> loeschen */
	if (delete_head ((char *)key, &dba) != S_OKAY)
		return ((INT)db_status);

return ((INT)(db_status = S_OKAY));
}


int FUNCTYPE delete_head (char *key, DB_ADDR *dba)
{
struct head head;
struct fhead headf;
INT satznr;
DB_ADDR mydba(dba->db_no);

/* ersten Satz einlesen */
	if (z_readrec (dba, &head) != S_OKAY) return (db_status);
	satznr = head.zntext;
/* ersten Satz freigeben */
	if (z_dispose (dba) != S_OKAY) return (db_status);
	while (satznr != 0) {
	/* fuer alle weiteren Saetze */
		mydba.file_no = FHEAD;
		mydba.rec_no = satznr;
	/* Einlesen ... */
		if (z_readrec (&mydba, &headf) != S_OKAY) return (db_status);
		satznr = headf.ztextf;
	/* ... und Freigeben */
		if (z_dispose (&mydba) != S_OKAY) return (db_status);
    }

return (db_status = S_OKAY);    
}
