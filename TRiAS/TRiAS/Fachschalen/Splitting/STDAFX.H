// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E2054A2A_4327_11D2_9EBE_006008447800__INCLUDED_)
#define AFX_STDAFX_H__E2054A2A_4327_11D2_9EBE_006008447800__INCLUDED_


#include "crtdbg.h" // _ASSERTE


#if _MSC_VER > 1000
#pragma once
#endif

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

#include <protos.h>


#if defined(__ATL_20_USED__)
	using namespace ::ospace::std;
	using namespace ::ospace::std::rel_ops;
	#include <atl20.h>
	#include <ospace/com/smartif.h>
#else
	#include <atl11.h>
	#include <smartif.h>
#endif // __ATL__


extern CComModule _Module;

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
//#include <xtencunk.hxx>
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include <registrx.hxx>

#include <xtensnxx.h>
#include <xtensnn.h>
#include <ristypes.hxx>


#include <xtsnprop.hxx>


#include <errcodes.hxx>         // FehlerCodes

#include <eieruhr.hxx>


#include <errinstx.hxx>



#include <eb.h>
#include <ibscript.hxx>

//#include "BerlinExt.h"		// die Erweiterung selbst

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E2054A2A_4327_11D2_9EBE_006008447800__INCLUDED)
