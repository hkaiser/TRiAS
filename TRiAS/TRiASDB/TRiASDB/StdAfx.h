// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__1CB3AB57_2E87_11D1_969D_00A024D6F582__INCLUDED_)
#define AFX_STDAFX_H__1CB3AB57_2E87_11D1_969D_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#include "TRiASDBConfig.h"
#include <TRiASConfig.h>

#include <trias01m.hxx>

///////////////////////////////////////////////////////////////////////////////
// jetzt alles andere
#include <basetsd.h>

#include <afxwin.h>
#include <afxdisp.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/list>
#include <ospace/std/map>
#include <ospace/std/set>
#include <ospace/std/vector>
#include <ospace/std/string>
#include <ospace/std/algorithm>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
#ifndef _ATL_NO_PRAGMA_WARNINGS
#pragma warning (disable: 4503)		// decorated name length exceeded, name was truncated	
#endif // _ATL_NO_PRAGMA_WARNINGS

namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
typedef os_string string;

#include <atlbase.h>
extern CComModule _Module;
#include <atlconv.h>
#include <atlcom.h>
#include <atlctl.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

#include <ospace/com/iterenum.h>
#include <Atl/atlbasex.h>
#include <Atl/atlcomx.h>
#include <Atl/DispatchImplEx.h>

#include <Com/PerfMonContext.h>
#include <Com/PerfMonInstanceMap.h>
#include <Com/PerfMonObjectCount.h>

#include <Atl/AtlAggregate.h>		// spezielle Version der Aggregierungstemplates
#include <Atl/AtlAggregateAlloc.h>
#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzeöne Objekttypen
#include <Atl/RunTimeObjectMapMgr.h>	// RuntimeObjectMap

#include <OneSizeHeapList.h> // class-specific heaps

#include <protos.h>
#include <errcodes.hxx>		// FehlerCodes

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen

#if defined(_USE_TRIAS_MESSAGES)
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#endif // _USE_TRIAS_MESSAGES

#include <shlobj.h>
#include <ixtnext.hxx>

#include "TRiASDB.h"		// Interface's für diesen Module

#include "DBUtil.h"			// allgemeine Makros
#include "DebugUtil.h"		// DebugHelper 

#include "DBMsg.hmc"		// Messagetable 

#include "ErrorHandling.h"
#include <d_lib/d_lib.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1CB3AB57_2E87_11D1_969D_00A024D6F582__INCLUDED)
