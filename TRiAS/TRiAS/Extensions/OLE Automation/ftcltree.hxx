// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File: FTCLTREE.HXX

#if !defined(_FTCLTREE_HXX)
#define _FTCLTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoFeatureBase;
typedef CGeoFeatureBase CGeoFeatureBase2;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CFeatClsTreeBase;
typedef CTable CFeatClsTreeTable;
typedef CSyncThread CFeatClsTreeSync;
typedef CLock CGeoFeatureBase2Lock;
#else
int FCmpBSTR (LPCSTR pFeat1, LPCSTR pFeat2);
DefineCmpForTree(CFeatClsTree, FCmpBSTR, LPCSTR);			// defines CFeatClsTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<LPCSTR, CGeoFeatureBase *, CFeatClsTreeCmp> CFeatClsTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoFeatureEnumFunc)(CGeoFeatureBase &, void *);
  
class CFeatClsTree : 
	public CFeatClsTreeBase 
{
private:
	CClass *m_pCls;
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pFeat);

public:
// Konstruktor/Destruktor
		 CFeatClsTree (void);
		~CFeatClsTree (void);

static CFeatClsTree *CreateInstance (CTriasApp *pApp, 
									 CGeoDoc *pDoc, 
									 CClass *pCls);

	bool FInit (CTriasApp *pApp, 
				CGeoDoc *pDoc, 
				CClass *pCls);

// Elementarfunktionen
	CGeoFeatureBase *FAddItem (LPCSTR bName, DGeoFeature **ppIFeat, FEATUREMODE rgMode);	// Element hinzufügen
	bool FAddItem (CGeoFeatureBase *pFeat);			// Element hinzufügen
	bool FDeleteItem (LPCSTR rKT);					// Element löschen
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
friend LPCSTR FCTTreeGetClsFeatBSTR (CGeoFeatureBase *pFeat);
friend int FCTTreeCmpClsFeatBSTR (LPCSTR pFeat1, LPCSTR pFeat2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CFeatClsTree, CGeoFeatureBase2);

#endif // _FTCLTREE_HXX

