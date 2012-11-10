// TRiASPRV.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To merge the proxy/stub code into the object DLL, add the file 
//      dlldatax.c to the project.  Make sure precompiled headers 
//      are turned off for this file, and add _MERGE_PROXYSTUB to the 
//      defines for the project.  
//
//      If you are not running WinNT4.0 or Win95 with DCOM, then you
//      need to remove the following define from dlldatax.c
//      #define _WIN32_WINNT 0x0400
//
//      Further, if you are running MIDL without /Oicf switch, you also 
//      need to remove the following define from dlldatax.c.
//      #define USE_STUBLESS_PROXY
//
//      Modify the custom build rule for TRiASPRV.idl by adding the following 
//      files to the Outputs.
//          TRiASPRV_p.c
//          dlldata.c
//      To build a separate proxy/stub DLL, 
//      run nmake -f TRiASPRVps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "dlldatax.h"

#include <ospace/file/path.h>

#include "Strings.h"
//#include "TRiASPRV_i.c"
#include "TRiASOleDBSession.h"
#include "TRiASOleDBDataSource.h"
#include "SchemaRowsets.h"

#include "TRiASOleDBErrorLookup.h"
#include "TRiASQL/Parser.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TRiASOleDB, CTRiASOleDBSource)
	OBJECT_ENTRY(CLSID_TRiASOleDBErrorLookup, CTRiASOleDBErrorLookup)
	OBJECT_ENTRY(CLSID_Parser, cParser)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
// component category
// {A0690A28-FAF5-11d1-BAF5-080036DB0B03}
EXTERN_C const GUID __declspec(selectany) CATID_OGISDataProvider = {0xA0690A28,0xFAF5, 0x11D1,{0xBA,0xF5,0x08,0x00,0x36,0xDB,0x0B,0x03}};

namespace {
	bool LoadGlobalString(UINT uiID, OLECHAR *wpcBuffer)
	{
	CComBSTR bstr;

		if (0 == bstr.LoadString(uiID))
			return false;
		wcscpy(wpcBuffer, bstr);
		return true;
	}

	bool InitGlobalStrings()
	{
	// Provider friendly name
		if (!LoadGlobalString(IDS_PROVIDERFRIENDLYNAME, g_cbProviderFriendlyName)) return FALSE;
		if (!LoadGlobalString(IDS_TABLETERM, g_cbTableTerm)) return FALSE;

	// Provider name
	char cbName[_MAX_PATH];

		if (0 == GetModuleFileName(_Module.GetModuleInstance(), cbName, sizeof(cbName)))
			return FALSE;

	os_path path = os_string(cbName);

		USES_CONVERSION;
		wcscpy(g_cbProviderName, A2OLE(path.filename().c_str()));
		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    lpReserved;
#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return FALSE;
#endif
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_TRiASOleDB);
		InitGlobalStrings();
        DisableThreadLibraryCalls(hInstance);

#if defined(_DEBUG)
	// ggf. beim Hochfahren anhalten
	CRegKey key;

		if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
			ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
			ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
		{
		CRegKey cfgkey;

			if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config")))
			{
			DWORD dwHaltOnStartup = 0;

				cfgkey.QueryValue (dwHaltOnStartup, TEXT("HaltOnStartup"));
				_ASSERTE(0 == dwHaltOnStartup);
			}
		}
#endif // defined(_DEBUG)
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllCanUnloadNow() != S_OK)
        return S_FALSE;
#endif
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

///////////////////////////////////////////////////////////////////////////////
// ComponentCategory
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
    HRESULT hRes = PrxDllRegisterServer();
    if (FAILED(hRes))
        return hRes;
#endif
// registers component category
char cbBuffer[128];

	USES_CONVERSION;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_CATIDDESC, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;
	CreateComponentCategory (CATID_OGISDataProvider, A2OLE(cbBuffer));

// registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    PrxDllUnregisterServer();
#endif
	RemoveComponentCategory (CATID_OGISDataProvider);
    return _Module.UnregisterServer(TRUE);
}


