//Precompiled Header ----------------------------------------------------------
// File: ATTRIBP.HXX

#if !defined(_ATTRIBP_HXX)
#define _ATTRIBP_HXX

#include <windows.h>	// Window-Konstanten und Datenstrukturen
#include "resource.h"
#include <commdlg.h>
#include <stdlib.h>	// für atol

#if !defined(WIN32)
#include <dlgs.h> 
#include <tchar.h>
#endif // WIN32


#include <tstring>
#include <string.h>	// für strcpy
#include <stdio.h>	// für sprintf
#include <ctype.h>	// islower
#include <math.h>
#include <limits.h>


#if defined (WIN32)
	#include <atl11.h>
	extern CComModule _Module;			// Main module for ATL
	#include <registrx.hxx>
#else
	#include <compobj.h>
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

#include <smartif.h>
#endif // _TPROJP_HXX
