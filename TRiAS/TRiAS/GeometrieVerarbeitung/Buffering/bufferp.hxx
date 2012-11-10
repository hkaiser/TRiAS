// Precompiled Header für buffer.ext
// File: BUFFERP.HXX

#ifndef _BUFFERP_HXX
#define _BUFFERP_HXX

#include "BufferConfig.h"
#include <TRiASConfig.h>

#include <windows.h>		// Window-Konstanten und Datenstrukturen
#include <math.h>			// sqrt()
#include <limits.h>			// LONG_MAX,...
#include <stdlib.h>			// atoi()

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

#include <containr.hxx>		// CTree in copttree.hxx
#include <copttree.hxx>		// COptTree in identlst.hxx
#include <commonvu.hxx>		// CommonView-Klassen (ResID, pWindow, Rectangle, ...)

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_RebuildSight, ...
#include <ixtensn.hxx>		// ITriasXtension in xtencatl.hxx
#include <xtencatl.hxx>		// allgemeine Datenstrukturen und Prototypen (CTriasExtension, ...)
#include <xtsnaux.hxx>		// EFUnLoadable, ...
#include <xtsnguid.h>		// IID_ITriasExtension2

#include "errcodes.hxx"		// ErrCode in errinstx.hxx
#include <errinstx.hxx>		// ErrInstall
#include <eieruhr.hxx>		// CEierUhr
#include <dblpair.hxx>		// DoublePair in geo_obj.hxx
#include <numeditx.hxx>		// NumEditX in buff_ein.hxx
#include <dblnumex.hxx>		// DoubleNumEditX in buff_ein.hxx
#include "GeometrM.hxx"		// _GEOMETR_ENTRY in identlst.hxx, geo_obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)
#include "identlst.hxx"		// IdentList in abstand.hxx

#include "geokonst.hxx"		// Posit in geo_obj.hxx
#include <IGeometr.hxx>		// IExtendBuffer
#include "geo_obj.hxx"		// EObjekt, ...
#include "objgext.hxx"		// CreateInterfaceOG (muß NACH ctfxmfc.h stehen !!!)

#include "bufferm.hxx"		// Manifestkonstanten für buffer.ext
#include "bufkonst.hxx"		// Konstanten (dBuffWidth, ...)
#include "buff_ein.hxx"		// Klasse Parameter

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _BUFFERP_HXX
