// Precompiled Header für ARCTRIAS.EXT -----------------------------------------
// File: pheader.h

#if !defined(_PHEADER_H)
#define _PHEADER_H

#if _MSC_VER >= 1100
#include "ArcTRiASConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>

enum DGeoTyp { DGT_Punkt = 1, DGT_Linie, DGT_Flaeche, DGT_Text, DGT_Symbol,
	       	   DGT_Unknown, DGT_OtherTable };

//  Konvertierungs-Message ausgeben
void OutKonvMess (DGeoTyp Typ);

#ifdef WIN32
	#define __export
//    #define HUGE		// #HK960812
	#define __HUGE
#else
	#define LPCTSTR LPCSTR
	#define LPTSTR  LPSTR
	#define TEXT    _T
	#include "xtensnm.hxx"	// _XTENSN_ENTRY, ... für 16-Bit-Variante
	#include <tchar.h>		// LPCTSTR in xtencunk.hxx für 16-Bit-Variante
	#include <ole2.h>		// ITriasXtension, ... in ixtensn.hxx für 16-Bit-Variante
	// #include <ole16.h>
	#include <shellapi.h>	// HKEY in xtsnaux.hxx für 16-Bit-Variante
	#include <print.h>
	#define LPCWSTR LPCSTR
	#define LPWSTR LPSTR
	#define LPOLESTR LPSTR
    #define __HUGE __huge
    
    //	umsetzen der Funktion    
	DWORD timeGetTime (void);
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

#endif // _PHEADER_H



