// Objekt, welches eine DBStruktur vollstaendig beschreibt --------------------
// File: DBD.HXX

#if !defined(_DBD_HXX)
#define _DBD_HXX

class _TRIAS01_ENTRY CDBDict {
private:
	bool m_fIsValid;

protected:
	DBDHEADER *m_pDBDHeader;		// HeaderInformation
	FILEENTRY *m_pFileTable;		// DateiEinträge
	KEYENTRY *m_pKeyTable;			// KeyTabelle
	RECORDENTRY *m_pRecordTable;		// RecordTabelle
	FIELDENTRY *m_pFieldTable;		// FeldTabelle
	PGZEROENTRY *m_pPZTable;		// PageZerotable
	
	long m_lDBDVersion;			// VersionsNummer
	long m_lPageSize;
	char *m_pDefExt;			// StandardErweiterung

// Memberfunktionen (zerlegen der DBDresource)
	DBDHEADER *ReadDBDHeader (LPBYTE);
	FILEENTRY *ReadFileTable (LPBYTE);
	KEYENTRY *ReadKeyTable (LPBYTE);
	RECORDENTRY *ReadRecordTable (LPBYTE);
	FIELDENTRY *ReadFieldTable (LPBYTE);
	long DBDVersion (LPBYTE);
	long PageSize (LPBYTE);
	char *pDefaultExt (LPBYTE);

	short RecordNum (short);

	ErrCode ReCreateBackupFileEntry (short iFileIndex, short iChain, short iNext);

// Parameter des Headers zugänglich machen
	short iFiles (void) { return short(m_pDBDHeader ? m_pDBDHeader->iFiles : 0); }
	short iKeys (void) { return short(m_pDBDHeader ? m_pDBDHeader->iKeys : 0); }
	short iRecords (void) { return short(m_pDBDHeader ? m_pDBDHeader->iRecords : 0); }
	short iFields (void) { return short(m_pDBDHeader ? m_pDBDHeader->iFields : 0); }
	short iBackup (void) { return short(m_pDBDHeader ? m_pDBDHeader->iBackupFlag : 0); }
	const char *pCopyRight (void) { return m_pDBDHeader ? m_pDBDHeader->Copyright : NULL; }
 
// sonstige Interna des DBDicts zugänglich machen
	long DBDVersion (void) { return m_lDBDVersion; }
	long PageSize (void) { return m_lPageSize; }
	
	short iFileType (short);
	
	char *pFileType (short);
	char *pKeyType (short);
	char *pKeyFileType (short);
	char *pKeyFieldType (short);

public:
	long FileNo (long lRecNo);
	short RecSize (long lRecNo);

		CDBDict (void);
	virtual ~CDBDict (void);

	bool Init (LPBYTE lpDBDResource);

// Objekt ist gültig/ungültig
	operator bool (void) { return m_fIsValid; }
	bool operator !(void) { return !m_fIsValid; }

	char *pFileName (short);
	char *pKeyFileName (short);
	char *pTargetFileName (short);
	char *pTreeKeyFileName (short);
	short isBTreeKey (short);

	long SetDBDVersion (LPBYTE lpDBDResource, long lNewVersion);

// neue leere GeoDB erzeugen
virtual ErrCode CreateDB (const char *pFullPath, const char *pUser = NULL,
			  const char *pPWD = NULL) = 0;

// KeyIteratorKlasse
friend class CKeyNameIterator;
friend class CTargetFileIterator;
};


// Verschiedene ProjektTypen --------------------------------------------------
class _TRIAS01_ENTRY CDBDictDOSFiles : public CDBDict {
protected:
	ErrCode ReIndex (HPROJECT hPr, short iKeyIndex, const char *pFullPath);

// Operationen in einer konkreten Datenbasis
	ErrCode CreateDictionary (const char *pFullPath);
	ErrCode CreateDataFile (short iFile, char *pFileN, const char *pFullPath);
	ErrCode CreateKeyFile (short iFile, char *pFileN, const char *pFullPath);
	ErrCode CreateTreeKeyFile (short iFile, char *pFileN, const char *pFullPath);
	ErrCode CreateGeoTreeFile (short iFile, char *pFileN, const char *pFullPath);
	ErrCode CreateBackupFile (short iFile, char *pFile, const char *pFullPath);
	ErrCode CreatePassWordFile (const char *pFullPath, const char *pUser = NULL, 
				    const char *pPWD = NULL);
	
public:
		CDBDictDOSFiles (void) {}
		~CDBDictDOSFiles (void) {}
		
static CDBDictDOSFiles *CreateInstance (LPBYTE);

	ErrCode CreateDataFile (short iIndex, const char *pFullPath);
	ErrCode CreateKeyFile (short iKeyIndex, const char *pFullPath);
	ErrCode CreateTreeKeyFile (short iKeyIndex, const char *pFullPath);
	ErrCode CreateGeoTreeFile (short iKeyIndex, const char *pFullPath);

// neue leere GeoDB erzeugen
	ErrCode CreateDB (const char *pFullPath, const char *pUser = NULL,
			  const char *pPWD = NULL);
};


#if defined(__WATCOMC__)
// redefinition of typedef ... ignored
#pragma warning 583 4;
#endif
typedef struct IStorage *LPSTORAGE;

class _TRIAS01_ENTRY CDBDictCompoundFile : public CDBDict {
protected:
	ErrCode CreateDictionary (LPSTORAGE pIStorage, DWORD dwMode);
	ErrCode CreatePassWordFile (LPSTORAGE pIStorage, DWORD dwMode,
				    const char *pFullPath, const char *pUser, 
				    const char *pPWD);
	ErrCode CreateDataFile (LPSTORAGE pIStorage, DWORD dwMode, short iIndex);
	ErrCode CreateKeyFile (LPSTORAGE pIStorage, DWORD dwMode, short iIndex);
	ErrCode CreateTreeKeyFile (LPSTORAGE pIStorage, DWORD dwMode, short iIndex);
	ErrCode CreateGeoTreeFile (LPSTORAGE pIStorage, DWORD dwMode, short iIndex);
	ErrCode CreateBackupFile (LPSTORAGE pIStorage, DWORD dwMode, short iIndex);

public:
		CDBDictCompoundFile (void) {}
		~CDBDictCompoundFile (void) {}
		
static CDBDictCompoundFile *CreateInstance (LPBYTE);

// neue leere GeoDB erzeugen
	ErrCode CreateDB (const char *pFullPath, const char *pUser = NULL,
			  const char *pPWD = NULL);
	ErrCode CreateDBEx (const char *pFullPath, const char *pUser = NULL,
			    const char *pPWD = NULL, LPSTORAGE *ppIStorage = NULL,
			    const CLSID *pClsID = NULL, const char *pCF = NULL);
};


// diverse HilfsKlassen -------------------------------------------------------
class CKeyNameIterator {
private:
	short m_iCurrIndex;
	CDBDict &m_rDBDict;

protected:
	char *GetKeyName (short);

public:
// Konstruktor/Destruktor
		CKeyNameIterator (CDBDict &);
		~CKeyNameIterator (void);

	char *GetFirstKeyName (void);
	char *GetNextKeyName (void);
};

#endif // _DBD_HXX
