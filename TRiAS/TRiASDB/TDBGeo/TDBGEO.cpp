// tdbgeo.cpp : Implementation of DLL Exports.


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
//		Modify the custom build rule for tdbgeo.idl by adding the following
//		files to the Outputs.
//			tdbgeo_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL,
//		run nmake -f tdbgeops.mk in the project directory.

#include "stdafx.h"
#include <Com/ClassFactoryCache.h>

#if defined(_DEBUG)
#include <crtdbg.h>
#endif // _DEBUG

#include "initguid.h"
#include "TDBGeoImpl.h"

#ifdef _MERGE_PROXYSTUB
#include "dlldatax.h"
#endif

#include "CSKGeomTypes.h"

#include <ospace/file/path.h>

#include "Strings.h"
#include "TDBGeoApp.h"

#include "tdbgeo_i.c"
#if !defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include "BaseGeometry_i.c"
#endif // !defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#include "TRiASCSPoint.h"
#include "TRiASCSPoints.h"
#include "TRiASCSRectangle.h"
#include "TRiASCSLine.h"
#include "TRiASCSPointGeometry.h"
#include "TRiASCSTextPointGeometry.h"
#include "TRiASCSPolyline.h"
#include "TRiASCSPolygon.h"
#include "TRiASCSBoundaryGeometry.h"
#include "TRiASCSGeometryCollection.h"
#include "TRiASCSVector.h"
#include "TRiASCSStorageService.h"
#include "TRiASCSOrientedPointGeometry.h"
#include "TRiASCSPointEnum.h"
#include "TRiASSpatialRelationService.h"

#if defined(_INCLUDE_OGC_OBJECTS)
///////////////////////////////////////////////////////////////////////////////
// OGC Objects
#include "OGCPoint.h"
#endif // defined(_INCLUDE_OGC_OBJECTS)

#include "GeometryMoniker.h"

extern "C" DWORD g_dwFlags = 0L;

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

const CLSID CLSID_TRiASCSPointInCol = { 0xcf8a8ff0, 0x3daf, 0x11d2, { 0x8c, 0x72, 0x0, 0x60, 0x97, 0xa8, 0xf3, 0x84 } };
// {8AE46797-080A-42ff-B21C-A9A47F0D372A}
const CLSID CLSID_TRiASCSPointInRect = { 0x8ae46797, 0x80a, 0x42ff, { 0xb2, 0x1c, 0xa9, 0xa4, 0x7f, 0xd, 0x37, 0x2a } };

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TRiASCSPoint, CTRiASCSPoint)
	OBJECT_ENTRY(CLSID_TRiASCSPoints, CTRiASCSPoints)
	OBJECT_ENTRY(CLSID_TRiASCSRectangleGeometry, CTRiASCSRectangleGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSLineGeometry, CTRiASCSLineGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSPointGeometry, CTRiASCSPointGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSTextPointGeometry, CTRiASCSTextPointGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSPolylineGeometry, CTRiASCSPolylineGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSPolygonGeometry, CTRiASCSPolygonGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSBoundaryGeometry, CTRiASCSBoundaryGeometry)
	OBJECT_ENTRY(CLSID_TRiASCSGeometryCollection, CTRiASCSGeometryCollection)
	OBJECT_ENTRY(CLSID_TRiASCSVector, CTRiASCSVector)
	OBJECT_ENTRY(CLSID_TRiASCSStorageService, CTRiASCSStorageService)
	OBJECT_ENTRY(CLSID_TRiASCSOrientedPointGeometry, CTRiASCSOrientedPointGeometry)
//	OBJECT_ENTRY(CLSID_TRiASCSPointInCol, CTRiASCSPointInCol)
//	OBJECT_ENTRY(CLSID_TRiASCSPointInRect, CTRiASCSPointInCsCoordTarget)
	OBJECT_ENTRY(CLSID_GeometryMoniker, CGeometryMoniker)
	OBJECT_ENTRY(CLSID_TRiASSpatialRelationService, CTRiASSpatialRelationService)
#if defined(_INCLUDE_OGC_OBJECTS)
	OBJECT_ENTRY(CLSID_OGCPoint, COGCPoint)
#endif // defined(_INCLUDE_OGC_OBJECTS)
END_OBJECT_MAP()

CLASSFACTORY_CACHE_BEGIN(ClassFactories)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPoint)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPoints)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSRectangleGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSLineGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPointGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSTextPointGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPolylineGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPolygonGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSGeometryCollection)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSOrientedPointGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSBoundaryGeometry)
CLASSFACTORY_CACHE_END()


///////////////////////////////////////////////////////////////////////////////
//
CTDBGeoApp theApp;

MapOfGUIDS	g_mapTRiAS2GDO;
MapOfGUIDS	g_mapGDO2TRiAS;

CClassFactoryMap::CClassFactories CClassFactoryMap::m_Factories;

BOOL CTDBGeoApp::InitInstance()
{
	ATLTRACE(_T("TDBGEO: (0x%08lx) Initializing... "), m_hInstance);

///////////////////////////////////////////////////////////////////////////////
// Geomedia - GUID's
	g_mapGDO2TRiAS[CLSID_GMPointFactory] = CLSID_TRiASCSPointGeometry;
	g_mapGDO2TRiAS[CLSID_GMLineFactory] = CLSID_TRiASCSLineGeometry;
	g_mapGDO2TRiAS[CLSID_GMPolylineFactory] = CLSID_TRiASCSPolylineGeometry;
	g_mapGDO2TRiAS[CLSID_GMRectangleFactory] = CLSID_TRiASCSRectangleGeometry;
	g_mapGDO2TRiAS[CLSID_GMPolygonFactory] = CLSID_TRiASCSPolygonGeometry;
	g_mapGDO2TRiAS[CLSID_GMBoundaryFactory] = CLSID_TRiASCSBoundaryGeometry;
	g_mapGDO2TRiAS[CLSID_GMGeometryCollectionFactory] = CLSID_TRiASCSGeometryCollection;
	g_mapGDO2TRiAS[CLSID_GMTextPointFactory] = CLSID_TRiASCSTextPointGeometry;
	g_mapGDO2TRiAS[CLSID_GMOrientedPointFactory] = CLSID_TRiASCSOrientedPointGeometry;

///////////////////////////////////////////////////////////////////////////////
// TRiAS - GUID's
	g_mapTRiAS2GDO[CLSID_TRiASCSPointGeometry] = CLSID_GMPointFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSLineGeometry] = CLSID_GMLineFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSPolylineGeometry] = CLSID_GMPolylineFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSRectangleGeometry] = CLSID_GMRectangleFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSPolygonGeometry] = CLSID_GMPolygonFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSBoundaryGeometry] = CLSID_GMBoundaryFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSGeometryCollection] = CLSID_GMGeometryCollectionFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSTextPointGeometry] = CLSID_GMTextPointFactory;
	g_mapTRiAS2GDO[CLSID_TRiASCSOrientedPointGeometry] = CLSID_GMOrientedPointFactory;

#ifdef _MERGE_PROXYSTUB
	g_dwFlags = 0L;
	hProxyDll = NULL;
#endif

CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
	{
	CRegKey cfgkey;

		if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config")))
		{
		DWORD dwCount = _countof(g_cbTRiAS);

			if (ERROR_SUCCESS != cfgkey.QueryValue (g_cbTRiAS, TEXT("TRiASName"), & dwCount))
				_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

#ifdef _MERGE_PROXYSTUB
		// erstmal feststellen, ob wirklich mit Proxies/Stubs gearbeitet werden soll
			cfgkey.QueryValue (g_dwFlags, TEXT("ProxyStub"));

		// jetzt evtl. ProxyStub initialisieren
			if (g_dwFlags)
				hProxyDll = m_hInstance;
#endif
		// Performance Counter verwenden ?
		DWORD dwData = 0L;

			cfgkey.QueryValue (dwData, TEXT("UsePerfCounters"));
			if (dwData) g_dwFlags |= REG_USE_PERFCOUNTERS;

#if defined(_DEBUG)
		// Debug flags auswerten
		DWORD dwMemDbg = _CrtSetDbgFlag (_CRTDBG_REPORT_FLAG);
		DWORD dwNewMemDbg = 0;

			if (ERROR_SUCCESS == cfgkey.QueryValue (dwNewMemDbg, TEXT("UseCrtMemDbgFlag")) && 
				dwNewMemDbg) 
			{
				if (ERROR_SUCCESS == cfgkey.QueryValue (dwNewMemDbg, TEXT("CrtMemDbgFlag")))
					_CrtSetDbgFlag (dwMemDbg|dwNewMemDbg);
			}
#endif // defined(_DEBUG)
		}
	}
	else {
	// Standards verwenden
		_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);
	}

// Performance counter environment initialisieren
	StartPerfCounters();

	_Module.Init(ObjectMap, m_hInstance);
	ClassFactoryCacheInit (GetClassFactories());
	if (!CWinApp::InitInstance())
		return FALSE;

	ATLTRACE(_T("OK\n"));
	return TRUE;
}

int CTDBGeoApp::ExitInstance()
{
	StopPerfCounters();

// classfactories freigeben
	CClassFactoryMap::ClassFactoryCacheTerm();
	ClassFactoryCacheTerm (GetClassFactories());

	_Module.Term();

	g_mapTRiAS2GDO.clear();
	g_mapGDO2TRiAS.clear();

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
	return (AfxDllCanUnloadNow() == S_OK && _Module.GetLockCount() == 0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID * ppv)
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
// register/unregister performance counters
extern "C" __declspec(dllexport)
int __cdecl DllRegisterPerfMon(void)
{
	return theApp.RegisterPerfCounters();
}

extern "C" __declspec(dllexport)
int __cdecl DllUnregisterPerfMon(void)
{
	return theApp.UnRegisterPerfCounters();
}
