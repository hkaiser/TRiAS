// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 10.09.2001 11:11:29 
//
// @doc
// @module String.h | Declaration of string constants

#if !defined(_STRING_H__E70FEAAC_21C6_4FF7_9278_D54BBD55AB16__INCLUDED_)
#define _STRING_H__E70FEAAC_21C6_4FF7_9278_D54BBD55AB16__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Name
extern const TCHAR g_cbTRiASName[];		// TEXT("TRiASName");
extern const TCHAR g_cbRegConfig[];		// TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
extern const TCHAR g_cbCopyrightName[];	// TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// beschreibbare Zeichenketten
extern TCHAR g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRING_H__E70FEAAC_21C6_4FF7_9278_D54BBD55AB16__INCLUDED_)
