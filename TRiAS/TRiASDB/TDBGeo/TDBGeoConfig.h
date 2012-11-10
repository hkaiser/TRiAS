// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.09.99 11:57:09
//
// @doc
// @module TDBGeoConfig.h | Declaration of the <c CTDBGeoConfig> class

#if !defined(_TDBGEOCONFIG_H__9084122D_07D7_4772_A2F7_272F34CC1308__INCLUDED_)
#define _TDBGEOCONFIG_H__9084122D_07D7_4772_A2F7_272F34CC1308__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#define	__ATL_USED__
#define	__OSPACESTL_USED__

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

// spezielle DumpLib (d_lib) zuschalten
#define USE_DLIB

// eigenes marshalling verwenden
//#define _MERGE_PROXYSTUB

#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die Standard-Speicherverwaltung
// verwendet werden soll
#define _USE_ONESIZEHEAP

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die keine ClassFactories im cache 
// gehalten werden sollen (s. CLASSFACTORY_CACHE_BEGIN etc.)
#define _USE_CLASSFACTORY_CACHE

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn keine Performance-Counter
// implementiert werdensollen
#if defined(_DEBUG)
//#define _USE_PERFMON_COUNTERS
//#define _USE_DYNAMIC_PERFMON_COUNTERS
#endif // defined(_DEBUG)

// das Eine geht nicht ohne das Andere
#if defined(_USE_DYNAMIC_PERFMON_COUNTERS) && !defined(_USE_PERFMON_COUNTERS)
#define _USE_PERFMON_COUNTERS
#endif // defined(_USE_DYNAMIC_PERFMON_COUNTERS)

///////////////////////////////////////////////////////////////////////////////
// OGC Objekte erzeugen
//#define _INCLUDE_OGC_OBJECTS

#endif // !defined(_TDBGEOCONFIG_H__9084122D_07D7_4772_A2F7_272F34CC1308__INCLUDED_)
