// This is -*- C++ -*-
// $Id: fit.cpp,v 1.2 1999/03/16 18:29:02 alstrup Exp $

/* fit.cpp
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
#include <specfns.h>
#include "fit.h"

void
GoodnessOfFit::add_category(unsigned obs, double ex)
{
  double q = obs-ex;
  chi2_ += q*q/ex;
  ++cat_;
}

double
GoodnessOfFit::p_value() const
{
  return chisq_cdf(df(), chi_sq());
}


// $Id: fit.cpp,v 1.2 1999/03/16 18:29:02 alstrup Exp $
