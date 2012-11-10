/* Lesen des aktuellen Schluesselwertes                         */
/* File: ZKEYREAD.C             last update: 24. November 1989  */

#include "trias01p.hxx"

#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" 
int FUNCTYPE EXPORT01 z_keyread (HPROJECT hPr, void *keyptr)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

#ifndef MULTI_DB
        if (!dbopen) return (dberr (S_DBOPEN, ZKREAD));
#else
//	TX_ASSERT_NULL_OR_POINTER(act_db, DBASE);
	TX_ASSERT_POINTER(act_db, DBASE);
//	if (act_db == NULL) return (dberr (S_DBOPEN, ZNEXT));
#endif  
/* Lesen des aktuellen Datensatzes */
	db_status = key_read (keyptr);

return (db_status);
}

/*
extern "C" long FUNCTYPE EXPORT01 zkread_ (void *keyptr)
{
	return (long)z_keyread (keyptr);
}
*/
