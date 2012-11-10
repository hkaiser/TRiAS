/* Page 0 Handling Routines                                     */
/* File: PGZERO.C               last update: 23. Oktober 1989   */

#include "trias01p.hxx"

#define NOCOPYRIGHT
#include <dbversio.h>
#include "syncdb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(MSWIND)
BOOL operator== (const PGZERO &pg1, const PGZERO &pg2)
{
	if (pg1.pz_dchain != pg2.pz_dchain)
		return false;
	if (pg1.pz_next != pg2.pz_next)
		return false;
	if (pg1.bdate != pg2.bdate)
		return false;

	return true;
}
#endif // MSWIND

extern "C" 
int FUNCTYPE EXPORT01 DBPageZeroAlloc(HPROJECT hPr, short fno, long *loc)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return db_pzalloc (fno, loc, hPr);
}

extern "C" 
int FUNCTYPE EXPORT01 DBPageZeroFree(HPROJECT hPr, short fno, long loc)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return db_pzfree (fno, loc, hPr);
}

extern "C" 
int FUNCTYPE EXPORT01 DBPageZeroReRead (HPROJECT hPr)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return db_pzreread (&db_table[(int)hPr -1]);
}

extern "C" 
int FUNCTYPE EXPORT01 DBPageZeroFlush(HPROJECT hPr, int iFlush)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return db_pzflush (iFlush, &db_table[(int)hPr -1]);
}

// neu einlesen der PGZERO-Tabelle --------------------------------------------
extern "C" 
int FUNCTYPE db_pzreread (DBASE *pDB)
{
FILE_ENTRY FAR *ft_p;
int RC;		// FehlerCode
#if !defined(MSWIND)
unsigned int num;
#endif

//	if (pDB == NULL) pDB = act_db;
	TX_ASSERT(NULL != pDB);
	
    for (short i = 0; i < pDB -> db_sft; ++i) {
		if (((ft_p = &pDB -> db_ftab[i])->ft_access) == O_NOACC)
			continue;

		if (pDB -> db_bflag >= 0 && i == pDB -> db_bflag)
			continue;

#if defined(MSWIND)
		if (ft_p -> ft_pIStream != NULL) {
		LPSTREAM pIStream = ft_p -> ft_pIStream;
		LARGE_INTEGER li;
		ULONG cbRead = 0;
		HRESULT hr = NOERROR;
					
			LISet32 (li, (long)COPYRIGHT_LEN);
			hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
			if (FAILED(hr))
				return db_error (S_STG_SEEKERROR, PZREREAD, hr);
			
			hr = pIStream -> Read (&pDB -> db_pztab[i], sizeof(PGZERO), &cbRead);
			if (FAILED(hr) || cbRead != sizeof(PGZERO))
				return (db_error (S_STG_READERROR, PZREREAD, hr));
		} else {
#endif // MSWIND
		short desc;

			DBASSERT (file_open (ft_p));
#if defined(MSWIND)
			_llseek (desc = ft_p->ft_desc, (long)COPYRIGHT_LEN, 0);
			if (_lread (desc, &pgzero[i], sizeof(PGZERO)) != sizeof(PGZERO))
#else
			lseek (desc = ft_p->ft_desc, (long)COPYRIGHT_LEN, 0);
			if (_dos_read (desc, &(pgzero[i]), sizeof (PGZERO), &num) != 0)
#endif
				return (db_error (S_NOSPACE, PZREREAD));
			DBASSERT (file_close (ft_p));
#if defined(MSWIND)
		}
#endif
	}
	return (db_status = S_OKAY);
}
 
 
/* Wegschreiben/Verwerfen der Page zero table */
extern "C" 
int FUNCTYPE db_pzflush (int iFlush, DBASE *pDB)
{
register short i;
register short desc;
register FILE_ENTRY FAR *ft_p;
int RC;		// FehlerCode
#if !defined(MSWIND)
unsigned int num;
#else
bool fCommit = (iFlush & FLUSH_COMMITDATA) ? true : false;
#endif

	iFlush &= ~FLUSH_COMMITDATA;

//	if (pDB == NULL) pDB = act_db;		// für alle Fälle
	TX_ASSERT(NULL != pDB);
	
	if (iFlush != FLUSH_NODATA) {
	// wenn PGZERO's weggeschrieben werden sollen
		for (i = 0; i < pDB -> db_sft; ++i) {
			if (((ft_p = &pDB -> db_ftab[i])->ft_access) == O_NOACC)
				continue;
			if (pDB -> db_bflag >= 0 && i == pDB -> db_bflag)
				continue;

#if defined(MSWIND)
			if (ft_p -> ft_pIStream != NULL) {
//				if (ft_p->ft_access == STGM_READ | STGM_SHARE_DENY_WRITE) 
//					continue;

			LPSTREAM pIStream = ft_p -> ft_pIStream;
			LARGE_INTEGER li;
			ULONG cbWritten = 0;
			HRESULT hr = NOERROR;
						
				LISet32 (li, (long)COPYRIGHT_LEN);
				hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
				if (FAILED(hr)) 
					return db_error (S_STG_SEEKERROR, PZFLUSH, hr);

			PGZERO pgZero;

				hr = pIStream -> Read (&pgZero, sizeof(PGZERO), NULL);
				if (FAILED(hr))
					return db_error (S_STG_READERROR, PZFLUSH, hr);

				if (pgZero == pDB -> db_pztab[i])
					continue;	// nur schreiben, wenn notwendig

				hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
				if (FAILED(hr)) 
					return db_error (S_STG_SEEKERROR, PZFLUSH, hr);
				hr = pIStream -> Write (&pDB -> db_pztab[i], sizeof(PGZERO), &cbWritten);
				if (FAILED(hr) || cbWritten != sizeof(PGZERO))
					return db_error (S_STG_WRITEERROR, PZFLUSH, hr);
			} else {
#endif // MSWIND
				if (ft_p->ft_access == O_RDONLY) continue;
				DBASSERT (file_open (ft_p));
#if defined(MSWIND)
				_llseek (desc = ft_p->ft_desc, (long)COPYRIGHT_LEN, 0);
				if (_lwrite (desc, (LPCSTR)&pgzero[i], sizeof(PGZERO)) != sizeof(PGZERO))
#else
				lseek (desc = ft_p->ft_desc, (long)COPYRIGHT_LEN, 0);
				if (_dos_write (desc, &(pgzero[i]), sizeof (PGZERO), &num) != 0)
#endif
					return (db_error (S_NOSPACE, PZFLUSH));
				
				DBASSERT (file_close (ft_p));
#if defined (MSWIND)
			}
#endif
		}
	} else {
	FILE_ENTRY *bf_p;

	// wenn die Resultate verworfen werden sollen
		if (pDB -> db_bflag < 0) return S_OKAY;	// keine BackupDatei

	// alte PGZERO's wieder einlesen
	        bf_p = &pDB -> db_ftab[pDB -> db_bflag];
#if defined(MSWIND)
		if (bf_p -> ft_pIStream != NULL) {
		LPSTREAM pIStream = bf_p -> ft_pIStream;
		LARGE_INTEGER li;
		HRESULT hr = NOERROR;
		ULONG cbRead = 0;
					
			LISet32 (li, (long)sizeof(PGZERO)+COPYRIGHT_LEN);
			hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
			if (FAILED(hr))
				return db_error (S_STG_SEEKERROR, PZFLUSH, hr);

			hr = pIStream -> Read (pDB -> db_pztab, pDB -> db_sft*sizeof(PGZERO), &cbRead);
			if (FAILED(hr) || cbRead != pDB -> db_sft*sizeof(PGZERO))
				return db_error (S_STG_READERROR, PZFLUSH, hr);
		} else {
#endif
			DBASSERT (file_open (bf_p));
#if defined(MSWIND)
			_llseek (desc = bf_p -> ft_desc, sizeof(PGZERO)+COPYRIGHT_LEN, 0);
	        	_lread (desc, pgzero, size_ft*sizeof(PGZERO));
#else
		        lseek (desc = bf_p -> ft_desc, sizeof(PGZERO)+COPYRIGHT_LEN, 0);
	        	_dos_read (desc, pgzero, size_ft*sizeof(PGZERO), &num);
#endif
			DBASSERT (file_close (bf_p));
#if defined(MSWIND)
		}
#endif // MSWIND
	}

#if defined(MSWIND)
// Storage Commit'n
	if (fCommit && !pDB -> db_fOpenedRO && NULL != pDB -> db_pIStorage) {
	// Streams rausschreiben
	HRESULT hr;

#if defined(_USE_COMPRESSED_STREAM)
		for (int i = 0; i < pDB -> db_sft; ++i) {
			if (NULL != pDB -> db_ftab[i].ft_pIStream) {
				hr = pDB -> db_ftab[i].ft_pIStream -> Commit (STGC_DEFAULT);
				if (FAILED(hr))
					return db_error (S_STG_FLUSHERROR, PZFLUSH, hr);
			}
		}
#endif // defined(_USE_COMPRESSED_STREAM)

	// Storage rausschreiben
	DWORD rgStgc = STGC_DEFAULT;

		if (IsWin50() && IsWinNT())
			rgStgc |= STGC_CONSOLIDATE;

		hr = pDB -> db_pIStorage -> Commit (rgStgc);
		if (FAILED(hr))
			return db_error (S_STG_FLUSHERROR, PZFLUSH, hr);
	}	
#endif // MSWIND

	return (db_status = S_OKAY);
}
 
 
/* Einrichten eines neuen Record-Slot mit Hilfe der Page zero Daten */
extern "C" 
int FUNCTYPE db_pzalloc (short fno, long *loc, HPROJECT hPr)
// short fno; /* Filenummer */
// INT *loc;  /* Nummer des eingerichteten Record */
{
DB_ADDR dba(hPr);
PGZERO FAR *pz_p = &pgzero[fno];
FILE_ENTRY FAR *ft_p = &file_table[fno];
INT pg;
int RC;

// Testen der Zugriffsrechte
/*	if (ft_p -> ft_pIStream != NULL) {
		if (ft_p->ft_access == STGM_READ | STGM_DIRECT)
			return (dberr (S_ACCESS, PZALLOC));
	} else 
*/	if (ft_p->ft_access == O_RDONLY) 
		return (dberr (S_ACCESS, PZALLOC));

	if (ft_p->ft_access == O_NOACC) 
		return (dberr (S_ACCESS, PZALLOC));

	if (ft_p->ft_type == KEYFILE) {
	NODE *nd;
 
		if (working_file != fno) 
			return (dberr (S_NOWORK, PZALLOC));
			
		if (pz_p->pz_dchain == NONE) {
			if (pz_p->pz_next == MAXRECORDS -1)
				return (dberr (S_NOSPACE, PZALLOC));
			pg = (pz_p->pz_next)++;
		} else {
			pg = pz_p->pz_dchain;
			DBASSERT (dio_get (pg, (NODE FAR **)&nd));
			pz_p->pz_dchain = *(INT *)(nd->nd_slots);
			memset (nd, '\0', sizeof(NODE));
			DBASSERT (dio_touch (pg));
		}
	} else {
	/* Typ == DATA oder HTREE */
	char *ptr;
 
		if (!(pz_p->pz_dchain)) {
		/* keine Leichen im File vorhanden */
			if (pz_p->pz_next == MAXRECORDS)
				return (dberr (S_NOSPACE, PZALLOC));
			pg = (pz_p->pz_next)++;
		} else {
		/* Verwenden der ersten Leiche, weitersetzen des chain-Pointers */
			pg = pz_p->pz_dchain;
			dba.file_no = fno;
			dba.rec_no = pg;
			DBASSERT (tdb_read (&dba, (void **)&ptr));
			pz_p->pz_dchain = *((INT *)(ptr)+1);
			memset (ptr, '\0', file_table[fno].ft_slsize);
			DBASSERT (tdb_write (&dba, NULL));
		}
	}
	*loc = pg;
 
return (db_status = S_OKAY);
}
 
 
/* Freigeben eines Record-Slots, eintragen in die Chain-Pointerkette */
extern "C" 
int FUNCTYPE db_pzfree (short fno, long loc, HPROJECT hPr)
// short fno;      Filenummer
// INT loc;        freizugebende Record-Nummer
{
DB_ADDR dba(hPr);
INT FAR *ip = &(pgzero[fno].pz_dchain);
FILE_ENTRY *ft_p = &file_table[fno];
int RC;

// Testen der Zugriffsrechte
/*	if (ft_p -> ft_pIStream != NULL) {
		if (!(ft_p->ft_access & STGM_READWRITE|STGM_WRITE))
			return (dberr (S_ACCESS, PZFREE));
	} else 
*/	if (ft_p->ft_access == O_RDONLY) 
		return (dberr (S_ACCESS, PZFREE));

	if (ft_p->ft_access == O_NOACC) 
		return (dberr (S_ACCESS, PZFREE));

	if (ft_p->ft_type == KEYFILE) {
	NODE *nd;
 
		if (working_file != fno) return (dberr (S_NOWORK, PZFREE));
		DBASSERT (dio_get (loc, (NODE FAR **)&nd));
		*((INT *)(nd->nd_slots)+1) = MAXPOSLONG;
		*(INT *)(nd->nd_slots) = *ip;
		*ip = loc;
		DBASSERT (dio_touch (loc));
	} else {
	char *ptr;
 
		dba.file_no = fno;
		dba.rec_no = loc;
		DBASSERT (tdb_read (&dba, (void **)&ptr));
		*(INT *)ptr = MAXPOSLONG;       /* Satz ist geloescht */
		*((INT *)(ptr)+1) = *ip;        /* Rueckverkettung */
		*ip = loc;
		DBASSERT (tdb_write (&dba, NULL));
	}
 
return (db_status = S_OKAY);
}
 
