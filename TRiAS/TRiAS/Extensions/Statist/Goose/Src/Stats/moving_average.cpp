// This is -*- C++ -*-
// $Id: moving_average.cpp,v 1.3 1999/03/16 18:29:07 alstrup Exp $

/* moving_average.cpp
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
#include "moving_average.h"

RealSet
goose_moving_average(const RealSet& rs, size_t N, bool suppress)
{
  RealSet ma;
  double* buffer = new double[N];
  size_t i = 0;
  bool full = false;
  double sum = 0;
  const double* d = rs.data();
  for(size_t j=0; j<rs.size(); ++j) {

    if (full)
      sum -= buffer[i];
    sum += (buffer[i] = d[j]);

    ++i;
    if (i == N) {
      i = 0;
      full = true;
    }

    if (full) 
      ma.add(sum / N);
    else if (!suppress)
      ma.add(sum / i);
  }
  
  delete [] buffer;
  return ma;
}

RealSet
goose_exponential_moving_average(const RealSet& rs, double a)
{
  RealSet ema;
  const double* d = rs.data();
  if (rs.size()) {
    double prev = d[0];
    ema.add(prev);
    for(size_t i=1; i<rs.size(); ++i)
      ema.add(prev = a*prev + (1-a)*d[i]);
  }
  return ema;
}


// $Id: moving_average.cpp,v 1.3 1999/03/16 18:29:07 alstrup Exp $
