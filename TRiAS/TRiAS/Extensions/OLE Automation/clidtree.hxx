// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
//File: CLIDTREE.HXX

#if !defined(_CLIDTREE_HXX)
#define _CLIDTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CClass;
typedef CClass CClass1;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CIDTreeBase;
typedef CTable CIDTreeTable;
typedef CSyncThread CIDTreeSync;
typedef CLock CClass1Lock;
#else
int FCmpULONG (const ULONG &, const ULONG &);	// vergleicht 2 Schlüssel
DefineCmpForTree(CIDTree, FCmpULONG, ULONG);			// defines CIDTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<ULONG, CClass *, CIDTreeCmp> CIDTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CClassEnumFunc)(CClass &, void *);
  
class CIDTree : 
	public CIDTreeBase 
{
private:
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pCls);

public:
// Konstruktor/Destruktor
		CIDTree (CTriasApp *pApp, CGeoDoc *pDoc);
		~CIDTree (void);

// Elementarfunktionen
	CClass *FAddItem (ULONG lIdent, DGeoClass **ppICls, GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL);	// Element hinzufügen
	bool FAddItem (CClass *pCls);		// Element hinzufügen
	bool FDeleteItem (ULONG &);		// Element löschen
	CClass *FFindItem (ULONG &);		// Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (ULONG &oldKey, ULONG &newKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CClassEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (ULONG &rKey, CClassEnumFunc pFcn, void *pEData = NULL);

// Zugriff auf Document
	CGeoDoc *GetDoc() { return m_pDoc; }

// SuchSchlüsselVerwaltung
friend ULONG *FCTTreeGetClsULONG (CClass *pCls);
friend int FCTTreeCmpClsULONG (const ULONG *pCls1, const ULONG *pCls2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CIDTree, CClass1);

#endif // _CLIDTREE_HXX

