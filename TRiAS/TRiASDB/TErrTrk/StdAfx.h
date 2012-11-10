// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__82198CE8_436B_11D2_8FB3_0060085FC1CE__INCLUDED_)
#define AFX_STDAFX_H__82198CE8_436B_11D2_8FB3_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define	__ATL_USED__
#include <TRiASConfig.h>

#define	_ASSERT_ON_THROW_FAILED_HRESULT	// THROW_FAILED_HRESULT liefert Assertion

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

#include <ospace/com/smartif.h>
#include <com/DefSmartIf.h>
#include <ospace/com/iterenum.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__82198CE8_436B_11D2_8FB3_0060085FC1CE__INCLUDED)
