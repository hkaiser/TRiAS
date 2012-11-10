// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.06.2002 16:35:25 
//
// @doc
// @module VidCtrlConfig.h | Konfigurationskonstanten für Xtension

#if !defined(_VIDCTRLCONFIG_H__D173D767_8080_46FE_A23F_4334ED2527E9__INCLUDED_)
#define _VIDCTRLCONFIG_H__D173D767_8080_46FE_A23F_4334ED2527E9__INCLUDED_

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
#pragma comment(lib, "ixtwtld.lib")
#pragma comment(lib, "ospace5d.lib")
#else
#pragma comment(lib, "ixtwtlr.lib")
#pragma comment(lib, "ospace5r.lib")
#endif // defined(_DEBUG

#else

#if defined(_DEBUG)
#pragma comment(lib, "ixtwtld70.lib")
#else
#pragma comment(lib, "ixtwtlr70.lib")
#endif // defined(_DEBUG

#endif // _MSC_VER < 1300

#endif // !defined(_VIDCTRLCONFIG_H__D173D767_8080_46FE_A23F_4334ED2527E9__INCLUDED_)
