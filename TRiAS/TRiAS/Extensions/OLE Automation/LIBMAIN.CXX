// StartupCode OLEAUTO.EXT -----------------------------------------------------
// File: LIBMAIN.CXX

#include "precomp.hxx"

extern "C" HINSTANCE g_hInstance = NULL;

#if !defined(WIN32)

extern "C" int PASCAL 
LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine) 
{
	g_hInstance = hInst;
	if (cbHeapSize != 0) UnlockData (0);

return 1;	// erfolgreich installiert
}

#else

bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		g_hInstance = hInst;
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

return true;
}

#endif

