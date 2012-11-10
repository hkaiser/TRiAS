// Precompiled Header für SCRIPT.EXT ------------------------------------------
// File: BSCRIPTP.HXX

#if !defined(_BSCRIPTP_HXX)
#define _BSCRIPTP_HXX

#if _MSC_VER >= 1100
#include "BasicScriptConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <afxole.h>		// OCX-Definitionen
#include <afxext.h>		// MFC extensions (including VB)
#include <afxcoll.h>		// Arrays und Listen
#include <afxcmn.h>

#include <shlobj.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)

#include <tstring>
#include <ospace/file/path.h>
#include <ospace/std/iterator>
#include <ospace/std/list>		
#include <ospace/std/map>
#include <ospace/std/set>
#include <ospace/std/vector>
#include <ospace/std/iostream>
#include <ospace/std/string>
#include <ospace/std/fstream>

#include <ospace/stream.h>
#include <ospace/header.h> 

#include <stdlib.h>
#include <assert.h>

#if !defined(WIN32)
#include <tchar.h>
#include <shellapi.h>
#endif // WIN32

#include <containr.hxx>
#include <errcodes.hxx>         // FehlerCodes
#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnn.h>
#include <xtensnx.h>		// Konstanten und Datenstrukturen

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

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include <ospace/com/iterenum.h>

#define _EBC_ENABLE_INLINES
#include <ebc.h>			// BasicScript
#include <ibscript.hxx>

#include <xtsnpropatl.h>

#include "bscrext.hxx"
#include "bscript.hxx"		// die Erweiterung selbst

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!x){}else{delete(x);x=NULL;}
#endif // DELETE_OBJ
#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#endif // _BSCRIPTP_HXX
