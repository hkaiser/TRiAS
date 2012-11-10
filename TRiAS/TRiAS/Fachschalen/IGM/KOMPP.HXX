//Precompiled Header ----------------------------------------------------------
// File: KOMPP.HXX

#if !defined(_KOMPP_HXX)

#define _KOMPP_HXX


#if _MSC_VER >= 1100

#include "KompaktConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100


#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include "kompaktr.h"

#include <bool.h>
#include <tstring>

#include <io.h>
#include <fcntl.h>
//#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>	// für sprintf
//#include <string.h>	// für strcpy
#include <stdlib.h>	// für atol
#include <commdlg.h>
#include <direct.h>

#include <ctype.h>	// islower
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


//#include <iterenum.h>
#include <winver.h>	// Definitionen
#include <windef.h>	// Definitionen
#include <commctrl.h>	// Definitionen

#include <protos.h>

#include <commonvu.hxx>		// CommonVu - eigene Klassendeklarationen
#include <containr.hxx>		// CommonVu - eigene Klassendeklarationen
#include <stddlg.hxx>
#include <ristypes.hxx>


#include <dllbindx.hxx>
#include <objcontx.hxx>

#if _MSC_VER >= 1100
#include <CtfxMfc.h>
#else
#include <ctfx.hxx>
#endif // _MSC_VER >= 1100



//#include <dllbindx.hxx>
//#include <objcontx.hxx>


#include <dblpair.hxx>
//#include <ctfx.hxx>
#include <errcodes.hxx>		// FehlerCodes

#include <numeditx.hxx>
//#include <mmsystem.h>		// TIMER

#include <dblnumex.hxx>
#include <eieruhr.hxx>
#include <helptxtx.hxx>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
				// Konstanten und Datenstrukturen
#include <xtensnx.h>
#include <xtensnxx.h>

#include <xtensnn.h>


#include <ixtensn.hxx>
#include <xtencunk.hxx>
//#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
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

#if _MSC_VER >= 1100
	#include <visinfo.h>
#endif
//#include <smartif.h>

#endif // _KOMPP_HXX
