// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/05/1998 10:53:59 PM
//
// @doc
// @module Strings.cpp | Stringkonstanten

#include "StdAfx.h"

#include "Strings.h"

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbTRiASDefaultName[] = TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbInterTRiASDefaultName[] = TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)

TCHAR g_cbTRiAS[_MAX_PATH];
