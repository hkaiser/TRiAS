// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "trias02p.hxx"

#if !defined(WIN16)
#include <registry.hxx>
#include <TRiASMode.h>
#include <Com/ClassFactoryCache.h>

#include "kons.hxx"
#include "Strings.h"
#include "MapCaches.h"
#endif // !WIN16

extern "C" HINSTANCE g_hInstance = 0;
char g_pDLLName[260];
DWORD g_dwTRiASMode = 0;				// TRiASMode

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


#if defined(WIN16)

extern "C" 
int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine) {

	if (cbHeapSize != 0) UnlockData (0);

// Namen der DLL abfragen
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hInst, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;
	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

	strcpy (g_pDLLName, OLE2A(pszModule));
	g_hInstance = hInst;

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
	g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (NULL, "DEXEXTENSIONPROC2");
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else

#if defined(_DEBUG) && _TRiAS_VER < 0x0400
extern "C" short g_iKonsFlags = KTDDiagnose;
#endif // _DEBUG

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

CLASSFACTORY_CACHE_BEGIN(ClassFactories)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSRectangleGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPointGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPoint)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSBoundaryGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPolygonGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSPolylineGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSLineGeometry)
	CLASSFACTORY_SIMPLE_CACHE_ENTRY(CLSID_TRiASCSTextPointGeometry)
CLASSFACTORY_CACHE_END()

extern "C" 
bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
	
		// Namen der DLL abfragen
		TCHAR szModule[_MAX_PATH];

			GetModuleFileName (hInst, szModule, _MAX_PATH);

		TCHAR szModuleShort[_MAX_PATH];
		int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
		LPOLESTR pszModule;

			USES_CONVERSION;
			if (cbShortName == _MAX_PATH)
				return false;
			pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

			strcpy (g_pDLLName, OLE2A(pszModule));
			_Module.Init(ObjectMap, hInst);

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (NULL);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, "DEXEXTENSIONPROC2");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

			{
			CCurrentUser reg (g_cbFakeMFCKey);

				g_dwTRiASMode = 
					TRIASMODE_SubClassTRiAS | 
					TRIASMODE_HookTRiAS | 
					TRIASMODE_SubClassTRiASView |
					TRIASMODE_InterTRiAS;
#if defined(_DEBUG)
					g_dwTRiASMode |= TRIASMODE_GDO;
#endif // _DEBUG
				reg.GetDWORD (g_cbTRiASMode, g_dwTRiASMode);
			}

		// TRiASName initialisieren
		CCurrentUser regCfg (TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"));
		DWORD dwSize = sizeof(g_cbTRiAS);

			if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize)) {
#if _TRiAS_VER < 0x0400
				if (g_dwTRiASMode & TRIASMODE_InterTRiAS)
					strcpy (g_cbTRiAS, g_cbCopyrightNameT);		// default: InterTRiAS
				else
#endif // _TRiAS_VER < 0x0400
					strcpy (g_cbTRiAS, g_cbCopyrightName);		// default: TRiAS
			}

#if defined(_DEBUG) && _TRiAS_VER < 0x0400
			if (!IsWin32s()) {
			DWORD dwData = 0L;

				g_iKonsFlags = KTDDiagnose;
				if (regCfg.GetDWORD (TEXT("KonsistenzTest"), dwData))
					g_iKonsFlags = short(dwData);
			}
#endif // _DEBUG
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		_Module.Term();
		break;
	}
	return true;
}

#endif // !WIN16

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
HWND __hWndM = NULL;
UINT __DexCmd = 0;
UINT __DexxCmd = 0;
UINT __DexNotify = 0;

__Interface<ITRiASObjectHandleMap> CMapCaches::m_ObjsMap;
__Interface<ITRiASObjectHandleMap> CMapCaches::m_ObjMap;
__Interface<ITRiASObjectHandleMap> CMapCaches::m_FeatMap;

extern "C" 
_TRIAS02_ENTRY void FUNCTYPE EXPORT02 InitTrias02 (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify) 
{
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DEXNotify;

	ClassFactoryCacheInit(GetClassFactories());
	InitMapCaches();
}

extern "C" 
_TRIAS02_ENTRY void FUNCTYPE EXPORT02 CleanUpTrias02 (void)
{
	FreeMapCaches();
	ClassFactoryCacheTerm(GetClassFactories());
}

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
extern "C" 
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return :: SendMessage (__hWndM, __DexCmd, w, l);
}
extern "C" 
LRESULT WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	TX_ASSERT(NULL != g_pDexExtensionProc2);
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG

extern "C" 
LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	return :: SendMessage (__hWndM, __DexNotify, w, l);
}

extern "C" 
LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	return :: PostMessage (__hWndM, __DexNotify, w, l);
}

#endif // __XT && __DEXPROCS



