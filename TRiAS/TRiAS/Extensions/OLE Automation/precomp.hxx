// PreCompiledHeaders ---------------------------------------------------------
// File: PRECOMP.HXX

#if !defined(_PRECOMP_HXX)
#define _PRECOMP_HXX

#include "OleAutoConfig.h"
#include <TRiASConfig.h>

#include <afxctl.h>		// OCX-Definitionen
#include <afxext.h>		// MFC extensions (including VB)
#include <afxcoll.h>	// Arrays und Listen
#include <afxdisp.h>
#include <afxcmn.h>

#if !defined(WIN32)
#include <toolhelp.h>
#include <dispatch.h>
#endif

#include <new>
#include <tstring>
#include <fnamestr.h>
#include <stdarg.h>
#include <stdlib.h>
#include "olestr.h"

#include <d_lib/d_lib.h>			// DumpLib support
#include <d_lib/DumpHelperScope.h>	// DumpLib Scope objects

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/set>
#include <ospace/std/list>
#include <ospace/std/map>

#if defined(__ATL_20_USED__)
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
extern CComModule _Module;
#include <ospace/com/smartif.h>

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#if defined(_USE_CLASSIC_CONTAINERS)
#include <containr.hxx>
#include <copttree.hxx>
#else
#include <ContainerWrapper.h>
#endif // defined(_USE_CLASSIC_CONTAINERS)

#include <errcodes.hxx>		// FehlerCodes

#include <ixtensn.hxx>
#include <xtencatl.hxx>
#include <XtsnPropAtl.h>
#include <xtsnguid.h>
#include <xtsnaux.hxx>
#include <errinstx.hxx>

#include <eb.h>

#include <tracemacros.h>

#include <ibscript.hxx>
#include <igeometr.hxx>
#include <igentext.h>

#if _MSC_VER <= 1020
#define DECLSPEC_UUID(x)
#endif

#include <triastlb.h>
#include <visinfo.h>

#include "Defines.h"		// allgemeine Konstanten

#include "ole2auto.hxx"		// Klasse für diese Erweiterung

#include "doctree.hxx"
#include "appcf.hxx"		// Klassen für Trias.Application
#include "app.hxx"

#include "viewtree.hxx"
#include "clstrees.hxx"
#include "objtrees.hxx"
#include "owintree.hxx"

#include "doc.hxx"		

#include "ftvwtree.hxx"
#include "ftcltree.hxx"
#include "ftobtree.hxx"

#if defined(WIN32)
#define __huge
#endif

#if !defined(_DELETE_OBJ)
#define DELETE_OBJ(x) if(!x){}else{delete(x); x=NULL;}
#endif // _DELETE_OBJ

#endif // _PRECOMP_HXX
