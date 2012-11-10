// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: CLNMTREE.HXX

#if !defined(_CLNMTREE_HXX)
#define _CLNMTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CClass;
typedef CClass CClass2;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CClsNameTreeBase;
typedef CTable CClsNameTreeTable;
typedef CSyncThread CClsNameTreeSync;
typedef CLock CClass2Lock;
#else
int FCmpBSTR (LPCSTR, LPCSTR);	// vergleicht 2 Schlüssel
DefineCmpForTree(CClsNameTree, FCmpBSTR, LPCSTR);			// defines CClsNameTreeCmp
typedef container_wrappers::CTreeOnStl<LPCSTR, CClass *, CClsNameTreeCmp> CClsNameTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CClassEnumFunc)(CClass &, void *);
  
class CClsNameTree : 
	public CClsNameTreeBase 
{
private:
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pCls);

public:
// Konstruktor/Destruktor
		CClsNameTree (CTriasApp *pApp, CGeoDoc *pDoc);
		~CClsNameTree (void);

// Elementarfunktionen
	CClass *FAddItem (LPCSTR bName, DGeoClass **ppICls, GEOCLASSMODE rgMode, LPCSTR pcSrc = NULL);	// Element hinzufügen
	bool FAddItem (CClass *);		// Element hinzufügen
	bool FDeleteItem (LPCSTR);		// Element löschen
	CClass *FFindItem (LPCSTR);		// Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (LPCSTR oldKey, LPCSTR newKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CClassEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (LPCSTR rKey, CClassEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend LPCSTR FCTTreeGetClsBSTR (CClass *pCls);
friend int FCTTreeCmpClsBSTR (LPCSTR pCls1, LPCSTR pCls2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CClsNameTree, CClass2);

#endif // _CLNMTREE_HXX

