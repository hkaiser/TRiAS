// WrapperKlasse, die KeyDatei(en) eines Schluessels umbennent ----------------
// File BAKKEY.HXX

#if !defined(_BAKKEY_HXX)
#define _BAKKEY_HXX

class _TRIAS01_ENTRY CDBDictDOSFiles;

class CBackupKeyFile {
private:
	char *m_pKeyFile;	// Dateinamen in der DB
	char *m_pTreeFile;
	char *m_pBackupKeyFile;	// umbennante Dateien
	char *m_pBackupTreeFile;
	HPROJECT m_hPr;

public:
		CBackupKeyFile (HPROJECT hPr);
		~CBackupKeyFile (void);

	bool Init (CDBDictDOSFiles &DBD, const char *pFullPath, short iKeyIndex);
	
	void SetOK (void);	// verhindert Rückbennenung
};

// lokale FunktionsTemplates
char *MakeTempName (unsigned int, const char *);

#endif // _BAKKEY_HXX
