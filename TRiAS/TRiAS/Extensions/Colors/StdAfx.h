// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#include "ColorsConfig.h"
#include <TRiASConfig.h>

///////////////////////////////////////////////////////////////////////////////
// jetzt alles andere
#include <bool.h>
#include <afxwin.h>
#include <afxdisp.h>

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/vector>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 
#if defined(__ATL_20_USED__)
using namespace ::ospace::std;
using namespace ::ospace::std::rel_ops;
#include <atl20.h>
#elif defined(__ATL_11_USED__)
#include <atl11.h>
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <ospace/com/smartif.h>


