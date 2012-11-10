// Enumerator der geöffneten Projekte -----------------------------------------
// File: ENUMCLSS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "clsarray.hxx"		// Collection: CClasses
#include "class.hxx"
#include "enumclss.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CEnumClasses *CEnumClasses::CreateInstance (CIdentArray *pArr)
{
	if (pArr == NULL) return NULL;

CEnumClasses *pEClass = NULL;

	TRY {
		pEClass = new CEnumClasses;

	// CIdentArray kopieren
		pEClass -> m_pIdArray = pArr -> Copy();
		if (NULL == pEClass -> m_pIdArray) 
			AfxThrowMemoryException();

		pEClass -> AddRef();
		pEClass -> InitCount();
	
	} CATCH(CMemoryException, e) {
		DELETE_OBJ(pEClass);
		return NULL;
	} END_CATCH;

return pEClass;
}


CEnumClasses *CEnumClasses::CreateInstance (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc,
	INITCLASSCOLLECTIONPROC pICProc, DWORD dwData)
{
CEnumClasses *pEClass = NULL;

	TRY {
	// CIdentArray neu anlegen
		pEClass = new CEnumClasses;
		pEClass -> m_pIdArray = CIdentArray::CreateInstance (
								pUnk, pApp, pDoc, pICProc, dwData);
		if (NULL == pEClass -> m_pIdArray) 
			AfxThrowMemoryException();

		pEClass -> AddRef();
		pEClass -> InitCount();
		
	} CATCH(CMemoryException, e) {
		DELETE_OBJ(pEClass);
		return NULL;
	} END_CATCH;

return pEClass;
}


CEnumClasses :: CEnumClasses (void)
{
	m_dwRefCnt = 0;
	m_iCurrent = 0;
	m_ulCount = 0L;
	m_pIdArray = NULL;
}

CEnumClasses :: ~CEnumClasses (void)
{
	DELETE_OBJ(m_pIdArray);
}

// IEnumVARAINT methods -------------------------------------------------------
STDMETHODIMP CEnumClasses :: Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
{
HRESULT hr;

	for(ULONG i = 0; i < celt; ++i)
		VariantInit (&rgvar[i]);

	for(i = 0; i < celt; ++i) {
		if(m_iCurrent == Count()) {
			hr = ResultFromScode (S_FALSE);
			goto LDone;
	  	}
	
		V_VT(&rgvar[i]) = VT_DISPATCH;
		hr = m_pIdArray -> GetClassDisp (m_iCurrent++, (LPVOID *)&V_DISPATCH(&rgvar[i]));
		if (FAILED(hr)) goto LError0;
	}
	hr = NOERROR;

LDone:
	if (pceltFetched != NULL)
		*pceltFetched = i;

return hr;

LError0:	// Fehler, alles wieder aufräumen

	for(i = 0; i < celt; ++i)
		VariantClear(&rgvar[i]);

return hr;
}


STDMETHODIMP CEnumClasses :: Skip (ULONG celt)
{
	m_iCurrent += celt;
	if(m_iCurrent > Count())
		m_iCurrent = Count();

return (m_iCurrent == Count()) ? ResultFromScode (S_FALSE) : NOERROR;
}


STDMETHODIMP CEnumClasses :: Reset (void)
{
	m_iCurrent = 0;

return NOERROR;
}


// Anlegen einer Kopie dieses Enumerators -------------------------------------
STDMETHODIMP CEnumClasses :: Clone (LPENUMVARIANT *ppenum)
{
CEnumClasses *penum = CEnumClasses :: CreateInstance (m_pIdArray);

	if (penum == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

	penum -> m_iCurrent = m_iCurrent;
	*ppenum = penum;

return NOERROR;
}


// IUnknown Methods -----------------------------------------------------------
STDMETHODIMP CEnumClasses :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	if(riid != IID_IUnknown && riid != IID_IEnumVARIANT) {
		*ppv = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}
	*ppv = this;
	AddRef();

return NOERROR;
}


STDMETHODIMP_(ULONG) CEnumClasses :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CEnumClasses :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}

return m_dwRefCnt;
}

