// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__FBD0C556_FF77_42FE_A04A_D6B3EE4C40A3__INCLUDED_)
#define AFX_STDAFX_H__FBD0C556_FF77_42FE_A04A_D6B3EE4C40A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MemDiffExtConfig.h"
#include <TRiASConfig.h>

#include "MemDiffExtUtil.h"

// MFC stuff
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls

// ospace stl
namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
#include <ospace/std/string>	// standard string class
typedef os_string string;
#define NPOS os_npos

// ATL stuff
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__FBD0C556_FF77_42FE_A04A_D6B3EE4C40A3__INCLUDED)
