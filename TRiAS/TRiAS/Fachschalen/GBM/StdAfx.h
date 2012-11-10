// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <bool.h>

#include <ospace/std/string>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <ospace/com/iterenum.h>
#include <atlbase.h>
#include <atlcom.h>


#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

#pragma message( "include AFX OLE" )
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC OLE automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

#pragma message( "include AFX DB" )
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

#pragma message( "include AFX DAO" )
#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

#pragma message( "include AFX CMN" )
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

#pragma message( "include AFX CTL" )
#include <afxctl.h>
//#include <afxext.h>
#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

//#pragma message( "include bool.h" )
//#include <bool.h>
//#ifdef _BITMASK
//#pragma message( "_BITMASK wurde definiert!" )
//#endif

#include <tstring>

#pragma message( "include stdio.h" )
#include <stdio.h>
#pragma message( "include stdlib.h" )
#include <stdlib.h>
#pragma message( "include time.h" )
#include <time.h>

#pragma message( "include OT 5.0" )
// Stingray ========
#include "secall.h"
// =================
#ifdef _BITMASK
#pragma message( "_BITMASK wurde definiert!" )
#endif

#pragma message( "include errcodes.hxx" )
#include <errcodes.hxx>         // FehlerCodes

#pragma message( "include triasm.hxx" )
#include <triasm.hxx>
#pragma message( "include xtension.h" )
#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#pragma message( "include xtensnx.h" )
#include <xtensnx.h>            // Konstanten und Datenstrukturen

#pragma message( "include ixtensn.h" )
#include <ixtensn.hxx>          // Interfaces einer Erweiterung
//#include <inotify.h>
#pragma message( "include xtencunk.h" )
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#pragma message( "include xtsnaux.h" )
#include <xtsnaux.hxx>
#include <xtsnprop.hxx>

#pragma message( "include xstring.h" )
#include <xstring.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include "VerzSet.h"
#include "TriDBSet.h"
#include "OrteSet.h"
#include "StrasseSet.h"

#include "NF_PG1.h"
#include "NF_PG1FL.h"
#include "NF_PG1GB.h"
#include "NF_PG2D.h"
#include "NF_PG2H.h"
#include "NF_PG3.h"
#include "NF_OG1.h"
#include "ObjProp.h"
#include "ObjProp2.h"
#include "SetNF_PG4.h"

#include "Strings.h"

#ifndef DELE
#define DELE(x) {     if ( x ) delete x; x = NULL; }
#endif  // DELE

#ifndef DELETE_VEC
#define DELETE_VEC(x) { if ( x ) delete [] x; x = NULL; }
#endif  // DELETE_VEC

#ifndef CLOSE_DELETE
#define CLOSE_DELETE(x) {if(x){ if (x->IsOpen())x->Close();delete x; x=NULL;}}
#endif  // CLOSE_DELETE


#define DEX_BeginModalDialog()              \
	DexExtensionProc((WPARAM)DEX_BEGINDIALOG,(LPARAM)0)
#define DEX_EndModalDialog()              \
	DexExtensionProc((WPARAM)DEX_ENDDIALOG,(LPARAM)0)

//const short DEX_BEGINDIALOG		= 375;	// modaler Dialog wurde erzeugt
//const short DEX_ENDDIALOG		= 376;	// modaler Dialog wurde zerlegt

BOOL FileExist( const char* );
void Fehler( UINT, const char* );
BOOL TestYES( const char* );
BOOL IsDoubleOK( double );
BOOL IsIDEok( const char*, BOOL );

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#endif // DELETE_OBJ
