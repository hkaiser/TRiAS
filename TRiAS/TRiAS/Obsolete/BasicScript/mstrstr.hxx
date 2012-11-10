// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT

#if !defined(_MSTRSTR_HXX)
#define _MSTRSTR_HXX

// Klasse, die im Baum hängen soll --------------------------------------------
class CStringString {
private:
	DWORD m_dwRefCnt;

	string m_Key;				// Suchschlüssel
	string m_Data;
	
public:
	DWORD AddRef (void);
	DWORD Release (void);

		CStringString (LPCTSTR pKey, LPCTSTR pData);
		~CStringString (void);

// Funktionen zur SuchSchlüsselVerwaltung
	LPCTSTR FGetLPCTSTR (void);		// liefert SuchSchlüssel
	LPCTSTR FGetData (void) { return m_Data.c_str(); }
	void FSetData (LPCTSTR pData) { m_Data = pData; }
		
friend int FCmpLPCTSTR (LPCTSTR, LPCTSTR);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
class CMapStringString : public CTree {
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
		CMapStringString (void);
		~CMapStringString (void);

static CMapStringString *CreateInstance (void);

// Elementarfunktionen
	bool FAddItem (LPCTSTR, LPCTSTR);	// Element hinzufügen
	bool FAddItem (CStringString *pItem);
	bool FDeleteItem (LPCTSTR);		// Element löschen
	CStringString *FFindItem (LPCTSTR);	// Element liefern

// SuchSchlüsselVerwaltung
friend LPCTSTR FCTTreeGetLPCTSTR (CStringString *pObj);
friend int FCTTreeCmpLPCTSTR (LPCTSTR pObj1, LPCTSTR pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CMapStringString, CStringString);

#endif // _MSTRSTR_HXX

