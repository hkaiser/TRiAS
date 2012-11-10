// CvrtAsc.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f CvrtAscps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "CvrtAsc.h"
#include "..\TransformLineOfTextEngine.h"

#include "CvrtAsc_i.c"
#include "ConvertAscCoords.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ConvertAscCoords, CConvertAscCoords)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_CvrtAsc);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

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
char cbBuffer[128];

	USES_CONVERSION;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_CATIDDESC, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CreateComponentCategory (CATID_TransformLineOfTextEngine, A2OLE(cbBuffer)));
 
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	RemoveComponentCategory (CATID_TransformLineOfTextEngine);
    return _Module.UnregisterServer(TRUE);
}


