// Precompiled Header für ODBCEXT.EXT -----------------------------------------
// File: pheader.h

#if !defined(_PHEADER_H)
#define _PHEADER_H

#if _MSC_VER >= 1100
#include "OdbcConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#include <afxole.h>				// MFC-Core, windows.h
#include <afxext.h>				// CToolBar u.a.
#include <afxdb.h>				// DataBase classes

#include "gxall.h"				// GridClasses
#include "gxodbc.h"				// FGridClasses for ODBC

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>				// _fmemcmp ()

#include <tstring>
#include <xtension.h>	
#include <xtensnx.h>

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;

#include <ixtensn.hxx>
#include <xtencatl.hxx>         // CTriasExtension

#include <containr.hxx>			// Container-Klassen
#include <hpp/errcodesodbc.hxx>         // FehlerCodes
#include <hpp/protos.h>				// DELETE ()

#include <ospace/com/smartif.h>
#include <ospace/com/comerrormacros.h>

#include <ospace/std/map>
#include <ospace/std/set>

#ifdef WIN32
	#define __export
	#define _huge
	#include <afxcmn.h>			// CListCtrl (WIN95-Control)
#else
	#include <print.h>
#endif // WIN16

//	globale Konstanten
const short MaxOperators = 17;			// max. Anzahl der verwendeten SQL-Operatoren
const short MaxFunctions = 47;			// max. Anzahl der Skalaren Vektoren
const short KlauselSize = 256;			// Max. Länge der Where-Klausel
const char TableSep = ',';				// Tabellen-Separator
const char TableSQLSep = '.';			// Tabellen-Separator für SQL
const char TableSQLSepStr [] = ".";
const char TextMerkmalStr [] = "'";		// Beginn und Ende-Zeichen eines Textwertes
const char DateMerkmalStr [] = "#";		// Beginn und Ende-Zeichen eines Datumwertes
const char MerkmalBeginStr [] = "{";	// Beginn und Ende-Zeichen eines
const char MerkmalEndStr [] = "}";		// Merkmals

#import "tlb/TRiASHelper.tlb"	raw_interfaces_only raw_dispinterfaces no_namespace named_guids 
#import "tlb/TRiASDB.tlb"		raw_interfaces_only raw_dispinterfaces no_namespace	named_guids \
	exclude("IPersistStreamInit", "IPersist", "IStream", "ISequentialStream") \
	exclude("_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME") \
	exclude("IObjectWithSite")

#endif // _PHEADER_H



