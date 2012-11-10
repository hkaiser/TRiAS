// Precompiled Header für DXFIMP.EXT -----------------------------------------
// File: pheader.hpp

#if !defined(_PHEADER_HPP)
#define _PHEADER_HPP

#if _MSC_VER >= 1100
#include "DxfImpConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>

#ifndef  _TRIAS02_ENTRY
#define  _TRIAS02_ENTRY
#endif

#ifdef WIN32
	#define __export
#else             
	#define LPCTSTR LPCSTR
	#define LPTSTR  LPSTR
	#define TEXT    _T
	#include "xtensnm.hxx"	// _XTENSN_ENTRY, ... für 16-Bit-Variante
	#include <tchar.h>		// LPCTSTR in xtencunk.hxx für 16-Bit-Variante
	#include <ole2.h>		// ITriasXtension, ... in ixtensn.hxx für 16-Bit-Variante
	#include <ole16.h>
	#include <shellapi.h>	// HKEY in xtsnaux.hxx für 16-Bit-Variante
	#include <print.h>
	#define LPCWSTR LPCSTR
	#define LPWSTR LPSTR
	#define LPOLESTR LPSTR
#endif // WIN32

#include <bool.h>
#include <tstring>
#include <stdio.h>
#include <stdlib.h>

#include <containr.hxx>
#include <commonvu.hxx>
#include <hpp/errcodesodbc.hxx>         // FehlerCodes

#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>			// Konstanten und Datenstrukturen

#include <ixtensn.hxx>			// Interfaces einer Erweiterung
#include <xtencunk.hxx>			// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <xtsnimp.hxx>			// ImportInterface
#include <hpp/protos.h>				// DELETE ()

#include "dxfimpif.hpp"         // ImportInterface
#include "dxfimp.hpp"           // die Erweiterung selbst
#include "dxfimp.hr"            // Resource-Konstanten
#include "optparam.hpp"			// optionale Parameter

#endif // _DXFIMPP_HPP



