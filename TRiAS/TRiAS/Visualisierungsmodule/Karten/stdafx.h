// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define	__STL_OSPACE5__
#include "stl.h"

// KK001211
#include <TRiASConfig.h>


#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxctl.h>         // MFC support for OLE Controls
#include <afxcmn.h>
#include <afxDlgs.h>

#include "lmfcx/lafx.h"
#include "lmfcx/lafxcoll.h"
#include "lmfcx/lafxwin.h"
//#include <lmfcx/lafxCtrl.h>
#include "lpict/pictdef.h"
#include "lpict/picture.h"

// KK001221
#include <ospace/std/string>	// standard string class
typedef os_string string;
#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/list>


#if defined(_DEBUG)
	#define IMPORT_PICT_DLL "lpict42d.lib"
#elif defined(_RDEBUG)
	#define IMPORT_PICT_DLL "lpict42r.lib"
#else
	#define IMPORT_PICT_DLL "lpict42.lib"
#endif

#pragma comment(lib,IMPORT_PICT_DLL)

//#ifndef WIN32
//#include "/msvc/mfc/src/auxdata.h"
//#include "/msvc/mfc/include/afxpriv.h"
//#endif

#define __XT			// 's ist eine Extension
#define __DEXPROCS		// sie kommuniziert nicht mit Messages

#include <errcodes.hxx>
#include <xtension.h>
#include <xtensnx.h>

#include <vismguid.h>
#include <vinfomfc.h>

#ifdef _AFXDLL
// For the MFCDLL build, non-header data is always in _DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA     __based(__segname("_DATA"))
#endif
