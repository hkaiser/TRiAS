// Enumerator vor View -----------------------------------------
// File: ENUVIEWS.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#include "viewarry.hxx"		// Collection: CGeoViews
#include "enuviews.hxx"
#include "view.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

CEnumViews *CEnumViews :: CreateInstance (CGeoViewsArray *pArr)
{
CEnumViews *pEViews = new CEnumViews;

	if (pEViews == NULL || pArr == NULL) return NULL;

// CGeoViewsArray kopieren
	pEViews -> m_pViewsArray = pArr -> Copy();
	if (pEViews -> m_pViewsArray == NULL) {
		DELETE_OBJ (pEViews);
		return NULL;
	} 
	pEViews -> AddRef();
		
return pEViews;
}


CEnumViews *CEnumViews :: CreateInstance (LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc,  
										  INITVIEWCOLLECTIONPROC pICProc, DWORD dwData)
{
CEnumViews *pEViews = new CEnumViews;

	if (pEViews == NULL) return NULL;

// CGeoViewsArray neu anlegen
	pEViews -> m_pViewsArray = CGeoViewsArray :: CreateInstance (pUnk, pApp, pDoc,  
								     							 pICProc, dwData);
	if (pEViews -> m_pViewsArray == NULL) {
		DELETE_OBJ (pEViews);
		return NULL;	
	}
	pEViews -> AddRef();
		
return pEViews;
}


CEnumViews :: CEnumViews (void)
{
	m_dwRefCnt = 0;
	m_iCurrent = 0;
	m_pViewsArray = NULL;
}


CEnumViews :: ~CEnumViews (void)
{
	DELETE_OBJ (m_pViewsArray);
}


// IEnumVARAINT methods -------------------------------------------------------
STDMETHODIMP CEnumViews :: Next (ULONG celt, VARIANT *rgvar, ULONG *pceltFetched)
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
		hr = m_pViewsArray -> GetViewDisp (m_iCurrent++, (LPVOID *)&V_DISPATCH(&rgvar[i]));
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


STDMETHODIMP CEnumViews :: Skip (ULONG celt)
{
	m_iCurrent += celt;
	if(m_iCurrent > Count())
		m_iCurrent = Count();

return (m_iCurrent == Count()) ? ResultFromScode (S_FALSE) : NOERROR;
}


STDMETHODIMP CEnumViews :: Reset (void)
{
	m_iCurrent = 0;

return NOERROR;
}


// Anlegen einer Kopie dieses Enumerators -------------------------------------
STDMETHODIMP CEnumViews :: Clone (LPENUMVARIANT *ppenum)
{
CEnumViews *penum = CEnumViews :: CreateInstance (m_pViewsArray);

	if (penum == NULL) 
		return ResultFromScode (E_OUTOFMEMORY);

	penum -> m_iCurrent = m_iCurrent;
	*ppenum = penum;

return NOERROR;
}


// IUnknown Methods -----------------------------------------------------------
STDMETHODIMP CEnumViews :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	if(riid != IID_IUnknown && riid != IID_IEnumVARIANT) {
		*ppv = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}
	*ppv = this;
	AddRef();

return NOERROR;
}


STDMETHODIMP_(ULONG) CEnumViews :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CEnumViews :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}

return m_dwRefCnt;
}

