// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.10.2000 08:08:45 
//
// @doc
// @module Strings.h | Declaration of the <c CStrings> class

#if !defined(_STRINGS_H__3C2093CA_3357_4740_A421_1865C9EE1D82__INCLUDED_)
#define _STRINGS_H__3C2093CA_3357_4740_A421_1865C9EE1D82__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbNB[16];
extern TCHAR g_cbSB[16];
extern TCHAR g_cbWL[16];
extern TCHAR g_cbOL[16];

extern const TCHAR g_cbTcf[];
extern const TCHAR g_cbIni[];
extern const TCHAR g_cbDef[];
extern const TCHAR g_cbDpd[];

extern const TCHAR g_cbNil[];

extern const TCHAR g_cbCOORDSYS[];

#endif // !defined(_STRINGS_H__3C2093CA_3357_4740_A421_1865C9EE1D82__INCLUDED_)
