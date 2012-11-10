// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.03.2001 10:57:40 
//
// @doc
// @module TRiASMainConfigVersion.h | Konfigurationskonstanten für TRiAS (versionsabhängig)

#if !defined(_TRIASMAINCONFIGVERSION_H__6D3DF331_6C42_4955_BCFD_53FE4822ED6D__INCLUDED_)
#define _TRIASMAINCONFIGVERSION_H__6D3DF331_6C42_4955_BCFD_53FE4822ED6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Xml-Templates für GeoComponentSequences verwenden (keep in sync with TRiAS03Config.h)
#if _TRiAS_VER >= 0x0410
#define _USE_XML_GEOCOMPONENTS
#endif // _TRiAS_VER >= 0x0410

///////////////////////////////////////////////////////////////////////////////
// Xml-Templates für zusätzliche Objekteigenschaften verwenden
#if defined(_USE_XML_GEOCOMPONENTS) && defined(_DEBUG)
#define _USE_XML_GEOCOMPONENTS_OBJECTPROPS
#endif // defined(_USE_XML_GEOCOMPONENTS) && defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// Objektbezogene Darstellungsparameter beim Kopieren der Visinfos mit übernehmen
// #HK010307
#if _TRiAS_VER >= 0x0410
#define _USE_OBJECT_COPYVISINFO
#endif // _TRiAS_VER >= 0x0410

///////////////////////////////////////////////////////////////////////////////
// LegendenLayout 
#if defined(_DEBUG)
#define _USE_LEGEND_LAYOUT
#endif // defined(_DEBUG)

#endif // !defined(_TRIASMAINCONFIGVERSION_H__6D3DF331_6C42_4955_BCFD_53FE4822ED6D__INCLUDED_)
