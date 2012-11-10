// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 13.08.2001 21:17:26 
//
// @doc
// @module StdAfx.h | Declaration of the <c CStdAfx> class

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#if !defined(_STDAFX_H__D0DFE06E_2BDA_47C2_B6D0_77CCD7E6F5BD__INCLUDED_)
#define _STDAFX_H__D0DFE06E_2BDA_47C2_B6D0_77CCD7E6F5BD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiASXPConfig.h"
#include <TRiASConfig.h>

#include <new> 
#include <memory>

// Include ODS headers
#include <Srv.h>		// Main header file that includes all other header files

///////////////////////////////////////////////////////////////////////////////
// ATL stuff
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/comerrormacros.h>
#include <ospace/com/smartif.h>

///////////////////////////////////////////////////////////////////////////////
// TRiAS  geometry objects
#pragma warning (disable: 4192)	// automatically excluding 'bla' while importing type library 'bla'
#include <GMObjects/PBasic.tlh>
#import "tlb/tdbgeo.tlb" no_namespace raw_native_types raw_interfaces_only named_guids no_implementation \
	exclude("IPersist", "IPersistMemory")
#pragma warning (default: 4192)	// automatically excluding 'bla' while importing type library 'bla'

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
#include "Wrapper.h"

#include "ErrorUtils.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H__D0DFE06E_2BDA_47C2_B6D0_77CCD7E6F5BD__INCLUDED_)
