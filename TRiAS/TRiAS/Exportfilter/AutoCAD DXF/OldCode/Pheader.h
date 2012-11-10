//	Vorübersetzter Haeder für das Projekt ACADXF

#include <windows.h>

#ifdef WIN32
// #HK960813: Wenn mich was stört, dann blende ich es eben mal schnell aus ...
//	#define __export
//	#define _pascal 
#include <expfltm.hxx>
#define EXPORT02
#define _TRIAS02_ENTRY
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


