// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 10/22/1998 09:11:34 AM
//
// @doc
// @module TRiASDBConfig.h | Konfigurationskonstanten für TRiASDB

#if !defined(_TRIASDBCONFIG_H__21005238_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _TRIASDBCONFIG_H__21005238_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define _USE_PROPERTYSTORAGE		// PropertyStorages für Collections verwenden
#define _MERGE_PROXYSTUB
// #define _USE_TRIAS_MESSAGES
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

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

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn 'einfache' Fehlerbehandlung gebraucht wird
//#define _USE_NEW_ERRORHANDLING

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die Standard-Speicherverwaltung verwendet 
// werden soll
#define _USE_ONESIZEHEAP

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn keine InMemoryStream-Objekte für das
// Speichern von Blobs verwendet werden sollen
#define _USE_INMEMORYSTREAMS_FOR_BLOBS

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die WildcardMoniker für die Connections
// nicht in der ROT registriert werden sollen
//#define _REGISTER_WILDCARD_MONIKERS

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die ConnectionMoniker nicht mit dem 
// voreingestellten MonikerTrenner ('!') ausgegeben werden sollen
#define _USE_CONNECTION_MK_WITHDELIMITER

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die gespeicherte Streams nicht optional
// komprimiert werden sollen/können
#define _USE_STREAMCOMPRESSION

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn an Stelle der MultiDispatch-Basisklasse
// IDispatchImplEx die normale Basisklasse IDispatchImpl verwendet werden soll
//#define _USE_DISPATCHIMPLEX

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn an Stelle der dynamisch erzeugten 
// OBJECT_MAP die herkömmliche statische verwendet werden soll 
#define _USE_RUNTIME_OBJECTMAP

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
// Die folgende Definition rausnehmen, wenn die keine ClassFactories im cache 
// gehalten werden sollen (s. CLASSFACTORY_CACHE_BEGIN etc.)
#define _USE_CLASSFACTORY_CACHE

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn für die Implementation der
// Klasse <c CTRiASObjectHandleMapBase> keine Hashmaps sondern normale Maps 
// verwendet werden sollen
#define _USE_HASHMAP_FOR_OBJECTNAMEMAP

#endif // !defined(_TRIASDBCONFIG_H__21005238_6792_11D2_9EDE_006008447800__INCLUDED_)
