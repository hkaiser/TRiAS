// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 09:23:30 
//
// @doc
// @module TRiASSQConfig.h | Declaration of the <c CTRiASSQConfig> class

#if !defined(_TRIASSQCONFIG_H__11155A0A_88EE_41ED_969C_D3BEBF50DF0E__INCLUDED_)
#define _TRIASSQCONFIG_H__11155A0A_88EE_41ED_969C_D3BEBF50DF0E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define _MERGE_PROXYSTUB

#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden

///////////////////////////////////////////////////////////////////////////////
// zusätzliche _DEBUG-Optionen
#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE

// evtl. Objekte global zählen
#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT
#define _DUMP_PENDING_OBJECTS

// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI
#endif // _DEBUG

#endif // !defined(_TRIASSQCONFIG_H__11155A0A_88EE_41ED_969C_D3BEBF50DF0E__INCLUDED_)
