// This is -*- C++ -*-
// $Id: normal.cpp,v 1.3 1999/03/16 18:29:09 alstrup Exp $

/* normal.cpp
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
#include <math.h>
#include <specfns.h>
#include "descriptive.h"
#include "normal.h"

ConfInt
ci_mean(const RealSet& ds, double c)
{
  double m = ds.mean();
  double se = ds.sdevs() / sqrt(ds.size());
  double t_val = inv_students_cdf(ds.size()-1, (1+c)/2);

  ConfInt ci;
  ci.set_confidence(c);
  ci.set_by_error(m, se*t_val);
  return ci;
}

ConfInt
ci_diff_mean(const RealSet& ds1, const RealSet& ds2, double c)
{
  double m1 = ds1.mean();
  double m2 = ds2.mean();
  double pv = goose_pooled_var(ds1,ds2);
  double t_val = inv_students_cdf(ds1.size()+ds2.size()-2, (1+c)/2);

  ConfInt ci;
  ci.set_confidence(c);
  ci.set_by_error(m1-m2, sqrt(pv*(1.0/ds1.size() + 1.0/ds2.size())) * t_val);
  return ci;
}


// $Id: normal.cpp,v 1.3 1999/03/16 18:29:09 alstrup Exp $
