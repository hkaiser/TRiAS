// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__F2ACEC38_4D87_11D2_9EC8_006008447800__INCLUDED_)
#define AFX_STDAFX_H__F2ACEC38_4D87_11D2_9EC8_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

#include <tstring>
#include <ospace/std/list>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

///////////////////////////////////////////////////////////////////////////////
// usefull macros
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(!(x)){}else{delete(x); (x)=NULL;}
#endif // DELETE_OBJ

#endif // !defined(AFX_STDAFX_H__F2ACEC38_4D87_11D2_9EC8_006008447800__INCLUDED)
