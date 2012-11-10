// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#include <afxdb.h>          // MFC database classes
#include <afxpriv.h>		// WM_IDLEUPDATECMDUI

#include <afxcmn.h>			// Win32 Common Controls

#include "lmfcx/lafx.h"
#include "lmfcx/lafxcoll.h"
#include "lmfcx/lafxwin.h"

#ifdef _AFXDLL
// For the MFCDLL build, non-header data is always in _DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA     __based(__segname("_DATA"))
#endif

