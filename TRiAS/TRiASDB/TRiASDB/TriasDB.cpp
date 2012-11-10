// TriasDB.cpp : Implementation of DLL Exports.


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
//			TriasDB_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f TriasDBps.mk in the project directory.

#include "stdafx.h"
#include <AfxDlgs.h>

#include "resource.h"

#include <comcat.h>
#include <ospace/file/path.h>

#include <CSPoint.h>
#include <CSRectGeom.h>

#include "Strings.h"
#include "dlldatax.h"
#include "TRiASDBGuids.h"

///////////////////////////////////////////////////////////////////////////////
// GUID's
#include <initguid.h>

#include <ictf.h>
#include <iobjman.h>		// ObjektManagement
#include <xtsnguid.h>

#include "TriasDB_i.c"
#include <ObjMan_i.c>

const IID IID_ICoordTransform = {0x0BDC3C18,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICoordTransformEvents = {0x764CA444,0xDFF6,0x11D1,{0x86,0x08,0x00,0x60,0x08,0x75,0x13,0x8A}};
const IID LIBID_CoordTransLib = {0x0BDC3C09,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const CLSID CLSID_DefaultCoordTrans = {0x0BDC3C19,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const CLSID CLSID_ManageCoordParam = {0x95F58F37,0xDF2C,0x11D1,{0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A}};
const IID IID_DTRiASBaseClass = {0x8DE4E3E0,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};

///////////////////////////////////////////////////////////////////////////////
// objects
#include "Wrapper.h"	// SmartIF's
#include "TRiASDBApp.h"	// application object

#if !defined(_USE_RUNTIME_OBJECTMAP)
#include "TRiASProject.h"
#include "TRiASView.h"
#include "TRiASViews.h"
#include "TRiASViewItems.h"
#include "TRiASViewItem.h"
#include "TRiASObjectsCollection.h"
#include "TRiASObjects.h"
#include "TRiASObjectsOperations.h"
#include "TRiASObject.h"
#include "TRiASFeatures.h"
#include "TRiASFeature.h"
#include "TRiASRelations.h"
#include "TRiASRelation.h"
#include "TRiASProjects.h"
#include "TRiASDBEngine.h"
#include "TRiASConnection.h"
#include "TRiASConnections.h"
#include "TRiASDatabase.h"
#include "TRiASDataServerRegEntries.h"

#include "TRiASProjectCTF.h"
#include "TRiASProjectStg.h"
#include "TRiASProperty.h"
#include "TRiASVariantProperty.h"
//#include "OpenWizPropExt.h"
#include "TRiASObjectHandleMap.h"
#include "GenObjectMap.h"
#include "DatabaseFeatureMap.h"
#include "TRiASConnectionFilters.h"
#include "TRiASConnectionFilter.h"

//#include "TRiASProperties.h"
//#include "TRiASDataServerRegEntry.h"
#include "TRiASSimpleObject.h"
#include "TRiASSimpleObjects.h"
#include "TRiASSimpleFeature.h"
#include "TRiASSimpleGeoFeature.h"
#include "TRiASSimpleFeatures.h"
#include "TRiASSimpleGeoFeatures.h"
#include "TRiASSimpleObjectsCollection.h"

#include "TRiASGuidFeature.h"
#include "ConnectionMoniker.h"
//#include "OleDocumentWrapper.h"
#endif // !defined(_USE_RUNTIME_OBJECTMAP)

///////////////////////////////////////////////////////////////////////////////
// {07963822-3123-101C-BB62-00AA0018497C}	
DEFINE_GUID(CLSID_TRiASMetaDocument, 0x07963822L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
//
#if defined(_USE_TRIAS_MESSAGES)

///////////////////////////////////////////////////////////////////////////////
// EinsprungRoutinen für TRiAS
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
extern "C" DEXDISPATCHPROC g_pDexDispatchProc = NULL;
extern "C" UINT __DexCmd = 0;
extern "C" UINT __DexNotify = 0;

#endif // _USE_TRIAS_MESSAGES

///////////////////////////////////////////////////////////////////////////////
// ComponentCategory
const CATID CATID_TRiASDBEngine = {0x079639C6,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

DWORD g_dwFlags = 0L;	// REG_USE_PROXYSTUB: use ProxyStub, REG_USE_PERFCOUNTERS: use PerfCounters

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

#if !defined(_USE_RUNTIME_OBJECTMAP)
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TRiASDBEngine, CTRiASDBEngine)
	OBJECT_ENTRY(CLSID_TRiASProject, CTRiASProject)
	OBJECT_ENTRY(CLSID_OleDocumentWrapper, COleDocumentWrapper)
	OBJECT_ENTRY(CLSID_TRiASConnection, CTRiASConnection)
	OBJECT_ENTRY(CLSID_TRiASDatabaseOnFile, CTRiASDatabaseOnFile)
	OBJECT_ENTRY(CLSID_TRiASDatabaseOnStg, CTRiASDatabaseOnStg)
	OBJECT_ENTRY(CLSID_TRiASCompatibleDatabase, CTRiASCompatibleDatabase)
	OBJECT_ENTRY(CLSID_TRiASView, CTRiASView)
	OBJECT_ENTRY(CLSID_TRiASViewItem, CTRiASViewItem)
	OBJECT_ENTRY(CLSID_TRiASObject, CTRiASObject)
	OBJECT_ENTRY(CLSID_TRiASFeature, CTRiASFeature)
	OBJECT_ENTRY(CLSID_TRiASRelation, CTRiASRelation)
	OBJECT_ENTRY(CLSID_TRiASDataServerRegEntries, CTRiASDataServerRegEntries)
	OBJECT_ENTRY(CLSID_TRiASObjectsCollection, CTRiASObjectsCollection)
	OBJECT_ENTRY(CLSID_TRiASProperty, CTRiASProperty)
	OBJECT_ENTRY(CLSID_TRiASVariantProperty, CTRiASVariantProperty)
	OBJECT_ENTRY(CLSID_TRiASAutoSaveProperty, CTRiASAutoSaveProperty)
	OBJECT_ENTRY(CLSID_TRiASProperties, CTRiASProperties)
	OBJECT_ENTRY(CLSID_TRiASObjectsOperations, CTRiASObjectsOperations)

// TRiAS-spezifische Objekte
	OBJECT_ENTRY(CLSID_TRiASSimpleObjects, CTRiASSimpleObjects)
	OBJECT_ENTRY(CLSID_TRiASSimpleObject, CTRiASSimpleObject)
	OBJECT_ENTRY(CLSID_TRiASSimpleFeatures, CTRiASSimpleFeatures)
	OBJECT_ENTRY(CLSID_TRiASSimpleFeature, CTRiASSimpleFeature)
	OBJECT_ENTRY(CLSID_TRiASSimpleGeoFeatures, CTRiASSimpleGeoFeatures)
	OBJECT_ENTRY(CLSID_TRiASSimpleGeoFeature, CTRiASSimpleGeoFeature)
	OBJECT_ENTRY(CLSID_TRiASSimpleObjectsCollection, CTRiASSimpleObjectsCollection)
	OBJECT_ENTRY(CLSID_TRiASGuidFeature, CTRiASGuidFeature)
	OBJECT_ENTRY(CLSID_TRiASConnectionFilters, CTRiASConnectionFilters)
	OBJECT_ENTRY(CLSID_TRiASConnectionFilter, CTRiASConnectionFilter)

// Singleton-Objekte
//	OBJECT_ENTRY(CLSID_OpenWizPropExt, COpenWizPropExt)
	OBJECT_ENTRY(CLSID_TRiASObjectHandleMap, CTRiASObjectHandleMap)
	OBJECT_ENTRY(CLSID_TRiASObjectsHandleMap, CTRiASObjectsHandleMap)
	OBJECT_ENTRY(CLSID_TRiASFeatureHandleMap, CTRiASFeatureHandleMap)

	OBJECT_ENTRY(CLSID_ConnectionMoniker, CConnectionMoniker)

// lediglich lokal verfügbare Objekte (sind nicht registriert)
	OBJECT_ENTRY(CLSID_TRiASCTFProperty, CTRiASCTFProperty)
	OBJECT_ENTRY(CLSID_TRiASCTFConnection, CTRiASCTFProperty)
	OBJECT_ENTRY(CLSID_TRiASStgProperty, CTRiASStgProperty)

// evtl. nicht als 'creatable' benötigte Objekte
	OBJECT_ENTRY(CLSID_GenObjectMap, CGenObjectMap)
	OBJECT_ENTRY(CLSID_DatabaseFeatureMap, CDatabaseFeatureMap)
	OBJECT_ENTRY(CLSID_TRiASConnections, CTRiASConnections)
	OBJECT_ENTRY(CLSID_TRiASProjects, CTRiASProjects)
	OBJECT_ENTRY(CLSID_TRiASViews, CTRiASViews)
	OBJECT_ENTRY(CLSID_TRiASViewItems, CTRiASViewItems)
	OBJECT_ENTRY(CLSID_TRiASObjects, CTRiASObjects)
	OBJECT_ENTRY(CLSID_TRiASFeatures, CTRiASFeatures)
	OBJECT_ENTRY(CLSID_TRiASRelations, CTRiASRelations)
//	OBJECT_ENTRY(CLSID_TRiASDataServerRegEntry, CTRiASDataServerRegEntry)
//	OBJECT_ENTRY(CLSID_OleDocumentWrapper, COleDocumentWrapper)
END_OBJECT_MAP()
#endif // !defined(_USE_RUNTIME_OBJECTMAP)

CLASSFACTORY_CACHE_BEGIN(ClassFactories)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSRectangleGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPoint)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASSimpleObject)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASObject)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASSimpleObjects)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASViewItem)
CLASSFACTORY_CACHE_END()

///////////////////////////////////////////////////////////////////////////////
// 
CTriasDBApp theApp;

BOOL CTriasDBApp::InitInstance()
{
#if defined(_USE_TRIAS_MESSAGES)
// bei TRiAS anhängen
HMODULE hTRiAS = GetModuleHandle (NULL);	// wir werden immer von TRiAS geladen

	_ASSERTE(NULL != hTRiAS);

	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTRiAS, TEXT("DEXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTRiAS, TEXT("DEXNOTIFICATIONPROCEX"));
	_ASSERTE(NULL != g_pDexExtensionProc && NULL != g_pDexNotificationProc);

// Registrieren der Messages
	__DexCmd = RegisterWindowMessage (TEXT("TriasExtensionMessage"));
	__DexNotify = RegisterWindowMessage (TEXT("TriasNotification"));
	_ASSERTE(NULL != __DexCmd && NULL != __DexNotify);
#endif // _USE_TRIAS_MESSAGES

// den aktuellen Namen von TRiAS lesen
CRegKey key;

	g_dwFlags = 0L;
#ifdef _MERGE_PROXYSTUB
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

#ifdef _MERGE_PROXYSTUB
		// erstmal feststellen, ob wirklich mut Proxies/Stubs gearbeitet werden soll
			cfgkey.QueryValue (g_dwFlags, TEXT("ProxyStub"));

		// jetzt evtl. ProxyStub initialisieren
			if (g_dwFlags & REG_USE_PROXYSTUB)
				hProxyDll = m_hInstance;
#endif
		// Performance Counter verwenden ?
		DWORD dwData = 0L;

			cfgkey.QueryValue (dwData, TEXT("UsePerfCounters"));
			if (dwData) g_dwFlags |= REG_USE_PERFCOUNTERS;

			dwData = 0L;
			cfgkey.QueryValue (dwData, TEXT("UseNovellTestCode"));
			if (dwData) g_dwFlags |= REG_USE_NOVELLTESTCODE;
		}

	CRegKey dirkey;

		if (ERROR_SUCCESS == dirkey.Open(key, TEXT("Directories"))) {
		DWORD dwCount = _countof(g_cbProjects);

			if (ERROR_SUCCESS != dirkey.QueryValue (g_cbProjects, TEXT("DefaultProjectDir"), &dwCount)) 
			{
				::GetModuleFileName (m_hInstance, g_cbProjects, _countof(g_cbProjects));	// Standard verwenden
			}
		}
	} 
	else {
	// Standards verwenden
		_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	
		::GetModuleFileName (m_hInstance, g_cbProjects, _countof(g_cbProjects));
	}

// Performance counter environment initialisieren
	StartPerfCounters();

// alle Objekte initialisieren
#if !defined(_USE_RUNTIME_OBJECTMAP)
	_Module.Init (ObjectMap, m_hInstance);
#else
	_Module.Init (GetRunTimeObjectMap(), m_hInstance);
#endif // !defined(_USE_RUNTIME_OBJECTMAP)
	ClassFactoryCacheInit(GetClassFactories());

	return CWinApp::InitInstance();
}

int CTriasDBApp::ExitInstance()
{
#if defined(_USE_TRIAS_MESSAGES)
	g_pDexExtensionProc = NULL;
	g_pDexNotificationProc = NULL;
#endif // _USE_TRIAS_MESSAGES

	ClassFactoryCacheTerm(GetClassFactories());
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
	if ((g_dwFlags & REG_USE_PROXYSTUB) && S_OK != PrxDllCanUnloadNow())
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
	if ((g_dwFlags & REG_USE_PROXYSTUB) && S_OK == PrxDllGetClassObject(rclsid, riid, ppv))
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
	if (g_dwFlags & REG_USE_PROXYSTUB) {
		if (FAILED(PrxDllRegisterServer())) 
			return false;
	} 
#endif
// registers component category
char cbBuffer[128];

	USES_CONVERSION;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_CATIDDESC, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CreateComponentCategory (CATID_TRiASDBEngine, A2OLE(cbBuffer)));

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
	RemoveComponentCategory (CATID_TRiASDBEngine);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// register/unregister performance counters
STDAPI DllRegisterPerfMon(void)
{
	return theApp.RegisterPerfCounters();		
}

STDAPI DllUnregisterPerfMon(void)
{
	return theApp.UnRegisterPerfCounters();
}

// WindowsVersion feststellen 
bool WINAPI IsWin31 (void) 
{ 
	return theApp.IsWin31(); 
}

bool WINAPI IsWin40 (void) 
{ 
	return theApp.IsWin40(); 
}

bool WINAPI IsWin41 (void) 
{ 
	return theApp.IsWin41(); 
}

bool WINAPI IsWin50 (void) 
{ 
	return theApp.IsWin50(); 
}

bool WINAPI IsWin32s (void) 
{ 
	return theApp.IsWin32s(); 
}

bool WINAPI IsWinNT (void) 
{ 
	return theApp.IsWinNT(); 
}

#if defined(_USE_TRIAS_MESSAGES)

///////////////////////////////////////////////////////////////////////////////
// EinsprungRoutinen für TRiAS-Commands

#if defined(_DEBUG)	// ansonsten inline
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	_ASSERTE(FALSE);		// zu zeitig gerufen
	return FALSE;
}
#endif // _DEBUG

LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	_ASSERTE(FALSE);		// zu zeitig gerufen
	return FALSE;
}

#endif // _USE_TRIAS_MESSAGES
