/* Einlesen des Steuerfiles					 */
/* File: INITTAB.C              last update: 28. Februar 1990   */

#include "trias01p.hxx"

#include <dwd.h>

#define NOCOPYRIGHT
#include <dbversio.h>

// #define _DEBUG_ISTREAM

#if defined(_DEBUG_ISTREAM)
#include <strmhelp.hxx>
#endif // _DEBUG

extern "C" {
	
	FILE_ENTRY *file_table = NULL;
	short size_ft = 0;
	
	KEY_ENTRY *key_table = NULL;
	short size_kt = 0;
	
	REC_ENTRY *record_table = NULL;
	short size_rt = 0;
	
}	// extern "C"

// Flag, welches darüber entscheidet, ob Copyright hart abgetestet wird -------
FLAG g_fCopyrightFlag = TRUE;		// default: Fehler führt zum Abbruch

extern "C" FLAG FUNCTYPE EXPORT01 SetCopyrightFlag (FLAG newFlag) 
{
FLAG oldFlag = g_fCopyrightFlag;
	
	g_fCopyrightFlag = newFlag;
	return oldFlag;
}

// Eigentliche Initialisierungsroutine ----------------------------------------
#ifndef MULTI_DB
FLAG dbopen;            /* TRUE, wenn DB eroffnet ist */
#else  //MULTI_DB

_TRIAS01_ENTRY DBASE *act_db = NULL;           /* aktuelle bearbeitete DB */
_TRIAS01_ENTRY DBASE *pActivatedDB = NULL;		/* aktuell aktivierte DB */

_TRIAS01_ENTRY DBASE db_table[MAXDB] = {       /* DB-Tabelle */
	/* db_table[i].db_name ist Freikennzeichen wenn gleich NULL */
	/* fuer "fdbopen.c" ist db_table[i].db_sft Freikennzeichen  */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 0 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 1 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 2 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 3 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 4 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 5 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 6 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 7 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 8 */
	{ NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0, 0L },        /* 9 */
};
#endif

long DBVersion = 0L;
unsigned short PageSize = PAGESIZE;

/* Initialisieren der internen Datenbasistabellen */
static BYTE s_cbCopyright[COPYRIGHT_LEN];

int FUNCTYPE inittab (char *dbname, struct dbpasswd *dwd, int dbh, BOOL fOpenRO) 
{
register int ft_s;
#ifndef MSWIND
unsigned int num;
#endif // MSWIND
long lDummy;
	
	/* Einlesen des Copyrights */
	_dos_read(dbh, s_cbCopyright, COPYRIGHT_LEN, &num);
	if (g_fCopyrightFlag && 
		mycrypt (s_cbCopyright, COPYRIGHT_LEN) & 0xffff != COPYRIGHT_CRC)
	{
		return (dberr (S_VERSION, INITTAB));
	}

	/* Einlesen der Tabellengroessen */
	_dos_read(dbh, (void *)&size_ft, sizeof(short), &num);
	_dos_read(dbh, (void *)&size_kt, sizeof(short), &num);
	_dos_read(dbh, (void *)&size_rt, sizeof(short), &num);
#ifdef BACKUP
	_dos_read(dbh, (char *)&backup_flag, sizeof(short), &num);
#endif
	/* lesen der File-Tabelle */
	ft_s = bitcnt (dwd->dw_access);
	if (ft_s) {
		register int i; /* Laufvariable */
		
		if (ft_s > size_ft) return (dberr (S_ACCESS, INITTAB));
		TX_TRY(file_table = new FILE_ENTRY [size_ft]);
		if (file_table == NULL)
			return (dberr (S_NOMEMORY, INITTAB));
		
		for (i = 0; i < size_ft; ++i) {
		register FILE_ENTRY *ft_p;
			
			ft_p = &file_table[i];
			if (bit (dwd->dw_access, i)) {
				/* Filetabelleneintrag  einlesen */
#if defined(__386__) || defined(WIN32)
				short locDesc;
				
				_dos_read (dbh, (void *)ft_p, sizeof(char *), &num);
				_dos_read (dbh, (void *)&locDesc, sizeof(short), &num);
				ft_p->ft_desc = (int)locDesc;	// short --> int
				_dos_read (dbh, (void *)&ft_p->ft_status, 
					sizeof(FT_ENTRY)-sizeof(char *)-sizeof(short), 
					&num);
#else // NormalFall -- 16-Bit Umgebeung
				_dos_read (dbh, (void *)ft_p, sizeof(FT_ENTRY), &num);
#endif
				/* Zugriffsmode vorgeben */
#ifdef MSWIND
				if (fOpenRO) {
					ft_p->ft_oldaccess =
						ft_p->ft_access = OF_READ;
				} else {
					ft_p->ft_oldaccess =
						ft_p->ft_access = (bit (dwd->dw_rw, i)) ? OF_READWRITE : OF_READ;
				}
				ft_p->ft_status = TO_INIT;
				ft_p->ft_pIStream = NULL;
#else
				ft_p-> ft_oldaccess =
					ft_p->ft_access = (bit (dwd->dw_rw, i)) ? O_RDWR : O_RDONLY;
				ft_p->ft_status = CLOSED;	// für file_open
#endif
				ft_p->ft_used = FALSE;
#ifdef HOLD
				ft_p->ft_refer = NONE;
#endif
			} else {
				/* Tabelleneintrag überspringen */
				lseek (dbh, (long)sizeof(FT_ENTRY), 1);
				ft_p-> ft_oldaccess =
					ft_p->ft_access = O_NOACC;  /* kein Zugriff */
				ft_p->ft_status = CLOSED;   /* fuer file_open */
				ft_p->ft_used = FALSE;
			}
		}
	} else {
		file_table = NULL;
		return (db_error (S_NOFILES, INITTAB));
	}
	
	{
	/* Generieren der vollständigen Filenamen */
	register char *path, *name_t;
	register short i;
	char filename[FILENMLEN];
		
		if ((path = getpath (NULL, dbname, strlen (dbname))) == NULL)
			return (dberr (S_NOMEMORY, INITTAB));

		TX_TRY(name_t = new char [size_ft * (_MAX_PATH +1) +1]);
		if (name_t == NULL) {
			DELETE_VEC (path);
			return (dberr (S_NOMEMORY, INITTAB));
		}
		
		memset (name_t, '\0', size_ft * (_MAX_PATH +1) +1);
		for (i = 0; i < size_ft; ++i) {
			_dos_read (dbh, filename, FILENMLEN, &num);
			if (bit (dwd->dw_access, i)) {
				strcpy (name_t, path);
				//				if (*name_t) _fstrcat (name_t, slashp);
				strcat (name_t, filename);
				file_table[i].ft_name = name_t;
				name_t += _MAX_PATH +1;
			} else 
				file_table[i].ft_name = NULL;
		}
		DELETE_VEC (path);
	}
	
	if (size_kt) {
		TX_TRY(key_table = new KEY_ENTRY [size_kt]);
		if (key_table == NULL)
			return (dberr (S_NOMEMORY, INITTAB));
		_lread (dbh, (VOID *)key_table, size_kt*sizeof(KEY_ENTRY));
	} else
		key_table = NULL;
	
	if (size_rt) {
		TX_TRY(record_table = new REC_ENTRY [size_rt]);
		if (record_table == NULL)
			return (dberr (S_NOMEMORY, INITTAB));
		_lread (dbh, (VOID *)record_table, sizeof (REC_ENTRY)*size_rt);
	} else
		record_table = NULL;
	
// VersionsNummer einlesen
DBVersion = 0L;

	_lread (dbh, (VOID *)&DBVersion, sizeof(DBVersion));
	
	lDummy = PAGESIZE;
	_lread (dbh, (VOID *)&lDummy, sizeof(lDummy));
	PageSize = (short)lDummy;
	
// Page 0 Tabelle der aktuellen DB anlegen
	if (dio_pzinit() != S_OKAY) return db_status;
	
	return (db_status = S_OKAY);
}


// Version für CompoundFiles --------------------------------------------------
#if defined(MSWIND)

#include <resstrg.h>
#include <commonvu.hxx>

const wchar_t g_cwDict[] = L"DatenBankStruktur";

short FUNCTYPE InitTables (
	LPSTORAGE pIStorage, DBASE *pDB, const char *pName, unsigned __int64 dwAccess, BOOL fRO)
{
// Dictionary eröffnen
LPSTREAM pIStream = NULL;
//ResString resDict (IDS_DBDICTIONARY, 32);
HRESULT hr = pIStorage -> OpenStream (g_cwDict/*WideString(resDict)*/, 0, 
		STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
		0, &pIStream);
	if (FAILED(hr)) return db_error (S_INVDB, INITTAB);
	
#if defined(_DEBUG_ISTREAM)
	pIStream = (IStream *)new CStreamWrapper (pIStream, resDict);
#endif // _DEBUG_ISTREAM
	
// Copyright einlesen und überprüfen
ULONG cbRead = 0;
	
	pIStream -> Read (s_cbCopyright, COPYRIGHT_LEN, &cbRead);
	if (g_fCopyrightFlag && 
		mycrypt (s_cbCopyright, COPYRIGHT_LEN) & 0xffff != COPYRIGHT_CRC)
	{
		pIStream -> Release();
		return db_error (S_VERSION, INITTAB);
	}	
	
	// Tabellen etc. einlesen
	pIStream -> Read (&pDB -> db_sft, sizeof(short), &cbRead);
	pIStream -> Read (&pDB -> db_skt, sizeof(short), &cbRead);
	pIStream -> Read (&pDB -> db_srt, sizeof(short), &cbRead);
#ifdef BACKUP
	pIStream -> Read (&pDB -> db_bflag, sizeof(short), &cbRead);
#endif
	
// Einlesen der File-Tabelle
short ft_s = bitcnt (dwAccess);
	
	if (ft_s) {
#if defined(OLD_PWD_IN_STORAGE)
		if (ft_s > pDB -> db_sft) {
			pIStream -> Release();
			return db_error (S_ACCESS, INITTAB);
		}
#endif // OLD_PWD_IN_STORAGE

		TX_TRY(pDB -> db_ftab = new FILE_ENTRY [pDB -> db_sft]);
		if (pDB -> db_ftab == NULL) {
			pIStream -> Release();
			return db_error (S_NOMEMORY, INITTAB);
		}
		for (short i = 0; i < pDB -> db_sft; ++i) {
			FILE_ENTRY *ft_p = &pDB -> db_ftab[i];
			
			if (bit (dwAccess, i)) {
				/* Filetabelleneintrag  einlesen */
#if defined(__386__) || defined(WIN32)
				short locDesc;
				
				pIStream -> Read (ft_p, sizeof(char *), &cbRead);
				pIStream -> Read (&locDesc, sizeof(short), &cbRead);
				ft_p->ft_desc = (int)locDesc;	// 16Bit --> 32Bit
				pIStream -> Read (&ft_p->ft_status, 
					sizeof(FT_ENTRY)-sizeof(char *)-sizeof(short), 
					&cbRead);
#else // NormalFall -- 16-Bit Umgebeung
				pIStream -> Read (ft_p, sizeof(FT_ENTRY), &cbRead);
#endif
				/* Zugriffsmode vorgeben */
				if (fRO) {
					ft_p->ft_oldaccess =
						ft_p->ft_access = STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
				} else {
					ft_p->ft_oldaccess =
						ft_p->ft_access = STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
				}
				ft_p->ft_status = TO_INIT;
				ft_p->ft_used = FALSE;
				ft_p->ft_pIStream = NULL;
			} else {
			// Tabelleneintrag überspringen
			LARGE_INTEGER li;
				
				LISet32 (li, sizeof(FT_ENTRY));
				pIStream -> Seek (li, STREAM_SEEK_CUR, NULL);
				ft_p -> ft_oldaccess =
					ft_p -> ft_access = O_NOACC;  /* kein Zugriff */
				ft_p -> ft_status = CLOSED;   /* fuer file_open */
				ft_p -> ft_used = FALSE;
				ft_p->ft_pIStream = NULL;
			}
		}
	} else {
		pDB -> db_ftab = NULL;
		pIStream -> Release();
		return db_error (S_NOFILES, INITTAB);
	}
	
// Einlesen der Streambezeichner
char *pFNames = NULL;

	TX_TRY(pFNames = new char [pDB -> db_sft*(FILENMLEN +1)]);
	if (pFNames == NULL) {
		pIStream -> Release();
		return db_error (S_NOMEMORY, INITTAB);
	}
	
	for (short i = 0; i < pDB -> db_sft; ++i) {
	FILE_ENTRY *ft_p = &pDB -> db_ftab[i];
		
		if (bit (dwAccess, i)) {
		// einlesen des StreamNamens
			ft_p -> ft_name = pFNames;
			pFNames += FILENMLEN +1;
			memset (ft_p -> ft_name, '\0', FILENMLEN+1);
			pIStream -> Read (ft_p -> ft_name, FILENMLEN, &cbRead);
			
		// öffnen des Streams
			hr = pIStorage -> OpenStream (
				WideString(ft_p -> ft_name), 0,
				ft_p -> ft_access, 0, 
				&ft_p -> ft_pIStream);
			
			if (FAILED(hr)) {
				pIStream -> Release();
				return db_error (S_NOFILE, INITTAB);
			}
			
#if defined(_DEBUG_ISTREAM)
			ft_p -> ft_pIStream = (IStream *)new CStreamWrapper (ft_p -> ft_pIStream, ft_p -> ft_name);
#endif // _DEBUG_ISTREAM
			
			ft_p -> ft_status = OPEN;
		} else {
		// Tabelleneintrag überspringen
		LARGE_INTEGER li;
			
			LISet32 (li, FILENMLEN);
			pIStream -> Seek (li, STREAM_SEEK_CUR, NULL);
			ft_p -> ft_name = NULL;
		}
	}
	
	// Einlesen der übrigen Tabellen
	if (pDB -> db_skt) {
		TX_TRY(pDB -> db_ktab = new KEY_ENTRY [pDB -> db_skt]);
		if (pDB -> db_ktab == NULL) {
			pIStream -> Release();
			return db_error (S_NOMEMORY, INITTAB);
		}
		pIStream -> Read (pDB -> db_ktab, pDB -> db_skt*sizeof(KEY_ENTRY), NULL);
	} else
		pDB -> db_ktab = NULL;
	
	if (pDB -> db_srt) {
		TX_TRY(pDB -> db_rtab = new REC_ENTRY [pDB -> db_srt]);
		if (pDB -> db_rtab == NULL) {
			pIStream -> Release();
			return db_error (S_NOMEMORY, INITTAB);
		}
		pIStream -> Read (pDB -> db_rtab, pDB -> db_srt*sizeof(REC_ENTRY), NULL);
	} else
		pDB -> db_rtab = NULL;
	
	// VersionsNummer einlesen
	pDB -> db_version = 0L;
	pIStream -> Read (&pDB -> db_version, sizeof(long), NULL);
	
long lDummy = PAGESIZE;
	
	pIStream -> Read (&lDummy, sizeof(long), NULL);
	pDB -> db_pagesize = (unsigned short)lDummy;
	
	pIStream -> Release();		// schließen
	
// Page 0 initialisieren
	if (InitPageZeroTable (pDB) != S_OKAY) return db_status;
	
	return (db_status = S_OKAY);
}

int ModifyDBVersion (HPROJECT hPr, long lVersion)
{
int num = (int)hPr -1;

	if (num < 0 || num >= MAXDB) 
		return db_error (S_ACTIV, INITTAB);

DBASE *pDB = &db_table[num];
IStorage *pIStg = pDB -> db_pIStorage;

// Dictionary eröffnen
IStream *pIStream = NULL;

HRESULT hr = pIStg -> OpenStream (g_cwDict, 0, 
		STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
		0, &pIStream);
	if (FAILED(hr)) return db_error (S_INVDB, INITTAB);
	
LARGE_INTEGER li;
LARGE_INTEGER uli;
long lError = S_OKAY;

	li.QuadPart = 0;
	hr = pIStream -> Seek (li, STREAM_SEEK_END, (ULARGE_INTEGER *)&uli);
	if (FAILED(hr)) {
		lError = S_STG_SEEKERROR;
		goto labelError;
	}
	uli.QuadPart = uli.QuadPart - 2*sizeof(long);
	hr = pIStream -> Seek (uli, STREAM_SEEK_SET, NULL);
	if (FAILED(hr)) {
		lError = S_STG_SEEKERROR;
		goto labelError;
	}

// neue Version schreiben
	hr = pIStream -> Write (&lVersion, sizeof(long), NULL);
	if (FAILED(hr)) {
		lError = S_STG_WRITEERROR;
		goto labelError;
	}

	pDB -> db_version = lVersion;
	pDB -> db_fDirty = TRUE;
	pIStream -> Commit (STGC_DEFAULT);
	pIStream -> Release();		// schließen

	return (db_status = S_OKAY);

labelError:
	return db_error (lError, INITTAB);
}

#endif // MSWIND

