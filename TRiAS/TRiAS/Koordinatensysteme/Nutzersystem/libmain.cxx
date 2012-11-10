// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "defaultp.hxx"
#define _TRIAS02_ENTRY
#include <registry.hxx>

char g_pDLLName[260];
extern "C" HINSTANCE g_hInstance = NULL;

#if defined(_USE_LEGACY_CODE)
#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
#endif // __XT && __DEXPROCS
#endif // _USE_LEGACY_CODE

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
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else // WIN32

CComModule _Module;

#include <comcat.h>

#include "dlldatax.h"

#include "default.h"
#include "Strings.h"

#include <TRiASDB_i.c>
// #include <TDBGeo_i.c>

// #include "ICTF_i.c"
#include "DefaultCoordTrans.h"
#include "ManageParamDlg.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
DWORD g_dwProxyStub = 0;
#endif

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ManageCoordParam, CManageParamDlg)
	OBJECT_ENTRY(CLSID_DefaultCoordTrans, CDefaultCoordTrans)
END_OBJECT_MAP()

EXTERN_C const IID IID_ICoordTransform = {0x0BDC3C18,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID LIBID_CoordTransLib = {0x0BDC3C09,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const CLSID CLSID_DefaultCoordTrans = {0x0BDC3C19,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const CLSID CLSID_ManageCoordParam = {0x95F58F37,0xDF2C,0x11D1,{0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A}};
//EXTERN_C const IID IID__DGMPoint = {0xCE361C90,0xB00C,0x11CF,{0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69}};

///////////////////////////////////////////////////////////////////////////////
// Component category: 079639C3-3123-101C-BB62-00AA0018497C	
const CATID CATID_TRiASCoordsystem = {0x079639C3L,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

///////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwProxyStub && PrxDllCanUnloadNow() != S_OK)
			return S_FALSE;
#endif
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwProxyStub && PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

HRESULT CreateComponentCategory (CATID catid, WCHAR *catDescription)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

// Make sure the HKCR\Component Categories\{..catid...}
// key is registered
CATEGORYINFO catinfo;

	catinfo.catid = catid;
	catinfo.lcid = GetUserDefaultLCID();

// Make sure the provided description is not too long.
// Only copy the first 127 characters if it is
int len = wcslen(catDescription);

	if (len > 127) len = 127;
    wcsncpy (catinfo.szDescription, catDescription, len);

// Make sure the description is null terminated
	catinfo.szDescription[len] = '\0';
    hr = pcr -> RegisterCategories (1, &catinfo);
	pcr -> Release();
	return hr;
}

HRESULT RemoveComponentCategory (REFCATID catid)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

    hr = pcr -> UnRegisterCategories (1, (CATID *)&catid);
	pcr -> Release();
	return hr;
}

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwProxyStub) {
	HRESULT hRes = PrxDllRegisterServer();
		
		if (FAILED(hRes)) return hRes;
	} else
		PrxDllUnregisterServer();
#endif
// registers component category
char cbBuffer[128];

	USES_CONVERSION;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_CATIDDESC, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;

HRESULT hr = CreateComponentCategory (CATID_TRiASCoordsystem, A2OLE(cbBuffer));

	if (FAILED(hr))	return hr;

// registers object, typelib and all interfaces in typelib
// AdminMode ?
CRegKey key;
DWORD dwSysFlags = 0;		// SysAdminMode

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY) &&
		ERROR_SUCCESS == key.Open(key, TEXT("Config")))
	{
		key.QueryValue (dwSysFlags, TEXT("SystemAdministration"));
	}
	if (dwSysFlags)
		_Module.UpdateRegistryFromResource (IDR_SOLDNER, true);

	_Module.UpdateRegistryFromResource (IDR_REGISTRY, true);
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwProxyStub) PrxDllUnregisterServer();
#endif
	_Module.UnregisterServer();

	_Module.UpdateRegistryFromResource (IDR_SOLDNER, false);
	_Module.UpdateRegistryFromResource (IDR_REGISTRY, false);
	RemoveComponentCategory (CATID_TRiASCoordsystem);
	return S_OK;
}

BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInst, dwReason, lpReserved))
		return FALSE;
#endif

	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
	
		// Namen der DLL abfragen
			GetModuleFileName (hInst, g_pDLLName, sizeof(g_pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(_USE_LEGACY_CODE)
#if defined(__XT) && defined(__DEXPROCS)
			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (
				GetModuleHandle (NULL), "DEXEXTENSIONPROC");
#endif // __XT && __DEXPROCS
			__DexCmd = RegisterWindowMessage (g_cbTriasExtensionMessage);
#endif // _USE_LEGACY_CODE

			DisableThreadLibraryCalls (hInst);
			_Module.Init (ObjectMap, hInst);

#ifdef _MERGE_PROXYSTUB
			{
			// erstmal feststellen, ob wirklich mut Proxies/Stubs gearbeitet werden soll
			CCurrentUser reg (TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"));

				g_dwProxyStub = 0L;
				reg.GetDWORD (TEXT("ProxyStub"), g_dwProxyStub);

			// jetzt evtl. ProxyStub initialisieren
				if (g_dwProxyStub)
					hProxyDll = hInst;
			}
#endif // _MERGE_PROXYSTUB
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
#ifdef _MERGE_PROXYSTUB
		hProxyDll = NULL;
#endif // _MERGE_PROXYSTUB
		_Module.Term();
		break;
	}

return true;
}

#endif // WIN32
#include "ManageParamDlg.h"

#if defined(_USE_LEGACY_CODE)

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
extern HWND __hWndM;
extern UINT __DexCmd;

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
extern "C" 
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG
#endif // __XT && __DEXPROCS

#endif // _USE_LEGACY_CODE
