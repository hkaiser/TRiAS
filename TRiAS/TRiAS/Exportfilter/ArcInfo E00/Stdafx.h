// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define _TRIAS_DBG_HEADER_DIAGNOSTICS
//#define	_TRIAS_DBG_DEFINES

#include <Pragmas.h>

#define	__ATL_USED__
#include <TRiASConfig.h>
#include "../ExportConfig.h"

#if defined(_DEBUG)
#define	_ASSERT_ON_THROW_FAILED_HRESULT	// THROW_FAILED_HRESULT liefert Assertion
#define _ATLX_ASSERT_ON_FAILURE
// evtl. ausführliches AddRef/Release Tracking zuschalten
//#define _ATLX_DEBUG_REFCOUNT_WALKSTACK
//#define _USE_IMAGE_HELP					// dabei MSSymbols verwenden

// evtl. Objekte global zählen
#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT

// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// speziell für Extension, Commonview etc.
#define	__CV__
#define	DLL
#define	__XT
#define	__DEXPROCS		// keine Messages, sondern direkte Funktionsaufrufe
//#define	__EXPFLTDLL__

///////////////////////////////////////////////////////////////////////////////
// STL-related stuff 
#define __STL_OSPACE5__
#include <stl.h>

///////////////////////////////////////////////////////////////////////////////
// ATL-related stuff 

//#define	_ATL_DEBUG_QI

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

#include <ospace/com/smartif.h>
#include <com/DefSmartIf.h>

#include <ospace/com/ComErrorMacros.h>
#include <com/Errormacros2.h>
#include <com/VariantHelpers.h>
#include <com/BSTRHelpers.h>
#include <com/GUIDHelpers.h>
#include <com/StreamHelpers.h>

#ifdef WIN32
#include <expfltm.hxx>
#define EXPORT02
#define _TRIAS02_ENTRY
#else
#error "You must compile with WIN32 defined!!"
#endif // WIN32

#include <bool.h>
#include <stdio.h>
#include <stdlib.h>
#include <tstring>

#include <containr.hxx>
#include <commonvu.hxx>
#include <errcodes.hxx>         // FehlerCodes

#include <xtension.h>	
#include <xtensnx.h>
#include <protos.h>				// DELETE ()
