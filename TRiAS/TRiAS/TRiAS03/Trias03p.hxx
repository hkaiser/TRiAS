// Precompiled Header für TRIAS03.DLL -----------------------------------------
// File: TRIAS03P.HXX

#if !defined(_TRIAS03P_HXX)
#define _TRIAS03P_HXX

#include "TRiAS03Config.h"
#include <TRiASConfig.h>
#include "TRiAS03ConfigVersion.h"

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

#define _RISDB_NO_STRUCTS
#include <protos.h>
#include <xtension.h>
#include <xtensnx.h>
#include <resstrg.h>

// Interfacedeklarationen
#include <ixtensn.hxx>

#if !defined(WIN16)
///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;

#include <atlbase.h>
#include <atlapp.h>
extern WTL::CAppModule _Module;
#include <atlcom.h>

#undef SubclassWindow	// was defined in windowsx.h
#include <atlhost.h>
#include <atlctl.h>
#include <atlwin.h>
#include <atldlgs.h>
#include <atlmisc.h>
#include <atlcrack.h>

#include <Atl/atlcomx.h>
#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzelne Objekttypen
#define DECLARE_STATIC_REGISTRY_RESOURCEID DECLARE_REGISTRY_RESOURCEID

#else
#error "Must use at least '__ATL_20_USED__'"
#endif // __ATL__

#include <ospace/com/iterenum.h>
#include <ospace/com/comerrormacros.h>

#if _TRiAS_VER < 0x0300
#define DECLSPEC_UUID(x)
#include <Helper.h>
#else
#import "tlb/Helper.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IParseStringPairs2") \
	exclude("IComposeStringPairs")
#include <TRiASDB.h>
#endif // _MSC_VER < 1100

#include <TRiASHelper.h>
#endif // !WIN16

#include <commonvu.hxx>
#include <containr.hxx>

#include <ristypes.hxx>
#include <errcodes.hxx>
#include <oddlgwin.hxx>
#include <owncombo.hxx>

#include <d_lib/d_lib.h>

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
#if _TRiAS_VER >= 0x0300
inline LRESULT DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);

	return::SendMessage (__hWndM, __DexCmd, w, l);
}
extern "C"
inline LRESULT WINAPI DexxExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexxExtensionProc)
		return (*g_pDexxExtensionProc)(w, l);

	return :: SendMessage (__hWndM, __DexxCmd, w, l);
}
#endif // _TRiAS_VER >= 0x0300
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

#define _countof(x)	(sizeof(x)/sizeof(x[0]))

///////////////////////////////////////////////////////////////////////////////
// Helper, um reine [out] Parameter sauber zu halten
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

#endif // _TRIAS03P_HXX
