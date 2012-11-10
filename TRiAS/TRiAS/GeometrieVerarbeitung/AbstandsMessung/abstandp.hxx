// Precompiled Header für abstand.ext
// File: ABSTANDP.HXX

#ifndef _ABSTANDP_HXX
#define _ABSTANDP_HXX

#include "AbstandConfig.h"
#include <TRiASConfig.h>

#include <windows.h>		// Window-Konstanten und Datenstrukturen
#include <stdio.h>			// FILE, fopen() in abst_aus.hxx
#include <math.h>			// sqrt()
#include <float.h>			// DBL_MAX

#include <tstring>			// string-Klasse von TRiAS (muß VOR commonvu.hxx stehen)

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;	// _Module in C:\MSDEV\OSPACE\ospace\com\src\atlimpl.cpp
#include <ospace/com/smartif.h>	// DefineSmartInterface, TRiASToolBar ... in uiowner.h
#include <basetsd.h>		// INT_PTR

#include <containr.hxx>		// BASED_CODE, ...
#include <copttree.hxx>		// COptTree in numtree.hxx
#include <commonvu.hxx>		// CommonView-Klassen, z.B. Rectangle

#include <itoolbar.h>		// ITRiASUIOwner in abstand.hxx

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_GetObjectType, ...
#include <ixtensn.hxx>		// ITriasXtension2 in xtencatl.hxx
#include <xtencatl.hxx>		// allgemeine Datenstrukturen und Prototypen (CTriasExtension, ...)
#include <xtsnaux.hxx>		// EFUnLoadable, ...
#include <xtsnguid.h>		// IID_ITriasExtension2

#include "errcodes.hxx"		// ErrCode in errinstx.hxx
#include <errinstx.hxx>		// ErrInstall
#include <eieruhr.hxx>		// CEierUhr
#include <dblpair.hxx>		// DoublePair in geo_obj.hxx
#include <numeditx.hxx>		// NumEditX in abst_aus.hxx
#include <dblnumex.hxx>		// DoubleNumEditX in abst_aus.hxx
#include <drawobj.hxx>		// LineObject in dragline.hxx
#include "GeometrM.hxx"		// _GEOMETR_ENTRY in identlst.hxx, geo_obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)
#include "identlst.hxx"		// IdentList in abstand.hxx

#include "geokonst.hxx"		// Posit in geo_obj.hxx
#include <IGeometr.hxx>		// IExtendAbstand2; IInitObjektGeometrie in objgext.hxx;
							//  IExtendTopRel2 für Ankopplung an toporel.ext
#include "geo_obj.hxx"		// EObjekt, ...
#include "objgext.hxx"		// CreateInterfaceOG (muß NACH ctfxmfc.h stehen !!!)
#include "FormatString.hxx" // Format()
#include "koord.hxx"		// BSInASCKoord(), BSKoordinaten(), ...

#include "AbstandM.hxx"		// Manifestkonstanten für abstand.ext
#include "AbstandR.h"		// RessourceKonstanten für diese Erweiterung
#include "abskonst.hxx"		// Konstanten
#include "numtree.hxx"		// ObjNrBaum
#include "abst_aus.hxx"		// AbstandsWerte
#include "dragline.hxx"		// DragLineObject in abstand.hxx

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _ABSTANDP_HXX
