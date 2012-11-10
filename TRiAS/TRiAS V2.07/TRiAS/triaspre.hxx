// Precompiled Header für TRiAS® ----------------------------------------------
// File: TRIASPRE.HXX

#if !defined(_TRIASPRE_HXX)
#define _TRIASPRE_HXX

#pragma warning (disable: 4304 4114 4786)

///////////////////////////////////////////////////////////////////////////////
// old Implementations
#define _TRIAS_OLDIMPLEMENTATION2	// Font --> CVFont

///////////////////////////////////////////////////////////////////////////////
//
#if !defined(WIN32)
#define OLD_TOOLBOX		// unter Win16 alte Toolbox verwenden	
#define OLD_MASSTAB		// unter Win16 alte Maßstabsanzeige verwenden
#define OLD_COORDS		// unter Win16 alte Koordinatenanzeige verwenden
#define ENABLE_WIN32S_CODE		// unter Win16 wird Win32s-code gebraucht
#define _OLD_DRAGNDROP	// unter Win16 altes FileManager Drag'n Drop
#endif // !WIN32

#define NOPROJEKTION
#define NOGITTER
#define DECLAREMAPFUNCTIONS
#define DECLAREMAPFUNCTIONS_NOTIFY

#define _NEWORMENU		// neues Menu im Recherchefenster

#if !defined(_countof)
#define _countof(x)	(sizeof(x)/sizeof(x[0]))
#endif // _countof

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)) {;} else { delete(x); (x) = NULL; }
#endif // DELETE_OBJ

#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>
// #include <mmsystem.h>

#undef DELETE		// ist in WinNT.h definiert

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <ctl3d.h>

#include <dbdtempl.h>

#include <ole2.h>
#if !defined(WIN32)
#include <storage.h>
#include <shellapi.h>
#include <tchar.h>
#else
#include <objbase.h>
#include <comcat.h>
#endif

#include <protos.h>
#include <zprotos.h>
#include <risdb.h>

#include <xtension.h>
#include <xtensnx.h>
#include <xtensnn.h>

#include <tstring>		// STDCPP

#if defined(WIN32)
#include <atl11.h>
extern CComModule _Module;		// Hauptmodule für ATL

#include <ospace/std/string>
#include <ospace/com/smartif.h>
#endif // WIN32

#include <commonvu.hxx>
#include <stddlg.hxx>
#include <clipbrd.hxx>
#include <drawobj.hxx>
#include <cvext.hxx>
#include <containr.hxx>
#include <dcreator.hxx>
#include <deltree.hxx>
#include <epen.hxx>

#include <ixtensn.hxx>

#include <resstrg.h>
#include <ristypes.hxx>
#include <errcodes.hxx>
#include <errinst.hxx>
#include <attribs.hxx>
#include <geo_obj.hxx>
#include <geo_obj1.hxx>
#include <geotext.hxx>
#include <komplex.hxx>
#include <db.hxx>
#include <transfrm.hxx>
#include <hdrentry.hxx>
#include <ident.hxx>
#include <pbd.hxx>
#include <merkmal.hxx>
#include <objliste.hxx>
#include <profile.hxx>
#include <dllbind.hxx>
#include <objmtree.hxx>
#include <eieruhr.hxx>
#include <ctf.hxx>
#include <numedit.hxx>
#include <dblnumed.hxx>
#include <dblpair.hxx>
#include <muscroll.hxx>
#include <spinctrl.hxx>
#include <bmpbox.hxx>
#include <strdup.hxx>
#include <dbasrt02.h>
#include <funcs03.h>

#include <oddlgwin.hxx>
#include <ownlist.hxx>
#include <ownliste.hxx>

#include "clbmpobj.hxx"
#include "draw_obj.hxx"
#include "drw_obj1.hxx"
#include "iris.hxx"

#if !defined(WIN32)
#include "extmain2.hxx"
#endif // WIN32

#if _MSC_VER <= 1020 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x) /**/
#endif // _MSC_VER <= 1020

#endif // _TRIASPRE_HXX
