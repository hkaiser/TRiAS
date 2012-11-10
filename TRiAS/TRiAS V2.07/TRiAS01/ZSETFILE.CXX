/* Setzen der Anzahl zur Verfuegung stehenden Filedeskriptoren  */
/* File: ZSETFILE.C             last update: 5. Dezember 1989   */

#include "trias01p.hxx"

#include "syncdb.hxx"

extern "C" 
int FUNCTYPE EXPORT01 z_setfiles (int num)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

#ifndef MULTI_DB
        if (dbopen) return (dberr (S_DBOPEN, ZSETF));
#else
register int i;

	for (i = 0; i < MAXDB; ++i)
		if (db_table[i].db_name || db_table[i].db_pIStorage) 
			break;
	if (i != MAXDB) return (dberr (S_DBOPEN, ZSETF));
#endif  
	if (num < 1) max_open_files = 1;
	else max_open_files = num;
 
return (db_status = S_OKAY);
}
