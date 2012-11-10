#if !defined(AFX_STDAFX_H__2CD725E7_0382_11D2_8F5A_0060085FC1CE__INCLUDED_)
#define AFX_STDAFX_H__2CD725E7_0382_11D2_8F5A_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MapMgrExtConfig.h"
#include <TRiASConfig.h>

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>
#include <afxdisp.h>
#include <afxdlgs.h>
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxext.h>

// ospace stl
namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ospace::std;
using namespace ospace::std::rel_ops;
#include <ospace/std/string>	// standard string class
typedef os_string string;
#define NPOS os_npos

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlwin.h>

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/list>

typedef list<string> list_char;

// ...
#undef AFX_EXT_CLASS
#define AFX_EXT_CLASS       AFX_CLASS_IMPORT

#include "lmfcx/lafxwin.h"
#include "lmfcx/LafxCtrl.h"

#include "LibTopoMap/LibTopoMapStructs.h"

#include "lpict/pictdef.h"
#include "lpict/picture.h"
#include "lpict/pictflt.h"

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#include <xtensnn.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

#include <errcodes.hxx>
#include <errinstx.hxx>

/////////////////////////////////////////////////////////////////////////////
// für die Definition von map< CComBSTR,...> und map<GUID,...>
#include <Com/BstrHelpers.h>
#include <Com/GUIDHelpers.h>

/////////////////////////////////////////////////////////////////////////////
// LibTopoMap etc.
#include <libTopoMap/libTopoMap.h>
#include <McKinney/OleType.h>

///////////////////////////////////////////////////////////////////////////////
// sonstige Makros
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) {if(x){delete (x); (x)=NULL;}}
#endif

#define	_countof(arr) (sizeof(arr)/sizeof(arr[0]))

///////////////////////////////////////////////////////////////////////////////
// globale Datentypdeklarationen
typedef map<CString, GEOPOINT> CoordMap;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2CD725E7_0382_11D2_8F5A_0060085FC1CE__INCLUDED)
