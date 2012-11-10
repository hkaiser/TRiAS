// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File VISMTREE.HXX
// Generiert aus TTREE.CTT

#if !defined(_VISMTREE_HXX)
#define _VISMTREE_HXX

typedef char * pChar;		// Schlüsseltyp

// Klasse, die im Baum hängen soll --------------------------------------------
class CVisModule {
	pChar m_Key;				// Suchschlüssel
	class CDllBindX *m_pVCSModule;		// angehängte DLL
	
public:
	LPVISMODULE m_pIVisModule;		// VisModule

		CVisModule (void);
		~CVisModule (void);

	bool FInit (pChar pVisModuleName, pChar pProject);	// Initialisierung der Klasse
	bool isValid (void);			// erfolgreich gebunden
		
// Funktionen zur SuchSchlüsselVerwaltung
	pChar & FGetpChar (void);		// liefert SuchSchlüssel

friend int FCmppChar (pChar &, pChar &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* TTREEGETKEYFCN) (void *);
typedef int (* TTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CVisModuleEnumFunc)(CVisModule &, void *);

  
class CVisModuleTree : public CTree {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CVisModuleTree (void);
		~CVisModuleTree (void);

// Elementarfunktionen
	bool FAddItem (pChar pVisModuleName, char *pProject = NULL);	// Element hinzufügen
	bool FDeleteItem (pChar &);			// Element löschen
	CVisModule *FFindItem (pChar &);		// Element liefern
	CVisModule *FFindOrAdd (pChar &, char *pProject = NULL);	// Element ggf. einfügen

// Notifikationen an einzelne VisModule
	void OnProjectChange (HWND hWndM, PROJECTCHANGE rgPC, char *pPrName);
	void OnViewChange (HWND hWndM, VIEWCHANGE rgVC, char *pView);
	void OnPaletteChange (HWND hWndM, HPALETTE hPal);
		
// SuchSchlüsselVerwaltung
friend pChar *FTTreeGetpChar (CVisModule *pObj);
friend int FTTreeCmppChar (pChar *pObj1, pChar *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator ---------------
DeclareLock (CVisModuleTree, CVisModule);

#endif // _VISMTREE_HXX

