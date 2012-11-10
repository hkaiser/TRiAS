// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.C

#include "trias03p.hxx"

char g_pDLLName[_MAX_PATH];
extern "C" HINSTANCE g_hInstance = 0;

#if defined(__XT) && defined(__DEXPROCS)
DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#if _MSC_VER >= 1100
DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
#endif // _MSC_VER >= 1100
#endif // __XT && __DEXPROCS

#if !defined(WIN32)

extern "C"
int FAR PASCAL 
LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine) {

	if (cbHeapSize != 0) UnlockData (0);

// Namen der DLL abfragen
	GetModuleFileName (hInst, g_pDLLName, sizeof(g_pDLLName));
	g_hInstance = hInst;

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else 

#include "trias03.h"

#include <fnamestr.h>

#include <xtsnguid.h>
#include <statguid.h>
#include <eonrguid.h>
#include <srchguid.h>
#include <oprpguid.h>

#include <ioprpini.hxx>
#include <registry.hxx>
#include <TRiASHelper.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "RegObj.h"
#include "Strings.h"

#include "selidprp.hxx"		// PropertyActions
#include "modidprp.hxx"
#include "selobwnd.hxx"
#include "dstobwnd.hxx"
#include "delobprp.hxx"
#include "clsfyprp.hxx"
#include "ImportProp.h"
#include "GenTextPropAct.h"

#include "propseq.hxx"
#include "enumonr.hxx"
#include "statimpl.hxx"

#include "intoprop.hxx"

#include "TextSearchEngine.h"
#include "multipi.h"
#include "RegisterExt.h"

#include "dlldatax.h"		// ProxyStub

#include <initguid.h>
#include <bscrguid.h>
#include <ScriptPropActGuid.h>

#include <ObjekteDoppelnGuid.h>
#include <ObjekteVereinigenGuid.h>

#include "ScriptPropAct.h"
#include "ObjekteDoppeln.h"
#include "ObjekteVereinigen.h"

#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
#include "CoDelegator.h"
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100

#if defined(_DEBUG)
// Count number of objects and number of locks.
extern LONG g_cObj;
extern LONG g_cLock;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// benötigte GUID's
#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
EXTERN_C const CLSID CLSID_TRiASObjectHandleMap = {0xD4C24AD6,0xA5EA,0x11D1,{0xBA,0x31,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const CLSID CLSID_TRiASObjectsHandleMap = {0xCD579673,0xAA9D,0x11D1,{0x85,0x8C,0x00,0x60,0x08,0x75,0x13,0x8A}};
EXTERN_C const CLSID CLSID_FakeTRiASLockFeature = {0x26A3BD85,0x6D09,0x11D2,{0x9E,0xE7,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const CLSID CLSID_CoDelegator = {0x58DAD7D5,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const CLSID CLSID_TRiASFeatureHandleMap = {0x95F58F33,0xDF2C,0x11D1,{0x86,0x06,0x00,0x60,0x08,0x75,0x13,0x8A}};

EXTERN_C const IID LIBID_TRiASDB = {0x1CB3AB53,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID IID_ITRiASPropertyBase = {0x97993C78,0x5FE6,0x11D1,{0xB9,0xE6,0x08,0x00,0x36,0xD6,0x38,0x03}};


EXTERN_C const IID IID_ITRiASLockFeature = {0xAF0CE5D5,0x57D8,0x11D2,{0x9E,0xD0,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID IID_IInitInnerObject = {0x58DAD7D6,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID IID_ITRiASObject = {0x1CB3AB6F,0x2E87,0x11D1,{0x96,0x9D,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID IID_IDelegatorFactory = {0x58DAD7D7,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100

EXTERN_C const IID IID_IInitScriptPropAct = {0x50AECBE6,0x46E8,0x11D2,{0x9E,0xBF,0x00,0x60,0x08,0x44,0x78,0x00}};

///////////////////////////////////////////////////////////////////////////////
// ATL
CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)		// Liste der PropertyActions 
// der RegistryHelper _muß_ der erste sein (HiHi)
	OBJECT_ENTRY(CLSID_TRiASRegistryHelper, CTRiASRegObject)

// PropertyActions 
	OBJECT_ENTRY(CLSID_SelectIdentObjTyp, CSelIDPropAct) 
	OBJECT_ENTRY(CLSID_ModifyIdent, CModIDPropAct) 
	OBJECT_ENTRY(CLSID_SelectFromObjectWindow, CSelObjWndPropAct)
	OBJECT_ENTRY(CLSID_PropertyActionSequence, CPropertySequence)
	OBJECT_ENTRY(CLSID_DestinationObjectWindow, CDestObjWndPropAct)
	OBJECT_ENTRY(CLSID_DeleteObjects, CDelObjPropAct)
	OBJECT_ENTRY(CLSID_ClassifyByObjProp, CClsfyPropAct)
	OBJECT_ENTRY(CLSID_ImportDataPropAct, CImportPropAct)
	OBJECT_ENTRY(CLSID_GenTextPropAct, CGenTextPropAct)
	OBJECT_ENTRY(CLSID_ScriptPropAct, CScriptPropAct)
	OBJECT_ENTRY(CLSID_ObjekteDoppeln, CObjekteDoppeln)
	OBJECT_ENTRY(CLSID_ObjekteVereinigen, CObjekteVereinigen)

// SearchEngines 
	OBJECT_ENTRY(CLSID_TextSearchEngine, CTextSearchEngine) 

// sonstige Objekteinträge
	OBJECT_ENTRY(CLSID_EnumObjectsByNumber, CEnumObjectNumbers)
	OBJECT_ENTRY(CLSID_ProgressIndicator, CProgressIndicator)
	OBJECT_ENTRY(CLSID_MultiProgressIndicator, CMultiProgressIndicator)
	OBJECT_ENTRY(CLSID_RegisterExt, CRegisterExt)

#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
	OBJECT_ENTRY(CLSID_FakeTRiASLockFeature, CTRiASLockFeatureStandAlone)
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
END_OBJECT_MAP()

void TermObjProps (void);	// freigeben der ObjPropCF's

#ifdef _MERGE_PROXYSTUB
extern "C" DWORD g_dwFlags = 0L;
extern "C" HINSTANCE hProxyDll;
#endif

extern "C" 
bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
#ifdef _MERGE_PROXYSTUB
		// erstmal feststellen, ob wirklich mut Proxies/Stubs gearbeitet werden soll
		CCurrentUser reg (TEXT("Software\\uve\\TRiAS\\Config"));

			g_dwFlags = 0L;
			reg.GetDWORD (TEXT("ProxyStub"), g_dwFlags);

		// jetzt evtl. ProxyStub initialisieren
			if (g_dwFlags) {
				hProxyDll = hInst;
				if (!PrxDllMain(hInst, dwReason, lpReserved))
					return FALSE;
			} else
				hProxyDll = NULL;
#endif
		// Namen der DLL abfragen
			GetModuleFileName (hInst, g_pDLLName, sizeof(g_pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (NULL);

			TX_ASSERT(NULL != hTrias);
			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
#if _MSC_VER >= 1100
			g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC2"));
#endif // _MSC_VER >= 1100
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

		// ATL Initialisieren
			_Module.Init (ObjectMap, hInst);
			DisableThreadLibraryCalls (hInst);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
#if defined(WIN32)
		TermObjProps();		// ATL freigeben
		_Module.Term();
#endif // WIN32

#if defined(_DEBUG)
		{
		string strName = g_pDLLName;
		string str = get_name(strName)+get_ext(strName);

			TX_TRACE1(TEXT("%s: exiting:\r\n"), str.c_str());
			if (0 != g_cObj) 
				TX_TRACE1(TEXT("\tInfo: Global object count: %ld\r\n"), g_cObj);
			if (0 != g_cLock) 
				TX_TRACE1(TEXT("\tInfo: Global lock count: %ld\r\n"), g_cLock);
			if (0 != _Module.GetLockCount())
				TX_TRACE1(TEXT("\tInfo: Global ATL lock count: %ld\r\n"), _Module.GetLockCount());
		}
#endif // _DEBUG
		break;
	}

return true;
}

#if defined(_MERGE_PROXYSTUB)
///////////////////////////////////////////////////////////////////////////////
// Testen, ob auf dieser Maschine DCOM enabled ist 
bool IsEnabledDCOM (void)
{
	TX_ASSERT(IsWin40());

CLocalMachine regDCOM (TEXT("SOFTWARE\\Microsoft\\Ole"));
TCHAR cbBuffer[10];
DWORD dwLen = sizeof(cbBuffer);

	if (!regDCOM.GetSubSZ (TEXT("EnableDCOM"), cbBuffer, dwLen))
		return false;

	return !_tcsicmp (cbBuffer, TEXT("y"));
}
#endif // defined(_MERGE_PROXYSTUB)

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Keys
static _ATL_REGMAP_ENTRY regEntryMap[] = 
{
#if _ATL_VER >= 0x0200
// HKCU\Software\uve\TRiAS\Config:ProxyStub
	{ L"PROXYSTUB", NULL },
#else
// HKCU\Software\uve\TRiAS\Config:ProxyStub
	{ TEXT("PROXYSTUB"), NULL },
#endif // _ATL_VER
	{ NULL, NULL },		// EndeKennung
};

HRESULT RegisterAdditionalKeys(bool fRegister)
{
#if defined(_MERGE_PROXYSTUB)
#if _ATL_VER >= 0x0200
	regEntryMap[0].szData = (IsWin40() && (IsWinNT() || IsEnabledDCOM())) ? L"1" : L"0";
#else
	regEntryMap[0].szData = (IsWin40() && (IsWinNT() || IsEnabledDCOM())) ? TEXT("1") : TEXT("0");
#endif // _ATL_VER
#else // _MERGE_PROXY_STUB
#if _ATL_VER >= 0x0200
	regEntryMap[0].szData = L"0";
#else
	regEntryMap[0].szData = TEXT("0");
#endif // _ATL_VER
#endif // defined(_MERGE_PROXYSTUB)

	return SUCCEEDED(_Module.UpdateRegistryFromResource(IDR_REGISTRY, fRegister, regEntryMap));
}

// DllRegisterServer - Adds entries to the system registry --------------------
STDAPI APIENTRY DllRegisterServer (void)
{
#ifdef _MERGE_PROXYSTUB
	if (g_dwFlags) {
		if (FAILED(PrxDllRegisterServer())) 
			return false;
	} 
#endif

	RegisterAdditionalKeys(true);
#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
	DelegatorRegisterServer();
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100

	return _Module.RegisterServer(true);
}

// DllUnregisterServer - Removes entries from the system registry -------------
STDAPI APIENTRY DllUnregisterServer (void)
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif

	RegisterAdditionalKeys(false);
#if !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100
	DelegatorUnregisterServer();
#endif // !defined(_FORCE_LEGACY_CODE) && _MSC_VER >= 1100

	return _Module.UnregisterServer();
}

#endif // WIN32

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
HWND __hWndM = NULL;
UINT __DexCmd = 0;
UINT __DexxCmd = 0;
UINT __DexNotify = 0;

extern "C" _TRIAS03_ENTRY
void FAR EXPORT02 FUNCTYPE InitTrias03 (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify) 
{
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DEXNotify;
}

#if defined(__XT) && defined(__DEXPROCS)

// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
#if defined(_DEBUG)	|| !defined(WIN32)	// ansonsten inline
extern "C" 
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);

	TX_ASSERT(NULL != __hWndM);
	return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#if _MSC_VER >= 1100
extern "C" 
LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	TX_ASSERT(NULL != g_pDexExtensionProc2);
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	TX_ASSERT(::IsWindow(__hWndM));
	return::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _MSC_VER >= 1100
#endif // _DEBUG || !WIN32

extern "C" 
LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	TX_ASSERT(NULL != __hWndM);
	return :: SendMessage (__hWndM, __DexNotify, w, l);
}

extern "C" 
LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	TX_ASSERT(NULL != __hWndM);
	return :: PostMessage (__hWndM, __DexNotify, w, l);
}
#endif // __XT && __DEXPROCS


