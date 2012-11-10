// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File: FTVWTREE.HXX

#if !defined(_FTVWTREE_HXX)
#define _FTVWTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoFeatureBase;
typedef CGeoFeatureBase CGeoFeatureBase1;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CFeatViewTreeBase;
typedef CTable CFeatViewTreeTable;
typedef CSyncThread CFeatViewTreeSync;
typedef CLock CGeoFeatureBase1Lock;
#else
int FCmpBSTR (LPCSTR pFeat1, LPCSTR pFeat2);
DefineCmpForTree(CFeatViewTree, FCmpBSTR, LPCSTR);			// defines CFeatViewTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<LPCSTR, CGeoFeatureBase *, CFeatViewTreeCmp> CFeatViewTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoFeatureEnumFunc)(CGeoFeatureBase &, void *);
  
class CFeatViewTree : 
	public CFeatViewTreeBase 
{
private:
	CGeoView *m_pView;
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pFeat);

public:
// Konstruktor/Destruktor
		 CFeatViewTree (void);
		~CFeatViewTree (void);

static CFeatViewTree *CreateInstance (CTriasApp *pApp, 
									  CGeoDoc *pDoc, 
									  CGeoView *pView);

	bool FInit (CTriasApp *pApp, 
				CGeoDoc *pDoc, 
				CGeoView *pView);

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
friend LPCSTR FCTTreeGetViewFeatBSTR (CGeoFeatureBase *pFeat);
friend int FCTTreeCmpViewFeatBSTR (LPCSTR pFeat1, LPCSTR pFeat2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CFeatViewTree, CGeoFeatureBase1);

#endif // _FTVWTREE_HXX

