// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:41:04 
//
// @doc
// @module TRiASNativeDB.cpp | Implementation of DLL Exports.

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
//      Modify the custom build rule for TRiASNativeDB.idl by adding the following 
//      files to the Outputs.
//          TRiASNativeDB_p.c
//          dlldata.c
//      To build a separate proxy/stub DLL, 
//      run nmake -f TRiASNativeDBps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"

#include <initguid.h>
#include <dirisole.h>

#include "TRiASNativeDB.h"
#include "dlldatax.h"

#include "TRiASNativeDB_i.c"

#include "TRiASNativeDataSource.h"
#include "TRiASNativeObject.h"
#include "TRiASNativeObjects.h"
#include "TRiASNativeIdent.h"
#include "TRiASNativeIdents.h"
#include "TRiASNativeAttribute.h"
#include "TRiASNativeAttributes.h"
#include "TRiASNativeObjectsOperations.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TRiASNativeDataSource, CTRiASNativeDataSource)
	OBJECT_ENTRY(CLSID_TRiASNativeObject, CTRiASNativeObject)
	OBJECT_ENTRY(CLSID_TRiASNativeIdent, CTRiASNativeIdent)
	OBJECT_ENTRY(CLSID_TRiASNativeAttribute, CTRiASNativeAttribute)
	OBJECT_ENTRY(CLSID_TRiASNativeObjectsOperations, CTRiASNativeObjectsOperations)
//	OBJECT_ENTRY(CLSID_TRiASNativeIdents, CTRiASNativeIdents)
//	OBJECT_ENTRY(CLSID_TRiASNativeAttributes, CTRiASNativeAttributes)
//	OBJECT_ENTRY(CLSID_TRiASNativeObjects, CTRiASNativeObjects)
END_OBJECT_MAP()

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
        _Module.Init(ObjectMap, hInstance, &LIBID_TRiASNativeDB);
        DisableThreadLibraryCalls(hInstance);

	// Init TRiAS01
	UINT uiDexCmd = ::RegisterWindowMessage ("TriasExtensionMessage");
	UINT uiDexNfy = ::RegisterWindowMessage ("TriasNotification");
	UINT uiDexxCmd = ::RegisterWindowMessage ("TriasCPPExtensionMessage");

		::InitTrias01 (NULL, uiDexCmd, uiDexNfy, uiDexxCmd);
		::SetCopyrightFlag (FALSE);
		::SetStartMode (0);
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

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hRes = PrxDllRegisterServer();
    if (FAILED(hRes))
        return hRes;
#endif
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
    return _Module.UnregisterServer(TRUE);
}
