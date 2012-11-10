// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.C

#include "trias03p.hxx"

char g_pDLLName[260];
extern "C" HINSTANCE g_hInstance = 0;

#if defined(__XT) && defined(__DEXPROCS)
DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

extern "C" {

#if !defined(WIN32)

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

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = hInst;
	
		// Namen der DLL abfragen
			GetModuleFileName (hInst, g_pDLLName, sizeof(g_pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (TRIAS_MODULENAME);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

return true;
}

#endif // WIN32

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------
HWND __hWndM = NULL;
UINT __DexCmd = 0;
UINT __DexxCmd = 0;
UINT __DexNotify = 0;

_TRIAS03_ENTRY
void FAR EXPORT02 FUNCTYPE InitTrias03 (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify) 
{
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DEXNotify;
}

#if defined(__XT) && defined(__DEXPROCS)

// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}

LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

return :: SendMessage (__hWndM, __DexNotify, w, l);
}

LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

return :: PostMessage (__hWndM, __DexNotify, w, l);
}
#endif // __XT && __DEXPROCS

}	// extern "C" 

