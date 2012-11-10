// Klassendeklarationen für lokale Profile-Dateien (Projekte umschalten)
// File: PROJPROF.HXX

#if !defined(_PROJPROF_HXX)
#define _PROJPROF_HXX


// Verwaltung einer ProfileDatei
class ProjectProFile {
private:
	char *_pProject;	// Project
	char *_pFullName;	// Pfadname der ProfileDatei
	char *_pFileName;
	char *_pDrive;
	char *_pPath;
	char *_pDBName;
	char *_pExt;
	char *_pKey;
	int _iNumMenuPoints;
	short _iLevel;
	char *_pProfProj;
	class TPRJTree *_pTPRJ;
	class PROJTree *_pPROJ;
	ResourceFile *_pResTarget;	// evtl. ResourceFile

	char *_pNewPath;
	char *_pOldPath;
	char *_pOldProject;

public:
// Konstruktor/Destruktor
		ProjectProFile (const char *Project, ResourceFile *pResTarget, PROJTree * pPROJ, short iLevel);
		~ProjectProFile (void);

// Memberfunktionen
// Verwalten der Merkmalskodes, die ProjectMCode enthalten

	char *GetProjectName ( char *pKey);
	char *GetIniName ( void ) { return _pFullName; };
	char *GetProjectTab ( void ) { return _pFileName; };
	int GetProjectFile ( void );	// Analysieren ProjectFile (Folge von DB's)
	TPRJTree * pTPRJ ( void ) { return _pTPRJ;};
	bool ActualProjectFile(char *, char *, char*, char *);

	// KK 010601
	bool PathCorrection(void);
};

#endif // _PROJPROF_HXX
