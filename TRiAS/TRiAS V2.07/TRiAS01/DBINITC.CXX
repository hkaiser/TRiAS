/* Initialisierung einiger notwendiger Variablen fuer die DB-Arbeit     */
/* File: DBINITC.C                      last update: 24. November 1989  */

#include "trias01p.hxx"
#include "syncdb.hxx"

extern "C" void FUNCTYPE EXPORT01 dbinit_ (void)
{
/*        db_errmode = BACKGRND;*/
	SYNC_DBACCESS_EX (g_pDbMutex);

	no_of_pages = 1024;
	max_open_files = 8;
}
