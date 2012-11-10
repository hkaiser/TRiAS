// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__51BB3DD5_0C38_11D2_8F6B_0060085FC1CE__INCLUDED_)
#define AFX_STDAFX_H__51BB3DD5_0C38_11D2_8F6B_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#define _ATL_STATIC_REGISTRY
#define	_ATL_QI_EXCEPTION

#if !defined(NDEBUG)
#define _ATL_DEBUG_QI
#endif

//#define _ATL_DEBUG_QI
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

#define _countof(array) (sizeof(array)/sizeof(array[0]))

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__51BB3DD5_0C38_11D2_8F6B_0060085FC1CE__INCLUDED)
