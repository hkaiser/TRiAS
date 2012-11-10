// Helper.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f Helperps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "Helper.h"

#include "Helper_i.c"
#include "RegExpr.h"
#include "StringPair.h"
#include "CookieHelper.h"
#include "MatchPlainExact.h"
#include "MatchRegExprExakt.h"
#include "MatchFuzzy.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ParseRegularExpression, CRegExpr)
	OBJECT_ENTRY(CLSID_ParseStringPairs, CStringPairs)

	OBJECT_ENTRY(CLSID_CookieHelper, CCookieHelper)

// MatchingObjects
	OBJECT_ENTRY(CLSID_MatchPlainTextExakt, CMatchPlainTextExakt)
	OBJECT_ENTRY(CLSID_MatchRegExprExakt, CMatchRegExprExakt)
	OBJECT_ENTRY(CLSID_MatchFuzzy, CMatchFuzzy)
END_OBJECT_MAP()

class CHelperApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CHelperApp theApp;

BOOL CHelperApp::InitInstance()
{
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CHelperApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}


