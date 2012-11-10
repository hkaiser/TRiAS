/* Lesen eines Datensatzes                                      */
/* File: ZREADREC.C             last update: 22. November 1989  */

#include "trias01p.hxx"

#include "syncdb.hxx"
 
#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/* Lesen eines gesuchten Datensatzes */
extern "C" int FUNCTYPE EXPORT01 z_readrec (DB_ADDR *dba, void *ptr)
{
	SYNC_DBACCESS (g_pDbMutex, (0 != dba->db_no) ? dba->db_no : GetHandleFromPtr(pActivatedDB));

/* Test, ob DB geoeffnet ist */
#ifndef MULTI_DB
	if (!dbopen) return (dberr (S_DBOPEN, ZREAD));
#else
//	TX_ASSERT_NULL_OR_POINTER(act_db, DBASE);
	TX_ASSERT_POINTER(act_db, DBASE);
//	if (act_db == NULL) return (dberr (S_DBOPEN, ZFIND));
#endif  
	TX_ASSERT_POINTER(dba, DB_ADDR);

	if (dba->file_no < 0 || dba->file_no >= size_rt)
		return (db_error (S_INVADDR, ZREAD, dba));

/* Datensatz lesen */
char *data;
 
	if (db_read (dba, (void **)&data) != S_OKAY) 
		return (db_status);

	TX_ASSERT(data);
	if (*(INT *)data == MAXPOSLONG)
		return db_error (S_DELRECORD, ZREAD, dba);

	TX_ASSERT(TIsValidAddress (record_table, sizeof(REC_ENTRY)*size_rt, false));
	TX_ASSERT(TIsValidAddress (ptr, record_table[(short)dba->file_no].rt_len));

	memcpy (ptr, data, record_table[(short)dba->file_no].rt_len);
 
return (db_status = S_OKAY);
}
 
/*
extern "C" long FUNCTYPE EXPORT01 zread_ (long *dba, void *ptr)
{
	return (long)z_readrec ((DB_ADDR *)dba, ptr);
}
*/
