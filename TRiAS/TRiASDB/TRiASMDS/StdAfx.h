// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__82B90CF8_577B_11D2_8FC9_0060085FC1CE__INCLUDED_)
#define AFX_STDAFX_H__82B90CF8_577B_11D2_8FC9_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define	__ATL_USED__
#include <TRiASConfig.h>

#if defined(_DEBUG)
#define	_ASSERT_ON_THROW_FAILED_HRESULT	// THROW_FAILED_HRESULT liefert Assertion
#define _ATLX_ASSERT_ON_FAILURE

///////////////////////////////////////////////////////////////////////////////
// evtl. ausführliches AddRef/Release Tracking zuschalten
//#define _ATLX_DEBUG_REFCOUNT_WALKSTACK
//#define _USE_IMAGE_HELP					// dabei MSSymbols verwenden

///////////////////////////////////////////////////////////////////////////////
// evtl. Objekte global zählen
//#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT

///////////////////////////////////////////////////////////////////////////////
// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI

///////////////////////////////////////////////////////////////////////////////
// evtl. Ein/Ausgang der Interfaces verfolgen
//#define _DEBUG_FUNCENTRY

#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#define __STL_OSPACE5__
#include <stl.h>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 

//#define	_ATL_DEBUG_QI

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

#include <ospace/com/smartif.h>
#include <com/DefSmartIf.h>
#include <ospace/string/src/regex.h>	// GNU regular expression matcher
#include <ospace/string/regexp.h>

#include <com/BSTRHelpers.h>
#include <com/ErrorMacros2.h>

#include "com/DebugFuncEntry.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__82B90CF8_577B_11D2_8FC9_0060085FC1CE__INCLUDED)
