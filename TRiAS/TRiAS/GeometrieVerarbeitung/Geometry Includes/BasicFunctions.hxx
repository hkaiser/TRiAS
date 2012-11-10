// Grundlegende Funktionen (mit double-Parametern), die für double-, KoOrd- und CoOrd-Parameter
// verwendet werden können
// File: BasicFunctions.hxx



#ifndef _BASICFUNCTIONS_HXX_
#define _BASICFUNCTIONS_HXX_



_GEOMETR_ENTRY HRESULT PunktLage (double x, double y, double* pX, double* pY, long lCnt, bool& bInner);

_GEOMETR_ENTRY int TurnDirection (double x1, double y1, double x2, double y2, double x3,
								  double y3);

_GEOMETR_ENTRY bool Intersection (double x11, double y11, double x21, double y21, double x12,
								  double y12, double x22, double y22);

bool IsPointOnStraight (double x, double y, double x1, double y1, double x2, double y2);

#endif //_BASICFUNCTIONS_HXX_
