// This is -*- C++ -*-
// $Id: PolynomialRegression.h,v 1.2 1999/03/16 18:28:55 alstrup Exp $

/* PolynomialRegression.h
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


#ifndef _INC_POLYNOMIALREGRESSION_H
#define _INC_POLYNOMIALREGRESSION_H

#include "RealSet.h"

class PolynomialRegression {
public:
  PolynomialRegression();
  PolynomialRegression(const RealSet& indep_var,
		       const RealSet& dep_var,
		       unsigned degree);

  ~PolynomialRegression();

  void model(const RealSet& indep_var,
	     const RealSet& dep_var,
	     unsigned degree);

  RealSet residuals() { return residuals_; }

  unsigned degree() const { return degree_; }
  double coefficient(unsigned i) const { 
    return coeff_ && i <= degree_ ? coeff_[i] : 0;
  }

  double predict(double x) const {
    unsigned i = degree_;
    double y = coeff_[i];
    while (i>0) y = y*x + coeff_[--i];
    return y;
  }

private:
  unsigned degree_;
  double* coeff_;
  RealSet x_, y_, residuals_;
};

#endif // _INC_POLYNOMIALREGRESSION_H

// $Id: PolynomialRegression.h,v 1.2 1999/03/16 18:28:55 alstrup Exp $
