// @doc
// @module QueryDefConfig.h | Konfigurationskonstanten für Xtension

#if !defined(_QUERYDEFCONFIG_H__1BF01AF3_33CF_11D3_94FA_0080C786297B__INCLUDED_)
#define _QUERYDEFCONFIG_H__1BF01AF3_33CF_11D3_94FA_0080C786297B__INCLUDED_

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

#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#define _ATLX_DEBUG_OBJECTCOUNT
#endif // _DEBUG

// einiges nicht aus helper.tlb übernehmen
#define _EXCLUDE_IPARSE_ETC_FROM_HELPER_TLH

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn 'einfache' Fehlerbehandlung gebraucht wird
//#define _USE_NEW_ERRORHANDLING

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die gespeicherte Streams nicht optional
// komprimiert werden sollen/können
#define _USE_STREAMCOMPRESSION

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

#endif // !defined(_QUERYDEFCONFIG_H__1BF01AF3_33CF_11D3_94FA_0080C786297B__INCLUDED_)
