/* Aktivieren einer Datenbasis                                  */
/* File: ZACTIV.C                                               */

#include "trias01p.hxx"

#include "syncdb.hxx"

#ifdef MULTI_DB

extern "C" 
HPROJECT FUNCTYPE EXPORT01 z_activate (HPROJECT hDB)
{
	SYNC_DBACCESS_EX (g_pDbMutex); //, hDB);

DBASE *oldDB;
int num = (int)hDB -1;

	if (num < 0 || num >= MAXDB) {
		db_error (S_ACTIV, ZACTIV);
		return (HPROJECT)0;
	}
	if ((oldDB = activate (&db_table[num])) == NULL) 
		return (HPROJECT)0;

return (HPROJECT)((oldDB - db_table) +1);
}

#endif // MULTI_DB

