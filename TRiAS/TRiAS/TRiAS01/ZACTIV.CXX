/* Aktivieren einer Datenbasis                                  */
/* File: ZACTIV.C                                               */

#include "trias01p.hxx"

#include <protos.h>
#include "syncdb.hxx"

#ifdef MULTI_DB

extern "C" 
HPROJECT FUNCTYPE EXPORT01 z_activate (HPROJECT hDB)
{
	SYNC_DBACCESS_EX (g_pDbMutex); //, hDB);

DBASE *oldDB = NULL;

	if (NULL != hDB) {
	int num = HPROJECT2Index(hDB);

		if (num < 0 || num >= MAXDB) {
			db_error (S_ACTIV, ZACTIV);
			return HACTCONNECTION;
		}
		if ((oldDB = activate (&db_table[num])) == NULL) 
			return HACTCONNECTION;
	} 
	else if ((oldDB = activate (NULL)) == NULL) 
		return HACTCONNECTION;

	return Index2HPROJECT(oldDB - db_table);
}

#endif // MULTI_DB

