// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/21/1998 08:48:50 PM
//
// @doc
// @module OleAutoConfig.h | Konfigurationskonstanten für OleAuto

#if !defined(_OLEAUTOCONFIG_H__02F179B5_813F_11D2_9EF6_006008447800__INCLUDED_)
#define _OLEAUTOCONFIG_H__02F179B5_813F_11D2_9EF6_006008447800__INCLUDED_

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

//#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#define USE_DLIB
#define USE_DLIB_SCOPE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// die folgende Definition reinnehmen, wenn alle Container mit der klassischen
// Containr.dll realisiert werden sollen
//#define _USE_CLASSIC_CONTAINERS

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungskonstanten
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__

#define _USE_NEWVISINFO
#define _SUPPORT_QUERYDEFS

///////////////////////////////////////////////////////////////////////////////
// BasicScript support
#define EBWIN32

#endif // !defined(_OLEAUTOCONFIG_H__02F179B5_813F_11D2_9EF6_006008447800__INCLUDED_)
