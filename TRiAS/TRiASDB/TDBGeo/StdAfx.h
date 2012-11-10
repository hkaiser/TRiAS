// stdafx.h : include file for standard system include files,
//	  or project specific include files that are used frequently,
//	  but are changed infrequently

#if !defined(AFX_STDAFX_H__6A0120C7_70C6_11D1_974B_00A024D6F582__INCLUDED_)
#define AFX_STDAFX_H__6A0120C7_70C6_11D1_974B_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TDBGeoConfig.h"
#include <TRiASConfig.h>

#include <afxwin.h>
#include <afxdisp.h>

///////////////////////////////////////////////////////////////////////////////
// STL Stuff

#include <ospace/std/list>
#include <ospace/std/map>
#include <ospace/std/vector>

#include <tstring>
#include <atl/ciid.h>

///////////////////////////////////////////////////////////////////////////////
// ATL Stuff
#include <atl/atl20.h>
#include <atl/atlcomx.h>

//////////////////////////////////////////////////////////////////////////////
// OSPACE Stuff
#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

///////////////////////////////////////////////////////////////////////////////
// Geomedia-Interfaces
#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#define _USE_DGMPOINT
#define _USE_DGMPOINTS
#include <GMObjects/GMObjects.h>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#include <OneSizeHeapList.h>	// class local heaps

//////////////////////////////////////////////////////////////////////////////
// unsere eigenen Erweiterungen
#include <Com/ErrorMacros2.h>
#include <Com/BSTRHelpers.h>
#include <Com/GUIDHelpers.h>

#include <Com/PerfMonContext.h>
#include <Com/PerfMonInstanceMap.h>
#include <Com/PerfMonObjectCount.h>

#include <Atl/DebugObjectCount.h>	// globale Objektzähler für einzelne Objekttypen

///////////////////////////////////////////////////////////////////////////////
// nützliche Makros
#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) {if(NULL==x){}else{delete(x);(x)=NULL;}}
#endif // !DELETE
#if !defined(DELETE_VEC)
#define DELETE_VEC(x) {if(NULL==x){}else{delete[](x);(x)=NULL;}}
#endif // !DELETE

#define _countof(x)	(sizeof(x)/sizeof(x[0]))

#include <Com/SafeArray.h>		// CSafeArray

/////////////////////////////////////////////////////////////////////////////
// Ummappen von Geomedia zu TRiAS - CLSID's
// #AK
typedef map<GUID, GUID> MapOfGUIDS;

extern MapOfGUIDS g_mapTRiAS2GDO;
extern MapOfGUIDS g_mapGDO2TRiAS;

/////////////////////////////////////////////////////////////////////////////
// Koordinatentransformation (mit Tricks und Schlichen wegen der GUID's)
#define TRiASEXTIFACE_IMPORT_OPTIONS raw_interfaces_only raw_dispinterfaces no_namespace named_guids

#import "tlb/TRiASCS.tlb"	TRiASEXTIFACE_IMPORT_OPTIONS \
	exclude("ISpatialReferenceInfo", "INT_PTR") \
	exclude("IStaticCollection", "IEnumCoordSystemNames")

// Map für ClassFactories
#include "ClassFactoryMap.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__6A0120C7_70C6_11D1_974B_00A024D6F582__INCLUDED)
