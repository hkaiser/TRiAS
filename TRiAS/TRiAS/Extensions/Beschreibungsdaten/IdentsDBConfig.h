// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/21/1998 01:28:06 PM
//
// @doc
// @module IdentsDBConfig.h | Konfigurationskonstanten für IdentsDB

#if !defined(_IDENTSDBCONFIG_H__CDAF1B55_7FDB_11D2_9EF6_006008447800__INCLUDED_)
#define _IDENTSDBCONFIG_H__CDAF1B55_7FDB_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __CV__

//#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungskonstanten
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__

#if defined(_DEBUG)	// (yet...)
#define _SUPPORT_QUERYDEFS
#endif // defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// required for Lol support
#define yy_user_config_

#endif // !defined(_IDENTSDBCONFIG_H__CDAF1B55_7FDB_11D2_9EF6_006008447800__INCLUDED_)
