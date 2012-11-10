// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "trias01p.hxx"

#include "syncdb.hxx"

CDbAccess *g_pDbMutex = NULL;	// globale ZugriffsKontrolle für DatenBasis

char pDLLName[260];
extern "C" HINSTANCE g_hInstance = NULL;

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

extern "C" {

#if !defined(WIN32)

int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, 
			WORD cbHeapSize, LPSTR lpszCmdLine) 
{
	if (cbHeapSize != 0) UnlockData (0);
	g_hInstance = hInst;
	
// Namen der DLL abfragen
	GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else // WIN32

BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
	
		// Namen der DLL abfragen
			GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (TRIAS_MODULENAME);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

		// DbAccess generieren
			g_pDbMutex = new CDbAccess;
			if (g_pDbMutex == NULL) return false;	// Fehler!

			DisableThreadLibraryCalls (hInst);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		if (g_pDbMutex) delete g_pDbMutex;
		g_pDbMutex = NULL;
		break;
	}

return true;
}

#endif // WIN32

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
HWND __hWndM = 0;
UINT __DexCmd = 0;
UINT __DexxCmd = 0;
UINT __DexNotify = 0;

#if !defined(WIN32)
BOOL WINAPI SetupInterruptHandler (void);
void WINAPI ShutdownInterruptHandler (void);
#endif // WIN32

void FUNCTYPE EXPORT01 InitTrias01 (HWND hWnd, UINT DEXCommand, 
				    UINT DEXXCommand, UINT DexNotify) 
{
// Schnittstelle zum Kern initialisieren
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DexNotify;

#if !defined(WIN32)
// evtl. GP abfangen
	SetupInterruptHandler();
#endif // WIN32
}

// Gezieltes Cleanup der DLL --------------------------------------------------

extern "C" BOOL FUNCTYPE ReleaseErrorTree (void);
extern "C" void FUNCTYPE ReleaseErrorList (void);

void FUNCTYPE EXPORT01 CleanUpTrias01 (void)
{
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

#if !defined(WIN32)
// GP-Handler wieder rücksetzen
	ShutdownInterruptHandler();
#endif // WIN32
}


#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	if (__hWndM) 		// von TRIAS initialisiert
		return :: SendMessage (__hWndM, __DexCmd, w, l);

	return false;
}
#endif // _DEBUG

LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

	if (__hWndM) 		// von TRIAS initialisiert
		return :: SendMessage (__hWndM, __DexNotify, w, l);

	return false;
}

LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

	if (__hWndM) 		// von TRIAS initialisiert
		return :: PostMessage (__hWndM, __DexNotify, w, l);

	return false;
}

#endif // __XT && __DEXPROCS

}	// extern "C"
