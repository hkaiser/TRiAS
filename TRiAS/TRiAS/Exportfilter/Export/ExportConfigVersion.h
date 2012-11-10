// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 14.10.2001 09:22:47 
//
// @doc
// @module ExportConfigVersion.h | Konfigurationskonstanten für Export (versionsabhängig)

#if !defined(_EXPORTCONFIGVERSION_H__C0EFE256_60A0_4DEF_BE41_3AE268EF5244__INCLUDED_)
#define _EXPORTCONFIGVERSION_H__C0EFE256_60A0_4DEF_BE41_3AE268EF5244__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Xml-Templates für GeoComponentSequences verwenden (keep in sync with TRiASMainConfig.h)
#if _TRiAS_VER >= 0x0410
#define _USE_XML_GEOCOMPONENTS
#endif // _TRiAS_VER >= 0x0410

#endif // !defined(_EXPORTCONFIGVERSION_H__C0EFE256_60A0_4DEF_BE41_3AE268EF5244__INCLUDED_)
