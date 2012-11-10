// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.09.99 11:05:56 
//
// @doc
// @module TRiAS01Config.h | Konfigurationskonstanten für TRiAS01

#if !defined(_TRIAS01CONFIG_H__0BBECE69_D5DB_4DAE_80B0_C5ADDA10D44D__INCLUDED_)
#define _TRIAS01CONFIG_H__0BBECE69_D5DB_4DAE_80B0_C5ADDA10D44D__INCLUDED_

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

#if _MSC_VER < 1300
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define OS_NO_MIN_MAX
#endif // _MSC_VER < 1300

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
#define USE_DLIB

// track memory leaks
#define _CRTDBG_MAP_ALLOC

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

///////////////////////////////////////////////////////////////////////////////
// die folgende Definition reinnehmen, wenn ErrorTree als Tree und nicht als 
// HashTable implementiert werden soll
//#define _IMPLEMENT_ERRTREE_AS_TREE

///////////////////////////////////////////////////////////////////////////////
// die folgende Definition rausnehmen, wenn komprimierte Streams in den
// Datenbanken nicht unterstützt werden sollen
#define _USE_COMPRESSED_STREAM

///////////////////////////////////////////////////////////////////////////////
// die folgende Definition rausnehmen, wenn Connectfilter nicht unterstützt 
// werden sollen
#define _USE_CONNECTFILTER

///////////////////////////////////////////////////////////////////////////////
// define for threadsafe access to the geodb routines
//#define _USE_THREAD_WRAPPER_FOR_DBACCESS 

///////////////////////////////////////////////////////////////////////////////
// experimental: RefCnt für z_open/z_close
#if defined(_DEBUG)
//#define _USE_OPENREFCNT
#endif // defined(_DEBUG)

#endif // !defined(_TRIAS01CONFIG_H__0BBECE69_D5DB_4DAE_80B0_C5ADDA10D44D__INCLUDED_)
