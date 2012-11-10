// ObjektGeometrieCF - Implementation in der DLL ---------------------------------
// File: OBJGEOCF.CXX
// H. Kaiser

#include "GeometrP.hxx"

#include <xtsnaux.hxx>	// piInterlockedDecrement

#include "objgeocf.hxx"


// Count number of objects and number of locks --------------------------------
LONG g_cObj;
LONG g_cLock;

// Konstruktor/Destruktor der ClassFactory ------------------------------------
ObjektGeometrieCF :: ObjektGeometrieCF (void)
{
	m_dwRefCnt = 0L;
}


ObjektGeometrieCF :: ~ObjektGeometrieCF (void)
{
}

// InterfaceMethods for VisModule ---------------------------------------------
STDMETHODIMP ObjektGeometrieCF :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
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


STDMETHODIMP_(ULONG) ObjektGeometrieCF :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) ObjektGeometrieCF :: Release (void)
{
ULONG cRefT;

	cRefT = --m_dwRefCnt;
	if (m_dwRefCnt == 0L) delete this;

return cRefT;
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
STDMETHODIMP ObjektGeometrieCF :: CreateInstance (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	return CreateAnObject (punkOuter, riid, ppvObj);
}


// Objekt generieren, ohne nochmal nach einer Lizenz zu fragen ----------------
HRESULT ObjektGeometrieCF :: CreateAnObject (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID FAR *ppvObj)
{
HRESULT hr = ResultFromScode(E_OUTOFMEMORY);

// Verify that if there is a controlling unknown it's asking for IUnknown
	if (punkOuter != NULL && !IsEqualIID (riid, IID_IUnknown))
		return ResultFromScode (E_NOINTERFACE);

// Create the object telling it a function to notify us when it's gone.
ObjektGeometrie *pOG = ObjektGeometrie::CreateInstance (punkOuter, ObjectDestroyed);

	if (NULL == pOG) return hr;
	piInterlockedIncrement (&g_cObj);		// Objekt mitzählen

// Kill the object if initial creation or FInit failed.

	hr = pOG -> QueryInterface (riid, ppvObj);
	pOG -> Release();		// CreateInstance liefert mit RefCnt == 1 ab

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
STDMETHODIMP ObjektGeometrieCF :: LockServer (BOOL fLock)
{
	if (fLock)
		piInterlockedIncrement (&g_cLock);
	else
		piInterlockedDecrement (&g_cLock);

return NOERROR;
}


