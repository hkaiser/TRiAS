// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.05.2001 09:05:43 
//
// @doc
// @module InterfaceWrappers.h | Declaration of smart interface classes

#if !defined(_INTERFACEWRAPPERS_H__5499DFDB_3309_4D3D_BB94_3A7C7E050D07__INCLUDED_)
#define _INTERFACEWRAPPERS_H__5499DFDB_3309_4D3D_BB94_3A7C7E050D07__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ConnectionPointContainer)
DefineSmartInterface(SpatialReference);
DefineSmartInterface(TRiASTransformGeometry);

#endif // !defined(_INTERFACEWRAPPERS_H__5499DFDB_3309_4D3D_BB94_3A7C7E050D07__INCLUDED_)
