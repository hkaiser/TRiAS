// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/14/1998 10:49:11 AM
//
// @doc
// @module GeoStatConfig.h | Konfigurationskonstanten für GeoStat

#if !defined(_GEOSTATCONFIG_H__BF399EA5_9327_11D2_9F04_006008447800__INCLUDED_)
#define _GEOSTATCONFIG_H__BF399EA5_9327_11D2_9F04_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __CV__

//#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungs
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__
#define __XTENSNDLL__
#define EBWIN32

#endif // !defined(_GEOSTATCONFIG_H__BF399EA5_9327_11D2_9F04_006008447800__INCLUDED_)
