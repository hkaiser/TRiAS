// GKCtf_COM.cpp : Implementation of DLL Exports.


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
//		Modify the custom build rule for GKCtf_COM.idl by adding the following 
//		files to the Outputs.
//			GKCtf_COM_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f GKCtf_COMps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "GKCtf_COM.h"
#include "dlldatax.h"

//#include "GKCtf_COM_i.c"
#include <TRiASDB_i.c>	// JG990120	needing _IID_ITRiASPropertyBase

#include "ComCat.h"
#include "GKBesselCoordTrans.h"
#include "GKKrassCoordTrans.h"
#include "GKEtrsCoordTrans.h"
#include "CTFExContext.h"

#include "Strings.h"
#include "GKPropExt.h"

#include <Esnecil.h>

///////////////////////////////////////////////////////////////////////////////
// Component category: 079639C3-3123-101C-BB62-00AA0018497C	
const CATID CATID_TRiASCoordsystem = {0x079639C3L,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

// {FE501AC0-ABD3-11d1-A066-0060975566B4}
extern "C" const CLSID CLSID_GKPropExt = {0xfe501ac0,0xabd3,0x11D1,{0xa0,0x66,0x00,0x60,0x97,0x55,0x66,0xb4}};

const IID IID_ICoordTransform = {0x0BDC3C18,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICTFExContext = {0x5FA91F05,0xA839,0x11D1,{0xA0,0x60,0x00,0x60,0x97,0x55,0x66,0xB4}};
const IID IID_ICoordTransformEvents = {0x764CA444,0xDFF6,0x11D1,{0x86,0x08,0x00,0x60,0x08,0x75,0x13,0x8A}};
const IID LIBID_GKCTF_COMLib = {0x727979C1,0xABAD,0x11D1,{0xA0,0x66,0x00,0x60,0x97,0x55,0x66,0xB4}};
const CLSID CLSID_GKBesselCoordTrans = {0x4EDBD3A1,0xAFA2,0x11d2,{0x8C,0xEC,0x00,0x60,0x97,0xA8,0xF3,0x84}};
const CLSID CLSID_GKKrassCoordTrans = {0x4EDBD3A4,0xAFA2,0x11d2,{0x8C,0xEC,0x00,0x60,0x97,0xA8,0xF3,0x84}};
const CLSID CLSID_GKEtrsCoordTrans = {0x089D69E1,0xB63E,0x11d2,{0x8C,0xEF,0x00,0x60,0x97,0xA8,0xF3,0x84}};
const CLSID CLSID_CTFExContext = {0xF2D244C1,0xB04F,0x11d2,{0x8C,0xEC,0x00,0x60,0x97,0xA8,0xF3,0x84}};

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_GKBesselCoordTrans, CGKBesselCoordTrans)
	OBJECT_ENTRY(CLSID_GKKrassCoordTrans, CGKKrassCoordTrans)
	OBJECT_ENTRY(CLSID_GKEtrsCoordTrans, CGKEtrsCoordTrans)
	OBJECT_ENTRY(CLSID_CTFExContext, CCTFExContext)
END_OBJECT_MAP()

class CGKCtf_COMApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CGKCtf_COMApp theApp;

BOOL CGKCtf_COMApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	hProxyDll = m_hInstance;
#endif
	_Module.Init(ObjectMap, m_hInstance);

	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_N_BREITE, g_cbNB, sizeof(g_cbNB)))
		return FALSE;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_S_BREITE, g_cbSB, sizeof(g_cbSB)))
		return FALSE;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_W_LAENGE, g_cbWL, sizeof(g_cbWL)))
		return FALSE;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_GEODAET_O_LAENGE, g_cbOL, sizeof(g_cbOL)))
		return FALSE;

	return CWinApp::InitInstance();
}

int CGKCtf_COMApp::ExitInstance()
{
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
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
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

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
BOOL IsLicencedGCO()
{
CEsnecil esnecil;

	return esnecil.VerifyOptions(CKIOPTION_GCOPRODUCTION);
}

BOOL IsLicencedInternally()
{
CEsnecil esnecil;

	return esnecil.VerifyOptions(CKIOPTION_INTERNAL_FEATURES);
}

STDAPI DllRegisterServer(void)
{
// registers component category
char cbBuffer[128];

	USES_CONVERSION;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_CATIDDESC, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;

HRESULT hr = CreateComponentCategory (CATID_TRiASCoordsystem, A2OLE(cbBuffer));

	if (FAILED(hr))	return hr;

// registers object, typelib and all interfaces in typelib
	_Module.UpdateRegistryFromResource (IDR_REGISTRY, true);
	if (IsLicencedGCO())
		_Module.UpdateRegistryFromResource (IDR_GCOCOORDS, true);
	if (IsLicencedInternally())
		_Module.UpdateRegistryFromResource (IDR_INTERNALCOORDS, true);
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
	_Module.UpdateRegistryFromResource (IDR_REGISTRY, false);
	_Module.UpdateRegistryFromResource (IDR_GCOCOORDS, false);
	_Module.UpdateRegistryFromResource (IDR_INTERNALCOORDS, false);
	RemoveComponentCategory (CATID_TRiASCoordsystem);
	return S_OK;
}

