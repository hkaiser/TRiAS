// Enumerator Aller ObjektProperties aller Erweiterungen ----------------------
// File EALLPROP.CXX

#include "triaspre.hxx"

#include <xtsnguid.h>
#include "eallprop.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Eine Objekteigenschaft -----------------------------------------------------
CObjProp :: CObjProp (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup)
{
	TX_ASSERT(NULL != pIObjProp);

	m_dwRefCnt = 1;

char cbBuffer[_MAX_PATH];

	m_pIObjProp = NULL;
	if (NULL != pIObjProp && SUCCEEDED(pIObjProp -> GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL))) 
	{
		m_strName.SetType (OBJPROP_ROOT);
		m_strName.SetGroup (pcGroup);
		m_strName.SetName (cbBuffer);

		m_pIObjProp = pIObjProp;
		m_pIObjProp -> AddRef();
	}
}


CObjProp :: ~CObjProp (void)
{
	if (m_pIObjProp) m_pIObjProp -> Release();
}

void *CObjProp :: GetPropName (void *pObj)
{
	return & (((CObjProp *)pObj) -> m_strName);
}

int CObjProp :: StringCmp (void *p1, void *p2)
{
CPropertyName *pStr1 = (CPropertyName *)p1;
CPropertyName *pStr2 = (CPropertyName *)p2;

	TX_ASSERT(NULL != pStr1 && NULL != pStr2);

	return Compare (*pStr1, *pStr2);
}

// *** IUnknown methods ***
STDMETHODIMP CObjProp :: QueryInterface (REFIID riid, LPVOID FAR* ppvObj)
{
	return m_pIObjProp -> QueryInterface (riid, ppvObj);
}

STDMETHODIMP_(ULONG) CObjProp :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CObjProp :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP CObjProp :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	if (NULL != pBuffer && wLen > 0) {
	// erst Namen reinfüllen
		if (!m_strName.GetFullName (pBuffer, wLen))
			return ResultFromScode (E_FAIL);
	}

// dann Flags direkt holen
return m_pIObjProp -> GetPropInfo (NULL, 0, pdwFlags);
}


STDMETHODIMP CObjProp :: Reset (void)
{
	return m_pIObjProp -> Reset();
}

STDMETHODIMP_(ULONG) CObjProp :: Count (void)
{
	return m_pIObjProp -> Count();
}

STDMETHODIMP CObjProp :: HelpInfo(LPSTR pBuffer, ULONG ulLen, 
				  LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	return m_pIObjProp -> HelpInfo (pBuffer, ulLen, pHelpFile, pulHelpCtx);
}


STDMETHODIMP CObjProp :: Eval(LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return m_pIObjProp -> Eval (lONr, pBuffer, ulLen, pulWritten);
}

STDMETHODIMP CObjProp :: Cumulation(LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return m_pIObjProp -> Cumulation (pBuffer, ulLen, pulWritten);
}

///////////////////////////////////////////////////////////////////////////////
// Ein Baum, der die Objprops nach ihrem Namen sortiert -----------------------
CObjProps :: ~CObjProps (void)
{
	EveryDelete();
}

void CObjProps :: UserDelete (void *pObj)
{
	((CObjProp *)pObj) -> Release();
}

bool CObjProps :: AddProp (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup)
{
CObjPropCreator OPCr (*this);

	return NULL != ContCreate (OPCr, CObjProp)(pIObjProp, pcGroup);
}

bool CObjProps :: FindProp (LPCSTR pcName, LPOBJECTPROPERTY *ppIObjProp)
{
	TX_ASSERT(NULL != ppIObjProp);

CTable t(*this);
CPropertyName strKey (pcName);

#if defined(_DEBUG)
	for (t.First(); t.Valid(); t.Next()) {
	CObjPropLock l(t);
	CObjProp *p = (CObjProp *)l;
	char cbBuffer[_MAX_PATH];

		p -> GetPropInfo (cbBuffer, _MAX_PATH, NULL);
	}
#endif // _DEBUG

	*ppIObjProp = NULL;	// für alle Fälle
	if (t.Find (&strKey)) {
	CObjPropLock l(t);

		TX_ASSERT(NULL != (CObjProp *)l);
		if (l) {
			l -> GetObjProp (ppIObjProp);
			return true;
		} 
	}

return false;
}

bool CObjProps :: DeleteProp (LPCSTR pcName)
{
CTable t(*this);
CPropertyName strKey (pcName);

	if (t.Find (&strKey)) 
		return t.Delete();

return false;
}

// Der eigentliche Enumerator der ObjektProperties ----------------------------
CEnumAllObjectProperties :: CEnumAllObjectProperties (void)
		          : m_Props(), m_tCurr(m_Props)
{
	m_dwRefCnt = 0L;
	Reset();
}

CEnumAllObjectProperties :: ~CEnumAllObjectProperties (void)
{
}

CEnumAllObjectProperties *CEnumAllObjectProperties :: CreateInstance (void)
{
CEnumAllObjectProperties *pEnum = new CEnumAllObjectProperties();

	if (NULL == pEnum || !pEnum -> FInit()) {
		DELETE (pEnum);
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CEnumAllObjectProperties :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumUnknown || 
	    riid == IID_IEnumObjProps)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CEnumAllObjectProperties :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CEnumAllObjectProperties :: Release (void)
{
DWORD dwRefT = --m_dwRefCnt;

	if (m_dwRefCnt == 0) delete this;	// freigeben

return dwRefT;
}

// *** IEnumUnknown methods ---------------------------------------------------
STDMETHODIMP CEnumAllObjectProperties :: Next (ULONG celt, LPUNKNOWN *rgelt, ULONG *ppeltFetched)
{
DWORD cONrReturn = 0L;

	if (ppeltFetched) *ppeltFetched = 0L;

	if (NULL == rgelt || m_Props.Count() <= m_ulCurr) 
		return ResultFromScode (S_FALSE);
        	
	while (m_Props.Count() > m_ulCurr && 0 < celt) {
	CObjPropLock l(m_tCurr);
	
		TX_ASSERT (NULL != (CObjProp *)l);
		if (!l) continue;

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

STDMETHODIMP CEnumAllObjectProperties :: Skip (ULONG dwSkip)
{
	if (m_Props.Count() > m_ulCurr + dwSkip) {
		m_ulCurr += dwSkip;
		while (0 < dwSkip--)
			m_tCurr.Next();
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

STDMETHODIMP CEnumAllObjectProperties :: Reset (void)
{
	m_tCurr.First();
	m_ulCurr = 0L;

return NOERROR;
}

STDMETHODIMP CEnumAllObjectProperties :: Clone (IEnumUnknown **ppenum)
{
	*ppenum = NULL;		// für alle Fälle

// Enumerator bilden
CEnumAllObjectProperties *pEnum = CEnumAllObjectProperties :: CreateInstance();

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Objects kopieren
CTable t(m_Props);

	for (t.First(); t.Valid(); t.Next()) {
	CObjPropLock l(t);
	
		TX_ASSERT(NULL != (CObjProp *)l);
		if (!l) continue;

	LPOBJECTPROPERTY pIObjProp = NULL;

		l -> GetObjProp (&pIObjProp);
		if (NULL == pIObjProp) {
			pEnum -> Release();
			return ResultFromScode (E_OUTOFMEMORY);
		}

	DWORD dwCookie = pEnum -> AddProp (pIObjProp);
		
		pIObjProp -> Release();
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

// *** IEnumObjProps methods --------------------------------------------------
STDMETHODIMP CEnumAllObjectProperties :: FindByName (LPCSTR pName, IObjectProperty **ppOProp)
{
	return m_Props.FindProp (pName, ppOProp) ? NOERROR : ResultFromScode (E_FAIL);
}

