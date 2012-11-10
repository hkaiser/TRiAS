// Precompiled Header für DYNQUERY.EXT 
// File: STDAFX.H

#if !defined(_STDAFX_H)
#define _STDAFX_H

#include <afxctl.h>		// OCX-Definitionen
#include <afxext.h>		// MFC extensions (including VB)
#include <afxcoll.h>	// Arrays und Listen
#include <afxdisp.h>
#include <afxcmn.h>

#include <eb.h>

#include <tstring>
#include <errcodes.hxx>         // FehlerCodes
#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>			// Konstanten und Datenstrukturen
#include <xtensnxx.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff ----------------------------------------------------------
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/map>
#include <ospace/std/string>

#if defined(__ATL_20_USED__)
using namespace std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;

#include <ospace/com/smartif.h>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include <ibscript.hxx>

#include <triastlb.h>
#include <visinfo.h>
#include <TRiASHelper.h>
#include <iobjman.h>
#include "DynQuery.h"

#include <dirisole.h> 

#endif // _STDAFX_H
