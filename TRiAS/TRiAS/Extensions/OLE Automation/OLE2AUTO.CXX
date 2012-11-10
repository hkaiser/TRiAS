// Erweiterungsklasse, für OLE2.0 Automation ----------------------------------
// File: OLE2AUTO.CXX

#include "precomp.hxx"		// Alle Header auf einen Blick

#include <ole2ver.h>
#include <registrx.hxx>

#include <ospace/string/regexp.h>

#include "oleautor.h"
#include "version.h"

#if defined(WIN32)
#include <olectl.h>
#else
#include <olectlid.h>
#endif

#include <toolguid.h>
#include <srchoice.h>
#include <statguid.h>
#include <ipropseq.hxx>
#include <oleguid.h>

#include <initguid.h>
#define _TriasTLB_H_
#include <dirisole.h>
#include "dlldatax.h"

#include <bscrguid.h>		// BSCRIPT.EXT
#include <abstguid.h>
#include <textguid.h>
#include <trelguid.h>
#include <buffguid.h>
#include <operguid.h>
#include <fmfcguid.h>
#include <editguid.h>
#include <reinguid.h>

#include "BScriptNotify.h"
#include "connect.hxx"
#include "WrapperExtension.h"
#include "Strings.h"

//EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const IID __declspec(selectany) IID_IStatusProgress = {0x8FB5DAD3,0xE4BD,0x11D1,{0x86,0x10,0x00,0x60,0x08,0x75,0x13,0x8A}};
#if _TRiAS_VER < 0x0300
EXTERN_C const CLSID __declspec(selectany) CLSID_TRiASCSRectangleGeometry = {0xCF648167,0x9E24,0x11D1,{0xBA,0x1C,0x08,0x00,0x36,0xD6,0x38,0x03}};
#endif // _TRiAS_VER < 0x0300

#if defined(_SUPPORT_QUERYDEFS)
EXTERN_C const CLSID __declspec(selectany) CLSID_QueryDefExt = {0x1BF01AF1,0x33CF,0x11D3,{0x94,0xFA,0x00,0x80,0xC7,0x86,0x29,0x7B}};
EXTERN_C const CLSID __declspec(selectany) CLSID_TRiASCollectObjects = {0x6BE4F280,0x33D1,0x11D3,{0x94,0xFA,0x00,0x80,0xC7,0x86,0x29,0x7B}};
#endif // defined(_SUPPORT_QUERYDEFS)

EXTERN_C const CLSID __declspec(selectany) CLSID_TRiASProject = {0x1CB3AB64,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#ifdef _MERGE_PROXYSTUB
extern "C" DWORD g_dwFlags = 0L;
extern "C" HINSTANCE hProxyDll;
#endif

#if defined(DYNAMIC_BASIC)
HINSTANCE g_hBScript = 0;	// BasicScript-Runtime
#endif // DYNAMIC_BASIC

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Dispatch);
DefineSmartInterface2(DDocument, IID_DDocument);

DefineSmartInterface(ClassFactory);

///////////////////////////////////////////////////////////////////////////////
// function declarations
bool IsEnabledDCOM (void);

#if defined(_DEBUG)
//
// WIN32: these flags could be set in
//	  HKEY_CURRENT_USER\Software\fez\TRiAS\Extensions\TRiAS.OleAutomation.1\Config\TraceFlags
//
// TraceFlags:	0x01 - ADDREF_TRACE, RELEASE_TRACE
//				0x02 - CONSTRUCT_TRACE, DESTRUCT_TRACE
//
extern "C" DWORD locTraceFlags = 0;
#endif

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
/*
CTriasExtension *NewExtension (void)
{
#if defined(_DEBUG) && defined(WIN32)
	if (!IsWin32s()) {	// Traceflags einlesen
	CCurrentUser regCfg (TEXT("Software\\TRiAS\\InterTRiAS\\Extensions\\TRiAS.OleAutomation.1\\Config"));

		locTraceFlags = 0;
		regCfg.GetDWORD (TEXT("TraceFlags"), locTraceFlags);
	}
#endif
	return new OLE2AutoExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_OleAutoExtension, sizeof (GUID));
	return true;
}
*/

// 
// NEU: Die folgende Funktion KANN vom Nutzer bereitgestellt werden, wenn eine
// TypeLib registriert werden soll. Auch die TypeLib muß einen eigenen GUID
// besitzen !
//
BOOL GetTypeLibGUID (GUID &guidTLib)
{
	memcpy (&guidTLib, &LIBID_TRiAS, sizeof (GUID));
	return true;		// TypeLib registrieren/deregistrieren
}

// 
// NEU: Die folgende Funktion KANN vom Nutzer bereitgestellt werden, wenn die
// TypeLib nicht als Resource an dieser Extension gespeichert ist. Diese Funktion
// muß in diesem Fall den Namen der zu registrierenden TypeLib liefern
//
bool GetTypeLibName (OLECHAR *cbBuffer)
{
	return false;	// hier nicht der Fall (Funktion könnte weggelassen werden)
}

//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.OleAutoExtension.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
bool fSuccess = false;

	if (fRegister) {
	// RegDB initialisieren
#ifdef _MERGE_PROXYSTUB
		if (g_dwFlags) {
			if (FAILED(PrxDllRegisterServer())) 
				return false;
		} 
#endif
	// Erweiterung registrieren
		fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_OleAutoExtension, 
				TEXT("TRiAS.OleAutomation.1"), IDS_LONGCLASSNAME,
				OLEAUTO_MAJORVERSION, OLEAUTO_MINORVERSION,
				EFPreLoad|EFPriorityLoad7);
		if (!fSuccess) return false;
	} else {
	// RegDB säubern
#ifdef _MERGE_PROXYSTUB
		PrxDllUnregisterServer();
#endif
		fSuccess = ExtOleUnregisterClass (CLSID_OleAutoExtension, 
				TEXT("TRiAS.OleAutomation.1"));
		if (!fSuccess) return false;
	}

// zusätzliche Funktionalität dieser Erweiterung registrieren
static _ATL_REGMAP_ENTRY regEntryMap[] = 
{
#if _ATL_VER >= 0x0200
// TRiAS.Application
	{ L"TRIASMODULE", NULL },
	{ L"PROGID", L"TRiAS.Application" },
	{ L"CLSID", L"{8DE4E3C2-4D53-101B-AAE1-E7E7E7E7E7E7}" },
	{ L"TYPELIB", L"{8DE4E3C0-4D53-101B-AAE1-E7E7E7E7E7E7}" },
#if _TRiAS_VER < 0x0300
	{ L"VERSION", L"2" },
#elif _TRiAS_VER < 0x0400
	{ L"VERSION", L"3" },
#else 
	{ L"VERSION", L"4" },
#endif // _TRiAS_VER < 0x0300 
//
// TRiAS.OleAutomation
	{ L"CLSIDEXT", L"{ED9655C2-3122-101C-BB62-00AA0018497C}" },
#else
// TRiAS.Application
	{ TEXT("TRIASMODULE"), NULL },
	{ TEXT("PROGID"), TEXT("TRiAS.Application") },
	{ TEXT("CLSID"), TEXT("{8DE4E3C2-4D53-101B-AAE1-E7E7E7E7E7E7}") },
	{ TEXT("TYPELIB"), TEXT("{8DE4E3C0-4D53-101B-AAE1-E7E7E7E7E7E7}") },
	{ TEXT("VERSION"), TEXT("2") },
//
// TRiAS.OleAutomation
	{ TEXT("CLSIDEXT"), TEXT("{ED9655C2-3122-101C-BB62-00AA0018497C}") },
#endif // _ATL_VER
	{ NULL, NULL },		// EndeKennung
};
TCHAR cbTRiASPath[_MAX_PATH];

	if (0 == GetModuleFileName (NULL, cbTRiASPath, _MAX_PATH))
		return false;
#if _ATL_VER >= 0x0200
	USES_CONVERSION;
	regEntryMap[0].szData = A2OLE(cbTRiASPath);
#else
	regEntryMap[0].szData = cbTRiASPath;
#endif // _ATL_VER
	return SUCCEEDED(_Module.UpdateRegistryFromResource(IDR_REGISTRY, fRegister, regEntryMap));
}

#ifdef _MERGE_PROXYSTUB
BOOL TxInitInstance (HINSTANCE hInst)
{
// erstmal feststellen, ob wirklich mut Proxies/Stubs gearbeitet werden soll
CCurrentUser reg (KEY_READ, g_cbRegConfig);

	g_dwFlags = 0L;
	reg.GetDWORD (TEXT("ProxyStub"), g_dwFlags);
	ASSERT((IsWin40() && (IsWinNT() || IsEnabledDCOM())) || 0L == g_dwFlags);		// nur unter WinNT40 verwendbar

	if (g_dwFlags && !PrxDllMain(hInst, DLL_PROCESS_ATTACH, NULL))
		return FALSE;

// jetzt evtl. ProxyStub initialisieren
	if (g_dwFlags)
		hProxyDll = hInst;
	else
		hProxyDll = NULL;
	return TRUE;
}

void TxExitInstance (void)
{
	if (g_dwFlags)
		PrxDllMain(hProxyDll, DLL_PROCESS_DETACH, NULL);
	hProxyDll = NULL;
}

HRESULT TxGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
	if (g_dwFlags)
		return PrxDllGetClassObject (rclsid, riid, ppv);
	return CLASS_E_CLASSNOTAVAILABLE;
}

HRESULT TxCanUnloadNow (void)
{
	if (g_dwFlags)
		return PrxDllCanUnloadNow();
	return S_OK;
}
#endif // _MERGE_PROXYSTUB

///////////////////////////////////////////////////////////////////////////////
// ClassFactories
// {D4752D2F-6067-442C-87E8-8C9417B99955}
extern "C" const IID __declspec(selectany) CLSID_GeoDocumentIntern = 
	{0xd4752d2f,0x6067,0x442c,{0x87,0xe8,0x8c,0x94,0x17,0xb9,0x99,0x55}};

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_WrapperExtension, CWrapperExtension)
	OBJECT_ENTRY(CLSID_GeoDocumentIntern, CGeoDoc)
	OBJECT_ENTRY(CLSID_OleAutoExtension, OLE2AutoExtension)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// ObjectMap liefern
}

inline 
HRESULT RegisterClassObject (
	CComModule &rModule, REFCLSID rClsId, DWORD dwClsContext, DWORD dwFlags)
{
	_ASSERTE(rModule.m_pObjMap != NULL);

_ATL_OBJMAP_ENTRY* pEntry = rModule.m_pObjMap;

	while (pEntry->pclsid != NULL) 
	{
		if (InlineIsEqualGUID(rClsId, *pEntry->pclsid))
			return pEntry -> RegisterClassObject(dwClsContext, dwFlags);
		pEntry++;
	}
	return S_FALSE;		// not found
}

inline 
HRESULT RevokeClassObject (CComModule &rModule, REFCLSID rClsId)
{
	_ASSERTE(rModule.m_pObjMap != NULL);

_ATL_OBJMAP_ENTRY* pEntry = rModule.m_pObjMap;

	while (pEntry->pclsid != NULL)
	{
		if (InlineIsEqualGUID(rClsId, *pEntry->pclsid))
			return pEntry->RevokeClassObject();
		pEntry++;
	}
	return S_FALSE;		// not found
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.
OLE2AutoExtension::OLE2AutoExtension (void)
{
	CONSTRUCT_TRACE(OLE2AutoExtension);
	
	m_dwAppCF = 0;
	m_dwDocCF = 0;
	m_dwProjCF = 0;
	m_dwRegister = 0;
	m_fOleInitialized = false;
//	m_fDocRegistered = false;
	m_fForceUnload = false;

	m_fIsDragSourceInst = false;
	m_hPrIsDragSource = NULL;
		
	m_pApp = NULL;
	m_pIAppPro = NULL;
	
	m_pIScript = NULL;
#if defined(DYNAMIC_BASIC)
	g_hBScript = NULL;
#endif // DYNAMIC_BASIC

	m_dwCookie = 0L;

	m_pIAbstand = NULL;
	m_pITextGen = NULL;
	m_pITopoRel = NULL;
	m_pIBuffer = NULL;
	m_pIObjOper = NULL;
	m_pIVisObj = NULL;
	m_pIEdit = NULL;
	m_pIGeoRein = NULL;

#if defined(_DEBUG) && !defined(WIN16)
	if (!IsWin32s()) 
	{	
	// Traceflags einlesen
	CCurrentUser regCfg (KEY_READ, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Extensions\\TRiAS.OleAutomation.1\\Config"));

		locTraceFlags = 0;
		regCfg.GetDWORD (TEXT("TraceFlags"), locTraceFlags);
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Objekt ist fertig konstruiert
HRESULT OLE2AutoExtension::FinalConstruct()
{
HRESULT hr = CTriasExtension::FinalConstruct();

	if (SUCCEEDED(hr))
		hr = CObjectProperties::FinalConstruct();
	return hr;
}

// Destruktor -----------------------------------------------------------------
OLE2AutoExtension::~OLE2AutoExtension (void) 
{
	DESTRUCT_TRACE(OLE2AutoExtension);

// OLE freigeben, wenn wir es initialisiert haben
	if (m_fOleInitialized)
		OleUninitialize();
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob auf dieser Maschine DCOM enabled ist 
bool IsEnabledDCOM (void)
{
	ASSERT(IsWin40());

CLocalMachine regDCOM (TEXT("SOFTWARE\\Microsoft\\Ole"));
TCHAR cbBuffer[10];
DWORD dwLen = sizeof(cbBuffer);

	if (!regDCOM.GetSubSZ (TEXT("EnableDCOM"), cbBuffer, dwLen))
		return false;

	return !_tcsicmp (cbBuffer, TEXT("y"));
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) OLE2AutoExtension::InitExtension (short iMode) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (!CTriasExtension::InitExtension (iMode)) 
		return false;

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
	}		

// Caption strings für embedded-Fall vorbereiten
CString strFileType (g_cbTRiAS);
CString strTitle, strHostObj;

	VERIFY(strHostObj.LoadString (IDS_DOCUMENT));
	strFileType += strHostObj;							// "TRiAS - Dokument"
	VERIFY(strHostObj.LoadString (IDS_OLEDOCUMENT));	// "OLE - Dokument"
	AfxFormatString2(strTitle, AFX_IDS_APP_TITLE_EMBEDDING,	strFileType, strHostObj);

// nur die Variable setzen (für später)
	m_strEmbeddedCaption = strTitle;

// sonstige Initialisierungen
HRESULT hr = NOERROR;

#if defined(WIN16)
// Testen, ob OLE schon initialisiert ist, OLE initialisieren
LPMALLOC pIMalloc = NULL;

	hr = CoGetMalloc(MEMCTX_TASK, &pIMalloc);
	if (SUCCEEDED(hr))
		pIMalloc -> Release();		// war schon einer schneller
	else {
	DWORD dwVer = OleBuildVersion();	// selbst initialisieren
	
		if (HIWORD (dwVer) != rmm)
			return false;		// falsche OleVersion
		if (FAILED(OleInitialize (NULL)))
			return false;
		m_fOleInitialized = true;
	}
#else // WIN32
	if (OleInitialize (NULL) == S_OK)
		m_fOleInitialized = true;
	else
		m_fOleInitialized = false;
#endif

// ApplicationObject generieren, App hält Erweiterung fest
	m_pApp = CTriasApp::CreateInstance ((ITriasXtension *)this);
	if (!m_pApp) return false;

// aktives Objekt anmelden (RunningObjectTable)
	hr = RegisterActiveObject ((_DApplication *)m_pApp, CLSID_Application, ACTIVEOBJECT_STRONG, &m_dwRegister);
	if (FAILED(hr)) return false;

// evtl. beim BScript anmelden
	hr = ((_DApplication *)m_pApp) -> QueryInterface (IID_DApplication, (LPVOID *)&m_pIAppPro);
	if (FAILED(hr)) return false;
	
	RegisterBScriptExtension();

// Notifications anmelden
	RegisterNotification (DEX_HANDLEAUTOMATION);
	RegisterNotification (DEX_HANDLEEMBEDDING);
	RegisterNotification (DEX_INITIALIZEDSERVER);
	RegisterNotification (DEX_SERVERCLOSED);
	RegisterNotification (DEX_SERVERISCLOSING);
	RegisterNotification (DEX_ISCLOSEDPROJECT);
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_SIGHTSELECTED);
	RegisterNotification (DEX_SIGHTTOSELECT);
	RegisterNotification (DEX_DELETEVIEW);
	RegisterNotification (DEX_DELOBJECT);
	RegisterNotification (DEX_N_RENAMINGFILE);
	RegisterNotification (DEX_N_FILERENAMED);
	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_OBJWNDCLOSED);
	RegisterNotification (DEX_CAPTIONREREAD);
	RegisterNotification (DEX_MODIFYINGIDENT);
	RegisterNotification (DEX_IDENTWASMODIFIED);

	RegisterNotification (DEX_OLEUPDATECLIENT);
	RegisterNotification (DEX_OLERETURN);		// #AD000510, Achtung! Neue DEX_ - Message!!
	
	RegisterNotification (DEX_ERASEBKGND);
	RegisterNotification (DEX_PAINTTOPLAYER);

	RegisterNotification (WM_CLOSE, FALSE);

	m_Cmds.SetMenuOffset (MenuOffset());
	return true;
}


STDMETHODIMP_(BOOL) OLE2AutoExtension::UnLoadExtension (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

#if defined(DYNAMIC_BASIC)
	if ((m_fOleInitialized || g_hBScript) && !m_fForceUnload)	
		return false;
#else
	if (m_fOleInitialized && !m_fForceUnload)	
		return false;
#endif // DYNAMIC_BASIC
	
// Notifications abmelden

	UnRegisterNotification (WM_CLOSE, FALSE);

	UnRegisterNotification (DEX_PAINTTOPLAYER);
	UnRegisterNotification (DEX_ERASEBKGND);
	UnRegisterNotification (DEX_OLERETURN);
	UnRegisterNotification (DEX_OLEUPDATECLIENT);

	UnRegisterNotification (DEX_IDENTWASMODIFIED);
	UnRegisterNotification (DEX_MODIFYINGIDENT);
	UnRegisterNotification (DEX_CAPTIONREREAD);
	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);
	UnRegisterNotification (DEX_N_RENAMINGFILE);
	UnRegisterNotification (DEX_N_FILERENAMED);
	UnRegisterNotification (DEX_DELOBJECT);
	UnRegisterNotification (DEX_DELETEVIEW);
	UnRegisterNotification (DEX_SIGHTTOSELECT);
	UnRegisterNotification (DEX_SIGHTSELECTED);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_ISCLOSEDPROJECT);
	UnRegisterNotification (DEX_SERVERISCLOSING);
	UnRegisterNotification (DEX_SERVERCLOSED);
///	UnRegisterNotification (DEX_INITIALIZEDSERVER);
//	UnRegisterNotification (DEX_HANDLEEMBEDDING);	// für alle Fälle noch mal
//	UnRegisterNotification (DEX_HANDLEAUTOMATION);	// für alle Fälle noch mal

	RELEASE(m_pIAbstand);	// AbstandsErweiterung freigeben
	RELEASE(m_pITextGen);	// TextObjekterweiterung freigeben
	RELEASE(m_pITopoRel);	// Topologische Relationen freigeben
	RELEASE(m_pIBuffer);	// Buffering freigeben
	RELEASE(m_pIObjOper);	// Objektoperationen freigeben
	RELEASE(m_pIVisObj);	// Visualisierung freigeben
	RELEASE(m_pIEdit);		// Editierung freigeben
	RELEASE(m_pIGeoRein);	// Geometriebereinigung freigeben

// BasicScript-Runtime und Interface freigeben
	if (m_dwCookie) {
		FDisconnect (m_dwCookie);	// Connection zu BScript auflösen
		m_dwCookie = 0L;
	}
	RELEASE(m_pIScript);

#if defined(DYNAMIC_BASIC)
	if (g_hBScript) {
		FreeLibrary (g_hBScript);
		g_hBScript = NULL;
	}
#endif // DYNAMIC_BASIC

// ClassFactories abmelden
	if (0 != m_dwRegister) {
		RevokeActiveObject (m_dwRegister, NULL);
		m_dwRegister = 0L;
	}
//	if (m_fDocRegistered) { 
//		RevokeClassObject(_Module, CLSID_GeoDocument);
//		m_fDocRegistered = false;
//	}
	if (0 != m_dwAppCF) {
		CoRevokeClassObject (m_dwAppCF);
		m_dwAppCF = 0L;
	}
	if (0 != m_dwDocCF) {
		CoRevokeClassObject (m_dwDocCF);
		m_dwDocCF = 0L;
	}
	if (0 != m_dwProjCF) {
		CoRevokeClassObject (m_dwProjCF);
		m_dwProjCF = 0L;
	}

// end all connections from remote processes
	CoDisconnectObject((_DApplication *)m_pApp, 0);	

	m_pApp -> InvApp();

	RELEASE(m_pIAppPro);
	RELEASE_CAST(_DApplication, m_pApp);
	m_pApp = NULL;

return CTriasExtension::UnLoadExtension();
}

STDMETHODIMP_(LRESULT) OLE2AutoExtension::WindowsNotification (UINT wMsg, 
											WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	CGeoDoc*	pDoc = NULL;

//ASSERT(FALSE);		// Debug-Break

	switch (wMsg) {
	case WM_CLOSE:
		// im Embedded-Mode auf WM_CLOSE nur reagieren, wenn
		// vorher das Dokument geordnet abgeräumt wurde!
		if (DEX_QueryMode() & QMEmbedding) {

			pDoc = m_pApp ->FGetGeoDocument (NULL, NULL);
			if ( NULL != pDoc )
			{
				pDoc ->OnHide();
				return 0L;
			}
		}
		break;

	default:
		;
	}

	return CTriasExtension::WindowsNotification (wMsg, wParam, lParam);
}

STDMETHODIMP_(LRESULT) OLE2AutoExtension::Notification (WPARAM iMsg, LPARAM p)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	char*		cbBuffer = NULL;
	CGeoDoc*	pDoc = NULL;

	switch (iMsg) {
	// ServerEvents
	case DEX_INITIALIZEDSERVER:	// Server fertig initialisiert
		UnRegisterNotification (DEX_HANDLEAUTOMATION);	// kommen nur einmal
		UnRegisterNotification (DEX_HANDLEEMBEDDING);
		UnRegisterNotification (DEX_INITIALIZEDSERVER);
		break;

	case DEX_SERVERISCLOSING:
		return m_pApp -> OnServerEvent (SERVEREVT_ClosingServer);
		
	case DEX_SERVERCLOSED:
		m_fForceUnload = true;
		return m_pApp -> OnServerEvent (SERVEREVT_ServerToClose);
		
	// ProjektEvents
	case DEX_PROJECTOPEN:
		{
		LRESULT lRes = m_pApp -> OnProjectEvent (PROJECTEVT_ProjectOpened, HPROJECT(p));
		
			InstallDropTargets (HPROJECT(p));


		// Spezielles Caption für den Embedded-Mode
//		if (DEX_QueryMode() & QMEmbedding) {
////			DEX_SetTRiASCaption ((const char*)m_strEmbeddedCaption);
//			DEX_ReReadCaption ();
//		}
			return lRes;
		}
		
	case DEX_PROJECTCLOSE:
		return m_pApp -> OnProjectEvent (PROJECTEVT_ClosingProject, HPROJECT(p));
		
	case DEX_ISCLOSEDPROJECT:
		RemoveDropTargets();
		return m_pApp -> OnProjectClosedEvent ((LPCSTR)p);

	case DEX_N_PROJECTTOCLOSE:
		return m_pApp -> OnProjectEvent (PROJECTEVT_ProjectToClose, HPROJECT(p));

	case DEX_N_RENAMINGFILE:
		return m_pApp -> OnProjectEvent (PROJECTEVT_RenamingFile, HPROJECT(p));

	case DEX_N_FILERENAMED:
		return m_pApp -> OnProjectEvent (PROJECTEVT_FileRenamed, HPROJECT(p));

	case DEX_SETGEODBDIRTY:
		return m_pApp -> OnProjectEvent (
			p ? PROJECTEVT_ProjectIsDirty : PROJECTEVT_ProjectIsNotDirty, 0L);

	// GeoViewEvents
	case DEX_SIGHTSELECTED:
		return m_pApp -> OnViewEvent (GEOVIEWEVT_ViewSelected, LPCTSTR(p));

	case DEX_SIGHTTOSELECT:
		return m_pApp -> OnViewEvent (GEOVIEWEVT_SelectingView, LPCTSTR(p));

	case DEX_DELETEVIEW:
		return m_pApp -> OnViewEvent (GEOVIEWEVT_DeletingView, LPCTSTR(p));
		
	case DEX_SIGHTDELETED:
		return m_pApp -> OnViewEvent (GEOVIEWEVT_ViewDeleted, LPCTSTR(p));
		
	// GeoObjectEvents
	case DEX_DELOBJECT:
		return m_pApp -> OnObjectEvent (GEOOBJECTEVT_ObjectDeleted, INT_PTR(p));

	case DEX_CAPTIONREREAD:
		// Spezielles Caption für den Embedded-Mode
		{
		DWORD dwMode = DEX_QueryMode();

			if (dwMode & QMEmbedding && !(dwMode & QMAutomation)) {
				cbBuffer = (char*)p;
				wsprintf (cbBuffer, "%s", m_strEmbeddedCaption);
			}
		}
		break;

	case DEX_MODIFYINGIDENT:		// Objekt wurde umklassifiziert
		m_pApp -> OnObjectEvent (GEOOBJECTEVT_ObjectToClassify, INT_PTR(p));
		break;

	case DEX_IDENTWASMODIFIED:		// Objekt wurde umklassifiziert
		m_pApp -> OnObjectEvent (GEOOBJECTEVT_ObjectClassified, INT_PTR(p));
		break;

#if defined(WIN16)
	case DEX_HANDLEAUTOMATION:
		break;
#else
	case DEX_HANDLEAUTOMATION:		// KommandoZeile: /Automation
		if (DEX_QueryMode() & QMAutomation) {
		// ClassFactory für AppObject registrieren
			_ASSERTE(NULL != m_pApp);

		WClassFactory AppCF (CTriasAppCF::CreateInstance (m_pApp), false);		// liefert AddRef'd ab

			if (!AppCF) return false;

		DWORD dwClsCtx = CLSCTX_LOCAL_SERVER;

#if defined(_DEBUG)
			if (IsWin40() && IsEnabledDCOM()) 
				dwClsCtx |= CLSCTX_REMOTE_SERVER;
#endif // _DEBUG

			if (SUCCEEDED(CoRegisterClassObject (CLSID_Application, AppCF, dwClsCtx, REGCLS_SINGLEUSE, &m_dwAppCF))) 
				return true;
		} 
		return false;

	case DEX_HANDLEEMBEDDING:		// KommandoZeile: /Embedding
//		DEX_ChangeMRUMode(false);		// Hier noch einmal probieren!
		if (DEX_QueryMode() & QMEmbedding) {
		// ClassFactory für Document anmelden
		WClassFactory WrappCF;

		// Beschaffen der ClassFactory für den GeoDocument
		HRESULT hr = CoGetClassObject (CLSID_GeoDocumentIntern, CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory, WrappCF.ppv());

			if (!SUCCEEDED(hr))
				return false;

		// CF für Dokument und Projekt anmelden
		DWORD dwClsCtx = CLSCTX_LOCAL_SERVER;
#if defined(_DEBUG)
			if (IsWin40() && IsEnabledDCOM()) 
				dwClsCtx |= CLSCTX_REMOTE_SERVER;
#endif // _DEBUG

		// Anmelden des GeoDocument, das über die ClassFactory des DocWrapper erzeugt wird!!
			hr = CoRegisterClassObject (CLSID_GeoDocument, WrappCF, dwClsCtx, REGCLS_SINGLEUSE, &m_dwDocCF);
			if (SUCCEEDED(hr)) 
				hr = CoRegisterClassObject (CLSID_TRiASProject, WrappCF, dwClsCtx, REGCLS_SINGLEUSE, &m_dwProjCF);

			if (SUCCEEDED(hr)) {
//				m_fDocRegistered = true;
				return true;
			}
		// ansonsten hier duchfallen
		// ...
		}
		return false;

	case DEX_OLERETURN:
		pDoc = m_pApp -> FGetGeoDocument (NULL, NULL);
		if (NULL != pDoc)
			pDoc -> OnHide();
		return false;

	case DEX_OLEUPDATECLIENT:
		pDoc = m_pApp -> FGetGeoDocument (NULL, NULL);
		if (NULL != pDoc)
			pDoc -> OnDataChanged();
		return false;

	case DEX_ERASEBKGND:
		pDoc = m_pApp -> FGetGeoDocument (NULL, NULL);
		if (NULL != pDoc)
			pDoc -> RegisterStartPaint();
		return false;

	case DEX_PAINTTOPLAYER:
		pDoc = m_pApp -> FGetGeoDocument (NULL, NULL);
		if (NULL != pDoc)
			pDoc -> RegisterStopPaint();
		return false;

	case DEX_CREATEOBJEKTINFO:
		return m_pApp -> OnObjectWindowEvent (OBJWNDEVT_WindowCreated, HWND(p));

	case DEX_N_CLOSINGOBJWND:
		return m_pApp -> OnObjectWindowEvent (OBJWNDEVT_DestroyingWindow, HWND(p));

	case DEX_N_OBJWNDTOCLOSE:
		return m_pApp -> OnObjectWindowEvent (OBJWNDEVT_WindowToDestroy, HWND(p));

	case DEX_OBJWNDCLOSED:
		return m_pApp -> OnObjectWindowEvent (OBJWNDEVT_WindowDestroyed, HWND(p));
#endif // WIN32

	default:	// alle anderen Notifikationen weiterreichen
		break;
	}
	return false;
}

// Handling für Inplace- und Embedded-Mode-Caption
// #AD000420
void OLE2AutoExtension::SetTitle (const char* strHost, const char* strHostObj)
{
// format the string into <server-name> in <docname>
CString strTitle;
CString strFileType (g_cbTRiAS);

	VERIFY(strTitle.LoadString (IDS_DOCUMENT));
	strFileType += strTitle;					// "InterTRiAS - Dokument"

	AfxFormatString2(strTitle, AFX_IDS_APP_TITLE_EMBEDDING,	strFileType, strHostObj);

// zunächst die Variable setzen (für später)
	m_strEmbeddedCaption = strTitle;

// dann Caption explicit ändern (jetzt gleich!)
	DEX_ReReadCaption();
}

///////////////////////////////////////////////////////////////////////////////
// MenuHandling
STDMETHODIMP_(BOOL) OLE2AutoExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (NULL != hWnd) return false;		// nicht für uns
	
// Strings laden und an TRiAS schicken
UINT uiRes = 0L;

	switch (uiMenuID) {
	case ID_DRAGDROPPOPUP_COPY:		uiRes = IDS_DRAGDROPPOPUP_COPY; break;
	case ID_DRAGDROPPOPUP_MOVE:		uiRes = IDS_DRAGDROPPOPUP_MOVE; break;
	case ID_DRAGDROPPOPUP_COPYWITHORWINDOW:		uiRes = IDS_DRAGDROPPOPUP_COPYWITHORWINDOW; break;
	case ID_DRAGDROPPOPUP_MOVEWITHORWINDOW:		uiRes = IDS_DRAGDROPPOPUP_MOVEWITHORWINDOW; break;
	case ID_DRAGDROPPOPUP_CANCEL:	uiRes = IDS_DRAGDROPPOPUP_CANCEL; break;
	default:
		{
			if (!m_Cmds.IsValid()) 
				return false;

		// Zeichenkette zusammenbauen
		HPROJECT hPr = HACTCONNECTION;
		BOOL fShowORWnd = FALSE;
		DWORD dwEffect = m_Cmds.FindCommand (uiMenuID, &hPr, &fShowORWnd);

			if (DROPEFFECT_NONE == dwEffect || HACTCONNECTION == hPr)
				return false;

		char cbBuffer[_MAX_PATH];

			if (!DEX_GetDataSourceShortName (hPr, cbBuffer))
				return false;

		CString strMsg;

			TRY {
				if (DROPEFFECT_COPY == dwEffect)
					strMsg.Format (fShowORWnd ? IDS_DRAGDROPPOPUP_COPYWITHORWINDOW_DS : IDS_DRAGDROPPOPUP_COPY_DS, cbBuffer);
				else
					strMsg.Format (fShowORWnd ? IDS_DRAGDROPPOPUP_MOVEWITHORWINDOW_DS : IDS_DRAGDROPPOPUP_MOVE_DS, cbBuffer);
			
			} CATCH(CMemoryException, e) {
				return false;
			} END_CATCH;

		// jetzt Meldung anzeigen
			DEX_SetMessageString ((LPCSTR)strMsg);
			return true;
		}
		break;
	}

	if (uiRes != 0L) {
	CString strMsg;

		TRY {
			strMsg.LoadString(uiRes);
		} CATCH(CMemoryException, e) {
			return false;
		} END_CATCH;

		DEX_SetMessageString ((LPCSTR)strMsg);
		return true;
	}
	return false;
}

STDMETHODIMP_(BOOL) OLE2AutoExtension::MenuCommand (WPARAM uiMenuID, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Interfacehelper
bool OLE2AutoExtension::RegisterBScriptExtension (void)
{
HRESULT hr = CoCreateInstance (CLSID_MacroScriptExtension, NULL, 
			       CLSCTX_INPROC_SERVER, IID_IExtendBScript,
			       (LPVOID *)&m_pIScript);

	if (FAILED(hr)) return false;

// Herstellen der Connection für Events an BScript
	if (FAILED(FConnect (&m_dwCookie)) || m_dwCookie == 0L) {
		m_pIScript -> Release();
		m_pIScript = NULL;
		return false;
	}

// diese Erweiterung als public BasicExtension registrieren
	if (FAILED(m_pIScript -> RegisterExtModule (g_pDLLName))) {
		m_pIScript -> Release();
		m_pIScript = NULL;
		return false;
	}

return true;
}

// Herstellen der Connection für Events an BScript ----------------------------
DefineSmartInterface(TriasXtensionSite);
DefineSmartInterface(TRiASNotificationSink);

HRESULT OLE2AutoExtension::FConnect (DWORD *pdwCookie)
{
	if (NULL == pdwCookie) return E_POINTER;

WTriasXtensionSite ISite;
HRESULT hr = GetXtensionSite (ISite.ppi());

	if (FAILED(hr)) return hr;

// normale Notifikationen bei TRiAS anmelden
DWORD dwCookie = 0L;

	COM_TRY {
	// Wrapperklasse für Sink anlegen
	CComObject<CTRiASNotificationSinkBScript> *pISink = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASNotificationSinkBScript>::CreateInstance(&pISink));

	WTRiASNotificationSink Sink (pISink);		// RefCnt jetzt 1

		THROW_FAILED_HRESULT(pISink -> FInit (m_pApp, m_pIScript));
		THROW_FAILED_HRESULT(AtlAdvise (ISite, Sink, IID_ITRiASNotificationSink, &dwCookie));
			
	} COM_CATCH;

// Resultat liefern
	*pdwCookie = dwCookie;
	return S_OK;
}

HRESULT OLE2AutoExtension::FDisconnect (DWORD dwCookie)
{
	ASSERT(0 != dwCookie);

WTriasXtensionSite ISite;
HRESULT hr = GetXtensionSite (ISite.ppi());

	if (SUCCEEDED(hr)) 
		hr = AtlUnadvise (ISite, IID_ITRiASNotificationSink, dwCookie);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// BasicScript binden
HRESULT OLE2AutoExtension::GetIBScript (LPEXTENDBSCRIPT *ppIBScript)
{
	if (NULL == ppIBScript) return E_POINTER;
	if (NULL == m_pIScript) return E_UNEXPECTED;

// erfolgreich gebunden
	*ppIBScript = m_pIScript;
	(*ppIBScript) -> AddRef();
	return NOERROR;
}

// AbstandsErweiterung binden -------------------------------------------------
HRESULT OLE2AutoExtension::GetIDistance (LPEXTENDABSTAND *ppIAbstand)
{
	*ppIAbstand = NULL;		// für alle Fälle
	
	if (m_pIAbstand == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_Abstand, IID_IExtendAbstand2, (LPVOID *)&m_pIAbstand);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	*ppIAbstand = m_pIAbstand;
	(*ppIAbstand) -> AddRef();
	return S_OK;
}


// Textobjekterweiterung binden -----------------------------------------------
HRESULT OLE2AutoExtension::GetITextGen (LPMAINTAINTEXTS *ppIGenText)
{
	*ppIGenText = NULL;		// für alle Fälle
	
	if (m_pITextGen == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_TextExtension, IID_IMaintainTexts, (LPVOID *)&m_pITextGen);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	*ppIGenText = m_pITextGen;
	(*ppIGenText) -> AddRef();
	return S_OK;
}

// Erweiterung für Topologische Relationen binden -----------------------------
HRESULT OLE2AutoExtension::GetITopoRel (IExtendTopRel2 **ppITopoRel)
{
	*ppITopoRel = NULL;		// für alle Fälle
	
	if (m_pITopoRel == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_Topologie, IID_IExtendTopRel2, (LPVOID *)&m_pITopoRel);

		if (FAILED(hr))	return hr;
	}
	
// erfolgreich gebunden
	*ppITopoRel = m_pITopoRel;
	(*ppITopoRel) -> AddRef();
	return S_OK;
}

// Erweiterung für Buffering binden -------------------------------------------
HRESULT OLE2AutoExtension::GetIBuffer (IExtendBuffer **ppIBuffer)
{
	*ppIBuffer = NULL;		// für alle Fälle
	
	if (m_pIBuffer == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_BufferExtension, IID_IExtendBuffer, (LPVOID *)&m_pIBuffer);

		if (FAILED(hr))	return hr;
	}
	
// erfolgreich gebunden
	*ppIBuffer = m_pIBuffer;
	(*ppIBuffer) -> AddRef();
	return S_OK;
}

// Erweiterung für Buffering binden -------------------------------------------
HRESULT OLE2AutoExtension::GetIObjOper (IExtendObjOper **ppIObjOper)
{
	*ppIObjOper = NULL;		// für alle Fälle
	
	if (m_pIObjOper == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_GeometrieOperationen, IID_IExtendObjOper, (LPVOID *)&m_pIObjOper);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	*ppIObjOper = m_pIObjOper;
	(*ppIObjOper) -> AddRef();
	return S_OK;
}

// Erweiterung für Editierung binden -------------------------------------------
HRESULT OLE2AutoExtension::GetIEdit (IExtendGeoEdit **ppIEdit)
{
	*ppIEdit = NULL;		// für alle Fälle
	
	if (m_pIEdit == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_GeometrieEditierung2, IID_IExtendGeoEdit, 
			(LPVOID *)&m_pIEdit);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	*ppIEdit = m_pIEdit;
	(*ppIEdit) -> AddRef();
	return S_OK;
}

// Erweiterung für Editierung binden -------------------------------------------
HRESULT OLE2AutoExtension::GetIGeoRein (IExtendGeoRein **ppIGeoRein)
{
	*ppIGeoRein = NULL;		// für alle Fälle
	
	if (NULL == m_pIGeoRein) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_GeometrieBereinigung, IID_IExtendGeoRein, 
			(LPVOID *)&m_pIGeoRein);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	*ppIGeoRein = m_pIGeoRein;
	(*ppIGeoRein) -> AddRef();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erweiterung für Visualisierung binden 
HRESULT OLE2AutoExtension::GetIVisInfo (IVisObjExt **ppIVisObj)
{
	*ppIVisObj = NULL;		// für alle Fälle
	
	if (m_pIVisObj == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_ObjVisInfoExtension, IID_IVisObjExt, (LPVOID *)&m_pIVisObj);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	*ppIVisObj = m_pIVisObj;
	(*ppIVisObj) -> AddRef();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** IGetTRiASApplication methods
STDMETHODIMP OLE2AutoExtension::GetApplication (REFIID riid, LPVOID *pIApp)
{
	return AppDisp() -> QueryInterface (riid, pIApp);
}

///////////////////////////////////////////////////////////////////////////////
// TrackPopupMenu für Drag'nDrop (rechte Maus)
HRESULT OLE2AutoExtension::TrackDragPopupMenuRight (
	POINTL *pPt, DWORD *pdwEffect, HPROJECT *phPr, BOOL *pfShowORWnd)
{
	if (NULL == pPt || NULL == pdwEffect || phPr == NULL) 
		return E_POINTER;

	ASSERT(DROPEFFECT_NONE == *pdwEffect);

// Menu anzeigen
CMenu menu;

	VERIFY(menu.LoadMenu(IDR_TRACKDRAGPOPUP));

int iCnt = DEX_GetOpenConnectionCount(QDCWriteAble);
CMenuCommandWrapper Cmds (m_Cmds, 1 == iCnt ? GetWriteAbleDatasource() : HACTCONNECTION);

	if (0 == iCnt) {
	CString strCap, strText;

		strCap.Format (IDS_APPVALUE, g_cbTRiAS);
		VERIFY(0 != strText.LoadString (IDS_NOOPENCONNECTIONS));
		MWind() -> MessageBox (strCap, strText, MB_OK);
		return E_FAIL;
	}

CMenu* pPopup = NULL;

	if (1 == iCnt) {
	// genau eine beschreibbare Datenquelle
		pPopup = menu.GetSubMenu(3);
		if (IsWin40())
			pPopup -> SetDefaultItem(0, true);
	} else {
	// mehr als eine beschreibbare Datenquelle
		pPopup = menu.GetSubMenu(2);

	// Datenquellen an alle Popupmenues einfügen
		AddDataSources (pPopup -> GetSubMenu(0), FALSE, DROPEFFECT_COPY);
		AddDataSources (pPopup -> GetSubMenu(1), TRUE, DROPEFFECT_COPY);
		AddDataSources (pPopup -> GetSubMenu(3), FALSE, DROPEFFECT_MOVE);
		AddDataSources (pPopup -> GetSubMenu(4), TRUE, DROPEFFECT_MOVE);
	}

HRESULT hr = S_OK;

	ASSERT(pPopup != NULL);
	hr = AddMenuOffset (pPopup);
	if (FAILED(hr)) return hr;

UINT uiCmd = pPopup->TrackPopupMenu (
			TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, 
			pPt->x, pPt->y, MWind());

	if (0 == uiCmd)
		hr = E_FAIL;
	else {
		*pdwEffect = m_Cmds.AnalyzeCommand (uiCmd, phPr, pfShowORWnd);
		hr = S_OK;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// TrackPopupMenu für Drag'nDrop (linke Maus)
HRESULT OLE2AutoExtension::TrackDragPopupMenuLeft (
	POINTL *pPt, DWORD *pdwEffect, HPROJECT *phPr, BOOL *pfShowORWnd, BOOL fCopy)
{
	if (NULL == pPt || NULL == pdwEffect || phPr == NULL) 
		return E_POINTER;

	ASSERT(DROPEFFECT_NONE == *pdwEffect);

// Menu anzeigen
CMenu menu;

	VERIFY(menu.LoadMenu(IDR_TRACKDRAGPOPUP));

int iCnt = DEX_GetOpenConnectionCount(QDCWriteAble);
CMenuCommandWrapper Cmds (m_Cmds, 1 == iCnt ? GetWriteAbleDatasource() : HACTCONNECTION);

	if (0 == iCnt) {
	CString strCap, strText;

		strCap.Format (IDS_APPVALUE, g_cbTRiAS);
		VERIFY(0 != strText.LoadString (IDS_NOOPENCONNECTIONS));
		MWind() -> MessageBox (strCap, strText, MB_OK);
		return E_FAIL;
	}

CMenu* pPopup = NULL;

	if (1 < iCnt) {
	// mehr als eine beschreibbare Datenquelle
		pPopup = menu.GetSubMenu(fCopy ? 0 : 1);

	// Datenquellen an alle Popupmenues einfügen
		AddDataSources (pPopup -> GetSubMenu(0), FALSE, fCopy ? DROPEFFECT_COPY : DROPEFFECT_MOVE);
	}

HRESULT hr = S_OK;

	if (NULL != pPopup) {
		hr = AddMenuOffset (pPopup);
		if (FAILED(hr)) return hr;

		if (IsWin40())
			pPopup -> GetSubMenu(0) -> SetDefaultItem(0, true);

	UINT uiCmd = pPopup->TrackPopupMenu (
			TPM_LEFTALIGN|TPM_RIGHTBUTTON|TPM_LEFTBUTTON|TPM_NONOTIFY|TPM_RETURNCMD, 
			pPt->x, pPt->y, MWind());

		if (0 == uiCmd)
			hr = E_FAIL;
		else {
			*pdwEffect = m_Cmds.AnalyzeCommand (uiCmd, phPr, pfShowORWnd);
			hr = S_OK ;
		}
	} 
	else {
		*phPr = m_Cmds.GetDataSourceHandle();
		*pfShowORWnd = FALSE;
		*pdwEffect = fCopy ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
	}
	return hr;
}

// Modifikation eines Menu's (addieren des Menuoffsets) -----------------------
HRESULT OLE2AutoExtension::AddMenuOffset (CMenu *pPopup)
{
	if (NULL == pPopup) 
		return E_FAIL;		// nur für gültige Menu's

UINT nCount = pPopup->GetMenuItemCount();
char cbMenuEntry[_MAX_PATH+1];
HRESULT hr = S_OK;

	for (UINT wItem = 0; wItem < nCount; wItem++) {
	UINT uiMenuState = pPopup->GetMenuState (wItem, MF_BYPOSITION);
	UINT uiMenuID = pPopup->GetMenuItemID (wItem);

		if (uiMenuID == (UINT)-1) {	// PopUpMenu
			AddMenuOffset (pPopup->GetSubMenu(wItem));
			if (FAILED(hr)) return hr;
			
			continue;
		}
		if (uiMenuState & (MF_MENUBARBREAK | MF_MENUBREAK | MF_SEPARATOR))
			continue;
		pPopup->GetMenuString (wItem, cbMenuEntry, sizeof(cbMenuEntry), MF_BYPOSITION);
		pPopup->ModifyMenu (wItem, MF_BYPOSITION | uiMenuState, uiMenuID+MenuOffset(), cbMenuEntry);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sämtliche beschreibbaren Datenquellen im Menu verewigen
typedef struct tagENUMDATASOURCES {
	CMenu *pPopup;
	CMenuCommands *pCmdIDs;
	BOOL fShowORWnd;
	DWORD dwEffect;
} ENUMDATASOURCES;

extern "C"
BOOL CALLBACK EnumDataSources (LONG hPr, BOOL, void *pData)
{
	if (DEX_GetROModeEx (reinterpret_cast<HPROJECT>(hPr)))
		return TRUE;		// nicht beschreibbar

ENUMDATASOURCES *pEDS = reinterpret_cast<ENUMDATASOURCES *>(pData);
char cbBuffer[_MAX_PATH];

	if (DEX_GetDataSourceShortName(reinterpret_cast<HPROJECT>(hPr), cbBuffer)) {
	UINT uiCmd = pEDS -> pCmdIDs -> GetNextCmdID();

		if (pEDS -> pPopup -> InsertMenu (0, MF_BYPOSITION|MF_STRING, uiCmd, cbBuffer))
			pEDS -> pCmdIDs -> AddCommand (reinterpret_cast<HPROJECT>(hPr), uiCmd, pEDS -> fShowORWnd, pEDS -> dwEffect);
	}
	return TRUE;
}

HRESULT OLE2AutoExtension::AddDataSources (
	CMenu *pPopup, BOOL fShowORWnd, DWORD dwEffect, BOOL fEmpty)
{
// evtl. sämtliche existierenden Einträge entfernen
	if (fEmpty) {
	int iCnt = pPopup -> GetMenuItemCount();

		while (iCnt-- > 0)
			pPopup -> RemoveMenu (0, MF_BYPOSITION);
	}

// jetzt alle beschreibbaren Datenquellen einfügen, IDs zuordnen und speichern
ENUMDATASOURCES EDS;

	EDS.pPopup = pPopup;
	EDS.pCmdIDs = &m_Cmds;
	EDS.fShowORWnd = fShowORWnd;
	EDS.dwEffect = dwEffect;

ENUMNOKEYLONG ENK;

	ENK.eFcn = (ENUMNOKEYLONGPROC)EnumDataSources;
	ENK.ePtr = &EDS;
	DEX_EnumDataSourceHandles(ENK);
	return S_OK;
}


extern "C"
BOOL CALLBACK FindWriteAbleDataSource (LONG hPr, BOOL, void *pData)
{
	if (DEX_GetROModeEx (reinterpret_cast<HPROJECT>(hPr)))
		return TRUE;		// nicht beschreibbar

	*reinterpret_cast<HPROJECT *>(pData) = reinterpret_cast<HPROJECT>(hPr);
	return FALSE;			// einer reicht
}

HPROJECT OLE2AutoExtension::GetWriteAbleDatasource()
{
HPROJECT hPr = HACTCONNECTION;
ENUMNOKEYLONG ENK;

	ENK.eFcn = (ENUMNOKEYLONGPROC)FindWriteAbleDataSource;
	ENK.ePtr = &hPr;
	DEX_EnumDataSourceHandles(ENK);
	return hPr;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert entweder _DGeoDocument oder DISP_E_NOPARAM
HRESULT OLE2AutoExtension::GetCorrespondingDocument(HPROJECT hPr, CComVariant &rvDoc)
{
	V_VT(&rvDoc) = VT_ERROR;
	V_ERROR(&rvDoc) = DISP_E_PARAMNOTFOUND;

	if (NULL == hPr) return S_OK;

WDDocument Doc;
HRESULT hr = App() -> FGetDocDispHandle (hPr, NULL, Doc.ppi());

	if (SUCCEEDED(hr)) {
		V_VT(&rvDoc) = VT_DISPATCH;
		V_DISPATCH(&rvDoc) = Doc.detach();
	}
	return hr;
}

#if defined(_SUPPORT_QUERYDEFS)
///////////////////////////////////////////////////////////////////////////////
// Nachsehen, ob Zuordnungsobjektklassen verfügbar sind
DefineSmartInterface(TriasXtension);

BOOL OLE2AutoExtension::HasQueryDef()
{
WTriasXtension QueryDef;

	if (SUCCEEDED(QueryDef.CreateInstance (CLSID_QueryDefExt))) 
		return QueryDef -> GetCapabilities (DEXCAP_NOTLOADED) ? FALSE : TRUE;

	return FALSE;
}
#endif // defined(_SUPPORT_QUERYDEFS)


/////////////////////////////////////////////////////////////////////////////
// OKS behandeln (globale Funktionen)

namespace {

// eigentlich passiert ja alles hier in der folgenden Klasse
	class COKSRegExpr :
		public os_regexp
	{
	public:
		COKSRegExpr() { pattern (g_cbOKS); }

		bool StringIsOKS (BSTR bstrToTest, BSTR *pbstrStripped = NULL, BSTR *pbstrAppendix = NULL)
		{ 
			USES_CONVERSION;

		// Eingabezeichenkette analysieren
		os_string strToTest (OLE2A(bstrToTest));
		int iMatched = match(strToTest);

			if (iMatched <= 0) 
				return false; 

		os_string strT;

			if (group(7).size() > 0) {
			// vierter Fall gefunden (Monikerformat)
				strT = group(7);
				if (NULL != pbstrAppendix) {
					_ASSERTE(group(8).size() > 0);

				CComBSTR bstrApp (os_string(group(8)).c_str());

					*pbstrAppendix = bstrApp.Detach();
				}

			} else if (group(4).size() > 0) {
			// dritter Fall gefunden ('[hexdigits]...')
				strT = group(4);
				if (NULL != pbstrAppendix) {
					_ASSERTE(group(5).size() > 0);

				CComBSTR bstrApp (os_string(group(5)).c_str());

					*pbstrAppendix = bstrApp.Detach();
				}
			} else if (group(1).size() > 0) {
			// ersten Fall gefunden ('[hexdigits]')
				strT = group(1);
			} else if (group(3).size() > 0) {
			// zweiten Fall gefunden ('hexdigits:...')
				strT = group(3);
			} else
				return false;

			if (0 == strT.size()) 
				return false;

		// Resultat liefern, wenn gewünscht
			if (NULL != pbstrStripped) {
			CComBSTR bstrRes (strT.c_str());

				*pbstrStripped = bstrRes.Detach();
			}
			return true;
		}
	};

	COKSRegExpr g_TestOKS;

}; // namespace

bool StringIsOKS (BSTR bstrToStrip, BSTR *pStripped, BSTR *pbstrAppendix)
{
	return g_TestOKS.StringIsOKS (bstrToStrip, pStripped, pbstrAppendix);
}
