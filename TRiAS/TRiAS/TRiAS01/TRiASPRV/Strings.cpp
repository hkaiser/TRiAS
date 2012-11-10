// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.05.2001 13:02:17 
//
// @doc
// @module Strings.cpp | Definition of the <c CStrings> class

#include "StdAfx.h"
#include "Strings.h"
#include "Version.h"

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten
const OLECHAR g_cbTRiAS[] = OLESTR("TRiAS®");
const OLECHAR g_cbProviderVer[] = L"0" TRIASOLEDB_VERSION_L L"." TRIASOLEDB_RELEASE_L L".0" TRIASOLEDB_BUILD_L;

///////////////////////////////////////////////////////////////////////////////
// globale Strings, die bei Startup geladen werden
OLECHAR g_cbProviderName[_MAX_PATH];
OLECHAR g_cbProviderFriendlyName[_MAX_PATH];

OLECHAR g_cbTableTerm[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// 
const TCHAR g_cbViewSelectP[] = "SELECT points.* FROM [%ls (POINTS)] points";
const TCHAR g_cbViewSelectL[] = "SELECT lines.* FROM [%ls (LINES)] lines";
const TCHAR g_cbViewSelectA[] = "SELECT areas.* FROM [%ls (AREAS)] areas";
const TCHAR g_cbViewSelectT[] = "SELECT texts.* FROM [%ls (TEXTS)] texts";

