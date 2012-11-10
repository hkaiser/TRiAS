// Enumerator for Object Windows -----------------------------------------
// File: ENUMOBWS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "obwarray.hxx"
#include "objwin.hxx"
#include "enumobws.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CEnumGeoObjWins *CEnumGeoObjWins :: CreateInstance (CGeoObjWinArray *pArr)
{
	if (pArr == NULL) return NULL;
	
CEnumGeoObjWins *pEGeoObjWin = new CEnumGeoObjWins;

	if (pEGeoObjWin == NULL) return NULL;
	        	
	pEGeoObjWin->m_pOWArray = pArr -> Copy();   // copy CGeoObjWinArray
	
	if (pEGeoObjWin->m_pOWArray == NULL) {
		DELETE_OBJ (pEGeoObjWin);
		return NULL;
	}
         pEGeoObjWin->AddRef();
         
return pEGeoObjWin;
}	


CEnumGeoObjWins *CEnumGeoObjWins :: CreateInstance (LPUNKNOWN  pUnk, 
													CTriasApp *pApp, 
													CGeoDoc   *pDoc, 
									  INITOBJWINCOLLECTIONPROC pICProc, 
													DWORD      dwData)
{

CEnumGeoObjWins *pEGeoObjWin = new CEnumGeoObjWins;

	if (pEGeoObjWin == NULL) return NULL;

	pEGeoObjWin->m_pOWArray = CGeoObjWinArray :: CreateInstance (pUnk, 
																 pApp, 
																 pDoc, 
																 pICProc, 
																 dwData);

	if (pEGeoObjWin->m_pOWArray == NULL) {
		DELETE_OBJ (pEGeoObjWin);
		return NULL;
	}

	pEGeoObjWin -> AddRef();
		
return pEGeoObjWin;

}


CEnumGeoObjWins :: CEnumGeoObjWins (void)
{
	m_dwRefCnt = 0;
	m_iCurrent = 0;
    m_pOWArray = NULL;
}


CEnumGeoObjWins :: ~CEnumGeoObjWins (void)
{
	DELETE_OBJ(m_pOWArray);
}


// IEnumVARIANT methods -------------------------------------------------------
STDMETHODIMP CEnumGeoObjWins :: Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
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
		hr = m_pOWArray -> GetObjectWinDisp (m_iCurrent++, (LPVOID *)&V_DISPATCH(&rgvar[i]));
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


STDMETHODIMP CEnumGeoObjWins :: Skip (ULONG celt)
{
	m_iCurrent += celt;
	if(m_iCurrent > Count())
		m_iCurrent = Count();

return (m_iCurrent == Count()) ? ResultFromScode (S_FALSE) : NOERROR;
}


STDMETHODIMP CEnumGeoObjWins :: Reset (void)
{
	m_iCurrent = 0;

return NOERROR;
}


STDMETHODIMP CEnumGeoObjWins :: Clone (LPENUMVARIANT *ppenum)
{
CEnumGeoObjWins *penum = CEnumGeoObjWins :: CreateInstance (m_pOWArray);

	if (penum == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

	penum -> m_iCurrent = m_iCurrent;
	*ppenum = penum;

return NOERROR;
}


// IUnknown Methods -----------------------------------------------------------
STDMETHODIMP CEnumGeoObjWins :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	if(riid != IID_IUnknown && riid != IID_IEnumVARIANT) {
		*ppv = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}
	*ppv = this;
	AddRef();

return NOERROR;
}


STDMETHODIMP_(ULONG) CEnumGeoObjWins :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CEnumGeoObjWins :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}

return m_dwRefCnt;
}

