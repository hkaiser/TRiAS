// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/05/1998 08:56:19 PM
//
// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__FECFEB45_5C7D_11D2_9ED7_006008447800__INCLUDED_)
#define _STRINGS_H__FECFEB45_5C7D_11D2_9ED7_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

extern const TCHAR g_cbNil[];						// TEXT("");
extern const TCHAR g_cbTRiASDefaultName[];			// TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbInterTRiASDefaultName[];		// TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];

#endif // !defined(_STRINGS_H__FECFEB45_5C7D_11D2_9ED7_006008447800__INCLUDED_)
