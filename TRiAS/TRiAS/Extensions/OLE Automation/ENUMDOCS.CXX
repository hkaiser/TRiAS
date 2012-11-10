// Enumerator vor Doc -----------------------------------------
// File: ENUMDOCS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "docarray.hxx"		// Collection: CGeoDocs
#include "enumdocs.hxx"
#include "doc.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CEnumDocs *CEnumDocs :: CreateInstance (CGeoDocsArray *pArr)
{
	if (pArr == NULL) return NULL;

CEnumDocs *pEDocs = NULL;

	TRY {
	// CGeoDocsArray kopieren
		pEDocs = new CEnumDocs;
		pEDocs -> m_pDocsArray = pArr -> Copy();
		if (NULL == pEDocs -> m_pDocsArray) 
			AfxThrowMemoryException();

		pEDocs -> AddRef();
		pEDocs -> InitCount();
	
	} CATCH(CMemoryException, e) {
		DELETE_OBJ(pEDocs);
		return NULL;
	} END_CATCH;
			
return pEDocs;
}


CEnumDocs *CEnumDocs :: CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
			INITDOCCOLLECTIONPROC pICProc, DWORD dwData)
{
CEnumDocs *pEDocs = NULL;

	TRY {
	// CGeoDocsArray neu anlegen
		pEDocs = new CEnumDocs;
		pEDocs -> m_pDocsArray = CGeoDocsArray::CreateInstance (
									pUnk, pApp, pICProc, dwData);
		if (NULL == pEDocs -> m_pDocsArray) 
			AfxThrowMemoryException();

		pEDocs -> AddRef();
		pEDocs -> InitCount();
	
	} CATCH(CMemoryException, e) {
		DELETE_OBJ(pEDocs);
		return NULL;
	} END_CATCH;
		
return pEDocs;
}


CEnumDocs :: CEnumDocs (void)
{
	m_dwRefCnt = 0;
	m_iCurrent = 0;
	m_ulCount = 0L;
	m_pDocsArray = NULL;
}


CEnumDocs :: ~CEnumDocs (void)
{
	DELETE_OBJ (m_pDocsArray);
}


// IEnumVARAINT methods -------------------------------------------------------
STDMETHODIMP CEnumDocs :: Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
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
		hr = m_pDocsArray -> GetDocDisp (m_iCurrent++, (DDocument **)&V_DISPATCH(&rgvar[i]));
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


STDMETHODIMP CEnumDocs :: Skip (ULONG celt)
{
	m_iCurrent += celt;
	if(m_iCurrent > Count())
		m_iCurrent = Count();

	return (m_iCurrent == Count()) ? S_FALSE : NOERROR;
}


STDMETHODIMP CEnumDocs :: Reset (void)
{
	m_iCurrent = 0;
	return NOERROR;
}


// Anlegen einer Kopie dieses Enumerators -------------------------------------
STDMETHODIMP CEnumDocs :: Clone (LPENUMVARIANT *ppenum)
{
CEnumDocs *penum = CEnumDocs :: CreateInstance (m_pDocsArray);

	if (penum == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

	penum -> m_iCurrent = m_iCurrent;
	*ppenum = penum;

return NOERROR;
}


// IUnknown Methods -----------------------------------------------------------
STDMETHODIMP CEnumDocs :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	if(riid != IID_IUnknown && riid != IID_IEnumVARIANT) {
		*ppv = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}
	*ppv = this;
	AddRef();

return NOERROR;
}


STDMETHODIMP_(ULONG) CEnumDocs :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CEnumDocs :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}

return m_dwRefCnt;
}

