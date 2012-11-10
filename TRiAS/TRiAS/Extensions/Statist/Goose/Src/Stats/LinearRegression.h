// This is -*- C++ -*-
// $Id: LinearRegression.h,v 1.3 1999/03/31 14:45:47 trow Exp $

/* 
 * LinearRegression.h
 *
 * Copyright (C) 1998, 1999 EMC Capital Management, Inc.
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

#ifndef _INC_LINEARREGRESSION_H
#define _INC_LINEARREGRESSION_H

#include "RealSet.h"
#include "ConfInt.h"

class LinearRegression {
public:
  LinearRegression() : slope_(0), intercept_(0), corr_(0) { }
  LinearRegression(const RealSet& indep_var, const RealSet& dep_var) {
    model(indep_var, dep_var);
  }

  void model(const RealSet& indep_var, const RealSet& dep_var);
  RealSet residuals() { return residuals_; }

  double slope() const { return slope_; }
  double intercept() const { return intercept_; }
  double correlation() const { return corr_; }
  double R() const { return corr_; }
  double R_sq() const { return corr_*corr_; }
  double predict(double x) const { return slope_ * x + intercept_; }

  double sdev_residuals() const { return sdev_residuals_; }
  double sdev_slope() const { return sdev_slope_; }
  double sdev_intercept() const { return sdev_intercept_; }
  double sdev_prediction(double x) const;

  ConfInt slope_interval(double conf) const;
  ConfInt intercept_interval(double conf) const;
  ConfInt prediction_interval(double x, double conf) const;
  ConfInt correlation_interval(double conf) const;

  double residual(size_t i) const { return residuals_.data(i); }
  double leverage(size_t i) const;
  double standardized_residual(size_t i) const {
    return residual(i) / (sdev_residuals_ * sqrt(1-leverage(i)));
  }

  double DFBETAS_slope(size_t i) const;
  double DFBETAS_intercept(size_t i) const;
  void DFBETAS(size_t i, double& slope, double& inter) const;
  double DFFITS(size_t i) const;

  // The fast versions use the std dev of the residuals of the original
  // model, rather than that of the new model with an observation omitted.
  // This means that we can calculate them in constant time, rather than
  // in O(N) time.
  double DFBETAS_slope_fast(size_t i) const;
  double DFBETAS_intercept_fast(size_t i) const;
  void DFBETAS_fast(size_t i, double& slope, double& inter) const;
  double DFFITS_fast(size_t i) const;

  double cooks_D(size_t) const;

  double independence_t() const;
  double independence_p() const;

private:
  void omit_and_model(size_t i, double& slope, double& intercept) const;
  void omit_and_model(size_t i, double& slope, double& intercept,
		      double& res_sdev) const;

  double covarXY_, slope_, intercept_, corr_;
  RealSet x_, y_, residuals_;
  size_t N_;
  double sdev_residuals_, sdev_slope_, sdev_intercept_, sdev_predict_;
};

#endif // _INC_LINEARREGRESSION_H

// $Id: LinearRegression.h,v 1.3 1999/03/31 14:45:47 trow Exp $
