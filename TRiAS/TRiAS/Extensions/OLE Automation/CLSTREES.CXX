// GeoClasses Trees -----------------------------------------------
// File: CLSTREES.CXX

#include "precomp.hxx"

#include "class.hxx"

#include "clidtree.hxx"
#include "clidtree.inl"

#include "clnmtree.hxx"
#include "clnmtree.inl"

#include "clstrees.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// constructor/destructor/initialisation --------------------------------------

CClsTrees *CClsTrees::CreateInstance (CTriasApp *pApp, CGeoDoc *pDoc)
{
CClsTrees *pTr = NULL;

	ATLTRY(pTr = new CClsTrees());
	if (pTr == NULL || !pTr -> FInit (pApp, pDoc)) {
		DELETE_OBJ (pTr);
		return NULL;
	}
	return pTr;
}

bool CClsTrees::FInit (CTriasApp *pApp, CGeoDoc *pDoc)
{
	COM_TRY {
		m_pIDTree = new CIDTree (pApp, pDoc);
		m_pClsNameTree = new CClsNameTree (pApp, pDoc);
	} COM_CATCH_IGNORE;

	return (m_pIDTree != NULL && m_pClsNameTree != NULL);
}

CClsTrees::CClsTrees (void)                       
{
	CONSTRUCT_TRACE(CClsTrees);

	m_pIDTree = NULL;
	m_pClsNameTree = NULL;
}               

CClsTrees::~CClsTrees (void)
{
	DESTRUCT_TRACE(CClsTrees);

	DELETE_OBJ(m_pIDTree);
	DELETE_OBJ(m_pClsNameTree);
}

// get IDispatch of CClass ------------------------------------------------
CClass *CClsTrees::FGetItem (ULONG lIdent, DGeoClass **ppICls)
{
CClsTreesSync Sync (this);
CClass *pCls = m_pIDTree -> FFindItem (lIdent);	

	if (NULL == pCls) 
		return NULL;
	if (NULL == ppICls || SUCCEEDED(((DGeoClass *)pCls) -> QueryInterface (IID_DGeoClass, (LPVOID *)ppICls)))
	{
		return pCls;
	}
	return NULL;
}

CClass *CClsTrees::FGetItem (LPCSTR bName, LPCSTR pcSrc, DGeoClass **ppICls)
{
CClsTreesSync Sync (this);
CClass *pCls = NULL;
char cbBufferSrc[_MAX_PATH];
HPROJECT hPrCtx = HACTCONNECTION;

	if (NULL == pcSrc || '\0' == pcSrc[0]) {
	// ZielDatenquelle ist nicht gegeben
		hPrCtx = m_pIDTree -> GetDoc() -> GetCtxDataSource();
		_ASSERTE(HACTCONNECTION != hPrCtx);
		DEX_GetDataSourceShortName (hPrCtx, cbBufferSrc);
	} else {
		strcpy (cbBufferSrc, pcSrc);
		hPrCtx = DEX_GetDataSourceHandleFromShortName(cbBufferSrc);
		_ASSERTE(HACTCONNECTION != hPrCtx);
	}

// wenn Objektklasse über OKS gesucht wird, dann direkt vorgehen
	if (!strncmp(bName, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN)) {
	ULONG lIdent = 0;
	HRESULT hr = IdentFromClassX (hPrCtx, bName, &lIdent);

		if (S_OK != hr)
			return NULL;	// existiert nicht
		return FGetItem(lIdent, ppICls);
	}

// Objektklasse wird über Kurztext gesucht
	if ('\0' != cbBufferSrc[0]) {
	CClsNameTreeTable t(*m_pClsNameTree);

		for (t.FindFirst ((LPVOID)bName); t.Valid(); t.FindNext ((LPVOID)bName)) {
		CClass2Lock l(t);

			if (!l) continue;

		HPROJECT hPr = DEX_GetObjectsProject(l -> GetValue());
		char cbBuffer[_MAX_PATH];

			if (DEX_GetDataSourceShortName (hPr, cbBuffer) && !strcmp (cbBufferSrc, cbBuffer)) {
				pCls = l;	// gefunden
				break;
			}
		}
	} else {
	// keine DatenQuelle gegeben, den Erstbesten nehmen
		pCls = m_pClsNameTree -> FFindItem (bName);	
	}

	if (NULL == pCls) 
		return NULL;

	if (ppICls == NULL || SUCCEEDED(((DGeoClass *)pCls) -> QueryInterface (IID_DGeoClass, (LPVOID *)ppICls)))
		return pCls;

	return NULL;	
}

// Remove from trees ----------------------------------------------------------
bool CClsTrees::FDeleteItem (ULONG lIdent)
{
CClsTreesSync Sync (this);
CClass *pCls = m_pIDTree -> FFindItem (lIdent);	

	if (pCls == NULL) 
		return DEX_DeleteAllIdentObjects (lIdent);
	
LPCSTR bName = pCls -> FGetBSTR();

	pCls -> Remove();	// remove physically
	
bool fResultName = m_pClsNameTree -> FDeleteItem (bName);
bool fResultIdent = m_pIDTree -> FDeleteItem (lIdent);

	return fResultName && fResultIdent;
}


bool CClsTrees::FDeleteItem (LPCSTR bName, LPCSTR pcSrc)
{
CClsTreesSync Sync (this);
CClass *pCls = FGetItem (bName, pcSrc);
ULONG lIdent = INVALID_IDENT;
HPROJECT hPrDest = HACTCONNECTION;

	if (NULL != pcSrc && '\0' != pcSrc[0])
		hPrDest = DEX_GetDataSourceHandleFromShortName (pcSrc);
	if (HACTCONNECTION == hPrDest)
		hPrDest = m_pIDTree -> GetDoc() -> GetCtxDataSource();

	if (NULL == pCls) {
		lIdent = DEX_GetIdentFromClassNameEx (hPrDest, bName); 
		if (lIdent != INVALID_IDENT) 
			return DEX_DeleteAllIdentObjects (lIdent);
		return false;
	}
	
	lIdent = pCls -> FGetULONG();
	pCls -> Remove();	// remove physically
	
bool fResultName = m_pClsNameTree -> FDeleteItem (bName);
bool fResultIdent = m_pIDTree -> FDeleteItem (lIdent);

	return fResultName && fResultIdent;
}


bool CClsTrees::FInvalidateItem (ULONG lIdent)
{
CClsTreesSync Sync (this);
CClass *pCls = m_pIDTree -> FFindItem (lIdent);	

	if (pCls == NULL) return true;
	
LPCSTR bName = pCls -> FGetBSTR();

	pCls -> Invalidate();	// invalidate and remove from trees
	
bool fResultName = m_pClsNameTree -> FDeleteItem (bName);
bool fResultIdent = m_pIDTree -> FDeleteItem (lIdent);

	return fResultName && fResultIdent;
}


// Get, OptCreate, Create, Remove item to/from tree 
CClass *CClsTrees::FAddItem (ULONG lIdent, DGeoClass **ppICls, GEOCLASSMODE rgMode, LPCSTR pcSrc)
{
CClsTreesSync Sync (this);
CClass *pCls = NULL;

	if (pCls = FGetItem (lIdent, ppICls)) return pCls;
		
// add to 1st tree
	if ((pCls = m_pIDTree -> FAddItem (lIdent, ppICls, rgMode, pcSrc)) == NULL)
		return NULL;	// error

// find bName of Class lIdent
	pCls -> GetName();	// trick 17

// add to 2nd tree
	if (!m_pClsNameTree -> FAddItem (pCls)) 
		return NULL;

	return pCls;
}

CClass *CClsTrees::FAddItem (LPCSTR bName, DGeoClass **ppICls, GEOCLASSMODE rgMode, LPCSTR pcSrc)
{
CClsTreesSync Sync (this);
CClass *pCls = NULL;

	if (pCls = FGetItem (bName, pcSrc, ppICls)) 
		return pCls;
		
// add to 1st tree
	if ((pCls = m_pClsNameTree -> FAddItem (bName, ppICls, rgMode, pcSrc)) == NULL)
		return NULL;	// error

// add to 2nd tree
	if (!m_pIDTree -> FAddItem (pCls)) 
		return NULL;

	return pCls;	
}


bool CClsTrees::SetClassName (ULONG lIdent, LPCSTR bNewName) 
{
CClsTreesSync Sync (this);
CClass *pCls = FGetItem (lIdent);

	if (pCls == NULL) return false;
	
LPCSTR bName = pCls -> GetName();

	if (!strcmp (bName, bNewName)) return true;
	
	if (m_pClsNameTree -> FDeleteItem (bName)) {
		if (!pCls -> SetName (bNewName, true, true))
			return false;
		pCls -> Validate();

		if (m_pClsNameTree -> FAddItem (pCls)) {
			((_DGeoClass *)pCls) -> AddRef();
			return true;
		}
	}
	return false;
}

ULONG CClsTrees::GetIdentFromClsName (LPCSTR bName, LPCSTR pcSrc)	// find lIdent
{
CClsTreesSync Sync (this);
CClass *pCls = FGetItem (bName, pcSrc);

	if (pCls == NULL) {
	HPROJECT hPr = HACTCONNECTION;

		if (NULL != pcSrc && '\0' != pcSrc[0])
			hPr = DEX_GetDataSourceHandleFromShortName (pcSrc);

	long lIdent = DEX_GetIdentFromClassNameEx (hPr, bName);
	
		if (lIdent == INVALID_IDENT) return INVALID_IDENT;
	
	// add to 1st tree
		if ((pCls = m_pIDTree -> FAddItem (lIdent, NULL, GEOCLASSMODE_Get)) == NULL)
			return INVALID_IDENT;	// error
		pCls -> SetName (bName);
	
	// add to 2nd tree
		if (!m_pClsNameTree -> FAddItem (pCls)) 
			return INVALID_IDENT;
	}
	return pCls -> GetValue();
}

