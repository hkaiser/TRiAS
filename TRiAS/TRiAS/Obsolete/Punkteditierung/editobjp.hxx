// Precompiled Header für EDITOBJ.EXT -----------------------------------------
// File: EDITOBJP.HXX

#if !defined(_EDITOBJP_HXX)
#define _EDITOBJP_HXX

#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include <string>	// für strcpy
#include <stdlib.h>	// für ltoa
#include <direct.h>
#if !defined(WIN32)
#include <shellapi.h>
#include <tchar.h>
#include <storage.h>
#endif // WIN32

#include <resstrg.h>

#include <commonvu.hxx>
#include <drawobj.hxx>

#include <errcodes.hxx>
#include <xtension.h>
#include <xtensnx.h>

#include <ixtensn.hxx>          // Interfaces einer Erweiterung
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

#include <containr.hxx>
#include <objcontx.hxx>

#if defined(WIN32)
#include <iunredo.hxx>          // Interface
#include <ospace/com/atl.h>
extern CComModule _Module;
#include <ospace/com/smartif.h>
#endif // WIN32

#include "identlst.hxx"
#include "shift.hxx"
#include "editobj.hxx"		// Klasse für diese Erweiterung

#endif // _EDITOBJP_HXX
