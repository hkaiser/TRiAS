// This is -*- C++ -*-
// $Id: parametric_estimation.cpp,v 1.5 1999/08/07 05:55:03 trow Exp $

/* 
 * parametric_estimation.cpp
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
#include <math.h>
#include <specfns.h>
#include <descriptive.h>
#include "parametric_estimation.h"

ConfInt
pest_normal_mean(double mean, double sdev, unsigned samples,
		       double conf)
{
  double t_val = inv_students_cdf(samples-2, (1+conf)/2);
  double serr = sdev / sqrt(samples);
  ConfInt ci;
  ci.set_by_error(mean, t_val * serr, conf);
  return ci;
}

ConfInt
pest_normal_mean(const RealSet& rs, double conf)
{
  return pest_normal_mean(rs.mean(), rs.sdevs(), rs.size(), conf);
}

ConfInt
pest_normal_difference_of_means_equal_sdev(double mean1, double mean2,
					   double sdev,
					   unsigned N1, unsigned N2,
					   double conf)
{
  double t_val = inv_students_cdf(N1+N2-2, (1+conf)/2);
  double err = sdev * sqrt((1.0/N1+1.0/N2));
  ConfInt ci;
  ci.set_by_error(mean1-mean2, t_val * err, conf);
  return ci;
}

ConfInt
pest_normal_difference_of_means_equal_sdev(const RealSet& a,
					   const RealSet& b,
					   double conf)
{
  return
    pest_normal_difference_of_means_equal_sdev(a.mean(), b.mean(),
					       sqrt(goose_pooled_var(a,b)),
					       a.size(), b.size(),
					       conf);
}

ConfInt
pest_normal_variance(double var, unsigned samples, double conf)
{
  if (samples < 2)
    throw Exception("Number of samples must be >= 2");
  if (var < 0)
    throw Exception("Estimated variance must be >= 0");
  double x_lo = inv_chi_square_cdf(samples-1, 1-(1+conf)/2);
  double x_hi = inv_chi_square_cdf(samples-1, (1+conf)/2);
  double est_lo = var*(samples-1)/x_hi;
  double est_hi = var*(samples-1)/x_lo;
  ConfInt ci;
  ci.set(est_lo, var, est_hi, conf);
  return ci;
}

ConfInt
pest_normal_variance(const RealSet& rs, double conf)
{
  // Yes, that has to be var() (and not vars()) for it to come out
  // properly.
  return pest_normal_variance(rs.var(), rs.size(), conf);
}

ConfInt
pest_normal_correlation(double r, unsigned samples, double conf)
{
  double z_val = inv_normal_cdf(0, 1, (1+conf)/2);

  double fisher_z = 0.5*(log(1+r) - log(1-r));
  double serr = 1/sqrt(samples-3);
  
  double z_lo = fisher_z - z_val * serr;
  double z_hi = fisher_z + z_val * serr;

  double r_lo = (exp(2*z_lo) - 1) / (exp(2*z_lo) + 1);
  double r_hi = (exp(2*z_hi) - 1) / (exp(2*z_hi) + 1);

  ConfInt ci;
  ci.set(r_lo, r, r_hi, conf);
  return ci;
}

ConfInt
pest_normal_correlation(const RealSet& a, const RealSet& b, double conf)
{
  double r = goose_corr(a,b);
  return pest_normal_correlation(r, a.size(), conf);
}

TTest::TTest(const RealSet& rs, double h, althyp_t ah) : ah_(ah), hm_(h)
{
  N_ = rs.size();
  em_ = rs.mean();
  ese_ = rs.sdevs() / sqrt(N_);
  t_ = (em_ - hm_)/ese_;

  if (ah_ == ALT_NOT_EQUAL)
    p_ = 2*t_cdf(N_-1, -fabs(t_));    
  else if (ah_ == ALT_LESS_THAN)
    p_ = t_cdf(N_-1, t_);
  else // if (ah_ == ALT_GREATER_THAN)
    p_ = 1-t_cdf(N_-1, t_);
    
}

EqualVarianceTest::EqualVarianceTest(const RealSet& a, const RealSet& b,
				     althyp_t ah) : ah_(ah)
{
  ev1_ = a.vars();
  ev2_ = b.vars();

  bool flipped = (ah_ == ALT_NOT_EQUAL) && ev1_ < ev2_;
  F_ = flipped ? ev2_/ev1_ : ev1_/ev2_;
  
  unsigned N1, N2;
  if (flipped) {
    N1 = b.size();
    N2 = a.size();
  } else {
    N1 = a.size();
    N2 = b.size();
  }
  
  if (ah_ == ALT_NOT_EQUAL) {
    // We can assume that F_ >= 1, by the "flipping" above.
    p_ = F_cdf(N2, N1, 1/F_) + (1-F_cdf(N1, N2, F_));
  } else if (ah_ == ALT_LESS_THAN) {
    p_ = F_cdf(N1, N2, F_);
  } else { // if (ah_ == ALT_GREATER_THAN)
    p_ = 1-F_cdf(N1, N2, F_);
  }
}

//////////////////////////////////////////////////////////////////////////////

ConfInt
pest_binomial_p_normal_approx(unsigned sucesses, unsigned trials, double conf)
{
  double z_val = inv_normal_cdf(0, 1, (1+conf)/2);
  double p = sucesses/(double)trials;
  double serr = sqrt(p*(1-p)/trials);
  ConfInt ci;
  ci.set_by_error(p, z_val * serr, conf);
  return ci;
}

// This approximation is given on page 272 of Hogg & Craig
ConfInt
pest_binomial_p_normal_approx_alt(unsigned sucesses, unsigned trials,
				  double conf)
{
  double z_val = inv_normal_cdf(0, 1, (1+conf)/2);
  double p = (sucesses+2.0)/(trials+4.0);
  double err = 
    sqrt((double)sucesses*(trials-sucesses)/trials + 1) / (trials + 4);
  
  ConfInt ci;
  ci.set_by_error(p, z_val * err, conf);
  return ci;
}

// Another interval from Hogg & Craig, p. 273
ConfInt
pest_binomial_p_arcsin_method(unsigned sucesses, unsigned trials,
			      double conf)
{
  double z_val = inv_normal_cdf(0, 1, (1+conf)/2);
  double sd = sqrt(0.25/trials);
  double aest = asin(sucesses/(double)trials);
  double lo = sin(aest - z_val * sd);
  double hi = sin(aest + z_val * sd);

  ConfInt ci;
  ci.set(lo, sucesses/(double)trials, hi, conf);
  return ci;
}

double*
binomial_success_exact_cdf(unsigned trials, double p)
{
  double* cdf = new double[trials+1];

  if (p > 1 || p < 0) throw Exception("p out of range");
  if (p == 0 || p == 1) {
    double init = 0;
    if (p == 0) init = 1;
    for(unsigned i=0; i<= trials; ++i)
      cdf[i] = init;
    if (p == 1) cdf[trials] = 1;
    return cdf;
  }

  double logp = log(p);
  double log1mp = log(1-p);

  double run=0;
  for (unsigned i=0; i<=trials; ++i) {
    run += exp(log_choose(trials, i) + i*logp + (trials-i)*log1mp);
    cdf[i] = run;
  }

  return cdf;
}

ConfInt
pest_binomial_difference_of_p_normal_approx(unsigned suc1, unsigned suc2,
					    unsigned tri1, unsigned tri2,
					    double conf)
{
  double z_val = inv_normal_cdf(0, 1, (1+conf)/2);
  double p1 = suc1/(double)tri1;
  double p2 = suc2/(double)tri2;
  double serr = sqrt(p1*(1-p1)/tri1 + p2*(1-p2)/tri2);

  ConfInt ci;
  ci.set_by_error(p1-p2, z_val * serr);
  return ci;
}



// $Id: parametric_estimation.cpp,v 1.5 1999/08/07 05:55:03 trow Exp $
