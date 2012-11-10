// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.03.2001 10:56:03 
//
// @doc
// @module TRiAS03ConfigVersion.h | Konfigurationskonstanten für TRiAS03 (versionsabhängig)

#if !defined(_TRIAS03CONFIGVERSION_H__D03682CA_F2A0_4895_859C_28F93389F6A0__INCLUDED_)
#define _TRIAS03CONFIGVERSION_H__D03682CA_F2A0_4895_859C_28F93389F6A0__INCLUDED_

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

///////////////////////////////////////////////////////////////////////////////
// AbfrageDialog bei Suchen/Ersetzen verwenden
#if _TRiAS_VER >= 0x0400
#define _USE_CONFIRMREPLACE_DIALOG
#endif // _TRiAS_VER >= 0x0400

#endif // !defined(_TRIAS03CONFIGVERSION_H__D03682CA_F2A0_4895_859C_28F93389F6A0__INCLUDED_)
