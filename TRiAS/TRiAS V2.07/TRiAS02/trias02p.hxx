// Precompiled Header für TRIAS02.DLL -----------------------------------------
// File: TRIAS02P.HXX

#if !defined(_TRIAS02P_HXX)
#define _TRIAS02P_HXX

#include <windows.h>
#include <commdlg.h>
#include <ctl3d.h>

#include <stdlib.h>
#include <tstring>
#if defined(WIN32)
#include <objbase.h>
#else
#include <compobj.h>
#endif

#if defined(WIN32)
#include <atl11.h>
extern CComModule _Module;
#endif // WIN32

#include <ospace/std/string>
#include <ospace/com/smartif.h>

#include <zprotos.h>
#include <protos.h>
#include <xtension.h>
#include <xtensnx.h>
#include <xtensnn.h>

#include <dbtypes.h>
#include <errdef.h>
#include <zipedb.h>
#include <zforc.h>
#include <risdb.h>

#include <resstrg.h>

#include <commonvu.hxx>
#include <containr.hxx>

#include <ixtensn.hxx>

#include <errcodes.hxx>
#include <errinst.hxx>
#include <ristypes.hxx>
#include <dllbind.hxx>
#include <ctf.hxx>
#include <dblpair.hxx>
#include <strdup.hxx>
#include <attribs.hxx>

#include <geo_inl.hxx>
#include <geo_obj.hxx>
#include <geo_obj1.hxx>
#include <geotext.hxx>
#include <komplex.hxx>
#include <db.hxx>

#include <dbasrt02.h>

#if !defined(_DEBUG) && defined(WIN32)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // !_DEBUG && WIN32

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MSG(desc)	message(__FILE__ "(" STR2(__LINE__) "): " #desc)

#endif // _TRIAS02P_HXX
