/* Bereitstellen und beschreiben eines neuen Datensatzes        */
/* File: ZFILLNEW.C             last update: 22. November 1989  */

#include "trias01p.hxx"

#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" int FUNCTYPE EXPORT01 z_fillnew (DB_ADDR *dba, void *ptr)
{
	SYNC_DBACCESS (g_pDbMutex, (0 != dba->db_no) ? dba->db_no : GetHandleFromPtr(pActivatedDB));
	
	register short keyindex;
	register KEY_ENTRY FAR *kt_p;
	register short offset;
	
	/* Test, ob DB geoeffnet ist */
#ifndef MULTI_DB
	if (!dbopen) return (dberr (S_DBOPEN, FILLNEW));
#else
	TX_ASSERT_POINTER(act_db, DBASE);
	//	TX_ASSERT_NULL_OR_POINTER(act_db, DBASE);
	//	if (act_db == NULL) return (dberr (S_DBOPEN, FILLNEW));
#endif  
	TX_ASSERT_POINTER(dba, DB_ADDR);
	TX_ASSERT(TIsValidAddress (record_table, sizeof(REC_ENTRY)*size_rt, false));
	TX_ASSERT(TIsValidAddress (key_table, sizeof(KEY_ENTRY)*size_kt, false));
	
	if (dba->file_no < 0 || dba->file_no >= size_rt)
		return (db_error (S_INVADDR, FILLNEW, dba));
	
	/* Anfordern des neuen Datensatzes */
	if (db_pzalloc (record_table[(short)dba->file_no].rt_file, 
		&dba->rec_no) != S_OKAY) 
		return (db_status);
	
	/* Schlüsseldateien laufendhalten */
	if ((keyindex = record_table[(short)dba->file_no].rt_keyfile) != NONE) {
        /* Satz enthält Schlüssel */
		do {		/* für alle Schlüssel */
			TX_ASSERT(keyindex >= 0 && keyindex < size_kt);
			
			kt_p = &key_table[keyindex];
			offset = kt_p->kt_offset;
			if (key_init (kt_p) != S_OKAY) 
				return (db_status);
			
			TX_ASSERT(TIsValidAddress((char *)ptr+offset, kt_p->kt_len, false));
			
			if (!nullcmp ((char *)ptr+offset, kt_p->kt_len)) {
				/* wenn neuer Schlüssel nicht gleich Null */
				if (insert_key (dba, (char *)ptr+offset) != S_OKAY) 
					return (db_status);
			}
			
			working_file = NONE;
		} while ((keyindex = kt_p->kt_chain) != NONE);
	}
	
	/* Satz selbst wegschreiben */
	db_status = db_write (dba, ptr);
	
	return (db_status);
}

/*
extern "C" long  FUNCTYPE EXPORT01 znew_ (long *dba, void *ptr)
{
return (long) z_fillnew ((DB_ADDR *)dba, ptr);
}
*/
