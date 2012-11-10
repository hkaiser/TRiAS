// Precompiled Header für IMPASC.EXT ------------------------------------------
// File: STDAFX.H

#if !defined(_STDAFX_H)
#define _STDAFX_H

#if _MSC_VER < 1100		
#define __ATL_11_USED__		// MSVC4.2
#elif _MSC_VER < 1200
#define __ATL_20_USED__		// MSDEV5
#else
#define __ATL_30_USED__		// MSDEV6
#endif // _MSC_VER
#define OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
//
#include <afxctl.h>		// OCX-Definitionen
#include <afxext.h>		// MFC extensions (including VB)
#include <afxcoll.h>	// Arrays und Listen
#include <afxdisp.h>
//#include <afxcmn.h>

#if _MSC_VER >= 1100		
#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#endif // _MSC_VER 

#include <tstring>
#include <stdlib.h>

#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>			// Konstanten und Datenstrukturen

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff ----------------------------------------------------------
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/map>
#include <ospace/std/string>

#if defined(__ATL_20_USED__)
using namespace ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

extern CComModule _Module;
#include <ospace/com/smartif.h>

#include <triastlb.h>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include <eb.h>
#include <ibscript.hxx>

#include "MsgBlast.h"
#include "MsgBlast.hxx"		// die Erweiterung selbst

// JG additional includes	// DEX_Aufrufe
#include <xtensnx.h>
/*
#include <tstring>
#include <errcodes.hxx>
#include <triasm.hxx>
#include <xtension.h>
#include <xtensnx.h>
#include <ixtensn.hxx>
#include <xtencunk.hxx>
#include <eb.h>
#include <IBScript.hxx>
#include <xtsnprop.hxx>
#include <xtsnaux.hxx>

#include "strings.h"
*/


#endif // _STDAFX_H
