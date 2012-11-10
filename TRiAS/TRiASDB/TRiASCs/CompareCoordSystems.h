// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 12:55:35 
//
// @doc
// @module CompareCoordSystems.h | Vergleichen zweier Koordinatensysteme

#if !defined(_COMPARECOORDSYSTEMS_H__4A651B6F_5788_49C1_828A_080468667BC8__INCLUDED_)
#define _COMPARECOORDSYSTEMS_H__4A651B6F_5788_49C1_828A_080468667BC8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

HRESULT EqualCoordSystems (ITRiASCS *pICS1, ITRiASCS *pICS2);
HRESULT EqualDatum (ITRiASCS *pICS1, ITRiASCS *pICS2);

#endif // !defined(_COMPARECOORDSYSTEMS_H__4A651B6F_5788_49C1_828A_080468667BC8__INCLUDED_)
