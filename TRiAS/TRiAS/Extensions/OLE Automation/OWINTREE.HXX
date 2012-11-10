// GeoObjWin Tree -------------------------------------------------------------
// File: OWINTREE.HXX

#if !defined(_OBJWINTREE_HXX)
#define _OBJWINTREE_HXX

// Eigentliche typspezifische TreeKlasse --------------------------------------
class CGeoObjectWin;
typedef CGeoObjectWin CGeoObjectWin2;

#if defined(_USE_CLASSIC_CONTAINERS)
typedef COptTree CObjWinTreeBase;
typedef CTable CObjWinTreeTable;
typedef CSyncThread CObjWinTreeSync;
typedef CLock CGeoObjectWin2Lock;
#else
int FCmpHWND (const HWND &ObjWin1, const HWND &ObjWin2);
DefineCmpForTree(CObjWinTree, FCmpHWND, HWND);			// defines CObjWinTreeCmp
typedef container_wrappers::CUniqueTreeOnStl<HWND, CGeoObjectWin *, CObjWinTreeCmp> CObjWinTreeBase; 
#endif // !defined(_USE_CLASSIC_CONTAINERS)

// Funktionstypen, die Schlüsselverwaltung realisieren ------------------------
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);
  
typedef bool (* CGeoObjectWinEnumFunc)(CGeoObjectWin &, void *);
  
class CObjWinTree : 
	public CObjWinTreeBase 
{
private:
	CGeoDoc   *m_pDoc;
	CTriasApp *m_pApp;

	bool m_fCreating;		// Rekursion verhindern

protected:
	void UserDelete (void *pObjWin);

public:
		 CObjWinTree (void);
		~CObjWinTree (void);
	
static CObjWinTree *CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc);

	bool FInit (CTriasApp *pApp, CGeoDoc *pDoc);
	
	CGeoObjectWin *FAddItem (HWND hWnd, DGeoObjectWin **ppIWin = NULL, GEOOBJWINMODE rgMode = GEOOBJWINMODE_Get);
	CGeoObjectWin *FAddItem (LPCSTR bName, DGeoObjectWin **ppIWin = NULL, GEOOBJWINMODE rgMode = GEOOBJWINMODE_Get);

	bool FAddItem (CGeoObjectWin *pObjWin);	// Element hinzufügen

	bool FDeleteItem (HWND &);
    bool FInvalidateItem (HWND &);

	CGeoObjectWin *FFindItem (HWND &);	// Element liefern
	CGeoObjectWin *FFindItem (LPCSTR pcName);

	bool SetObjWinName (HWND hWnd, LPCSTR bNewName);
	HWND GethWndFromObjWinName (LPCSTR bName);

#if defined(_USE_UNSAFE_REINSERT)	
	bool FReInsert (HWND &roldKey, HWND &rnewKey);
#endif // defined(_USE_UNSAFE_REINSERT)

// EnumerationsFunktionen
	bool FEnumAllItems (CGeoObjectWinEnumFunc pFcn, void *pEData = NULL);
	bool FEnumItems (HWND &rKey, CGeoObjectWinEnumFunc pFcn, void *pEData = NULL);

// SuchSchlüsselVerwaltung
friend HWND *FCTTreeGetObjWinHWND (CGeoObjectWin *pObjWin);
friend int   FCTTreeCmpObjWinHWND (HWND *pObjWin1, HWND *pObjWin2);
};

// KlassenDeklarationen/Definitionen für TypLock und TypCreator
DeclareOptLockStl (CObjWinTree, CGeoObjectWin2);

#endif // _OBJWINTREE_HXX

