// Precompiled Header für BNAIMP.EXT -----------------------------------------
// File: BNAIMPP.H

#if !defined(_BNAIMPP_H)
#define _BNAIMPP_H

#if _MSC_VER >= 1100
#include "BnaImpConfig.h"
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
#include <ShlObj.h>

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
#include <ospace/std/set>
#include <ospace/std/map>
#include <ospace/std/vector>

#include <commonvu.hxx>
#include <errcodes.hxx>		// FehlerCodes

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <Ixtnext.hxx>
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <XtsnImpAtl.h>		// ImportInterface

#include <containr.hxx>

#include "resource.h"
#include "bnaimp.hpp"		// die Erweiterung selbst

#include "bnaerrs.h"
#include "input.h"

#if !defined(_INPLACE_COMBO_STRINGLIST_DEFINED)
typedef set<os_string> CStringList;
#define _INPLACE_COMBO_STRINGLIST_DEFINED
#endif // !defined(_INPLACE_COMBO_STRINGLIST_DEFINED)

#define _TRIAS03_ENTRY
#include <InPlaceCombo.h>

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) if(x){delete(x);(x)=NULL;}
#endif // DELETE_OBJ

#endif // _BNAIMPP_H
