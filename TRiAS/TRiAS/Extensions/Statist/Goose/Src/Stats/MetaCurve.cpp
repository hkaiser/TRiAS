// This is -*- C++ -*-
// $Id: MetaCurve.cpp,v 1.2 1999/03/16 18:28:52 alstrup Exp $

/* 
 * MetaCurve.cpp
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
#include <assert.h> // Stop me before I assert() again!
#include <string.h>
#include <math.h>
#include "Exception.h"
#include "MetaCurve.h"

MetaCurve::MetaCurve() : interp_(LINEAR), 
  have_y_min_(false), have_y_max_(false),
  calcbits_(0), y_buffer_(0)
{ }

MetaCurve::~MetaCurve()
{
  delete [] calcbits_;
  delete [] y_buffer_;
}

void
MetaCurve::set_range(double x0, double x1)
{
  x_min_ = x0;
  x_max_ = x1;
}

void
MetaCurve::set_sample_count(unsigned N)
{
  if (N == 0)
    interp_ = NONE;
  else {
    if (N < 2)
      N = 2;

    x_freq_ = (x_max_ - x_min_) / (N-1);

    calcbits_ = new unsigned[N/sizeof(unsigned)+1];
    memset(calcbits_, 0, (N/sizeof(unsigned)+1)*sizeof(unsigned));

    y_buffer_ = new double[N];
  }
  N_ = N;
}

double
MetaCurve::value(double x)
{
  if (interp_ == NONE || y_buffer_ == 0 || x < x_min_ || x_max_ < x) 
    return y_clip(calc(x));

  double y;
  
  double z = (x - x_min_)/x_freq_;
  int zf = (int)floor(z);
  int zc = (int)ceil(z);

  // Take care of the case where we fall directly on a cached point.
  if (zf == zc) {

    if (0 <= zf && zf < (int)N_) {
      if (!have_in_buffer(zf))
	put_in_buffer(zf,calc(x));
      
      y = y_buffer_[zf];
    } else {
      y = calc(x);
    }
   
    return y_clip(y);
  }
    
  double xf = x_min_ + zf * x_freq_;
  double xc = x_min_ + zc * x_freq_;
  double yf, yc;
      
  if (0 <= zf && zf < (int)N_) {
    if (!have_in_buffer(zf))
      put_in_buffer(zf, yf = calc(xf));
    else
      yf = y_buffer_[zf];
  } else {
    yf = calc(xf);
  }
      
  if (0 <= zc && zc < (int)N_) {
    if (!have_in_buffer(zc))
      put_in_buffer(zc, yc = calc(xc));
    else
      yc = y_buffer_[zc];
  } else {
    yc = calc(xc);
  }

  if (interp_ == NEAREST) {
	
    // Because of how we've set this up, both adjacent points get
    // calculated (if not cached), even though we only need one right now.
    // This would be easy to fix, but doesn't really seem worth it...
    y = (x - xf < xc - x) ? yf : yc;
    
  } else if (interp_ == LINEAR) {
    
    y = linear_interp(x, xf,yf, xc,yc);
    
  } else if (interp_ == QUADRATIC) {
	
    int z3 = (z-zf < 0.5 && zf != 0) || zc == (int)N_-1 ? zf-1 : zc+1;
    double x3 = x_min_ + z3 * x_freq_, y3;
    
    if (0 <= z3 && z3 < (int)N_) {
      if (!have_in_buffer(z3))
	put_in_buffer(z3, y3 = calc(x3));
      else
	y3 = y_buffer_[z3];
    } else {
      y3 = calc(x3);
    }
	
    y = quadratic_interp(x, xf,yf, xc,yc, x3,y3);
  } else {
    // Unknown type... just call calc()
    y = calc(x);
  }
  
  return y_clip(y);
}

void
MetaCurve::enhance(size_t q)
{
  if (q == 0) throw Exception("Attempted enhance(0)");
  if (q == 1) return;

  size_t old_N = N_;
  
  unsigned* old_calcbits = calcbits_;
  double* old_y_buffer = y_buffer_;

  set_sample_count(N_ * q);

  for(size_t i=0; i<old_N; ++i) {
    if ((old_calcbits[i/sizeof(unsigned)] & (1 << (i % sizeof(unsigned)))) == 1)
      put_in_buffer(i*q, old_y_buffer[i]);
  }

  delete [] old_calcbits;
  delete [] old_y_buffer;
}

void
MetaCurve::oversampled_dump(ostream& out, size_t n)
{
  for(size_t i=0; i<=n*(N_-1); ++i) {
    double x = x_min_ + i*x_freq_/n;
    out << x << " " << value(x) << endl;
  }
}

double
MetaCurve::linear_interp(double x,
			 double x1, double y1,
			 double x2, double y2) const
{
  return ((x2-x)*y1 + (x-x1)*y2)/(x2-x1);
}

double
MetaCurve::quadratic_interp(double x,
			    double x1, double y1,
			    double x2, double y2,
			    double x3, double y3) const
{
  double div = (x1-x2)*(x1-x3)*(x2-x3);

  double a = x1*(y3-y2) + x2*(y1-y3) + x3*(y2-y1);

  double b = x1*x1*(y2-y3) + x2*x2*(y3-y1) + x3*x3*(y1-y2);

  double c = y1*(x2*x2*x3 - x2*x3*x3) + y2*(x1*x3*x3 - x1*x1*x3)
    + y3*(x1*x1*x2 - x1*x2*x2);

  return ((a*x+b)*x+c)/div;
}





