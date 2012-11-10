//Precompiled Header ----------------------------------------------------------
// File: TPROJP.HXX

#if !defined(_TPROJP_HXX)
#define _TPROJP_HXX

// KK010115
#define	__STL_OSPACE5__
#include "stl.h"


#if _MSC_VER >= 1100

#include "ProjectConfig.h"
#include <TRiASConfig.h>
#endif // _MSC_VER >= 1100

#include <bool.h>
#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include <commdlg.h>
#include <stdlib.h>	// für atol
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#if !defined(WIN32)
#include <dlgs.h> 
#include <tchar.h>
#endif // WIN32

// KK010115
#include <ospace/std/string>	// standard string class
typedef os_string string;
#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/list>



#include <tstring>
#include <string.h>	// für strcpy
#include <stdio.h>	// für sprintf
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
#endif

#if defined (WIN32)
	#include <winver.h>	// Definitionen
	#include <windef.h>	// Definitionen
#else
	#include <compobj.h>
#endif

#include <protos.h>

#include <commonvu.hxx>		// CommonVu - eigene Klassendeklarationen
#include <containr.hxx>		// CommonVu - eigene Klassendeklarationen
#include <stddlg.hxx>
#include <ristypes.hxx>
#include <dllbindx.hxx>
#include <objcontx.hxx>

#include <dblpair.hxx>
#include <ctfx.hxx>
#include <errcodes.hxx>		// FehlerCodes

#include <numeditx.hxx>
#include <mmsystem.h>		// TIMER

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
#include <xtsnprop.hxx>

#include <errinstx.hxx>


#endif // _TPROJP_HXX
