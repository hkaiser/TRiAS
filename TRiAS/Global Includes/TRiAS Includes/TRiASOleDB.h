// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.05.2001 10:34:37 
//
// @doc
// @module TRiASOleDB.h | Declaration of the TRiAS specific OleDB properties

#if !defined(_TRIASOLEDB_H__183A596A_4237_408E_9732_ADB535A9ED7D__INCLUDED_)
#define _TRIASOLEDB_H__183A596A_4237_408E_9732_ADB535A9ED7D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Konfigurationskonstanten
#if !defined(_TRiAS_OLEDB_VER)
#define _TRiAS_OLEDB_VER _TRiAS_VER
#endif // !defined(_TRiAS_OLEDB_VER)

///////////////////////////////////////////////////////////////////////////////
// TRiAS spezifische Properties
// B3EE7F41-D397-4C3C-832F-1649A5F09DC0
extern "C" const GUID __declspec(selectany) DBPROPSET_TRiAS_INITDATASOURCE = 
	{ 0xB3EE7F41, 0xD397, 0x4C3C, 0x83, 0x2F, 0x16, 0x49, 0xA5, 0xF0, 0x9D, 0xC0 };
// B3EE7F42-D397-4C3C-832F-1649A5F09DC0
extern "C" const GUID __declspec(selectany) DBPROPSET_TRiAS_CREATEDATASOURCE = 
	{ 0xB3EE7F42, 0xD397, 0x4C3C, 0x83, 0x2F, 0x16, 0x49, 0xA5, 0xF0, 0x9D, 0xC0 };
// B3EE7F43-D397-4C3C-832F-1649A5F09DC0
extern "C" const GUID __declspec(selectany) DBPROPSET_TRiAS_DATASOURCEINFO = 
	{ 0xB3EE7F43, 0xD397, 0x4C3C, 0x83, 0x2F, 0x16, 0x49, 0xA5, 0xF0, 0x9D, 0xC0 };

///////////////////////////////////////////////////////////////////////////////
// TRiAS spezifische properties
enum DBPROPENUM_TRiAS {
// DBPROPSET_TRiAS_INITDATASOURCE
	DBPROP_TRiAS_GEOMETRYTYPE = 0x1,		// VT_I4: Art der Bereitstellung der Geometrien
	DBPROP_TRiAS_GENERATEVIEWS = 0x2,		// VT_BOOL: Vordefinierte Views erzeugen

// DBPROPSET_TRiAS_CREATEDATASOURCE
	DBPROP_TRiAS_CREATE_COMPATIBLE = 0x10,	// VT_I4: kompatibel zu TRiAS V2, V3 oder V4
	DBPROP_TRiAS_CREATE_COMPRESSED = 0x11,	// VT_BOOL: komprimierte Datenbank

// DBPROPSET_TRiAS_DATASOURCEINFO
	DBPROP_TRiAS_DBVERSION = 0x21,			// VT_BSTR: Dateiversion der Datenbank
};

///////////////////////////////////////////////////////////////////////////////
// mögliche Werte für DPROPENUM_TRiAS properties
// DBPROP_TRiAS_GEOMETRYTYPE
#define DBPROPVAL_TRiAS_GEOMETRYCOLUMNS		0x00000001	// Geometrien als Spalten in einer Tabelle
#define DBPROPVAL_TRiAS_GEOMETRYTABLES		0x00000002	// Objekte verschiedener Typen in verschiedenen Tabellen

#endif // !defined(_TRIASOLEDB_H__183A596A_4237_408E_9732_ADB535A9ED7D__INCLUDED_)
