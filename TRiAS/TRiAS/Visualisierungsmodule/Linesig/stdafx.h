// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define	__STL_OSPACE5__
#include "stl.h"

#include <afxctl.h>         // MFC support for OLE Controls
#include <afxcmn.h>			// MFC common controls
#include <afxDlgs.h>

#include "lmfcx/lafx.h"
#include "lmfcx/lafxcoll.h"
#include "lmfcx/lafxwin.h"
#include "lmfcx/lafxCtrl.h"		// CTreeCtrlEx & Co.
#include "lpict/pictdef.h"
#include "lpict/picture.h"		// HPBYTE

#define __XT			// 's ist eine Extension
#define __DEXPROCS		// sie kommuniziert nicht mit Messages

#include <errcodes.hxx>
#include <xtension.h>
#include <xtensnx.h>

#include <vismguid.h>
#include <vinfomfc.h>

#ifdef PI
#undef PI
#endif

#ifdef halfPI
#undef halfPI
#endif

#ifdef twoPI
#undef twoPI
#endif

#define	PI		(3.1415926535897932384626433)
#define halfPI	(PI/2.0)
#define	twoPI	(PI*2.0)

#ifdef _AFXDLL
// For the MFCDLL build, non-header data is always in _DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA     __based(__segname("_DATA"))
#endif
