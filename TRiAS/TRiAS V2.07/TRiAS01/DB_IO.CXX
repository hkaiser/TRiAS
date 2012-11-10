/* Datenbank - I/O Funktionen unterste Ebene                            */
/* Elementare I/O-Routinen                                              */
/* File: DB_IO.C                                                        */

#include "trias01p.hxx"
#include "syncdb.hxx"

#ifdef STATISTICS
extern int write_cnt;
extern int read_cnt;
extern int statistics;
#endif

static int FUNCTYPE find_page (DB_ADDR *dbkey, PAGE_ENTRY **pe_p, short *offset);
static int FUNCTYPE dio_in (PAGE_ENTRY *pe_p);
static int FUNCTYPE dio_out (PAGE_ENTRY *pe_p);
#ifdef BACKUP
static int FUNCTYPE backup (PAGE_ENTRY *pe_p);
#endif

#if (defined(__WATCOMC__) && defined(__386__)) || defined(WIN32)
#define hfree(a)        free(a)
#endif

extern unsigned short ActPageSize;
 
/* Bereitstellen eines gesuchten Datensatzes (ueber Recordnummer) */
int FUNCTYPE db_read (DB_ADDR *dba, void **recptr)
// register DB_ADDR *dba;  /* DB-Adresse des gesuchten Satzes */
// char **recptr;       /* Resultat: Adresse des gesuchten Satzes */
{
short offset;           /* Pagenummer und entspr. Offset der gesuchten Daten */
PAGE_ENTRY *pe_p;

// wenn keine DB gegeben ist, dann ActDB verwenden
	if (NULL == dba->db_no) {
		TX_ASSERT(0 != dba->db_no);
		dba->db_no = (HPROJECT)((act_db - db_table) +1);
	}

DB_ADDR localdba(dba->db_no);
ErrCode RC;

/* DBA auf Dateinummer Umsetzen */
// bereits geprüft #HK910818
//        if (dba->file_no < 0 || dba->file_no >= size_rt)
//                return (db_error (S_INVADDR, DB_READ, dba));
	localdba.file_no = record_table[dba->file_no].rt_file;
	localdba.rec_no = dba->rec_no;
	
/* Bereitstellen der entsprechenden Page */
	DBASSERT (find_page (&localdba, &pe_p, &offset));
	*recptr = (char *)&(pe_p->buff[offset]);

return (db_status = S_OKAY);
}
 
 
/* Wegschreiben eines gegebenen Datensatzes (ueber Recordnummer) */
int FUNCTYPE db_write (DB_ADDR *dba, void *recptr)
// register DB_ADDR *dba;  /* DB-Adresse des gegebenen Satzes */
// char FAR *recptr;                /* Adresse, wo Satz bereitgestellt ist */
{
short offset;           /* Pagenummer und entspr. Offset der gesuchten Daten */
PAGE_ENTRY *pe_p;

// wenn keine DB gegeben ist, dann ActDB verwenden
	if (NULL == dba->db_no) {
		TX_ASSERT(0 != dba->db_no);
		dba->db_no = (HPROJECT)((act_db - db_table) +1);
	}

DB_ADDR localdba(dba->db_no);
ErrCode RC;

/* DBA auf Dateinummer Umsetzen */
// bereits geprüft #HK910818
//        if (dba->file_no < 0 || dba->file_no >= size_rt)
//                return (db_error (S_INVADDR, DB_WRITE, dba));
	localdba.file_no = record_table[dba->file_no].rt_file;
	localdba.rec_no = dba->rec_no;
 
/* Bereitstellen der entsprechenden Page */
	DBASSERT (find_page (&localdba, &pe_p, &offset));
	if (recptr != NULL) {
	register unsigned char *buffptr = &(pe_p->buff[offset]);

/* Slot ausnullen und neu beschreiben */
		memset (buffptr, '\0',
			file_table[(short)localdba.file_no].ft_slsize);
		memcpy (buffptr, recptr,
			record_table[(short)dba->file_no].rt_len);
	}
	pe_p->modified = TRUE;
 
return (db_status = S_OKAY);
}
 
 
/* Bereitstellen eines gesuchten Datensatzes (ueber Dateinummer) */
int FUNCTYPE tdb_read (DB_ADDR *dbkey, void **recptr)
// DB_ADDR *dbkey;         /* DB-Adresse des gesuchten Satzes */
// char FAR **recptr;       /* Resultat: Adresse des gesuchten Satzes */
{
short offset;           /* Pagenummer und entspr. Offset der gesuchten Daten */
PAGE_ENTRY *pe_p;
ErrCode RC;
 
	if (NULL == dbkey -> db_no) {		// zur Zeit noch
//		TX_ASSERT(0 != dbkey->db_no);	// darf passieren
		dbkey -> db_no = (HPROJECT)((act_db - db_table) +1);
	}

/* Bereitstellen der entsprechenden Page */
	DBASSERT (find_page (dbkey, &pe_p, &offset));
	*recptr = (char *)&(pe_p->buff[offset]);
 
return (db_status = S_OKAY);
}
 
 
/* Wegschreiben eines gegebenen Datensatzes (ueber Dateinummer) */
int FUNCTYPE tdb_write (DB_ADDR *dbkey, void *recptr)
// DB_ADDR *dbkey;			/* DB-Adresse des gegebenen Satzes */
// char FAR *recptr;		/* Adresse, wo Satz bereitgestellt ist */
{
short offset;           /* Pagenummer und entspr. Offset der gesuchten Daten */
PAGE_ENTRY *pe_p;
ErrCode RC; 

	if (NULL == dbkey -> db_no)	{		// zur Zeit noch
//		TX_ASSERT(0 != dbkey->db_no);	// darf passieren
		dbkey -> db_no = (HPROJECT)((act_db - db_table) +1);
	}

	/* Bereitstellen der entsprechenden Page */
	DBASSERT (find_page (dbkey, &pe_p, &offset));
	if (recptr != NULL) {
		memcpy (&(pe_p->buff[offset]), recptr,
			pe_p -> dbase -> db_ftab[(short)dbkey->file_no].ft_slsize);
	}
	pe_p->modified = TRUE;
 
return (db_status = S_OKAY);
}
 
/* Bereitstellen einer Datenseite, die gewuenschten Satz enthaelt */
static int FUNCTYPE find_page (DB_ADDR *dbkey, PAGE_ENTRY **ppPage, short *offset)
// DB_ADDR *dbkey;         /* Datenbankadresse */
// PAGE_ENTRY **ppPage;    /* gesuchte Seite */
// short *offset;          /* gesuchter offset in Seite */
{
PAGE_NO pageno;         /* Seitennummer im File */
PAGE_ENTRY *pe_p;
FILE_ENTRY *fe_p;
INT aux1, aux2;
int RC;
DBASE *pDB = &db_table[short(dbkey -> db_no) -1];	// konkrete DatenBasis

	if (dbkey->rec_no <= 0 || 
	    dbkey->rec_no >= pgzero[(short)dbkey->file_no].pz_next) 
		return (dberr (S_INVADDR, FIND_PAGE, (DB_ADDR *)dbkey));
 
	/* Berechnung der Seitennummer und des offsets */
	aux1 = dbkey->rec_no -1;
	aux2 = (fe_p = &file_table[(short)dbkey->file_no])->ft_slots;
	pageno = (INT)((aux1 / aux2) + FIRST_PAGE);
	*offset = (short)(fe_p->ft_slsize * (aux1 % aux2) + PAGEHDRSIZE);
 
	/* normale Datei */
#ifndef PAGEHASH
	{
	register int i;

	for (i = 0; i < dynamic; ++i) {
		if ((pe_p = page_table[i])->file == (short)dbkey->file_no) {
		/* File ist vertreten */
			if (pe_p->pageno == pageno) 
#ifdef MULTI_DB
				if (pe_p->dbase == pDB)
#endif
					break;  /* gefunden */
		}
	}
	if (i == dynamic) {
		if (replace_page (pe_p, pDB, (short)dbkey->file_no, pageno) != S_OKAY)
			return (db_status);
	}
	}
#else
	{
	register short hash = HASH (pageno, dbkey->file_no);
	HASH_LIST *hl_p, **hl_prev;

		hl_prev = &hash_table[hash];
		hl_p = *hl_prev;
		while (hl_p != NULL) {
			if ((pe_p = hl_p->pPage) == NULL)
					return db_error (S_SYSERR, FIND_PAGE);
			if (pe_p->file == (short)dbkey->file_no &&
#if defined(MULTI_DB)
				pe_p->dbase == pDB &&
#endif
				    pe_p->pageno == pageno) {
			// gefunden
					break;
			}
			// nächstes ListenElement
			hl_prev = &hl_p->pHList;
			hl_p = *hl_prev;
		}
		if (hl_p == NULL) {
		// nicht gefunden: neues ListenElement anhängen
		HASH_LIST *pNew;	// neues ListenElement
#if defined(MSWIND)
		// Speicher für neues ListenElement anfordern
			pNew = new HASH_LIST;
			
#else
			pNew = (HASH_LIST *)calloc (1, sizeof(HASH_LIST));
#endif // MSWIND
			if (pNew == NULL)
				return db_error (S_NOMEMORY, FIND_PAGE);
		// gewünschte Seite einlesen
			DBASSERT (replace_page (&pe_p, pDB, (short)dbkey->file_no, pageno));
		// Stelle zum Einfügen noch einaml suchen
			hl_prev = &hash_table[hash];
			hl_p = *hl_prev;
			while (hl_p != NULL) {
				hl_prev = &hl_p->pHList;
				hl_p = *hl_prev;
			}
		// neue Seite Einfügen
			*hl_prev = pNew;
			pNew->pPage = pe_p;
			pNew->pHList = NULL;
			pe_p->hash = hash;
		}
	}
#endif
	pe_p->recently_used = TRUE;
	fe_p->ft_used = TRUE;
	*ppPage = pe_p;

return (db_status = S_OKAY);
}
 
/* Verwalten der Speicherpages nach dem CLOCK- Algorithmus,
   der in seinen Eigenschaften in etwa dem LRU- Algorithmus (Least 
   Recently Used) gleichkommt, aber wesentlich einfacher zu implemen-
   tieren ist. */
int FUNCTYPE replace_page (PAGE_ENTRY **pPage, DBASE *pDB, short filenum, long pageno)
// PAGE_ENTRY **pPage;     /* ausgetauschte bzw. gefundene Page */
// short filenum;  /* Filenummer */
// INT pageno;     /* Pagenummer im File */
{
register short i;
register PAGE_ENTRY *pe_p;
int RC;
 
	for (i = least_recent; TRUE; i = (i + 1) % dynamic) {
	/* Suchen einer Page, die Austauschbedingung genuegt */
		pe_p = page_table[i];
		if (!pe_p->recently_used) {
		/* Page kann ausgetauscht werden */
			if (pe_p->modified) {
			/* Page bei Bedarf wegschreiben */
				DBASSERT (dio_out (pe_p));
				pe_p->modified = FALSE;
			}
			pe_p->recently_used = TRUE;
			pe_p->file = filenum;
			pe_p->pageno = pageno;
#ifdef PAGEHASH
			if (pe_p->hash != NONE) {
			/* alten Eintrag löschen */
			HASH_LIST *hl_p, **hl_prev;

				hl_prev = &hash_table[pe_p->hash];
				hl_p = *hl_prev;
				while (hl_p != NULL) {
					if (pe_p == hl_p->pPage) {
					// Page gefunden, freigeben des HList
						*hl_prev = hl_p->pHList;
#if defined(MSWIND)
						DELETE (hl_p);
#else
						free ((char *)hl_p);
#endif // MSWIND
						break;
					}
					hl_prev = &hl_p->pHList;
					hl_p = *hl_prev;
				}
			}
#endif
#ifdef MULTI_DB
			pe_p -> dbase = pDB;
			pe_p -> pg_pagesize = pDB -> db_pagesize;
#endif                  
			if (filenum >= 0 && dio_in (pe_p) != S_OKAY)
				return (db_status);
			*pPage = pe_p;
			least_recent = (i + 1) % dynamic;
			return (db_status = S_OKAY);
		} else 
			pe_p->recently_used = FALSE;
	}
}
 
 
/* Einlesen einer Seite in den Speicher */
 
static int FUNCTYPE dio_in (PAGE_ENTRY *pe_p)
// register PAGE_ENTRY *pe_p;      /* Zeiger auf Page im Speicher */
{
register int desc;              /* Filedescriptor */
long addr;                      /* Seek-Adresse im File */
register unsigned n;            /* Anzahl der gelesenen/geschriebenen Bytes */
int RC; 
register FILE_ENTRY *ft_p;
	
#if defined(MULTI_DB)
	ft_p = &pe_p -> dbase -> db_ftab[pe_p -> file];
#else	// MULTI_DB
	ft_p = &file_table[pe_p -> file];
#endif	// MULTI_DB

	addr = (long)pe_p -> pageno * pe_p -> pg_pagesize;

#if defined(MSWIND)
	if (ft_p -> ft_pIStream != NULL) {
	// CompoundFile
	LPSTREAM pIStream = ft_p -> ft_pIStream;
	LARGE_INTEGER li;
	ULONG cbRead = 0;
	HRESULT hr = NOERROR;
		
		LISet32 (li, addr);	
		hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
		if (FAILED(hr))
			return db_error (S_STG_SEEKERROR, DIO_IN, hr);
		
		hr = pIStream -> Read (pe_p -> buff, pe_p -> pg_pagesize, &cbRead);
		if (FAILED(hr))
			return db_error (S_STG_READERROR, DIO_IN, hr);
			
#ifdef STATISTICS
		if(statistics) ++read_cnt;
#endif
		if (cbRead < pe_p -> pg_pagesize) {
		// weniger gelesen als geplant
			memset (&(pe_p -> buff[cbRead]), '\0', (size_t)((ULONG)pe_p -> pg_pagesize - cbRead));
			((INT *)(pe_p -> buff))[0] = MAXPOSLONG;  // neue Seite
			hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
			if (FAILED(hr))
				return db_error (S_STG_SEEKERROR, DIO_IN, hr);
				
			hr = pIStream -> Write (pe_p -> buff, pe_p -> pg_pagesize, &cbRead);
			if (FAILED(hr)) {
				DBASSERT (db_flush (FLUSH_ALLDATA, pe_p -> dbase));	// alles wegschreiben
				return db_error (S_NOSPACE, DIO_IN);
			}
#ifdef STATISTICS
			if (statistics) ++write_cnt;
#endif
			if (cbRead != pe_p -> pg_pagesize) {	// Schreibfehler 
				DBASSERT (db_flush (FLUSH_ALLDATA, pe_p -> dbase));	// alles wegschreiben
				return db_error (S_NOSPACE, DIO_IN);
			}
		}
	} else {
#endif // MSWIND
	// normale DateiVariante
		DBASSERT (file_open (ft_p));
		desc = ft_p -> ft_desc;
		lseek (desc, addr, 0);                  /* Einstellen Fileposition */
#ifdef MSWIND
		n = _lread (desc, (LPSTR)pe_p -> buff, pe_p -> pg_pagesize);
#else
		n = read (desc, (char *)pe_p -> buff, pe_p -> pg_pagesize);  /* Einlesen der Daten */
#endif
#ifdef STATISTICS
		if(statistics) ++read_cnt;
#endif
		if (n < pe_p -> pg_pagesize) {
		/* weniger gelesen als geplant */
			memset (&(pe_p -> buff[n]), '\0', pe_p -> pg_pagesize -n);
			((INT *)(pe_p -> buff))[0] = MAXPOSLONG;  /* neue Seite */
			lseek (desc, addr, 0);
#ifdef MSWIND
			n = _lwrite (desc, (LPSTR)pe_p -> buff, pe_p -> pg_pagesize);
#if defined(SINGLEFILE)
			file_close (ft_p);
#endif // SINGLEFILE
#else
			n = write (desc, (char *)pe_p -> buff, pe_p -> pg_pagesize);
#endif
#ifdef STATISTICS
			if (statistics) ++write_cnt;
#endif
			if (n != pe_p -> pg_pagesize) {
			/* Schreibfehler */
				DBASSERT (db_flush (FLUSH_ALLDATA, pe_p -> dbase));            /* alles wegschreiben */
				return (dberr (S_NOSPACE, DIO_IN));
			}
		}
#if defined(SINGLEFILE) && defined(MSWIND)
		else
			DBASSERT (file_close (ft_p));
#endif
#if defined(MSWIND)
	}
#endif // MSWIND

return (db_status = S_OKAY);
}
 
/* Ausgeben einer Speicherseite */
static int FUNCTYPE dio_out (PAGE_ENTRY *pe_p)
// register PAGE_ENTRY _huge * pe_p;     /* Speicherseite */
{
register int desc;              /* Filedescriptor */
register FILE_ENTRY *ft_p;
PGZERO *pPage0;
int RC;
#if defined(BACKUP)
int iLocBackup;
#endif

#if defined(MULTI_DB)
DBASE *pDB = pe_p -> dbase;

	ft_p = &pDB -> db_ftab[pe_p -> file];
	pPage0 = pDB -> db_pztab;

#if defined(BACKUP)
	iLocBackup = pDB -> db_bflag;
#endif	// BACKUP

#else	// MULTI_DB

	ft_p = &file_table[pe_p -> file];
	pPage0 = pgzero;

#if defined(BACKUP)
	iLocBackup = backup_flag;
#endif	// BACKUP

#endif	// MULTI_DB

#if defined(BACKUP)
	if (iLocBackup >= 0 &&                 /* backup enabled */
	    ((INT *)(pe_p -> buff))[0] - (INT)pPage0[pe_p->file].bdate <= 0) {
	// erstes Schreiben seit dbtouch --> Backup dieser Page 
	register PAGE_ENTRY *bp_p;

		(bp_p = backup_page) -> file = pe_p -> file;
		bp_p -> pageno = pe_p -> pageno;
		bp_p -> pg_pagesize = pe_p -> pg_pagesize;
		bp_p -> dbase = pe_p -> dbase;
		DBASSERT (backup (bp_p));
	}
#endif

	if (pe_p -> pageno && ((INT *)(pe_p -> buff))[0] != MAXPOSLONG)
	/* nicht Seite 0 und Seite nicht neu */
		*((time_t *)pe_p -> buff) = time (NULL); /* Zeit merken */

#if defined(MSWIND)
	if (ft_p -> ft_pIStream != NULL) {
	LPSTREAM pIStream = ft_p -> ft_pIStream;
	LARGE_INTEGER li;
	HRESULT hr = NOERROR;
	
		LISet32 (li, (long)pe_p -> pageno * (long)pe_p -> pg_pagesize);
		hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
		if (FAILED(hr))
			return db_error (S_STG_SEEKERROR, DIO_OUT, hr);
		
		pIStream -> Write (pe_p -> buff, pe_p -> pg_pagesize, NULL);
		if (FAILED(hr))
			return db_error (S_STG_WRITEERROR, DIO_OUT, hr);
	} else {
#endif // MSWIND
		if (ft_p -> ft_access != O_RDWR) return (dberr (S_ACCESS, DIO_OUT));
		DBASSERT (file_open (ft_p));
		desc = ft_p->ft_desc;
	
	// Seite wegschreiben
#if defined(MSWIND)
		_llseek (desc, (long)pe_p -> pageno * (long)pe_p -> pg_pagesize, 0);
		_lwrite (desc, (LPSTR)pe_p -> buff, pe_p -> pg_pagesize);
#if defined(SINGLEFILE)
		DBASSERT (file_close (ft_p));
#endif //SINGLEFILE
	}
#else
	lseek (desc, (long)pe_p -> pageno * pe_p -> pg_pagesize, 0);
	write (desc, pe_p -> buff, pe_p -> pg_pagesize);
#endif // MSWIND

#if defined(STATISTICS)
	if (statistics) ++write_cnt;
#endif // STATISTICS

return (db_status = S_OKAY);
}

 
#ifdef BACKUP
/* Ablegen einer Page der DB am Ende der Backupdatei */
 
static int FUNCTYPE backup (PAGE_ENTRY *pe_p)
// register PAGE_ENTRY _huge *pe_p;
{
register int desc;
int RC;
register FILE_ENTRY *ft_p;
	
#if defined(MULTI_DB)
	ft_p = &pe_p -> dbase -> db_ftab[pe_p -> dbase -> db_bflag];
#else	// MULTI_DB
	ft_p = &file_table[backup_flag];
#endif	// MULTI_DB

/* alte Page einlesen */
	DBASSERT (dio_in (pe_p));
	if (((INT *)(pe_p->buff))[0] == MAXPOSLONG)
	/* wenn neue Seite gespeichert werden soll */
		return (dberr (S_BACKUP, BACK_UP));

/* DB-Adresse verschlüsseln */
	((INT *)(pe_p->buff))[0] = pe_p->file*MAXPAGES + pe_p->pageno;

/* Page ans Ende der Backupdatei schreiben */
#if defined(MSWIND)
	if (ft_p -> ft_pIStream != NULL) {
	LPSTREAM pIStream = ft_p -> ft_pIStream;
	LARGE_INTEGER li;
	ULONG cbWritten = 0;
	HRESULT hr = NOERROR;
			
		LISet32 (li, 0);
		hr = pIStream -> Seek (li, STREAM_SEEK_END, NULL);
		if (FAILED(hr))
			return db_error (S_STG_SEEKERROR, BACK_UP, hr);
			
		hr = pIStream -> Write (pe_p->buff, pe_p -> pg_pagesize, &cbWritten);
		if (FAILED(hr))
			return db_error (S_STG_WRITEERROR, BACK_UP, hr);
			
		if (cbWritten  < pe_p -> pg_pagesize)
			return db_error (S_NOSPACE, BACK_UP);
	} else {
#endif // MSWIND
		DBASSERT (file_open (ft_p));
		desc = ft_p -> ft_desc;
		lseek (desc, 0L, 2);    /* ans Ende der Backupdatei positionieren */

#ifdef MSWIND
		if (_lwrite (desc, (LPSTR)pe_p->buff, pe_p -> pg_pagesize) < pe_p -> pg_pagesize)
			return (dberr (S_NOSPACE, BACK_UP));
#if defined(SINGLEFILE)
		DBASSERT (file_close (ft_p));
#endif
	}
#else
	if (write (desc, pe_p->buff, pe_p -> pg_pagesize) < pe_p -> pg_pagesize)
		return (dberr (S_NOSPACE, BACK_UP));
#endif // MSWIND
#ifdef STATISTICS
	if (statistics) ++write_cnt;
#endif

return (db_status = S_OKAY);
}
#endif
 
/* Wegschreiben aller Speicherpages */
int FUNCTYPE EXPORT01 DBFlush(HPROJECT hPr, int iFlush)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return db_flush (iFlush, &db_table[(int)hPr -1]);
}

int FUNCTYPE db_flush (int iFlush, DBASE *pDB)
{
register short i;
register PAGE_ENTRY *pe_p;
 
//	if (pDB == NULL) pDB = act_db;
	TX_ASSERT(NULL != pDB);
	
	for (i = 0; i < no_of_pages; ++i) {
		pe_p = page_table[i];
#ifdef MULTI_DB
		if (iFlush != FLUSH_ALLDATA && pDB != pe_p->dbase) 
			continue;
#endif                          
		if (pe_p->modified) {
		/* Page ist modifiziert worden */
			if (iFlush != FLUSH_NODATA && dio_out (pe_p) != S_OKAY) 
				return (db_status);
		}

	// in jedem Fall Page passivieren
		pe_p->modified = FALSE;
		pe_p->file = -1;
		pe_p->pageno = 0;
		pe_p->recently_used = FALSE;
#ifdef PAGEHASH
		if (pe_p->hash != NONE) {	/* alten Eintrag löschen */
		HASH_LIST *hl_p, **hl_prev;

			hl_prev = &hash_table[pe_p->hash];
			hl_p = *hl_prev;
			while (hl_p != NULL) {
				if (pe_p == hl_p->pPage) {
				// Page gefunden, freigeben des HList
					*hl_prev = hl_p->pHList;
#if defined(MSWIND)                                                
					DELETE (hl_p);
#else
					free ((char *)hl_p);
#endif // MSWIND
					break;
				}
				hl_prev = &hl_p->pHList;
				hl_p = *hl_prev;
			}
		}
		pe_p->hash = NONE;
#endif
#ifdef MULTI_DB
		pe_p->dbase = NULL;
#endif                  
	}       /* for */

return (db_status = S_OKAY);
}
 
/* Freigeben des Pagespeicherplatzes */
void FUNCTYPE db_free (void)
{
short i;

	if (page_table) for (i = 0; i < no_of_pages; i++) {
		if (page_table[i]) {
			delete (char *)page_table[i];
			page_table[i] = NULL;
		}
	}
	
#if defined(BACKUP)
	if (backup_page != NULL) {
		if (backup_page) {
			delete (char *)backup_page;
			backup_page = NULL;
		}
	}
#endif
#ifdef PAGEHASH
// Hashtabelle freigeben
	if (hash_table) {
		for (int j = 0; j < hashsize; ++j) {
		HASH_LIST *pHL = hash_table[j];

			while (NULL != pHL) {
			HASH_LIST *pHLNext = pHL -> pHList;

				delete pHL;
				pHL = pHLNext;
			}
		}
		delete [] hash_table;
		hash_table = NULL;
	}
#endif
	DELETE (page_table);
	ActPageSize = 0;
}
