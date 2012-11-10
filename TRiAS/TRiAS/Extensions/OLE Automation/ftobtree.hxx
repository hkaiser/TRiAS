// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File: FTOBTREE.HXX

#if !defined(_FTOBTREE_HXX)
#define _FTOBTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoFeatureBase;
typedef CGeoFeatureBase CGeoFeatureBase3;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CFeatObjTreeBase;
typedef CTable CFeatObjTreeTable;
typedef CSyncThread CFeatObjTreeSync;
typedef CLock CGeoFeatureBase3Lock;
#else
int FCmpBSTR (LPCSTR pFeat1, LPCSTR pFeat2);
DefineCmpForTree(CFeatObjTree, FCmpBSTR, LPCSTR);			// defines CFeatObjTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<LPCSTR, CGeoFeatureBase *, CFeatObjTreeCmp> CFeatObjTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoFeatureEnumFunc)(CGeoFeatureBase &, void *);
  
class CFeatObjTree : 
	public CFeatObjTreeBase 
{
private:
	IDispatch *m_pObj;
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pFeat);

public:
// Konstruktor/Destruktor
		 CFeatObjTree (void);
		~CFeatObjTree (void);

static CFeatObjTree *CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc, IDispatch *pObj);

	bool FInit (CTriasApp *pApp, CGeoDoc *pDoc, IDispatch *pObj);

// Elementarfunktionen
	CGeoFeatureBase *FAddItem (
		LPCSTR bName, DGeoFeature **ppIFeat, FEATUREMODE rgMode, 
		PROPCAPS rgProps, VARIANT *pvOptData, IObjectProperty *pIObjProp);	// Element hinzufügen

	bool FAddItem (CGeoFeatureBase *pFeat);				// Element hinzufügen
	bool FDeleteItem (LPCSTR rKT);						// Element löschen
	bool FInvalidateItem (LPCSTR pName);
		
	CGeoFeatureBase *FFindItem (LPCSTR rKT);			// Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (LPCSTR oldKey, LPCSTR newKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CGeoFeatureEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (LPCSTR rKey, CGeoFeatureEnumFunc pFcn, void *pEData = NULL);

	bool SetFeatureName (LPCSTR bOldName, LPCSTR bNewName);

// SuchSchlüsselVerwaltung
friend LPCSTR FCTTreeGetObjFeatBSTR (CGeoFeatureBase *pFeat);
friend int FCTTreeCmpObjFeatBSTR (LPCSTR pFeat1, LPCSTR pFeat2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CFeatObjTree, CGeoFeatureBase3);

#endif // _FTOBTREE_HXX

