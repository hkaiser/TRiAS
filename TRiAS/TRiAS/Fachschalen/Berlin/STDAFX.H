// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E2054A2A_4327_11D2_9EBE_006008447800__INCLUDED_)
#define AFX_STDAFX_H__E2054A2A_4327_11D2_9EBE_006008447800__INCLUDED_



#if _MSC_VER >= 1100
#include "BerlinConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>


#include <bool.h>
#include <tstring>
#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>			// Konstanten und Datenstrukturen

#include <commonvu.hxx>         // CommonVu - eigene Klassendeklarationen

#include <winver.h>	// Definitionen
#include <windef.h>	// Definitionen

#include <commctrl.h>	// Definitionen
#include <stddlg.hxx>

#include <io.h>
#include <fcntl.h>

#include <stdio.h>	// für sprintf
#include <stdlib.h>	// für atol


#if defined (WIN32)
	#if defined(__ATL_20_USED__)
	using namespace ::ospace::std;
	using namespace ::ospace::std::rel_ops;
	#include <atl20.h>
	#include <ospace/com/smartif.h>
	#else
	#include <atl11.h>
	#endif // __ATL__

	extern CComModule _Module;			// Main module for ATL

#endif // WIN32

#include <registrx.hxx>

//#include <smartif.h>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
//#include <xtencunk.hxx>
#include <xtsnguid.h>
#include <xtsnaux.hxx>

//#include <protos.h>


#include <xtensnxx.h>
#include <xtensnn.h>
#include <ristypes.hxx>


#include <xtsnprop.hxx>


#include <errcodes.hxx>         // FehlerCodes

#include <eieruhr.hxx>


#include <errinstx.hxx>



#include <eb.h>
#include <ibscript.hxx>



#if _MSC_VER < 1100
#include <smartif.h>
#endif // _MSC_VER < 1100

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)



//#include "BerlinExt.h"		// die Erweiterung selbst

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E2054A2A_4327_11D2_9EBE_006008447800__INCLUDED)
