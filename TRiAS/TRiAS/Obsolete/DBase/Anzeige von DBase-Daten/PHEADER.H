// FILE: PHEADER.H
// vorübersetzter Header für DBASEX32.EXT

#ifndef _PHEADER_H
#define _PHEADER_H

#include <dbasedlm.h>
// #include <dbtoolsm.h>

#include <d4all.h>			// CodeBase-Klassen
#include <crcb.hxx>		 	// Erzeugen/Löschen eines CodeBase-Objektes

#ifdef WIN32
   	#define __export
#include <bool.h>
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
#endif

#include <tstring>
#include <stdio.h>
#include <stdlib.h>
#include <protos.h>  
#include <errcodes.hxx>      // FehlerCodes
 
#include <commonvu.hxx>

#include <xtension.h>	
#include <ixtensn.hxx>
#include <xtensnx.h>
#include <xtencunk.hxx>			// CTriasExtension			  

#endif 		// _PHEADER_H
