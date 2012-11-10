// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 02/18/1999 10:29:59 PM
//
// @doc 
// @module DexCommands.h | Description goes here

#if !defined(_DEXCOMMANDS_H__710B2C38_890F_11D2_9EFB_006008447800__INCLUDED_)
#define _DEXCOMMANDS_H__710B2C38_890F_11D2_9EFB_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// in dieser Erweiterung definierte command handler
	LRESULT OnDefineNewObjects (HPROJECT, LPARAM);		// DEX_DEFINENEWOBJECTS

#endif // !defined(_DEXCOMMANDS_H__710B2C38_890F_11D2_9EFB_006008447800__INCLUDED_)
