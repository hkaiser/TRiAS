// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:18:07 PM
//
// @doc 
// @module PerfMonConfig.h | Konfigurationskonstanten für PerfMon

#if !defined(_PERFMONCONFIG_H__8FE6106F_9A8D_11D2_9F08_006008447800__INCLUDED_)
#define _PERFMONCONFIG_H__8FE6106F_9A8D_11D2_9F08_006008447800__INCLUDED_

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
#endif // _DEBUG

#define __MFC__

#define CLASSICS_EXPORT				// no __declspec(dllexport/dllimport) at all

#endif // !defined(_PERFMONCONFIG_H__8FE6106F_9A8D_11D2_9F08_006008447800__INCLUDED_)
