// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:43:38 
//
// @doc
// @module TRiASNativeDBConfig.h | Konfigurationskonstanten für TRiASNativeDB

#if !defined(_TRIASNATIVEDBCONFIG_H__CDDD75C1_A54B_48CF_8E4E_458A0E41DF0F__INCLUDED_)
#define _TRIASNATIVEDBCONFIG_H__CDDD75C1_A54B_48CF_8E4E_458A0E41DF0F__INCLUDED_

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
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

#define _ATL_FREE_THREADED			// apartment model ist Both

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
//#define _ATL_DEBUG_QI

// spezielle DumpLib (d_lib) zuschalten
#define USE_DLIB
#endif // _DEBUG

#endif // !defined(_TRIASNATIVEDBCONFIG_H__CDDD75C1_A54B_48CF_8E4E_458A0E41DF0F__INCLUDED_)
