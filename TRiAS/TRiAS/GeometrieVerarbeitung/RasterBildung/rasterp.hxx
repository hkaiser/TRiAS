	// Precompiled Header für Gitter.ext
// File: RasterP.hxx

#ifndef _RASTERP_HXX
#define _RASTERP_HXX

#include "GitterConfig.h"
#include <TRiASConfig.h>

#include <windows.h>		// Window-Konstanten und Datenstrukturen
#include <math.h>			// sin(), ...

#include <tstring>			// string-Klasse von TRiAS (muß VOR commonvu.hxx stehen)

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;
#include <ospace/com/smartif.h>	// DefineSmartInterface, THROW_FAILED_HRESULT()
#include <basetsd.h>		// INT_PTR

//#include <containr.hxx>		// CTree in copttree.hxx
//#include <copttree.hxx>		// COptTree in identlst.hxx
#include <commonvu.hxx>		// CommonView-Klassen (ResID, pWindow, Rectangle, ...)

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_EnumIdentObjects, ...
#include <ixtensn.hxx>		// ITriasXtension2 in xtencatl.hxx
#include <xtencatl.hxx>		// allgemeine Datenstrukturen und Prototypen (CTriasExtension, ...)
#include <xtsnaux.hxx>		// EFUnLoadable, ...
#include <xtsnguid.h>		// IID_ITriasExtension2

#include <dblpair.hxx>		// DoublePair in geo_obj.hxx
#include <numeditx.hxx>		// NumEditX in DblNumEx.hxx
#include <dblnumex.hxx>		// DoubleNumEditX in Koord.hxx
#include "GeometrM.hxx"		// _GEOMETR_ENTRY Geo_Obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)

#include "GeoKonst.hxx"		// Posit in Geo_Obj.hxx
#include <IGeometr.hxx>		// IInitObjektGeometrie in ObjGExt.hxx
#include <TriasHelper.h>	// IProgressIndicator2

#include "Geo_Obj.hxx"		// EObjekt, ...
#include "ObjGExt.hxx"		// CreateInterfaceOG (muß NACH ctfxmfc.h stehen !!!)
#include "FormatString.hxx"	// Format()
#include <ospace/com/iterenum.h>	// IEnum<LONG> in DataObjectHelp.h
#include "DataObjectHelp.h"	// SetHWNDData(), GetHWNDData()

#include "RasterM.hxx"		// Manifestkonstanten für Gitter.ext
//#include "RasterR.h"		// Konstantendefinitionen (IDE_RECHTSWERTOBEN, ...)
#include "GitterKonst.h"	// RQUADRAT, ...


#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _RASTERP_HXX
