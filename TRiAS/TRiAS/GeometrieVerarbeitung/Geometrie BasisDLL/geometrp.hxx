// Precompiled Header für geometr.dll
// File: GeometrP.hxx

#ifndef _GEOMETRP_HXX
#define _GEOMETRP_HXX

#include "GeometryConfig.h"
#include <TRiASConfig.h>
#pragma warning(disable: 4390)	// empty controlled statement found; is this the intend?

#include <windows.h>    // Window-Konstanten und Datenstrukturen
#include <math.h>		// sqrt(), ...
#include <limits.h>     // LONG_MAX
#include <float.h>		// DBL_MAX
#include <stdio.h>      // FILE

#include <ospace/std/vector>	// vector
#include <ospace/std/set>		// set
#include <ospace/std/list>		// list

#include <tstring>		// string-Klasse von TRiAS (muß VOR commonvu.hxx stehen)

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

extern CComModule _Module;			// _Module in C:\MSDEV\OSPACE\ospace\com\src\atlimpl.cpp
#include <ospace/com/smartif.h>		// DefineSmartInterface, THROW_FAILED_HRESULT()
#include <ospace/com/iterenum.h>	// IEnum<LONG>
#include <basetsd.h>	// INT_PTR

#include <containr.hxx>	// CTree für copttree.hxx, CListContainer
#include <copttree.hxx>	// COptTree in identlst.hxx
#include <commonvu.hxx>	// ModeLessDialog
#include <tchar.h>		// LPCTSTR in xtencunk.hxx, _tcsinc()

#include <xtension.h>   // Konstanten und Datenstrukturen für xtensnx.h (OBJGEOMETRIE, ...)
#include <xtensnx.h>	// DEX_Error
#include <ixtensn.hxx>	// ITriasXtensionSite in xtencunk.hxx
#include <xtensnn.h>	// DEXN_ErrorMessage in ctfx.cxx (in ctfxmfc.h)
#include <xtencunk.hxx>	// DESTROYNOTIFYPROC in objgeom.hxx

#include <dblpair.hxx>	// DoublePair in geo_obj.hxx
#include <numeditx.hxx>	// NumEditX in dblnumex.hxx
#include <dblnumex.hxx>	// DoubleNumEditX
#include "GeometrM.hxx"	// _GEOMETR_ENTRY in ctfx.hxx (in ctfxmfc.h), geo_obj.hxx
#include "ctfxmfc.h"	// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)

#include "GeomDLL.hxx"	// InitGeometrie
#include "GeometrR.h"

#include "geokonst.hxx"	// Posit, ...
#include <IGeometr.hxx>	// IInitObjektGeometrie, IObjektGeometrie in objgext.hxx
#include "BasicFunctions.hxx"
#include "geo_obj.hxx"	// EObjekt, ...
#include "geo_obj1.hxx"	// GeoKreis
#include "objgext.hxx"  // CObjGeometrieInit, CObjGeometrieFunkt (muß NACH ctfxmfc.h stehen !!!)
#include "objgeom.hxx"	// ObjektGeometrie (u.a. für geotrias.hxx)
#include "geotrias.hxx"
#include "mark_obj.hxx"	// MarkVertex, MarkLine
#include "koord.hxx"	// DBKoordInReal
#include "strecke.hxx"

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _GEOMETRP_HXX
