// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__2DF06A07_E3EF_11D1_8F3E_0060085FC1CE__INCLUDED_)
#define AFX_STDAFX_H__2DF06A07_E3EF_11D1_8F3E_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASCsConfig.h"
#include <TRiASConfig.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#include <stl.h>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>
#include <atlctl.h>

#include <Atl/atlcomx.h>
#include <Atl/AtlDebug.h>
#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzelne Objekttypen

#include <ospace/com/smartif.h>
#include <ospace/com/ComErrorMacros.h>

#include <Com/ErrorMacros2.h>
#include <Com/DebugFuncEntry.h>

#include <GMObjects/GMObjects.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2DF06A07_E3EF_11D1_8F3E_0060085FC1CE__INCLUDED)
