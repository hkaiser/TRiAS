// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.03.2002 23:51:50 
//
// @doc
// @module MMPolyGIS.cpp | Definition of the <c CMMPolyGIS> class

// MMPolyGIS.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f MMPolyGISps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "MMPolyGIS.h"
#include "../MapCtrlImpl.h"
#include "MapPolyGIS.h"
//#include "dlldatax.h"

#include "MMPolyGIS_i.c"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
#endif // __XT && __DEXPROCS
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic = false;
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// 
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_MapPolyGIS, CMapPolyGIS)
END_OBJECT_MAP()

class CMMPolyGISApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CMMPolyGISApp theApp;

BOOL CMMPolyGISApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	hProxyDll = m_hInstance;
#endif

	_Module.Init(ObjectMap, m_hInstance);

#if defined(_DEBUG)
	{
	// globale Lizensierung überprüfen
	CRegKey regKey;
	
		if (ERROR_SUCCESS == regKey.Open(HKEY_CURRENT_USER, _T("Software"), KEY_READ) &&
			ERROR_SUCCESS == regKey.Open(regKey, REG_COMPANY_KEY, KEY_READ) &&
			ERROR_SUCCESS == regKey.Open(regKey, REG_PRODUCT_KEY, KEY_READ) &&
			ERROR_SUCCESS == regKey.Open(regKey, _T("Config")))
		{
		DWORD dwLic = 0;

			regKey.QueryValue(dwLic, _T("GlobalLicense"));
			g_fGlobalLic = dwLic ? true : false;
		}
	}
#endif // defined(_DEBUG

HMODULE hTrias = GetModuleHandle (NULL);

	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC"));
	return CWinApp::InitInstance();
}

int CMMPolyGISApp::ExitInstance()
{
	g_pDexExtensionProc = NULL;
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
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
	_Module.UnregisterServer();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf TRiAS (für Lizenzierung)
#if defined(_DEBUG)	// ansonsten inline
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
	_ASSERTE(NULL != g_pDexExtensionProc);
	return (*g_pDexExtensionProc)(w, l);
}
#endif // defined(_DEBUG)

