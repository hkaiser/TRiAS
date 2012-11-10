///////////////////////////////////////////////////////////////////////
// Standard

#include <iostream.h>

#define	__ATL_USED__
#include <TRiASConfig.h>
#include "Basetsd.h"		// 64-bit Definitionen

///////////////////////////////////////////////////////////////////////
// STL

#define	__STL_OSPACE5__
#include "stl.h"

///////////////////////////////////////////////////////////////////////
// Windows

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)
//#include <afxole.h>         // MFC OLE classes
//#include <afxdb.h>			// MFC DB extensions
#include <afxcmn.h>			// Win32 Common Controls
//#include <afxdisp.h>		// COleVariant
#include <afxpriv.h>

#include <atlbase.h>

///////////////////////////////////////////////////////////////////////
// aus mfc/src/stdafx.h 'geborgt'

#ifndef _AFX_OLD_EXCEPTIONS

// MFC does not rely on auto-delete semantics of the TRY..CATCH macros,
//  therefore those macros are mapped to something closer to the native
//  C++ exception handling mechanism when building MFC itself.

#undef TRY
#define TRY { try {

#undef CATCH
#define CATCH(class, e) } catch (class* e) \
	{ ASSERT(e->IsKindOf(RUNTIME_CLASS(class))); UNUSED(e);

#undef AND_CATCH
#define AND_CATCH(class, e) } catch (class* e) \
	{ ASSERT(e->IsKindOf(RUNTIME_CLASS(class))); UNUSED(e);

#undef CATCH_ALL
#define CATCH_ALL(e) } catch (CException* e) \
	{ { ASSERT(e->IsKindOf(RUNTIME_CLASS(CException))); UNUSED(e);

#undef AND_CATCH_ALL
#define AND_CATCH_ALL(e) } catch (CException* e) \
	{ { ASSERT(e->IsKindOf(RUNTIME_CLASS(CException))); UNUSED(e);

#undef END_TRY
#define END_TRY } catch (CException* e) \
	{ ASSERT(e->IsKindOf(RUNTIME_CLASS(CException))); e->Delete(); } }

#undef THROW_LAST
#define THROW_LAST() throw

// Because of the above definitions of TRY...CATCH it is necessary to
//  explicitly delete exception objects at the catch site.

#define DELETE_EXCEPTION(e) do { e->Delete(); } while (0)
#define NO_CPP_EXCEPTION(expr)

#else   //!_AFX_OLD_EXCEPTIONS

// In this case, the TRY..CATCH macros provide auto-delete semantics, so
//  it is not necessary to explicitly delete exception objects at the catch site.

#define DELETE_EXCEPTION(e)
#define NO_CPP_EXCEPTION(expr) expr

#endif  //_AFX_OLD_EXCEPTIONS

/////////////////////////////////////////////////////////////////////////////

#ifdef _AFXDLL		// For the MFCDLL build, non-header data is always in _DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA     __based(__segname("_DATA"))
#endif
