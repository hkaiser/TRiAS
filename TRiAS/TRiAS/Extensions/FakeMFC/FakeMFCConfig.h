// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/22/1998 01:11:33 PM
//
// @doc
// @module FakeMFCConfig.h | Konfigurationskonstanten für FakeMFC

#if !defined(_FAKEMFCCONFIG_H__21005239_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _FAKEMFCCONFIG_H__21005239_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __MFC__						// MFC wird verwendet
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define OS_NO_MIN_MAX

//#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Objective Toolkit
#define _SECDLL
#define _USE_SEC_CLASSES
#define _USE_SEC_VER0600

//#define _SEC_USE_TABWND
//#define _SEC_SUBCLASS_ORWND

//#define _USE_WHEELMOUSE
#define _USE_TOOLBARCUSTOMIZE
#define _USE_PRINT_PREVIEW
#define _USE_DRAG_N_DROP

///////////////////////////////////////////////////////////////////////////////
// TRiAS-Erweitungs-Spezifika
#define __XT
#define __DEXPROCS
#define __XTNSNDLL__

///////////////////////////////////////////////////////////////////////////////
// neue VisInfo-Strukturen verwenden
#define _USE_NEWVISINFO

///////////////////////////////////////////////////////////////////////////////
// Sollte irgend wann noch mal Win32s aktuelle werden, dann hilft das Folgende 
// vielleicht weiter ;-)
// #define _USE_WIN32S_CODE

#endif // !defined(_FAKEMFCCONFIG_H__21005239_6792_11D2_9EDE_006008447800__INCLUDED_)

