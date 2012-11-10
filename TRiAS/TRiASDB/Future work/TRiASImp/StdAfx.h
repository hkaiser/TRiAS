// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__7BACA165_8C1B_11D1_A00E_0060975566B4__INCLUDED_)
#define AFX_STDAFX_H__7BACA165_8C1B_11D1_A00E_0060975566B4__INCLUDED_

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

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <ospace/com/iterenum.h>
#include <atlbasex.h>
#include <atlcomx.h>
#include <ShlObj.h>

#include <protos.h>
#include <errcodes.hxx>		// FehlerCodes

#if defined(_USE_TRIAS_MESSAGES)
#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#endif // _USE_TRIAS_MESSAGES

#include "Strings.h"		// StringKonstanten
#include "DBUtil.h"			// nützliche Makros
#include "ImpMsg.hmc"		// Messagetable 

#include "Resource.h"

//#include "ReportError.h"	// Error-Methoden
//#include "OneSizeHeap.h"	// class-specific heaps

// EnumeratorObjekt für LPOLESTR's
typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7BACA165_8C1B_11D1_A00E_0060975566B4__INCLUDED)
