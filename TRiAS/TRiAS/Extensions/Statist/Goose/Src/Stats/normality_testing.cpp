// This is -*- C++ -*-
// $Id: normality_testing.cpp,v 1.3 1999/03/31 21:21:57 trow Exp $

/* normality_testing.cpp
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
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

#include <config.h>
#include <specfns.h>
#include <RealSet.h>
#include "normality_testing.h"

/*
  This is supposed to be a good approximation to w for 7 <= N <= 2000
 */
double
shapiro_wilks_royden_approx(const RealSet& rs)
{
  const size_t N = rs.size();
  const double* d = rs.sorted_data();

  size_t NN = N<=20 ? N-1 : N;
  double g = exp(log_gamma(0.5*(NN+1)) - log(sqrt(2)) - log_gamma(NN/2.0+1));

  double run_tot = 0;
  double run_a_sq = 0;
  double continuity = N%2 ? 1.0 : 0.5;
  for(size_t i=1; i<N-1; ++i) {
    double a = 2 * inv_normal_cdf((i+continuity)/(double)N);
    run_tot += a * d[i];
    run_a_sq += a*a;
  }
  
  double ax = sqrt( g/(1-2*g) * run_a_sq);
  run_tot += ax * (d[N-1] - d[0]);
  run_a_sq += 2*ax*ax;

  return (run_tot*run_tot) / (run_a_sq * (N-1) * rs.vars());
}




// $Id: normality_testing.cpp,v 1.3 1999/03/31 21:21:57 trow Exp $
