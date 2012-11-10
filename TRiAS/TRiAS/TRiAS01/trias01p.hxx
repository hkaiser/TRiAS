// Precompiled Header für TRIAS01.DLL -----------------------------------------
// File: TRIAS01P.HXX

#if !defined(_TRIAS01P_HXX)
#define _TRIAS01P_HXX

#include "TRiAS01Config.h"
#include <TRiASConfig.h>

#if _MSC_VER >= 1020
#pragma warning (disable: 4800)		// forcing value to bool 'true' or 'false'
#endif // _MSC_VER

#include <bool.h>
#include "trias01m.hxx"				// TRIAS01 Deklarationen
#include "trias02m.hxx"				// TRIAS02 Deklarationen

///////////////////////////////////////////////////////////////////////////////
// 
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <tstring>
#include <stdlib.h>
#include <io.h>
#include <time.h>
#include <ctype.h>
#include <Basetsd.h>

#include <ole2.h>
#include <objbase.h>
#include <new>
#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
#if !defined(OS_USE_ALTERNATE_STD)
using namespace ::ospace::std;
using namespace ::ospace::std::rel_ops;
#else
using namespace std;
#endif // !defined(OS_USE_ALTERNATE_STD)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

extern CComModule _Module;
#include <ospace/com/smartif.h>

///////////////////////////////////////////////////////////////////////////////
//#define NODBIO
#include <dbtypes.h>
#include <protos.h>

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

#include "ResString.h"

#include "switchkc.h"
#include "syncdb.hxx"

#if !defined(_DEBUG) && defined(WIN32)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // !_DEBUG && WIN32

#if !defined(_countof)
#define _countof(x)		(sizeof(x)/sizeof(x[0]))
#endif // _!countof

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)		#x
#define STR2(x)		STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) "): " desc)

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

#endif // _TRIAS01P_HXX
