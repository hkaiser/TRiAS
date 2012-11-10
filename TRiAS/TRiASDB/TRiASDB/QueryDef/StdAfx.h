// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__1BF01AF2_33CF_11D3_94FA_0080C786297B__INCLUDED_)
#define AFX_STDAFX_H__1BF01AF2_33CF_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "QueryDefConfig.h"
#include <TRiASConfig.h>

// MFC stuff
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls

// ospace stl
#include <tstring>
#include <ospace/std/list>
#include <ospace/std/map>

// ATL stuff
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <Atl/atlbasex.h>
#include <Atl/atlcomx.h>
#include <Atl/AtlAggregate.h>		// spezielle Version der Aggregierungstemplates
#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzeöne Objekttypen

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <ipropseq.hxx>
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

#include <TRiASDB.h>
#include <DbMsg.hmc>

#include <ospace/Com/ComErrorMacros.h>
#include <Com/ErrorMacros2.h>

#include "QueryDefUtil.h"
 
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__1BF01AF2_33CF_11D3_94FA_0080C786297B__INCLUDED)
