// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include <d4all.h>   

#if !defined(WIN32)
#include <tchar.h>
#endif // WIN32

#include <stdlib.h>		// _MAX_PATH  
#include "version.h"
#include "bttncuri.h"	// ToolButtonFree
#include "gizmoint.h"	// FRegisterControl ()

extern "C" char pDLLName[_MAX_PATH] = "";
extern "C" HINSTANCE hDLLInst = NULL;

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS 
            
extern "C" {            
// BOOL WINAPI _CRT_INIT(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved);
HINSTANCE _hInstance = 0;       // Instanz der Bibliothek

    // alles merken, was zur Kommunikation mit dem Kern notwendig ist
UINT __DexNotify = 0;
HWND __hWndM = NULL;            // Handle des TRIAS-MainWindow
UINT __DexCmd;
UINT __DexxCmd;

E4EXPORT_FCT void FAR PASCAL __export
InitDBaseDLL (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify)
{
    __hWndM = hWnd;
    __DexCmd = DEXCommand;
    __DexxCmd = DEXXCommand;
    __DexNotify = DEXNotify;
}               

// liefert DLL-Versions-Kennung
short FAR PASCAL __export dBaseVersion (void) {
#if defined (CLIPPER) || defined (NDX) || defined (MDX)

    #ifdef CLIPPER
	return Clipper;
    #endif

    #ifdef NDX
	return dBaseIII;
    #endif

    #ifdef MDX
	return dBaseIV;
    #endif

#else
    #error - CLIPPER, NDX, oder MDX muá gesetzt werden !
#endif
}

#if !defined(WIN32)

int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, 
			WORD cbHeapSize, LPSTR lpszCmdLine) 
{
	if (cbHeapSize != 0) 
		UnlockData (0);
		
	OutputDebugString ("Lade DBASEDLL.DLL\n");		
	
	if (!ButtonCurInit (hInst))			// ButtonCur init.
		return 0;
	if (!FRegisterControl (hInst))		// Gizmo init.
		return 0;                                   
		
	OutputDebugString ("ToolBarInit in DBASEDLL.DLL OK !\n");				

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

BOOL APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) 
	{
		case DLL_PROCESS_ATTACH:
		{
			// if (!_CRT_INIT (hInst, dwReason, NULL))
        	//	return FALSE;			

			if (!ButtonCurInit (hInst))			// ButtonCur init
				return FALSE;
			if (!FRegisterControl (hInst))		// Gizmo init.
				return FALSE;
	
			hDLLInst = hInst;

		// 	Namen der DLL abfragen
			GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));
			OutputDebugString("DBASE32D.DLL wird geladen.\r\n");

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

	return TRUE;
}

#endif // WIN32

void FAR PASCAL WEP (int bSystemExit)
{
	OutputDebugString ("WEP in DBASEDLL.DLL\n");				
    ToolButtonFree();
    return;
}
}	// extern "C"
