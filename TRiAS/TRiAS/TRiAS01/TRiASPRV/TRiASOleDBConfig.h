// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.05.2001 14:55:46 
//
// @doc
// @module TRiASOleDBConfig.h | Konfigurationskonstanten für TRiASOleDB Provider

#if !defined(_TRIASOLEDBCONFIG_H__0B7FA77B_C771_4F94_821D_4220369F4B5E__INCLUDED_)
#define _TRIASOLEDBCONFIG_H__0B7FA77B_C771_4F94_821D_4220369F4B5E__INCLUDED_

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

#if defined(__ICL)
#define OS_USE_ALTERNATE_STD		// alternative STL verwenden
#endif // defined(__ICL)

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
#define ATL_TRACE_LEVEL		-1			// -1: no tracing, 4: max tracing
#define ATL_TRACE_CATEGORY	0xFFFFFFFF

// spezielle DumpLib (d_lib) zuschalten
#if _MSC_VER < 1300
#define USE_DLIB
#define _OVERLOAD_ATLTRACE
#endif // _MSC_VER < 1300
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// nachfolgende Konstante definieren, wenn eine gemeinsame Tabelle mit 4 Geometrietypen
// für jede Objektklasse erzeugt werden soll (TRiAS OleDB:GeometryAs=1)
//#define _USE_PROP_GEOMETRYAS

///////////////////////////////////////////////////////////////////////////////
// nachfolgende Konstante definieren, wenn vordefinierte (nichtlöschbare) Views
// erzeugt werden sollen, die alle Objekte einer Objektklasse enthält, mit gemischten
// Geometrietypen in einer Spalte
#define _USE_PREDEFINED_GEOMETRYVIEWS

///////////////////////////////////////////////////////////////////////////////
// gibt das Trennzeichen zwischen TabellenName(Kurztext) und Objekttyp vor
#define TABLE_OBJTYPE_DELIMITER					L' '
#define TABLE_OBJTYPE_DELIMITER_PREFIX			L'('

#define TABLE_OBJTYPE_DELIMITER_STR_PREFIX		L" ("
#define TABLE_OBJTYPE_DELIMITER_STR_POSTFIX		L")"
#define TABLE_OBJTYPE_DELIMITER_STR_PREFIX_LEN	2
#define TABLE_OBJTYPE_DELIMITER_STR_POSTFIX_LEN	1

///////////////////////////////////////////////////////////////////////////////
// OGC specifics
#define _USE_OGC_OPTIONAL_COLUMNS

#endif // !defined(_TRIASOLEDBCONFIG_H__0B7FA77B_C771_4F94_821D_4220369F4B5E__INCLUDED_)
