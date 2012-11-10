// Enumerator der ObjektProperties einer Erweiterung --------------------------
// File ENUMPROP.CXX

#include "xtensnp.hxx"

#include "enumprop.hxx"
#include <xtsnguid.h>

#include "synccook.h"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

static char cbBuffer[512];

// Eine Objekteigenschaft -----------------------------------------------------
CObjProp *CObjProp :: CreateInstance (ULONG uiID, LPOBJECTPROPERTY pIObjProp)
{
CObjProp *pOP = new CObjProp();

	if (NULL == pOP || !pOP -> FInit (uiID, pIObjProp)) {
		DELETE_OBJ (pOP);
		return NULL;
	}

return pOP;
}

bool CObjProp :: FInit (ULONG uiID, LPOBJECTPROPERTY pIObjProp)
{
	if (SUCCEEDED(pIObjProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL))) {
		m_strName = cbBuffer;
		m_ulID = uiID;
		m_pIObjProp = pIObjProp;
//		m_pIObjProp -> AddRef();	// already done
		return true;
	}

return false;
}

CObjProp :: CObjProp (void)
{
	m_ulID = 0L;
	m_pIObjProp = NULL;
}


CObjProp :: ~CObjProp (void)
{
	if (m_pIObjProp) m_pIObjProp -> Release();
}

CObjProp :: CObjProp (CObjProp &rOProp)
{
	m_ulID = rOProp.m_ulID;
	m_strName = rOProp.m_strName;
	m_pIObjProp = rOProp.m_pIObjProp;
	if (m_pIObjProp) m_pIObjProp -> AddRef();
}

void *GetPropName (void *pObj)
{
	return & (((CObjProp *)pObj) -> m_strName);
}

void *GetPropID (void *pObj)
{
	return & (((CObjProp *)pObj) -> m_ulID);
}

int StringCmp (void *p1, void *p2)
{
string *pStr1 = (string *)p1;
string *pStr2 = (string *)p2;

	return strcmp (pStr1 -> c_str(), pStr2 -> c_str());
}

int ULongCmp (void *p1, void *p2)
{
ULONG *pUL1 = (ULONG *)p1;
ULONG *pUL2 = (ULONG *)p2;

	if (*pUL1 > *pUL2) return 1;
	if (*pUL1 < *pUL2) return -1;

return 0;
}

// Ein Baum, der die Objprops nach ihrem Namen sortiert -----------------------
CObjPropsName :: ~CObjPropsName (void)
{
	EveryDelete();
}

void CObjPropsName :: UserDelete (void *pObj)
{
	((CObjProp *)pObj) -> ~CObjProp();
}

CObjProp *CObjPropsName :: AddProp (ULONG uiID, LPOBJECTPROPERTY pIObjProp)
{
CObjPropCreator OPCr (*this);
CObjProp *pOP = CObjProp :: CreateInstance (uiID, pIObjProp);

	if (NULL == pOP) return NULL;

#if defined(__MFC__) && !defined(WIN32)
// das Objekt muß doppelt angelegt werden , damit die FREESTORE Speicherverwaltung 
// greifen kann
CObjProp *pRes = ContCreate (OPCr, CObjProp)(*pOP);

	DELETE_OBJ (pOP);

return pRes;
#else
return OPCr.InsertPtr (pOP);
#endif // __MFC__ && !WIN32
}

bool CObjPropsName :: FindProp (LPCSTR pName, LPOBJECTPROPERTY *ppIObjProp)
{
	_ASSERTE(NULL != ppIObjProp);

CTable t(*this);
string strKey = pName;

	*ppIObjProp = NULL;	// für alle Fälle
	if (t.Find (&strKey)) {
	CObjPropLock l(t);

		_ASSERTE(NULL != (CObjProp *)l);
		l -> GetObjProp (ppIObjProp);
		return true;
	}

return false;
}

bool CObjPropsName :: DeleteProp (LPCSTR pName)
{
CTable t(*this);
string strKey = pName;

	if (t.Find (&strKey)) 
		return t.Delete();

return false;
}

// Ein Baum der die ObjProps nach ihrem ID sortiert ---------------------------
CObjPropsID :: ~CObjPropsID (void)
{
	EveryDelete();
}

void CObjPropsID :: UserDelete (void *)
{
	// nothing to do (CDelTree)
}

bool CObjPropsID :: AddProp (CObjProp *pObjProp)
{
CObjProp1Creator OPCr (*this);

	return NULL != OPCr.InsertPtr (pObjProp) ? true : false;
}

bool CObjPropsID :: FindProp (ULONG ulID, LPOBJECTPROPERTY *ppIObjProp)
{
	_ASSERTE(NULL != ppIObjProp);

CTable t(*this);

	*ppIObjProp = NULL;	// für alle Fälle
	
	if (t.Find (&ulID)) {
	CObjPropLock l(t);

		_ASSERTE(NULL != (CObjProp *)l);
		l -> GetObjProp (ppIObjProp);
		return true;
	}

return false;
}

bool CObjPropsID :: DeleteProp (ULONG ulID)
{
CTable t(*this);

	if (t.Find (&ulID)) 
		return t.Delete();

return false;
}

// Zusammenfassen beider Bäume in einem Interface -----------------------------
DWORD CObjProps :: AddProp (ULONG uiID, LPOBJECTPROPERTY pIObjProp)
{
	pIObjProp -> AddRef();		// hold on

CObjProp *pObjProp = m_PropsName.AddProp (uiID, pIObjProp);

	if (NULL == pObjProp) {
		pIObjProp -> Release();
		return 0L;
	}

	if (!m_PropsID.AddProp (pObjProp)) {
		m_PropsName.DeleteProp (pObjProp -> GetPropName() -> c_str());
		pIObjProp -> Release();
		return 0L;
	}

	DEXN_AddedObjectProperty();
	return uiID;
}

bool CObjProps :: DeleteProp (ULONG ulID)
{
LPOBJECTPROPERTY pIObjProp = NULL;

	if (!m_PropsID.FindProp (ulID, &pIObjProp))
		return false;

bool fOK1 = m_PropsID.DeleteProp (ulID);

	pIObjProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL);

bool fOK2 = m_PropsName.DeleteProp (cbBuffer);
	
	pIObjProp -> Release();

	DEXN_RemovedObjectProperty();
	return fOK1 && fOK2;
}

// Alle ObjProps aus Doppeltbaum löschen --------------------------------------
bool CObjProps :: EveryDelete (void)
{
bool fOK1 = m_PropsID.EveryDelete();
bool fOK2 = m_PropsName.EveryDelete();

	DEXN_RemovedObjectProperty();
	return fOK1 && fOK2;
}

// Der eigentliche Enumerator der ObjektProperties ----------------------------
CEnumObjectProperties :: CEnumObjectProperties (void)
		       : m_Props(), m_tCurr(m_Props.m_PropsID)
{
	m_dwRefCnt = 0L;
	m_dwCookie = 100L;
	Reset();
}

CEnumObjectProperties :: ~CEnumObjectProperties (void)
{
}

CEnumObjectProperties *CEnumObjectProperties :: CreateInstance (void)
{
CEnumObjectProperties *pEnum = new CEnumObjectProperties();

	if (NULL == pEnum || !pEnum -> FInit()) {
		DELETE_OBJ (pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// get next cookie thread save ------------------------------------------------
DWORD CEnumObjectProperties :: GetCookie (void)
{
CSyncCookies Sync;

	return Sync.IncrementSynced (&m_dwCookie);
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CEnumObjectProperties :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumUnknown || 
	    riid == IID_IEnumObjProps)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CEnumObjectProperties :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CEnumObjectProperties :: Release (void)
{
DWORD dwRefT = --m_dwRefCnt;

	if (m_dwRefCnt == 0) delete this;	// freigeben

return dwRefT;
}

// *** IEnumUnknown methods ---------------------------------------------------
STDMETHODIMP CEnumObjectProperties :: Next (ULONG celt, LPUNKNOWN *rgelt, ULONG *ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (NULL == rgelt || m_Props.Count() <= m_ulCurr) 
		return ResultFromScode (S_FALSE);
        	
	while (m_Props.Count() > m_ulCurr && 0 < celt) {
	CObjPropLock l(m_tCurr);
	
		_ASSERTE (NULL != (CObjProp *)l);

		l -> GetObjProp ((LPOBJECTPROPERTY *)rgelt);
		rgelt++;

	// weiterzählen
		m_ulCurr++;
		m_tCurr.Next();
		celt--;
		cONrReturn++;
	}
	if (ppeltFetched) 
		*ppeltFetched = (cONrReturn - celt);	// gelieferte Werte

return NOERROR;
}

STDMETHODIMP CEnumObjectProperties :: Skip (ULONG dwSkip)
{
	if (m_Props.Count() > m_ulCurr + dwSkip) {
		m_ulCurr += dwSkip;
		while (0 < dwSkip--)
			m_tCurr.Next();
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

STDMETHODIMP CEnumObjectProperties :: Reset (void)
{
	m_tCurr.First();
	m_ulCurr = 0L;

return NOERROR;
}

STDMETHODIMP CEnumObjectProperties :: Clone (IEnumUnknown **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

// Enumerator bilden
CEnumObjectProperties *pEnum = CEnumObjectProperties :: CreateInstance();

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Objects kopieren
CTable t(m_Props.m_PropsName);

	for (t.First(); t.Valid(); t.Next()) {
	CObjPropLock l(t);
	
		_ASSERTE(NULL != (CObjProp *)l);
		
	LPOBJECTPROPERTY pIObjProp = NULL;

		l -> GetObjProp (&pIObjProp);
		if (NULL == pIObjProp) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}

	DWORD dwCookie = pEnum -> AddProp (l -> GetPropID(), pIObjProp);
		
		pIObjProp -> Release();
		if (0L == dwCookie) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}
	}

// Status kopieren
	pEnum -> m_ulCurr = m_ulCurr;

ULONG ulT = m_ulCurr;

	_ASSERTE(m_ulCurr <= m_Props.m_PropsName.Count());

	while (0 < ulT--) {
		_ASSERTE(pEnum -> m_tCurr.Valid());
		pEnum -> m_tCurr.Next();
	}

	*ppenum = pEnum;

return NOERROR;
}

// *** IEnumObjProps methods --------------------------------------------------
STDMETHODIMP CEnumObjectProperties :: FindByID (ULONG ulID, IObjectProperty **ppOProp)
{
	return m_Props.FindProp (ulID, ppOProp) ? NOERROR : ResultFromScode (E_FAIL);
}

STDMETHODIMP CEnumObjectProperties :: FindByName (LPCSTR pName, IObjectProperty **ppOProp)
{
	return m_Props.FindProp (pName, ppOProp) ? NOERROR : ResultFromScode (E_FAIL);
}

