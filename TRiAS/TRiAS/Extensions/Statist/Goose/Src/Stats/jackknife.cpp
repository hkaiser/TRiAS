// This is -*- C++ -*-
// $Id: jackknife.cpp,v 1.2 1999/03/16 18:29:05 alstrup Exp $

/* jackknife.cpp
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
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
#include "jackknife.h"

RealSet
jackknife_mean(const RealSet& ds)
{
  if (ds.size() < 2) return RealSet();

  RealSet jack;
  jack.reserve(ds.size());
  
  double Nm1 = ds.size()-1;
  for(size_t i=0; i<ds.size(); ++i)
    jack.add((ds.sum() - ds.data(i))/Nm1);

  return jack;
}

/*
  In general, doing this sort of thing is a bad idea... but a highly
  optimized version is included here for experimental purposes, and for
  the sheer pathology of the jackknife in this sort of non-smooth
  situation.
*/
RealSet
jackknife_median(const RealSet& ds)
{
  if (ds.size() < 2) return RealSet();
  const size_t N = ds.size();
  RealSet jack;
  jack.reserve(N);

  if (N % 2 == 0 /* even */) {
    double m1 = ds.sorted_data(N/2);
    double m2 = ds.sorted_data(N/2-1);
    for(size_t i=0; i<N/2; ++i)
      jack.add(m1);
    for(size_t i=0; i<N/2; ++i)
      jack.add(m2);
  } else {
    double m1 = 0.5*(ds.sorted_data(N/2) + ds.sorted_data(N/2+1));
    double m2 = 0.5*(ds.sorted_data(N/2-1) + ds.sorted_data(N/2+1));
    double m3 = 0.5*(ds.sorted_data(N/2-1) + ds.sorted_data(N/2));
    for(size_t i=0; i<N/2; ++i)
      jack.add(m1);
    jack.add(m2);
    for(size_t i=0; i<N/2; ++i)
      jack.add(m3);
  }

  return jack;
}

RealSet
jackknife_sdev(const RealSet& ds)
{
  if (ds.size() < 2) return RealSet();
  RealSet jack;
  jack.reserve(ds.size());

  const double sum = ds.sum();
  const double sumsq = ds.var()*ds.size();
  const size_t N = ds.size();

  for(size_t i=0; i<ds.size(); ++i) {
    double x = ds.data(i);
    double new_sumsq = sumsq - (x-sum/N)*(x-(sum-x)/(N-1));
    jack.add(sqrt(new_sumsq/(N-1)));
  }

  return jack;
}

// $Id: jackknife.cpp,v 1.2 1999/03/16 18:29:05 alstrup Exp $
