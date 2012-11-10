// Enumerator for GeoObjects -----------------------------------------
// File: ENUMOBJS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "objarray.hxx"		// Collection: GeoObjects
#include "obj.hxx"
#include "enumobjs.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CEnumGeoObjs *CEnumGeoObjs :: CreateInstance (CGeoObjArray *pArr)
{
	if (pArr == NULL) return NULL;
	
CEnumGeoObjs *pEGeoObj = NULL;

	TRY {
		pEGeoObj = new CEnumGeoObjs;
		
		pEGeoObj->m_pGeoObjArray = pArr -> Copy();   // copy CGeoObjArray
		if (NULL == pEGeoObj->m_pGeoObjArray) 
			AfxThrowMemoryException();

		pEGeoObj->AddRef();
		pEGeoObj->InitCount();

	} CATCH(CMemoryException, e) {
		DELETE_OBJ(pEGeoObj);
		return NULL;
	} END_CATCH;
         
return pEGeoObj;
}	

CEnumGeoObjs *CEnumGeoObjs :: CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, 
					      CGeoDoc *pDoc, 
					      INITOBJCOLLECTIONPROC pICProc, DWORD dwData)
{
CEnumGeoObjs *pEGeoObj = NULL;

	TRY {
		pEGeoObj = new CEnumGeoObjs;
		pEGeoObj->m_pGeoObjArray = CGeoObjArray::CreateInstance (pUnk, pApp, pDoc, pICProc, dwData);

		if (NULL == pEGeoObj->m_pGeoObjArray) 
			AfxThrowMemoryException();

		pEGeoObj->AddRef();
		pEGeoObj->InitCount();
	
	} CATCH (CMemoryException, e) {
		DELETE_OBJ(pEGeoObj);
		return NULL;
	} END_CATCH;
			
return pEGeoObj;
}

CEnumGeoObjs :: CEnumGeoObjs (void)
{
	m_dwRefCnt = 0;
	m_iCurrent = 0;
	m_ulCount = 0L;
	m_pGeoObjArray = NULL;
}


CEnumGeoObjs :: ~CEnumGeoObjs (void)
{
	DELETE_OBJ(m_pGeoObjArray);
}


// IEnumVARIANT methods -------------------------------------------------------
STDMETHODIMP CEnumGeoObjs :: Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
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
		hr = m_pGeoObjArray -> GetObjectDisp (m_iCurrent++, (LPVOID *)&V_DISPATCH(&rgvar[i]));
		if(FAILED(hr)) goto LError0;
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


STDMETHODIMP CEnumGeoObjs :: Skip (ULONG celt)
{
	m_iCurrent += celt;
	if(m_iCurrent > Count())
		m_iCurrent = Count();

return (m_iCurrent == Count()) ? ResultFromScode (S_FALSE) : NOERROR;
}


STDMETHODIMP CEnumGeoObjs :: Reset (void)
{
	m_iCurrent = 0;

return NOERROR;
}


STDMETHODIMP CEnumGeoObjs :: Clone (LPENUMVARIANT *ppenum)
{
CEnumGeoObjs *penum = CEnumGeoObjs :: CreateInstance (m_pGeoObjArray);

	if (penum == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

	penum -> m_iCurrent = m_iCurrent;
	*ppenum = penum;

return NOERROR;
}


// IUnknown Methods -----------------------------------------------------------
STDMETHODIMP CEnumGeoObjs :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	if(riid != IID_IUnknown && riid != IID_IEnumVARIANT) {
		*ppv = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}
	*ppv = this;
	AddRef();

return NOERROR;
}


STDMETHODIMP_(ULONG) CEnumGeoObjs :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CEnumGeoObjs :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}

return m_dwRefCnt;
}

