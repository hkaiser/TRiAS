// GeodCtf_COM.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f GeodCtf_COMps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"

#include <ComCat.h>

#include "GeodCtf_COM.h"

//#include "GeodCtf_COM_i.c"
//#include <TDBGeo_i.c>
#include <TRiASDB_i.c>

#include "Strings.h"

#include "GeodBesselCoordTrans.h"
#include "GeodKrassCoordTrans.h"
#include "GeodEtrsCoordTrans.h"
#include "CTFExContext.h"

///////////////////////////////////////////////////////////////////////////////
// Component category: 079639C3-3123-101C-BB62-00AA0018497C	
const CATID CATID_TRiASCoordsystem = {0x079639C3L,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

const IID IID_ICoordTransform = {0x0BDC3C18,0x503F,0x11D1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_ICTFExContext = {0x5FA91F05,0xA839,0x11D1,{0xA0,0x60,0x00,0x60,0x97,0x55,0x66,0xB4}};
const IID IID_ICoordTransformEvents = {0x764CA444,0xDFF6,0x11D1,{0x86,0x08,0x00,0x60,0x08,0x75,0x13,0x8A}};
const IID LIBID_GEODCTFLib = {0xEA290595,0xA6A3,0x11D1,{0xA0,0x5D,0x00,0x60,0x97,0x55,0x66,0xB4}};
const CLSID CLSID_GeodBesselCoordTrans = {0xEA2905A3,0xA6A3,0x11D1,{0xA0,0x5D,0x00,0x60,0x97,0x55,0x66,0xB4}};
const CLSID CLSID_GeodKrassCoordTrans = {0xA8549CE0,0xA86D,0x11D1,{0xA0,0x60,0x00,0x60,0x97,0x55,0x66,0xB4}};
const CLSID CLSID_GeodEtrsCoordTrans = {0x085A4E71,0xA911,0x11D1,{0xA0,0x61,0x00,0x60,0x97,0x55,0x66,0xB4}};
const CLSID CLSID_CTFExContext = {0x5FA91F06,0xA839,0x11D1,{0xA0,0x60,0x00,0x60,0x97,0x55,0x66,0xB4}};
const CLSID CLSID_GeodCTFPropExt = {0xD3BFCD43,0xE31A,0x11D1,{0x86,0x0D,0x00,0x60,0x08,0x75,0x13,0x8A}};

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_GeodBesselCoordTrans, CGeodBesselCoordTrans)
	OBJECT_ENTRY(CLSID_GeodKrassCoordTrans, CGeodKrassCoordTrans)
	OBJECT_ENTRY(CLSID_GeodEtrsCoordTrans, CGeodEtrsCoordTrans)
	OBJECT_ENTRY(CLSID_CTFExContext, CCTFExContext)
END_OBJECT_MAP()

class CGeodCtf_COMApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CGeodCtf_COMApp theApp;

BOOL CGeodCtf_COMApp::InitInstance()
{
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

int CGeodCtf_COMApp::ExitInstance()
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
// registers component category
char cbBuffer[128];

	USES_CONVERSION;
	if (0 == ::LoadString (_Module.GetResourceInstance(), IDS_CATIDDESC, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;

HRESULT hr = CreateComponentCategory (CATID_TRiASCoordsystem, A2OLE(cbBuffer));

	if (FAILED(hr))	return hr;

// registers object, typelib and all interfaces in typelib
	_Module.UpdateRegistryFromResource (IDR_REGISTRY, true);
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	_Module.UpdateRegistryFromResource (IDR_REGISTRY, false);
	RemoveComponentCategory (CATID_TRiASCoordsystem);
	return S_OK;
}
