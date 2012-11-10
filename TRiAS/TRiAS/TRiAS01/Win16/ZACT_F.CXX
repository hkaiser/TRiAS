/* Fortranschnittstelle (UNIX) - Abschliessen einer Datenbasis  */
/* File: ZACT_F.C                                               */

#include "trias01p.hxx"

#include "syncdb.hxx"

#ifdef MULTI_DB

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#ifdef vms
#define zact_ zact
#endif

extern "C" long FUNCTYPE EXPORT01 zact_ (long *dblun)
{
	SYNC_DBACCESS (g_pDbMutex, (*dblun)-1);

register DBASE *olddb;

	TX_ASSERT(*dblun >= 0 && *dblun < MAXDB);
//	if (*dblun < 0 || *dblun >= MAXDB)
//		return (db_error (S_ACTIV, ZACT_F));

	if ((olddb = activate (&db_table[*dblun])) == NULL) 
		return (db_status);

return ((INT)(olddb - db_table));
}

#endif // MULTI_DB

