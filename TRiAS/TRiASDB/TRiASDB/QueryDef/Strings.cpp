// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.07.99 21:31:32
//
// @doc
// @module Strings.cpp | Stringkonstanten

#include <StdAfx.h>

#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// 
const TCHAR g_cbTRiASDefaultName[] = TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbInterTRiASDefaultName[] = TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400

const OLECHAR g_cbObjectsMap[] = L"ObjectsMap";
const OLECHAR g_cbObjectMap[] = L"ObjectMap";

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
TCHAR g_cbTRiAS[_MAX_PATH];



