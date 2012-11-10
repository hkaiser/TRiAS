// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/09/1998 08:57:59 PM
//
// @doc
// @module ScriptPropActGuid.h | Allgemeines zur PropertyAction 'CLSID_ScriptPropAct' 

#if !defined(_SCRIPTPROPACTGUID_H__50AECBE4_46E8_11D2_9EBF_006008447800__INCLUDED_)
#define _SCRIPTPROPACTGUID_H__50AECBE4_46E8_11D2_9EBF_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GUID ///////////////////////////////////////////////////////////////////////
// {50AECBE5-46E8-11D2-9EBF-006008447800}
DEFINE_GUID(CLSID_ScriptPropAct, 0x50AECBE5L, 0x46E8, 0x11D2, 0x9E, 0xBF, 0x00, 0x60, 0x08, 0x44, 0x78, 0x00);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbScriptpropAct[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Bearbeiten von Objekten durch BasicScripte";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // !defined(_SCRIPTPROPACTGUID_H__50AECBE4_46E8_11D2_9EBF_006008447800__INCLUDED_)
