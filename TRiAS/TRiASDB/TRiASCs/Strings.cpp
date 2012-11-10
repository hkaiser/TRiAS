// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.10.2000 08:08:58 
//
// @doc
// @module Strings.cpp | Definition of the <c CStrings> class

#include "StdAfx.h"
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
TCHAR g_cbNB[16];
TCHAR g_cbSB[16];
TCHAR g_cbWL[16];
TCHAR g_cbOL[16];

const TCHAR g_cbTcf[] = _T("tcf");
const TCHAR g_cbIni[] = _T("ini");
const TCHAR g_cbNil[] = _T("");
const TCHAR g_cbDef[] = _T("def");		// für SABiS
const TCHAR g_cbDpd[] = _T("dpd");

const TCHAR g_cbCOORDSYS[] = _T("COORDSYS");
