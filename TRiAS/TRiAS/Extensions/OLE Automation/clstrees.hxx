// GeoClasses Trees -----------------------------------------------
// File: CLSTREES.HXX

#if !defined(_CLSTREES_HXX)
#define _CLSTREES_HXX

class CIDTree;
class CClsNameTree;
class CClass;

#include "clidtree.hxx"	

#if defined(_USE_CLASSIC_CONTAINERS)
typedef CSyncMonitor CClsTreesSyncMonitor;
#else
typedef class {} CClsTreesSyncMonitor;
typedef container_wrappers::CSyncThreadOnStl<CIDTree> CClsTreesSync;
#endif // defined(_USE_CLASSIC_CONTAINERS)

class CClsTrees : 
	public CClsTreesSyncMonitor 
{
private:
	CIDTree *m_pIDTree;
	CClsNameTree *m_pClsNameTree;
	
#if !defined(_USE_CLASSIC_CONTAINERS)
public:
	CIDTree::guard_t Guard() { return m_pIDTree -> Guard(); }
#endif // !defined(_USE_CLASSIC_CONTAINERS)

public:
		 CClsTrees (void);
		~CClsTrees (void);
	
static CClsTrees *CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc);

	bool FInit (CTriasApp *pApp, CGeoDoc *pDoc);
	
	CClass *FGetItem (ULONG lIdent, DGeoClass **ppICls = NULL);
	CClass *FGetItem (LPCSTR bName, LPCSTR pcSrc = NULL, DGeoClass **ppICls = NULL);

	CClass *FAddItem (ULONG lIdent, DGeoClass **ppICls, GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL);
	CClass *FAddItem (LPCSTR bName, DGeoClass **ppICls, GEOCLASSMODE rgMode = GEOCLASSMODE_Get, LPCSTR pcSrc = NULL);
	
	bool FDeleteItem (ULONG lIdent);
	bool FDeleteItem (LPCSTR bName, LPCSTR pcSrc = NULL);
	bool FInvalidateItem (ULONG lIdent);

	bool SetClassName (ULONG lIdent, LPCSTR bNewName); 

	ULONG GetIdentFromClsName (LPCSTR bName, LPCSTR pcSrc = NULL);	// find Ident
};

#endif // _CLSTREES_HXX

