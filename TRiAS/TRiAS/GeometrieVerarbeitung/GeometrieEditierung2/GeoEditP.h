// Precompiled Header für GeoEdit.ext
// File: GeoEditP.h

#ifndef _GEOEDITP_H
#define _GEOEDITP_H

#include "GeoEditConfig.h"
#include <TRiASConfig.h>
#pragma warning(disable: 4390)	// empty controlled statement found; is this the intend?

#include <windows.h>
#include <math.h>			// fabs()
#include <float.h>			// DBL_MAX
#include <stdlib.h>			// class exception
#include <basetsd.h>		// INT_PTR

#include <tstring>			// string-Klasse von TRiAS (muß VOR commonvu.hxx stehen)

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;	// _Module in C:\MSDEV\OSPACE\OSPACE\COM\SRC\atlimpl.cpp
#include <ospace/std/list>	// list (STL-Header)
#include <ospace/std/map>	// map (STL-Header)
#include <ospace/com/smartif.h>	// DefineSmartInterface, THROW_FAILED_HRESULT()
#include <ospace/com/iterenum.h>// IEnum<LONG>

#include <containr.hxx>		// CTree in copttree.hxx
#include <copttree.hxx>		// COptTree in identlst.hxx
#include <commonvu.hxx>		// CommonView-Klassen, z.B. Rectangle
#include <drawobj.hxx>		// LineObject in DragLine.h, RectangleObject in Marker.h

#if !defined(DECLSPEC_UUID) && _MSC_VER < 1100
#define DECLSPEC_UUID(x) /**/
#endif // !defined(DECLSPEC_UUID) && _MSC_VER < 1100
#include <triastlb.h>		// ITRiASNotificationSink

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_EnumSelectedObjects, ...
#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtensnn.h>		// DEXN_ObjectCreated
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>		// EFUnLoadable, ...
#include <xtsnguid.h>		// IID_ITriasExtension2

#include <eb.h>				// BScript
#include <ibscript.hxx>

#include "errcodes.hxx"		// ErrCode in errinstx.hxx
#include <eieruhr.hxx>		// CEierUhr
#include <numeditx.hxx>		// NumEditX in dblnumed.hxx
#include <dblnumex.hxx>		// DoubleNumEditX
#include <dblpair.hxx>		// DoublePair in geo_obj.hxx
#include "GeometrM.hxx"		// _GEOMETR_ENTRY in ctfx.hxx (in ctfxmfc.h), geo_obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)
#include "identlst.hxx"		// IdentList

#include "GeoKonst.hxx"		// Posit, ...
#include <IGeometr.hxx>		// IExtendGeoEdit, IObjektGeometrie, ...
#include "geo_obj.hxx"		// EObjekt, ...
#include "ObjGExt.hxx"		// CreateInterfaceOG (muß NACH ctfxmfc.h stehen !!!)
#include "Koord.hxx"		// DBKoordinaten, BSKoordinaten, RealInDBKoord
#include "Zeichnen.hxx"		// DrawLine
#include "DatBank.hxx"		// WriteFeatureText(), FehlerhaftesObjekt()
#include "FormatString.hxx"	// Format()

#include "GeoEditM.h"		// Manifestkonstanten für geoedit.ext
#include "GeoEditR.h"		// RessourceKonstanten für diese Erweiterung
#include "EditKonst.h"		// Winkel
#include "IGeoEdit.h"
#include "GeoEditLib.h"
#include "Marker.h"			// Marker

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _GEOEDITP_H
