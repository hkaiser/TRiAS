// This is -*- C++ -*-
// $Id: LinearRegression.cpp,v 1.4 1999/03/31 14:45:45 trow Exp $

/* 
 * LinearRegression.cpp
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

#include <config.h>
#include <specfns.h>
#include "Exception.h"
#include "descriptive.h"
#include "LinearRegression.h"

void
LinearRegression::model(const RealSet& x, const RealSet& y)
{
  if (x.size() != y.size())
    throw Exception("Size of datasets does not agree");
  
  if (x.size() < 3)
    throw Exception("Datasets too small (min size=3)");

  x_ = x;
  y_ = y;
  N_ = x.size();

  covarXY_ = goose_covar(x,y);
  slope_ = covarXY_ / x.var();
  intercept_ = y.mean() - slope_ * x.mean();
  corr_ = slope_ * x.sdev() / y.sdev();

  // Calculate residuals
  residuals_.clear();
  residuals_.reserve(N_);
  for(size_t i=0; i<N_; ++i)
    residuals_.add(y.data(i) - predict(x.data(i)));

  /*
    We can't just take the sdevs() of the residuals, since they are not
    independent!  We have to correct for an extra lost degree of freedom.
  */
  sdev_residuals_ = sqrt( N_ * residuals_.var() / (N_-2) );
  sdev_slope_ = sdev_residuals_ / sqrt(N_ * x_.var());
  sdev_intercept_ = sdev_residuals_ * sqrt(goose_rms(x_) / (N_ * x_.var()));
}

double
LinearRegression::sdev_prediction(double x) const
{
  return sdev_residuals_ *
    sqrt(1 + 1.0/N_ + (x-x_.mean())*(x-x_.mean())/(N_ * x_.var()));
}

ConfInt
LinearRegression::slope_interval(double conf) const
{
  double t_val = inv_students_cdf(N_-2, (1+conf)/2);
  ConfInt ci;
  ci.set_by_error(slope(), t_val * sdev_slope(), conf);
  return ci;
}

ConfInt
LinearRegression::intercept_interval(double conf) const
{
  double t_val = inv_students_cdf(N_-2, (1+conf)/2);
  ConfInt ci;
  ci.set_by_error(intercept(), t_val * sdev_intercept(), conf);
  return ci;
}

ConfInt
LinearRegression::prediction_interval(double x, double conf) const
{
  double t_val = inv_students_cdf(N_-2, (1+conf)/2);
  ConfInt ci;
  ci.set_by_error(predict(x), t_val * sdev_prediction(x), conf);
  return ci;
}

ConfInt
LinearRegression::correlation_interval(double conf) const
{
  double r = correlation();
  double z_val = inv_normal_cdf(0, 1, (1+conf)/2);

  double fisher_z = 0.5*(log(1+r)-log(1-r));
  double fisher_z_stderr = 1/sqrt(N_-3);

  double z_lo = fisher_z - z_val * fisher_z_stderr;
  double z_hi = fisher_z + z_val * fisher_z_stderr;

  double r_lo = (exp(2*z_lo)-1)/(exp(2*z_lo)+1);
  double r_hi = (exp(2*z_hi)-1)/(exp(2*z_hi)+1);

  ConfInt ci;
  ci.set(r_lo, r, r_hi, conf);
  return ci;
}

double
LinearRegression::leverage(size_t i) const
{
  double xx = x_.data(i) - x_.mean();
  return 1.0/N_ + xx*xx/(N_*x_.var());
}

double
LinearRegression::DFBETAS_slope(size_t i) const
{
  double oslope, ointer, osdr;
  omit_and_model(i, oslope, ointer, osdr);

  return sqrt(N_*x_.var())*(slope_ - oslope)/osdr;
}

double
LinearRegression::DFBETAS_slope_fast(size_t i) const
{
  double oslope, ointer;
  omit_and_model(i, oslope, ointer);

  return sqrt(N_*x_.var())*(slope_ - oslope)/sdev_residuals_;
}

double
LinearRegression::DFBETAS_intercept(size_t i) const
{
  double oslope, ointer, osdr;
  omit_and_model(i,oslope, ointer, osdr);
  return sqrt(N_*x_.var())*(intercept_ - ointer)/(osdr*goose_rms(x_));
}

double
LinearRegression::DFBETAS_intercept_fast(size_t i) const
{
  double oslope, ointer;
  omit_and_model(i,oslope, ointer);
  return sqrt(N_*x_.var())*
    (intercept_ - ointer)/(sdev_residuals_*goose_rms(x_));
}

void
LinearRegression::DFBETAS(size_t i, double& slope, double& inter) const
{
  double oslope, ointer, osdr;
  omit_and_model(i,oslope, ointer, osdr);
  slope = sqrt(N_*x_.var())*(slope_ - oslope)/osdr;
  inter = sqrt(N_*x_.var())*(intercept_ - ointer)/(osdr * goose_rms(x_));
}

void
LinearRegression::DFBETAS_fast(size_t i, double& slope, double& inter) const
{
  double oslope, ointer;
  omit_and_model(i,oslope, ointer);
  slope = sqrt(N_*x_.var())*(slope_ - oslope)/sdev_residuals_;
  inter = sqrt(N_*x_.var())*
    (intercept_ - ointer)/(sdev_residuals_*goose_rms(x_));
}

double
LinearRegression::DFFITS(size_t i) const
{
  double m, b, osdr;
  omit_and_model(i, m, b, osdr);
  double x = x_.data(i);

  return ( (slope_-m)*x + (intercept_-b) ) / (osdr * sqrt(leverage(i)));
}

double
LinearRegression::DFFITS_fast(size_t i) const
{
  double m, b;
  omit_and_model(i, m, b);
  double x = x_.data(i);

  return ( (slope_-m)*x + (intercept_-b) )/(sdev_residuals_*sqrt(leverage(i)));
}

double
LinearRegression::cooks_D(size_t i) const
{
  const double* dx = x_.data();

  double m,b;
  omit_and_model(i,m,b);
  
  m -= slope_;
  b -= intercept_;

  double run = 0;
  for(size_t j=0; j<N_; ++j) {
    double x = m*dx[j]+b;
    run += x*x;
  }

  return run / (2 * sdev_residuals_ * sdev_residuals_);
}

double
LinearRegression::independence_t() const
{
  double omrr = 1-corr_*corr_;
  return omrr > 1e-8 ? sqrt(N_-2)*fabs(corr_)/sqrt(omrr) : HUGE_VAL;
}

double
LinearRegression::independence_p() const
{
  double t = independence_t();
  return t == HUGE_VAL ? 1.0 : 2*students_cdf(N_-2, t) - 1;
}

void
LinearRegression::omit_and_model(size_t i,
				 double& oslope, double& ointercept) const
{
  double omx = x_.data(i), omy = y_.data(i);

  // Recalculate regression model, omitting the ith point.
  double covar = N_*covarXY_;
  covar -= (omx - x_.mean()) * (omy - (y_.sum()-omy)/(N_-1));
  double var = N_*x_.var();
  var -= (omx - x_.mean()) * (omx - (x_.sum()-omx)/(N_-1));
  
  oslope = covar / var;
  ointercept = (y_.sum()-omy)/(N_-1) - oslope*(x_.sum()-omx)/(N_-1);
}

void
LinearRegression::omit_and_model(size_t i,
				 double& oslope, double& ointercept,
				 double& res_sdev) const
{
  omit_and_model(i,oslope,ointercept);

  const double* dx = x_.data();
  const double* dy = y_.data();
  double sum = dy[0] - (oslope*dx[0]+ointercept);
  double ssq = 0;
  size_t count = 1;
  for(size_t j=1; j<N_; ++j)
    if (i != j) {
      double res = dy[j] - (oslope*dx[j]+ointercept);
      sum += res;
      ++count;
      ssq += (res - sum/count)*(res - (sum-res)/(count-1));
    }
  res_sdev = sqrt(ssq/(N_-3)); // == (N_-1)-2
}

// $Id: LinearRegression.cpp,v 1.4 1999/03/31 14:45:45 trow Exp $










