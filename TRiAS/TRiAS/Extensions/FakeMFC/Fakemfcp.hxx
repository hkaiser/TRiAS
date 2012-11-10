// Precompiled Header für FAKEMFC.EXT -----------------------------------------
// File: FAKEMFCP.HXX

#if !defined(_FAKEMFCP_HXX)
#define _FAKEMFCP_HXX

#include "FakeMFCConfig.h"
#include <TRiASConfig.h>
#include "FakeMFCConfigVersion.h"

#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)

#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdocob.h>

#include <afxcmn.h>
#include <afxmt.h>

#include <tstring>

///////////////////////////////////////////////////////////////////////////////
// notwendige Makros für solche Konstrukte wie '#pragma message(...)'
#define STR(x)			#x
#define STR2(x)			STR(x)
#define MESSAGE(desc)	message(__FILE__ "(" STR2(__LINE__) ") : " #desc)
#define TODO(desc)		message(__FILE__ "(" STR2(__LINE__) ") : TODO: " #desc)

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff ----------------------------------------------------------
#include <ospace/std/vector>
#include <ospace/std/map>
#include <ospace/std/set>
#include <ospace/std/list>
#include <ospace/std/string>
#include <ospace/std/algorithm>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
using namespace ::ospace::std::rel_ops;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

extern CComModule _Module;		// Hauptmodule für ATL

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

#include <errcodes.hxx>		// FehlerCodes
#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#if _MSC_VER < 1100			// der neue midl generiert sowas
#define DECLSPEC_UUID(x)
#define DECLSPEC_SELECTANY()
#else
#ifndef DECLSPEC_SELECTANY
#define DECLSPEC_SELECTANY  __declspec(selectany)
#endif
#endif // _MSC_VER < 1100

#include <triastlb.h>
#include <dtoolbar.h>
//#include <gdo.h>
#include <TRiASDB.h>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

///////////////////////////////////////////////////////////////////////////////
// Flags aus Registry, die über den Mode von FakeMFC/TRiAS entscheiden 
#define TRIASMODE_SubClassTRiAS		0x01
#define TRIASMODE_HookTRiAS			0x02
#define TRIASMODE_SubClassTRiASView	0x04

#define TRIASMODE_NativeDB			0x00	// Default
#define TRIASMODE_GDO				0x08

#define TRIASMODE_InterTRiAS		0x10

extern DWORD g_dwHookFlags;

#if defined(_USE_SEC_VER0600)
// Stingray-Stuff  (JG 981016)
#include <SecRes.h>			// SECRessourcen (IDD_OPEN_WORKSPACE wird benötigt)

// Stingray Objective Toolkit
#include <ot_dockingwindows.h>	// Objective Toolkit docking windows
#include <ot_toolbar.h>			// Objective Toolkit toolbar/menubar
#include <ot_treectrl.h>		// Objective Toolkit tree/listcontrols
#endif // _USE_SEC_VER0600

///////////////////////////////////////////////////////////////////////////////
// nützliche Makros
#define _countof(array) (sizeof(array)/sizeof(array[0]))

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

///////////////////////////////////////////////////////////////////////////////
// helper, um reine [out] Parameter sauber zu halten
inline BSTR *CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != pbstr) {
		::SysFreeString(*pbstr);
		*pbstr = NULL;
	}
	return pbstr;
}

inline VARIANT *CLEARED (CComVariant *pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();
	return pv;
}

#endif // _FAKEMFCP_HXX
