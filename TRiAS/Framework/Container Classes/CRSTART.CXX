#include "contpre.hxx"

#include <windows.h>

#if !defined(WIN32)
// Every DLL has an entry point LibMain and an exit point WEP.

extern "C" 
int __far __pascal LibMain (unsigned int, int ,int wHeapSize, char *)
{
// The startup code for the DLL initializes the local heap (if there is one)
// with a call to LocalInit which locks the data segment.
	if (wHeapSize != 0)
		UnlockData(0);
	
return 1;   // Indicate that the DLL was initialized successfully.
} 

extern "C" 
int __far __pascal WEP ( int )
{
	return 1;
}

#else

#if defined(__GC__)
#include <gc_cpp.h> 
#endif // __GC__
#define _TRIAS02_ENTRY
#include <registry.hxx>

HINSTANCE g_hInst = NULL;

extern "C" 
bool APIENTRY DllMain (HINSTANCE hInst, DWORD dwReason, LPVOID)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		{
		CCurrentUser regCfg (TEXT("Software\\uve\\TRiAS\\Config"));
		DWORD dwT;

#if defined(__GC__)
			dwT = 0;
			if (regCfg.GetDWORD (TEXT("EnableGC"), dwT))
				GC_Enable_GC = static_cast<GCConfig>(dwT);
#endif // __GC__
		// CFAutoDelete und CFUniqueKey sind immer gültig
			dwT = 0;
			if (regCfg.GetDWORD (TEXT("ContFlags"), dwT))
				g_rgContFlags = static_cast<CONTFLAG>(dwT | CFAutoDelete | CFUniqueKey);
		}
		g_hInst = hInst;
		DisableThreadLibraryCalls (hInst);
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

return true;
}

#endif
