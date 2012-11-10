// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 04.11.2000 12:33:36 
//
// @doc
// @module MapMgrImpl.h | Declaration of the <c CMapMgrImpl> class

#if !defined(__MAPMGR_IMPL_H__03896A00_1B40_11d2_8F7D_0060085FC1CE)
#define __MAPMGR_IMPL_H__03896A00_1B40_11d2_8F7D_0060085FC1CE

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "MapMgr.h"

#import "tlb/MapCtrl.tlb" raw_interfaces_only raw_dispinterfaces no_implementation no_namespace	named_guids

typedef	CComQIPtr<ITopoMap,&IID_ITopoMap>	MAPPOINTER;

#endif // __MAPMGR_IMPL_H__03896A00_1B40_11d2_8F7D_0060085FC1CE
