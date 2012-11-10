// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:42:08 
//
// @doc
// @module StdAfx.h | Precompiled header stuff

#if !defined(_STDAFX_H__E6D222AC_0EB7_4B38_81F2_D0CEC6228A58__INCLUDED_)
#define _STDAFX_H__E6D222AC_0EB7_4B38_81F2_D0CEC6228A58__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#include "TRiASNativeDBConfig.h"
#include <TRiASConfig.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/string>
#include <ospace/std/algorithm>
#include <ospace/std/set>

#ifndef _ATL_NO_PRAGMA_WARNINGS
#pragma warning (disable: 4503)		// decorated name length exceeded, name was truncated	
#endif // _ATL_NO_PRAGMA_WARNINGS

namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
typedef os_string string;

#include <atlbase.h>
#include <atlapp.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atldb.h>

#include <atlwin.h>
#include <atlmisc.h>
#include <atldlgs.h>

#include <ospace/com/iterenum.h>
#include <ospace/com/threadedenum.h>

#include <Atl/atlcomx.h>

///////////////////////////////////////////////////////////////////////////////
// import functions from TRiAS01
#include <protos.h>

#include "Util.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__E6D222AC_0EB7_4B38_81F2_D0CEC6228A58__INCLUDED_)
