// Precompiled Header für TRIAS02.DLL -----------------------------------------
// File: TRIAS02P.HXX

#if !defined(_TRIAS02P_HXX)
#define _TRIAS02P_HXX

#include "TRiAS02Config.h"
#include <TRiASConfig.h>

/////////////////////////////////////////////////////////////////////////////
// 
#include <windows.h>
#include <commdlg.h>
#include <ctl3d.h>

#undef DELETE		// ist dummerweise in WinNT.h definiert

#include <stdlib.h>
#include <tstring>
#include <objbase.h>
//#include <basetsd.h>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

#include <ospace/com/smartif.h>

#include <funcs02.h>

#define _RISDB_NO_STRUCTS
#include <protos.h>
#include <xtension.h>
#include <xtensnx.h>
#include <xtensnn.h>

#include <TRiASDB.h>

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
#include <dblpair.hxx>
#include <strdup.hxx>
#include <attribs.hxx>

#include <CSPoint.h>
#include <CSRectGeom.h>
#include <ctf.hxx>

#if defined(_FORCE_LEGACY_CODE)
#include <geo_obj.hxx>
#include <geo_obj1.hxx>
#else
#include <GeoObjekt.h>
#endif // _FORCE_LEGACY_CODE
#include <geotext.hxx>
#include <komplex.hxx>

#include <db.hxx>
#include <dbasrt02.h>
#include <Versions.h>

/////////////////////////////////////////////////////////////////////////////
// 
#if !defined(_DEBUG) && defined(WIN32)
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
#endif // !_DEBUG && WIN32

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)			#x
#define STR2(x)			STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) "): " #desc)

///////////////////////////////////////////////////////////////////////////////
// helper, um reine [out] Parameter sauber zu halten
inline BSTR *CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != pbstr) {
		::SysFreeString(*pbstr);
		*pbstr = NULL;
	}
	return pbstr;
}

inline VARIANT *CLEARED (CComVariant *pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();
	return pv;
}

#endif // _TRIAS02P_HXX
