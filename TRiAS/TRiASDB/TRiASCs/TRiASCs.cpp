// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.01.2001 22:07:03 
//
// @doc
// @module TRiASCs.cpp | DLL specific functions and definitions

// Note: Proxy/Stub Information
//		To merge the proxy/stub code into the object DLL, add the file 
//		dlldatax.c to the project.  Make sure precompiled headers 
//		are turned off for this file, and add _MERGE_PROXYSTUB to the 
//		defines for the project.  
//
//		If you are not running WinNT4.0 or Win95 with DCOM, then you
//		need to remove the following define from dlldatax.c
//		#define _WIN32_WINNT 0x0400
//
//		Further, if you are running MIDL without /Oicf switch, you also 
//		need to remove the following define from dlldatax.c.
//		#define USE_STUBLESS_PROXY
//
//		Modify the custom build rule for TriasDB.idl by adding the following 
//		files to the Outputs.
//			TriasCS_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f TRiASCsps.mk in the project directory.

#include "stdafx.h"
#include "initguid.h"
#include "TRiASCsImpl.h"
#include "LibCTF/LibCTFImpl.h"

#include "Strings.h"
#include "dlldatax.h"

#include "EPSGMgr.h"
#include "TRiASCs_i.c"
#include "TRiASGeographicCS.h"
#include "TRiASProjectedCS.h"
#include "TRiASCoordSystem.h"
#include "TRiASCSDatumTransformation.h"
#include "TRiASCoordTransform.h"
#include "TRiASCSPpg.h"
#include "TRiASCSUI.h"
#include "TRiASGCSPpg.h"
#include "TRiASPCSPpg.h"
#include "TRiASCSSet.h"
#include "TRiASCSUIService.h"
#include "TRiASCSTransformService.h"
#include "TRiASCSDistanceService.h"
#if defined(_USE_WKTSERVICE)
#include "TRiASCSWktService.h"
#endif // defined(_USE_WKTSERVICE)
#include "EnumCoordSystemNames.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

#if defined(_DEBUG)
bool g_fGlobalLic = false;

class CGlobalLicense {
public:
	CGlobalLicense()
	{
		CRegKey regCfg;

		g_fGlobalLic = false;
		if (ERROR_SUCCESS == regCfg.Open (HKEY_CURRENT_USER, "Software", KEY_READ) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, REG_COMPANY_KEY, KEY_READ) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, REG_PRODUCT_KEY, KEY_READ) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, "Config"))
		{
		DWORD dwValue = 0;

			if (ERROR_SUCCESS == regCfg.QueryValue(dwValue, "GlobalLicense")) 
				g_fGlobalLic = dwValue ? true : false;
		}
	}
};

CGlobalLicense g_Lic;
#endif // defined(_DEBUG)

CComModule _Module;
CEPSGManager _EM;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TRiASCS, CTRiASCoordSystem)
	OBJECT_ENTRY(CLSID_TRiASCSGCS, CTRiASGeographicCS)
	OBJECT_ENTRY(CLSID_TRiASCSPCS, CTRiASProjectedCS)
	OBJECT_ENTRY(CLSID_TRiASCSTransform, CTRiASCoordTransform)
	OBJECT_ENTRY(CLSID_TRiASCSDatumTransformation, CTRiASCSDatumTransformation)
	OBJECT_ENTRY(CLSID_TRiASCSUI, CTRiASCSUI)
	OBJECT_ENTRY(CLSID_TRiASCSPpg, CTRiASCSPpg)
	OBJECT_ENTRY(CLSID_TRiASGCSPpg, CTRiASGCSPpg)
	OBJECT_ENTRY(CLSID_TRiASPCSPpg, CTRiASPCSPpg)
	OBJECT_ENTRY(CLSID_TRiASCSSet, CTRiASCSSet)
	OBJECT_ENTRY(CLSID_TRiASCSUIService, CTRiASCSUIService)
	OBJECT_ENTRY(CLSID_TRiASCSTransformService, CTRiASCSTransformService)
	OBJECT_ENTRY(CLSID_TRiASCSDistanceService, CTRiASCSDistanceService)
#if defined(_USE_WKTSERVICE)
	OBJECT_ENTRY(CLSID_TRiASCSWktService, CTRiASCSWktService)
#endif // defined(_USE_WKTSERVICE)
	OBJECT_ENTRY_NON_CREATEABLE(CEnumCoordSystemNames)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/) 
{
	if (dwReason == DLL_PROCESS_ATTACH) {
#ifdef _MERGE_PROXYSTUB
		hProxyDll = hInstance;
#endif 
		_Module.Init(ObjectMap, hInstance);
		_EM.LoadTables();
		DisableThreadLibraryCalls(hInstance);

	// diverse Stringresourcen laden
		if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_N_BREITE, g_cbNB, sizeof(g_cbNB)))
			return FALSE;
		if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_S_BREITE, g_cbSB, sizeof(g_cbSB)))
			return FALSE;
		if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_W_LAENGE, g_cbWL, sizeof(g_cbWL)))
			return FALSE;
		if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_O_LAENGE, g_cbOL, sizeof(g_cbOL)))
			return FALSE;
	} 
	else if (dwReason == DLL_PROCESS_DETACH) {
		_EM.UnloadTables();
		_Module.Term();
	}
	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void) 
{
#ifdef _MERGE_PROXYSTUB
	if (S_OK != PrxDllCanUnloadNow())
		return S_FALSE;
#endif
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) 
{
#ifdef _MERGE_PROXYSTUB
	if (S_OK == PrxDllGetClassObject(rclsid, riid, ppv))
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void) 
{
HRESULT hr = S_OK;

#ifdef _MERGE_PROXYSTUB
	hr = PrxDllRegisterServer();
	if (FAILED(hr)) 
		return hr;
#endif

// registers object, typelib and all interfaces in typelib
CTRiASCCSKeys keys (L"CoordinateSystems");

	if(!SUCCEEDED(hr = keys.Register()))
		return hr;

	if(!SUCCEEDED(hr = _Module.RegisterServer(TRUE)))
		return hr;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void) 
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif

CTRiASCCSKeys keys(L"CoordinateSystems");

	keys.Unregister();
	_Module.UnregisterServer();
	return S_OK;
}
