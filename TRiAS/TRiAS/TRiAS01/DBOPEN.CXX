/* Eroeffnen einer Datenbasis                                   */
/* File: DBOPEN.C               last update: 28. februar 1990   */

#include "trias01p.hxx"
#include "syncdb.hxx"

#include "trias01r.h"

#include <limits.h>
#include <sys/types.h>			// _stat
#include <sys/stat.h>

#include <resstrg.h>

#include <dbdtempl.h>
#include "resource.h"

#define INITGUIDS
#include <dirisole.h>
#include <dwd.h>

#include <dbd.h>
#include <dbd.hxx>

//#define _DEBUG_ISTORAGE
#if defined(_DEBUG_ISTORAGE)
#include <stghelp.hxx>
#endif // _DEBUG

#include <ospace/file/path.h>
#include <ospace/time/timedate.h>
#include <ospace/std/set>

#include "PerfCounters.h"

#if defined(MSWIND)
#define close(fh)	_lclose(fh)
#endif // MSWIND

///////////////////////////////////////////////////////////////////////////////
// 
extern int g_rgStartMode;		// STARTMODE_Normal

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);

BOOL CreateFullGeoDBPath (const char *pFullPath);

/*VARARGS 2*/
extern "C"
HPROJECT FUNCTYPE EXPORT01 z_open (
		LPSTR dbfile, LPSTR uname, LPSTR passwd, BOOL fRO, DWORD dwMode)
{
	return z_open_ex (dbfile, uname, passwd, fRO, dwMode, TRUE);
}

// testen, ob die gegebene Datei existiert
inline bool FileExists (LPCSTR pcName)
{
	return (0xFFFFFFFF == GetFileAttributes (pcName)) ? false : true; 
}

extern "C" 
HRESULT EXPORT01 z_test_open (LPCSTR pcName, HPROJECT *phPr)
{
	for (int i = 0; i < MAXDB; ++i) {
		if ((NULL != db_table[i].db_name) && !strcmp (db_table[i].db_name, pcName)) {
		// diese DB ist bereits eröffnet
			if (NULL != phPr)
				*phPr = (HPROJECT)(i+1);		// HPROJECT == 0 ist Fehler
			return S_OK;		
		}
	}
	if (NULL != phPr)
		*phPr = (HPROJECT)0;
	return S_FALSE;
}

extern "C" 
HRESULT EXPORT01 z_addref_database (HPROJECT hPr)
{
#if defined(_USE_OPENREFCNT)
	if (NULL == hPr) 
		return E_INVALIDARG;
// gegebenes Projekt verwenden
short db_slot = (short)hPr -1;

	_ASSERTE(0 <= db_slot && db_slot < MAXDB);

register DBASE *db_p = &db_table[db_slot];

	if (NULL == db_p -> db_name && NULL == db_p -> db_pIStorage) 
		return E_UNEXPECTED;

	++db_p -> db_RefCnt;
#endif // defined(_USE_OPENREFCNT)

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Backup eines Datenfiles anlegen
inline 
void FreeHandleIfAppropriate(HANDLE &rhFind)
{
	if (INVALID_HANDLE_VALUE != rhFind) {
		FindClose(rhFind);
		rhFind = INVALID_HANDLE_VALUE;
	}
}

HRESULT BackupDatafile (LPCSTR pcName, int iFilesToLeave = 3)
{
	_ASSERTE(iFilesToLeave > 0);
	if (NULL == pcName)
		return E_POINTER;

HANDLE hFind = INVALID_HANDLE_VALUE;

	COM_TRY {
	// zuerst Kopie anlegen
	os_path findName(pcName);

		if (iFilesToLeave > 0) {
		// nur, wenn auch Dateien stehen bleiben sollen
		os_time_and_date now;
		os_path filename(pcName);
		os_string basename(filename.base());

			now = os_time_and_date::now();
			basename += now.to_string(".%Y%m%d.%H%M%S");
			filename.base(basename);
			if (!CopyFile(pcName, (LPCSTR)filename, FALSE))
				return HRESULT_FROM_WIN32(GetLastError());
		}

	// danach dafür sorgen, daß lediglich die letzten 'iFilesToLeave' Kopien 
	// stehen bleiben
	WIN32_FIND_DATA findData;

		findName.base(findName.base() + ".*.*");
		memset(&findData, '\0', sizeof(WIN32_FIND_DATA));
	
		hFind = FindFirstFile((LPCSTR)findName, &findData);
		if (INVALID_HANDLE_VALUE != hFind) {
		set<os_string> files;

			do {
				files.insert(findData.cFileName);
			} while (FindNextFile (hFind, &findData));
			FreeHandleIfAppropriate(hFind);

		// jetzt alle Dateien bis auf die letzten (neuesten) 'iFilesToLeave' löschen
			if (files.size() > iFilesToLeave) {
			set<os_string>::reverse_iterator rit = files.rbegin();
			set<os_string>::reverse_iterator end = files.rend();

				advance (rit, iFilesToLeave);
				for (/**/; rit != end; ++rit) {
				os_path fileToDelete (pcName);

					fileToDelete.filename(*rit);
					DeleteFile((LPCSTR)fileToDelete);
				}
			}
		}
		else {
		// wenigstens die gerade kopierte Datei muß da sein
			_ASSERTE(INVALID_HANDLE_VALUE != hFind);
		}

	} COM_CATCH_OP(FreeHandleIfAppropriate(hFind));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Datenbank eröffnen
extern "C"
HPROJECT FUNCTYPE EXPORT01 z_open_ex (
		LPSTR dbfile, LPSTR uname, LPSTR passwd, BOOL fRO, DWORD dwMode, BOOL fHandleErrors)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

register struct dbpasswd *dwd;
int namelen, db_slot;
char *name;
int *dummy;
#ifdef MSWIND
OFSTRUCT of;	// Dateiverwaltungsstruktur
#endif // MSWIND
int dbf;	// Dateihandle

#ifdef MULTI_DB
register int i;
#endif // MULTI_DB

BOOL fReportError = true;
short RC = S_OKAY;	// FehlerCode
#if defined(PROJECT_LOCKING)
HFILE fhShared = HFILE_ERROR;
#endif //PROJECT_LOCKING

#ifdef MSWIND
	name = new char [_MAX_PATH+5];
	namelen = _MAX_PATH;
#else // MSWIND
/* Steuerblockdatei eroeffnen */
	namelen = strlen (dbfile);
	name = calloc (namelen+5, 1);
#endif // MSWIND
	if (name == NULL) {
		dberr (S_NOMEMORY, Z_OPEN);
		return (HPROJECT)S_NOMEMORY;
	}
	memset (name, '\0', _MAX_PATH+5);

	if (dbfile != NULL) {
		strcpy (name, dbfile);
#if !defined(MSWIND)
		strcat (name, STB_EXTENSION);
#endif // MSWIND
	}

#ifdef MULTI_DB
/* Bereitstellen eines DB-slots */
	db_slot = -1;
	for (i = 0; i < MAXDB; ++i) {
		if (db_table[i].db_name == NULL && db_table[i].db_pIStorage == NULL) 
		{
			db_slot = i;
			break;		// freien Slot gefunden
		} 
#if defined(_USE_OPENREFCNT)
		else if ((NULL != db_table[i].db_name) && !strcmp (db_table[i].db_name, name)) {
		// diese DB ist bereits eröffnet
			z_addref_database((HPROJECT)(i+1));
			pActivatedDB = act_db = &db_table[i];		// aktivieren
			return (HPROJECT)(i+1);		// HPROJECT == 0 ist Fehler
		}
#endif // defined(_USE_OPENREFCNT)
	}

	if (db_slot == -1) {
	// kein freier Slot mehr vorhanden
		RC = S_MAXDB;
		goto labelOpenError;
	} else {
		i = db_slot;
		db_table[i].db_name = "Slot besetzt";
	}
#endif // MULTI_DB

#if defined(MSWIND)
// Überprüfen, ob die angegebene Datei ein CompoundFile ist, wenn ja, eröffnen
#if defined(WIN32)
	if (*name == '\0') {	// temporäre Datei erzeugen
	HPROJECT hPr = CreateTempStorageProject (&db_table[i]);

		if (NULL == hPr)
			db_table[i].db_name = NULL;
		
		return hPr;	
	}
#endif // WIN32

	if (!FileExists (name)) {
		::SetLastError (HRESULT_FROM_ERRCODE(S_INVDB));
		db_table[i].db_name = NULL;
		return NULL;
	}

	if (StgIsStorageFile (WideString(name)) == NOERROR) {
	// ggf. Backup dieser Datei anlegen
		if (!fRO && g_rgStartMode & 0x02) 		// STARTMODE_BackupDatafile
			BackupDatafile(name);
//		else
//			BackupDatafile(name, 0);			// alle existierenden Backups löschen

	// Datenbank eröffnen
	HPROJECT hPr = OpenStorageProjectEx (NULL, &db_table[i], name, uname, 
		passwd, fRO, false, dwMode, &CLSID_DirisProject, fHandleErrors);

		if (NULL == hPr) 	// Aufräumen, wenn Fehler
			db_table[i].db_name = NULL;
		return hPr;
	}

char cbBuffer[64];

	if (NULL == uname) {
		_splitpath (name, NULL, NULL, cbBuffer, NULL);
		uname = cbBuffer;
	}

#if defined(PROJECT_LOCKING)
// MultiUserZugriff realisieren
	if (!fRO && OpenFile (name, &of, OF_EXIST) != HFILE_ERROR) {
	// DB existiert und soll mit Schreibrechten eröffnet werden
		RC = InitSharedAccess (&fhShared, name, uname);
		if (RC != S_OKAY || fhShared == HFILE_ERROR) {
		// Nutzer will keinen ROZugriff bei bereits geöffnetem Projekt
			if (RC == S_OKAY) RC = S_ACCESS;
			fReportError = false;
			goto labelOpenError;
		}
		if (fhShared == 0) {
			RC = S_OPENRO;
			fReportError = false;
			goto labelOpenError;
		}
	} else
		fhShared = 0;
#endif // PROJECT_LOCKING
					
	if ((dbf = OpenFile ((LPSTR)name, &of, OF_READ)) == -1) {
#else // MSWIND
	if ((dbf = open (name, O_RDONLY+O_BINARY)) < 0) {
#endif // MSWIND
		RC = S_INVDB;		
		goto labelOpenError;
	}
/* Passworteintrag lesen */
	if ((dwd = getdwnam (uname, dbfile)) == NULL) {
		RC = S_ACCESS;
		close (dbf);
		goto labelOpenError;
	}

/* Passwort vergleichen */
	if (*dwd->dw_passwd &&
	     strcmp ((char FAR *)crypt (passwd, dwd->dw_passwd), dwd->dw_passwd)) 
	{
		RC = S_ACCESS;
		close (dbf);
		goto labelOpenError;
	}

#ifndef MULTI_DB
	if (dbopen) db_close ();                /* nur eine DB offen halten */
#endif // MULTI_DB

/* interne Tabellen einrichten */
	if ((RC = inittab (name, dwd, dbf, fRO)) != S_OKAY) {
		fReportError = false;
		close (dbf);
		goto labelOpenError;
	}

/* E/A-Tabellen, Pages etc. einrichten */
	if ((RC = dio_init (NULL)) != S_OKAY) {
		fReportError = false;
		close (dbf);
		goto labelOpenError;
	}
	close (dbf);

/* Handler fuer S_INVADDR installieren */
	err_install (S_INVADDR, (INT_FUNC *)einvaddr, (INT_FUNC **)&dummy);

#ifdef MULTI_DB
/* Diese Datenbasis ist die aktuelle */
	{
	DBASE *new_db = &db_table[i];

		name[namelen] = '\0';
		new_db->db_name = name;         /* DB-Name */
		new_db->db_sft = size_ft;       /* Groesse der Dateitabelle */
		new_db->db_skt = size_kt;       /* Anzahl der Schluessel */
		new_db->db_srt = size_rt;       /* Anzahl der Records */
		new_db->last_file = 0;          /* zuletzt angefasste Datei */
		new_db->db_work = NONE;         /* working_file */
		new_db->db_field = NONE;	/* KeyFieldNumber */
		new_db->db_lvl = 0;             /* Level im BTree */
		new_db->db_ftab = file_table;   /* Dateitabelle */
		new_db->db_ktab = key_table;    /* Schluesseltabelle */
		new_db->db_rtab = record_table; /* Recordtabelle */
		new_db->db_pztab = pgzero;      /* Page 0 Tabelle */
		new_db->db_slots = NULL;        /* Position im BTree */
		new_db->db_parent = NULL;
		new_db->db_version = DBVersion;	/* VersionsNummer */
		new_db->db_pagesize = PageSize;	/* PageGröße */
#if defined(PROJECT_LOCKING)
		new_db->db_fhShared = fhShared;	/* LockingDateiHandle */
#endif // PROJECT_LOCKING
#ifdef BACKUP
		new_db->db_bflag = backup_flag; /* Backupdatei */
#endif // BACKUP
#if defined(MSWIND)
		new_db->db_pIStorage = NULL;	// kein CompoundFile
		new_db->db_fOpenedRO = fRO;
		new_db->db_fOpenedAsCopy = FALSE;
		new_db->db_fDirty = FALSE;
		new_db->db_hProjectRelated = NULL;
#endif
	// neue DB aktivieren
		z_activate ((HPROJECT)(i + 1));
	}
	return (HPROJECT)(i + 1);

#else // MULTI_DB
	dbopen = true;
	return (db_status = S_OKAY);
#endif // MULTI_DB

labelOpenError:		// FehlerAusgang

#if defined(MSWIND)
#if defined(PROJECT_LOCKING)
	if (fhShared > 0) {
	// LockDatei schließen und sofort löschen
	char *pcbT = NULL;
		
		if (pcbT = strrchr (name, '.'))
			*pcbT = '\0';		// Erweiterung ändern
		strcat (name, LOK_EXTENSION);				
		
		_lclose (fhShared);
		unlink (name);
		fhShared = 0;
	}
#endif // PROJECT_LOCKING

	DELETE_VEC (name);
#else
	free (name);
#endif
	db_table[i].db_name = NULL;
	if (fReportError) dberr (RC, Z_OPEN);
	::SetLastError(HRESULT_FROM_ERRCODE(RC));

	return (HPROJECT)NULL;
}

extern "C" 
HPROJECT FUNCTYPE EXPORT01 z_open_storage (LPSTORAGE pIStorage, BOOL fRO, BOOL fTemp)
{
	return z_open_storage_ex (pIStorage, fRO, fTemp, &CLSID_DirisProject, TRUE);
}

extern "C" 
HPROJECT FUNCTYPE EXPORT01 z_open_storage_ex (
	LPSTORAGE pIStorage, BOOL fRO, BOOL fTemp, const CLSID *pClsID, BOOL fHandleErrors)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

short RC = EC_OKAY;

#ifdef MULTI_DB
/* Bereitstellen eines DB-slots */
int i = 0;
int db_slot = -1;

	for (; i < MAXDB; ++i) {
		if (db_table[i].db_name == NULL && db_table[i].db_pIStorage == NULL) {
			db_slot = i;
			break;		// freien Slot gefunden
		} 
#if defined(_USE_OPENREFCNT)
		else if (db_table[i].db_pIStorage == pIStorage) {
		// diese DB ist bereits eröffnet
			z_addref_database((HPROJECT)(i+1));
			pActivatedDB = act_db = &db_table[i];		// aktivieren
			return (HPROJECT)(i+1);		// HPROJECT == 0 ist Fehler
		}
#endif // defined(_USE_OPENREFCNT)
	}

	if (db_slot == -1) {
	// kein freier Slot mehr vorhanden
		RC = S_MAXDB;
		goto labelOpenError;
	} else {
		i = db_slot;
		db_table[i].db_name = "Slot besetzt";
	}
#endif // MULTI_DB

	return OpenStorageProjectEx (pIStorage, &db_table[i], NULL, NULL, NULL, fRO, fTemp, 0L, pClsID, fHandleErrors);

labelOpenError:
	db_table[i].db_name = NULL;
	dberr (RC, Z_OPEN);
	::SetLastError(HRESULT_FROM_ERRCODE(RC));

	return (HPROJECT)NULL;
}

extern "C" 
HPROJECT FUNCTYPE EXPORT01 z_open_storage_pbd (LPSTORAGE pIStorage, BOOL fRO)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

short RC = EC_OKAY;

#ifdef MULTI_DB
/* Bereitstellen eines DB-slots */
int i = 0;
int db_slot = -1;

	for (; i < MAXDB; ++i) {
		if (db_table[i].db_name == NULL && db_table[i].db_pIStorage == NULL) {
			db_slot = i;
			break;		// freien Slot gefunden
		} 
#if defined(_USE_OPENREFCNT)
		else if (db_table[i].db_pIStorage == pIStorage) {
		// diese DB ist bereits eröffnet
			z_addref_database((HPROJECT)(i+1));
			pActivatedDB = act_db = &db_table[i];		// aktivieren
			return (HPROJECT)(i+1);		// HPROJECT == 0 ist Fehler
		}
#endif // defined(_USE_OPENREFCNT)
	}

	if (db_slot == -1) {
	// kein freier Slot mehr vorhanden
		RC = S_MAXDB;
		goto labelOpenError;
	} else {
		i = db_slot;
		db_table[i].db_name = "Slot besetzt";
	}
#endif // MULTI_DB

return OpenStoragePbd (pIStorage, &db_table[i], NULL, fRO);

labelOpenError:
	db_table[i].db_name = NULL;
	dberr (RC, Z_OPEN);
	::SetLastError(HRESULT_FROM_ERRCODE(RC));

	return (HPROJECT)NULL;
}

/*
extern "C" long FUNCTYPE EXPORT01 zopen_ (char *s_dbfile, int l_dbfile, 
					  char *s_uname, int l_uname, 
					  char *s_passwd, int l_passwd)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

char dbfile[81], uname[81], passwd[81];
register char *cptr;

        memset (dbfile, '\0', 81);
        memset (uname, '\0', 81);
        memset (passwd, '\0', 81);
        strncpy (dbfile, s_dbfile, (int)l_dbfile > 80 ? 80 : (int)l_dbfile);
        strncpy (uname, s_uname, (int)l_uname > 80 ? 80 : (int)l_uname);
        strncpy (passwd, s_passwd, (int)l_passwd > 80 ? 80 : (int)l_passwd);
        if ((cptr = strrlchr (dbfile, ' ')) != NULL) *cptr = '\0';
        if ((cptr = strrlchr (uname, ' ')) != NULL) *cptr = '\0';
        if ((cptr = strrlchr (passwd, ' ')) != NULL) *cptr = '\0';

HPROJECT hPr = z_open (dbfile, uname, passwd, false);

return (INT)(void *)hPr -1;
}
*/

#if defined(PROJECT_LOCKING)
// Initialisieren eines MultiUserZugriffs -------------------------------------
short FUNCTYPE InitSharedAccess (HFILE *pfhShared, char *pDBName, char *pUName)
{
// 1. LockingDateiNamen generieren
	*pfhShared = HFILE_ERROR;
	
char *pLName = new char [_MAX_PATH];

	if (pLName == NULL) return db_error (S_NOMEMORY, Z_OPEN);
	strcpy (pLName, pDBName);

char *pcbT = strrchr (pLName, '.');

	if (pcbT) *pcbT = '\0';
	strcat (pLName, LOK_EXTENSION);		// ".lok" anhängen
		
// 2. Versuchen Locking Datei anzulegen
OFSTRUCT of;
unsigned int oldErrMode = SetErrorMode (SEM_FAILCRITICALERRORS);
HFILE fh = OpenFile (pLName, &of, OF_CREATE|OF_READWRITE);

	DELETE_OBJ (pLName);
	if (fh == HFILE_ERROR) {
	// es hat ein anderer die Finger drauf
		SetErrorMode (oldErrMode);	// vorherigen Zustand wieder einstellen
		*pfhShared = AskToOpenRO();
		return S_OKAY;
	}

// 3. Wieder schließen, da OF_CREATE keine OF_SHARE_... Flags akzeptiert
	_lclose (fh);
	
// 4. Versuchen diese Datei mit OF_SHARE_DENY_WRITE zu öffnen
	fh = OpenFile (NULL, &of, OF_REOPEN|OF_READWRITE|OF_SHARE_DENY_WRITE);
	SetErrorMode (oldErrMode);	// vorherigen Zustand wieder einstellen
	
	if (fh == HFILE_ERROR) {
	// jemand ist dazwischengerutscht
		fh = AskToOpenRO();
	} else {
	// alles ok, Info über aktuellen Nutzer wegschreiben
	char cbBuff[30] = { '\0' };
	short iLen = strlen (pUName);
		
		wsprintf (cbBuff, "%02d:%-17.17s\n", iLen, pUName);
		_lwrite (fh, cbBuff, sizeof(cbBuff));
	}
	*pfhShared = fh;	// FileHandle übergeben
	return S_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
static char cbOutString[_MAX_PATH +1] = { '\0' };
static char cbOutCaption[_MAX_PATH +1] = { '\0' };

extern "C" HINSTANCE g_hInstance;

HFILE FUNCTYPE AskToOpenRO (void)
{
// MessageBox anzeigen, in der gefragt wird, ob Projekt nur RO geöffnet 
// werden soll
// StringResourcen laden
	LoadString (g_hInstance, IDS_OPENROTEXT, cbOutString, sizeof(cbOutString));
	LoadString (g_hInstance, IDS_OPENROCAPTION, cbOutCaption, sizeof(cbOutCaption));

int iRes = MessageBox (__hWndM, cbOutString, cbOutCaption,
		       MB_TASKMODAL|MB_YESNO|MB_ICONQUESTION);
		       
	if (iRes == IDYES) 
		return 0;	// RO eröffnen
	
	return HFILE_ERROR;	// nicht öffnen
}

#if defined(WIN32)

BOOL FUNCTYPE AskToOpenCopy (void)
{
// MessageBox anzeigen, in der gefragt wird, ob Projekt als Kopie geöffnet 
// werden soll
// StringResourcen laden
	LoadString (g_hInstance, IDS_OPENCOPYTEXT, cbOutString, sizeof(cbOutString));
	LoadString (g_hInstance, IDS_OPENROCAPTION, cbOutCaption, sizeof(cbOutCaption));

int iRes = MessageBox (__hWndM, cbOutString, cbOutCaption,
		       MB_TASKMODAL|MB_YESNO|MB_ICONQUESTION);
		       
	if (iRes == IDYES) 
		return true;	// RO eröffnen

	return false;	// nicht öffnen
}

#endif

#endif // PROJECT_LOCKING


#if defined(MSWIND)
#if defined(WIN32)

BYTE *ReadResource (HINSTANCE hInstance, int iResID, DWORD &dwResSize)
{
BYTE *lpResult = NULL;

//  Resource laden
HRSRC hFindRes = FindResource (hInstance, MAKEINTRESOURCE (iResID), MAKEINTRESOURCE (ID_DBDTEMPLATE));
HGLOBAL hRes = LoadResource (hInstance, hFindRes);

	if (!hFindRes || !hRes) return NULL;

//  Resource im Speicher festhalten
BYTE *lpResource = (BYTE *)LockResource (hRes);

	if (lpResource) {	    // wenn Resource erfolgreich geladen
	// Resource in Buffer kopieren
		if ((dwResSize = SizeofResource (hInstance, hFindRes)) == 0)
			return NULL;

	// einfach umkopieren
		TX_TRY(lpResult = new BYTE [dwResSize]);
		if (NULL == lpResult) return NULL;

		CopyMemory(lpResult, lpResource, dwResSize);

	// Resource wieder freigeben
		UnlockResource (hRes);
		FreeResource (hRes);
	} else {
	// Resource existiert nicht
		FreeResource (hRes);
		return NULL;
	}
	return lpResult;
}

// Erzeugen eines temporären Projektes ----------------------------------------
HPROJECT FUNCTYPE CreateTempStorageProject (DBASE *pDB)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

HINSTANCE hTrias = GetModuleHandle (NULL);
DWORD dwResSize = 0;
LPBYTE lpRes = (LPBYTE)ReadResource (hTrias, DBD050B, dwResSize);
CDBDictCompoundFile *pDBDict = CDBDictCompoundFile :: CreateInstance (lpRes);
ErrCode EC = EC_NOMEMORY;

	DELETE_OBJ (lpRes);
	if (pDBDict == NULL) {
		db_error (EC_NOMEMORY, Z_OPEN);
		return NULL;
	}

LPSTORAGE pIStorage = NULL;

	EC = pDBDict -> CreateDBEx (NULL, NULL, NULL, &pIStorage);
	DELETE_OBJ (pDBDict);
	if (EC != EC_OKAY) {
		::SetLastError(HRESULT_FROM_ERRCODE(EC));
		return NULL;
	}

	return OpenStorageProject (pIStorage, pDB, NULL, NULL, NULL, false, true);
}

// Umbennen eines Projektes (für SaveAs) --------------------------------------
HRESULT FUNCTYPE RenameStorageProject (HPROJECT hPr, LPCTSTR pszFile)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

	::SetLastError(S_OK);
	return NOERROR;
}

// Umkopieren in ein neues Projekt --------------------------------------------
HRESULT CopyDictionary (IStorage *pIStorage, IStorage *pIStgDest)
{
ResString resDict (ResID(IDS_DBDICTIONARY, NULL), 30);
LPSTREAM pIStrDest = NULL;
HRESULT hr = pIStgDest -> CreateStream (WideString(resDict.Addr()), 
				STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, 
				0, 0, &pIStrDest);
	if (FAILED(hr)) return hr;

LPSTREAM pIStream = NULL;

	hr = pIStorage -> OpenStream (WideString(resDict.Addr()), 
				NULL, STGM_READ | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, 
				0, &pIStream);
	if (FAILED(hr)) {
		pIStrDest -> Release();
		return hr;
	}

ULARGE_INTEGER cb;

	cb.HighPart = cb.LowPart = 0L;
	hr = pIStream -> Seek ((LARGE_INTEGER &)cb, STREAM_SEEK_SET, NULL);
	if (SUCCEEDED(hr)) {
		cb.HighPart = cb.LowPart = ULONG_MAX;
		hr = pIStream -> CopyTo (pIStrDest, cb, NULL, NULL);
	}

	pIStrDest -> Release();
	pIStream -> Release();
	return hr;
}

HRESULT CopyToStorageProject (DBASE *pDB, LPCSTR pcName, IStorage **ppIStorage, 
							  const CLSID *pClsID, LPCSTR pCF)
{
	if (NULL == pDB -> db_pIStorage)
		return ResultFromScode (E_UNEXPECTED);

HRESULT hr = NOERROR;
IStorage *pIStgDest = NULL;
DWORD dwMode = STGM_CREATE | STGM_READWRITE | STGM_TRANSACTED;
int i = 0;

// entscheiden, ob neu anlegen oder als SubStorage verwenden
	if (NULL != ppIStorage && NULL != *ppIStorage) {
		(*ppIStorage) -> AddRef();
		pIStgDest = *ppIStorage;
	} 
	else {
	// nur wenn nicht in bestehendem CompFile erzeugt werden soll
		if (!CreateFullGeoDBPath (pcName)) 	// Pfad sicherstellen
			return ResultFromScode (STG_E_INVALIDNAME);

	// Feststellen, ob diese Datei auf sich selbst kopiert werden soll
	// z.B. bei ReadOnly --> full Access
		if (pcName) {
		STATSTG stg;

			hr = pDB -> db_pIStorage -> Stat (&stg, STATFLAG_DEFAULT);
			if (FAILED(hr)) return hr;		// E_UNEXPECTED

			if (strcmp (pcName, AnsiString (stg.pwcsName)))
				dwMode |= STGM_SHARE_DENY_WRITE;
			CoTaskMemFree (stg.pwcsName);
		} else
			dwMode |= STGM_SHARE_DENY_WRITE;		// TempDateien sowieso

	// ProjektDatei anlegen, wenn Name nicht gegeben ist, dann temporäre Datei erzeugen
		hr = StgCreateDocfile (pcName ? WideString(pcName) : NULL, dwMode, 0, &pIStgDest);
		if (FAILED(hr)) return hr;
	}

// Typ der Datenbank wegschreiben
	if (NULL == pClsID)
		hr = WriteClassStg (pIStgDest, CLSID_DirisProject);
	else
		hr = WriteClassStg (pIStgDest, *pClsID);
	if (FAILED(hr)) goto labelErrorReturn;

	if (NULL == pCF) {
	ResString resClass (ResID(IDS_TRIASFULLNAME130, NULL), 30);
	CLIPFORMAT cf = RegisterClipboardFormat (resClass);

		hr = WriteFmtUserTypeStg (pIStgDest, cf, WideString(resClass));
	} else {
	CLIPFORMAT cf = RegisterClipboardFormat (pCF);

		hr = WriteFmtUserTypeStg (pIStgDest, cf, WideString(pCF));
	}
	if (FAILED(hr)) goto labelErrorReturn;

// alle Streams der DB umkopieren
	hr = CopyDictionary (pDB -> db_pIStorage, pIStgDest);
	if (FAILED(hr)) goto labelErrorReturn;

// Datenbasis aus Cache wegschreiben
	if (S_OKAY != db_flush (FLUSH_ACTDB, pDB)) {	/* alle Pages wegschreiben */
		hr = ResultFromScode (E_FAIL);
		goto labelErrorReturn;
	}
	if (S_OKAY != db_pzflush (FLUSH_ACTDB, pDB)) {	/* alle Page 0 wegschreiben */
		hr = ResultFromScode (E_FAIL);
		goto labelErrorReturn;
	}

// jetzt Daten ansich kopieren
	hr = S_OK;
	for (i = 0; i < pDB -> db_sft; i++) {
	FILE_ENTRY *pFE = &pDB -> db_ftab[i];

	// ZielStream erzeugen
	WStream StrDest;
	
		hr = pIStgDest -> CreateStream (WideString(pFE -> ft_name), 
				STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
				0, 0, StrDest.ppi());
		if (FAILED(hr)) break;
		
	// sicherheitshalber Streamdaten schreiben (wichtig, wenns ein CompressedStream ist)
		hr = pFE -> ft_pIStream -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) break;

	// Stream umkopieren
	ULARGE_INTEGER cb;

		cb.HighPart = cb.LowPart = 0L;
		hr = pFE -> ft_pIStream -> Seek ((LARGE_INTEGER &)cb, STREAM_SEEK_SET, NULL);
		if (SUCCEEDED(hr)) {
			cb.HighPart = cb.LowPart = ULONG_MAX;
			hr = pFE -> ft_pIStream -> CopyTo (StrDest, cb, NULL, NULL);
		}
		if (FAILED(hr)) break;
		hr = StrDest -> Commit(STGC_DEFAULT);
		if (FAILED(hr)) break;
	}

	if (SUCCEEDED(hr)) {
	// alles OK	
		if (NULL != ppIStorage && NULL == *ppIStorage) {	// evtl. Pointer merken
			pIStgDest -> AddRef();
			*ppIStorage = pIStgDest;
		} else if (NULL == ppIStorage)
			hr = pIStgDest -> Commit (STGC_DEFAULT);		// Datei wegschreiben
	}

labelErrorReturn:
	pIStgDest -> Release();		// Datei schließen, bzw. freigeben
	
#if defined(WIN32)
	if (FAILED(hr) && NULL != pDB -> db_name && 
	    NULL != pcName && StgIsStorageFile(WideString(pDB -> db_name))) 
	{
	// IRootStorage für SaveAs verwenden
	IRootStorage *pIRootStg = NULL;

		hr = pDB -> db_pIStorage -> QueryInterface (IID_IRootStorage, (LPVOID *)&pIRootStg);
		if (FAILED(hr)) return hr;

		hr = pIRootStg -> SwitchToFile (WideString(pcName));
		pIRootStg -> Release();
		if (FAILED(hr)) return hr;

		hr = pDB -> db_pIStorage -> Commit (STGC_DEFAULT);
		pDB -> db_fDirty = FALSE;
	}
#endif // WIN32
	return hr;
}

HRESULT FUNCTYPE CopyToStorageProject (HPROJECT hPr, LPCTSTR pszFile, 
	IStorage **ppIStgDest, const CLSID *pClsID, LPCSTR pCF)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

// eigenes Storage besorgen
short db_slot = (short)hPr -1;

	if (db_slot < 0 || db_slot >= MAXDB) 
		return ResultFromScode (E_UNEXPECTED);

DBASE *pDB = &db_table[db_slot]; 

	if (pDB -> db_pIStorage == NULL)
		return ResultFromScode (E_UNEXPECTED);

// Datenbank kopieren
	return CopyToStorageProject (pDB, pszFile, ppIStgDest, pClsID, pCF);
}

#endif // WIN32

// Liefert PIStorage des Projektes --------------------------------------------
HRESULT FUNCTYPE EXPORT01 GetProjectStorage (HPROJECT hPr, LPSTORAGE *ppIStorage)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

short db_slot = (short)hPr -1;

	if (db_slot < 0 || db_slot >= MAXDB) 
		return ResultFromScode (E_UNEXPECTED);

DBASE *pDB = &db_table[db_slot]; 

	if (pDB -> db_pIStorage == NULL)
		return ResultFromScode (E_UNEXPECTED);

//return pDB -> db_pIStorage -> QueryInterface (IID_IStorage, (LPVOID *)ppIStorage);	// Pointer festhalten
	pDB -> db_pIStorage -> AddRef();
	*ppIStorage = pDB -> db_pIStorage;

return NOERROR;
}


static BOOL TestFileRO (LPCSTR pName, BOOL &rRO)
{
struct _stat buf;
BOOL fResult = _stat (pName, &buf);

	if (fResult || !(buf.st_mode & _S_IFREG)) 
		return false;		// keine Datei oder existiert nicht

	rRO = (buf.st_mode & _S_IWRITE) ? false : true;

return true;
}

HPROJECT FUNCTYPE OpenStorageProject (LPSTORAGE pIStg, DBASE *pDB, 
				      LPCSTR pName, LPCSTR pUser, LPCSTR pPWD, 
					  BOOL fRO, BOOL fTemp, DWORD dwMode)
{
	return OpenStorageProjectEx (pIStg, pDB, pName, pUser, pPWD, fRO, fTemp, dwMode, &CLSID_DirisProject, TRUE);
}

// stellt fest, ob das angegebene Verzeichnis die Besonderheiten eines Novell-Verzeichnisses 
// besitzt (sharingcontrol nicht selbst machen)
// vorerst wird dieser Test an Hand der Existenz einer Datei 'TRiAS.Dir' erledigt
namespace {
	inline bool IsNovellDrive (LPCSTR pcName)
	{
#if defined(_USE_BADLY_HACKED_NOVELL_PATCH)
		if (!(g_dwFlags & REG_USE_NOVELLTESTCODE))
			return false;	// nicht auf 'Novell' testen

	os_path path (pcName);

		path.filename("TRiAS.Dir");
		return ((DWORD)-1 == ::GetFileAttributes (os_string(path).c_str())) ? false : true;
#else
	return false;
#endif // defined(_USE_BADLY_HACKED_NOVELL_PATCH)
	}
}

HPROJECT FUNCTYPE OpenStorageProjectEx (
	LPSTORAGE pIStg, DBASE *pDB, LPCSTR pName, LPCSTR pUser, LPCSTR pPWD, 
	BOOL fRO, BOOL fTemp, DWORD dwMode, const CLSID *pClsID, BOOL fHandleErrors)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

// Eröffnen der ProjektDatei
short RC = S_OKAY;	// FehlerCode
BOOL fReportError = true;
HRESULT hr = NOERROR;
LPSTORAGE pIStorage = NULL;

	pDB -> db_fOpenedAsCopy = fRO;		// initialisieren

	if (pIStg == NULL) {
		if (0 == dwMode) {
			if (fRO)
				dwMode = STGM_READ | STGM_SHARE_DENY_NONE;
			else
				dwMode = STGM_READWRITE | (IsNovellDrive(pName) ? STGM_SHARE_DENY_NONE : STGM_SHARE_DENY_WRITE);
//				dwMode = STGM_READWRITE | STGM_SHARE_DENY_WRITE;
		} 
		else if ((dwMode & STGM_READWRITE) || (dwMode & STGM_WRITE)) {
			if (IsNovellDrive (pName)) {
				dwMode &= ~STGM_SHARE_DENY_WRITE;
				dwMode |= STGM_SHARE_DENY_NONE;
			} 
			else if (!(dwMode & (STGM_SHARE_DENY_NONE|STGM_SHARE_DENY_READ|STGM_SHARE_EXCLUSIVE)))
				dwMode |= STGM_SHARE_DENY_WRITE;	// wenn nichts anderes gegeben ist
		}
		dwMode |= STGM_TRANSACTED;

//		if (fTemp) dwMode |= STGM_DELETEONRELEASE;	// STG_INVALIDFUNCTION
#if defined(WIN32)
		if (IsWin40() && !IsWinNT() && !fRO)		// nicht bei RO
			dwMode |= STGM_NOSCRATCH;
#endif // WIN32

		hr = StgOpenStorage (WideString(pName), NULL, dwMode, 0, 0, &pIStorage);

#if defined(_DEBUG_ISTORAGE)
		pIStorage = (IStorage *)new CStorageWrapper (pIStorage, pName);
#endif // _DEBUG_ISTORAGE

	// shared access
		if (FAILED(hr)) {
#if defined(WIN32)
			if (!fHandleErrors) {
				::SetLastError (hr);
				return NULL;
			}

		SCODE sc = GetScode(hr);

			if (STG_E_SHAREVIOLATION == sc || STG_E_LOCKVIOLATION == sc) {
			// ZugriffsRechtsÜberschreitung
				if (!fRO && !TestFileRO (pName, fRO)) {
				// keine Datei oder existiert nicht
					db_error (S_INVDB, Z_OPEN);
					::SetLastError (HRESULT_FROM_ERRCODE(S_INVDB));
					return NULL;
				}
				if (fRO || AskToOpenCopy()) {
					hr = StgOpenStorage (WideString(pName), 
							NULL, STGM_TRANSACTED | STGM_READ, 
							0, 0, &pIStorage);
					if (SUCCEEDED(hr))
						pDB -> db_fOpenedAsCopy = true;
				
#if defined(_DEBUG_ISTORAGE)
					pIStorage = (IStorage *)new CStorageWrapper (pIStorage, pName);
#endif // _DEBUG_ISTORAGE

				// alles ok es geht als Kopie weiter
				//
				} else {
					::SetLastError (S_OK);
					return NULL;	// abgebrochen, Nutzer will keine Kopie erstellen
				}

			} else if (STG_E_ACCESSDENIED == sc) {
			// lediglich ReadOnly
				if (!TestFileRO (pName, fRO)) {
				// keine Datei oder existiert nicht
					db_error (S_INVDB, Z_OPEN);
					::SetLastError (HRESULT_FROM_ERRCODE(S_INVDB));
					return NULL;
				}

			// Kopie anlegen
				dwMode = STGM_TRANSACTED | STGM_READ;

				hr = StgOpenStorage (WideString(pName), 
						NULL, dwMode, 0, 0, &pIStorage);
				if (SUCCEEDED(hr))
					pDB -> db_fOpenedAsCopy = true;
			}
#endif // WIN32
			
			if (FAILED(hr)) {
			// sonstiger Fehler
				db_error (S_INVDB, Z_OPEN);
				::SetLastError (hr);
				return NULL;
			}
		}
	} else 
		pIStorage = pIStg;

// Version überprüfen
	if (NULL == pClsID)
		pClsID = &CLSID_DirisProject;

CLSID clsID;
struct dbpasswd *pPwd = NULL;

	hr = ReadClassStg (pIStorage, &clsID);
	if (FAILED(hr) || !IsEqualCLSID (clsID, *pClsID)) {
		RC = S_NOTAPROJECT;
		goto labelStgOpenError;
	}
	
#if defined(OLD_PWD_IN_STORAGE)
// PasswortEintrag lesen und überprüfen (wenn kein TempFile)
	pPwd = GetPWDName (pIStorage, pUser);
	if (pPwd == NULL) {
		RC = S_ACCESS;
		goto labelStgOpenError;			
	}

	if (*pPwd->dw_passwd &&
	     strcmp (crypt ((char *)pPWD, pPwd->dw_passwd), pPwd->dw_passwd)) 
	{
		RC = S_ACCESS;
		goto labelStgOpenError;
	}
#endif // OLD_PWD_IN_STORAGE

// interne Tabellen einrichten
	if ((RC = InitTables (pIStorage, pDB, pName, pPwd ? pPwd->dw_access : ~0x0i64, fRO)) != S_OKAY) 
	{
		fReportError = false;
		goto labelStgOpenError;
	}

// E/A-Tabellen, Pages etc. einrichten
	if ((RC = dio_init (pDB)) != S_OKAY) {
		fReportError = false;
		goto labelStgOpenError;
	}

// Handler fuer S_INVADDR installieren
	err_install (S_INVADDR, (INT_FUNC *)einvaddr, NULL);

	pDB -> db_name = (char *)pName;
	pDB -> db_pIStorage = pIStorage;	// ProjektDatei offen halten
	if (pIStg != NULL) 
		pDB -> db_pIStorage -> AddRef();	// Pointer festhalten
	pDB -> db_fhShared = 0;
	pDB -> db_fOpenedRO = fRO;		// RO eröffnet
	pDB -> db_fDirty = FALSE;
	pDB -> db_hProjectRelated = NULL;

#if defined(_USE_OPENREFCNT)
	pDB -> db_RefCnt = 1;
	pDB -> db_Mode = dwMode;
#endif // defined(_USE_OPENREFCNT)
	
// neue DB aktivieren
	activate (pDB);
	::SetLastError(S_OK);

return (HPROJECT)((pDB-db_table) + 1);

labelStgOpenError:
	memset (pDB, '\0', sizeof(DBASE));
	if (pName) delete (char *)pName;	// Speicher freigeben
	pIStorage -> Release();		// Datei schließen
	if (fReportError) db_error (RC, Z_OPEN);	
	::SetLastError (HRESULT_FROM_ERRCODE(RC));

	return NULL;
}

HPROJECT FUNCTYPE OpenStoragePbd (
		LPSTORAGE pIStg, DBASE *pDB, LPCSTR pcName, BOOL fRO)
{
	SYNC_DBACCESS_EX (g_pDbMutex);

// Eröffnen der ProjektDatei
short RC = S_OKAY;	// FehlerCode
BOOL fReportError = true;
HRESULT hr = NOERROR;

	if (pIStg == NULL) return NULL;

// Version überprüfen
CLSID clsID;
struct dbpasswd *pPwd = NULL;

	hr = ReadClassStg (pIStg, &clsID);
	if (FAILED(hr) || !IsEqualCLSID (clsID, CLSID_TRiASMetaDocument)) {
		RC = S_NOTAPROJECT;
		goto labelStgOpenError;
	}
	
// interne Tabellen einrichten
	if ((RC = InitTables (pIStg, pDB, pcName, ~0x0i64, fRO)) != S_OKAY) 
	{
		fReportError = false;
		goto labelStgOpenError;
	}

// E/A-Tabellen, Pages etc. einrichten
	if ((RC = dio_init (pDB)) != S_OKAY) {
		fReportError = false;
		goto labelStgOpenError;
	}

	pDB -> db_name = (char *)pcName;
	pDB -> db_pIStorage = pIStg;		// ProjektDatei offen halten
	pDB -> db_pIStorage -> AddRef();	// Pointer festhalten
	pDB -> db_fhShared = 0;
	pDB -> db_fOpenedRO = fRO;		// RO eröffnet
	pDB -> db_fDirty = FALSE;
	pDB -> db_hProjectRelated = NULL;
			
// neue DB aktivieren
	activate (pDB);
	::SetLastError(S_OK);

return (HPROJECT)((pDB-db_table) + 1);

labelStgOpenError:
	memset (pDB, '\0', sizeof(DBASE));
	if (fReportError) db_error (RC, Z_OPEN);	
	::SetLastError (HRESULT_FROM_ERRCODE(RC));

	return NULL;
}

#endif // MSWIND

