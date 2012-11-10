// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/22/1998 08:54:17 AM
//
// @doc
// @module TRiASConfig.h | Konfigurationskonstanten f¸r TRiASÆ

#if !defined(_TRIASCONFIG_H__21005237_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _TRIASCONFIG_H__21005237_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// verschiedene Varianten um 'Win32' bekannt zu machen... #AK981029
#if defined(_WINDOWS)	// wenn Windows, dann Win32...
#if !defined(WIN32)
#define WIN32
#endif
#if !defined(_WIN32)
#define _WIN32
#endif
#if !defined(_WIN32_)
#define _WIN32_
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
// Systemkonfigurationen
#define STRICT

#if !defined(_WIN32_IE)
#if _MSC_VER <= 1100
#define _WIN32_IE 0x0300		// 'alte' CommCtrl-Strukturen verwenden
#else
#define _WIN32_IE 0x0501		// 'neue' CommCtrl-Strukturen verwenden
#endif // _MSC_VER <= 1100
#endif // _WIN32_IE

#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0400
#endif // _WIN32_WINNT

///////////////////////////////////////////////////////////////////////////////
// ATL-Konfigurationen
#if defined(__ATL_USED__)

#if _MSC_VER < 1100
#define __ATL_11_USED__
#endif // _MSC_VER < 1100
#if _MSC_VER >= 1100
#define __ATL_20_USED__
#endif // _MSC_VER >= 1100

#define ATL_NO_NAMESPACE
#define QI_EXCEPTION
#define _ATL_EXCEPTIONS		// #HK990711

// Standardm‰ﬂig alle ATL-Objekte als ApartmentObjekte anlegen
#if !defined(_ATL_SINGLE_THREADED) && !defined(_ATL_APARTMENT_THREADED) && !defined(_ATL_FREE_THREADED)
#define _ATL_APARTMENT_THREADED	
#endif // !defined(_ATL_SINGLE_THREADED) && !defined(_ATL_APARTMENT_THREADED) && !defined(_ATL_FREE_THREADED)

#endif // __ATL_USED__

///////////////////////////////////////////////////////////////////////////////
// OSpaceSTL-Konfigurationen
#if defined(__OSPACESTL_USED__)

#define OS_WIN_95
#define OS_ALTERNATIVE_STRING_NAMES
#define OS_MULTI_THREADED
#define OS_NO_STREAM_SUPPORT
#define OS_NO_ALLOCATORS
#define OS_STL_ASSERT

#if defined(_DEBUG)
//#define OS_STL_ASSERT_ALLOCATORS
#endif // _DEBUG

#endif // __OSPACESTL_USED__

// evtl. gleich noch GC einbinden
#if defined(_USE_BOEHM_GC)
#include <GC/GCConfig.h>
#endif // defined(_USE_BOEHM_GC)

#endif // !defined(_TRIASCONFIG_H__21005237_6792_11D2_9EDE_006008447800__INCLUDED_)
