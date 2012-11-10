// Klassendeklaration der typspezifischen TreeKlasse --------------------------
// File: CONMTREE.HXX

#if !defined(_CONMTREE_HXX)
#define _CONMTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoObject;
typedef CGeoObject CGeoObject2;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CObjNameTreeBase;
typedef CTable CObjNameTreeTable;
typedef CSyncThread CObjNameTreeSync;
typedef CLock CGeoObject2Lock;
#else
int FCmpBSTR (LPCSTR pObj1, LPCSTR pObj2);
DefineCmpForTree(CObjNameTree, FCmpBSTR, LPCSTR);			// defines CObjNameTreeCmp
typedef container_wrappers::CTreeOnStl<LPCSTR, CGeoObject *, CObjNameTreeCmp> CObjNameTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)


// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoObjectEnumFunc)(CGeoObject &, void *);
  
class CObjNameTree : 
	public CObjNameTreeBase 
{
private:
	CGeoDoc *m_pDoc;
	CTriasApp *m_pApp;
	
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CObjNameTree (CTriasApp *pApp, CGeoDoc *pDoc);
		~CObjNameTree (void);

// Elementarfunktionen
	CGeoObject *FAddItem (LPCSTR bName, DGeoObject **ppIObj, GEOOBJECTMODE rgMode, VARIANT *pvCls);	// Element hinzufügen
	bool FAddItem (CGeoObject *);							 // Element hinzufügen
	bool FDeleteItem (LPCSTR, LONG lONr = INVALID_ONR);		 // Element löschen
	CGeoObject *FFindItem (LPCSTR, LONG lONr = INVALID_ONR); // Element liefern

#if defined(_USE_UNSAFE_REINSERT)
	bool FReInsert (LPCSTR oldKey, LPCSTR newKey, LONG lONr = INVALID_ONR);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CGeoObjectEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (LPCSTR rKey, CGeoObjectEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend LPCSTR FCTTreeGetObjBSTR (CGeoObject *pObj);
friend int FCTTreeCmpObjBSTR (LPCSTR pObj1, LPCSTR pObj2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CObjNameTree, CGeoObject2);

#endif // _CONMTREE_HXX

