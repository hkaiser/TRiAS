// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__727979C7_ABAD_11D1_A066_0060975566B4__INCLUDED_)
#define AFX_STDAFX_H__727979C7_ABAD_11D1_A066_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

// TRiASsettings laden JG 990118
#define __ATL_USED__
#define __OSPACESTL_USED__
#define __STL_OSPACE5__

#include <TRiASConfig.h>

#include <afxwin.h>
#include <afxdisp.h>
#include <afxdlgs.h>
#include <afxcmn.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/list>
#include <ospace/std/map>
#include <ospace/std/set>
#include <ospace/std/string>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <ospace/com/iterenum.h>
#include <atlbasex.h>
#include <atlcomx.h>
#include <Atl/Ciid.h>

#include <TRiASDB.h>

#include <Math.h>
#include <ShlObj.h>

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'

#include <GMObjects/PBasic.tlh>
#import "tlb/TDBGeo.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IPersist", "IPersistMemory", "_DGMPoint", "_DGMPoints")

#define ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__

#include "macros.h"	// JG990125

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__727979C7_ABAD_11D1_A066_0060975566B4__INCLUDED)
