// DLL - Startupcode ----------------------------------------------------------
// File: LIBMAIN.CXX

#include "trias02p.hxx"

#if defined(WIN32)
#include <registry.hxx>
#include <TRiASMode.h>

#include "kons.hxx"

#include "Strings.h"
#endif // WIN32

extern "C" HINSTANCE g_hInstance = 0;
char g_pDLLName[260];
DWORD g_dwTRiASMode = 0;				// TRiASMode

#if defined(__XT) && defined(__DEXPROCS)
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
#endif // __XT && __DEXPROCS

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern "C" {

#if !defined(WIN32)

int FAR WINAPI LibMain (HINSTANCE hInst, WORD wDataSeg, WORD cbHeapSize, LPSTR lpszCmdLine) {

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

#if defined(_DEBUG)
short g_iKonsFlags = KTDDiagnose;
#endif // _DEBUG

CComModule _Module;

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
		CCurrentUser regCfg (TEXT("Software\\uve\\TRiAS\\Config"));
		DWORD dwSize = sizeof(g_cbTRiAS);

			if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize)) {
				if (g_dwTRiASMode & TRIASMODE_InterTRiAS)
					strcpy (g_cbTRiAS, g_cbCopyrightNameT);		// default: InterTRiAS
				else
					strcpy (g_cbTRiAS, g_cbCopyrightName);		// default: TRiAS
			}

#if defined(_DEBUG)
			if (!IsWin32s()) {
			CCurrentUser regCfg (TEXT("Software\\uve\\TRiAS\\Config"));
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

_TRIAS02_ENTRY
void FUNCTYPE EXPORT02 InitTrias02 (HWND hWnd, UINT DEXCommand, UINT DEXXCommand, UINT DEXNotify) 
{
	__hWndM = hWnd;
	__DexCmd = DEXCommand;
	__DexxCmd = DEXXCommand;
	__DexNotify = DEXNotify;
}

#if defined(__XT) && defined(__DEXPROCS)
#if defined(_DEBUG)
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
return :: SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _DEBUG

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


