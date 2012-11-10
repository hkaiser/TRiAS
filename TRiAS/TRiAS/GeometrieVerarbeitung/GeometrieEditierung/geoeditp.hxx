// Precompiled Header für geoedit.ext
// File: GEOEDITP.HXX

#if !defined(_GEOEDITP_HXX)
#define _GEOEDITP_HXX


#include "geometrm.hxx"	// _GEOMETR_ENTRY in geo_obj.hxx
#include "geoeditm.hxx"	// Manifestkonstanten für geoedit.ext

#include <windows.h>    // Window-Konstanten und Datenstrukturen
#include <basetsd.h>	// INT_PTR
#include <tstring>		// string-Klasse von TRiAS

#if !defined(WIN32)		// für 16-Bit-Variante
#include <xtensnm.hxx>	// _XTENSN_ENTRY, ...
#include <tchar.h>		// LPCTSTR in xtencunk.hxx
#include <ole2.h>		// ITriasXtension, ... in ixtensn.hxx
#include <shellapi.h>	// HKEY in xtsnaux.hxx
#endif // !WIN32

#include <commonvu.hxx> // CommonView-Klassen, z.B. Rectangle

#include <atl11.h>		// atlcom.h in smartif.h
extern CComModule _Module;	// _Module in C:\MSDEV\OSPACE\ospace\com\src\atlimpl.cpp

#include <xtension.h>   // erweiterungsspezifische Konstanten und Datenstrukturen für xtensnx.h
#include <xtensnx.h>	// DEX_EnumSelectedObjects, ...
#include <ixtensn.hxx>	// ITriasXtension2 in xtencatl.hxx
#include <xtencatl.hxx>	// allgemeine Datenstrukturen und Prototypen (CTriasExtension, ...)
#include <xtsnaux.hxx>  // EFUnLoadable, ...
#include <eieruhr.hxx>	// CEierUhr

#include <containr.hxx>	// CTree in copttree.hxx
#include <copttree.hxx>	// COptTree in geomtree.hxx
#include "registrx.hxx"	// CCurrentUser; den lokalen Header (NICHT den globalen) ziehen !!!

#include "geokonst.hxx"	// Posit in geo_obj.hxx
#include <dblpair.hxx>	// DoublePair in geo_obj.hxx
#include "igeometr.hxx"	// IExtendGeoEdit; IInitObjektGeometrie in objgext.hxx; IExtendGeoRein für
						//  Ankopplung von georein.ext; IExtendObjOper für Ankopplung von objoper.ext
#include "geo_obj.hxx"	// EObjekt, ...
#include "objgext.hxx"  // CreateInterfaceOG

#include <numeditx.hxx>	// NumEdit in dblnumed.hxx
#include <dblnumex.hxx> // DoubleNumEdit in neu_ein.hxx
#include <dllbindx.hxx>	// CDllBindX in ctfx.hxx
#include "ctfx.hxx"		// MEIN modifizierter Header (!!!) für CoordTransX
#include <drawobj.hxx>  // LineObject in dragline.hxx

#include "geotrias.hxx"	// GeometrieAnTRIAS, ...
#include "zeichnen.hxx"	// KanteNeuZeichnen
#include "dragline.hxx" // DragLineObject in geoedit.hxx
#include "identlst.hxx"	// IdentList in neu_ein.hxx
#include "koord.hxx"	// DBKoordinaten, BSKoordinaten, RealInDBKoord
#include "datbank.hxx"	// FehlerhaftesObjekt()

#include "neu_ein.hxx"  // NeuEdWerte
#include "marker.hxx"	// Marker
#include "edikonst.hxx" // AktNeu, Curs
#include "geomtree.hxx"

#include <funcs03.h>	// template<class T> class IEnum in geoedit.hxx
#include <ospace/com/smartif.h>	// DefineSmartInterface, THROW_FAILED_HRESULT(), TRiASToolBar

#include "geoedit.h"    // RessourceKonstanten für diese Erweiterung
#include "ddgeoobj.hxx"	// CEditDropSource

#endif // _GEOEDITP_HXX
