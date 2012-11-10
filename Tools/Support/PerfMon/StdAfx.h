// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__8FE6105B_9A8D_11D2_9F08_006008447800__INCLUDED_)
#define AFX_STDAFX_H__8FE6105B_9A8D_11D2_9F08_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PerfMonConfig.h"
#include <TRiASConfig.h>

#include <afxwin.h>
#include <afxdisp.h>
#include <winperf.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/vector>
#include <ospace/std/string>

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
#include <Atl/NamedObjTableModule.h>
extern CNamedObjTableModule _Module;
#include <atlcom.h>
#include <Atl/NamedObjects.h>

#include <ospace/com/smartif.h>
#include <Com/PropertyMacros.h>
#include <Atl/CollTempl.h>

#include "PerfMonUtil.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8FE6105B_9A8D_11D2_9F08_006008447800__INCLUDED)
