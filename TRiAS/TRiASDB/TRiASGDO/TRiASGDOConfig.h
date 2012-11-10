// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.02.2000 22:38:14 
//
// @doc
// @module TRiASGDOConfig.h | Konfigurationskonstanten für TRiASGDO

#if !defined(_TRIASGDOCONFIG_H__EC49BC4B_0C00_477B_8A7D_FC32A18B8976__INCLUDED_)
#define _TRIASGDOCONFIG_H__EC49BC4B_0C00_477B_8A7D_FC32A18B8976__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define	__ATL_USED__
#define __STL_OSPACE5__
#define NOMINMAX

// die MFC gibt es nicht mehr in TRiASGDO
#define	AFX_MANAGE_STATE(func)

#if defined(_DEBUG)

#define	_ASSERT_ON_THROW_FAILED_HRESULT	// THROW_FAILED_HRESULT liefert Assertion
#define _ATLX_ASSERT_ON_FAILURE

///////////////////////////////////////////////////////////////////////////////
// evtl. ausführliches AddRef/Release Tracking zuschalten
//#define _ATLX_DEBUG_REFCOUNT_WALKSTACK
//#define _USE_IMAGE_HELP					// dabei MSSymbols verwenden

///////////////////////////////////////////////////////////////////////////////
// evtl. Objekte global zählen
//#define _ATLX_DEBUG_REFCOUNT
#define _ATLX_DEBUG_OBJECTCOUNT
//#define _DUMP_PENDING_OBJECTS

///////////////////////////////////////////////////////////////////////////////
// Interfaces verfolgen
//#define _ATL_DEBUG_INTERFACES
//#define _ATL_DEBUG_QI

///////////////////////////////////////////////////////////////////////////////
// evtl. Ein/Ausgang der Interfaces verfolgen
//#define _DEBUG_FUNCENTRY

///////////////////////////////////////////////////////////////////////////////
// spezielle DumpLib (d_lib) zuschalten
//#define USE_DLIB

#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die keine ClassFactories im cache 
// gehalten werden sollen (s. CLASSFACTORY_CACHE_BEGIN etc.)
#define _USE_CLASSFACTORY_CACHE

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die Standard-Speicherverwaltung verwendet 
// werden soll
#define _USE_ONESIZEHEAP

#endif // !defined(_TRIASGDOCONFIG_H__EC49BC4B_0C00_477B_8A7D_FC32A18B8976__INCLUDED_)
