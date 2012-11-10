/* Freigeben  eines Datensatzes                                 */
/* File: ZDISPOSE.C             last update: 22. November 1989  */

#include "trias01p.hxx"

#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" int FUNCTYPE EXPORT01 z_dispose (DB_ADDR *dba)
{
	SYNC_DBACCESS (g_pDbMutex, (0 != dba->db_no) ? dba->db_no : GetHandleFromPtr(pActivatedDB));

register short keyindex;
register KEY_ENTRY FAR *kt_p;
register short offset;
char FAR *ptr;
 
/* Test, ob DB geöffnet ist */
#ifndef MULTI_DB
	if (!dbopen) return (dberr (S_DBOPEN, ZDISPOSE));
#else
//	TX_ASSERT_NULL_OR_POINTER(act_db, DBASE);
	TX_ASSERT_POINTER(act_db, DBASE);
//	if (act_db == NULL) return (dberr (S_DBOPEN, ZDISPOSE));
#endif  
	TX_ASSERT_POINTER(dba, DB_ADDR);
	TX_ASSERT(TIsValidAddress (record_table, sizeof(REC_ENTRY)*size_rt, false));
	TX_ASSERT(TIsValidAddress (key_table, sizeof(KEY_ENTRY)*size_kt, false));

	if (dba->file_no < 0 || dba->file_no >= size_rt)
		return (db_error (S_INVADDR, ZDISPOSE, dba));

/* Schluesseldateien laufendhalten */
	if ((keyindex = record_table[(short)dba->file_no].rt_keyfile) != NONE) {
	/* Satz enthält Schlüssel */
                
		if (db_read (dba, (void **)&ptr) != S_OKAY) /* Datensatz einlesen */
			return (db_status);
		do {		/* für alle Schlüssel */
			TX_ASSERT(keyindex >= 0 && keyindex < size_kt);

			kt_p = &key_table[keyindex];
			offset = kt_p->kt_offset;
			if (key_init (kt_p) != S_OKAY) 
				return (db_status);

			TX_ASSERT(TIsValidAddress(ptr+offset, kt_p->kt_len, false));

			if (!nullcmp (ptr+offset, kt_p->kt_len)) 
			/* wenn alter Schlüssel nicht gleich Null */
				db_status = delete_key (dba, ptr+offset);
			
			if (db_status == S_NOTFOUND) {
				db_status = S_OKAY;
			} else if (db_status != S_OKAY) 
				return (db_status);
                        
			working_file = NONE;
		} while ((keyindex = kt_p->kt_chain) != NONE);
	}

/* Datensatz freigeben */
	db_status = db_pzfree (record_table[(short)dba->file_no].rt_file, 
						   dba->rec_no, dba->db_no);

return (db_status);
}

/*
extern "C" long FUNCTYPE EXPORT01 zdisp_ (long *dba)
{
	return (long)z_dispose ((DB_ADDR *)dba);
}
*/
