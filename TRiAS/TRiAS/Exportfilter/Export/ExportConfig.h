// @doc
// @module ExportConfig.h | Konfigurationskonstanten für Xtension

#if !defined(_EXPORTCONFIG_H__BD1B0ED3_FFAF_11D2_94C3_0080C786297B__INCLUDED_)
#define _EXPORTCONFIG_H__BD1B0ED3_FFAF_11D2_94C3_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma HDR_ON()

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __MFC__


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
// lokale defines
#define _USE_CHECKMARK_OBJPROPTREE

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Bibliotheken
#if defined(_DEBUG)
#pragma comment(lib, "ixtmad50.lib")
#pragma comment(lib, "ospace5d.lib")
#else
#pragma comment(lib, "ixtmar50.lib")
#pragma comment(lib, "ospace5r.lib")
#endif // defined(_DEBUG

#pragma HDR_OFF()

#endif // !defined(_EXPORTCONFIG_H__BD1B0ED3_FFAF_11D2_94C3_0080C786297B__INCLUDED_)
