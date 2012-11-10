// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__BD1B0ED2_FFAF_11D2_94C3_0080C786297B__INCLUDED_)
#define AFX_STDAFX_H__BD1B0ED2_FFAF_11D2_94C3_0080C786297B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define _TRIAS_DBG_HEADER_DIAGNOSTICS
//#define	_TRIAS_DBG_DEFINES

#include <Pragmas.h>

#include "ExportConfig.h"
#include <TRiASConfig.h>
#include "ExportConfigVersion.h"

// MFC stuff
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcmn.h>			// MFC support for Windows 95 Common Controls

///////////////////////////////////////////////////////////////////////
// STL
#define __STL_OSPACE5__
#include <stl.h>

// ospace stl
namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
#include <ospace/std/string>	// standard string class
typedef os_string string;
#define NPOS os_npos

///////////////////////////////////////////////////////////////////////
// ATL stuff
#define	_ATL_STATIC_REGISTRY

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/smartif.h>
#include <com/DefSmartIf.h>
#include <ospace/com/iterenum.h>

#include <com/Errormacros2.h>
#include <com/BSTRHelpers.h>
#include <com/VariantHelpers.h>
#include <com/StreamHelpers.h>
#include <com/GUIDHelpers.h>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
//#include <tstring>

#include <errcodes.hxx>
#include <hdrentrx.hxx>		// Definition von HDRKEYLENGTH

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BD1B0ED2_FFAF_11D2_94C3_0080C786297B__INCLUDED)
