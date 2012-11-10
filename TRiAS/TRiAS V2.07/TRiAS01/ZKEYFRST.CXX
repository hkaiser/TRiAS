/* Finden des ersten Schluessels ueber einen BTree              */
/* File: ZKEYFRST.C             last update: 24. November 1989  */

#include "trias01p.hxx"

#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" 
int FUNCTYPE EXPORT01 z_keyfirst (DB_ADDR *dba, register int keyno)
{
	SYNC_DBACCESS (g_pDbMutex, (0 != dba->db_no) ? dba->db_no : GetHandleFromPtr(pActivatedDB));

#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, Z1ST));
#else
	TX_ASSERT_POINTER(act_db, DBASE);
//	TX_ASSERT_NULL_OR_POINTER(act_db, DBASE);
//	if (act_db == NULL) return (dberr (S_DBOPEN, Z1ST));
#endif  
	TX_ASSERT(TIsValidAddress (dba, sizeof(DB_ADDR)));
	TX_ASSERT(keyno >= 0 && keyno < size_kt);

//	if (keyno < 0 || keyno >= size_kt) return (dberr (S_NOKEY, Z1ST));

/* Finden des gesuchten Datensatzes */
	db_status = key_first (keyno, dba);

return (db_status);
}

/*
extern "C" long FUNCTYPE EXPORT01 zfirst_ (long *dba, register long *keyno)
{
	return (long)z_keyfirst ((DB_ADDR *)dba, (int) *keyno);
}
*/

