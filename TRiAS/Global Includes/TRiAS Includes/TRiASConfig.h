// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/22/1998 08:54:17 AM
//
// @doc
// @module TRiASConfig.h | Konfigurationskonstanten für TRiAS®

#if !defined(_TRIASCONFIG_H__21005237_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _TRIASCONFIG_H__21005237_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// TRiAS Version (build control)
#define _TRiAS		1			// TRiAS
#if !defined(_TRiAS_VER)
// nur hier definieren, wenns noch nicht anderweitig vorgegeben ist
#define _TRiAS_VER	0x0510		// TRiAS Version 4.00 (#HK001130)
								// TRiAS Version 4.10 (#HK010307)
								// TRiAS Version 4.20 (#HK010704)
								// TRiAS Version 5.00 (#HK020226)
								// TRiAS Version 5.10 (#HK031213)
#endif // !defined(_TRiAS_VER)

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
#elif _MSC_VER >= 1300
#define __ATL_70_USED__
#elif _MSC_VER >= 1100
#define __ATL_20_USED__
#endif // _MSC_VER >= 1100

#define ATL_NO_NAMESPACE
#define QI_EXCEPTION
#define _ATL_EXCEPTIONS		// #HK990711

// Standardmäßig alle ATL-Objekte als ApartmentObjekte anlegen
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

#else
#if !defined(OS_USE_ALTERNATE_STD) && _MSC_VER >= 1300
#define OS_USE_ALTERNATE_STD					// ggf. StandardSTL verwenden
#endif // !defined(OS_USE_ALTERNATE_STD) && _MSC_VER >= 1300

#define OS_WIN_95
#define OS_ALTERNATIVE_STRING_NAMES
#define OS_MULTI_THREADED
#define OS_NO_STREAM_SUPPORT
#define OS_NO_ALLOCATORS
#define OS_STL_ASSERT

#endif // __OSPACESTL_USED__

///////////////////////////////////////////////////////////////////////////////
// undefine to use throw(...) decls in smartif.h
// #define _USE_THROW_DECLS						// #HK000717

// evtl. gleich noch GC einbinden
#if defined(_USE_BOEHM_GC)
#include <GC/GCConfig.h>
#endif // defined(_USE_BOEHM_GC)

#if !defined(_NO_AGGRESSIVE_OPTIMIZATIONS)		// #HK000201
#include <AggressiveOptimize.h>
#endif // !defined(_NO_AGGRESSIVE_OPTIMIZATIONS)

///////////////////////////////////////////////////////////////////////////////
// verwendete Registrykeys (#HK000923)
#if _TRiAS_VER < 0x0300
#define REG_COMPANY_KEY	TEXT("fez")
#define REG_PRODUCT_KEY TEXT("TRiAS")
#elif _TRiAS_VER < 0x0400
#define REG_COMPANY_KEY	TEXT("TRiAS")
#define REG_PRODUCT_KEY TEXT("InterTRiAS")
#else
#define REG_COMPANY_KEY	TEXT("TRiAS")
#define REG_PRODUCT_KEY TEXT("TRiAS")
#endif // _TRiAS_VER

///////////////////////////////////////////////////////////////////////////////
// Geomedia-Geometrie-Typelibraries verwenden
#define _USE_GEOMEDIA_GEOMETRY_TYPELIBS

#endif // !defined(_TRIASCONFIG_H__21005237_6792_11D2_9EDE_006008447800__INCLUDED_)
