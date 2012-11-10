// FillMode.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include <string>
#include <initguid.h>
#include <vismguid.h>

#include <registrx.hxx>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" char g_pDLLName[_MAX_PATH] = "";
extern "C" HWND __hWndM = NULL;
extern "C" UINT __DexCmd = 0;
extern "C" HINSTANCE g_hInstance = NULL;

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

#if !defined(_NOVERSION)
static void PreCalcVersion (void);
#endif // !defined(_NOVERSION)

static AFX_EXTENSION_MODULE FillModeDLL = { NULL, NULL };

#if _MSC_VER >= 1000
void AFXAPI AfxLockGlobals(int nLockType);
void AFXAPI AfxUnlockGlobals(int nLockType);
#define CRIT_OBJECTFACTORYLIST  13
#endif // _MSC_VER

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("FILLMODE.VMD Initializing!\n");
		
	bool bRegister = !FillModeDLL.bInitialized;

		GetModuleFileName (hInstance, g_pDLLName, _MAX_PATH);
		g_hInstance = hInstance;
#if !defined(_NOVERSION)
		PreCalcVersion();
#endif // !defined(_NOVERSION)

	// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(FillModeDLL, hInstance)) {
			TRACE1("Could not init ExtensionModule %s\r\n", g_pDLLName);
			return false;   // failure
		}

	// Insert this DLL into the resource chain
	CDynLinkLibrary *pDLL = new CDynLinkLibrary(FillModeDLL);
		
		if (pDLL == NULL) {
			TRACE1("Out of memory in DLLInit of %s\r\n", g_pDLLName);
			return false;   // failure
		}
		pDLL -> m_bSystem = true;
			
	// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	HMODULE hTrias = GetModuleHandle (NULL);

		g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
#endif // __XT && __DEXPROCS
#if _MSC_VER >= 1000
		{
		// Register class factories in context of private module state
		bool bResult = true;

			if (bRegister) {
			// register this DLL's factories
				AfxLockGlobals(CRIT_OBJECTFACTORYLIST);
				for (COleObjectFactory *pFactory = pDLL->m_factoryList;
					 pFactory != NULL; pFactory = pFactory->m_pNextFactory)
				{
					// register any non-registered, non-doctemplate factories
					if (!pFactory->IsRegistered() &&
						pFactory->GetClassID() != CLSID_NULL && !pFactory->Register())
					{
						TRACE1("Could not init classFactory in %s\r\n", g_pDLLName);
						bResult = false;
					}
				}
				AfxUnlockGlobals(CRIT_OBJECTFACTORYLIST);
			}
			if (!bResult) return false;
		}
#endif //_MSC_VER
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("FILLMODE.VMD Terminating!\n");
		AfxTermExtensionModule(FillModeDLL);
	}
	return 1;   // ok
}

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
extern "C"
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (__hWndM) {		// von TRIAS initialisiert
		if (g_pDexExtensionProc)
			return (*g_pDexExtensionProc)(w, l);
		
		return :: SendMessage (__hWndM, __DexCmd, w, l);
	}

return false;
}
#endif // _DEBUG
#endif // __XT && __DEXPROCS

extern "C"
HRESULT _VMD_EXPORT FAR PASCAL DllGetClassObject (REFCLSID rclsid, REFIID riid, 
					          LPVOID FAR *ppv)
{
// zuerst MFC interne Abfragen
	AFX_MANAGE_STATE(AfxGetModuleState());
	return AfxDllGetClassObject (rclsid, riid, ppv);
}

extern "C" 
STDAPI _VMD_EXPORT DllCanUnloadNow(void)
{
// zuerst MFC befragen
	AFX_MANAGE_STATE(AfxGetModuleState());
	return AfxDllCanUnloadNow();
}

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

// DllRegisterServer - Adds entries to the system registry --------------------
const char g_cbProgID[] = TEXT("TRiAS.FillSignatures.1");
const char g_cbFillMode[] = TEXT("fillmode");

extern "C"
STDAPI _VMD_EXPORT DllRegisterServer (void)
{
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return SELFREG_E_CLASS;

string strKey = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\VisModules\\");

	strKey += g_cbProgID;

CCurrentUser regOldName (strKey.c_str());

	if (!regOldName.SetSZ (TEXT("OldName"), g_cbFillMode))
		return SELFREG_E_CLASS;

	return NOERROR;
}

// DllUnregisterServer - Removes entries from the system registry -------------
extern "C"
STDAPI _VMD_EXPORT DllUnregisterServer (void)
{
// MFC bedienen
	AFX_MANAGE_STATE(AfxGetModuleState());
	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

return NOERROR;
}

#if !defined(_NOVERSION)

// WindowsVersion feststellen -------------------------------------------------
static bool s_fWin31 = false;
static bool s_fWin40 = false;
static bool s_fWinNT = false;
static bool s_fWin32s = false;

static void PreCalcVersion (void)
{
// Initialise Version Info
DWORD dwVersion = GetVersion();

	s_fWin31 = false;
	s_fWinNT = false;
	s_fWin32s = false;
	s_fWin40 = false;

#if defined(WIN32)
	if (dwVersion < ~0x7fffffff) {			// Windows NT
		s_fWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 3) {
			s_fWin40 = true;	// NT4.0
			s_fWin31 = true;
		}
	} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin31 = true;
		s_fWin32s = true;
	} else {					// Chicago
		s_fWin31 = true;
		s_fWin40 = true;
	}
#else
	if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
	    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
		s_fWin31 = true;
#endif
}

bool IsWin31 (void) { return s_fWin31; }
bool IsWin40 (void) { return s_fWin40; }
bool IsWin32s (void) { return s_fWin32s; }
bool IsWinNT (void) { return s_fWinNT; }

#endif // !_NOVERSION
