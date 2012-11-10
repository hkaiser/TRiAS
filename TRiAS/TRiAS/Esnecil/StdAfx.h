// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.11.2000 10:06:49 
//
// @doc
// @module StdAfx.h | Precompiled stuff

#if !defined(_STDAFX_H__202FA6E8_A2F8_4EB5_972E_03F7CEEB6AB5__INCLUDED_)
#define _STDAFX_H__202FA6E8_A2F8_4EB5_972E_03F7CEEB6AB5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "EsnecilConfig.h"
#include <TRiASConfig.h>

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#include <ospace/std/string>
namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
typedef os_string string;

#include <atlbase.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__202FA6E8_A2F8_4EB5_972E_03F7CEEB6AB5__INCLUDED_)
