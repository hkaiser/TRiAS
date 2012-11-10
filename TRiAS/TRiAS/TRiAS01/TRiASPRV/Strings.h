// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.05.2001 13:01:22 
//
// @doc
// @module Strings.h | Declaration of the <c CStrings> class

#if !defined(_STRINGS_H__6F173E52_1497_431C_9197_0930F819AC62__INCLUDED_)
#define _STRINGS_H__6F173E52_1497_431C_9197_0930F819AC62__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten
extern const OLECHAR g_cbTRiAS[];			// OLESTR("TRiAS®")
extern const OLECHAR g_cbProviderVer[];		// TRIASOLEDB_VERSION_L L"." TRIASOLEDB_RELEASE_L L"." TRIASOLEDB_BUILD_L L", " TRIASOLEDB_COPYRIGHT_L;

///////////////////////////////////////////////////////////////////////////////
// globale Strings, die bei Startup geladen werden
extern OLECHAR g_cbProviderName[];
extern OLECHAR g_cbProviderFriendlyName[];
extern OLECHAR g_cbTableTerm[];

///////////////////////////////////////////////////////////////////////////////
// 
extern const TCHAR g_cbViewSelectP[];		// "SELECT points.* FROM [%ls (POINTS)] points"
extern const TCHAR g_cbViewSelectL[];		// "SELECT lines.* FROM [%ls (LINES)] lines"
extern const TCHAR g_cbViewSelectA[];		// "SELECT areas.* FROM [%ls (AREAS)] areas"
extern const TCHAR g_cbViewSelectT[];		// "SELECT texts.* FROM [%ls (TEXTS)] texts"

#endif // !defined(_STRINGS_H__6F173E52_1497_431C_9197_0930F819AC62__INCLUDED_)
