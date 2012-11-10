// Precompiled Header für TORTEN.VMD ------------------------------------------
// File: TORTENP.HXX

#if !defined(_TORTENP_HXX)
#define _TORTENP_HXX

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#include "TortenConfig.h"
#include <TRiASConfig.h>

#include <windows.h>
#include <tstring>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <crtdbg.h>

#include <ole2.h>
#if !defined(WIN32)
#include <storage.h>
#endif

#include <commonvu.hxx>
#include <containr.hxx>

#include <errcodes.hxx>

#include <xtension.h>
#include <xtensnx.h>

#define EXPORT02
#define _TRIAS02_ENTRY
#define NOSICHT
#include <attribs.hxx>

#include <eieruhr.hxx>

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Funktionen, die bei !_DEBUG als inline generiert werden

#if defined(__XT) && defined(__DEXPROCS) 
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}

inline LRESULT DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // __XT && __DEXPROCS 
#endif //!_DEBUG

#endif // _TORTENP_HXX
