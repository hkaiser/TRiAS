// Klassendeklarationen für lokale Profile-Dateien ----------------------------
// File: PROFILE.HXX

#if !defined(_PROFILE_HXX)
#define _PROFILE_HXX

// Konstanten für Ansichtenverwaltung
#define MAXSIGHTS	200				// max. Anzahl der Ansichten
#define SIGHTMENUITEM	_MAX_PATH	// max. Länge eines Menuitems

#if !defined(NOPROFILE)

class DBaseRel;

// Verwaltung einer ProfileDatei
class ProFile {
protected:
	char *_FullName;	// Pfadname der ProfileDatei
	const char *_pResTarget;	// evtl. ResourceFile

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 ProFile (const char *Project, const char *pResTarget = NULL);

// Memberfunktionen
// Identifikatorweises einfärben
	Bool SetIdEntry (long Id, Color C, Bool Fill, int Prio);
	Color *GetIdEntry (long Id, Bool &Fill, int &Prio);

#if defined(_FORCE_LEGACY_CODE)
// Verwaltung der Ansichten (Sight's)
	char *GetStandardSight (void);
	void SetStandardSight (char *);

// Verwalten des MerkmalsKodes, der Objektnamen enthält
	long GetObjNameCode (char *pOKS = NULL, bool *pfForceMCode = NULL);
#endif // defined(_FORCE_LEGACY_CODE)

	_TRIAS02_ENTRY char *GetObjNameFeature (LPCSTR pOKS, char *pBuffer, int iLen, bool *pfForce = NULL);

// Extensions laden
_TRIAS02_ENTRY int EXPORT02 SetPreLoad (char *, int);
_TRIAS02_ENTRY int EXPORT02 GetPreLoad (char *);

// Letzten verwendeten Ident verwalten
	long GetLastIdent (void);
	void SetLastIdent (long lIdent);
	HPROJECT FindConnection (LPCSTR pcConnection);

// Destruktor
	_TRIAS02_ENTRY EXPORT02 ~ProFile (void);
};
#endif // NOPROFILE

#endif // _PROFILE_HXX
