// Precompiled Header für SCRIPT.EXT ------------------------------------------
// File: BSCRIPTP.HXX

#if !defined(_BSCRIPTP_HXX)
#define _BSCRIPTP_HXX

#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)         // debug info truncated

#include <bool.h>

#include <afxole.h>		// OCX-Definitionen
#include <afxext.h>		// MFC extensions (including VB)
#include <afxcoll.h>		// Arrays und Listen
#include <afxcmn.h>

#include <triastlb_i.c>

#include <shlobj.h>

#include <tstring>

#include <ospace/std/iterator>
#include <ospace/std/list>		
#include <ospace/std/map>
#include <ospace/std/set>
#include <ospace/std/vector>

#include <iostream.h>
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
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include <atl11.h>
extern CComModule _Module;

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#define _EBC_ENABLE_INLINES
#include <ebc.h>			// BasicScript
#include <ibscript.hxx>

#if ! defined(WIN32)
#include <ole16.h>
#endif // defined(WIN32) 

#include "bscrext.hxx"
#include "bscript.hxx"		// die Erweiterung selbst

#endif // _BSCRIPTP_HXX
