// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/23/1998 07:19:03 PM
//
// @doc
// @module ObjekteVereinigenGuid.h | GUID für PropertyAction 'ObjekteVereinigen'

#if !defined(_OBJEKTEVEREINIGENGUID_H__D32D1684_5308_11D2_9ECC_006008447800__INCLUDED_)
#define _OBJEKTEVEREINIGENGUID_H__D32D1684_5308_11D2_9ECC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GUID ///////////////////////////////////////////////////////////////////////
// {D32D1685-5308-11D2-9ECC-006008447800}
DEFINE_GUID(CLSID_ObjekteVereinigen, 0xD32D1685L, 0x5308, 0x11D2, 0x9E, 0xCC, 0x00, 0x60, 0x08, 0x44, 0x78, 0x00);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbObjekteVereinigenPropAct[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Vereinigen aller Eingabeobjekte";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle vereinigten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // !defined(_OBJEKTEVEREINIGENGUID_H__D32D1684_5308_11D2_9ECC_006008447800__INCLUDED_)
