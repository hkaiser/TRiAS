// Precompiled Header für georein.ext
// File: GEOREINP.HXX

#ifndef _GEOREINP_HXX
#define _GEOREINP_HXX

#include "GeoReinConfig.h"
#include <TRiASConfig.h>

#include <windows.h>		// Window-Konstanten und Datenstrukturen
#include <math.h>			// sqrt(), pow()

#include <tstring>			// string-Klasse von TRiAS (muß VOR commonvu.hxx stehen)

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;	// _Module in C:\MSDEV\OSPACE\ospace\com\src\atlimpl.cpp
#include <ospace/com/smartif.h>	// DefineSmartInterface, THROW_FAILED_HRESULT()
#include <basetsd.h>		// INT_PTR

#include <containr.hxx>		// CListContainer in gerrlist.hxx
#include <commonvu.hxx>		// CommonView-Klassen (ResID, pWindow, Rectangle, ...)

#include <xtension.h>		// erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>		// DEX_Error, ...
#include <ixtensn.hxx>		// ITriasXtension2 in xtencatl.hxx
#include <xtencatl.hxx>		// allgemeine Datenstrukturen und Prototypen (CTriasExtension, ...)
#include <xtsnaux.hxx>		// EFPreLoad
#include <xtsnguid.h>		// IID_ITriasExtension2

#include "errcodes.hxx"		// ErrCode in errinstx.hxx
#include <errinstx.hxx>		// ErrInstall
#include <dblpair.hxx>		// DoublePair in geo_obj.hxx
#include <registrx.hxx>		// CCurrentUser
#include "GeometrM.hxx"		// _GEOMETR_ENTRY in ctfx.hxx (in ctfxmfc.h), geo_obj.hxx
#include "ctfxmfc.h"		// MEIN (!!!) modifizierter Header (muß VOR geo_obj.hxx stehen)

#include "geokonst.hxx"		// Posit in geo_obj.hxx
#include <IGeometr.hxx>		// IExtendGeoRein; IObjektGeometrie in geotrias.hxx
#include "geo_obj.hxx"		// EObjekt, ...
#include "geotrias.hxx"		// OBJGEOMETRIEinEObj(), EFlaecheErzeugen()
#include <numeditx.hxx>		// NumEditX in dblnumex.hxx
#include <dblnumex.hxx>		// DoubleNumEditX in koord.hxx
#include "koord.hxx"		// DBKoordInReal()
#include "FormatString.hxx" // Format()
#include "ErrorCorrection.hxx"

#include "GeoReinM.hxx"		// Manifestkonstanten für georein.ext
#include "GeoReinR.h"		// RessourceKonstanten (IDS_AUTOCLEAR, ...)
#include "ReinKonst.hxx"	// Konstanten dieser Erweiterung
#include "gerrlist.hxx"		// GeoFehlerCreator in badpunkt.hxx, ...
#include "geofehl.hxx"

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _GEOREINP_HXX
