// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.08.2000 21:36:57 
//
// @doc
// @module EdbsImpConfig.h | Declaration of the <c CEdbsImpConfig> class

#if !defined(_EDBSIMPCONFIG_H__B180A77D_9EAC_4DAB_BFD0_498E98B9B29F__INCLUDED_)
#define _EDBSIMPCONFIG_H__B180A77D_9EAC_4DAB_BFD0_498E98B9B29F__INCLUDED_

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

///////////////////////////////////////////////////////////////////////////////
// B-Regeln verwenden
//#define _USE_B_REGELN

#endif // !defined(_EDBSIMPCONFIG_H__B180A77D_9EAC_4DAB_BFD0_498E98B9B29F__INCLUDED_)
