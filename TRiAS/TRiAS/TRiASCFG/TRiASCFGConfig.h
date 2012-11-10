// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.12.2000 20:27:12 
//
// @doc
// @module TRiASCFGConfig.h | Konfigurationskonstanten für TRiASCFG

#if !defined(_TRIASCFGCONFIG_H__8B382681_A4D9_4165_A656_931F8DE7FBAE__INCLUDED_)
#define _TRIASCFGCONFIG_H__8B382681_A4D9_4165_A656_931F8DE7FBAE__INCLUDED_

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

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE

// track memory leaks
#define _CRTDBG_MAP_ALLOC

// evtl. Objekte global zählen
#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT

#endif // _DEBUG

#endif // !defined(_TRIASCFGCONFIG_H__8B382681_A4D9_4165_A656_931F8DE7FBAE__INCLUDED_)
