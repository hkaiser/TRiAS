// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 09:25:53 
//
// @doc
// @module StdAfx.h | Precompiled Header

#if !defined(_STDAFX_H__BF5417D4_3475_4176_AD34_07027A6B60D8__INCLUDED_)
#define _STDAFX_H__BF5417D4_3475_4176_AD34_07027A6B60D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiASQLConfig.h"
#include <TRiASConfig.h>

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/std/vector>
#include <ospace/std/map>

#include "parser\smartpointers.h"

#define RELEASE(a) if(!a){}else{a->Release(); a=NULL;}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__BF5417D4_3475_4176_AD34_07027A6B60D8__INCLUDED_)
