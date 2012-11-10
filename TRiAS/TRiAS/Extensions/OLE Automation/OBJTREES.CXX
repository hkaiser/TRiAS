// GeoObject Trees -----------------------------------------------
// File: OBJTREES.CXX

#include "precomp.hxx"

#include "obj.hxx"

#include "conrtree.hxx"
#include "conrtree.inl"

#include "conmtree.hxx"
#include "conmtree.inl"

#include "objtrees.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

#if defined(USE_DLIB)
const char *GetGeoObjectModeText (GEOOBJECTMODE rgMode)
{
static const char *cbGeoObjectMode[] = {
		"GEOOBJECTMODE_Get",
		"GEOOBJECTMODE_Replace", 
		"GEOOBJECTMODE_Add", 
		"GEOOBJECTMODE_Remove", 
	};
	_ASSERTE(rgMode >= GEOOBJECTMODE_Get || rgMode <= GEOOBJECTMODE_Remove);
	return cbGeoObjectMode[rgMode];
}
#endif // defined(USE_DLIB)

// constructor/destructor/initialisation --------------------------------------
CObjTrees *CObjTrees::CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc)
{
CObjTrees *pTr = new CObjTrees();

	if (pTr == NULL || !pTr -> FInit (pApp, pDoc)) {
		DELETE_OBJ (pTr);
		return NULL;
	}
	return pTr;
}

bool CObjTrees::FInit (CTriasApp *pApp, CGeoDoc *pDoc)
{
	COM_TRY {
		m_pONrTree = new CONrTree (pApp, pDoc);
		m_pObjNameTree = new CObjNameTree (pApp, pDoc);
	} COM_CATCH_IGNORE;
	
	return (m_pONrTree != NULL && m_pObjNameTree != NULL);
}

CObjTrees::CObjTrees (void) :
	m_Cache(*this, OBJECTTREES_CACHE_SIZE)
{
	CONSTRUCT_TRACE(CObjTrees);
	
	m_pONrTree = NULL;
	m_pObjNameTree = NULL;
}               

CObjTrees::~CObjTrees (void)
{
	DESTRUCT_TRACE(CObjTrees);
	
	DELETE_OBJ(m_pONrTree);
	DELETE_OBJ(m_pObjNameTree);
}

// get IDispatch of CGeoObject ------------------------------------------------
CGeoObject *CObjTrees::FGetItem (INT_PTR lONr, DGeoObject **ppIObj)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pONrTree -> FFindItem (lONr);	

	if (NULL == pObj) return NULL;

	m_Cache.CacheHit(lONr);		// Cache informieren
	if (ppIObj == NULL || SUCCEEDED(((DGeoObject *)pObj) -> QueryInterface (IID_DGeoObject, (LPVOID *)ppIObj)))
		return pObj;

	return NULL;
}

CGeoObject *CObjTrees::FGetItem (LPCSTR bName, DGeoObject **ppIObj)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pObjNameTree -> FFindItem (bName);	

	if (NULL == pObj) return NULL;

	m_Cache.CacheHit(pObj -> GetValue());		// Cache informieren
	if (ppIObj == NULL || SUCCEEDED(((DGeoObject *)pObj) -> QueryInterface (IID_DGeoObject, (LPVOID *)ppIObj)))
		return pObj;

	return NULL;	
}

// Remove from trees ----------------------------------------------------------
bool CObjTrees::FDeleteItem (INT_PTR lONr)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pONrTree -> FFindItem (lONr);	

	if (pObj == NULL) {
		if (INVALID_ONR == lONr) {
			ASSERT(INVALID_ONR != lONr);
			return false;
		}
		D_OUTF1(2, "CObjTrees::FDeleteItemONr (%ld): removing directly.", lONr);
		return DEX_DeleteObject (lONr);
	}
	
LPCSTR bName = pObj -> FGetBSTR();

	D_OUTF2(2, 
		"CObjTrees::FDeleteItemONr (%s/", bName,
		"%ld): removing.", lONr);
	m_Cache.RemoveItem(pObj -> GetValue());
	pObj -> Remove();	// remove physically

bool fResultName = m_pObjNameTree -> FDeleteItem (bName, lONr);
bool fResultONr = m_pONrTree -> FDeleteItem (lONr);

	return fResultName && fResultONr;
}

bool CObjTrees::FDeleteItem (LPCSTR bName)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pObjNameTree -> FFindItem (bName);	

	if (pObj == NULL) {
	long lONr = DEX_GetONrFromObjName (bName);
	
		if (lONr != INVALID_ONR) {
			D_OUTF2(2, 
				"CObjTrees::FDeleteItem (%s/", bName,
				"%ld): removing directly.", lONr);
			return DEX_DeleteObject (lONr);
		}
		return false;
	}
	

LONG lONr = pObj -> FGetLONG();

	D_OUTF2(2, 
		"CObjTrees::FDeleteItem (%s/", bName,
		"%ld): removing.", lONr);
	m_Cache.RemoveItem(pObj -> GetValue());
	pObj -> Remove();	// remove physically
	
bool fResultName = m_pObjNameTree -> FDeleteItem (bName, lONr);
bool fResultONr = m_pONrTree -> FDeleteItem (lONr);

	return fResultName && fResultONr;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt aus den Bümen herauslösen
bool CObjTrees::ReleaseItem (INT_PTR lONr)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pONrTree -> FFindItem (lONr);	

//	_ASSERTE(NULL != pObj);
	if (NULL == pObj) 
		return false;
	
LPCSTR bName = pObj -> FGetBSTR();

	D_OUTF2(2, 
		"CObjTrees::ReleaseItem (%s/", bName,
		"%ld): releasing from cache.", lONr);

bool fResultName = m_pObjNameTree -> FDeleteItem (bName, lONr);
bool fResultONr = m_pONrTree -> FDeleteItem (lONr);

	return fResultName && fResultONr;
}

///////////////////////////////////////////////////////////////////////////////
// remove from tree's only 
bool CObjTrees::FInvalidateItem (INT_PTR lONr)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pONrTree -> FFindItem (lONr);	

	if (pObj == NULL) return true;

LPCSTR bName = pObj -> FGetBSTR();

	pObj -> Invalidate();	// invalidate GeoObject-object

bool fResultName = m_pObjNameTree -> FDeleteItem (bName, lONr);
bool fResultONr = m_pONrTree -> FDeleteItem (lONr);

	return fResultName && fResultONr;
}

// Get, OptCreate, Create, Remove item to/from tree 
CGeoObject *CObjTrees::FAddItem (INT_PTR lONr, DGeoObject **ppIObj, GEOOBJECTMODE rgMode, VARIANT *pvClass)
{
CObjTreesSync Sync (this);
CGeoObject *pObj = NULL;

	if (NULL != (pObj = FGetItem (lONr, ppIObj))) {
		D_OUTF3(2, 
			"CObjTrees::FAddItemONr (%s/", pObj -> GetName(),
			"%ld): ", pObj -> GetValue(),
			"%s: exists.", GetGeoObjectModeText(rgMode));
		return pObj;
	}

// add to 1st tree
	if (NULL == (pObj = m_pONrTree -> FAddItem (lONr, ppIObj, rgMode, pvClass)))
		return NULL;	// error

// find bName of Object lONr
	pObj -> GetName();	// trick 17	HK

// add to 2nd tree
	if (!m_pObjNameTree -> FAddItem (pObj)) 
		return NULL;

	D_OUTF3(2, 
		"CObjTrees::FAddItemONr (%s/", pObj -> GetName(),
		"%ld): ", pObj -> GetValue(),
		"%s: created.", GetGeoObjectModeText(rgMode));

	m_Cache.CacheHit(lONr);
	return pObj;
}

CGeoObject *CObjTrees::FAddItem (BSTR bName, DGeoObject **ppIObj, GEOOBJECTMODE rgMode, VARIANT *pvClass)
{
GUID guid;
HRESULT hr = E_FAIL;
UINT uiLen = SysStringLen(bName);

	if (GEOOBJECTMODE_Add == rgMode && 0 == uiLen)		// kein Objektname, also neuen Guid verwenden
		hr = CoCreateGuid(&guid);
	else if (uiLen+1 == GUID_CCH && L'{' == *bName)		// bName enthält evtl. Guid
		hr = CLSIDFromString (bName, &guid);

	if (SUCCEEDED(hr)) {
	// wenns ein Guid ist, dann über Objektnummer holen
	OBJECTGUID OUID;

		INITSTRUCT (OUID, OBJECTGUID);
		OUID.guid = guid;
		if (SUCCEEDED(DEX_FindObjectFromGuid(OUID))) 
			return FAddItem (OUID.lONr, ppIObj, rgMode, pvClass);
		else if (GEOOBJECTMODE_Add == rgMode)
			return FAddItem (INVALID_ONR, ppIObj, GEOOBJECTMODE_Add, pvClass);
	}

	USES_CONVERSION;

CObjTreesSync Sync (this);
CGeoObject *pObj = NULL;
LPCSTR pcName = OLE2A(bName);

	if (NULL != (pObj = FGetItem (pcName, ppIObj))) {
		D_OUTF3(2, 
			"CObjTrees::FAddItem (%s/", pcName,
			"%ld): ", pObj -> GetValue(),
			"%s: exists.", GetGeoObjectModeText(rgMode));
		if (GEOOBJECTMODE_Get == rgMode) 
			return pObj;		// nur, wenn Objekt nicht neu erzeugt werden soll
		return NULL;
	}
		
// add to 1st tree
	if (NULL == (pObj = m_pObjNameTree -> FAddItem (pcName, ppIObj, rgMode, pvClass)))
		return NULL;	// error

// wenn ein neues Objekt erzeugt werden soll, dann wird das neue Objekt u.U. über eine
// Notifikation in die Bäume reingebaut (von hinten). 
	TX_ASSERT(rgMode == GEOOBJECTMODE_Add || NULL == m_pONrTree -> FFindItem (pObj -> GetValue()));

// add to 2nd tree
	if (rgMode == GEOOBJECTMODE_Add) {
		if (NULL == m_pONrTree -> FFindItem(pObj -> GetValue()) && !m_pONrTree -> FAddItem (pObj)) {
			m_pObjNameTree -> FDeleteItem(pcName, pObj -> GetValue());
//			delete pObj;
			return NULL;
		}
	}

	D_OUTF3(2, 
		"CObjTrees::FAddItem (%s/", pcName,
		"%ld): ", pObj -> GetValue(),
		"%s: created.", GetGeoObjectModeText(rgMode));

	m_Cache.CacheHit(pObj -> GetValue());
	return pObj;
}

ULONG CObjTrees::ChangeObjectIdent (INT_PTR lONr, ULONG lNewIdent, bool fIsNotification)
{
	_ASSERTE(0 != lNewIdent || fIsNotification);
	
CObjTreesSync Sync (this);
CGeoObject *pObj = m_pONrTree -> FFindItem (lONr);	

	if (pObj) {
		m_Cache.CacheHit(lONr);
		return pObj -> ChangeObjIdent (lNewIdent, fIsNotification);
	}
	return INVALID_IDENT;
}

bool CObjTrees::SetObjectName (INT_PTR lONr, LPCSTR bNewName) 
{
CObjTreesSync Sync (this);
CGeoObject *pObj = FGetItem (lONr);

	if (pObj == NULL) return false;
	
LPCSTR bName = pObj -> GetName();

	if (!strcmp (bName, bNewName)) return true;
	
	if (m_pObjNameTree -> FDeleteItem (bName, lONr)) {
		if (!pObj -> SetName (bNewName, true, true))
			return false;
		pObj -> Validate();
		if (m_pObjNameTree -> FAddItem (pObj)) {
			((_DGeoObject *)pObj) -> AddRef();
			return true; 
		}
	}
	return false;
}

LONG CObjTrees::GetONrFromObjName (LPCSTR bName)	// find lONr
{
CObjTreesSync Sync (this);
CGeoObject *pObj = FGetItem (bName);

	if (pObj == NULL) {
	long lONr = DEX_GetONrFromObjName (bName);
	
		if (lONr == INVALID_ONR) return INVALID_ONR;
	
	// add to 1st tree
		if ((pObj = m_pONrTree -> FAddItem (lONr, NULL, GEOOBJECTMODE_Get)) == NULL)
			return INVALID_ONR;	// error
		pObj -> SetName (bName);
	// add to 2nd tree
		if (!m_pObjNameTree -> FAddItem (pObj)) 
			return INVALID_ONR;
	}
	return pObj -> GetValue();
}

