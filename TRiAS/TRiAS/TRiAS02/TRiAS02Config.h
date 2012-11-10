// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.10.1999 10:05:44 
//
// @doc
// @module TRiAS02Config.h | Konfigurationskonstanten für TRiAS02

#if !defined(_TRIAS02CONFIG_H__604E8E64_7B76_40F1_BFD5_0751FA3AAF49__INCLUDED_)
#define _TRIAS02CONFIG_H__604E8E64_7B76_40F1_BFD5_0751FA3AAF49__INCLUDED_

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
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

/////////////////////////////////////////////////////////////////////////////
// sonstige Konfigurationsskonstanten
//#define _USE_LEGACY_CODE
#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED

#define _USE_NEWVISINFO

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die keine ClassFactories im cache 
// gehalten werden sollen (s. CLASSFACTORY_CACHE_BEGIN etc.)
#define _USE_CLASSFACTORY_CACHE

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn für den Objekt-Doppelbaum COptTree
// bzw. CDelTree verwendet werden sollen (ansonsten map/multimap)
#define _USE_MAP_FOR_OBJEKTLISTE

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

// spezielle DumpLib zuschalten
//#define USE_DLIB

// track memory leaks
#define _CRTDBG_MAP_ALLOC

// optimize CTF.hxx
#define _CTF_USE_POINTMEMBER

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn keine Performance-Counter 
// implementiert werdensollen
//#define _USE_PERFMON_COUNTERS
//#define _USE_DYNAMIC_PERFMON_COUNTERS
#endif // defined(_DEBUG)

// das Eine geht nicht ohne das Andere
#if defined(_USE_DYNAMIC_PERFMON_COUNTERS) && !defined(_USE_PERFMON_COUNTERS)
#define _USE_PERFMON_COUNTERS
#endif // defined(_USE_DYNAMIC_PERFMON_COUNTERS)

#endif // !defined(_TRIAS02CONFIG_H__604E8E64_7B76_40F1_BFD5_0751FA3AAF49__INCLUDED_)
