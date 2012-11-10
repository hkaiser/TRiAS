// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__CF461D83_EE47_11D2_9BE4_BAF620524153__INCLUDED_)
#define AFX_STDAFX_H__CF461D83_EE47_11D2_9BE4_BAF620524153__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StatistConfig.h"
#include <TRiASConfig.h>
#include "StatistConfigVersion.h"

//// MFC stuff
//#include <afxwin.h>         // MFC core and standard components
//#include <afxext.h>         // MFC extensions
//#include <afxcmn.h>			// MFC support for Windows 95 Common Controls

// ospace stl
#include <tstring>
#include <ospace/std/algorithm>
#include <ospace/std/list>

// ATL stuff
#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlcom.h>

#include <atlhost.h>
#include <atlctl.h>
#include <atlwin.h>
#include <atlmisc.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlddx.h>
#include <atlcrack.h>
#include <atldlgs.h>
#include <atlframe.h>

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <errcodes.hxx>

#include <itoolbar.h>		// Toolbar und docking support
#include <TRiASHelper.h>
#include <XtsnPropAtl.h>	// Objekteigenschaften

// Interfacewrapper und Fehlerbehandlung
#include <ospace/Com/ComErrorMacros.h>
#include <Com/ErrorMacros2.h>

#include <Atl/DebugObjectCount.h>
#include <Atl/RunTimeObjectMapMgr.h>	// RuntimeObjectMap

///////////////////////////////////////////////////////////////////////////////
// lokales
#include "StatistUtil.h"
#include "StatistApp.h"
#include "Statist.hmc"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
#include "SmartIFs.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CF461D83_EE47_11D2_9BE4_BAF620524153__INCLUDED)
