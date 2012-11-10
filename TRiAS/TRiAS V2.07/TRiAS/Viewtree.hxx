// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: VIEWTREE.HXX

#if !defined(_VIEWTREE_HXX)
#define _VIEWTREE_HXX

// Klasse, die im Baum hängen soll --------------------------------------------
class CViewEntry {
private:
	string m_Key;			// Suchschlüssel
	bool m_fActView;		// aktuell ausgewählte Sicht
	bool m_fDefaultView;		// StandardSicht
	bool m_fInMenu;			// ist derzeit im Menu

public:
		CViewEntry (LPCSTR pcView);
		~CViewEntry (void);

// Memberfunktionen
	bool isActView (void) { return m_fActView ? true : false; }
	bool isDefaultView (void) { return m_fDefaultView ? true : false; }
	bool isInMenu (void) { return m_fInMenu ? true : false; }

	void SetActive (bool fActView = true) 
		{ m_fActView = fActView ? true : false; }
	void SetDefault (bool fDefView = true) 
		{ m_fDefaultView = fDefView ? true : false; }
	void SetInMenu (bool fInMenu = true) 
		{ m_fInMenu = fInMenu ? true : false; }

// Funktionen zur SuchSchlüsselVerwaltung
	string & FGetstring (void);		// liefert SuchSchlüssel
friend int FCmpstring (string &, string &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CViewEntryEnumFunc)(CViewEntry &, bool, void *);

  
class CViewsTree : public CTree {
private:
	GeoDB &m_rDB;
	bool n_fTempViewActive;

protected:
	void UserDelete (void *pObj);

		CViewsTree (GeoDB &rDB);

	bool FInit (void);	// Sichten einlesen

public:
// Konstruktor/Destruktor/Initialisierung
		~CViewsTree (void);

static CViewsTree *CViewsTree :: CreateInstance (GeoDB &rDB);

// Elementarfunktionen
	CViewEntry *FAddItem (LPCSTR pcView);		// Element hinzufügen
	bool FDeleteItem (LPCSTR pcView);		// Element löschen
	CViewEntry *FFindItem (LPCSTR pcView);	// Element liefern

	bool FReInsert (const string &oldKey, const string &newKey);

// EnumerationsFunktionen
	bool FEnumAllItems (CViewEntryEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (const string &rKey, CViewEntryEnumFunc pFcn, void *pEData = NULL);

// sonstige Memberfunktionen
	GeoDB & DB (void) const { return m_rDB; }

	bool GetDefaultView (LPSTR pcView, int iLen);
	bool GetActView (LPSTR cbView, int iLen);

	bool isDefaultView (LPCSTR pcView);
	bool isActView (LPCSTR pcView);
	bool isInMenu (LPCSTR pcView);

	bool SetDefaultView (LPCSTR pcView);
	bool SetActView (LPCSTR pcView, bool fAct = true);
	bool SetInMenu (LPCSTR pcView, bool fInMenu = true);

	bool GetNext (string &rstr);

// SuchSchlüsselVerwaltung
friend string *FCTTreeGetstring (CViewEntry *pObj);
friend int FCTTreeCmpstring (string *pObj1, string *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CViewsTree, CViewEntry);

#include "viewtree.inl"	// Inline-Funktionen

#endif // _VIEWTREE_HXX

