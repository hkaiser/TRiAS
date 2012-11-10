// Precompiled Header für TXTROT.VMD ------------------------------------------
// File: TXTROTLP.HXX

#if !defined(_TXTROTLP_HXX)
#define _TXTROTLP_HXX

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#include "TxtRotlConfig.h"
#include <TRiASConfig.h>

#include <windows.h>
#include <tstring>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <crtdbg.h>
		
#include <ole2.h>

#include <commonvu.hxx>

#include <xtension.h>
#include <resstrg.h>

#include <containr.hxx>
#include <errcodes.hxx>

//#define _TRIAS02_ENTRY
//#define EXPORT02
#include <visinfo.hxx>

#include <xtensnx.h>
#include <xtsnaux.hxx>

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!(x)){;} else { delete (x); (x) = NULL; }
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
#endif // __XT && __DEXPROCS 
#endif //!_DEBUG

#endif // _TXTROTLP_HXX
