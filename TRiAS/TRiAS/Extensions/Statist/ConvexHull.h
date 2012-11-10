// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 11:38:11 
//
// @doc
// @module ConvexHull.h | Declaration of the <c CConvexHull> class

#if !defined(_CONVEXHULL_H__5093DF2B_D052_4C7A_BB7E_5C42BF360E4A__INCLUDED_)
#define _CONVEXHULL_H__5093DF2B_D052_4C7A_BB7E_5C42BF360E4A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Funktion berechnet konvexe Hülle der übergebenen Koordinaten
long ConvexHull2D(double **P, long n);

#endif // !defined(_CONVEXHULL_H__5093DF2B_D052_4C7A_BB7E_5C42BF360E4A__INCLUDED_)
