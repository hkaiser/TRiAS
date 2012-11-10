// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.07.2002 14:58:26 
//
// @doc
// @module CvrtGuidConfig.h | Declaration of the <c CCvrtGuidConfig> class

#if !defined(_CVRTGUIDCONFIG_H__09B4A698_A918_4865_8FC2_05FCF506737E__INCLUDED_)
#define _CVRTGUIDCONFIG_H__09B4A698_A918_4865_8FC2_05FCF506737E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __WTL__

#if _MSC_VER < 1300
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#else
#define OS_NO_STREAM_SUPPORT
#endif // _MSC_VER < 1300

#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungs-Spezifika
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Bibliotheken
#if _MSC_VER < 1300

#if defined(_DEBUG)
#pragma comment(lib, "ospace5d.lib")
#else
#pragma comment(lib, "ospace5r.lib")
#endif // defined(_DEBUG

#endif // _MSC_VER < 1300

#endif // !defined(_CVRTGUIDCONFIG_H__09B4A698_A918_4865_8FC2_05FCF506737E__INCLUDED_)
