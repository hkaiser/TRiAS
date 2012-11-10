// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 11:48:45 
//
// @doc
// @module StdAfx.h | include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#if !defined(_STDAFX_H__845E7CB6_F2CA_4A88_B72F_5CC728D167B7__INCLUDED_)
#define _STDAFX_H__845E7CB6_F2CA_4A88_B72F_5CC728D167B7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiASOleDBConfig.h"
#include <TRiASConfig.h>

///////////////////////////////////////////////////////////////////////////////
// ospace-STL specific stuff
#if !defined(OS_USE_ALTERNATE_STD)
namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
#endif // !defined(OS_USE_ALTERNATE_STD)

#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/set>
#include <ospace/std/string>

#if !defined(OS_USE_ALTERNATE_STD)
typedef os_string string;
#else
using namespace std;
#endif // !defined(OS_USE_ALTERNATE_STD)

#include <ospace/std/algorithm>
#include <ospace/stlex/pointainer.h>

///////////////////////////////////////////////////////////////////////////////
// eigene Implementationen für AtlTrace etc.
#include <d_lib/d_lib.h>
#include <Atl/DLibWrapper.h>

///////////////////////////////////////////////////////////////////////////////
// ATL/WTL-related stuff 
#include <atlbase.h>
#if _ATL_VER >= 0x0700
#include <atlwin.h>
#endif // _ATL_VER >= 0x0700
#include <atlapp.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <atlcom.h>
#include <atlctl.h>

#include <TRiASOleDB.h>				// _vor_ atldb.h
#include <Atl/OleDB/xatldb.h>		// fixed atldb.h

#if _ATL_VER < 0x0700
#include <atlwin.h>
#endif // _ATL_VER < 0x0700
#include <atlmisc.h>
#include <atldlgs.h>

#include <Atl/atlcomx.h>
#include <Atl/DebugObjectCount.h>	// count objects in debug builds

#include <Atl/OleDB/IRowsetScrollImpl.h>
#include <Atl/OleDB/IDBInfoImpl.h>
#include <Atl/OleDB/AtlArray.h>		// CAtlArray for _ATL_VER < 0x0700

#include <Com/VariantHelpers.h>
#include <Com/BstrHelpers.h>

#include <ospace/com/comerrormacros.h>
#include <Pragmas.h>

#pragma warning (disable: 4192)
#import "tlb/TRiASNativeDB.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("DBRANGEENUM")
#import "tlb/TRiASPRV.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("tagDBBINDING", "tagDBOBJECT", "tagDBBINDEXT", "IErrorLookup", "ITRiASExpression") 

#pragma warning (default: 4192)

#include "OleDBError.h"
#include "Util.h"
#include "OleDbOGC.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__845E7CB6_F2CA_4A88_B72F_5CC728D167B7__INCLUDED_)
