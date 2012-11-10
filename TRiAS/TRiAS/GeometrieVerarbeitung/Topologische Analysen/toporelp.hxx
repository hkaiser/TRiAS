// Precompiled Header für TopoRel.ext
// File: TopoRelP.hxx

#ifndef _TOPORELP_HXX
#define _TOPORELP_HXX

#include "TopoRelConfig.h"

#include <TRiASConfig.h>
#pragma warning(disable: 4390)	// empty controlled statement found; is this the intend?

#include <windows.h>		// Window-Konstanten und Datenstrukturen

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

#include <ContainerWrapper.h>	// CTreeOnStl
#include <Commonvu.hxx>		// CommonView-Klassen (ResID, pWindow, Rectangle, ...)

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_EnumIdentObjects, ...
#include <ixtensn.hxx>		// ITriasXtension2 in xtencatl.hxx
#include <xtencatl.hxx>		// allgemeine Datenstrukturen und Prototypen (CTriasExtension, g_pTE ...)
#include <xtsnaux.hxx>		// EFUnLoadable, ...
#include <xtsnguid.h>		// IID_ITriasExtension2, CLSID_EnumObjectsByNumber, ...

#include <eieruhr.hxx>		// CEierUhr
#include "errcodes.hxx"		// ErrCode in errinstx.hxx
#include <errinstx.hxx>		// ErrInstall

#include <IGeometr.hxx>		// IExtendTopRel2; IInitObjektGeometrie in ObjGExt.hxx
#include "GeometrM.hxx"		// _GEOMETR_ENTRY in geo_obj.hxx
#include "GeoKonst.hxx"		// Posit in geo_obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR Geo_Obj.hxx stehen)
#include "Geo_Obj.hxx"		// EObjekt, ...

#include "TopoRelM.hxx"		// Manifestkonstanten für TopoRel.ext
#include "TopoRelR.h"		// RessourceKonstanten für diese Erweiterung (IDM_ORMENU, ...)
#include "RelKonst.hxx"		// WITH, ...
#include "NumTree.hxx"		// ObjNrBaum

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _TOPORELP_HXX
