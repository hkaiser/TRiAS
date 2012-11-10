// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 03.02.2002 19:03:37 
//
// @doc
// @module BasicFunctions.h | Declaration of the <c CBasicFunctions> class

#if !defined(_BASICFUNCTIONS_H__EE7D622C_405E_4D01_BD46_DD52231F44DE__INCLUDED_)
#define _BASICFUNCTIONS_H__EE7D622C_405E_4D01_BD46_DD52231F44DE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// die elementarsten aller Elementarfunktionen
HRESULT PunktLage (double x, double y, double* pX, double* pY, long lCnt, 
	bool& bInner);
int TurnDirection (double x1, double y1, double x2, double y2, double x3,
	double y3);
bool Intersection (double x11, double y11, double x21, double y21, double x12,
	double y12, double x22, double y22);
bool IsPointOnStraight (double x, double y, double x1, double y1, double x2, 
	double y2);

} // namespace trias_wmgeometry 

#endif // !defined(_BASICFUNCTIONS_H__EE7D622C_405E_4D01_BD46_DD52231F44DE__INCLUDED_)
