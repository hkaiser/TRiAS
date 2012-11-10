/* Abschliessen einer Datenbasis                                */
/* File: DBCLOSE.C              last update: 19 .Mai 1989       */

#include "trias01p.hxx"
#include "syncdb.hxx"

#if defined(_DEBUG) && !defined(WIN32)
#include <ole2dbg.h>
#endif (// _DEBUG

#if defined(_USE_CONNECTFILTER)
#include "ObjectGiST.h"
#endif // defined(_USE_CONNECTFILTER)

extern "C" int FUNCTYPE EXPORT01 z_close (HPROJECT hDB, BOOL fCommit)
{
	SYNC_DBACCESS (g_pDbMutex, hDB);

FILE_ENTRY *fe_p;

#ifndef MULTI_DB
	if (dbopen) {
#else  // MULTI_DB
	register DBASE *db_p; 
	short db_slot = (short)hDB -1;

		if (db_slot < 0 || db_slot >= MAXDB) 
			return db_error (S_CLOSE, Z_CLOSE);

        if ((db_p = &db_table[db_slot])->db_name != NULL || db_p -> db_pIStorage != NULL) {
		// diese Datenbank ist wirklich geöffnet
#if defined(_USE_OPENREFCNT)
			if (0 != --db_p -> db_RefCnt) 
				return (db_status = S_OKAY);		// lediglich freigeben
#endif // defined(_USE_OPENREFCNT)

        DBASE* old_slot = activate (db_p);
#endif // MULTI_DB
        short i;
        ErrCode RC;
		
			if (fCommit) {
				DBASSERT(db_flush (FLUSH_ACTDB, db_p));		/* alle Pages wegschreiben */
				DBASSERT(db_pzflush (FLUSH_ACTDB, db_p));  	/* alle Page 0 wegschreiben */
			} else {
				DBASSERT(db_flush (FLUSH_NODATA, db_p));		/* alle Pages dieser DB säubern */
			}

// Speicher dieser DB wieder freigeben
#ifdef MSWIND
			if (db_p -> db_pIStorage) {
				for (i = 0, fe_p = db_p -> db_ftab; i < db_p -> db_sft; ++i, ++fe_p) 
					file_close (fe_p, false, fCommit);	// nur Commit

				if (!db_p -> db_fOpenedRO && fCommit) {
#if defined(_DEBUG) && !defined(WIN32)
					DbgDumpObject (db_p -> db_pIStorage, 0L);
#endif // _DEBUG
#if defined(WIN32)
				DWORD rgStgc = STGC_DEFAULT;

					if (IsWin50() && IsWinNT())
						rgStgc |= STGC_CONSOLIDATE;

				HRESULT hr = db_p -> db_pIStorage -> Commit (rgStgc);
#else
// workaround für BUG in Storage.dll
				HRESULT hr = db_p -> db_pIStorage -> Commit (STGC_OVERWRITE);
#endif // WIN32
					if (FAILED(hr))
						return db_error (S_STG_CLOSEERROR, Z_CLOSE, hr);
				}					

			// jetzt alle Streams schließen
				for (i = 0, fe_p = db_p -> db_ftab; i < db_p -> db_sft; ++i, ++fe_p) 
					file_close (fe_p, true, false);	// letztes Schließen

				db_p -> db_pIStorage -> Release();
				db_p -> db_pIStorage = NULL;

				db_p -> db_hProjectRelated = NULL;

#if defined(_USE_OPENREFCNT)
				db_p -> db_Mode = 0; 
#endif // defined(_USE_OPENREFCNT)

			} else {
			// jetzt alle Dateien schließen
				for (i = 0, fe_p = db_p -> db_ftab; i < db_p -> db_sft; ++i, ++fe_p) 
					file_close (fe_p, true);	// letztes Schließen
			}
			
			DELETE_VEC (db_p -> db_ftab[0].ft_name/*, strlen(db_p -> db_ftab[0].ft_name)*/);
			DELETE_VEC (db_p -> db_pztab/*, db_p -> db_sft*/);
			DELETE_VEC (db_p -> db_ftab/*, db_p -> db_sft*/);
			DELETE_VEC (db_p -> db_ktab/*, db_p -> db_skt*/);
			DELETE_VEC (db_p -> db_parent/*, MAXLEVEL*/);
			DELETE_VEC (db_p -> db_slots/*, MAXLEVEL*/);
			DELETE_VEC (db_p -> db_rtab/*, db_p -> db_srt*/);

			file_table = NULL;
			key_table = NULL;
			record_table = NULL;
			pgzero = NULL;
			slots = NULL;
			parent = NULL;

		// evtl. MetaTables freigeben
			if (NULL != db_p -> db_pIIdentMap) {
				db_p -> db_pIIdentMap -> Release();
				db_p -> db_pIIdentMap = NULL;
			}
			if (NULL != db_p -> db_pIMCodeMap) {
				db_p -> db_pIMCodeMap -> Release();
				db_p -> db_pIMCodeMap = NULL;
			}

#if defined(_USE_CONNECTFILTER)
			DELETE_VEC(db_p->db_ConnectFilter.m_pX);
			DELETE_VEC(db_p->db_ConnectFilter.m_pY);
			DELETE_OBJ(db_p->db_ConnectFilter.m_prsTree);
			db_p->m_dbfConnectFilterValid = FALSE;
			db_p->db_ConnectFilter.m_dXMin = 
				db_p->db_ConnectFilter.m_dXMax =
				db_p->db_ConnectFilter.m_dYMin =
				db_p->db_ConnectFilter.m_dYMax = 0.0;
#endif // defined(_USE_CONNECTFILTER)

#else // MSWIND
		// jetzt alle Dateien schließen
			for (i = 0, fe_p = db_p -> db_ftab; i < db_p -> db_sft; ++i, ++fe_p) 
				file_close (fe_p, TRUE);	// letztes Schließen

            free ((char *)pgzero);  /* Page 0 freigeben */
		
		/* Tabellen wegraeumen */
            if (file_table) {
                    free (file_table[0].ft_name);
                    free ((char *)file_table);
            }
            if (key_table) free ((char *)key_table);
            if (record_table) free ((char *)record_table);
		
		/* Schlüsselsuchposition freigeben */
            if (parent) {
                    free ((char *)parent);
                    free ((char *)slots);
            }
#endif // MSWIND

#ifndef MULTI_DB
            dbopen = FALSE;
            db_free ();     /* Speicherseiten wieder freigeben */
#else // MULTI_DB

#if defined(PROJECT_LOCKING)
		// als letztes evtl. LockingFile löschen
			if (db_p->db_fhShared > 0 && db_p -> db_name) {
			// Datei schließen und sofort löschen
			char *pcbT = NULL;
			
				if (pcbT = strrchr (db_p->db_name, '.'))
					*pcbT = '\0';		// Erweiterung ändern
				strcat (db_p->db_name, LOK_EXTENSION);				
			
				_lclose (db_p->db_fhShared);
				unlink (db_p->db_name);
				db_p->db_fhShared = 0;
			}
#endif // PROJECT_LOCKING
		// DB-slot freimachen
#ifdef MSWIND
			DELETE_VEC (db_p->db_name/*, strlen (db_p->db_name)*/);
#else  // MSWIND
			free (db_p->db_name);
#endif // MSWIND
			db_p->db_name = NULL;
			db_p->db_sft = 0;
                
	/* ueberpruefen ob noch eine DB aktiv ist */
			for (i = 0; i < MAXDB; ++i) {
				if (NULL != db_table[i].db_name || 
					NULL != db_table[i].db_pIStorage) 
				{	
					break;
				}
			}
			if (i == MAXDB)
			/* keine DB mehr aktiv --> Speicherseiten freigeben */
				db_free ();     /* Speicherplatz wieder freigeben */

			if (old_slot != db_p) activate (old_slot);
			else                  activate (NULL);
#endif // MULTI_DB
        } else 
			return (dberr (S_CLOSE, Z_CLOSE));
	return (db_status = S_OKAY);
}
 
/*
extern "C" long FUNCTYPE EXPORT01 zclose_ (long *db_slot)
{
	return (long) z_close ((HPROJECT) (*db_slot +1), true);
}
*/
