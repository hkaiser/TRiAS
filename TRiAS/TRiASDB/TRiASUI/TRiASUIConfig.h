// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/24/1998 07:49:26 PM
//
// @doc
// @module TRiASUIConfig.h | Konfigurationskonstanten für TRiASUI

#if !defined(_TRIASUICONFIG_H__B30EE9E5_6ABB_11D2_9EE3_006008447800__INCLUDED_)
#define _TRIASUICONFIG_H__B30EE9E5_6ABB_11D2_9EE3_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
#define _MERGE_PROXYSTUB
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __STL_OSPACE5__

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#endif // _DEBUG

#endif // !defined(_TRIASUICONFIG_H__B30EE9E5_6ABB_11D2_9EE3_006008447800__INCLUDED_)
