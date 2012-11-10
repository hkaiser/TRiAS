// Eine TargetDatei neu Indizieren --------------------------------------------
// File: REINDEX.C

#include "trias01p.hxx"
#include "syncdb.hxx"

extern "C" 
int FUNCTYPE EXPORT01 ReIndexFile (HPROJECT hPr, short iFile, short iRecord, short iKeyIndex, 
					     short (*pProc)(void *))
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

char *inPtr;
DB_ADDR dba(hPr);
long lLast = pgzero[iFile].pz_next;
KEY_ENTRY *pKE = &key_table[iKeyIndex];
int RC;

	for (dba.rec_no = 1; dba.rec_no < lLast; dba.rec_no++) {
	// alle Sätze der Datei behandeln

		dba.file_no = iFile;
		DBASSERT (tdb_read (&dba, (void **)&inPtr));	// Satz einlesen
		if (*(INT *)inPtr == MAXPOSLONG)	// Satz ist gelöscht
			continue;

		if (pProc == NULL || (*pProc)(inPtr)) {
			DBASSERT (key_init (pKE));	// Schlüssel initialisieren
			dba.file_no = iRecord;
			DBASSERT (insert_key (&dba, inPtr + pKE -> kt_offset));
			working_file = NONE;
		}
	}

return S_OKAY;
}


