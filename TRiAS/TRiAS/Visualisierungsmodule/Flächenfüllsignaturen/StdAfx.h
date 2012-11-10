// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#include "FillModeConfig.h"
#include <TRiASConfig.h>

//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <bool.h>
#include <vmdm.hxx>

#include <afxctl.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Xtension etc.
#include <xtension.h>
#include <xtensnx.h>
#include <xtensnxx.h>
#include <xtensnn.h>
#include <xtsnaux.hxx>

#include <tstring>

// VisInfo etc.
#include <vinfomfc.h>

// alles was hier sonst noch gebraucht wir
#include "CGObject.h"
#include "FillParm.h"
#include "FillArea.h"
#include "Helper.h"

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!(x)){;} else { delete (x); (x) = NULL; }
#endif // !defined(DELETE_OBJ)

#if !defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Funktionen, die bei !_DEBUG als inline generiert werden

#if defined(__XT) && defined(__DEXPROCS) 
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // __XT && __DEXPROCS 
#endif //!_DEBUG
