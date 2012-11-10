// Precompiled Header für BEGEOD.CTF -----------------------------------------
// File: BEGEODP.HXX

#if !defined(_BEGEODP_HXX)
#define _BEGEODP_HXX

#include <windows.h>
#include <tstring>
#if defined(WIN32)
#include <objbase.h>
#else
#include <compobj.h>
#endif // WIN32
#include <math.h>
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

#include <atl11.h>			// ATL für RegistrySupport
extern CComModule _Module;

#if !defined(_DEBUG) && defined(WIN32)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // !_DEBUG && WIN32

#endif // _BEGEODP_HXX
