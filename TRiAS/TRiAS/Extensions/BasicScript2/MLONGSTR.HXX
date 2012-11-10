// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT

#if !defined(_MLONGSTR_HXX)
#define _MLONGSTR_HXX

// Klasse, die im Baum hängen soll --------------------------------------------
class CLongString {
private:
	LONG m_Key;				// Suchschlüssel
	string m_Data;

public:
		CLongString (LONG lKey, LPCTSTR pData);
		~CLongString (void);

// Funktionen zur SuchSchlüsselVerwaltung
	LONG & FGetLONG (void);		// liefert SuchSchlüssel
	LPCTSTR FGetData (void) { return m_Data.c_str(); }

friend int FCmpLONG (LONG &, LONG &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
class CMapLongString : public CTree {
private:
	DWORD m_dwRefCnt;

	DWORD m_dwInsert;	// Zeit der letzten Einfügung
	DWORD m_dwOpt;		// Zeit der letzten Optimierung

protected:
	void UserDelete (void *pObj);

public:
	DWORD AddRef (void);
	DWORD Release (void);
	
// Konstruktor/Destruktor
		CMapLongString (void);
		~CMapLongString (void);

static CMapLongString *CreateInstance (void);

// Elementarfunktionen
	bool FAddItem (LONG lKey, LPCTSTR pData);	// Element hinzufügen
	bool FDeleteItem (LONG &);			// Element löschen
	CLongString *FFindItem (LONG &);		// Element liefern

// SuchSchlüsselVerwaltung
friend LONG *FCTTreeGetLONG (CLongString *pObj);
friend int FCTTreeCmpLONG (LONG *pObj1, LONG *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CMapLongString, CLongString);

#endif // _MLONGSTR_HXX

