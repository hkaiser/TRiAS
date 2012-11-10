// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.09.2001 21:31:50 
//
// @doc
// @module StatisticsImageIds.h | Declaration of the Imagelist-Ids 

#if !defined(_STATISTICSIMAGEIDS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_)
#define _STATISTICSIMAGEIDS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// ItemIds in Imagelist
#define OVL_PUBLISH							1		// publish overlay

#define IMG_NOICON							0
#define IMG_PUBLISH							1

#define IMG_DATASOURCE						18		// allgemeine Datenquelle
#define IMG_DATASOURCE_TRiAS1				19		// .stb
#define IMG_DATASOURCE_TRiAS2				20		// V2.0 .ris
#define IMG_DATASOURCE_TRiAS3				21		// V3.0 .ris
#define IMG_DATASOURCE_TRiAS_EMBEDDED		22		// V3.0 embedded in .riw
#define IMG_DATASOURCE_ARCVIEW				23		// ArcView
#define IMG_DATASOURCE_MAPINFO				24		// MapInfo
#define IMG_DATASOURCE_OLEDB				25		// OleDb
#define IMG_DATASOURCE_POLYGIS				26		// PolyGIS
#define IMG_DATASOURCE_GDO					27		// Geomedia GDO
#define IMG_DATASOURCE_MEMDB				28		// FastDB

#define IMG_WORKSPACE						29		// Workspace

#define IMG_STATFUNC_TAB					30
#define IMG_STATFUNC						31
#define IMG_STATFUNC_CLASS					32		// StatFunc für Objektklassen
#define IMG_STATFUNC_CUM					33		// kumulative StatFunc
#define IMG_STATFUNC_CLASS_CUM				34		// kumulative StatFunc für Objektklassen

#define IMG_STATFUNC_ORWND					35		// StatFunc für Objektrecherchfenster

#define IMG_STATFUNC_OBJECT					36		// StatFunc für Objekte
#define IMG_STATFUNC_OBJECT_CUM				37		// kumulative StatFunc für Objekte
#define IMG_STATFUNC_POINT					38		// StatFunc für Punkte
#define IMG_STATFUNC_LINE					39		// StatFunc für Linien
#define IMG_STATFUNC_AREA					40		// StatFunc für Flächen
#define IMG_STATFUNC_TEXT					41		// StatFunc für Texte

#define IMG_STATFUNC_ORWND_NODE				42		// Recherchefenster
#define IMG_STATFUNC_ORWND_CUM				43		// kumulative StatFunc für Recherchefenster

///////////////////////////////////////////////////////////////////////////////
// Column numbers
#define NAME_COLUMN							0
#define VALUE_COLUMN						1

#endif // !defined(_STATISTICSIMAGEIDS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_)
