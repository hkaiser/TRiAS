// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//      oder häufig verwendete, projektspezifische Include-Dateien,
//      die nur in unregelmäßigen Abständen geändert werden.

#if !defined(AFX_STDAFX_H__5F311067_B950_11D4_A9C5_00104BAF20DA__INCLUDED_)
#define AFX_STDAFX_H__5F311067_B950_11D4_A9C5_00104BAF20DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define __STL_OSPACE5__
#include <stl.h>
#include <TRiASConfig.h>


#define STRICT
#include <afxwin.h>
#include <afxdisp.h>
#include <afxcmn.h>
#include "lmfcx/lafxwin.h"

#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
#define _ATL_STATIC_REGISTRY
#define	_ATL_QI_EXCEPTION

#if !defined(NDEBUG)
#define _ATL_DEBUG_QI
#endif

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include "libTopoMap/libTopoMap.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__5F311067_B950_11D4_A9C5_00104BAF20DA__INCLUDED)
