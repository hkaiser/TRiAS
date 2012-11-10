// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "begeodp.hxx"

#if !defined(WIN32)
#include <tchar.h>
#endif // WIN32

extern "C" char g_pDLLName[260] = "";
extern "C" HINSTANCE g_hInstance = NULL;

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

#if !defined(WIN32)

extern "C" 
int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, 
			WORD cbHeapSize, LPSTR lpszCmdLine) 
{
	if (cbHeapSize != 0) UnlockData (0);
	g_hInstance = hInst;
	
// Namen der DLL abfragen
	GetModuleFileName (hInst, g_pDLLName, sizeof(g_pDLLName));

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, TEXT("DEXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, TEXT("DEXNOTIFICATIONPROCEX"));
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else // WIN32

CComModule _Module;

#include "begeod.h"
#include <ctfpguid.h>
#include "ctfprpcf.hxx"		// ClassFactory für PropertyPage

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

///////////////////////////////////////////////////////////////////////////////
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	return SUCCEEDED(_Module.UpdateRegistryFromResource (IDR_REGISTRY, fRegister));
}

BEGIN_OBJECT_MAP(ObjectMap)
	// no ATL objects
END_OBJECT_MAP()

extern "C"
bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
	
		// Namen der DLL abfragen
			GetModuleFileName (hInst, g_pDLLName, sizeof(g_pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (TRIAS_MODULENAME);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, TEXT("DEXNOTIFICATIONPROCEX"));
#endif // __XT && __DEXPROCS
			DisableThreadLibraryCalls (hInst);
			_Module.Init (ObjectMap, hInst);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		_Module.Term();
		break;
	}

return true;
}

/*
 * DllGetClassObject
 *
 * Purpose:
 *  Provides an IClassFactory for a given CLSID that this DLL is
 *  registered to support.  
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
extern "C" 
HRESULT FAR PASCAL DllGetClassObject (
				REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv)
{
// abfragen und vergleichen des ClassID's
#if defined(ELLIPSE_BESSEL)
	if (!IsEqualIID (rclsid, CLSID_CTFBesselGeodProp))		// rufen der spezifischen Funktion
		return ResultFromScode(E_FAIL);
#elif defined(ELLIPSE_KRASSOVSKI)
	if (!IsEqualIID (rclsid, CLSID_CTFKrassGeodProp))		// rufen der spezifischen Funktion
		return ResultFromScode(E_FAIL);
#elif defined(ELLIPSE_ETRS89)
	if (!IsEqualIID (rclsid, CLSID_CTFEtrs89GeodProp))		// rufen der spezifischen Funktion
		return ResultFromScode(E_FAIL);
#else
#error "No Ellipse defined, Bessel assumed"
#endif

// Check that we can provide the interface
	if (!IsEqualIID(riid, IID_IUnknown) && 
	    !IsEqualIID(riid, IID_IClassFactory))
		return ResultFromScode(E_NOINTERFACE);

// Return our IClassFactory for Xtension objects
	*ppv = (LPVOID) new CCTFPropPageCF;
	if (*ppv == NULL)
		return ResultFromScode(E_OUTOFMEMORY);

// Don't forget to AddRef the object through any interface we return
	((LPUNKNOWN)(*ppv)) -> AddRef();

return NOERROR;
}


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
 *  bool            true if nothing is using us, false otherwise.
 */
extern LONG g_cObj;		// Anzahl der aktiven Objekte
extern LONG g_cLock;	// Anzahl der externen Locks

extern "C"
HRESULT PASCAL DllCanUnloadNow(void)
{
SCODE sc;

// Our answer is whether there are any object or locks
	sc = (g_cObj == 0L && g_cLock == 0) ? S_OK : S_FALSE;

return ResultFromScode(sc);
}


// DllRegisterServer - Adds entries to the system registry --------------------
extern "C"
HRESULT PASCAL DllRegisterServer (void)
{
	return ResultFromScode (UpdateRegistry(true) ? NOERROR : SELFREG_E_CLASS);
}


// DllUnregisterServer - Removes entries from the system registry -------------
extern "C"
HRESULT PASCAL DllUnregisterServer (void)
{
	return ResultFromScode (UpdateRegistry(false) ? NOERROR : SELFREG_E_CLASS);
}

/*
 * ObjectDestroyed
 *
 * Purpose:
 *  Function for the TriasXtension object to call when it gets destroyed.
 *  Since we're in a DLL we only track the number of objects here
 *  letting DllCanUnloadNow take care of the rest.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
void PASCAL ObjectDestroyed(void)
{
	piInterlockedDecrement (&g_cObj);
}

#endif // WIN32

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
extern "C" HWND __hWndM;
extern "C" UINT __DexCmd;
extern "C" UINT __DexNotify;

#if defined(__XT) && defined(__DEXPROCS)

// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
#if defined(_DEBUG)
extern "C"
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG

extern "C"
LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

return :: SendMessage (__hWndM, __DexNotify, w, l);
}

extern "C"
LRESULT PASCAL DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

return :: PostMessage (__hWndM, __DexNotify, w, l);
}

#endif // __XT && __DEXPROCS

