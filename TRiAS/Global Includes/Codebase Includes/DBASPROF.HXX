// Klassendeklarationen für lokale Profile-Dateien (DBasedaten anzeigen)
// File: DBASPROF.HXX

#if !defined(_DBASPROF_HXX)
#define _DBASPROF_HXX

#if !defined(NODBASEPROF)
class E4EXPORT_FCT DBaseRel;

// Verwaltung einer ProfileDatei
class E4EXPORT_FCT DBaseProFile {
private:
	char *_FullName;        // Pfadname der ProfileDatei

public:
// Konstruktor/Destruktor
	DBaseProFile (void);
	~DBaseProFile (void);

// Memberfunktionen
// 	Verwalten der Merkmalskodes, die Bildinfo enthalten
    int ReadDBaseCodes (long **, char ***, long Id = -1L);
	int ReadDBaseRelations (DBaseRel &, DBaseRel ***, long Id = -1L);
	char *GetProFileName (void) { return _FullName; }
	Bool ReadDBaseEntry (long Ident, pchar pBuffer, short BufferSize);
	Bool WriteDBaseEntry (long Ident, pchar pBuffer);
	char *GetAliasFileName (char *pAliasName);	// Speicher ist freizugeben
                // neuen Alias-Dateinamen in Projekt-Ini-Datei schreiben 
        Bool WriteAliasFileName (char *pAliasName, char *pFileName);    
};
#endif // NODBASEPROF

/*
class CAliasFieldProFile
{ 
private:
	char *m_pFileName;    	// Name der Profile-Datei
	short m_sMaxCnt;		// max. Größe eines Profile-Eintrages
	
//	Konstruktor/Destruktor		
	CAliasFieldProFile (void);
	~CAliasFieldProFile (void);	
	
//	weitere Member                 
	Bool Init (char *pAliasName);		// Dateinamen und. MaxCnt ermitteln
	const char* GetFileName (void) { return m_pFileName; }                                        
	short GetMaxCnt (void) { return m_sMaxCnt;}
	char* GetAliasName (char *pFieldName);		// lesen zugeh. Aliasnamen, 
												// Speicher ist explizit freizugeben
};
*/  
  
#endif // _DBASPROF_HXX
