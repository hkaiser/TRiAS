// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 14.03.2002 21:27:59 
//
// @doc
// @module TrSABiSConfig.h | Declaration of the <c CTrSABiSConfig> class

#if !defined(_TRSABISCONFIG_H__90258AA5_410C_440D_8F4A_40A66AEB702B__INCLUDED_)
#define _TRSABISCONFIG_H__90258AA5_410C_440D_8F4A_40A66AEB702B__INCLUDED_

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
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#define _ATLX_DEBUG_OBJECTCOUNT
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungs-Spezifika
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__
#define __ATL_XTENSION_BASE__

///////////////////////////////////////////////////////////////////////////////
// defines für SmartIF's
#define OS_NO_STREAM_SUPPORT
#define QI_EXCEPTION

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Bibliotheken
#if defined(_DEBUG)
#pragma comment(lib, "Ixtmad50.lib")
#pragma comment(lib, "ospace5d.lib")
#pragma comment(lib, "TriasTld.lib")
#else
#pragma comment(lib, "Ixtmar50.lib")
#pragma comment(lib, "ospace5r.lib")
#pragma comment(lib, "TriasTlb.lib")
#endif // defined(_DEBUG

#endif // !defined(_TRSABISCONFIG_H__90258AA5_410C_440D_8F4A_40A66AEB702B__INCLUDED_)
