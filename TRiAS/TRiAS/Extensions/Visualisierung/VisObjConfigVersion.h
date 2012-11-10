// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.03.2001 13:54:08 
//
// @doc
// @module VisObjConfigVersion.h | Konfigurationskonstanten für VisObj (versionsabhängig)

#if !defined(_VISOBJCONFIGVERSION_H__F36B24A1_7040_48ED_A1CB_2A00D22CB3A3__INCLUDED_)
#define _VISOBJCONFIGVERSION_H__F36B24A1_7040_48ED_A1CB_2A00D22CB3A3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// für VisModule PropertyACtions verwenden
#if _TRiAS_VER > 0x0410
#define _USE_PROPACT_FOR_CUSTOMVIS
#endif // _TRiAS_VER >= 0x0410

#endif // !defined(_VISOBJCONFIGVERSION_H__F36B24A1_7040_48ED_A1CB_2A00D22CB3A3__INCLUDED_)
