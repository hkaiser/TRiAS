// TRiASGM.cpp : Implementation of DLL Exports.


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
//		Modify the custom build rule for TRiASGM.idl by adding the following 
//		files to the Outputs.
//			TRiASGM_p.c
//			dlldata.c
//		To build a separate proxy/stub DLL, 
//		run nmake -f TRiASGMps.mk in the project directory.

#include "stdafx.h"

#include "Strings.h"
#include "TRiASGMR.h"
#include "initguid.h"

#include <CSKGeomTypes.h>

#include "TRiASGM.h"
#include <VisInfo.h>
#include <VisInfoInterfaces.h>

#include "dlldatax.h"

#include <VisInfo_i.c>
#include <VisInfoInterfaces_i.c>
#include "TRiASGM_i.c"

#include "RecordsetGenerator.h"
#include "ViewRecordsetGenerator.h"
#include "RecordsetSource.h"
#include "TRiASSourceInfo.h"
#include "TRiASVisInfoObj.h"

DEFINE_GUID(CLSID_GDOFrameWork, 0x55692ac0, 0xd99, 0x11d1, 0x92, 0x7, 0x0, 0x60, 0x97, 0x38, 0x31, 0x87);
DEFINE_GUID(IID_GDatabase,0x6946F650,0x78F6,0x11cf,0x83,0xFC,0x08,0x00,0x36,0x83,0x03,0x02);
DEFINE_GUID(IID_GRecordset,0xBCBD18C0,0x72D2,0x11cf,0x83,0x57,0x08,0x00,0x36,0x01,0xE5,0xF9);

DEFINE_GUID(CLSID_InMemoryRecordset,0x3DCB2382,0x3BF0,0x11D1,0x92,0x11,0x00,0x60,0x97,0x38,0x31,0x87);
DEFINE_GUID(IID_IInMemoryRecordset,0x3DCB2383,0x3BF0,0x11D1,0x92,0x11,0x00,0x60,0x97,0x38,0x31,0x87);

DEFINE_GUID(IID_IGMProjSpace,0x803E6BF0L,0xB312,0x11CE,0x96,0x4D,0x08,0x00,0x36,0x01,0xC1,0xAF);
DEFINE_GUID(IID_IGMGeogSpace,0x76416DE0L,0xC82D,0x11CE,0x96,0x53,0x08,0x00,0x36,0x01,0xC1,0xAF);
DEFINE_GUID(IID_IGMRefSpaceMgr,0xC85D2720L,0x49A1,0x11CE,0x9C,0xB5,0x08,0x00,0x36,0x01,0xC1,0xAF);

DEFINE_GUID(CLSID_CoordSystem,0xF9796220L,0x1876,0x11CE,0x9C,0xB5,0x08,0x00,0x36,0x01,0xC1,0xAF);
DEFINE_GUID(IID_IGMCoordSystem,0xA94CD060L,0x33DF,0x11CE,0x9C,0xB5,0x08,0x00,0x36,0x01,0xC1,0xAF);

const IID IID_DTRiASBaseClass = {0x8DE4E3E0,0x4D53,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

// lokale Funktionen
static void PreLoadStrings();

///////////////////////////////////////////////////////////////////////////////
//
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_OKSRecordsetGenerator, COKSRecordsetGenerator)
	OBJECT_ENTRY(CLSID_ViewRecordsetGenerator, CViewRecordsetGenerator)
	OBJECT_ENTRY(CLSID_RecordsetSource, CRecordsetSource)
	OBJECT_ENTRY(CLSID_TRiASSourceInfo, CTRiASSourceInfo)

	OBJECT_ENTRY(CLSID_TRiASDefaultVisInfo, CVisInfoObject)
	OBJECT_ENTRY(CLSID_TRiASPointVisInfo, CPVisInfoObject)
	OBJECT_ENTRY(CLSID_TRiASLineVisInfo, CLVisInfoObject)
	OBJECT_ENTRY(CLSID_TRiASAreaVisInfo, CFVisInfoObject)
	OBJECT_ENTRY(CLSID_TRiASTextVisInfo, CTVisInfoObject)
END_OBJECT_MAP()

class CTRiASGMApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CTRiASGMApp theApp;

BOOL CTRiASGMApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	hProxyDll = m_hInstance;
#endif
	_Module.Init(ObjectMap, m_hInstance);

// ResourceDLL besorgen
TCHAR cbPathBuff[MAX_PATH];
TCHAR *pdest = NULL;

	if (GetModuleFileName(m_hInstance, cbPathBuff, sizeof(cbPathBuff)))
	{
		pdest = _tcsrchr(cbPathBuff, _T('\\'));
		*pdest = _T('\0');
		_tcscat(cbPathBuff, _T("\\resdlls\\0009\\TRiASGM1.drx"));

		_Module.m_hInstResource = LoadLibrary (cbPathBuff);
		AfxSetResourceHandle(_Module.m_hInstResource);
	}

// diverse Stringresourcen laden
	PreLoadStrings();

// DBMS initialisieren
UINT uiDexCmd = ::RegisterWindowMessage (g_cbTriasExtensionMessage);
UINT uiDexNfy = ::RegisterWindowMessage (g_cbTriasNotification);
UINT uiDexxCmd = ::RegisterWindowMessage (g_cbTriasCPPExtensionMessage);

	::InitTrias01 (NULL, uiDexCmd, uiDexNfy, uiDexxCmd);
	::SetCopyrightFlag(FALSE);
	
	return CWinApp::InitInstance();
}

int CTRiASGMApp::ExitInstance()
{
	::CleanUpTrias01();
	if (NULL != _Module.GetResourceInstance()) {
		FreeLibrary (_Module.GetResourceInstance());
		_Module.m_hInstResource = NULL;
	}
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

/////////////////////////////////////////////////////////////////////////////
// diverse Stringresourcen laden
void PreLoadStrings()
{
CString str;

	VERIFY(str.LoadString(IDS_OBJEKTNUMMER));
	strcpy (g_cbObjektNummer, str);
	VERIFY(str.LoadString(IDS_GEOMETRY));
	strcpy (g_cbGeometry, str);
	VERIFY(str.LoadString(IDS_OBJEKTTYP));
	strcpy (g_cbObjektTyp, str);

	VERIFY(str.LoadString(IDS_POINT));
	strcpy (g_cbPunkt, str);
	VERIFY(str.LoadString(IDS_LINE));
	strcpy (g_cbLinie, str);
	VERIFY(str.LoadString(IDS_AREA));
	strcpy (g_cbFlaeche, str);
	VERIFY(str.LoadString(IDS_TEXT));
	strcpy (g_cbText, str);

	VERIFY(str.LoadString(IDS_POINTS));
	strcpy (g_cbPunkte, str);
	VERIFY(str.LoadString(IDS_LINES));
	strcpy (g_cbLinien, str);
	VERIFY(str.LoadString(IDS_AREAS));
	strcpy (g_cbFlaechen, str);
	VERIFY(str.LoadString(IDS_TEXTS));
	strcpy (g_cbTexte, str);

	VERIFY(str.LoadString(IDS_IDENTIFIKATOR));
	strcpy (g_cbIdentifikator, str);
	VERIFY(str.LoadString(IDS_OBJEKTTYPEN));
	strcpy (g_cbObjekttypen, str);
	VERIFY(str.LoadString(IDS_KURZTEXT));
	strcpy (g_cbKurztext, str);
	VERIFY(str.LoadString(IDS_LANGTEXT));
	strcpy (g_cbLangtext, str);
}

