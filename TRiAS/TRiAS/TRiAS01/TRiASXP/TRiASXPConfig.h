// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 13.08.2001 21:26:11 
//
// @doc
// @module TRiASXPConfig.h | Declaration of the <c CTRiASXPConfig> class

#if !defined(_TRIASXPCONFIG_H__E35D523D_0760_4191_8725_213FD0D3AEBE__INCLUDED_)
#define _TRIASXPCONFIG_H__E35D523D_0760_4191_8725_213FD0D3AEBE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
//#define __OSPACESTL_USED__		// OspaceSTL in diesem Projekt verwenden

#define _ATL_APARTMENT_THREADED		// apartment model ist Apartment

///////////////////////////////////////////////////////////////////////////////
// zusätzliche _DEBUG-Optionen
#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE

// evtl. ausführliches AddRef/Release Tracking zuschalten
//#define _ATLX_DEBUG_REFCOUNT_WALKSTACK
//#define _USE_IMAGE_HELP					// dabei MSSymbols verwenden

// evtl. Objekte global zählen
#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT
#define _DUMP_PENDING_OBJECTS

// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
#define _ATL_DEBUG_QI
#define ATL_TRACE_LEVEL 4			// -1: no tracing, 4: max tracing
#define ATL_TRACE_CATEGORY 0xFFFFFFFF

// spezielle DumpLib (d_lib) zuschalten
#if _MSC_VER < 1300
#define USE_DLIB
#define _OVERLOAD_ATLTRACE
#endif // _MSC_VER < 1300
#endif // _DEBUG

#endif // !defined(_TRIASXPCONFIG_H__E35D523D_0760_4191_8725_213FD0D3AEBE__INCLUDED_)
