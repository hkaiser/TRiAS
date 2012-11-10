// Precompiled Header für TRIAS03.DLL -----------------------------------------
// File: TRIAS03P.HXX

#if !defined(_TRIAS03P_HXX)
#define _TRIAS03P_HXX

#if _MSC_VER >= 1100
#include "TRiAS03Config.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <bool.h>
#include <trias01m.hxx>		// TRIAS01 wird importiert
#include <trias02m.hxx>		// TRIAS02 Deklarationen
#include <trias03m.hxx>		// TRIAS03 Deklarationen

#include <windows.h>
#include <windowsx.h>
#include <ole2.h>

#undef DELETE			// ist dummerweise in WinNT.h definiert

#include <tstring>
#include <stdlib.h>
#include <limits.h>

#if defined(WIN32)
// STL-related stuff ----------------------------------------------------------
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/vector>
#include <ospace/std/list>
#include <ospace/std/set>
#include <ospace/std/map>
#include <ospace/std/string>
#endif // WIN32

#include <protos.h>
#include <xtension.h>
#include <xtensnx.h>
#include <resstrg.h>

// Interfacedeklarationen
#include <ixtensn.hxx>

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
#include <atl20.h>
#undef SubclassWindow	// was defined in windowsx.h
#include <atlctl.h>
#include <Atl/atlcomx.h>
#define DECLARE_STATIC_REGISTRY_RESOURCEID DECLARE_REGISTRY_RESOURCEID
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#include "static\\statreg.h"
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;

#include <ospace/com/iterenum.h>

#if _MSC_VER < 1100
#define DECLSPEC_UUID(x)
#else
#include <TRiASDB.h>
#endif // _MSC_VER < 1100

#include <Helper.h>
#include <TRiASHelper.h>
#endif // WIN32

#include <commonvu.hxx>
#include <containr.hxx>

#include <ristypes.hxx>
#include <errcodes.hxx>
#include <oddlgwin.hxx>
#include <owncombo.hxx>

///////////////////////////////////////////////////////////////////////////////
//
#if defined(WIN32)
inline LONG piInterlockedIncrement (LONG *pVal) 
{ 
	if (IsWin32s()) return ++(*pVal);
	else return InterlockedIncrement (pVal); 
}
inline LONG piInterlockedDecrement (LONG *pVal) 
{
	if (IsWin32s()) return --(*pVal);
	else return InterlockedDecrement (pVal); 
}
#if !defined(_DEBUG)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#if _MSC_VER >= 1100
inline LRESULT DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);

	return::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // _MSC_VER >= 1100
#endif // _DEBUG
#else // WIN32
inline LONG piInterlockedIncrement (LONG *pVal) { return ++(*pVal); }
inline LONG piInterlockedDecrement (LONG *pVal) { return --(*pVal); }
#endif // !WIN32

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);(x)=NULL;}
#endif // _DELETE_OBJ

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MSG(desc)	message(__FILE__ "(" STR2(__LINE__) "): " #desc)

#endif // _TRIAS03P_HXX
