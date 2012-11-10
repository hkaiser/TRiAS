// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/10/1998 12:02:44 PM
//
// @doc
// @module ColorsConfig.h | Konfigurationskonstanten für Colors.Ebn

#if !defined(_COLORSCONFIG_H__77DDD6D5_901C_11D2_9EFF_006008447800__INCLUDED_)
#define _COLORSCONFIG_H__77DDD6D5_901C_11D2_9EFF_006008447800__INCLUDED_

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
// #define _USE_TRIAS_MESSAGES
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
//#define _ATL_DEBUG_QI
#endif // _DEBUG

#define EBWIN32

#endif // !defined(_COLORSCONFIG_H__77DDD6D5_901C_11D2_9EFF_006008447800__INCLUDED_)
