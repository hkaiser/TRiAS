// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File: DOCTREE.HXX

#if !defined(_DOCTREE_HXX)
#define _DOCTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoDoc;
typedef CGeoDoc CGeoDoc2;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CDocTreeBase;
typedef CTable CDocTreeTable;
typedef CSyncThread CDocTreeSync;
typedef CLock CGeoDoc2Lock;
#else
int FCmpBSTR (LPCSTR, LPCSTR);
DefineCmpForTree(CDocTree, FCmpBSTR, LPCSTR);		// defines CDocTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<LPCSTR, CGeoDoc *, CDocTreeCmp> CDocTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CDocEnumFunc)(CGeoDoc &, void *);
  
class CDocTree :
	public CDocTreeBase
{
private:
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pDoc);

public:
// Konstruktor/Destruktor
		 CDocTree (void);
		~CDocTree (void);

static CDocTree *CreateInstance (CTriasApp *pApp);

	bool FInit (CTriasApp *pApp);

// Elementarfunktionen
	HRESULT FAddItem (LPCSTR bName, CGeoDoc **ppDoc, DDocument **ppIDoc, DOCMODE rgMode);	// Element hinzufügen
	HRESULT FAddItem (HPROJECT hPr, CGeoDoc **ppDoc, DDocument **ppIDoc, DOCMODE rgMode);	// Element hinzufügen
	bool FAddItem (CGeoDoc *pDoc);				// Element hinzufügen
	bool FDeleteItem (LPCSTR rKT);				// Element löschen
	bool FInvalidateItem (LPCSTR pName);
		
	CGeoDoc *FFindItem (LPCSTR rKT);			// Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (LPCSTR oldKey, LPCSTR newKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CDocEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (LPCSTR rKey, CDocEnumFunc pFcn, void *pEData = NULL);

	bool SetDocName (LPCSTR bOldName, LPCSTR bNewName);

// SuchSchlüsselVerwaltung
friend LPCSTR FCTTreeGetDocBSTR (CGeoDoc *pDoc);
friend int FCTTreeCmpDocBSTR (LPCSTR pDoc1, LPCSTR pDoc2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CDocTree, CGeoDoc2);

#endif // _DOCTREE_HXX

