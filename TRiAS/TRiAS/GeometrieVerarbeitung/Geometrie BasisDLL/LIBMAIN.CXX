// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "GeometrP.hxx"

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#if _TRiAS_VER >= 0x0300
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
#endif // _TRiAS_VER >= 0x0300
#endif // __XT && __DEXPROCS

HINSTANCE hInstance = NULL;
extern "C" char pDLLName [_MAX_PATH] = "";

extern "C" {
/*
#if !defined(WIN32)

int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine)
{
	if (cbHeapSize != 0) UnlockData (0);

// Namen der DLL abfragen
	GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));
	hInstance = hInst;

// externe Funktionen von TRiAS abfragen
#if defined(__XT) && defined(__DEXPROCS)
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (NULL, "DEXEXTENSIONPROC");
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (NULL, "DEXNOTIFICATIONPROCEX");
#endif // __XT && __DEXPROCS

return 1;	// erfolgreich installiert
}

#else
*/
#if _TRiAS_VER >= 0x0300
CComModule _Module;			// Main module for ATL

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()
#endif // _TRiAS_VER >= 0x0300

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
			hInstance = hInst;
	
		// Namen der DLL abfragen
			GetModuleFileName (hInst, pDLLName, sizeof(pDLLName));

		// externe Funktionen von Trias abfragen
#if defined(__XT) && defined(__DEXPROCS)
		HMODULE hTrias = GetModuleHandle (NULL);

			g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, "DEXEXTENSIONPROC");
			g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, "DEXNOTIFICATIONPROCEX");
#if _TRiAS_VER >= 0x0300
			g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, "DEXEXTENSIONPROC2");
#endif // _TRiAS_VER >= 0x0300
#endif // __XT && __DEXPROCS
#if _TRiAS_VER >= 0x0300
			_Module.Init (ObjectMap, hInst);
#endif // _TRiAS_VER >= 0x0300
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
#if _TRiAS_VER >= 0x0300
		_Module.Term();
#endif // _TRiAS_VER >= 0x0300
		break;
	}

return true;
}

//#endif // WIN32

// alles merken, was zur Kommunikation mit dem Kern notwendig ist -------------

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#if _TRiAS_VER >= 0x0300
LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	return::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _TRiAS_VER >= 0x0300
#endif //_DEBUG

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


//-------------------------------------------------------------------------------------------------
// für App :: Exec (ExecWhileEvent) in buffstat.cxx
//#if defined(WIN32) && defined(__CV__)
#if defined(__CV__)

__declspec(dllimport) int CallAppExec (ExecType et);

int	App :: Exec	(ExecType et)
{
	return CallAppExec (et);
}

#endif // __CV__
