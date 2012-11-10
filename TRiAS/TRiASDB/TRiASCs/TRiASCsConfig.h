// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:52:50 
//
// @doc
// @module TRiASCsConfig.h | Konfigurationskonstanten für TRiASCs

#if !defined(_TRIASCSCONFIG_H__8591C6B1_0D68_4F7E_923C_65D600F584B9__INCLUDED_)
#define _TRIASCSCONFIG_H__8591C6B1_0D68_4F7E_923C_65D600F584B9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define __ATL_USED__				// ATL in diesem Projekt verwenden
//#define __OSPACESTL_USED__		// OspaceSTL in diesem Projekt verwenden
#define __STL_OSPACE5__

///////////////////////////////////////////////////////////////////////////////
// zusätzliche _DEBUG-Optionen
#if defined(_DEBUG)
#define	_ASSERT_ON_THROW_FAILED_HRESULT	// THROW_FAILED_HRESULT liefert Assertion
#define _ATLX_ASSERT_ON_FAILURE

// evtl. ausführliches AddRef/Release Tracking zuschalten
//#define _ATLX_DEBUG_REFCOUNT_WALKSTACK
//#define _USE_IMAGE_HELP					// dabei MSSymbols verwenden

// evtl. Objekte global zählen
//#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT

// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI

// spezielle DumpLib zuschalten
//#define USE_DLIB

// Tracing
//#define _TRIAS_CS

// Pad arrays
//#define _FILL_WITH_PADCHAR
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// ...wenn mit GM-Koordinatensystemen gearbeitet werden soll (s. TRiASCoordSystem.cpp)
//#define _USE_GM_CS

///////////////////////////////////////////////////////////////////////////////
// OGC kompatible interfaces implementieren
//#define _USE_OGC_COMPATIBILITY

#endif // !defined(_TRIASCSCONFIG_H__8591C6B1_0D68_4F7E_923C_65D600F584B9__INCLUDED_)
