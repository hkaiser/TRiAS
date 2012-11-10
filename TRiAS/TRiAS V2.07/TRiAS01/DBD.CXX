// Memberfunktionen fuer DBDictionary -----------------------------------------
// File: DBD.CXX

#include "trias01p.hxx"

#include <commonvu.hxx>
#include <resstrg.h>

#include <process.h>
#include <io.h>
#include <direct.h>
#include <dos.h>
#include <time.h>
#include <limits.h>
		
#include <dbd.h>
#include <dbd.hxx>

#include <dirisole.h>

#include <strdup.hxx>
#include <strfcns.hxx>
#include <bakkey.hxx>
#include <targetfi.hxx>

#include <fnamestr.h>

#if !defined(WIN32)
#error "DBD.CXX: Diese Datei nur unter WIN32 verwenden!"
#endif

// Member der BasisKlasse -----------------------------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
CDBDict :: CDBDict (void)
	 : m_fIsValid (FALSE)
{
	m_pDBDHeader = NULL;
	m_pFileTable = NULL;
	m_pKeyTable = NULL;
	m_pRecordTable = NULL;
	m_pFieldTable = NULL;
	m_lDBDVersion = 0L;
	m_lPageSize = 0L;
	m_pDefExt = NULL;
	m_pPZTable = NULL;
}


BOOL CDBDict :: Init (LPBYTE lpDBDResource)
{
	m_pDBDHeader = ReadDBDHeader (lpDBDResource);
	if (m_pDBDHeader != NULL) {
		m_pFileTable = ReadFileTable (lpDBDResource);
		m_pKeyTable = ReadKeyTable (lpDBDResource);
		m_pRecordTable = ReadRecordTable (lpDBDResource);
		m_pFieldTable = ReadFieldTable (lpDBDResource);
		m_lDBDVersion = DBDVersion (lpDBDResource);
		m_lPageSize = PageSize (lpDBDResource);
		m_pDefExt = pDefaultExt (lpDBDResource);
		m_pPZTable = new PGZEROENTRY [iFiles()];
	}

	if (m_pDBDHeader == NULL || m_pDefExt == NULL ||
	    m_pFileTable == NULL || m_pKeyTable == NULL || 
	    m_pRecordTable == NULL || m_pFieldTable == NULL ||
	    m_pPZTable == NULL)
	{
		db_error (EC_NOMEMORY, RC_ctDBDict);
		return FALSE;
	}
	memset (m_pPZTable, '\0', iFiles()*sizeof(PGZEROENTRY));
	m_fIsValid = TRUE;
	
return TRUE;
}

CDBDict :: ~CDBDict (void)
{
	for (short i = 0; i < iFiles(); i++) {		// DateiNamen löschen
		DELETE (m_pFileTable[i].fepName);
	}
	DELETE (m_pFileTable);
	DELETE (m_pKeyTable);
	DELETE (m_pRecordTable);
	DELETE (m_pFieldTable);
	DELETE (m_pDefExt);
	DELETE (m_pPZTable);
	DELETE (m_pDBDHeader);
}


// Memberfunktionen -----------------------------------------------------------
DBDHEADER *CDBDict :: ReadDBDHeader (LPBYTE lpDBDResource)
{
DBDHEADER *pDBDHdr = new DBDHEADER;

	if (pDBDHdr == NULL) return NULL;

// umkopieren aus der Resource
	memcpy (pDBDHdr, lpDBDResource, sizeof(DBDHEADER));

return pDBDHdr;
}

// DateiTabelle aus Resource lesen --------------------------------------------
#if defined(__WATCOMC__)
#pragma warning 594 4;		// lookahead warnings
#pragma warning 597 4;
#pragma warning 604 4;
#endif

FILEENTRY *CDBDict :: ReadFileTable (LPBYTE lpDBDResource)
{ 
// Speicher anfordern
FILEENTRY *pFT = new FILEENTRY [iFiles()];

	if (pFT == NULL) return NULL;	// Kein Speicherplatz

// FileTabelle aufbauen
LPBYTE lpOffset = lpDBDResource + sizeof(DBDHEADER);

	memcpy (pFT, lpOffset, sizeof(FILEENTRY) * iFiles());

char (*lpFileNames)[FILENMLEN] = (char (*)[FILENMLEN])
					(lpOffset + 
					 sizeof(FILEENTRY)*iFiles());

	memcpy (lpFileNames, 
		lpOffset + sizeof(FILEENTRY)*iFiles(),
		FILENMLEN*iFiles());

	for (short i = 0; i < iFiles(); i++) {
	// DateiNamen generieren und einfügen
	char *newName =  new char [FILENMLEN+1];

		if (newName == NULL) return NULL;

		memset (newName, '\0', FILENMLEN+1);
		strncpy (newName, lpFileNames[i], FILENMLEN);
		newName[FILENMLEN] = '\0';
		pFT[i].fepName = newName;
	}

return pFT;
}

// Schlüsseltabelle aus Resource lesen ----------------------------------------
KEYENTRY *CDBDict :: ReadKeyTable (LPBYTE lpDBDResource)
{
// Speicher anfordern
KEYENTRY *pKT = new KEYENTRY [iKeys()];

	if (pKT == NULL) return NULL;	// Kein Speicherplatz

// KeyTabelle aufbauen
LPBYTE lpOffset = lpDBDResource + sizeof(DBDHEADER) +
		 (sizeof(FILEENTRY)+FILENMLEN) * iFiles();

	memset (pKT, '\0', sizeof(KEYENTRY)*iKeys());
	for (short i = 0; i < iKeys(); i++) 
		memcpy (&pKT[i], lpOffset + (sizeof(DBDKEYENTRY) * i), 
				 sizeof(DBDKEYENTRY));

	for (i = 0; i < iKeys(); i++) {
		memcpy (pKT[i].kepName, lpOffset + 
					(sizeof(DBDKEYENTRY) * iKeys()) +
					(NAMELEN * i),
					NAMELEN);
		pKT[i].kepName[NAMELEN-1] = '\0';
	}

return pKT;
}

// RecordTabelle aus Resource lesen -------------------------------------------
RECORDENTRY *CDBDict :: ReadRecordTable (LPBYTE lpDBDResource)
{
// Speicher anfordern
RECORDENTRY *pRT = new RECORDENTRY [iRecords()];

	if (pRT == NULL) return NULL;	// Kein Speicherplatz

// RecordTabelle aufbauen
LPBYTE lpOffset = lpDBDResource + sizeof(DBDHEADER) +
		 (sizeof(FILEENTRY)+FILENMLEN) * iFiles() +
		 (sizeof(DBDKEYENTRY)+NAMELEN) * iKeys();

	memset (pRT, '\0', sizeof(RECORDENTRY)*iRecords());
	for (short i = 0; i < iRecords(); i++) 
		memcpy (&pRT[i], lpOffset + (sizeof(DBDRECORDENTRY) * i), 
				 sizeof(DBDRECORDENTRY));

	for (i = 0; i < iRecords(); i++) {
		memcpy (pRT[i].repName, lpOffset + 
					(sizeof(DBDRECORDENTRY) * iRecords()) +
					(NAMELEN * i),
					NAMELEN);
		pRT[i].repName[NAMELEN-1] = '\0';
	}

return pRT;
}

// Einlesen der FeldTabelle aus der Resource ----------------------------------
FIELDENTRY *CDBDict :: ReadFieldTable (LPBYTE lpDBDResource)
{
// Speicher anfordern
FIELDENTRY *pFT = new FIELDENTRY [iFields()];

	if (pFT == NULL) return NULL;	// Kein Speicherplatz

// FeldTabelle aufbauen
	memcpy (pFT, lpDBDResource + sizeof(DBDHEADER) +
		     (sizeof(FILEENTRY)+FILENMLEN) * iFiles() + 
		     sizeof(KEYENTRY) * iKeys() +
		     sizeof(RECORDENTRY) * iRecords(),
		     sizeof(FIELDENTRY) * iFields());

return pFT;
}

// Lesen der StandardErweiterung aus der Resource -----------------------------
char *CDBDict :: pDefaultExt (LPBYTE lpDBDResource)
{
char *lpDefExt = new char [_MAX_EXT];

	if (lpDefExt == NULL) return NULL;	// Kein Speicherplatz

	strcpy (lpDefExt, (char *)(lpDBDResource + sizeof(DBDHEADER) +
				   (sizeof(FILEENTRY)+FILENMLEN) * iFiles() + 
				    sizeof(KEYENTRY) * iKeys() +
				    sizeof(RECORDENTRY) * iRecords() +
				    sizeof(FIELDENTRY) * iFields() +
				    2*sizeof(long)));

return lpDefExt;
}


// Einlesen der PageGröße -----------------------------------------------------
long CDBDict :: PageSize (LPBYTE lpDBDResource)
{
long *lpPageSize = (long *)(lpDBDResource + sizeof(DBDHEADER) +
				   (sizeof(FILEENTRY)+FILENMLEN) * iFiles() + 
				    sizeof(KEYENTRY) * iKeys() +
				    sizeof(RECORDENTRY) * iRecords() +
				    sizeof(FIELDENTRY) * iFields() +
				    sizeof(long));

return *lpPageSize;
}


// Lesen der Dateiversion aus der Resource --------------------------------
long CDBDict :: DBDVersion (LPBYTE lpDBDResource)
{
long *lpVersion = (long *)(lpDBDResource + sizeof(DBDHEADER) +
					  (sizeof(FILEENTRY)+FILENMLEN) * iFiles() + 
					  sizeof(KEYENTRY) * iKeys() +
					  sizeof(RECORDENTRY) * iRecords() +
					  sizeof(FIELDENTRY) * iFields());

return *lpVersion;
}

/////////////////////////////////////////////////////////////////////////////
// Modifizieren der Dateiversion in der Resource
long CDBDict::SetDBDVersion (LPBYTE lpDBDResource, long lNewVersion)
{
long *lpVersion = (long *)(lpDBDResource + sizeof(DBDHEADER) +
					  (sizeof(FILEENTRY)+FILENMLEN) * iFiles() + 
					  sizeof(KEYENTRY) * iKeys() +
					  sizeof(RECORDENTRY) * iRecords() +
					  sizeof(FIELDENTRY) * iFields());

long lOldVersion = *lpVersion;

	*lpVersion = lNewVersion;
	return lOldVersion;
}

// Zugriffsfunktionen auf interessierende Informationen -----------------------
char *CDBDict :: pKeyType (short iIndex)
{
unsigned int idKey = 0;

	if (iIndex < 0 || iIndex >= iKeys()) return NULL;

	switch (m_pKeyTable[iIndex].keiType) {
	case KEY:		idKey = IDS_KEYTYPEKEY; 	break;
	case KEY_ONLY:		idKey = IDS_KEYTYPEKEYONLY; 	break;
	case UNIQUE:		idKey = IDS_KEYTYPEUNIQUE; 	break;
	case UNIQUE_ONLY:	idKey = IDS_KEYTYPEUNIQUEONLY; 	break;
	default:		idKey = IDS_UNKNOWN; break;
	}

return StrDup (ResString (ResID (idKey), 30), RC_pKeyType);
}


// SchlüsselTyp besorgen ------------------------------------------------------
char *CDBDict :: pKeyFieldType (short iKeyIndex)
{
unsigned int idKey = 0;

	if (iKeyIndex < 0 || iKeyIndex >= iKeys()) return NULL;

	switch (m_pKeyTable[iKeyIndex].keiField) {
	case CHARACTER:		idKey = IDS_FIELDTYPECHARACTER; break;
	case CHAR_ARRAY:	idKey = IDS_FIELDTYPECHARARRAY; break;
	case SHORTINT:		idKey = IDS_FIELDTYPESHORT; break;
	case REGINT:		idKey = IDS_FIELDTYPEINTEGER; break;
	case STRUCT:		idKey = IDS_FIELDTYPESTRUCTURE; break;
	case UNION:		idKey = IDS_FIELDTYPEUNION; break;
	case LONGINT:		idKey = IDS_FIELDTYPELONG; break;
	case FLOAT:		idKey = IDS_FIELDTYPEFLOAT; break;
	case DOUBLE:		idKey = IDS_FIELDTYPEDOUBLE; break;
	case DBADDR:		idKey = IDS_FIELDTYPEDBADDR; break;
	default:		idKey = IDS_UNKNOWN; break;
	}

return StrDup (ResString (ResID (idKey), 30), RC_pKeyFieldType);
}


// DateiTyp besorgen ----------------------------------------------------------
char *CDBDict :: pFileType (short iFile)
{
	if (iFile < 0 || iFile >= iFiles()) return NULL;

unsigned int idKey = 0;

	switch (m_pFileTable[iFile].feiType) {
	case DATAFILE:		idKey = IDS_FILETYPEDATA; break;
	case KEYFILE:		idKey = IDS_FILETYPEKEY; break;
	case QTREEFILE:		idKey = IDS_FILETYPEQTREE; break;
	case HTREEFILE:		idKey = IDS_FILETYPEHTREE; break;
	case BACKUPFILE:	idKey = IDS_FILETYPEBACKUP; break;
	case TREEKEYFILE:	idKey = IDS_FILETYPETREEKEY; break;
	default:		idKey = IDS_UNKNOWN; break;
	}

return StrDup (ResString (ResID (idKey), 30), RC_pFileType);
}


short CDBDict :: iFileType (short iFile)
{
	if (iFile < 0 || iFile >= iFiles()) return -1;

return m_pFileTable[iFile].feiType;
}


// DateiTyp der KeyDatei besorgen ---------------------------------------------
char *CDBDict :: pKeyFileType (short iKeyIndex)
{
	if (iKeyIndex < 0 || iKeyIndex >= iKeys())
		return NULL;

short iKeyFile = m_pKeyTable[iKeyIndex].keiTreefile;

	if (iKeyFile == -1) iKeyFile = m_pKeyTable[iKeyIndex].keiKeyfile;

return pFileType (iKeyFile);
}


// DateiNamen besorgen --------------------------------------------------------
char *CDBDict :: pFileName (short iIndex)
{
	if (iIndex < 0 || iIndex >= iFiles()) return NULL;

return StrDup (m_pFileTable[iIndex].fepName, RC_pFileName);
}


// KeyDateiNamen besorgen -----------------------------------------------------
char *CDBDict :: pKeyFileName (short iKeyIndex)
{
	if (iKeyIndex < 0 || iKeyIndex >= iKeys()) return NULL;

short iKeyFile = m_pKeyTable[iKeyIndex].keiTreefile;

	if (iKeyFile == -1)
		iKeyFile = m_pKeyTable[iKeyIndex].keiKeyfile;

	if (iKeyFile < 0 || iKeyFile >= iFiles())
		return NULL;

return StrDup (m_pFileTable[iKeyFile].fepName, RC_pKeyFileName);
}


// Liefert, ob TreeKey vorliegt -----------------------------------------------
char *CDBDict :: pTreeKeyFileName (short iKeyIndex)
{
	if (iKeyIndex < 0 || iKeyIndex >= iKeys()) return NULL;

short iKeyFile = m_pKeyTable[iKeyIndex].keiTreefile;

	if (iKeyFile != -1)
		iKeyFile = m_pKeyTable[iKeyIndex].keiKeyfile;

	if (iKeyFile < 0 || iKeyFile >= iFiles())
		return NULL;

return StrDup (m_pFileTable[iKeyFile].fepName, RC_pTreeKeyFileName);
}

// TargetDateiNamen besorgen --------------------------------------------------
char *CDBDict :: pTargetFileName (short iKeyIndex)
{
	if (iKeyIndex < 0 || iKeyIndex >= iKeys()) return NULL;

short iFile = m_pKeyTable[iKeyIndex].keiFile;

	if (iFile < 0 || iFile >= iFiles())
		return NULL;

return StrDup (m_pFileTable[iFile].fepName, RC_pTargetFileName);
}

// Testen, ob Schlüssel ein normaler BTreeKey ist -----------------------------
short CDBDict :: isBTreeKey (short iKeyIndex)
{
	if (iKeyIndex < 0 || iKeyIndex >= iKeys())
		return 0;	// Fehler

short iFile = m_pKeyTable[iKeyIndex].keiKeyfile;

	if (iFile < 0 || iFile >= iFiles())
		return 0;

return (m_pFileTable[iFile].feiType == KEYFILE) ? 1 : -1;
}


long CDBDict :: FileNo (long lRecNo)
{
	if (lRecNo >= 0 && lRecNo < iRecords())
		return m_pRecordTable[lRecNo].reiFile;

return -1;
}

// liefert RecordGröße --------------------------------------------------------
short CDBDict :: RecSize (long lRecNo)
{
	if (lRecNo >= 0 && lRecNo < iRecords())
		return m_pRecordTable[lRecNo].reiLen;

return 0;
}

// Neu generieren eines PGZERO Eintrages in der BackUpDatei -------------------
ErrCode CDBDict :: ReCreateBackupFileEntry (short iFile, short iChain, short iNext)
{
#if defined(BACKUP)
	if (m_pPZTable && iFile >= 0 && iFile < iFiles()) {
		m_pPZTable[iFile].pzlDelChain = long(iChain);
		m_pPZTable[iFile].pzlNext = long(iNext); 
		m_pPZTable[iFile].pzlBTime = 0L;
	}
#endif

return EC_OKAY;
}


// Liefert RecordNummer zu einem Schlüssel ------------------------------------
short CDBDict :: RecordNum (short iKeyIndex)
{
// alle Records absuchen
	for (short i = 0; i < iRecords(); i++) {
	short ilocKey = m_pRecordTable[i].reiKeyfile;

		while (ilocKey != -1) {
		// hurra, gefunden
			if (ilocKey == iKeyIndex) return i;

		// nächster Eintrag
			ilocKey = m_pKeyTable[ilocKey].keiChain;
		}
	}

return -1;	// nichts gefunden
}


// ----------------------------------------------------------------------------
// Alter ProjektTyp (DOSDateien) ----------------------------------------------
CDBDictDOSFiles * CDBDictDOSFiles :: CreateInstance (LPBYTE lpDBDResource)
{
CDBDictDOSFiles *pDict = new CDBDictDOSFiles ();

	if (pDict == NULL || !pDict -> Init (lpDBDResource)) {
		DELETE (pDict);
		return NULL;
	}
	
return pDict;
}


// Neuanlegen einer Datenbasis ------------------------------------------------
BOOL CreateFullGeoDBPath (const char *pFullPath);

ErrCode CDBDictDOSFiles :: CreateDB (const char *pFullPath, 
				     const char *pUser, const char *pPWD)
{
ErrCode RC = EC_OKAY;

// Sicherstellen, daß Verzeichnis existiert
	if (!CreateFullGeoDBPath (pFullPath))
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDictionary);

// Dateien der GeoDB anlegen
	DBASSERT (CreateDictionary (pFullPath));
	DBASSERT (CreatePassWordFile (pFullPath, pUser, pPWD));

	for (short iFile = 0; iFile < iFiles(); iFile++) {
		switch (iFileType (iFile)) {
		case DATAFILE:		// File enthält Daten 
			DBASSERT (CreateDataFile (iFile, pFileName (iFile), pFullPath));
			break;
			
		case KEYFILE:		// File enthält Schluesselinfo's 
			DBASSERT (CreateKeyFile (iFile, pFileName (iFile), pFullPath));
			break;
			
		case HTREEFILE:		// File enthält Geometriehexbaum 
		case QTREEFILE:		// File enthält Geometrie-QuadTree 
                case CTREEFILE:
			DBASSERT (CreateGeoTreeFile (iFile, pFileName (iFile), pFullPath));
			break;
			
		case TREEKEYFILE:	// File enthält HilfsBaum
			DBASSERT (CreateTreeKeyFile (iFile, pFileName (iFile), pFullPath));
			break;
			
		case BACKUPFILE:
			DBASSERT (CreateBackupFile (iFile, pFileName (iFile), pFullPath));
			break;
			
		default:
			continue;	// Unknown FileType
		}	
	}

return EC_OKAY;
}


// Anlegen der Steuerdatei ----------------------------------------------------
ErrCode CDBDictDOSFiles :: CreateDictionary (const char *pFullPath)
{
char *pDictName = new char[10];

	if (pDictName == NULL)
		return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDictionary);
		
	wsprintf (pDictName, "*.%s", m_pDefExt);
	
char *pFile = ExpandWithName (pDictName, pFullPath, TRUE);
OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFile, &of, OF_CREATE | OF_READWRITE)) < 0) {
		DELETE (pFile);
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDictionary);
	}
	DELETE (pFile);

// Copyright schreiben
	_lwrite (fh, pCopyRight(), COPYRIGHTLEN);

// Tabellen schreiben
short iOutVal = iFiles();

	_lwrite (fh, (LPCSTR)&iOutVal, sizeof(short));
	iOutVal = iKeys();
        _lwrite (fh, (LPCSTR)&iOutVal, sizeof(short));
	iOutVal = iRecords();
        _lwrite (fh, (LPCSTR)&iOutVal, sizeof(short));
#if defined(BACKUP)
	iOutVal = iBackup();
        _lwrite (fh , (LPCSTR)&iOutVal, sizeof(short));
#endif

	for (short iIndex = 0; iIndex < iFiles(); iIndex++) {
	FILEENTRY fe = m_pFileTable[iIndex];	// temporäre Kopie
	
		fe.fepName = NULL;		// Dateinamen ausnullen
		if (fe.feiType == TREEKEYFILE)
			fe.feiType = KEYFILE;
		_lwrite (fh, (LPCSTR)&fe, sizeof(FILEENTRY));
	}
	for (iIndex = 0; iIndex < iFiles(); iIndex++) {
	char *pName = StrDup (m_pFileTable[iIndex].fepName, RC_CreateDictionary);
	char *pFName = ExpandWithName (pName, pFullPath);
	
		if (pFName == NULL) 
			return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDictionary);

		_lwrite (fh, pFName, FILENMLEN);
		delete pFName;
	}
	
	for (iIndex = 0; iIndex < iKeys(); iIndex++) 
	        _lwrite (fh, (LPCSTR)&m_pKeyTable[iIndex], sizeof (DBDKEYENTRY));
        for (iIndex = 0; iIndex < iRecords(); iIndex++)
                _lwrite (fh, (LPCSTR)&m_pRecordTable[iIndex], sizeof (RISRECORDENTRY));

long lOutVal = DBDVersion();

	_lwrite (fh, (LPCSTR)&lOutVal, sizeof(long));	// VersionsNummer schreiben
	lOutVal = PageSize();
	_lwrite (fh, (LPCSTR)&lOutVal, sizeof(long));	// PageGröße wegschreiben

	_lclose (fh);		// Datei schließem

return EC_OKAY;
}


// Anlegen der PassWordDatei --------------------------------------------------
ErrCode CDBDictDOSFiles :: CreatePassWordFile (const char *pFullPath, 
					       const char *pUser, 
					       const char *pPWD)
{
// Passwortdatei generieren
char *pPWDName = new char [10];

	if (pPWDName == NULL)
		return (ErrCode)db_error (EC_NOMEMORY, RC_CreatePWDFile);
		
	strcpy (pPWDName, "*.pwd");
	
char *pFile = ExpandWithName (pPWDName, pFullPath, TRUE);
OFSTRUCT of;
int fh;

	if ((fh = OpenFile (pFile, &of, OF_READ)) >= 0) {
	// PassWordDatei existiert bereits
		_lclose (fh);
		DELETE (pFile);
		return EC_OKAY;
	}
	
	if ((fh = OpenFile (pFile, &of, OF_CREATE | OF_READWRITE)) < 0) {
		DELETE (pFile);
		return (ErrCode)db_error (EC_NOFILE, RC_CreatePWDFile);
	}

// ZugriffsSchlüssel generieren
unsigned long lAccess = 0L;

        for (short i = 0; i < iFiles(); ++i)
                lAccess = lAccess | (unsigned long)(1L << i);

// Dateieinträge erzeugen
char *pOutBuff = new char [_MAX_PATH];
char *pDBName = new char [_MAX_PATH];

	if (pOutBuff == NULL || pDBName == NULL) {
		DELETE (pFile);
		return (ErrCode)db_error (EC_NOMEMORY, RC_CreatePWDFile);
	}
			
	_splitpath (pFullPath, NULL, NULL, pDBName, NULL);
	strlwr (pDBName);
	wsprintf (pOutBuff, ResString (IDS_PASSWD1, 40),
		  pDBName, lAccess, lAccess, pDBName);
	_lwrite (fh, pOutBuff, strlen (pOutBuff));
	wsprintf (pOutBuff, ResString (IDS_PASSWD2, 40),
		  pDBName, lAccess);
	_lwrite (fh, pOutBuff, strlen (pOutBuff));
                
	if (pUser != NULL) {
		if (pPWD != NULL) {
		// Neues Passwort verschlüsseln
		char saltc[2];
		time_t lSalt;
		
        		time (&lSalt);
        		lSalt += getpid();
	        	saltc[0] = char (lSalt & 077);
	        	saltc[1] = char ((lSalt >> 6) & 077);
        		for (i = 0; i < 2; i++){
			short c = saltc[i] + '.';
			
				if(c > '9') c += 7;
				if(c > 'Z') c += 6;
				saltc[i] = (char)c;
        		}
        		pPWD = crypt ((char *)pPWD, saltc);
        	}
		wsprintf (pOutBuff, ResString (IDS_PASSWD3, 40),
			  pUser, pPWD ? pPWD : "", lAccess, lAccess, pUser);
		_lwrite (fh, pOutBuff, strlen (pOutBuff));
	}
        _lclose (fh);
	chmod (pFile, 0400);	// ReadOnly machen
	
	DELETE (pFile);
	DELETE (pOutBuff);
	DELETE (pDBName);

return EC_OKAY;
}


// Neuanlegen einer Datendatei der DatenBasis ---------------------------------
ErrCode CDBDictDOSFiles :: CreateDataFile (short iIndex, const char *pFullPath)
{
	return CreateDataFile (iIndex, pFileName (iIndex), pFullPath);
}


ErrCode CDBDictDOSFiles :: CreateDataFile (short iIndex, char *pDataName, 
					   const char *pFullPath)
{
// vollständigen Namen erzeugen
char *pFile = ExpandWithName (pDataName, pFullPath, TRUE);
ErrCode RC;

	if (pFile == NULL) return EC_NOMEMORY;

// Datei anlegen
	DBASSERT (::CreateDataFile (pFile, pCopyRight(), 0, (short)PageSize()));
	DELETE (pFile);

#if defined(BACKUP)
// Update der BackupDatei
	DBASSERT (ReCreateBackupFileEntry (iIndex, 0, 1));
#endif

return EC_OKAY;
}


// Neuanlegen einer Schlüsseldatei der DatenBasis -----------------------------
ErrCode CDBDictDOSFiles :: CreateKeyFile (short iKeyIndex, const char *pFullPath)
{
short iFile = m_pKeyTable[iKeyIndex].keiKeyfile;

	return CreateKeyFile (iFile, pKeyFileName (iKeyIndex), pFullPath);
}


ErrCode CDBDictDOSFiles :: CreateKeyFile (short iFile, char *pFileName, 
					  const char *pFullPath)
{
// vollständigen Namen erzeugen
char *pKeyFile = ExpandWithName (pFileName, pFullPath, TRUE);
ErrCode RC;

	if (pKeyFile == NULL) return EC_NOMEMORY;

// Datei anlegen
	DBASSERT (::CreateKeyFile (pKeyFile, pCopyRight(), 0, (short)PageSize()));
	DELETE (pKeyFile);

#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iFile, -1, 2));
#endif

return EC_OKAY;
}


ErrCode CDBDictDOSFiles :: CreateTreeKeyFile (short iKeyIndex, const char *pFullPath)
{
short iFile = m_pKeyTable[iKeyIndex].keiTreefile;

	return CreateTreeKeyFile (iFile, pTreeKeyFileName (iKeyIndex), pFullPath);
}


ErrCode CDBDictDOSFiles :: CreateTreeKeyFile (short iFile, char *pTreeKeyFile, 
					      const char *pFullPath)
{
// vollständigen Namen erzeugen
char *pTreeFile = ExpandWithName (pTreeKeyFile, pFullPath, TRUE);
ErrCode RC;

	if (pTreeFile == NULL) return EC_NOMEMORY;

// Datei anlegen
	DBASSERT (::CreateTreeKeyFile (pTreeFile, pCopyRight(), 0, (short)PageSize()));
	DELETE (pTreeFile);

#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iFile, -1, 1));
#endif

return EC_OKAY;
}


ErrCode CDBDictDOSFiles :: CreateGeoTreeFile (short iKeyIndex, const char *pFullPath)
{
short iFile = m_pKeyTable[iKeyIndex].keiKeyfile;

	return CreateGeoTreeFile (iFile, pKeyFileName (iKeyIndex), pFullPath);
}


ErrCode CDBDictDOSFiles :: CreateGeoTreeFile (short iFile, char *pGeoFileName, 
					      const char *pFullPath)
{
// vollständigen Namen erzeugen
char *pGeoKeyFile = ExpandWithName (pGeoFileName, pFullPath, TRUE);
ErrCode RC;

	if (pGeoKeyFile == NULL) return EC_NOMEMORY;

// Datei anlegen
	DBASSERT (::CreateGeoTreeFile (pGeoKeyFile, pCopyRight(), 0, (short)PageSize()));
	DELETE (pGeoKeyFile);

#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iFile, 0, 2));
#endif

return EC_OKAY;
}


// BackupFile generieren ------------------------------------------------------
ErrCode CDBDictDOSFiles :: CreateBackupFile (short iFile, char *pFile, 
					     const char *pFullPath)
{
#if defined(BACKUP)
char *pFName = ExpandWithName (pFile, pFullPath, TRUE);
ErrCode RC;

	DBASSERT (ReCreateBackupFileEntry (iFile, -1, -1));
	DBASSERT (::CreateBackupFile (pFName, pCopyRight(), 0, (struct pg_zero *)m_pPZTable, iFiles(), (short)PageSize()));
	DELETE (pFName);
#endif

return EC_OKAY;
}


short EXPORT01 pTestPOL (void *pData) 
{
pol *pPOLSatz = (pol *)pData;

	return (pPOLSatz -> zpvgo != 0);
}

// ReIndizieren einer Schlüsseldatei -----------------------------------------
ErrCode CDBDictDOSFiles :: ReIndex (HPROJECT hPr, short iKeyIndex, const char *pFullPath)
{
	if (iKeyIndex < 0 || iKeyIndex >= iKeys()) return EC_OKAY;

// 1. Umbennen der alten Schlüsseldatei (Backup) und KeyDateien neu erzeugen
CBackupKeyFile BKF(hPr);

	if (!BKF.Init(*this, pFullPath, iKeyIndex))	// WrapperKlasse
		return EC_OKAY;

// 2. Für alle Datensätze der Targetdatei(en) Schlüssel neu schreiben
CTargetFileIterator TFI (*this);

	if (!TFI.Init (iKeyIndex)) return EC_OKAY;

short iFile = TFI.GetFirstTargetFile ();

	iKeyIndex  = TFI.iKeyIndex();
	while (iFile >= 0) {
	ErrCode RC;
	short iRecord = RecordNum (iKeyIndex);

		if (iRecord == -1) return EC_OKAY;

		if (iKeyIndex == KPKRD) {
			DBASSERT (ReIndexFile (hPr, iFile, iRecord, iKeyIndex, pTestPOL));
		} else {
			DBASSERT (ReIndexFile (hPr, iFile, iRecord, iKeyIndex, NULL));
		}
		iFile = TFI.GetNextTargetFile ();
		iKeyIndex = TFI.iKeyIndex();
	}

// 3. OK-Status setzen, damit neue Key's erhalten bleiben
	BKF.SetOK();

return EC_OKAY;
}


// Neuer ProjektTyp (Compoundfile) --------------------------------------------
CDBDictCompoundFile * CDBDictCompoundFile :: CreateInstance (LPBYTE lpDBDResource)
{
CDBDictCompoundFile *pDict = new CDBDictCompoundFile;

	if (pDict == NULL || !pDict -> Init (lpDBDResource)) {
		DELETE (pDict);
		return NULL;
	}
	
return pDict;
}


// Neuanlegen einer Datenbasis ------------------------------------------------
ErrCode CDBDictCompoundFile :: CreateDB (const char *pFullPath, 
					 const char *pUser, const char *pPWD)
{
	return CreateDBEx (pFullPath, pUser, pPWD);
}

// Diese Funktion erzeugt ein neues CompounfFile, wenn kein pIStorage gegeben
// ist (*ppIStorage == NULL). Wenn ein pIStorage gegeben ist, (*ppIStorage != NULL),
// dann wird in diesem Storage eine neue DB angelegt. In jedem Fall wird 
// das Storage zurückgeliefert, wenn ppIStorage != NULL ist.
ErrCode CDBDictCompoundFile :: CreateDBEx (
		LPCSTR pFullPath, LPCSTR pUser, LPCSTR pPWD,
		LPSTORAGE *ppIStorage, const CLSID *pClsID, LPCSTR pCF)
{
ErrCode RC = EC_OKAY;
HRESULT hr = NOERROR;
LPSTORAGE pIStorage = NULL;
DWORD dwMode = STGM_CREATE | STGM_READWRITE;

// entscheiden, ob neu anlegen oder als SubStorage verwenden
	if (NULL != ppIStorage && NULL != *ppIStorage) {
		(*ppIStorage) -> AddRef();
		pIStorage = *ppIStorage;
	} else {
	// nur wenn nicht in bestehendem CompFile erzeugt werden soll
		if (!CreateFullGeoDBPath (pFullPath))	// Pfad sicherstellen
			return (ErrCode)db_error (EC_NOFILE, RC_CreateDictionary);

	// ProjektDatei anlegen, wenn Name nicht gegeben ist, dann temporäre Datei erzeugen
		hr = StgCreateDocfile (pFullPath ? WideString(pFullPath) : NULL, 
				       dwMode | STGM_TRANSACTED | STGM_SHARE_DENY_WRITE, 
					   0, &pIStorage);
		if (FAILED(hr))
			return (ErrCode)db_error (EC_NOFILE, RC_CreateDBEx);
	}

// Typ der Datenbank wegschreiben
	if (NULL == pClsID)
		WriteClassStg (pIStorage, CLSID_DirisProject);
	else
		WriteClassStg (pIStorage, *pClsID);

	if (NULL == pCF) {
	ResString resClass (IDS_TRIASFULLNAME130, 30);
	CLIPFORMAT cf = RegisterClipboardFormat (resClass);

		WriteFmtUserTypeStg (pIStorage, cf, WideString(resClass));
	} else {
	CLIPFORMAT cf = RegisterClipboardFormat (pCF);

		WriteFmtUserTypeStg (pIStorage, cf, WideString(pCF));
	}

// eigentliche SubStorages erzeugen
	if ((RC = CreateDictionary (pIStorage, dwMode)) != EC_OKAY) {
		pIStorage -> Release();
		return RC;
	}

#if defined(OLD_PWD_IN_STORAGE)
	if ((RC = CreatePassWordFile (pIStorage, dwMode, pFullPath, pUser, pPWD)) != EC_OKAY) 
	{
		pIStorage -> Release();
		return RC;
	}
#endif // OLD_PWD_IN_STORAGE

	for (short iFile = 0; iFile < iFiles(); iFile++) {
		switch (iFileType (iFile)) {
		case DATAFILE:		// File enthält Daten 
			RC = CreateDataFile (pIStorage, dwMode, iFile);
			break;
			
		case KEYFILE:		// File enthält Schluesselinfo's 
			RC = CreateKeyFile (pIStorage, dwMode, iFile);
			break;
			
		case HTREEFILE:		// File enthält Geometriehexbaum 
		case QTREEFILE:		// File enthält Geometrie-QuadTree 
                case CTREEFILE:
			RC = CreateGeoTreeFile (pIStorage, dwMode, iFile);
			break;
			
		case TREEKEYFILE:	// File enthält HilfsBaum
			RC = CreateTreeKeyFile (pIStorage, dwMode, iFile);
			break;
			
		case BACKUPFILE:
			RC = CreateBackupFile (pIStorage, dwMode, iFile);
			break;
			
		default:
			continue;	// Unknown FileType
		}	
		if (RC != EC_OKAY) {
			pIStorage -> Release();
			return RC;
		}
	}

// alles OK	
	if (NULL != ppIStorage && NULL == *ppIStorage) {	// evtl. Pointer merken
		pIStorage -> AddRef();
		*ppIStorage = pIStorage;
	} else
		pIStorage -> Commit (STGC_DEFAULT);	// Datei wegschreiben

	pIStorage -> Release();		// Datei schließen, bzw. freigeben

	return EC_OKAY;
}

// Anlegen der Steuerdatei ----------------------------------------------------
ErrCode CDBDictCompoundFile :: CreateDictionary (LPSTORAGE pIStorage, DWORD dwMode)
{
ResString resDict (IDS_DBDICTIONARY, 30);
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(resDict.Addr()), 
					dwMode | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
					0, 0, &pIStream);

	if (FAILED(hr)) return (ErrCode)db_error (EC_NOFILE, RC_CreateDictionary);

// Copyright schreiben
	pIStream -> Write (pCopyRight(), COPYRIGHTLEN, NULL);

// Tabellen schreiben
short iOutVal = iFiles();

	pIStream -> Write (&iOutVal, sizeof(short), NULL);
	iOutVal = iKeys();
        pIStream -> Write (&iOutVal, sizeof(short), NULL);
	iOutVal = iRecords();
        pIStream -> Write (&iOutVal, sizeof(short), NULL);
#if defined(BACKUP)
	iOutVal = iBackup();
        pIStream -> Write (&iOutVal, sizeof(short), NULL);
#endif

	for (short iIndex = 0; iIndex < iFiles(); iIndex++) {
	FILEENTRY fe = m_pFileTable[iIndex];	// temporäre Kopie
	
		fe.fepName = NULL;		// Dateinamen ausnullen
		if (fe.feiType == TREEKEYFILE)
			fe.feiType = KEYFILE;
		pIStream -> Write (&fe, sizeof(FILEENTRY), NULL);
	}
	for (iIndex = 0; iIndex < iFiles(); iIndex++) {
	char *pT = m_pFileTable[iIndex].fepName;
	
		if (islower (*pT)) *pT = char(toupper (*pT));
		pIStream -> Write (pT, FILENMLEN, NULL);
	}
	for (iIndex = 0; iIndex < iKeys(); iIndex++)
	        pIStream -> Write (&m_pKeyTable[iIndex], sizeof (DBDKEYENTRY), NULL);
	
        for (iIndex = 0; iIndex < iRecords(); iIndex++) 
                pIStream -> Write (&m_pRecordTable[iIndex], sizeof (RISRECORDENTRY), NULL);
        

long lOutVal = DBDVersion();

// VersionsNummer schreiben
	pIStream -> Write ((LPVOID)&lOutVal, sizeof(long), NULL);
	lOutVal = PageSize();
// PageGröße wegschreiben
	pIStream -> Write ((LPVOID)&lOutVal, sizeof(long), NULL);

	pIStream -> Release();

return EC_OKAY;
}

#if defined(OLD_PWD_IN_STORAGE)
// Anlegen der PassWordDatei --------------------------------------------------
ErrCode CDBDictCompoundFile :: CreatePassWordFile (
			LPSTORAGE pIStorage, DWORD dwMode,
			const char *pFullPath,
			const char *pUser, const char *pPWD)
{
ResString resDict (IDS_DBPWDSTREAM, 30);
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(resDict.Addr()), 
				dwMode | STGM_DIRECT | STGM_FAILIFTHERE | STGM_SHARE_EXCLUSIVE, 
				0, 0, &pIStream);

	if (FAILED(hr)) {
		if (SCODE(hr) == STG_E_FILEALREADYEXISTS)
			return EC_OKAY;
		return (ErrCode)db_error (EC_NOFILE, RC_CreatePWDFile);
	}

// ZugriffsSchlüssel generieren
unsigned long lAccess = 0L;

        for (short i = 0; i < iFiles(); ++i)
                lAccess = lAccess | (unsigned long)(1L << i);

// Dateieinträge erzeugen
char *pOutBuff = new char [_MAX_PATH];
char *pDBName = new char [_MAX_PATH];

	if (pOutBuff == NULL || pDBName == NULL) {
		pIStream -> Release();
		return (ErrCode)db_error (EC_NOMEMORY, RC_CreatePWDFile);
	}
			
	if (pFullPath) 
		_splitpath (pFullPath, NULL, NULL, pDBName, NULL);
	else 
		strcpy (pDBName, TEXT("temp"));
	strlwr (pDBName);
	wsprintf (pOutBuff, ResString (IDS_PASSWD1, 40),
		  pDBName, lAccess, lAccess, pDBName);
	pIStream -> Write (pOutBuff, strlen (pOutBuff), NULL);
	wsprintf (pOutBuff, ResString (IDS_PASSWD2, 40),
		  pDBName, lAccess);
	pIStream -> Write (pOutBuff, strlen (pOutBuff), NULL);
                
	if (pUser != NULL) {
		if (pPWD != NULL) {
		// Neues Passwort verschlüsseln
		char saltc[2];
		time_t lSalt;
		
        		time (&lSalt);
        		lSalt += getpid();
	        	saltc[0] = char (lSalt & 077);
	        	saltc[1] = char ((lSalt >> 6) & 077);
        		for (i = 0; i < 2; i++){
			short c = saltc[i] + '.';
			
				if(c > '9') c += 7;
				if(c > 'Z') c += 6;
				saltc[i] = (char)c;
        		}
        		pPWD = crypt ((char *)pPWD, saltc);
        	}
		wsprintf (pOutBuff, ResString (IDS_PASSWD3, 40),
			  pUser, pPWD ? pPWD : "", lAccess, lAccess, pUser);
		pIStream -> Write (pOutBuff, strlen (pOutBuff), NULL);
	}
	
	pIStream -> Release();		// Stream schließen
	
	DELETE (pOutBuff);
	DELETE (pDBName);

return EC_OKAY;
}
#endif // OLD_PWD_IN_STORAGE

ErrCode CDBDictCompoundFile :: CreateDataFile (
					LPSTORAGE pIStorage, DWORD dwMode,
					short iIndex)
{
// vollständigen Namen erzeugen
char *pT = pFileName (iIndex);

	if (pT == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDBEx);
	if (islower (*pT)) *pT = char(toupper (*pT));
	
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(pT), 
					dwMode | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
					0, 0, &pIStream);

	if (FAILED(hr)) {
		DELETE (pT);
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDBEx);
	}

// Datei anlegen
ErrCode RC;

	RC = (ErrCode)::CreateDataStream (pIStream, pCopyRight(), 0, (short)PageSize());
	DELETE (pT);
	pIStream -> Release();
	
	if (RC != EC_OKAY) return RC;
	
#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iIndex, 0, 1));
#endif

return EC_OKAY;
}


ErrCode CDBDictCompoundFile :: CreateKeyFile (
		LPSTORAGE pIStorage, DWORD dwMode, short iIndex)
{
// vollständigen Namen erzeugen
char *pT = pFileName (iIndex);

	if (pT == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDBEx);
	if (islower (*pT)) *pT = char(toupper (*pT));
	
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(pT), 
					dwMode | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
					0, 0, &pIStream);

	if (FAILED(hr)) {
		DELETE (pT);
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDBEx);
	}

// Datei anlegen
ErrCode RC;

	RC = (ErrCode)::CreateKeyStream (pIStream, pCopyRight(), 0, (short)PageSize());
	DELETE (pT);
	pIStream -> Release();
	
	if (RC != EC_OKAY) return RC;
	
#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iIndex, -1, 2));
#endif

return EC_OKAY;
}


ErrCode CDBDictCompoundFile :: CreateTreeKeyFile (
		LPSTORAGE pIStorage, DWORD dwMode, short iIndex)
{
// vollständigen Namen erzeugen
char *pT = pFileName (iIndex);

	if (pT == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDBEx);
	if (islower (*pT)) *pT = char(toupper (*pT));
	
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(pT), 
					dwMode | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
					0, 0, &pIStream);

	if (FAILED(hr)) {
		DELETE (pT);
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDBEx);
	}

// Datei anlegen
ErrCode RC;

	RC = (ErrCode)::CreateTreeKeyStream (pIStream, pCopyRight(), 0, (short)PageSize());
	DELETE (pT);
	pIStream -> Release();
	
	if (RC != EC_OKAY) return RC;
	
#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iIndex, -1, 1));
#endif

return EC_OKAY;
}


ErrCode CDBDictCompoundFile :: CreateGeoTreeFile (
		LPSTORAGE pIStorage, DWORD dwMode, short iIndex)
{
// vollständigen Namen erzeugen
char *pT = pFileName (iIndex);

	if (pT == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDBEx);
	if (islower (*pT)) *pT = char(toupper (*pT));
	
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(pT), 
					dwMode | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
					0, 0, &pIStream);

	if (FAILED(hr)) {
		DELETE (pT);
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDBEx);
	}

// Datei anlegen
ErrCode RC;

	RC = (ErrCode)::CreateGeoTreeStream (pIStream, pCopyRight(), 0, (short)PageSize());
	DELETE (pT);
	pIStream -> Release();
	
	if (RC != EC_OKAY) return RC;
	
#if defined(BACKUP)
// Update der BackupDatei 
	DBASSERT (ReCreateBackupFileEntry (iIndex, 0, 2));
#endif

return EC_OKAY;
}


// BackupFile generieren ------------------------------------------------------
ErrCode CDBDictCompoundFile :: CreateBackupFile (
		LPSTORAGE pIStorage, DWORD dwMode, short iIndex)
{
ErrCode RC = EC_OKAY;

#if defined(BACKUP)
char *pT = pFileName (iIndex);

	if (pT == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_CreateDBEx);
	if (islower (*pT)) *pT = char(toupper (*pT));
	
LPSTREAM pIStream = NULL;
HRESULT hr = pIStorage -> CreateStream (WideString(pT), 
					dwMode | STGM_DIRECT | STGM_SHARE_EXCLUSIVE, 
					0, 0, &pIStream);

	if (FAILED(hr)) {
		DELETE (pT);
		return (ErrCode)db_error (EC_NOFILE, RC_CreateDBEx);
	}

// Datei anlegen
	ReCreateBackupFileEntry (iIndex, -1, -1);
	RC = (ErrCode)::CreateBackupStream (pIStream, pCopyRight(), 0, (struct pg_zero *)m_pPZTable, iFiles(), (short)PageSize());
	DELETE (pT);
	pIStream -> Release();
#endif

return RC;
}





// sonstige Klassen -----------------------------------------------------------
// KeyNameIterator ------------------------------------------------------------
CKeyNameIterator :: CKeyNameIterator (CDBDict &DBD)
		  : m_rDBDict (DBD)
{
	m_iCurrIndex = 0;
}

CKeyNameIterator :: ~CKeyNameIterator (void)
{
	// nothing to do
}

char *CKeyNameIterator :: GetFirstKeyName (void)
{
	return GetKeyName (m_iCurrIndex = 0);		// erster Eintrag
}

char *CKeyNameIterator :: GetNextKeyName (void)
{
	return GetKeyName (++m_iCurrIndex);		// nächster Eintrag
}

char *CKeyNameIterator :: GetKeyName (short iIndex)
{
	if (m_rDBDict.m_pKeyTable == NULL || 
	    iIndex < 0 || iIndex >= m_rDBDict.iKeys())
		return NULL;

	return m_rDBDict.m_pKeyTable[iIndex].kepName;
}

// SicherStellen, daß Pfad existiert ------------------------------------------
BOOL CreateFullGeoDBPath (const char *pFullPath)
{
	if (pFullPath == NULL) return true;	// temporär erzeugen

// Testen, ob Pfad schon existiert
string strNewPath = pFullPath;
char cbPath[_MAX_PATH];

	{
	string strPath = get_path (strNewPath);
	string strDrive = get_drive (strNewPath);

		_makepath (cbPath, strDrive.c_str(), strPath.c_str(), "", "");
		strNewPath = cbPath;
	}

BOOL fRes = true;

	GetCurrentDirectory (_MAX_PATH, cbPath);
	if (!SetCurrentDirectory (cbPath))	// Verzeichnis erzeugen
		fRes = CreateDirectory (cbPath, NULL);
	SetCurrentDirectory (cbPath);

return fRes;
}

