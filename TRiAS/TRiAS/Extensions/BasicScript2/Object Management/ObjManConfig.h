// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/22/1998 01:11:33 PM
//
// @doc
// @module ObjManConfig.h | Konfigurationskonstanten für ObjMan

#if !defined(_OBJMANCONFIG_H__21005239_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _OBJMANCONFIG_H__21005239_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __MFC__
#define __STL_OSPACE5__

#define _USE_LEGACY_CODE			// Code kompatibel mit V2.10 halten

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

#endif // !defined(_OBJMANCONFIG_H__21005239_6792_11D2_9EDE_006008447800__INCLUDED_)

