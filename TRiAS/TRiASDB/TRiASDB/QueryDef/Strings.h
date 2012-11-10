// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.07.99 21:30:27 
//
// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__3882C952_33D9_11D3_94FA_0080C786297B__INCLUDED_)
#define _STRINGS_H__3882C952_33D9_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
extern const TCHAR g_cbTRiASDefaultName[];			// TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbInterTRiASDefaultName[];		// TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400

extern const OLECHAR g_cbObjectsMap[];				// TEXT("ObjectsMap");
extern const OLECHAR g_cbObjectMap[];				// TEXT("ObjectMap");

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRINGS_H__3882C952_33D9_11D3_94FA_0080C786297B__INCLUDED_)
