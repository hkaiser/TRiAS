// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C321813F_38C8_4621_BD1A_CA1BBE22A597__INCLUDED_)
#define AFX_STDAFX_H__C321813F_38C8_4621_BD1A_CA1BBE22A597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Pragmas.h>

#include "LineToolsConfig.h"
#include <TRiASConfig.h>

#include "LineToolsUtil.h"

#if defined(__MFC__)
// MFC stuff
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls
#endif // defined(__MFC__)

// ospace stl
#include <tstring>

// ATL stuff
#if defined(__WTL__)

#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlcom.h>
#include <atlwin.h>

#else

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#endif // defined(__WTL__)

#include "crtdbg.h" // _ASSERTE

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/list>


#include <com/DefSmartIf.h>


#include <com/Errormacros2.h>
#include <com/BSTRHelpers.h>
#include <com/VariantHelpers.h>
#include <com/StreamHelpers.h>
#include <com/GUIDHelpers.h>

#include <bool.h>
#include <tstring>

#include <winver.h>	// Definitionen
#include <windef.h>	// Definitionen
#include <protos.h>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <xtensnm.hxx>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C321813F_38C8_4621_BD1A_CA1BBE22A597__INCLUDED)
