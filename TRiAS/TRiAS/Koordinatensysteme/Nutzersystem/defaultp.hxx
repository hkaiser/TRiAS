// Precompiled Header für DEFAULT.CTF -----------------------------------------
// File: DEFAULTP.HXX

#if _MSC_VER >= 1100
#include "DefaultCTFConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>
#include <math.h>
#include <ShlObj.h>

#include <tstring>

#include <xtension.h>
#include <xtensnx.h>

#if defined(__ATL_20_USED__)
#include <atl20.h>
#else
#include <atl11.h>
#endif // __ATL_20_USED__
extern CComModule _Module;

#include <ospace/std/list>
#include <ospace/com/iterenum.h>

#include <atlcomx.h>

#include <commonvu.hxx>
#include <containr.hxx>		// TX_ASSERT

#include <TRiASDB.h>
#include <CSRectGeom.h>

#include "ICtf.h"
#include "Wrapper.h"

#if defined(_USE_LEGACY_CODE)
#if !defined(_DEBUG)
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // !_DEBUG
#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// externe globale Variablen
extern TCHAR g_pDLLName[];		// der Name dieser DLL

