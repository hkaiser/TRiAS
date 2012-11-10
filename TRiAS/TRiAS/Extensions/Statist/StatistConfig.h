// @doc
// @module StatistConfig.h | Konfigurationskonstanten für Xtension

#if !defined(_STATISTCONFIG_H__CF461D84_EE47_11D2_9BE4_BAF620524153__INCLUDED_)
#define _STATISTCONFIG_H__CF461D84_EE47_11D2_9BE4_BAF620524153__INCLUDED_

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
#define __WTL__

#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#define _EXCLUDE_IPARSE_ETC_FROM_HELPER_TLH
#define _USE_RUNTIME_OBJECTMAP

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
// WTL 
#define _ATL_NO_MSIMG
#define _ATL_NO_OPENGL

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Bibliotheken
#if defined(_DEBUG)
#pragma comment(lib, "ixtwtld.lib")
#pragma comment(lib, "ospace5d.lib")
#else
#pragma comment(lib, "ixtwtlr.lib")
#pragma comment(lib, "ospace5r.lib")
#endif // defined(_DEBUG

#endif // !defined(_STATISTCONFIG_H__CF461D84_EE47_11D2_9BE4_BAF620524153__INCLUDED_)
