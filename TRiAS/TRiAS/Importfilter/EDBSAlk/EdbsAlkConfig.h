// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.09.2000 19:13:42 
//
// @doc
// @module EdbsAlkConfig.h | Declaration of the <c CEdbsAlkConfig> class

#if !defined(_EDBSALKCONFIG_H__9FDE133B_E166_4909_9A0C_E58CECA1B6E5__INCLUDED_)
#define _EDBSALKCONFIG_H__9FDE133B_E166_4909_9A0C_E58CECA1B6E5__INCLUDED_

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
#define __MFC__						// MFC wird verwendet
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungsspezifika
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__

///////////////////////////////////////////////////////////////////////////////
// die folgende Definition reinnehmen, wenn alte Konfigurationsdialoge 
// verfügbar sein sollen
//#define _USE_CONFIG_DIALOGS

#endif // !defined(_EDBSALKCONFIG_H__9FDE133B_E166_4909_9A0C_E58CECA1B6E5__INCLUDED_)
