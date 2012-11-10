// This is -*- C++ -*-
// $Id: kolmogorov_smirnov.cpp,v 1.2 1999/07/15 17:44:38 trow Exp $

/* kolmogorov_smirnov.cpp
 *
 * Copyright (C) 1998, 1999 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@emccta.com>.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <iostream>
#include <math.h>
#include <specfns_protos.h>
#include "kolmogorov_smirnov.h"

// An implementation of the exact "path-counting" algorithm.
//
// *** This is broken ***
//
double
kolmogorov_smirnov_2sample_exact(unsigned m, unsigned n, double c)
{
  const unsigned N=(m+1)*(n+1)+1;

  double* A = new double[N];

  double a;
  for(unsigned u=0; u<=m; ++u)
    for(unsigned v=0; v<=n; ++v) {
      a = (u == 0 && v == 0) ? 1 : 0;
      double cc = fabs(u/(double)m - v/(double)n);
      if (cc < c) {
	if (u>0) a += A[(u-1)*(n+1)+v];
	if (v>0) a += A[u*(n+1)+(v-1)];
      }
      A[u*(n+1)+v] = a;
    }
  delete [] A;

  return exp(log(a) - log_choose(m+n,m));
}


// $Id: kolmogorov_smirnov.cpp,v 1.2 1999/07/15 17:44:38 trow Exp $
