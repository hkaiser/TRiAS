// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 18:47:34 
//
// @doc
// @module TextReplacePrp.h | Declaration of the <c CTextReplacePrp> class

#if !defined(_TEXTREPLACEPRP_H__D9F90E06_72CB_40FA_AB5B_E4620A7C79F7__INCLUDED_)
#define _TEXTREPLACEPRP_H__D9F90E06_72CB_40FA_AB5B_E4620A7C79F7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// GUID ///////////////////////////////////////////////////////////////////////
// {F6BE912A-BE20-4ABE-8B22-025B7FEA9822}
DEFINE_GUID(CLSID_TextReplaceEngine, 0xF6BE912AL, 0xBE20, 0x4ABE, 0x8B, 0x22, 0x02, 0x5B, 0x7F, 0xEA, 0x98, 0x22);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbTextReplaceName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Sucht und ersetzt in Werten von Objekteigenschaften.";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // !defined(_TEXTREPLACEPRP_H__D9F90E06_72CB_40FA_AB5B_E4620A7C79F7__INCLUDED_)
