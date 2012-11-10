// Precompiled Header für ASCIMP.EXT -----------------------------------------
// File: ASCIMPP.H

#if !defined(_ASCIMPP_H)
#define _ASCIMPP_H

#if _MSC_VER >= 1100
#include "AscImpConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>

#if !defined(WIN32)
#include <ole16.h>
#endif // WIN32

#include <tstring>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////
// richtige ATL Version verwenden

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define __ATL_11_USED__ or __ATL_20_USED__!"
#endif
extern CComModule _Module;
extern _ATL_OBJMAP_ENTRY *GetObjectMap (void);

#include <ospace/com/iterenum.h>
#include <ospace/std/map>

#include <commonvu.hxx>
#include <errcodes.hxx>		// FehlerCodes

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <XtsnImpAtl.h>		// ImportInterface

#include <containr.hxx>

#include "ascimp.hpp"		// die Erweiterung selbst

#include "ascpars.h"
#include "ascerrs.h"
#include "input.h"

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(x){delete(x);(x)=NULL;}
#endif // DELETE_OBJ

#endif // _ASCIMPP_H
