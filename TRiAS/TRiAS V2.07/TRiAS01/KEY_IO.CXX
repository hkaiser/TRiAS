/* Routinen fuer elemantare IO- Operationen bei Key-Filezugriffen       */
/* File: KEY_IO.C               last update: 28. Juli 1989              */

#include "trias01p.hxx"

#if !defined(PAGEHASH)
short last_page;
#endif

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Einlesen einer Page für Key-Verarbeitung -----------------------------------
extern "C" 
int FUNCTYPE dio_get (PAGE_NO page_no, NODE **pg_ptr, SUGGESTPAGE *pSP)
{
	PAGE_ENTRY *pe_p;
	register FILE_ENTRY *ft_p = &file_table[working_file];
	int RC;
	DBASE *pDB = act_db;
	
	TX_ASSERT(NULL != pDB);
	TX_ASSERT(NULL != pg_ptr);
	TX_ASSERT(working_file != NONE);
	//	if (working_file == NONE) return (dberr(S_NOWORK, DIO_GET));
	
#ifndef PAGEHASH
	for (last_page = 0; last_page < dynamic; ++last_page) {
		if ((pe_p = page_table[last_page])->file == working_file) {
			/* File ist vertreten */
#ifdef MULTI_DB
			if (pe_p->dbase == pDB)
#endif
				if (pe_p->pageno == page_no) break;
		}
	}
	if (last_page == dynamic)
		DBASSERT (replace_page (&pe_p, pDB, working_file, page_no));
#else
	{
		// wenn VergleichsPage gegeben, dann zuerst testen, ob Page noch da ist
		if (NULL != pSP && NULL != pSP -> m_pPE) {
			pe_p = pSP -> m_pPE;	// bisherige Page
			if (pe_p -> file == pSP -> m_iFileNo &&
#ifdef MULTI_DB
				pe_p -> dbase == pSP -> m_pDB &&
#endif // MULTI_DB
				pe_p -> pageno == pSP -> m_lPageNo)
			{
				// immer noch die gleiche Page, nicht nachladen
				*pg_ptr = (NODE *)(pe_p -> buff);		// Ergebnis
				
				pe_p -> recently_used = true;
				ft_p -> ft_used = true;
				return (db_status = S_OKAY);
			}
		}
		
		// entweder neue Page oder keine Vergleichspage gegeben
		register short hash = HASH (page_no, working_file);
		HASH_LIST *hl_p, **hl_prev;
		
		hl_prev = &hash_table[hash];
		hl_p = *hl_prev;
		while (hl_p != NULL) {
			if ((pe_p = hl_p->pPage) == NULL)
				return db_error (S_SYSERR, DIO_GET);
			if (pe_p->file == working_file &&
#ifdef MULTI_DB
				pe_p->dbase == pDB &&
#endif                              
				pe_p->pageno == page_no) 
			{
				// gefunden 
				break;
			}
			// nächstes ListenElement
			hl_prev = &hl_p->pHList;
			hl_p = *hl_prev;			
		}
		if (hl_p == NULL) {
			// nicht gefunden
			HASH_LIST *pNew;	// neues ListenElement
			
			pNew = new HASH_LIST;
			if (pNew == NULL) return db_error (S_NOMEMORY, DIO_GET);
			
			// gesuchte Seite einlesen
			DBASSERT (replace_page (&pe_p, pDB, working_file, page_no));
			
			// Stelle zum Einfügen noch einmal suchen
			hl_prev = &hash_table[hash];
			hl_p = *hl_prev;
			while (hl_p != NULL) {
				hl_prev = &hl_p->pHList;
				hl_p = *hl_prev;
			}
			
			// Seite einfügen
			*hl_prev = pNew;
			pNew->pPage = pe_p;
			pNew->pHList = NULL;	// letztes Element
			pe_p->hash = hash;
		}
	}
#endif
	*pg_ptr = (NODE *)(pe_p->buff);		// Ergebnis
	
	pe_p->recently_used = true;
	ft_p->ft_used = true;
	
	if (NULL != pSP) {
		pSP -> m_pPE = pe_p;		// VergleichsPage liefern
		pSP -> m_iFileNo = pe_p -> file;
		pSP -> m_lPageNo = pe_p -> pageno;
		pSP -> m_pDB = pDB;
	}
	
	return (db_status = S_OKAY);
}


/* 'modified'-Flag fuer eine Page setzen */
int FUNCTYPE dio_touch (PAGE_NO page_no)
// PAGE_NO page_no;
{
	register PAGE_ENTRY *pe_p;
	DBASE *pDB = act_db;
	
	TX_ASSERT(pDB);
	TX_ASSERT(working_file != NONE);
	//	if (working_file == NONE) return (dberr(S_NOWORK, DIO_GET));
	
#ifndef PAGEHASH
	{
		register int p;
		
		for (p = 0; p < no_of_pages; ++p) 
			if (((pe_p = page_table[p])->file == working_file) &&
#ifdef MULTI_DB
				(pe_p->dbase == pDB) &&
#endif
				(pe_p->pageno == page_no))
				break;
			if (p == no_of_pages) return (dberr (S_FAULT, DIO_TOUCH));
	}
#else
	{
		register short hash = HASH (page_no, working_file);
		HASH_LIST *hl_p, **hl_prev;
		
		hl_prev = &hash_table[hash];
		hl_p = *hl_prev;
		while (hl_p != NULL) {
			if ((pe_p = hl_p->pPage) == NULL)
				return db_error (S_SYSERR, DIO_TOUCH);
			if (pe_p->file == working_file &&
#ifdef MULTI_DB
				pe_p->dbase == pDB &&
#endif                              
				pe_p->pageno == page_no) {
				/* gefunden */
				break;
			}
			// nächstes Listenelement
			hl_prev = &hl_p->pHList;
			hl_p = *hl_prev;
		}
		if (hl_p == NULL)	// nicht gefunden
			return db_error (S_FAULT, DIO_TOUCH);
	}
#endif
	pe_p->modified = TRUE;
	
	return (db_status = S_OKAY);
}
