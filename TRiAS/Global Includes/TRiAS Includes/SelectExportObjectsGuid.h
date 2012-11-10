// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 05.05.99 21:16:18 
//
// @doc
// @module SelectExportObjectsGuid.h | Declaration of the GUID for the <c CSelectExportObjectsGuid> class

#if !defined(_SELECTEXPORTOBJECTSGUID_H__FADE50A0_031E_11D3_94CB_0080C786297B__INCLUDED_)
#define _SELECTEXPORTOBJECTSGUID_H__FADE50A0_031E_11D3_94CB_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// GUID ///////////////////////////////////////////////////////////////////////
// {C3CF0270-0190-11D3-94CB-0080C786297B}
DEFINE_GUID(CLSID_SelectObjectsDatasource, 0xC3CF0270L, 0x0190, 0x11D3, 0x94, 0xCB, 0x00, 0x80, 0xC7, 0x86, 0x29, 0x7B);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbSelectObjectsdataSource[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Objekte aus Datenquellen selektieren";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren
#endif // !defined(_SELECTEXPORTOBJECTSGUID_H__FADE50A0_031E_11D3_94CB_0080C786297B__INCLUDED_)
