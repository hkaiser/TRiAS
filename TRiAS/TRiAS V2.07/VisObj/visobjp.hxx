// Precompiled Header für VISOBJ.EXT ------------------------------------------
// File: VISOBJP.HXX

#if !defined(_VISOBJP_HXX)
#define _VISOBJP_HXX

#if _MSC_VER >= 1100
#include "VisObjConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include <string.h>	// für strcpy
#include <stdlib.h>
#include <tchar.h>
#include <shellapi.h>

#include <tstring>

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

extern CComModule _Module;
#include <ospace/com/smartif.h>
#endif // WIN32

#include <resstrg.h>

#if defined(EXTVIS)
#include <ole2.h>
#endif

#include <commonvu.hxx>		// CommonVu - eigene Klassendeklarationen
#include <containr.hxx>
#include <errcodes.hxx>		// FehlerCodes
#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
							// Konstanten und Datenstrukturen
#include <xtensnn.h>
#include <xtensnx.h>
#include <xtensnxx.h>

#include <ixtensn.hxx>
#include <xtencatl.hxx>
// #include <xtsnaux.hxx>

#include <errcodes.hxx>
#include <errinstx.hxx>
#include <numeditx.hxx>
#include <rangenum.hxx>

#define _TRIAS02_ENTRY
#define EXPORT02
#include <attribs.hxx>

#include <viserror.hxx>
#include <dllbindx.hxx>

#include <triastlb.h>		// TriasTlb.idl
#include <visinfo.h>		// visinfo.idl

#include "visobj.hxx"		// Klasse für diese Erweiterung

#include <errinstx.hxx>

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)) {} else { delete(x); x=NULL; }
#endif // DELETE_OBJ

#if _MSC_VER <= 1020
#define DECLSPEC_UUID(x)
#endif // _MSC_VER <= 1020

#endif // _VISOBJP_HXX
