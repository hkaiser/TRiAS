// Precompiled Header für FAKEMFC.EXT -----------------------------------------
// File: FAKEMFCP.HXX

#if !defined(_FAKEMFCP_HXX)
#define _FAKEMFCP_HXX

#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdocob.h>

#include <afxcmn.h>
#include <afxmt.h>

#include <tstring>

#if !defined(DECLSPEC_UUID) && _MSC_VER < 1100
#define DECLSPEC_UUID(x)
#endif // !defined(DECLSPEC_UUID) && _MSC_VER < 1100

// #include <afxpriv.h>			// muß vor ATL geladen werden
#include <atl11.h>
extern CComModule _Module;		// Hauptmodule für ATL

#include <ospace/com/smartif.h>
#include <ospace/com/iterenum.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff ----------------------------------------------------------
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/vector>
#include <ospace/std/map>
#include <ospace/std/list>
#include <ospace/std/string>

#include <errcodes.hxx>		// FehlerCodes
#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#include <triastlb.h>
#include <dtoolbar.h>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

// Flags aus Registry, die über den Mode von FakeMFC entscheiden ------------
#define SUBCLASSTRIAS		0x01
#define HOOKTRIAS			0x02
#define SUBCLASSTRIASVIEW	0x04

extern DWORD g_dwHookFlags;

#endif // _FAKEMFCP_HXX
