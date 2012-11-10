// @doc
// @module PropActSubSeqConfig.h | Konfigurationskonstanten für Xtension

#if !defined(_PROPACTSUBSEQCONFIG_H__83728723_01F3_11D3_94CB_0080C786297B__INCLUDED_)
#define _PROPACTSUBSEQCONFIG_H__83728723_01F3_11D3_94CB_0080C786297B__INCLUDED_

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
#endif // _DEBUG

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

#endif // !defined(_PROPACTSUBSEQCONFIG_H__83728723_01F3_11D3_94CB_0080C786297B__INCLUDED_)
