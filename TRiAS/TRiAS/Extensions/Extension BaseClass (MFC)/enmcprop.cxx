// Enumerator der ObjektClassProperties einer Erweiterung ---------------------
// File ENMCPROP.CXX

#include "xtensnp.hxx"

#include "enmcprop.hxx"
#include <xtsnguid.h>

#include "synccook.h"

#if defined(_DEBUG) && defined(WIN32)
#if defined(__MFC__)
#define new DEBUG_NEW
#endif // __MFC__
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Eine Objekteigenschaft -----------------------------------------------------
CClsProp :: CClsProp (ULONG uiID, LPCLASSPROPERTY pIClsProp)
{
char cbBuffer[64];

	m_ulID = 0L;
	m_pIClsProp = NULL;

	if (SUCCEEDED(pIClsProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL))) {
		m_strName = cbBuffer;
		m_ulID = uiID;
		m_pIClsProp = pIClsProp;
//		m_pIClsProp -> AddRef();	// already done
	}
}


CClsProp :: ~CClsProp (void)
{
	if (m_pIClsProp) m_pIClsProp -> Release();
}

void *GetClsPropName (void *pObj)
{
	return & (((CClsProp *)pObj) -> m_strName);
}

void *GetClsPropID (void *pObj)
{
	return & (((CClsProp *)pObj) -> m_ulID);
}

// Ein Baum, der die ClsProps nach ihrem Namen sortiert -----------------------
CClsPropsName :: ~CClsPropsName (void)
{
	EveryDelete();
}

void CClsPropsName :: UserDelete (void *pObj)
{
	((CClsProp *)pObj) -> ~CClsProp();
}

CClsProp *CClsPropsName :: AddProp (ULONG uiID, LPCLASSPROPERTY pIClsProp)
{
CClsPropCreator OPCr (*this);

#if defined(__MFC__)
CClsProp *pClsProp = new CClsProp (uiID, pIClsProp);

	if (NULL == pClsProp) return NULL;

	return OPCr.InsertPtr(pClsProp);
#elif defined(__ATL_USED__)
	return ContCreate (OPCr, CClsProp)(uiID, pIClsProp);
#else
	return Create (OPCr, CClsProp)(uiID, pIClsProp);
#endif // __MFC__
}

bool CClsPropsName :: FindProp (LPCSTR pName, LPCLASSPROPERTY *ppIClsProp)
{
	_ASSERTE(NULL != ppIClsProp);

CTable t(*this);
string strKey = pName;

	*ppIClsProp = NULL;	// für alle Fälle
	if (t.Find (&strKey)) {
	CClsPropLock l(t);

		_ASSERTE(NULL != (CClsProp *)l);
		l -> GetClsProp (ppIClsProp);
		return true;
	}

return false;
}

bool CClsPropsName :: DeleteProp (LPCSTR pName)
{
CTable t(*this);
string strKey = pName;

	if (t.Find (&strKey)) 
		return t.Delete();

return false;
}

// Ein Baum der die ClsProps nach ihrem ID sortiert ---------------------------
CClsPropsID :: ~CClsPropsID (void)
{
	EveryDelete();
}

void CClsPropsID :: UserDelete (void *)
{
	// nothing to do (CDelTree)
}

bool CClsPropsID :: AddProp (CClsProp *pClsProp)
{
CClsProp1Creator OPCr (*this);

	return NULL != OPCr.InsertPtr (pClsProp) ? true : false;
}

bool CClsPropsID :: FindProp (ULONG ulID, LPCLASSPROPERTY *ppIClsProp)
{
	_ASSERTE(NULL != ppIClsProp);

CTable t(*this);

	*ppIClsProp = NULL;	// für alle Fälle
	
	if (t.Find (&ulID)) {
	CClsPropLock l(t);

		_ASSERTE(NULL != (CClsProp *)l);
		l -> GetClsProp (ppIClsProp);
		return true;
	}

return false;
}

bool CClsPropsID :: DeleteProp (ULONG ulID)
{
CTable t(*this);

	if (t.Find (&ulID)) 
		return t.Delete();

return false;
}

// Zusammenfassen beider Bäume in einem Interface -----------------------------
DWORD CClsProps :: AddProp (ULONG uiID, LPCLASSPROPERTY pIClsProp)
{
	pIClsProp -> AddRef();		// hold on

CClsProp *pClsProp = m_PropsName.AddProp (uiID, pIClsProp);

	if (NULL == pClsProp) {
		pIClsProp -> Release();
		return 0L;
	}

	if (!m_PropsID.AddProp (pClsProp)) {
		m_PropsName.DeleteProp (pClsProp -> GetPropName() -> c_str());
		pIClsProp -> Release();
		return 0L;
	}

	DEXN_AddedClassProperty();
	return uiID;
}

bool CClsProps :: DeleteProp (ULONG ulID)
{
LPCLASSPROPERTY pIClsProp = NULL;

	if (!m_PropsID.FindProp (ulID, &pIClsProp))
		return false;

bool fOK1 = m_PropsID.DeleteProp (ulID);
char cbBuffer[64];

	pIClsProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL);

bool fOK2 = m_PropsName.DeleteProp (cbBuffer);
	
	pIClsProp -> Release();

	DEXN_RemovedClassProperty();
	return fOK1 && fOK2;
}

// Alle ClsProps aus Doppeltbaum löschen --------------------------------------
bool CClsProps :: EveryDelete (void)
{
bool fOK1 = m_PropsID.EveryDelete();
bool fOK2 = m_PropsName.EveryDelete();

	DEXN_RemovedClassProperty();
	return fOK1 && fOK2;
}

// Der eigentliche Enumerator der ObjektProperties ----------------------------
CEnumClassProperties :: CEnumClassProperties (void)
		      : m_Props(), m_tCurr(m_Props.m_PropsID)
{
	m_dwRefCnt = 0L;
	m_dwCookie = 100L;
	Reset();
}

CEnumClassProperties :: ~CEnumClassProperties (void)
{
}

CEnumClassProperties *CEnumClassProperties :: CreateInstance (void)
{
CEnumClassProperties *pEnum = new CEnumClassProperties();

	if (NULL == pEnum || !pEnum -> FInit()) {
		DELETE_OBJ (pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// get next cookie thread save ------------------------------------------------
DWORD CEnumClassProperties :: GetCookie (void)
{
CSyncCookies Sync;

	return Sync.IncrementSynced (&m_dwCookie);
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CEnumClassProperties :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumUnknown || 
	    riid == IID_IEnumClassProps)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CEnumClassProperties :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CEnumClassProperties :: Release (void)
{
DWORD dwRefT = --m_dwRefCnt;

	if (m_dwRefCnt == 0) delete this;	// freigeben

return dwRefT;
}

// *** IEnumUnknown methods ---------------------------------------------------
STDMETHODIMP CEnumClassProperties :: Next (ULONG celt, LPUNKNOWN *rgelt, ULONG *ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (NULL == rgelt || m_Props.Count() <= m_ulCurr) 
		return ResultFromScode (S_FALSE);
        	
	while (m_Props.Count() > m_ulCurr && 0 < celt) {
	CClsPropLock l(m_tCurr);
	
		_ASSERTE (NULL != (CClsProp *)l);

		l -> GetClsProp ((LPCLASSPROPERTY *)rgelt);
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

STDMETHODIMP CEnumClassProperties :: Skip (ULONG dwSkip)
{
	if (m_Props.Count() > m_ulCurr + dwSkip) {
		m_ulCurr += dwSkip;
		while (0 < dwSkip--)
			m_tCurr.Next();
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

STDMETHODIMP CEnumClassProperties :: Reset (void)
{
	m_tCurr.First();
	m_ulCurr = 0L;

return NOERROR;
}

STDMETHODIMP CEnumClassProperties :: Clone (IEnumUnknown **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

// Enumerator bilden
CEnumClassProperties *pEnum = CEnumClassProperties :: CreateInstance();

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Objects kopieren
CTable t(m_Props.m_PropsName);

	for (t.First(); t.Valid(); t.Next()) {
	CClsPropLock l(t);
	
		_ASSERTE(NULL != (CClsProp *)l);
		
	LPCLASSPROPERTY pIClsProp = NULL;

		l -> GetClsProp (&pIClsProp);
		if (NULL == pIClsProp) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}

	DWORD dwCookie = pEnum -> AddProp (l -> GetPropID(), pIClsProp);
		
		pIClsProp -> Release();
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

// *** IEnumClsProps methods --------------------------------------------------
STDMETHODIMP CEnumClassProperties :: FindByID (ULONG ulID, IClassProperty **ppOProp)
{
	return m_Props.FindProp (ulID, ppOProp) ? NOERROR : ResultFromScode (E_FAIL);
}

STDMETHODIMP CEnumClassProperties :: FindByName (LPCSTR pName, IClassProperty **ppOProp)
{
	return m_Props.FindProp (pName, ppOProp) ? NOERROR : ResultFromScode (E_FAIL);
}

