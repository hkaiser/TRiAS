// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/12/1998 09:36:54 PM
//
// @doc
// @module ObjekteDoppelnGuid.h | GUID für PropertyAction 'ObjekteDoppeln'

#if !defined(_OBJEKTEDOPPELNGUID_H__E3C50CA5_4A48_11D2_9EC2_006008447800__INCLUDED_)
#define _OBJEKTEDOPPELNGUID_H__E3C50CA5_4A48_11D2_9EC2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// GUID ///////////////////////////////////////////////////////////////////////
// {4480D1A5-481C-11D2-9EBF-006008447800}
DEFINE_GUID(CLSID_ObjekteDoppelnV1, 0x4480D1A5L, 0x481C, 0x11D2, 0x9E, 0xBF, 0x00, 0x60, 0x08, 0x44, 0x78, 0x00);

// {D3F0170D-E741-4AD5-9BF0-82CDA30B1EF2}
DEFINE_GUID(CLSID_ObjekteDoppelnV2, 0xD3F0170DL, 0xE741, 0x4AD5, 0x9B, 0xF0, 0x82, 0xCD, 0xA3, 0x0B, 0x1E, 0xF2);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbObjekteDoppelnPropAct[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Doppeln aller Eingabeobjekte";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // !defined(_OBJEKTEDOPPELNGUID_H__E3C50CA5_4A48_11D2_9EC2_006008447800__INCLUDED_)
