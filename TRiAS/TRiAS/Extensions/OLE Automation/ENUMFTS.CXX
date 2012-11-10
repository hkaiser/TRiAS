// Enumerator for GeoFeatures -----------------------------------------
// File: ENUMFTS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "ftsarray.hxx"		// Collection: GeoFtsects
#include "feat.hxx"
#include "enumfts.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CEnumGeoFts *CEnumGeoFts::CreateInstance (CGeoFtsArray *pArr)
{
CEnumGeoFts *pEGeoFts = new CEnumGeoFts;

	if (pEGeoFts == NULL || pArr == NULL) return NULL;
	        	
	pEGeoFts -> m_pGeoFtsArray = pArr -> Copy();   // copy CGeoFtsArray
	
	if (pEGeoFts->m_pGeoFtsArray == NULL) {
		DELETE_OBJ (pEGeoFts);
		return NULL;
	}
    pEGeoFts->AddRef();
	pEGeoFts->InitCount();
         
return pEGeoFts;
}	


CEnumGeoFts *CEnumGeoFts::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pViewClsObj, 
	INITFEATCOLLECTIONPROC pICProc, DWORD dwData, DWORD dwFlags)
{
CEnumGeoFts *pEGeoFts = new CEnumGeoFts;

	if (pEGeoFts == NULL) return NULL;

	pEGeoFts -> m_pGeoFtsArray = CGeoFtsArray::CreateInstance (
		pUnk, pApp, pDoc, pViewClsObj, pICProc, dwData, dwFlags);
	if (pEGeoFts -> m_pGeoFtsArray == NULL) {
		DELETE_OBJ (pEGeoFts);
		return NULL;
	}
	pEGeoFts -> AddRef();
	return pEGeoFts;
}


CEnumGeoFts::CEnumGeoFts (void)
{
	m_dwRefCnt = 0;
	m_iCurrent = 0;
    m_pGeoFtsArray = NULL;
}

CEnumGeoFts::~CEnumGeoFts (void)
{
	DELETE_OBJ (m_pGeoFtsArray);
}


// IEnumVARIANT methods -------------------------------------------------------
STDMETHODIMP CEnumGeoFts::Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
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
		hr = m_pGeoFtsArray -> GetFeatureDisp (m_iCurrent++, (DGeoFeature **)&V_DISPATCH(&rgvar[i]));
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


STDMETHODIMP CEnumGeoFts::Skip (ULONG celt)
{
	m_iCurrent += celt;
	if(m_iCurrent > Count())
		m_iCurrent = Count();

return (m_iCurrent == Count()) ? ResultFromScode (S_FALSE) : NOERROR;
}


STDMETHODIMP CEnumGeoFts::Reset (void)
{
	m_iCurrent = 0;

return NOERROR;
}


STDMETHODIMP CEnumGeoFts::Clone (LPENUMVARIANT *ppenum)
{
CEnumGeoFts *penum = CEnumGeoFts::CreateInstance (m_pGeoFtsArray);

	if (penum == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

	penum -> m_iCurrent = m_iCurrent;
	*ppenum = penum;

return NOERROR;
}


// IUnknown Methods -----------------------------------------------------------
STDMETHODIMP CEnumGeoFts::QueryInterface (REFIID riid, LPVOID *ppv)
{
	if(riid != IID_IUnknown && riid != IID_IEnumVARIANT) {
		*ppv = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}
	*ppv = this;
	AddRef();

return NOERROR;
}


STDMETHODIMP_(ULONG) CEnumGeoFts::AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CEnumGeoFts::Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}

return m_dwRefCnt;
}

