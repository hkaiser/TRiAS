// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "trias01p.hxx"

#include "syncdb.hxx"

CDbAccess *g_pDbMutex = NULL;		// globale ZugriffsKontrolle für DatenBasis

char pDLLName[260];
extern "C" HINSTANCE g_hInstance = NULL;

static LONG g_nLockCnt = 0;			// globaler Initialisierungs-Zähler 

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

#if defined(WIN16)

extern "C" 
int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, 
			WORD cbHeapSize, LPSTR lpszCmdLine) 
{
	if (cbHeapSize != 0) UnlockData (0);
	g_hInstance = hInst;
	
// Namen der DLL abfragen
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (hMod, szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;
	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);

	strcpy (pDLLName, OLE2A(pszModule));

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

	return 1;	// erfolgreich installiert
}

#else // WIN16

#include "PerfCounters.h"

#if defined(_USE_COMPRESSED_STREAM)
#include "CompressedStream.h"
#endif // defined(_USE_COMPRESSED_STREAM)

/////////////////////////////////////////////////////////////////////////////
// ClassFactory etc.

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
#if defined(_USE_COMPRESSED_STREAM)
	OBJECT_ENTRY(CLSID_CompressedStream, CCompressedStream)
#endif // defined(_USE_COMPRESSED_STREAM)
END_OBJECT_MAP()

DWORD g_dwFlags = 0;	// REG_USE_PROXYSTUB: use ProxyStub, REG_USE_PERFCOUNTERS: use PerfCounters

extern "C" 
BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
			g_nLockCnt = 0;			// globaler Initialisierungs-Zähler 
	
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
			strcpy (pDLLName, OLE2A(pszModule));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (NULL);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

			DisableThreadLibraryCalls (hInst);
			{
			CRegKey key;

				g_dwFlags = 0L;
				if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
					ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
					ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
				{
				CRegKey cfgkey;

					if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config"))) {
					// Performance Counter verwenden ?
					DWORD dwData = 0L;

						cfgkey.QueryValue (dwData, TEXT("UsePerfCounters"));
						if (dwData) g_dwFlags |= REG_USE_PERFCOUNTERS;

					// NovellTestCode verwenden ?
						dwData = 0L;
						cfgkey.QueryValue (dwData, TEXT("UseNovellTestCode"));
						if (dwData) g_dwFlags |= REG_USE_NOVELLTESTCODE;

					// ThreadSafe DbAccess ?
#if defined(_USE_THREAD_WRAPPER_FOR_DBACCESS)
						dwData = 1L;
#else
						dwData = 0L;
#endif // defined(_USE_THREAD_WRAPPER_FOR_DBACCESS)
						cfgkey.QueryValue (dwData, TEXT("UseThreadSafeDbAccess"));
						if (dwData) g_dwFlags |= REG_USE_THREADSAFE_DBACCESS;
					}
				}
			}

		// DbAccess generieren
			g_pDbMutex = new CDbAccess((g_dwFlags & REG_USE_THREADSAFE_DBACCESS) ? true : false);
			if (g_pDbMutex == NULL) return false;	// Fehler!

			_Module.Init (ObjectMap, hInst);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		if (g_pDbMutex) delete g_pDbMutex;
		g_pDbMutex = NULL;
		_Module.Term();
		break;
	}
	return true;
}

#endif // !WIN16

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
HWND __hWndM = 0;
UINT __DexCmd = 0;
UINT __DexxCmd = 0;
UINT __DexNotify = 0;

#if defined(WIN16)
BOOL WINAPI SetupInterruptHandler (void);
void WINAPI ShutdownInterruptHandler (void);
#endif // WIN16

void InitDatabaseStruct();

extern "C" 
void FUNCTYPE EXPORT01 InitTrias01 (
	HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DexNotify) 
{
// Schnittstelle zum Kern initialisieren
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DexNotify;

// globalen Zähler hochsetzen
	CComGlobalsThreadModel::Increment(&g_nLockCnt);

	CreateErrorTree();
	InitDatabaseStruct();

#if defined(WIN16)
// evtl. GP abfangen
	SetupInterruptHandler();
#endif // WIN16
}

// Gezieltes Cleanup der DLL --------------------------------------------------

extern "C" BOOL FUNCTYPE ReleaseErrorTree (void);
extern "C" void FUNCTYPE ReleaseErrorList (void);

extern "C" 
void FUNCTYPE EXPORT01 CleanUpTrias01 (void)
{
// globalen Zähler runterzählen
	CComGlobalsThreadModel::Decrement(&g_nLockCnt);
	if (0 == g_nLockCnt) {
	// noch offene Datenbanken schließen (ohne commit)
	short i;

		for (i = 0; i < MAXDB; i++) {
			if (db_table[i].db_name != NULL || db_table[i].db_pIStorage != NULL)
				z_close ((HPROJECT)(i+1), false);
		}
		db_free();		// evtl. übrig gebliebenes freigeben (wenn keine DB offen war)

	// Installierte FehlerBehandlungen freigeben
		ReleaseErrorTree();		// ErrInstallListe freigeben

	// FehlerListe freigeben
		ReleaseErrorList();

#if defined(_USE_PERFMON_COUNTERS)
	// PerformanceCounter stoppen
		StopPerfCounters();
#endif // defined(_USE_PERFMON_COUNTERS)
#if defined(WIN16)
	// GP-Handler wieder rücksetzen
		ShutdownInterruptHandler();
#endif // WIN16
	}
}

/////////////////////////////////////////////////////////////////////////////
// register/unregister performance counters
extern "C" __declspec(dllexport)
int __cdecl DllRegisterPerfMon(void)
{
	return RegisterPerfCounters();		
}

extern "C" __declspec(dllexport)
int __cdecl DllUnregisterPerfMon(void)
{
	return UnRegisterPerfCounters();
}

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
extern "C" 
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	if (__hWndM) 		// von TRIAS initialisiert
		return :: SendMessage (__hWndM, __DexCmd, w, l);

	return false;
}
#endif // _DEBUG

extern "C" 
LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	if (__hWndM) 		// von TRIAS initialisiert
		return :: SendMessage (__hWndM, __DexNotify, w, l);

	return false;
}

extern "C" 
LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	if (__hWndM) 		// von TRIAS initialisiert
		return :: PostMessage (__hWndM, __DexNotify, w, l);

	return false;
}

#endif // __XT && __DEXPROCS

