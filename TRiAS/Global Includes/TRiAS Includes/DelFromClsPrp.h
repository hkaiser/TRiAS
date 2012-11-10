// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2000 20:16:49 
//
// @doc
// @module DelFromClsPrp.h | Declaration of the <c CDelFromClsPrp> class

#if !defined(_DELFROMCLSPRP_H__A592E248_628A_4456_9904_F8E180074BB9__INCLUDED_)
#define _DELFROMCLSPRP_H__A592E248_628A_4456_9904_F8E180074BB9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// GUID ///////////////////////////////////////////////////////////////////////
// {2F1FFEA0-0D4F-403D-9B02-371FE4AE8B7E}
DEFINE_GUID(CLSID_RemoveFromObjectClass, 0x2F1FFEA0L, 0x0D4F, 0x403D, 0x9B, 0x02, 0x37, 0x1F, 0xE4, 0xAE, 0x8B, 0x7E);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbDelFromClassName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Entfernt sämtliche ausgewählten Objekte aus ihrer Rechercheobjektmenge.";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // !defined(_DELFROMCLSPRP_H__A592E248_628A_4456_9904_F8E180074BB9__INCLUDED_)
