// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 10:43:21
//
// @doc
// @module ConvexHull.cpp | Implementation of the <c CConvexHull> class

#include "stdafx.h"

#include "ConvexHull.h"

namespace ConvexHull {

// true if points i, j, k counterclockwise
bool CounterClockWise (double **P, long i, long j, long k) 
{
double	a = P[i][0] - P[j][0],
		b = P[i][1] - P[j][1],
		c = P[k][0] - P[j][0],
		d = P[k][1] - P[j][1];

	return (a*d - b*c) <= 0;
}

///////////////////////////////////////////////////////////////////////////////
// Vergleichen zweier Punktkoordinaten
inline int cmpm (long c, const void *A, const void *B) 
{
	_ASSERTE(0 == c || 1 == c);

double v = (*(double **)A)[c] - (*(double **)B)[c];

	if (v > 0) return 1;
	if (v < 0) return -1;
	return 0;
}

int cmpl(const void *a, const void *b) 
{
int iCmp = cmpm(0, a, b);

	if (0 != iCmp)
		return iCmp;
	return cmpm (1, b, a);
}

int cmph(const void *a, const void *b) 
{
	return cmpl(b, a);
}

long make_chain(double **V, int n, int (*cmp)(const void*, const void*)) 
{
long i, j, s = 1;

	qsort(V, n, sizeof(double *), cmp);
	for (i = 2; i < n; i++)
	{
		for (j = s; j >= 1 && CounterClockWise(V, i, j, j - 1); --j)
			;

		s = j + 1;
		swap(V[s], V[i]);
	}
	return s;
}

} // namespace

///////////////////////////////////////////////////////////////////////////////
// Berechnen der Konvexen Hülle der übergebenen Punkte
long ConvexHull2D(double **P, long n)  
{
using namespace ConvexHull;

long u = make_chain(P, n, cmpl);		// make lower hull

	if (!n)
		return 0;

	P[n] = P[0];
	return u + make_chain(P + u, n - u + 1, cmph);	// make upper hull
}

