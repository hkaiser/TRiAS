// Precompiled Header für BILDER.EXT -----------------------------------------
// File: BILDERP.HXX

#if !defined(_BILDERP_HXX)
#define _BILDERP_HXX

#if _MSC_VER >= 1100
#include "BilderConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include <tstring>	// für strcpy
#include <stdlib.h>	// für ltoa

#include <resstrg.h>

#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#include <ospace/com/smartif.h>
#include <commonvu.hxx>
#include <drawobj.hxx>

#include <errcodes.hxx>

#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>            // Konstanten und Datenstrukturen

#include <ixtensn.hxx>          // Interfaces einer Erweiterung
#include <xtencunk.hxx>         // InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>

#include <containr.hxx>

#include "bildobj.hxx"
#include "minmaxwd.hxx"
#include "bildwind.hxx"

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(!(x)){}else{delete(x);x=NULL;}
#define DELETE_VEC(x)	if(!(x)){}else{delete[](x);x=NULL;}
#endif // DELETE_OBJ

#endif // _BILDERP_HXX
