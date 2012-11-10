// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.01.2000 10:46:21 
//
// @doc
// @module AddAsClsPrp.h | Allgemeines zur PropertyAction 'CLSID_AddAsObjectClass'

#if !defined(_ADDASCLSPRP_H__3F921636_170D_42E2_A1D1_446AA742362D__INCLUDED_)
#define _ADDASCLSPRP_H__3F921636_170D_42E2_A1D1_446AA742362D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// GUID ///////////////////////////////////////////////////////////////////////
// {B5E77BA6-2BA0-4FB0-BB4E-D3E102EB505E}
DEFINE_GUID(CLSID_AddAsObjectClass, 0xB5E77BA6L, 0x2BA0, 0x4FB0, 0xBB, 0x4E, 0xD3, 0xE1, 0x02, 0xEB, 0x50, 0x5E);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbAddAsClassName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Speichert sämtliche ausgewählten Objekte als neue Objektklasse.";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // !defined(_ADDASCLSPRP_H__3F921636_170D_42E2_A1D1_446AA742362D__INCLUDED_)
