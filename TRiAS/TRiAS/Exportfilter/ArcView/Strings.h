// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 14:22:27 
//
// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__53B3D841_4A21_4667_82D4_3207EE3A881F__INCLUDED_)
#define _STRINGS_H__53B3D841_4A21_4667_82D4_3207EE3A881F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Dateierweiterungen
extern const TCHAR g_cbShp[];		// TEXT("shp");
extern const TCHAR g_cbShx[];		// TEXT("shx");
extern const TCHAR g_cbDbf[];		// TEXT("dbf");

extern const TCHAR g_cbNil[];		// TEXT("");

///////////////////////////////////////////////////////////////////////////////
// sonstiges
extern const TCHAR g_cbLabelText[];	// TEXT("LabelText");

#endif // !defined(_STRINGS_H__53B3D841_4A21_4667_82D4_3207EE3A881F__INCLUDED_)
