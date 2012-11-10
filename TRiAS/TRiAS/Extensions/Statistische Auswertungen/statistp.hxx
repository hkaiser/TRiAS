// Precompiled Header ----------------------------------------------------------
// File: STATISP.HXX

#if !defined(_STATISTP_HXX)
#define _STATISTP_HXX

#if _MSC_VER >= 1100
#include "GeoStatConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include "resource.h"
#include <commdlg.h>
#include <stdlib.h>	// für atol

#include <tstring>	// für strcpy
#include <stdio.h>	// für sprintf
#include <math.h>
#include <limits.h>

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
	#include <registrx.hxx>
#else
	#include <dlgs.h> 
	#include <tchar.h>
	#include <compobj.h>
#endif // WIN32
#include <protos.h>

#include <commonvu.hxx>		// CommonVu - eigene Klassendeklarationen
#include <containr.hxx>		// CommonVu - eigene Klassendeklarationen

#include <ristypes.hxx>

#if _MSC_VER >= 1100
#include <CtfxMfc.h>
#else
#include <ctfx.hxx>
#endif // _MSC_VER >= 1100

#include <dllbindx.hxx>
#include <objcontx.hxx>
#include <dblpair.hxx>

#include <errcodes.hxx>		// FehlerCodes

#include <numeditx.hxx>
#include <mmsystem.h>		// TIMER

#include <dblnumex.hxx>
#include <eieruhr.hxx>
#include <helptxtx.hxx>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#include <xtensnxx.h>


#include <ixtensn.hxx>
#include <xtencunk.hxx>
#include <xtsnprop.hxx>
#include <errinstx.hxx>

#if _MSC_VER < 1100
#include <smartif.h>
#endif // _MSC_VER < 1100

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x)	if(NULL==x){}else{delete(x);(x)=NULL;}
#endif // !defined(DELETE_OBJ)

#if !defined(DELETE_VEC)
#define DELETE_VEC(x)	if(NULL==x){}else{delete[](x);(x)=NULL;}
#endif // !defined(DELETE_VEC)

#endif // _STATISTP_HXX
