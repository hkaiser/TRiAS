// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus TTREE.CTT

#if !defined(__TTREE_HXX)
#define __TTREE_HXX

typedef char * pChar;

// Klasse, die im Baum hängen soll --------------------------------------------
class CImpView {
	pChar m_pView;		// Suchschlüssel
	short m_cnIdents;	// Anzahl der Idents
	short m_fImport;	// soll importiert werden

public:
		CImpView (char *pView, short cnCnt = 0);
		~CImpView (void);

// ZugriffsFunktionen
	char *GetViewName (void) { return m_pView; }
	short &IdCount (void) { return m_cnIdents; }
	short &Import (void) { return m_fImport; }
	
// Funktionen zur SuchSchlüsselVerwaltung
	pChar & FGetpChar (void);		// liefert SuchSchlüssel
	
friend int FCmppChar (pChar &, pChar &);	// vergleicht 2 Schlüssel
};


// Eigentliche typspezifische TreeKlasse --------------------------------------

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* TTREEGETKEYFCN) (void *);
typedef int (* TTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CImpViewEnumFunc)(CImpView &, void *);

  
class CImpViewTree : public CTree {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CImpViewTree (void);
		~CImpViewTree (void);

// Elementarfunktionen
	bool FAddItem (char *, short = 0);	// Element hinzufügen
	bool FDeleteItem (pChar &);		// Element löschen
	CImpView *FFindItem (pChar &);		// Element liefern

	bool FReInsert (pChar &oldKey, pChar &newKey);

// EnumerationsFunktionen
	bool FEnumAllItems (CImpViewEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (pChar &rKey, CImpViewEnumFunc pFcn, void *pEData = NULL);

	short CountIdents (void);
	
// SuchSchlüsselVerwaltung
friend pChar *FTTreeGetpChar (CImpView *pObj);
friend int FTTreeCmppChar (pChar *pObj1, pChar *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareLock (CImpViewTree, CImpView);

#endif // _TTREE_HXX

