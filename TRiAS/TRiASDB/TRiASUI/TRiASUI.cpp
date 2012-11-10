// TRiASUI.cpp : Implementation of DLL Exports.


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
//		Modify the custom build rule for TRiASUI.idl by adding the following 
//		files to the Outputs.
//			TRiASUI_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f TRiASUIps.mk in the project directory.

#include "stdafx.h"

#if defined(_DEBUG)
#include <ospace/file/path.h>
#endif // _DEBUG

#include "resource.h"
#include "initguid.h"
#include "TRiASUI.h"
#include "dlldatax.h"

#include "TRiASUI_i.c"

#include "UIUtil.h"
#include "Strings.h"
#include "TRiASOptionDlg.h"

#include "EditFeatureDlg.h"
#include "EditFeatureParamDlg.h"

#ifdef _MERGE_PROXYSTUB
extern "C" DWORD g_dwFlags = 0L;
extern "C" HINSTANCE hProxyDll;
#endif

#if _TRiAS_VER < 0x0400
///////////////////////////////////////////////////////////////////////////////
// Version 4 emulieren
DWORD g_dwVer4 = 0;
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// 
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
// allgemeine Dialoge
	OBJECT_ENTRY(CLSID_TRiASOptionDlg, CTRiASOptionDlg)

// PropertyPages
	OBJECT_ENTRY(CLSID_EditFeatureDlg, CEditFeatureAtlDlg)
	OBJECT_ENTRY(CLSID_EditFeatureParamDlg, CEditFeatureParamAtlDlg)
END_OBJECT_MAP()

///////////////////////////////////////////////////////////////////////////////
//
static void PreCalcVersion (void);		// WindowsVersion ermitteln

class CTRiASUIApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CTRiASUIApp theApp;

BOOL CTRiASUIApp::InitInstance()
{
	_Module.Init(ObjectMap, m_hInstance);
	if (!CWinApp::InitInstance())
		return FALSE;

// den aktuellen Namen von TRiAS lesen
CRegKey key;

#ifdef _MERGE_PROXYSTUB
	g_dwFlags = 0L;
	hProxyDll = NULL;
#endif 

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
	{
	CRegKey cfgkey;

		if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config"))) {
		DWORD dwCount = _countof(g_cbTRiAS);

			if (ERROR_SUCCESS != cfgkey.QueryValue (g_cbTRiAS, TEXT("TRiASName"), &dwCount))
				_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

#if _TRiAS_VER < 0x0400
#if defined(_DEBUG)
			g_dwVer4 = 1;
#else
			g_dwVer4 = 0;
#endif // defined(_DEBUG)
			cfgkey.QueryValue(g_dwVer4, TEXT("FakeTRiAS4"));
#endif // _TRiAS_VER < 0x0400

#ifdef _MERGE_PROXYSTUB
		// erstmal feststellen, ob wirklich mut Proxies/Stubs gearbeitet werden soll
			cfgkey.QueryValue (g_dwFlags, TEXT("ProxyStub"));

		// jetzt evtl. ProxyStub initialisieren
			if (g_dwFlags)
				hProxyDll = m_hInstance;
#endif
		}
	} 
	else {
	// Standards verwenden
		_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	
	}

	PreCalcVersion();
	return TRUE;
}

int CTRiASUIApp::ExitInstance()
{
	_Module.Term();

#if defined(_DEBUG)
char cbBuffer[_MAX_PATH];

	::GetModuleFileName (m_hInstance, cbBuffer, sizeof(cbBuffer));

os_path path (cbBuffer);
os_string str (path.filename());

	TRACE1(TEXT("%s: exiting: \r\n"), str.c_str());
	if (_Module.GetLockCount() != 0) 
		TRACE1(TEXT("\tInfo: Global ATL lock count: %ld\r\n"), _Module.GetLockCount());
	
	TRACE0(TEXT("\t"));

HRESULT hr = AfxDllCanUnloadNow();

	if (S_OK != hr)
		TRACE1(TEXT("Info: AfxDllCanUnloadNow returns: 0x%lx\r\n"), hr);
#endif // _DEBUG

	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwFlags && S_OK != PrxDllCanUnloadNow())
		return S_FALSE;
#endif
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwFlags && S_OK == PrxDllGetClassObject(rclsid, riid, ppv))
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwFlags) {
		if (FAILED(PrxDllRegisterServer())) 
			return false;
	} 
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


/////////////////////////////////////////////////////////////////////////////
// WindowsVersion feststellen 
static bool s_fWin31 = false;
static bool s_fWin40 = false;
static bool s_fWin41 = false;	// Memphis (#HK970827)
static bool s_fWin50 = false;	// Cairo (#HK980223)
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
	s_fWin41 = false;
	s_fWin50 = false;

	if (dwVersion < ~0x7fffffff) {			// Windows NT
		s_fWinNT = true;
		if (LOBYTE(LOWORD(dwVersion)) == 3) {		// Major Version is 3 or greater
			if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
				s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 3) {
			s_fWin40 = true;	// NT4.0
			s_fWin31 = true;
		} else if (LOBYTE(LOWORD(dwVersion)) > 4) {
			s_fWin50 = true;	// NT5.0
			s_fWin40 = true;
			s_fWin31 = true;
		}
	} else if (LOBYTE(LOWORD(dwVersion)) < 4) {	// Win32s
		if (LOBYTE(LOWORD(dwVersion)) >= 3 &&		// Major Version is 3 or greater
		    HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin31 = true;
		s_fWin32s = true;
	} else {					// Chicago or Memphis
		if (HIBYTE(LOWORD(dwVersion)) >= 0x0a) 		// Minor Version is 0x0a or greater
			s_fWin41 = true;	// 4.10
		s_fWin31 = true;
		s_fWin40 = true;
	}
}

bool WINAPI IsWin31 (void) 
{ 
	return s_fWin31; 
}

bool WINAPI IsWin40 (void) 
{ 
	return s_fWin40; 
}

bool WINAPI IsWin41 (void) 
{ 
	return s_fWin41; 
}

bool WINAPI IsWin50 (void) 
{ 
	return s_fWin50; 
}

bool WINAPI IsWin32s (void) 
{ 
	return s_fWin32s; 
}

bool WINAPI IsWinNT (void) 
{ 
	return s_fWinNT; 
}

