// Enumerator Aller ObjektProperties aller Erweiterungen ----------------------
// File EALLCPRP.CXX

#include "triaspre.hxx"

#include <xtsnguid.h>
#include "eallcprp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Eine Objekteigenschaft -----------------------------------------------------
CClsProp :: CClsProp (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup)
{
	TX_ASSERT(NULL != pIClsProp);

	m_dwRefCnt = 1;

char cbBuffer[_MAX_PATH];

	m_pIClsProp = NULL;
	if (NULL != pIClsProp && SUCCEEDED(pIClsProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL))) 
	{
		m_strName.SetType (CLSPROP_ROOT);
		m_strName.SetGroup (pcGroup);
		m_strName.SetName (cbBuffer);

		m_pIClsProp = pIClsProp;
		m_pIClsProp -> AddRef();
	}
}


CClsProp :: ~CClsProp (void)
{
	if (m_pIClsProp) m_pIClsProp -> Release();
}

void *CClsProp :: GetPropName (void *pObj)
{
	return & (((CClsProp *)pObj) -> m_strName);
}

int CClsProp :: StringCmp (void *p1, void *p2)
{
CPropertyName *pStr1 = (CPropertyName *)p1;
CPropertyName *pStr2 = (CPropertyName *)p2;

	TX_ASSERT(NULL != pStr1 && NULL != pStr2);

	return Compare (*pStr1, *pStr2);
}

// *** IUnknown methods ***
STDMETHODIMP CClsProp :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	return m_pIClsProp -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CClsProp :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CClsProp :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

// *** IClassProperty specific functions ***
STDMETHODIMP CClsProp :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
// erst Namen reinfüllen
	if (!m_strName.GetFullName (pBuffer, wLen))
		return ResultFromScode (E_FAIL);

// dan Flags direkt holen
return m_pIClsProp -> GetPropInfo (NULL, 0, pdwFlags);
}

STDMETHODIMP CClsProp :: Reset (void)
{
	return m_pIClsProp -> Reset();
}

STDMETHODIMP_(ULONG) CClsProp :: Count (void)
{
	return m_pIClsProp -> Count();
}

STDMETHODIMP CClsProp :: HelpInfo(LPSTR pBuffer, ULONG ulLen, 
				  LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	return m_pIClsProp -> HelpInfo (pBuffer, ulLen, pHelpFile, pulHelpCtx);
}


STDMETHODIMP CClsProp :: Eval (IEnumLONG *pEnumObj, LPSTR pBuffer, 
			       ULONG ulLen, ULONG *pulWritten)
{
	return m_pIClsProp -> Eval (pEnumObj, pBuffer, ulLen, pulWritten);
}

STDMETHODIMP CClsProp :: Cumulation(LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return m_pIClsProp -> Cumulation (pBuffer, ulLen, pulWritten);
}

///////////////////////////////////////////////////////////////////////////////
// Ein Baum, der die ClsProps nach ihrem Namen sortiert -----------------------
CClsProps :: ~CClsProps (void)
{
	EveryDelete();
}

void CClsProps :: UserDelete (void *pObj)
{
	((CClsProp *)pObj) -> Release();
}

bool CClsProps :: AddProp (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup)
{
CClsPropCreator OPCr (*this);

	return NULL != ContCreate (OPCr, CClsProp)(pIClsProp, pcGroup);
}

bool CClsProps :: FindProp (LPCSTR pcName, LPCLASSPROPERTY *ppIClsProp)
{
	TX_ASSERT(NULL != ppIClsProp);

CTable t(*this);
CPropertyName strKey (pcName);

	*ppIClsProp = NULL;	// für alle Fälle
	if (t.Find (&strKey)) {
	CClsPropLock l(t);

		TX_ASSERT(NULL != (CClsProp *)l);
		l -> GetClsProp (ppIClsProp);
		return true;
	}

return false;
}

bool CClsProps :: DeleteProp (LPCSTR pcName)
{
CTable t(*this);
CPropertyName strKey (pcName);

	if (t.Find (&strKey)) 
		return t.Delete();

return false;
}

// Der eigentliche Enumerator der ObjektProperties ----------------------------
CEnumAllClassProperties :: CEnumAllClassProperties (void)
		         : m_Props(), m_tCurr(m_Props)
{
	m_dwRefCnt = 0L;
	Reset();
}

CEnumAllClassProperties :: ~CEnumAllClassProperties (void)
{
}

CEnumAllClassProperties *CEnumAllClassProperties :: CreateInstance (void)
{
CEnumAllClassProperties *pEnum = new CEnumAllClassProperties();

	if (NULL == pEnum || !pEnum -> FInit()) {
		DELETE (pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CEnumAllClassProperties :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumUnknown || 
	    riid == IID_IEnumClassProps)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CEnumAllClassProperties :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CEnumAllClassProperties :: Release (void)
{
DWORD dwRefT = --m_dwRefCnt;

	if (m_dwRefCnt == 0) delete this;	// freigeben

return dwRefT;
}

// *** IEnumUnknown methods ---------------------------------------------------
STDMETHODIMP CEnumAllClassProperties :: Next (ULONG celt, LPUNKNOWN *rgelt, ULONG *ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (NULL == rgelt || m_Props.Count() <= m_ulCurr) 
		return ResultFromScode (S_FALSE);
        	
	while (m_Props.Count() > m_ulCurr && 0 < celt) {
	CClsPropLock l(m_tCurr);
	
		TX_ASSERT (NULL != (CClsProp *)l);

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

STDMETHODIMP CEnumAllClassProperties :: Skip (ULONG dwSkip)
{
	if (m_Props.Count() > m_ulCurr + dwSkip) {
		m_ulCurr += dwSkip;
		while (0 < dwSkip--)
			m_tCurr.Next();
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

STDMETHODIMP CEnumAllClassProperties :: Reset (void)
{
	m_tCurr.First();
	m_ulCurr = 0L;

return NOERROR;
}

STDMETHODIMP CEnumAllClassProperties :: Clone (IEnumUnknown **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

// Enumerator bilden
CEnumAllClassProperties *pEnum = CEnumAllClassProperties :: CreateInstance();

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Objects kopieren
CTable t(m_Props);

	for (t.First(); t.Valid(); t.Next()) {
	CClsPropLock l(t);
	
		TX_ASSERT(NULL != (CClsProp *)l);
		
	LPCLASSPROPERTY pIClsProp = NULL;

		l -> GetClsProp (&pIClsProp);
		if (NULL == pIClsProp) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}

	DWORD dwCookie = pEnum -> AddProp (pIClsProp);
		
		pIClsProp -> Release();
		if (0L == dwCookie) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}
	}

// Status kopieren
	pEnum -> m_ulCurr = m_ulCurr;

ULONG ulT = m_ulCurr;

	TX_ASSERT(m_ulCurr <= m_Props.Count());

	while (0 < ulT--) {
		TX_ASSERT(pEnum -> m_tCurr.Valid());
		pEnum -> m_tCurr.Next();
	}

	*ppenum = pEnum;

return NOERROR;
}

// *** IEnumClsProps methods --------------------------------------------------
STDMETHODIMP CEnumAllClassProperties :: FindByName (LPCSTR pName, IClassProperty **ppOProp)
{
	return m_Props.FindProp (pName, ppOProp) ? NOERROR : ResultFromScode (E_FAIL);
}

