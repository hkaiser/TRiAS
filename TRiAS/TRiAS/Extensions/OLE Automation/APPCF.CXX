// ClassFactory für CTriasApp -----------------------------------------
// File: APPCF.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Konstruktor/Destruktor -----------------------------------------------------
CTriasAppCF :: CTriasAppCF (CTriasApp *pApp)
{
	CONSTRUCT_TRACE(CTriasAppCF);
	
	m_dwRefCnt = 1;
	m_App = (_DApplication *)pApp;
}

CTriasAppCF :: ~CTriasAppCF (void)
{
	DESTRUCT_TRACE(CTriasAppCF);
}

LPCLASSFACTORY CTriasAppCF :: CreateInstance (CTriasApp *pApp)
{
	return new CTriasAppCF (pApp);
}

// IUnknown methods -----------------------------------------------------------
STDMETHODIMP CTriasAppCF :: QueryInterface (REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown || riid == IID_IClassFactory) {
		AddRef();
		*ppv = this;
		return NOERROR;
	}
	*ppv = NULL;

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CTriasAppCF :: AddRef (void)
{
	ADDREF_TRACE(CTriasAppCF, m_dwRefCnt);
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CTriasAppCF :: Release (void)
{
	RELEASE_TRACE(CTriasAppCF, m_dwRefCnt);
	if(--m_dwRefCnt == 0) {
		delete this;
		return 0;
	}
	return m_dwRefCnt;
}

// IClassFactoryMethods -------------------------------------------------------
// CreateInstance liefert immer wieder das eine existierende ApplicationObject 
STDMETHODIMP CTriasAppCF::CreateInstance (
	LPUNKNOWN punkOuter, REFIID riid, void **ppv)
{
	if (NULL != punkOuter)
		return CLASS_E_NOAGGREGATION;
	return m_App -> QueryInterface (riid, ppv);
}

STDMETHODIMP CTriasAppCF :: LockServer (BOOL fLock)
{
	return NOERROR;
}
