// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "pheader.h"

#if !defined(WIN32)
#include <tchar.h>
#endif // WIN32

extern "C" char pDLLName[_MAX_PATH] = "";
extern "C" HINSTANCE hDLLInst = NULL;

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
	hDLLInst = hInst;
	
// Namen der DLL abfragen
	GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));

// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, TEXT("DEXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, TEXT("DEXNOTIFICATIONPROCEX"));
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else // WIN32

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			hDLLInst = hInst;
	
		// Namen der DLL abfragen
			GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
HMODULE hTrias = GetModuleHandle (TRIAS_MODULENAME);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, TEXT("DEXNOTIFICATIONPROCEX"));
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
extern HWND __hWndM;
extern UINT __DexCmd;
extern UINT __DexNotify;

#if defined(__XT) && defined(__DEXPROCS)

// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}

LRESULT PASCAL DexNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, false);

return :: SendMessage (__hWndM, __DexNotify, w, l);
}

LRESULT PASCAL DexPostNotificationProc (WPARAM w, LPARAM l)
{
	if (g_pDexNotificationProc)
		return (*g_pDexNotificationProc)(w, l, true);

return :: PostMessage (__hWndM, __DexNotify, w, l);
}

#endif // __XT && __DEXPROCS

}	// extern "C"
