// CCTFPropPageCF - Implementation in der DLL ---------------------------------
// File: CTFPRPCF.CXX

#include "besslgkp.hxx"

#include <shlobj.h>
#include <ixtnext.hxx>

#include "ctfprpcf.hxx"
#include "ctfprop.hxx"

#include <initguid.h>
#include <dirisole.h>
#include <xtsnguid.h>
#include <ctfpguid.h>

// Count number of objects and number of locks --------------------------------
LONG g_cObj = 0;
LONG g_cLock = 0;

// Konstruktor/Destruktor der ClassFactory ------------------------------------
CCTFPropPageCF :: CCTFPropPageCF (void)
{
	m_dwRefCnt = 0L;
}


CCTFPropPageCF :: ~CCTFPropPageCF (void)
{
}

// InterfaceMethods for VisModule ---------------------------------------------
STDMETHODIMP CCTFPropPageCF :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	*ppv = NULL;

// Any interface on this object is the object pointer.
	if (riid == IID_IUnknown || riid == IID_IClassFactory)
		*ppv = (LPVOID)this;

// If we actually assign an interface to ppv we need to AddRef it
// since we're returning a new pointer.
	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CCTFPropPageCF :: AddRef (void)
{
	piInterlockedIncrement (&m_dwRefCnt);
	return m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CCTFPropPageCF :: Release (void)
{
	if (piInterlockedDecrement (&m_dwRefCnt) == 0L) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}


/*
 * CreateInstance
 *
 * Purpose:
 *  Instantiates a object that supports the ITriasXtension
 *  and IUnknown interfaces.  If the caller asks for a different
 *  interface than these two then we fail.
 *
 * Parameters:
 *  punkOuter       LPUNKNOWN to the controlling IUnknown if we are
 *                  being used in an aggregation.
 *  riid            REFIID identifying the interface the caller desires
 *                  to have for the new object.
 *  ppvObj          LPVOID FAR * in which to store the desired interface
 *                  pointer for the new object.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise contains E_NOINTERFACE
 *                  if we cannot support the requested interface.
 */
// Es existiert in jedem AddressRaum genau eine Instanz einer jeden Erweiterung
STDMETHODIMP CCTFPropPageCF :: CreateInstance (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	return CreateAnObject (punkOuter, riid, ppvObj);
}


// Objekt generieren, ohne nochmal nach einer Lizenz zu fragen ----------------
HRESULT CCTFPropPageCF :: CreateAnObject (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID FAR *ppvObj)
{
HRESULT hr = ResultFromScode(E_OUTOFMEMORY);

// Verify that if there is a controlling unknown it's asking for IUnknown
	if (punkOuter != NULL && !IsEqualIID (riid, IID_IUnknown))
		return ResultFromScode (E_NOINTERFACE);

// Create the object telling it a function to notify us when it's gone.
CCTFPropExt *pInfo = CCTFPropExt::CreateInstance (punkOuter, ObjectDestroyed);

	if (NULL == pInfo) return hr;

// Kill the object if initial creation or FInit failed.
	piInterlockedIncrement (&g_cObj);

	hr = pInfo -> QueryInterface (riid, ppvObj);
	pInfo -> Release();		// CreateInstance liefert mit RefCnt == 1 ab

return hr;
}


/*
 * LockServer
 *
 * Purpose:
 *  Increments or decrements the lock count of the DLL.  If the lock
 *  count goes to zero and there are no objects, the DLL is allowed
 *  to unload.  See DllCanUnloadNow.
 *
 * Parameters:
 *  fLock           BOOL specifying whether to increment or decrement the
 *                  lock count.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */
STDMETHODIMP CCTFPropPageCF :: LockServer (BOOL fLock)
{
	if (fLock)
		piInterlockedIncrement (&g_cLock);
	else
		piInterlockedDecrement (&g_cLock);

return NOERROR;
}


