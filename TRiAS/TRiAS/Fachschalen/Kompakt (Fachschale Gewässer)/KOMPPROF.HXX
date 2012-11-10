// Klassendeklarationen für Kompakt-Profile-Dateien (Applikationen)
// File: KOMPPROF.HXX

#if !defined(_KOMPPROF_HXX)
#define _KOMPPROF_HXX


//--------------------------------------------------------------------------

// Verwaltung einer ProfileDatei
class KompaktProFile {
private:  
	
	char *_pFullName;	// Pfadname der ProfileDatei
	char *_pSoftPath;	// Pfad Software
	char *_pDataPath;	// Pfad Daten
	ResourceFile *_pResTarget;	// evtl. ResourceFile

public:
// Konstruktor/Destruktor
		KompaktProFile ( ResourceFile *pResTarget);
		~KompaktProFile (void);

// Member
	char * GetPathLibrary(void);
	char * GetSoftPath(void) { return _pSoftPath;};
	char * GetDataPath(void) { return _pDataPath;};
	char * GetPathDaten(void);
	char *GetLeistungsSchrittweite(void);
	char *GetPufferZone(void);
	void SetLeistungsSchrittweite(short);
	void SetPufferZone(short);
};
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

// Verwaltung einer ProfileDatei
class KompaktPrivateProFile {
private:  
	
	char *_pFullName;	// Pfadname der ProfileDatei
	char *_pSoftPath;	// Pfad Software
	char *_pDataPath;	// Pfad Daten
	ResourceFile *_pResTarget;	// evtl. ResourceFile

public:
// Konstruktor/Destruktor
		KompaktPrivateProFile ( ResourceFile *pResTarget, char *pProject);
		~KompaktPrivateProFile (void);

// Member
	char * GetPathLibrary(void);
	char * GetPathDaten(void);
	char * GetDataPath(void) { return _pDataPath;};
	char * GetSoftPath(void) { return _pSoftPath;};
	char *GetLeistungsSchrittweite(void);
	char *GetPufferZone(void);
};

#endif // _KOMPPROF_HXX
