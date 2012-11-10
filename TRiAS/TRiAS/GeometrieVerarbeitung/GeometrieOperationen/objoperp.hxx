// Precompiled Header für objoper.ext
// File: ObjOperP.hxx

#ifndef _OBJOPERP_HXX
#define _OBJOPERP_HXX

#include "ObjOperConfig.h"
#include <TRiASConfig.h>
#pragma warning(disable: 4390)	// empty controlled statement found; is this the intend?

#include <windows.h>		// Window-Konstanten und Datenstrukturen
#include <math.h>			// sqrt()
#include <limits.h>			// LONG_MAX,...

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
#include <ospace/com/iterenum.h>// IEnum<LONG>
#include <ospace/std/vector>	// vector
#include <ospace/std/list>		// list
#include <ospace/std/map>		// map (STL-Header)

#include <eb.h>
#include <basetsd.h>		// INT_PTR

#include <containr.hxx>		// CListContainer in cliplist.hxx, CTree in copttree.hxx
#include <copttree.hxx>		// COptTree in identlst.hxx
#include <commonvu.hxx>		// CommonView-Klassen (ResID, pWindow, Rectangle, ...)

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_GetObjectType, ...
#include <xtensnn.h>		// DEXN_ObjectSplitted
#include <ixtensn.hxx>		// ITriasXtension2 in xtencatl.hxx
#include <xtencatl.hxx>		// allgemeine Datenstrukturen und Prototypen (CTriasExtension, ...)
#include <xtsnaux.hxx>		// EFUnLoadable, ...
#include <xtsnguid.h>		// IID_ITriasExtension2
#include <ienumonr.hxx>		// CEnumObjectsByNumber
#include <IPropSeq.hxx>		// IPropertyActionSequence

#include "errcodes.hxx"		// ErrCode in errinstx.hxx
#include <errinstx.hxx>		// ErrInstall
#include <eieruhr.hxx>		// CEierUhr
#include <dblpair.hxx>		// DoublePair in geo_obj.hxx
#include <numeditx.hxx>		// NumEditX in dblnumex.hxx
#include <dblnumex.hxx>		// DoubleNumEditX in SetsOperatDlg.h
#include "GeometrM.hxx"		// _GEOMETR_ENTRY in identlst.hxx, geo_obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)
#include "IdentLst.hxx"		// IdentList in abstand.hxx

#include "GeoKonst.hxx"		// IndPos in IGeometr.hxx; Posit in geo_obj.hxx
#include <IGeometr.hxx>		// IExtendObjOper
#include "Geo_Obj.hxx"		// EObjekt, ...
#include "ClipList.hxx"		// für ClipListe in ObjOper.hxx
#include "Mark_Obj.hxx"		// MarkLine
#include "DatBank.hxx"		// MerkmaleKopieren(), IdentErmitteln(), ParentsUniqueIdents()...
#include "ObjGExt.hxx"		// CreateInterfaceOG (muß NACH ctfxmfc.h stehen !!!)
#include "FormatString.hxx"	// Format()
#include "DataObjectHelp.h"	// GetEnumLONGData(), ...
#include "Koord.hxx"		// BSKoordinaten(), ...

#include "IObjOper.h"		// IGetGeoOperatOptions, ...
#include "ObjOperM.hxx"		// Manifestkonstanten für objoper.ext
#include "PropAct.h"		// CPropertyAction
#include "OpDeklar.hxx"		// DatKop, ObjOp

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#if !defined(ATL_NO_VTABLE)
#define ATL_NO_VTABLE 
#endif // ATL_NO_VTABLE 

#endif // _OBJOPERP_HXX
