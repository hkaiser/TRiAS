// This is -*- C++ -*-
// $Id: runs.cpp,v 1.5 1999/07/20 08:34:27 alstrup Exp $

/* runs.cpp
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
#include <math.h>
#include <Exception.h>
#include <specfns.h>
#include <assert.h>
#include "runs.h"



// Returns the pdf in an array of length N-1
double*
runs_exact_pdf_array(unsigned N, double p)
{
  if (p < 0) throw Exception("Probability less than zero.");
  if (p > 1) throw Exception("Probability greater than one.");
  if (N < 2) throw Exception("Sample size too small.");

  double q = 1-p;
  double* Rp = new double[N-1];
  double* Rq = new double[N-1];

  Rp[0] = p;
  Rq[0] = q;
  for(size_t i=1; i<N-1; ++i)
    Rp[i] = Rq[i] = 0;

  size_t j=2;
  while (j < N) {
    ++j;
    double Pp = 0, Pq = 0;
    for(size_t k=0; k<j-1; ++k) {
      double xp = Rp[k], xq = Rq[k];
      Rp[k] = p * (xp + Pq);
      Rq[k] = q * (xq + Pp);
      Pp = xp, Pq = xq;
    }
  }

  for(size_t i=0; i<N-1; ++i) 
    Rp[i] += Rq[i];
  
  delete [] Rq;

  return Rp;
}

double*
runs_exact_cdf_array(unsigned N, double p)
{
  double* pdf = runs_exact_pdf_array(N, p);
  for(size_t i=1; i<N-1; ++i)
    pdf[i] += pdf[i-1];
  return pdf;
}

/*
  Calculate a conservative confidence interval for the # of runs,
  centered on the mean, adjusted for any skewness in the exact
  distribution.
*/
ConfInt
runs_exact_interval(unsigned N, double p, double conf)
{
  double* pdf = runs_exact_pdf_array(N, p);
  double mean = 2*p*(1-p)*(N-1)+1;
  int mean_f = (int)floor(mean), mean_c = (int)ceil(mean);

  double right_mass = 0, left_mass = 0;
  for(int i=0; i<=mean_f; ++i)
    left_mass += pdf[i];
  for(int i=mean_c; i<(int)N-1; ++i)
    right_mass += pdf[i];
  if (mean_f == mean_c) {
    left_mass -= pdf[mean_f]/2;
    right_mass -= pdf[mean_c]/2;
  }
  assert(fabs(left_mass+right_mass-1) < 1e-8);
  left_mass *= conf;
  right_mass *= conf;

  int bot=mean_f, top=mean_c;
  if (mean_f == mean_c) {
    left_mass -= pdf[mean_f]/2;
    right_mass -= pdf[mean_c]/2;
  }
  while (mean_f >= 0 && left_mass > 0)
    left_mass -= pdf[mean_f--];
  while (mean_c < (int)N-1 && right_mass > 0)
    right_mass -= pdf[mean_c++];
  
  assert(left_mass <= 0);
  assert(right_mass <= 0);

  ConfInt ci;
  ci.set(bot, mean, top);
  ci.set_confidence(conf-left_mass-right_mass);

  delete [] pdf;

  return ci;
}

// Returns probability that number of runs is <= k.
double
runs_exact_cdf(unsigned N, double p, unsigned k)
{
  if (k < 1) return 0;
  if (N != 0 && k >= N-1) return 1.0;
  double* cdf = runs_exact_cdf_array(N,p);
  double pp = cdf[k-1];
  delete [] cdf;
  return pp;
}

double
runs_approx_cdf(unsigned N, double p, unsigned k)
{
  if (p < 0) throw Exception("Probability less than zero.");
  if (p > 1) throw Exception("Probability greater than one.");
  if (N < 2) throw Exception("Sample size too small.");

  if (k < 0) return 0.0;
  if (k >= N-1) return 1.0;

  double mean = 1 + 2*N*p*(1-p);
  double sdev = sqrt(2*p*(1-p)*N*(2*N*p*(1-p)-1)/(N-1));
  return normal_cdf(mean, sdev, k);
}


// runs_mean() and runs_sdev() are based on asymptotic properties of the
// distribution of runs.  For small samples, these will be inaccurate.
// Eventually I need to add look-up tables of tail probabilities for
// sample sizes up to about 20 or so.


double
RunsCount::runs_mean() const
{
  return size_ ? 1+2.0*t_*f_/size_ : 0;
}

double
RunsCount::runs_sdev() const
{
  if (size_ == 0 || t_ == size_ || f_ == size_)
    return 0;
  double tf = t_*f_;
  double N = size_;
  return sqrt(2*tf*(2*tf-N)/(N*N*(N-1)));
}

double
RunsCount::p_value() const
{
  return 2*normal_cdf(fabs(z()))-1;
}


void
RunsCount::add(bool x)
{
  if (size_ == 0 || last_ != x) ++runs_;
  ++size_;
  x ? ++t_ : ++f_;
  last_ = x;
}

////////////////////////////////////////////////////////////////

double
RunsUpDown::runs_mean() const
{
  return size_ > 2 ? (2.0*size_-1)/3.0 : (size_ ? 1 : 0);
}

double
RunsUpDown::runs_sdev() const
{
  return size_ >= 2 ? sqrt((16.0*size_-29.0)/90.0) : 0;
}

double
RunsUpDown::p_value() const
{
  return 2*normal_cdf(fabs(z()))-1;
}

void
RunsUpDown::add(double x)
{
  if (size_ == 0) {
    ++runs_;
    constant_ = true;
  } else if (constant_) {
    if (x != last_) {
      last_higher_ = (x > last_);
      constant_ = false;
    }
  } else {
    if (last_higher_ ? (x < last_) : (x > last_)) {
      last_higher_ = !last_higher_;
      ++runs_;
    }
  }
  last_ = x;
  ++size_;
}



// $Id: runs.cpp,v 1.5 1999/07/20 08:34:27 alstrup Exp $
