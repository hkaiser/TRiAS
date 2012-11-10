// PerfMon.cpp : Implementation of DLL Exports.


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
//		Modify the custom build rule for PerfMon.idl by adding the following 
//		files to the Outputs.
//			PerfMon_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f PerfMonps.mk in the project directory.

#include "stdafx.h"

#include <WinVersion.h>
#include <Com/PerfMonContext.h>

#include "resource.h"
#include "initguid.h"
#include "dlldatax.h"

#include "Wrapper.h"

#include "PerfData.h"
#include "PerfObject.h"
#include "PerfObjects.h"
#include "PerfCounterDefinition.h"
#include "PerfCounterDefinitions.h"
#include "PerfCounter.h"
#include "PerfCounters.h"
#include "PerfInstanceDefinition.h"
#include "PerfInstanceDefinitions.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CNamedObjTableModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_PerfContext, CPerfContext)
	OBJECT_ENTRY(CLSID_PerfObject, CPerfObject)
	OBJECT_ENTRY(CLSID_PerfObjects, CPerfObjects)
	OBJECT_ENTRY(CLSID_PerfCounterDefinition, CPerfCounterDefinition)
	OBJECT_ENTRY(CLSID_PerfCounterDefinitionCollect, CPerfCounterDefinitionCollect)
	OBJECT_ENTRY(CLSID_PerfCounterDefinitions, CPerfCounterDefinitions)
	OBJECT_ENTRY(CLSID_PerfCounterInt32, CPerfCounterInt32)
	OBJECT_ENTRY(CLSID_PerfCounterInt64, CPerfCounterInt64)
	OBJECT_ENTRY(CLSID_PerfCounters, CPerfCounters)
	OBJECT_ENTRY(CLSID_PerfInstanceDefinition, CPerfInstanceDefinition)
	OBJECT_ENTRY(CLSID_PerfInstanceDefinitions, CPerfInstanceDefinitions)
END_OBJECT_MAP()

class CPerfMonApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CPerfMonApp theApp;
#if defined(_DEBUG)
extern DWORD dwHaltOnStartup = false;
#endif // _DEBUG

BOOL CPerfMonApp::InitInstance()
{
CWinVersion Ver;

	if (!Ver.IsWinNT())	return FALSE;		// sinnvoll nur unter NT

#if defined(_DEBUG)
CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("TRiAS")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("InterTRiAS")))
	{
	CRegKey cfgkey;

		if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config"))) 
			cfgkey.QueryValue (dwHaltOnStartup, TEXT("PerfMonHaltOnStartup"));
	}
#endif // _DEBUG

#ifdef _MERGE_PROXYSTUB
	hProxyDll = m_hInstance;
#endif
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CPerfMonApp::ExitInstance()
{
CWinVersion Ver;

	if (!Ver.IsWinNT())	return 1;		// sinnvoll nur unter NT
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// API Funktion
//STDAPI PerfMonGetOrCreateContext (LPCOLESTR pcContext, IPerfContext **ppICtx)
//{
//	return NamedObjectGetReference(CLSID_PerfContext, pcContext, IID_IPerfContext, (LPVOID *)ppICtx);
//}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
CWinVersion Ver;

	if (!Ver.IsWinNT()) return S_OK;		// sinnvoll nur unter NT

#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
CWinVersion Ver;

	if (!Ver.IsWinNT()) return E_UNEXPECTED;		// sinnvoll nur unter NT

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
CWinVersion Ver;

	if (!Ver.IsWinNT()) return E_UNEXPECTED;		// sinnvoll nur unter NT

#ifdef _MERGE_PROXYSTUB
	HRESULT hRes = PrxDllRegisterServer();
	if (FAILED(hRes))
		return hRes;
#endif
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
CWinVersion Ver;

	if (!Ver.IsWinNT()) return E_UNEXPECTED;		// sinnvoll nur unter NT

#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif
	_Module.UnregisterServer();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// die einzige exportierte Funktion
namespace PerfMon {

_PERFMON_EXPORT 
HRESULT GetOrCreateContext (LPCOLESTR pcoleContext, IPerfContext **ppICtx)
{
	if (NULL == pcoleContext)
		return E_POINTER;

	COM_TRY {
	CComBSTR bstrMk("clsid:8FE61067-9A8D-11D2-9F08-006008447800:!");

		bstrMk += pcoleContext;
		THROW_FAILED_HRESULT(CoGetObject (bstrMk, NULL, __uuidof(IPerfContext), (LPVOID *)ppICtx));

	} COM_CATCH;
	return S_OK;
}

} // namespace PerfMon
