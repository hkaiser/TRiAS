// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.11.2000 16:04:01 
//
// @doc
// @module TestExtConfig.h | Konfigurationskonstanten für Xtension

#if !defined(_TESTEXTCONFIG_H__E9C86B1E_FADF_4E94_B55D_DD45DFF0B587__INCLUDED_)
#define _TESTEXTCONFIG_H__E9C86B1E_FADF_4E94_B55D_DD45DFF0B587__INCLUDED_

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
#define __MFC__
#define __STL_OSPACE5__

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
#if defined(_DEBUG)
#pragma comment(lib, "ixtmad50.lib")
#pragma comment(lib, "ospace5d.lib")
#else
#pragma comment(lib, "ixtmar50.lib")
#pragma comment(lib, "ospace5r.lib")
#endif // defined(_DEBUG

#endif // !defined(_TESTEXTCONFIG_H__E9C86B1E_FADF_4E94_B55D_DD45DFF0B587__INCLUDED_)
