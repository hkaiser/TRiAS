// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 28.06.2001 22:33:14 
//
// @doc
// @module OleDbOGC.h | Declaration of the OGC specific constants

#if !defined(_OLEDBOGC_H__7122BA91_E3EF_43CA_AB82_43129F5A40F3__INCLUDED_)
#define _OLEDBOGC_H__7122BA91_E3EF_43CA_AB82_43129F5A40F3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// OGC Schema GUID's
// {A0690A29-FAF5-11d1-BAF5-080036DB0B03}
EXTERN_C const GUID __declspec(selectany) DBSCHEMA_OGIS_FEATURE_TABLES = 
	{ 0xA0690A29, 0xFAF5, 0x11D1, { 0xBA, 0xF5, 0x08, 0x00, 0x36, 0xDB, 0x0B, 0x03 }};

// {A0690A2A-FAF5-11d1-BAF5-080036DB0B03}
EXTERN_C const GUID __declspec(selectany) DBSCHEMA_OGIS_GEOMETRY_COLUMNS = 
	{ 0xA0690A2A, 0xFAF5, 0x11D1, { 0xBA, 0xF5, 0x08, 0x00, 0x36, 0xDB, 0x0B, 0x03 }};

// {A0690A2B-FAF5-11d1-BAF5-080036DB0B03}
EXTERN_C const GUID __declspec(selectany) DBSCHEMA_OGIS_SPATIAL_REF_SYSTEMS = 
	{ 0xA0690A2B, 0xFAF5, 0x11D1, { 0xBA, 0xF5, 0x08, 0x00, 0x36, 0xDB, 0x0B, 0x03 }};

// {A0690A2C-FAF5-11d1-BAF5-080036DB0B03}
EXTERN_C const GUID __declspec(selectany) DBPROPSET_OGIS_SPATIAL_OPS = 
	{ 0xA0690A2C, 0xFAF5, 0x11D1, { 0xBA, 0xF5, 0x08, 0x00, 0x36, 0xDB, 0x0B, 0x03 }};

enum DBPROPOGISENUM {
	DBPROP_OGIS_TOUCHES = 0x1L,
	DBPROP_OGIS_WITHIN = 0x2L,
	DBPROP_OGIS_CONTAINS = 0x3L,
	DBPROP_OGIS_CROSSES = 0x4L,
	DBPROP_OGIS_OVERLAPS = 0x5L,
	DBPROP_OGIS_DISJOINT = 0x6L,
	DBPROP_OGIS_INTERSECT = 0x7L,
	DBPROP_OGIS_ENVELOPE_INTERSECTS = 0x8L,
	DBPROP_OGIS_INDEX_INTERSECTS = 0x9L
};

///////////////////////////////////////////////////////////////////////////////
// additional optional columns for IColumnsRowset
#define LOCAL_GUID_NULL { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}

EXTERN_C const DBID __declspec(selectany) DBCOLUMN_GEOM_TYPE = { LOCAL_GUID_NULL, DBKIND_NAME, L"GEOM_TYPE" };
EXTERN_C const DBID __declspec(selectany) DBCOLUMN_SPATIAL_REF_SYSTEM_ID = { LOCAL_GUID_NULL, DBKIND_NAME, L"SPATIAL_REF_SYSTEM_ID"};
EXTERN_C const DBID __declspec(selectany) DBCOLUMN_SPATIAL_REF_SYSTEM_WKT = { LOCAL_GUID_NULL, DBKIND_NAME, L"SPATIAL_REF_SYSTEM_WKT"};

#endif // !defined(_OLEDBOGC_H__7122BA91_E3EF_43CA_AB82_43129F5A40F3__INCLUDED_)
