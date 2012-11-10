// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/25/1998 07:33:56 PM
//
// @doc
// @module TRiAS03Config.h | Konfigurationskonstanten für TRiAS03

#if !defined(_TRIAS03CONFIG_H__78227405_6C18_11D2_9EE5_006008447800__INCLUDED_)
#define _TRIAS03CONFIG_H__78227405_6C18_11D2_9EE5_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define EBWIN32
#define _WTL_NO_AUTOMATIC_NAMESPACE

#define __TRIAS03DLL__
#define _USE_LEGACY_CODE
#define _KOORD_ISDOUBLE

//#define NOMINMAX
#define __CV__
#define __XT
#define __DEXPROCS
//#define MSWIND
#define DLL
#define MSCC8

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#define USE_DLIB					// Dump/Trace support aus d_lib verwenden

// track memory leaks
#define _CRTDBG_MAP_ALLOC

// evtl. Objekte global zählen
#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT

#endif // _DEBUG

//#if _TRiAS_VER < 0x0300
//#define _ATL_TRIAS_REGISTER
//#define _TRIAS_OLDIMPLEMENTATION2
//#endif // _TRiAS_VER < 0x0300

#define _USE_NEWVISINFO

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften sollen registriert werden (auch in *.rc beachten)
//#define _REGISTER_OBJECT_PROPERTIES

///////////////////////////////////////////////////////////////////////////////
// jetzt sind (Begleit-)Relationen wieder implementiert: #HK001218
#define _TRIAS_HAS_RELATIONS

#endif // !defined(_TRIAS03CONFIG_H__78227405_6C18_11D2_9EE5_006008447800__INCLUDED_)
