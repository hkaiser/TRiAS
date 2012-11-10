// Precompiled Header für BESSELGK.CTF -----------------------------------------
// File: BESSLGKP.HXX

#if !defined(_BESSLGKP_HXX)
#define _BESSLGKP_HXX

#include <windows.h>
#include <math.h>
#include <tstring>
#if defined(WIN32)
#include <objbase.h>
#else
#include <compobj.h>
#endif // WIN32
#include <protos.h>

#include <xtension.h>
#include <xtensnx.h>
#include <resstrg.h>

#include <commonvu.hxx>
#include <containr.hxx>
#include <dblpair.hxx>
#include <errcodes.hxx>
#include <hdrentrx.hxx>
#include <ctf.h>

#if !defined(_DEBUG) && defined(WIN32)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // !_DEBUG && WIN32

#endif // _BESSLGKP_HXX
