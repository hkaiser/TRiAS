// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 10.03.2002 17:46:30 
//
// @doc
// @module CopyDLKConfig.h | Declaration of the <c CCopyDLKConfig> class

#if !defined(_COPYDLKCONFIG_H__E22781D1_7BB7_4773_99A0_05B23DC45FD0__INCLUDED_)
#define _COPYDLKCONFIG_H__E22781D1_7BB7_4773_99A0_05B23DC45FD0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB			// merge proxys/stubs with this dll
//#define __ATL_USED__				// ATL in diesem Projekt verwenden
#if _MSC_VER < 1300
#define __OSPACESTL_USED__			// ospace-STL verwenden
#endif // _MSC_VER < 1300
#define __MFC_USED__				// MFC verwenden (u.U. rauskommentieren!)

///////////////////////////////////////////////////////////////////////////////
// zusätzliche _DEBUG-Optionen
#if defined(_DEBUG) && defined(__ATL_USED__)
#define _ATLX_ASSERT_ON_FAILURE
// evtl. ausführliches AddRef/Release Tracking zuschalten
//#define _ATLX_DEBUG_REFCOUNT_WALKSTACK
//#define _USE_IMAGE_HELP			// dabei MSSymbols verwenden

// evtl. Objekte global zählen
#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT

// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI
#endif // _DEBUG

#endif // !defined(_COPYDLKCONFIG_H__E22781D1_7BB7_4773_99A0_05B23DC45FD0__INCLUDED_)
