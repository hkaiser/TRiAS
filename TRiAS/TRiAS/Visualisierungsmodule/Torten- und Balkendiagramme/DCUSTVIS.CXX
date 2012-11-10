// ICustomVisualisation - Implementation in der DLL ---------------------------
// File: DCUSTVIS.CXX

#include "tortenp.hxx"
// Must do this once in the entire build or we can't define our own GUIDs
#define INITGUIDS

#include <icustom.hxx>
#include <vismguid.h>

#include "impcustm.hxx"
#include "dcustvis.hxx"
#include "tortenid.h"		// CLSID definieren
#include "tortenr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Count number of objects and number of locks.
ULONG g_cObj = 0;
ULONG g_cLock = 0;


// Konstruktor/Destruktor der ClassFactory ------------------------------------
CVisModuleClassFactory :: CVisModuleClassFactory (void)
{
	m_cRef=0L;
}


CVisModuleClassFactory :: ~CVisModuleClassFactory (void)
{
}

// InterfaceMethods for VisModule ---------------------------------------------
STDMETHODIMP CVisModuleClassFactory :: QueryInterface (REFIID riid, LPVOID FAR *ppv)
{
	*ppv=NULL;

// Any interface on this object is the object pointer.
	if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
		*ppv = (LPVOID)this;

/*
 * If we actually assign an interface to ppv we need to AddRef it
 * since we're returning a new pointer.
 */
	if (*ppv != NULL) {
		((LPUNKNOWN)*ppv) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}


STDMETHODIMP_(ULONG) CVisModuleClassFactory :: AddRef (void)
{
	return ++m_cRef;
}


STDMETHODIMP_(ULONG) CVisModuleClassFactory :: Release (void)
{
ULONG cRefT;

	cRefT = --m_cRef;

	if (m_cRef == 0L)
        	delete this;

return cRefT;
}


/*
 * CreateInstance
 *
 * Purpose:
 *  Instantiates a Koala object that supports the IPersist
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

STDMETHODIMP CVisModuleClassFactory :: CreateInstance (LPUNKNOWN punkOuter, 
						       REFIID riid, LPVOID FAR *ppvObj)
{
LPCVisModule pObj;
HRESULT hr = ResultFromScode(E_OUTOFMEMORY);

	*ppvObj=NULL;

// Verify that if there is a controlling unknown it's asking for IUnknown
	if (punkOuter != NULL && !IsEqualIID(riid, IID_IUnknown))
		return ResultFromScode(E_NOINTERFACE);

// Create the object telling it a function to notify us when it's gone.
	pObj = new CVisModule (punkOuter, ObjectDestroyed);
	if (pObj == NULL) return hr;

	if (pObj -> FInit())
		hr = pObj -> QueryInterface (riid, ppvObj);

// Kill the object if initial creation or FInit failed.
	if (FAILED (hr))
		delete pObj;
	else
		g_cObj++;

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

STDMETHODIMP CVisModuleClassFactory :: LockServer (BOOL fLock)
{
	if (fLock)
		g_cLock++;
	else
		g_cLock--;

return NOERROR;
}


extern "C" char FAR g_pDLLName[_MAX_PATH] = "";
extern "C" HWND __hWndM = 0;

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
#endif // __XT && __DEXPROCS

extern "C" {

#if !defined(WIN32)

/*
 * LibMain
 *
 * Purpose:
 *  DLL-specific entry point called from LibEntry.
 *
 * Parameters:
 *  hInst           HINSTANCE instance of the DLL.
 *  wDataSeg        WORD segment selector of the DLL's data segment.
 *  wHeapSize       WORD byte count of the heap.
 *  lpCmdLine       LPSTR to command line used to start the module.
 *
 * Return Value:
 *  HANDLE          Instance handle of the DLL.
 *
 */

HINSTANCE PASCAL LibMain (HINSTANCE hInst, WORD /*wDataSeg*/, 
			   WORD cbHeapSize, LPSTR /*lpCmdLine*/)
{
	if (cbHeapSize != NULL)
		UnlockData(0);

	GetModuleFileName (hInst, g_pDLLName, _MAX_PATH);

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
#endif // __XT && __DEXPROCS

return hInst;
}

/*
 * _WEP
 *
 * Purpose:
 *  Required DLL Exit function.  Does nothing.
 *
 * Parameters:
 *  bSystemExit     BOOL indicating if the system is being shut
 *                  down or the DLL has just been unloaded.
 *
 * Return Value:
 *  void
 *
 */

void FAR PASCAL _WEP(int /*bSystemExit*/)
{
}

#else

HINSTANCE g_hInstance = NULL;

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			GetModuleFileName (hInst, g_pDLLName, _MAX_PATH);
			g_hInstance = hInst;

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (NULL);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, "DEXEXTENSIONPROC2");
#endif // __XT && __DEXPROCS
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

return true;
}

#endif

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)

// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	if (__hWndM) 	// von TRIAS initialisiert
		return :: SendMessage (__hWndM, __DexCmd, w, l);

	TX_ASSERT(NULL != __hWndM);
	return FALSE;
}

LRESULT WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	if (__hWndM) 	// von TRIAS initialisiert
		return :: SendMessage (__hWndM, __DexCmd, w, l);

	TX_ASSERT(NULL != __hWndM);
	return FALSE;
}
#endif // _DEBUG
#endif // __XT && __DEXPROCS

} // extern "C"




/*
 * DllGetClassObject
 *
 * Purpose:
 *  Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  This DLL is placed under the CLSID
 *  in the registration database as the InProcServer.
 *
 * Parameters:
 *  clsID           REFCLSID that identifies the class factory desired.
 *                  Since this parameter is passed this DLL can handle
 *                  any number of objects simply by returning different
 *                  class factories here for different CLSIDs.
 *
 *  riid            REFIID specifying the interface the caller wants
 *                  on the class object, usually IID_ClassFactory.
 *
 *  ppv             LPVOID FAR * in which to return the interface pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, otherwise contains an error SCODE.
 */

extern "C" {

HRESULT _VMD_EXPORT FAR PASCAL DllGetClassObject (REFCLSID rclsid, REFIID riid, 
					       LPVOID FAR *ppv)
{
	if (!IsEqualCLSID (rclsid, CLSID_GraphVM))
		return ResultFromScode(E_FAIL);

// Check that we can provide the interface
	if (!IsEqualIID (riid, IID_IUnknown) && !IsEqualIID(riid, IID_IClassFactory))
		return ResultFromScode(E_NOINTERFACE);

// Return our IClassFactory for Koala objects
	*ppv = (LPVOID)new CVisModuleClassFactory();

	if (*ppv == NULL)
		return ResultFromScode(E_OUTOFMEMORY);

// Don't forget to AddRef the object through any interface we return
	((LPUNKNOWN)(*ppv)) -> AddRef();

return NOERROR;
}

} // extern "C" 



/*
 * DllCanUnloadNow
 *
 * Purpose:
 *  Answers if the DLL can be freed, that is, if there are no
 *  references to anything this DLL provides.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if nothing is using us, FALSE otherwise.
 */

extern "C" {

STDAPI DllCanUnloadNow(void)
{
SCODE   sc;

// Our answer is whether there are any object or locks
	sc = (g_cObj == 0L && g_cLock == 0) ? S_OK : S_FALSE;

return ResultFromScode(sc);
}

} // extern "C"


/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the Koala object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here
 *  letting DllCanUnloadNow take care of the rest.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

extern "C" {

void FAR PASCAL ObjectDestroyed(void)
{
	g_cObj--;
}

} // extern "C" 


#if defined(WIN32)

#if !defined(_OLECTL_H)
/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer/DllUnregisterServer status codes

#define SELFREG_E_FIRST    MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
#define SELFREG_E_LAST     MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)
#define SELFREG_S_FIRST    MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x0200)
#define SELFREG_S_LAST     MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x020F)

#define SELFREG_E_TYPELIB           (SELFREG_E_FIRST+0)
// failed to register/unregister type library

#define SELFREG_E_CLASS             (SELFREG_E_FIRST+1)
// failed to register/unregister class
#endif _OLECTL_H

bool RegisterVisModule (REFCLSID rclsid, LPCTSTR pcProgID, LPCTSTR pcOldName,
						HINSTANCE hInstance, UINT uiName, DWORD dwObjType);
bool UnRegisterVisModule (REFCLSID rclsid, LPCTSTR pcProgID);

// DllRegisterServer - Adds entries to the system registry --------------------
extern "C"
STDAPI _VMD_EXPORT DllRegisterServer (void)
{
	if (!RegisterVisModule (CLSID_GraphVM, TEXT("TRiAS.StatGraphics.1"), TEXT("torten"),
				g_hInstance, IDS_LONGCLASSNAME, OTPunkt|OTLinie|OTFlaeche))
		return SELFREG_E_CLASS;

return S_OK;
}

// DllUnregisterServer - Removes entries from the system registry -------------
extern "C"
STDAPI _VMD_EXPORT DllUnregisterServer (void)
{
	if (!UnRegisterVisModule (CLSID_GraphVM, "TRiAS.StatGraphics.1"))
		return SELFREG_E_CLASS;

return S_OK;
}

#endif // WIN32


