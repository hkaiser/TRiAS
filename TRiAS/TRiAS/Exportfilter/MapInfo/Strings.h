// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.01.2001 12:48:59 
//
// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__D2CA71C8_0771_4056_8531_BE2A4A6020A5__INCLUDED_)
#define _STRINGS_H__D2CA71C8_0771_4056_8531_BE2A4A6020A5__INCLUDED_

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

#endif // !defined(_STRINGS_H__D2CA71C8_0771_4056_8531_BE2A4A6020A5__INCLUDED_)
