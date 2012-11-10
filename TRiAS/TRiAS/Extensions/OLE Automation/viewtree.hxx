// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// Generiert aus CTTREE.CTT
// File: VIEWTREE.HXX

#if !defined(_VIEWTREE_HXX)
#define _VIEWTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoView;
typedef CGeoView CGeoView2;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CViewTreeBase;
typedef CTable CViewTreeTable;
typedef CSyncThread CViewTreeSync;
typedef CLock CGeoView2Lock;
#else
int FCmpBSTR (LPCSTR pView1, LPCSTR pView2);
DefineCmpForTree(CViewTree, FCmpBSTR, LPCSTR);			// defines CViewTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<LPCSTR, CGeoView *, CViewTreeCmp> CViewTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoViewEnumFunc)(CGeoView &, void *);
  
class CViewTree : 
	public CViewTreeBase 
{
private:
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pView);

public:
// Konstruktor/Destruktor
		 CViewTree (void);
		~CViewTree (void);

static CViewTree *CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc);

	bool FInit (CTriasApp *pApp, CGeoDoc *pDoc);

// Elementarfunktionen
	CGeoView *FAddItem (LPCSTR bName, DView **ppIView, VIEWMODE rgMode);	// Element hinzufügen
	bool FAddItem (CGeoView *pView);				// Element hinzufügen
	bool FDeleteItem (LPCSTR rKT);			// Element löschen
	bool FInvalidateItem (LPCSTR pName);
		
	CGeoView *FFindItem (LPCSTR rKT);		// Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (LPCSTR oldKey, LPCSTR newKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CGeoViewEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (LPCSTR rKey, CGeoViewEnumFunc pFcn, void *pEData = NULL);

	bool SetViewName (LPCSTR bOldName, LPCSTR bNewName);

// SuchSchlüsselVerwaltung
friend LPCSTR FCTTreeGetViewBSTR (CGeoView *pView);
friend int FCTTreeCmpViewBSTR (LPCSTR pView1, LPCSTR pView2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CViewTree, CGeoView2);

#endif // _VIEWTREE_HXX

