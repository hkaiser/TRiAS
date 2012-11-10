// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

//#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define _AFX_NO_DAO_SUPPORT
#define _AFX_NO_DB_SUPPORT
#define _AFX_NO_AFXCMN_SUPPORT

#define OS_NO_STREAM_SUPPORT

#include <bool.h>

#include <afxwin.h>         // MFC core and standard components
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

#define _DB_NOFORCE_LIBS
#include <dbdao.h>

#include <tstring>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
using namespace ::ospace::std;
using namespace ::ospace::std::rel_ops;
#include <atl20.h>

extern CComModule _Module;		// Hauptmodule für ATL

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

