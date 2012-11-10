// Precompiled Header für TRIAS01.DLL -----------------------------------------
// File: TRIAS01P.HXX

#if !defined(_TRIAS01P_HXX)
#define _TRIAS01P_HXX

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <tstring>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <ctype.h>

#include <ole2.h>
#if defined(WIN32)
#include <objbase.h>

#include <new>
#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER

#else
#include <storage.h>
#endif

//#define NODBIO
#include <protos.h>
#include <zprotos.h>

#include <dbtypes.h>
#include <dioexter.h>
#include <keyexter.h>
#include <htextern.h>
#include <qtextern.h>
#include <errdef.h>
#include <risdb.h>

#include <containr.hxx>
#include <errcodes.hxx>

#include <xtension.h>
#include <xtensnx.h>
#include <xtensnn.h>

#if !defined(_DEBUG) && defined(WIN32)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // !_DEBUG && WIN32

#endif // _TRIAS01P_HXX
