// This is -*- C++ -*-
// $Id: PolynomialRegression.cpp,v 1.2 1999/03/16 18:28:54 alstrup Exp $

/* PolynomialRegression.cpp
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
#include "gala.h"
#include "PolynomialRegression.h"

PolynomialRegression::PolynomialRegression() : degree_(0), coeff_(0)
{ }

PolynomialRegression::PolynomialRegression(const RealSet& x,
					   const RealSet& y,
					   unsigned d) :
  degree_(0), coeff_(0)
{
  model(x,y,d);
}

PolynomialRegression::~PolynomialRegression()
{
  delete [] coeff_;
}

void
PolynomialRegression::model(const RealSet& x,
			    const RealSet& y,
			    unsigned degree)
{
  degree_ = degree;
  delete [] coeff_;
  coeff_ = new double[degree_+1];

  x_ = x;
  y_ = y;
  residuals_.clear();

  GVec v(degree_+1);
  for(size_t i=0; i<x_.size(); ++i) {
    double xx = x_.data(i);
    double yy = y_.data(i);
    double q = 1.0;
    for(size_t j=0; j<=degree_; ++j) {
      v[j] += q * yy;
      q *= xx;
    }
  }

  GMat M(degree_+1, degree_+1);
  for(size_t k=0; k<x_.size(); ++k) {
    double xk = x_.data(k);
    double xki = 1;
    for(size_t i=0; i<=degree_; ++i) {
      double xkij = xki;
      for(size_t j=0; j<=degree_; ++j) {
	M(i,j) += xkij;
	xkij *= xk;
      }
      xki *= xk;
    }
  }
  M.invert();

  GVec b = M(v);
  for(size_t i=0; i<=degree_; ++i)
    coeff_[i] = b[i];

  const double* d = x_.data();
  for(size_t i=0; i<x_.size(); ++i)
    residuals_.add(predict(d[i]));
}
  


// $Id: PolynomialRegression.cpp,v 1.2 1999/03/16 18:28:54 alstrup Exp $
