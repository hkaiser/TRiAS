// Liefert VersionsNummer fuer aktuelle Datenbasis
// File: VERSION.C

#include "trias01p.hxx"
#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

long FUNCTYPE LocGetDBVersion (HPROJECT hPr) 
{
	if (hPr == 0) {
	// aktuelles Projekt verwenden
		if (act_db != NULL) 
			return act_db -> db_version;
		else {
			TX_ASSERT(NULL != act_db);
			return 0L;
		}
	} else {
	// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;
	register DBASE *db_p = &db_table[db_slot];

		if (db_p -> db_name != NULL || db_p -> db_pIStorage) 
			return db_p -> db_version;
		else {
			TX_ASSERT(db_p -> db_name != NULL || db_p -> db_pIStorage);
			return 0L;	// Fehler
		}
	}
	
return 0L;
}

extern "C" 
long FUNCTYPE EXPORT01 GetDBVersion (HPROJECT hPr) 
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return LocGetDBVersion (hPr);
}

extern "C" 
BOOL FUNCTYPE EXPORT01 GetCopyMode (HPROJECT hPr, BOOL *pfRO)
{
	if (NULL == pfRO) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*pfRO = act_db -> db_fOpenedAsCopy;
			return true;
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;
	register DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*pfRO = db_p -> db_fOpenedAsCopy;
			return true;
		}
	}

return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 GetROMode (HPROJECT hPr, BOOL *pfRO)
{
	if (NULL == pfRO) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*pfRO = act_db -> db_fOpenedRO;
			return true;
		} 
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;
	register DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*pfRO = db_p -> db_fOpenedRO;
			return true;
		}
	}

return false;	// nicht festzustellen
}

