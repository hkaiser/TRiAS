// This is -*- C++ -*-
// $Id: KernelDE.cpp,v 1.3 1999/03/16 18:28:48 alstrup Exp $

/* KernelDE.cpp
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
#include "constants.h"
#include "Exception.h"
#include "descriptive.h"
#include "KernelDE.h"

KernelDE::KernelDE(const RealSet& ds, double h,
		   size_t N, kernel_t type) :
  ds_(ds), h_(h), type_(type)
{
  if (type_ == Gaussian) {
    double w = goose_range(ds_); 
    // This could be a *lot* smarter
    set_range(ds_.min() - w/2, ds_.max() + w/2);
  } else {
    // All other kernels are zero outside of [-1,1] --- a fact we exploit.
    set_range(ds_.min() - h_, ds_.max() + h_);
  }

  set_y_min(0);
  set_sample_count(N);
  set_interpolation(QUADRATIC); // It wouldn't kill me to offer a choice...
}

double
KernelDE::calc(double x)
{
  if (type_ != Gaussian && (x < ds_.min()-h_ || x > ds_.max()+h_))
    return 0;
  
  double sum=0;
  const double* d = ds_.data();
  size_t N = ds_.size();

  if (type_ == Gaussian) {
    for(size_t i=0; i<N; ++i) {
      double t = x-d[i];
      sum += exp(-t*t/h_);
    }
    sum /= GOOSE_SQRT2PI;
  } else if (type_ == Epanechnikov) {
    for(size_t i=0; i<N; ++i) {
      if (d[i] - h_ <= x && x <= d[i] + h_) {
	double t = (x-d[i])/h_;
	sum += 1 - t*t;
      }
    }
    sum *= 3.0/4.0;
  } else if (type_ == Biweight) {
    for(size_t i=0; i<N; ++i) {
      if (d[i] - h_ <= x && x <= d[i] + h_) {
	double t = (x-d[i])/h_;
	double u = 1 - t*t;
	sum += u*u;
      }
    }
    sum *= 15.0/16.0;
  } else if (type_ == Triweight) {
    for(size_t i=0; i<N; ++i) {
      if (d[i] - h_ <= x && x <= d[i] + h_) {
	double t = (x-d[i])/h_;
	double u = 1 - t*t;
	sum += u*u*u;
      }
    }
    sum *= 35.0/32.0;
  } else if (type_ == Uniform) {
    for(size_t i=0; i<N; ++i) {
      if (d[i] - h_ <= x && x <= d[i] + h_)
	sum += 0.5;
    }
  } else {
    throw Exception("Unknown kernel type");
  }


  return sum / (N*h_);
}


// $Id: KernelDE.cpp,v 1.3 1999/03/16 18:28:48 alstrup Exp $
