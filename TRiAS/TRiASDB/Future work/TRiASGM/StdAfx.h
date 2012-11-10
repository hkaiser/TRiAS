// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__39AD80D7_ADE3_11D1_BA28_00600875138A__INCLUDED_)
#define AFX_STDAFX_H__39AD80D7_ADE3_11D1_BA28_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/map>
#include <ospace/std/vector>

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/smartif.h>

#include <protos.h>
#include <errcodes.hxx>		// FehlerCodes

#include <igdo.h>
#include <GMcssTypes.h>
#include <igmcss.h>

#include "DBMsg.hmc"

///////////////////////////////////////////////////////////////////////////////
// some helpfull macros
#if !defined(_countof)
#define _countof(x)		(sizeof(x)/sizeof(x[0]))
#endif // _countof

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#endif // DELETE_OBJ

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__39AD80D7_ADE3_11D1_BA28_00600875138A__INCLUDED)
