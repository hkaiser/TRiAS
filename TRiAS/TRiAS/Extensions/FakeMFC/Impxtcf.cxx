// IXtensionCF - Implementation in der DLL ------------------------------------
// File: IMPXTCF.CXX

#include "fakemfcp.hxx"

#include "impxtcf.hxx"

// da wir eine Bibliothek generieren, müssen die CLSIID's explizit definiert werden
#include <xtsnguid.h>
#include <olectl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

// Count number of objects and number of locks --------------------------------
LONG g_cObj = 0;
LONG g_cLock = 0;

// jeder AddressRaum hat genau eine Instanz jeder Erweiterung -----------------
CTriasExtension *g_pTE = NULL;

// Konstruktor/Destruktor der ClassFactory ------------------------------------
CXtensionClassFactory :: CXtensionClassFactory (void)
{
	m_dwRefCnt = 0L;
}


CXtensionClassFactory :: ~CXtensionClassFactory (void)
{
}

// InterfaceMethods for VisModule ---------------------------------------------
STDMETHODIMP CXtensionClassFactory :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	*ppv = NULL;

// Any interface on this object is the object pointer.
	if (riid == IID_IUnknown || 
	    riid == IID_IClassFactory || riid == IID_IClassFactory2)
		*ppv = (LPVOID)this;

// If we actually assign an interface to ppv we need to AddRef it
// since we're returning a new pointer.
	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CXtensionClassFactory :: AddRef (void)
{
	return ++m_dwRefCnt;
}


STDMETHODIMP_(ULONG) CXtensionClassFactory :: Release (void)
{
ULONG cRefT;

	cRefT = --m_dwRefCnt;
	if (m_dwRefCnt == 0L)
        	delete this;

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
STDMETHODIMP CXtensionClassFactory :: CreateInstance (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	if (!g_fGlobalLic && !GetLicenseKey (NULL, 0))
		return ResultFromScode (CLASS_E_NOTLICENSED);

return CreateAnObject (punkOuter, riid, ppvObj);
}


// Objekt generieren, ohne nochmal nach einer Lizenz zu fragen ----------------
HRESULT CXtensionClassFactory :: CreateAnObject (LPUNKNOWN punkOuter, 
			REFIID riid, LPVOID FAR *ppvObj)
{
HRESULT hr = ResultFromScode(E_OUTOFMEMORY);

// Verify that if there is a controlling unknown it's asking for IUnknown
	if (punkOuter != NULL && !IsEqualIID (riid, IID_IUnknown))
		return ResultFromScode (E_NOINTERFACE);

// Create the object telling it a function to notify us when it's gone.
CSyncThread Sync (this);	// Thread safe !

	if (g_pTE == NULL) {			// erster Versuch
		g_pTE = NewExtension();		// erzeugen der Erwiterung

		if (g_pTE == NULL) return hr;

	// vollständige Initialisierung durchführen
		piInterlockedIncrement (&g_cObj);
		if (!g_pTE -> __FInit (punkOuter, ObjectDestroyed)) {
			hr = ResultFromScode (E_UNEXPECTED);
			DELETE_OBJ (g_pTE);
			return ResultFromScode (E_UNEXPECTED);
		}

	// Kill the object if initial creation or FInit failed.
		hr = g_pTE -> QueryInterface (riid, ppvObj);
		if (FAILED (hr)) {
			DELETE_OBJ (g_pTE);
		}
	} else
		hr = g_pTE -> QueryInterface (riid, ppvObj);

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
STDMETHODIMP CXtensionClassFactory :: LockServer (BOOL fLock)
{
	if (fLock)
		piInterlockedIncrement (&g_cLock);
	else
		piInterlockedDecrement (&g_cLock);

return NOERROR;
}


// *** IClassFactory2 mebers --------------------------------------------------
STDMETHODIMP CXtensionClassFactory :: GetLicInfo (LPLICINFO pLicInfo)
{
	if (NULL == pLicInfo)
		return ResultFromScode (E_POINTER);

	pLicInfo -> cbLicInfo = sizeof(LICINFO);

bool fLicensed = g_fGlobalLic || GetLicensed();

	pLicInfo -> fRuntimeKeyAvail = fLicensed;
	pLicInfo -> fLicVerified = fLicensed;

return NOERROR;
}

STDMETHODIMP CXtensionClassFactory :: RequestLicKey (DWORD, BSTR *pbstrKey)
{
#if !defined(WIN32) || defined(OLE2ANSI)
char szTemp[256];

	if ((!g_fGlobalLic && !GetLicensed()) || !GetLicenseKey (szTemp, 256))
		return ResultFromScode (CLASS_E_NOTLICENSED);

	*pbstrKey = SysAllocString (szTemp);
#else
WORD szTemp[256];

	if ((!g_fGlobalLic && !GetLicensed()) || !GetLicenseKey ((LPWSTR)szTemp, 256))
		return ResultFromScode (CLASS_E_NOTLICENSED);

	*pbstrKey = SysAllocString ((LPWSTR)szTemp);
#endif // WIN32

return (NULL != *pbstrKey) ? NOERROR : ResultFromScode (E_OUTOFMEMORY);
}


STDMETHODIMP CXtensionClassFactory :: CreateInstanceLic (LPUNKNOWN pUnkOuter,
		LPUNKNOWN pUnkReserved, REFIID riid, BSTR bstrKey,
		LPVOID *ppvObject)
{
#if !defined(WIN32) || defined(OLE2ANSI)
char szTemp[256];

	if ((!g_fGlobalLic && !GetLicensed()) || !GetLicenseKey (szTemp, 256))
		return ResultFromScode (CLASS_E_NOTLICENSED);

bool fMatch = (0 == memcmp (szTemp, bstrKey, lstrlen(szTemp)));

	if (!fMatch) return ResultFromScode (CLASS_E_NOTLICENSED);

// alles ok
	SetLicensed();

#else
bool fNotLicensed = false;

	if (!g_fGlobalLic && !GetLicensed())	// nicht global/lokal lizensiert
		fNotLicensed = true;	

	USES_CONVERSION;
	if (!SetLicensed (OLE2A(bstrKey)) && fNotLicensed)
		return ResultFromScode (CLASS_E_NOTLICENSED);
#endif // WIN32

	return CreateAnObject (pUnkOuter, riid, ppvObject);
}

