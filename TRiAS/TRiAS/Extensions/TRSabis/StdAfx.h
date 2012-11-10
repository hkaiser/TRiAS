// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__139DED27_68CD_11D2_8CBD_006097A8F384__INCLUDED_)
#define AFX_STDAFX_H__139DED27_68CD_11D2_8CBD_006097A8F384__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TrSABiSConfig.h"
#include <TRiASConfig.h>

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>

#include <tstring>

#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>			// Konstanten und Datenstrukturen

#if defined(__ATL_20_USED__)
using namespace ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#define _ATL_NEW_CCOMSTRUCT
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzelne Objekttypen

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <ospace/com/smartif.h>
#include "macros.h"

// #include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include <xtension.h>
#include <xtensnx.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__139DED27_68CD_11D2_8CBD_006097A8F384__INCLUDED)
