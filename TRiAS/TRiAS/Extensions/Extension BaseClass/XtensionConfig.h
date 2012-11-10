// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/22/1998 11:30:55 AM
//
// @doc
// @module XtensionConfig.h | Konfigurationskonstanten für XtensionLibrary

#if !defined(_XTENSIONCONFIG_H__02F179BD_813F_11D2_9EF6_006008447800__INCLUDED_)
#define _XTENSIONCONFIG_H__02F179BD_813F_11D2_9EF6_006008447800__INCLUDED_

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
#define ATL_NO_NAMESPACE			// ... aber ohne namespace

#if _MSC_VER < 1300
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#endif // _MSC_VER < 1300

//#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungs
#define __XT
#define __DEXPROCS
#define __XTENSNDLL__

#endif // !defined(_XTENSIONCONFIG_H__02F179BD_813F_11D2_9EF6_006008447800__INCLUDED_)
