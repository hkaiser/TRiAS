// GeoObject Trees -----------------------------------------------
// File: OBJTREES.HXX

#if !defined(_OBJTREES_HXX)
#define _OBJTREES_HXX

class CONrTree;
class CObjNameTree;
class CGeoObject;
 
#include "conrtree.hxx"	
#include "conmtree.hxx"

#include "ObjTreesCache.h"

///////////////////////////////////////////////////////////////////////////////
// Größe des Caches
const int OBJECTTREES_CACHE_SIZE = 1024;

///////////////////////////////////////////////////////////////////////////////
// 
#if defined(_USE_CLASSIC_CONTAINERS)
typedef CSyncMonitor CObjTreesSync;
#else
typedef class {} CObjTreesSyncMonitor;
typedef container_wrappers::CSyncThreadOnStl<CONrTree> CObjTreesSync;
#endif // defined(_USE_CLASSIC_CONTAINERS)

class CObjTrees : 
	public CObjTreesSyncMonitor 
{
private:
	CONrTree *m_pONrTree;
	CObjNameTree *m_pObjNameTree;
	CObjTreesCache m_Cache;

#if !defined(_USE_CLASSIC_CONTAINERS)
public:
	CONrTree::guard_t Guard() { return m_pONrTree -> Guard(); }
#endif // !defined(_USE_CLASSIC_CONTAINERS)

public:
		CObjTrees (void);
		~CObjTrees (void);
	
static CObjTrees *CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc);

	bool FInit (CTriasApp *pApp, CGeoDoc *pDoc);
	
	CGeoObject *FGetItem (INT_PTR lONr, DGeoObject **ppIObj = NULL);
	CGeoObject *FGetItem (LPCSTR bName, DGeoObject **ppIObj = NULL);

	CGeoObject *FAddItem (INT_PTR lONr, DGeoObject **ppIObj = NULL, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvCls = NULL);
	CGeoObject *FAddItem (BSTR bName, DGeoObject **ppIObj = NULL, GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get, VARIANT *pvCls = NULL);
	
	bool FDeleteItem (INT_PTR lONr);
	bool FDeleteItem (LPCSTR bName);
	bool FInvalidateItem (INT_PTR lONr);

	bool ReleaseItem (INT_PTR lONr);
	
	ULONG ChangeObjectIdent (INT_PTR lONr, ULONG lNewIdent, bool fIsNotification = false);
	
	bool SetObjectName (INT_PTR lONr, LPCSTR bNewName);

	LONG GetONrFromObjName (LPCSTR bName);	// find lONr
};

#endif // _OBJTREES_HXX
