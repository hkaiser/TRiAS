// StartupCode VISOBJ.EXT -----------------------------------------------------
// File: LIBMAIN.CXX

#include "visobjp.hxx"

extern "C" HINSTANCE hInstance = NULL;

#if !defined(WIN32)

extern "C" int PASCAL 
LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine) 
{
	hInstance = hInst;
	g_pTE = NULL;
	
	if (cbHeapSize != 0) UnlockData (0);

return 1;	// erfolgreich installiert
}

#else

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		hInstance = hInst;
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

return true;
}

#endif

