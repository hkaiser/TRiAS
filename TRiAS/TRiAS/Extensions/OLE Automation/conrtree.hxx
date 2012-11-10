// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File: CONRTREE.HXX

#if !defined(_CONRTREE_HXX)
#define _CONRTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoObject;
typedef CGeoObject CGeoObject1;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CONrTreeBase;
typedef CTable CONrTreeTable;
typedef CSyncThread CONrTreeSync;
typedef CLock CGeoObject1Lock;
#else
int FCmpLONG (const LONG &Obj1, const LONG &Obj2);
DefineCmpForTree(CONrTree, FCmpLONG, LONG);			// defines CONrTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<LONG, CGeoObject *, CONrTreeCmp> CONrTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoObjectEnumFunc)(CGeoObject &, void *);
  
class CONrTree : 
	public CONrTreeBase 
{
private:
	CGeoDoc   *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CONrTree (CTriasApp *pApp, CGeoDoc *pDoc);
		~CONrTree (void);

// Elementarfunktionen
	CGeoObject *FAddItem (LONG lONr, DGeoObject **ppIObj, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvCls = NULL);	// Element hinzufügen
	bool FAddItem (CGeoObject *pObj);	// Element hinzufügen

	bool FDeleteItem (const LONG &);		// Element löschen
	CGeoObject *FFindItem (const LONG &);	// Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (const LONG &oldKey, LONG &newKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CGeoObjectEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (LONG &rKey, CGeoObjectEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend LONG *FCTTreeGetObjLONG (CGeoObject *pObj);
friend int FCTTreeCmpObjLONG (LONG *pObj1, LONG *pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CONrTree, CGeoObject1);

#endif // _CONRTREE_HXX

