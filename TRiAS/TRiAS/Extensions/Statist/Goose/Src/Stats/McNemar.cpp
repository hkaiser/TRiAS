// This is -*- C++ -*-
// $Id: McNemar.cpp,v 1.2 1999/07/19 13:21:47 alstrup Exp $

/* McNemar.cpp
 *
 * Copyright (C) 1999 Sophus Medical Aps
 *
 * Developed by Mikkel Munck Rasmussen <mikkel@sophusmedical.dk>.
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

// Nonparametric statistic utility for calculation of the 
// McNemar change test.

// See "Nonparametric statistics for the Behavioral sciences",
// Sidney Siegel, N. John Castellan, Jr., McGRAW-HILL, ISBN 0-07-100326-6

#include "config.h"
#include "McNemar.h"
#include <cmath>

McNemarResult McNemar(double A, double D) {
  McNemarResult result;

  if ( A + D != 0) {
	  result.X2 = ((A - D) * (A - D)) / (A + D);
	  result.X2c = ((fabs(A - D) - 1) * (fabs(A - D) - 1)) / (A + D);
	  result.p = chisq_cdf(1, result.X2);
	  result.pc = chisq_cdf(1, result.X2c);
  } else {
	  result.X2 = 0;
	  result.X2c = 0;
	  result.p = 0;
	  result.pc = 0;
  }
  return result;
}
