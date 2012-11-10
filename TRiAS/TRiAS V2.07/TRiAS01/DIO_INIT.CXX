/* Datenbank - I/O Funktionen unterste Ebene                            */
/* Initialisierung der Datenbank I/O-Arbeit                             */
/* File: DIO_INIT.C             last update: 15. Februar 1990           */

#include "trias01p.hxx"

#define NOCOPYRIGHT
#include <dbversio.h>

/* globale Datendefinitionen fuer DIO */
short max_open_files = MAXFILES;        /* maximale Anzahl eröffneter Files */
short cnt_open_files = 0;       	/* aktuelle Anzahl eröffneter Files */

short no_of_pages = DEFPAGES;   	/* Anzahl der Pages in der Pagetabelle */
short dynamic = DEFPAGES;       	/* Anzahl der dynamisch verwalteten Pages */
short least_recent = 0;         	/* Zähler fuer dynamisches Pageswopping */
short working_file = NONE;      	/* für Operationen mit default_file */

PAGE_ENTRY *pages = NULL;       	/* Pageverzeichnisse */
PGZERO *pgzero = NULL;			/* Nullpagetabelle */
PAGE_ENTRY **page_table = NULL; 	/* Pagetabelle */
unsigned short ActPageSize = 0;		/* aktuelle Pagegröße */

#ifdef BACKUP
short backup_flag = NONE;
PAGE_ENTRY *backup_page = NULL;
#endif // BACKUP

#ifdef PAGEHASH
HASH_LIST FAR **hash_table = NULL;	/* Hashtabelle */
short hashsize = HASHSIZE;      	/* Größe der Hashtabelle */
#else // PAGEHASH
short hashsize;
#endif // PAGEHASH

#ifdef MULTI_DB
short last_db = 0;			/* zuletzt angesprochene DB (fdbopen) */
#endif // MULTI_DB

extern "C" REC_ENTRY *FUNCTYPE EXPORT01 RecordTable (HPROJECT hPr, short iIndex)
{
	if (iIndex >= 0 && iIndex < size_rt)
		return record_table + iIndex;
	
	return record_table;
}

// Test auf Übereinstimmung des CopyrightStrings ist Fatal bei Fehler
extern FLAG g_fCopyrightFlag;

int FUNCTYPE dio_init (DBASE *pDB)
{
register short i;
register PAGE_ENTRY *pe_p;
	
#ifdef BACKUP
	/* Eigene Page fuer Backup anfordern */
	if (backup_page == NULL && (pDB ? pDB -> db_bflag >= 0 : backup_flag)) {
		TX_TRY(backup_page = (PAGE_ENTRY *)new char [sizeof (PAGE_ENTRY) + MAXPAGESIZE -1]); 
		if (backup_page == NULL)
			return (db_error (S_NOMEMORY, DIO_INIT));
	}
#endif // BACKUP
	
unsigned short uiPageSize = (pDB != NULL) ? pDB -> db_pagesize : PageSize;
	
#ifdef MULTI_DB
	/* wenn nicht erste DB und Pages richtig in der Größe --> return */
	if (page_table != NULL && ActPageSize >= uiPageSize)
		return (db_status = S_OKAY);
#endif // MULTI_DB
	
	// Anlegen der Pageverwaltungsstrukturen
	if (page_table == NULL) {
		TX_TRY(page_table = new PAGE_ENTRY * [no_of_pages]);
		if (!page_table)
			return (dberr (S_NOMEMORY, DIO_INIT));
		memset (page_table, '\0', sizeof(PAGE_ENTRY *) * no_of_pages);
	} 	
	
#ifdef PAGEHASH
	hashsize = prim (no_of_pages);
	TX_TRY(hash_table = new HASH_LIST *[hashsize]);
	if (!hash_table) return (dberr (S_NOMEMORY, DIO_INIT));
	for (i = 0; i < hashsize; ++i)
		hash_table[i] = NULL;
#endif // PAGEHASH
	
	// Initialisieren der angelegten Strukturen
	last_db = 0;
	if (pDB) pDB -> db_work = NONE;
	else working_file = NONE;
	
	pe_p = pages;
	
	for (i = 0; i < no_of_pages; ++i) {
		if (NULL == page_table[i]) {
			// Speicher neu enfordern
			TX_TRY(pe_p = (PAGE_ENTRY *)new char [sizeof(PAGE_ENTRY) + uiPageSize -1]);
			if (pe_p == NULL)
				return (db_error (S_NOMEMORY, DIO_INIT));
			
			// Pages initialisieren
			pe_p->file = -1;
			pe_p->pageno = 0;
			pe_p->recently_used = FALSE;
			pe_p->modified = FALSE;
#ifdef PAGEHASH	
			pe_p->hash = NONE;
#endif
#ifdef MULTI_DB
			pe_p->dbase = NULL;
#endif
			pe_p -> pg_pagesize = uiPageSize;
		} else {
		// Pages vergrößern
		PAGE_ENTRY *pPE = NULL;
		
			TX_TRY(pPE = (PAGE_ENTRY *)new char [sizeof(PAGE_ENTRY) + uiPageSize -1]);
			if (pPE == NULL) return (db_error (S_NOMEMORY, DIO_INIT));
			
			memcpy (pPE, page_table[i], page_table[i] -> pg_pagesize);
			delete [] (char *)page_table[i];
			pe_p = pPE;
		}
		page_table[i] = pe_p;
	}
	least_recent = 0;
	dynamic = no_of_pages;
	ActPageSize = uiPageSize;
	
	return (db_status = S_OKAY);
}


// Initialisieren der Page 0 Tabellen -----------------------------------------
int FUNCTYPE dio_pzinit (void)
{
register short i;
register int desc;
register FILE_ENTRY *ft_p;
BYTE version[COPYRIGHT_LEN];
	
	TX_TRY(pgzero = new PGZERO [size_ft]);
	if (!pgzero) return (dberr (S_NOMEMORY, DIO_PZINIT));
	
	for (i = 0; i < size_ft; ++i) {
		if ((ft_p = &file_table[i])->ft_access == O_NOACC) 
			continue;
		if (file_open (ft_p) != S_OKAY) 
			return (db_status);
	
	// auf Anfang positionieren
		lseek (desc = ft_p->ft_desc, 0L, 0);
	
	// Version überprüfen
#ifdef MSWIND
		_lread (desc, (LPSTR)version, COPYRIGHT_LEN);
#else
		read (desc, version, COPYRIGHT_LEN);
#endif
		if (g_fCopyrightFlag && 
			(mycrypt (version, COPYRIGHT_LEN) & 0xffff) != COPYRIGHT_CRC)
		{
			return (dberr (S_VERSION, DIO_PZINIT));
		}

		/* einlesen der Page 0 */
#ifdef MSWIND
		if (_lread (desc, (LPSTR)&(pgzero[i]), sizeof(PGZERO)) < 0)
#else
			if (read (desc, &(pgzero[i]), sizeof (PGZERO)) < 0)
#endif
				return (dberr (S_NOREAD, DIO_PZINIT));
			file_close (ft_p);
	}
	
	return (db_status = S_OKAY);
}


// Version für CompoundFiles --------------------------------------------------
#if defined(MSWIND)

short FUNCTYPE InitPageZeroTable (DBASE *pDB)
{
BYTE cbVersion[COPYRIGHT_LEN];
	
	TX_TRY(pDB -> db_pztab = new PGZERO [pDB -> db_sft]);
	if (!pDB -> db_pztab) return db_error (S_NOMEMORY, DIO_PZINIT);
	
	for (short i = 0; i < pDB -> db_sft; ++i) {
	FILE_ENTRY *ft_p = &pDB -> db_ftab[i];
		
		if (ft_p -> ft_access == O_NOACC) 
			continue;
		
	// auf Anfang positionieren
	LPSTREAM pIStream = ft_p -> ft_pIStream;
	LARGE_INTEGER li;
		
		LISet32 (li, 0);	
		pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
		
		// Version überprüfen
		pIStream -> Read (cbVersion, COPYRIGHT_LEN, NULL);
		if (g_fCopyrightFlag && 
			(mycrypt (cbVersion, COPYRIGHT_LEN) & 0xffff) != COPYRIGHT_CRC)
		{
			return db_error (S_VERSION, DIO_PZINIT);
		}
	
	// Einlesen der Page 0
	HRESULT hr = pIStream -> Read (&pDB -> db_pztab[i], sizeof(PGZERO), NULL);
		
		if (FAILED(hr)) return db_error (S_NOREAD, DIO_PZINIT);
	}
	
	return (db_status = S_OKAY);
}
#endif
