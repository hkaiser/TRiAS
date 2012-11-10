// $Header: $
// Copyright© 1999 TRiAS GmbH, All rights reserved
// Created: 11/22/1998 01:20:47 PM
//
// @doc
// @module GeometryConfig.h | Konfigurationskonstanten für GeoDLL

#if !defined(_GEOMETRYCONFIG_H__CB8A8F87_8195_11D2_9EF6_006008447800__INCLUDED_)
#define _GEOMETRYCONFIG_H__CB8A8F87_8195_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define ATL_NO_NAMESPACE			// ...aber ohne namespace

#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __CV__

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungskonstanten
#define DLL
#define __XT
#define __DEXPROCS
#define __XTENSNDLL__

///////////////////////////////////////////////////////////////////////////////
// spezifische Konstanten des GeoDLL-Modules
#define __GEOMETRDLL__
#define _NO_XTENSIONSITE_INTERFACE

#endif // !defined(_GEOMETRYCONFIG_H__CB8A8F87_8195_11D2_9EF6_006008447800__INCLUDED_)
