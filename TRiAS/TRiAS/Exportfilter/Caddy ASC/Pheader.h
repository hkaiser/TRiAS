//	Vorübersetzter Haeder für das Projekt ACADXF

#include <windows.h>

#ifdef WIN32
	#define __export
	#define _pascal 
#else
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

#include <expfltm.hxx>		// EXPORTFLT

#ifndef _TRIAS02_ENTRY
#define _TRIAS02_ENTRY
#endif

#ifndef EXPORT02
#define EXPORT02
#endif

#include <bool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tstring>

#include <containr.hxx>
#include <commonvu.hxx>
#include <errcodes.hxx>         // FehlerCodes

#include <xtension.h>	
#include <ixtensn.hxx>
#include <xtensnx.h>
#include <xtencunk.hxx>			// CTriasExtension			  

#include <protos.h>				// DELETE ()


