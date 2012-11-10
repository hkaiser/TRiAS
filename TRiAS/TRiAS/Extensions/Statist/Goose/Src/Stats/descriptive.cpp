// This is -*- C++ -*-
// $Id: descriptive.cpp,v 1.15 1999/07/20 08:34:27 alstrup Exp $

/* descriptive.cpp
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
#include <algorithm>
#include <functional>
#include <assert.h>
#include "descriptive.h"

double
goose_min(const RealSet& rs)
{
  rs.empty_throw();
  return rs.min();
}

double
goose_max(const RealSet& rs)
{
  rs.empty_throw();
  return rs.max();
}

double
goose_range(const RealSet& rs)
{
  return rs.max() - rs.min();
}

double
goose_sum(const RealSet& rs)
{
  return rs.sum();
}

double
goose_mean(const RealSet& rs)
{
  rs.empty_throw();
  return rs.mean();
}

double
goose_var(const RealSet& rs)
{
  return rs.var();
}

double
goose_vars(const RealSet& rs)
{
  return rs.vars();
}

double
goose_sdev(const RealSet& rs)
{
  return rs.sdev();
}

double
goose_sdevs(const RealSet& rs)
{
  return rs.sdevs();
}

double
goose_percentile(const RealSet& rs, double p)
{
  rs.empty_throw();
  if (p < 0 || p > 1)
    throw Exception("Percentile out-of-range.");
  const double* s = rs.sorted_data();
  double t = p*(rs.size()-1);
  int i = (int) t;
  return (i+1-t)*s[i] + (t-i)*s[i+1];
}

double
goose_med(const RealSet& rs)
{
  return goose_percentile(rs, 0.5);
}

double
goose_q1(const RealSet& rs)
{
  return goose_percentile(rs, 0.25);
}

double
goose_q3(const RealSet& rs)
{
  return goose_percentile(rs, 0.75);
}

double
goose_iqr(const RealSet& rs)
{
  return goose_q3(rs) - goose_q1(rs);
}

double
goose_decile(const RealSet& rs, int i) {
  if (i<1||i>9) 
    throw Exception("Decile out of range");
  return goose_percentile(rs, i/10.0);
}

double
goose_mean_trimmed(const RealSet& rs, size_t l, size_t r)
{
  rs.empty_throw();
  if (l+r >= rs.size())
    throw Exception("Not enough data.");

  double mean = rs.mean();
  size_t N = rs.size(), N0=N;
  const double* s = rs.sorted_data();
  for(size_t i=0; i<l; ++i)
    mean += (mean-s[i])/(--N);
  for(size_t i=0; i<r; ++i)
    mean += (mean-s[N0-1-i])/(--N);
  return mean;
}

double
goose_mean_winsorized(const RealSet& rs, size_t l, size_t r)
{
  rs.empty_throw();
  if (l+r >= rs.size())
    throw Exception("Not enough data.");

  double mean = rs.mean();
  const size_t N=rs.size();
  const double* s = rs.sorted_data();
  double sl=s[l], sr=s[N-1-r];
  for(size_t i=0; i<l; ++i)
    mean += (sl-s[i])/N;
  for(size_t i=0; i<r; ++i)
    mean += (sr-s[N-1-i])/N;
  return mean;
}

double
goose_moment(const RealSet& rs, unsigned k, double x)
{
  rs.empty_throw();
  const double* d = rs.data();
  double sum=0;
  for(size_t i=0; i<rs.size(); ++i)
    sum += pow(d[i]-x, (int)k);
  return sum/rs.size();
}

double
goose_gmean(const RealSet& rs)
{
  rs.empty_throw();
  if (rs.min() <= 0)
    throw Exception("RealSet contains non-positive data.");
  const double* d = rs.data();
  double logsum = 0;
  for(size_t i=0; i<rs.size(); ++i)
    logsum += log(d[i]);
  return exp(logsum/rs.size());
}

double
goose_hmean(const RealSet& rs)
{
  rs.empty_throw();
  const double* d = rs.data();
  double invsum=0;
  for(size_t i=0; i<rs.size(); ++i) {
    if (d[i] == 0.0)
      throw Exception("RealSet contains zero.");
    invsum += 1/d[i];
  }
  if (invsum == 0.0)
    throw Exception("RealSet inverses sum to zero.");
  return rs.size()/invsum;
}

double
goose_rms(const RealSet& rs)
{
  // "My work on free software is motivated by an idealistic goal: spreading
  // freedom and cooperation.  I want to encourage free software to spread,
  // replacing proprietary software which forbids cooperation, and thus
  // make our society better." -rms
  rs.empty_throw();
  const double* d = rs.data();
  double sum=0;
  for(size_t i=0; i<rs.size(); ++i)
    sum += d[i]*d[i];
  return sqrt(sum/rs.size());
}

double
goose_meandev(const RealSet& rs)
{
  rs.empty_throw();
  const double* d = rs.data();
  double sum=0, m=rs.mean();
  for(size_t i=0; i<rs.size(); ++i)
    sum += fabs(d[i]-m);
  return sum/rs.size();
}

double
goose_meddev(const RealSet& rs)
{
  // This is expensive, and it duplicates code.  And it could be optimized.
  // Yipee!
  rs.empty_throw();
  size_t N = rs.size();
  double m=goose_med(rs);
  const double* d = rs.data();
  double* dtmp = new double[N];
  for(size_t i=0; i<N; ++i)
    dtmp[i] = fabs(d[i]-m);
  ::sort(dtmp,dtmp+N,less<double>());
  double md = N%2 ? dtmp[N/2] : (dtmp[N/2-1]+dtmp[N/2])/2;
  delete [] dtmp;
  return md;
}

double
goose_kurtosis(const RealSet& rs)
{
  rs.empty_throw();
  const double* d = rs.data();
  double m=rs.mean(), mom2=0, mom4=0;
  for(size_t i=0; i<rs.size(); ++i) {
    double x = d[i]-m;
    x *= x;
    mom2 += x;
    mom4 += x*x;
  }
  return mom4/(mom2*mom2);
}

double
goose_skewness(const RealSet& rs)
{
  rs.empty_throw();
  const double* d = rs.data();
  double m=rs.mean(), mom2=0, mom3=0;
  for(size_t i=0; i<rs.size(); ++i) {
    double x = d[i]-m;
    mom2 += x*x;
    mom3 += x*x*x;
  }
  return mom3/pow(mom2,1.5);
}

double 
goose_excess_kurtosis(const RealSet& rs)
{
  return goose_kurtosis(rs)-3;
}

double 
goose_momental_skewness(const RealSet& rs)
{
  return goose_skewness(rs)/2;
}

double
goose_durbin_watson(const RealSet& rs)
{
  if (rs.size() < 2)
    throw Exception("RealSet much contain at least two values.");

  double run = 0;
  double run_sq = 0;
  const double* d = rs.data();
  run_sq = d[0] * d[0];
  for(size_t i=1; i<rs.size(); ++i) {
    double x = d[i] - d[i-1];
    run += x*x;
    run_sq += d[i] * d[i];
  }

  return run / run_sq;
}

/*
  This is the test from pg. 93 of Madansky's
  "Prescriptions for Working Statisticians". 
  It checks for independence, with the alternative being
  AR(1) autoregression.  Does it have a name?
  It looks like a Durbin-Watson statistic with a slight
  change in the denominator.
*/
double
goose_AR1_independence_z(const RealSet& rs)
{
  if (rs.size() < 2)
    throw Exception("RealSet much contain at least two values.");
  
  double run=0;
  const size_t N = rs.size();
  const double* d = rs.data();
  for(size_t i=1; i<N; ++i) {
    double x = d[i] - d[i-1];
    run += x*x;
  }

  double v = run / rs.sumsq();
  const double exp_mean = 2.0;
  const double exp_var = 4.0 * (N - 1)/(N*N - 1);

  return (v-exp_mean)/sqrt(exp_var);
}

double
goose_autocorr(const RealSet& rs, size_t lag)
{
  const size_t N = rs.size();
  if (lag >= N)
    throw Exception("Lag is too large");

  const double* d = rs.data();
  const double m = rs.mean();
  double run = 0;
  for(size_t i=lag; i<N; ++i)
    run += (d[i]-m)*(d[i-lag]-m);
  
  return (run/(N-lag)) / goose_var(rs);
}

double
goose_autocorr_z(const RealSet& rs, size_t lag)
{
  const size_t N = rs.size();
  const double ac = goose_autocorr(rs, lag);
  const double exp_mean = -1.0/(N-1);
  const double exp_var  = 1.0/N;
  return (ac - exp_mean) / sqrt(exp_var);
}

double
goose_cramer_vos_mises(const RealSet& rs)
{
  rs.empty_throw();
  if (rs.min() <= 0.0 || rs.max() >= 1.0)
    throw Exception("Data must lie in the interval (0,1)");

  const size_t N = rs.size();
  double twoN = 2.0*N;
  const double* sd = rs.sorted_data();
  double w2 = 0;
  for(size_t i=0; i<N; ++i) {
    double x = sd[i] - (2*i+1)/twoN;
    w2 += x*x;
  }
  w2 += 1.0/(12*N);
  return w2;
}

double
goose_anderson_darling(const RealSet& rs)
{
  rs.empty_throw();
  if (rs.min() <= 0.0 || rs.max() >= 1.0)
    throw Exception("Data must lie in the interval (0,1)");

  const size_t N = rs.size();
  const double* sd = rs.sorted_data();
  double a2 = -N;
  for(size_t i=0; i<N; ++i)
    a2 += ((2*i+1)*log(sd[i]) + (2*N-1-2*i)*log(1-sd[i]))/N;
  return a2;
}

/*
  Find the value T >= 0 such that
  \prod (1+\min(x_i, T)) = c\prod (1+x_i) - c + 1
  (0 <= c <= 1)
*/

double
goose_gmean_threshold(const RealSet& rs, double c)
{
  const double epsilon = 1e-12;

  const unsigned N = rs.size();
  const double* d = rs.data();
  
  double a = 0, b = rs.max();
  double va = 0, vb = 0;
  for(unsigned i=0; i<N; ++i) {
    double x = log(1+d[i]);
    if (x < 0) va += x;
    vb += x;
  }
  double goal = log(c*exp(vb) - c + 1);
  assert(va <= goal && goal <= vb);

  double guess, vguess;
  do {
    guess = (a+b)/2;
    vguess = 0;
    double logguessp1 = log(guess+1);
    for(unsigned i=0; i<N; ++i) {
      if (d[i] < guess)
	vguess += log(1+d[i]);
      else
	vguess += logguessp1;
    }
        
    if (vguess < goal) 
      a = guess;
    else
      b = guess;

  } while (fabs(vguess-goal) > epsilon);

  return guess;
}

double
goose_mean_threshold_percentage(const RealSet& rs, double c)
{
  const unsigned N = rs.size();
  const double* d = rs.sorted_data();
  double goal = rs.sum() * c;
  
  unsigned count = 0;
  double tally = 0;
  while (count < N && tally <= goal) {
    tally += d[count];
    if (tally <= goal)
      ++count;
  }

  return (N-count)/(double)N;
}

double
goose_gmean_threshold_percentage(const RealSet& rs, double c)
{
  const unsigned N = rs.size();
  const double* d = rs.sorted_data();

  double goal = 0;
  for(unsigned i=0; i<N; ++i)
    goal += log(1+d[i]);
  goal = log(c*exp(goal) - c + 1);

  unsigned count = 0;
  double tally = 0;
  while (count < N && tally <= goal) {
    tally += log(1+d[count]);
    if (tally <= goal)
      ++count;
  }

  return (N-count)/(double)N;
}

double
goose_covar(const RealSet& rs0, const RealSet& rs1)
{
  rs0.empty_throw();
  rs0.same_size_throw(rs1);

  const double* d0 = rs0.data();
  const double* d1 = rs1.data();
  const size_t N = rs0.size();
  double sumx=d0[0], sumy=d1[0], Sxy=0;
  for(size_t i=1; i<N; ++i) {
    double x = d0[i];
    double y = d1[i];
    sumx += x;
    Sxy += (x - sumx/(i+1))*(y - sumy/i);
    sumy += y;
    // Exercise for the reader: Why does this give us the right answer?
  }
  return Sxy/N;
}

double
goose_corr(const RealSet& rs0, const RealSet& rs1)
{
  if (rs0.constant() || rs1.constant())
    throw Exception("Correlation against constant data is undefined.");
  double sdds = goose_sdev(rs0) * goose_sdev(rs1);
  return goose_covar(rs0,rs1)/sdds;
}

double
goose_spearman_rho(const RealSet& rs0, const RealSet& rs1)
{
  rs0.empty_throw();
  rs0.same_size_throw(rs1);

  RealSet rnk0=rs0, rnk1=rs1;
  rnk0.rank();
  rnk1.rank();

  double d_sum=0;
  const double* d0 = rnk0.data();
  const double* d1 = rnk1.data();
  size_t N = rnk0.size();
  for(size_t i=0; i<N; ++i) {
    double x = d0[i]-d1[i];
    d_sum += x*x;
  }

  return 1 - 6*d_sum/(((double)N*N-1)*N);
}

double
goose_kendall_tau(const RealSet& rs0, const RealSet& rs1)
{
  rs0.empty_throw();
  rs0.same_size_throw(rs1);

  Permutation p = rs0.sorting_permutation();
  RealSet cp1 = rs1;
  cp1.permute(p);
  
  const double* d = cp1.data();
  size_t N = cp1.size();

  int total=0;
  for(size_t i=0; i<N; ++i)
    for(size_t j=i+1; j<N; ++j) {
      if (d[j]<d[i])
	--total;
      else if (d[j]>d[i])
	++total;
    }
  cout << total << endl;

  double ties0=0;
  const double* sd0 = rs0.sorted_data();
  for(size_t i=0; i<N;) {
    size_t j=1;
    while (i+j<N && sd0[i]==sd0[i+j]) ++j;
    if (j>1) ties0 += j*(j-1.0);
    i += j;
  }

  double ties1=0;
  const double* sd1 = rs1.sorted_data();
  for(size_t i=0; i<N;) {
    size_t j=1;
    while (i+j<N && sd1[i]==sd1[i+j]) ++j;
    if (j>1) ties1 += j*(j-1.0);
    i += j;
  }

  double n = N*(N-1.0)/2.0;

  return total/sqrt((n-ties0/2)*(n-ties1/2));
}

void
goose_EDF_D_both(const RealSet& rs0, const RealSet& rs1,
		 double& dp, double& dm)
{
  rs0.empty_throw();
  rs1.empty_throw();

  const size_t N0 = rs0.size(), N1 = rs1.size();
  const double inc0 = 1.0/N0, inc1 = 1.0/N1;
  const double* d0 = rs0.sorted_data();
  const double* d1 = rs1.sorted_data();
  double y0=0, y1=0;
  size_t i0=0, i1=0;
  double supp = 0, supm = 0;

  while (i0 < N0 && i1 < N1) {
    if (d0[i0] < d1[i1]) {
      ++i0;
      y0 += inc0;
    } else if (d0[i0] > d1[i1]) {
      ++i1;
      y1 += inc1;
    } else {
      ++i0;
      ++i1;
      y0 += inc0;
      y1 += inc1;
    }

    double diff = y1-y0;
    if (diff > 0 && diff > supp)
      supp = diff;
    if (diff < 0 && -diff > supm)
      supm = -diff;
  }

  dp = supp;
  dm = supm;
}

double
goose_EDF_D_plus(const RealSet& rs0, const RealSet& rs1)
{
  double dp, dm;
  goose_EDF_D_both(rs0, rs1, dp, dm);
  return dp;
}

double
goose_EDF_D_minus(const RealSet& rs0, const RealSet& rs1)
{
  double dp, dm;
  goose_EDF_D_both(rs0, rs1, dp, dm);
  return dm;
}

double
goose_EDF_D(const RealSet& rs0, const RealSet& rs1)
{
  double dp, dm;
  goose_EDF_D_both(rs0, rs1, dp, dm);
  return dp < dm ? dm : dp;
}

double
goose_EDF_kuiper_V(const RealSet& rs0, const RealSet& rs1)
{
  double dp, dm;
  goose_EDF_D_both(rs0, rs1, dp, dm);
  return dp+dm;
}


double
goose_pooled_mean(const RealSet& rs0, const RealSet& rs1)
{
  if (rs0.size() == 0 && rs1.size() == 0)
    throw Exception("Both RealSets are empty.");
  return (rs0.size()*rs0.mean()+rs1.size()*rs1.mean())/(rs0.size()+rs1.size());
}

double
goose_pooled_var(const RealSet& rs0, const RealSet& rs1)
{
  if (rs0.size() == 0 && rs1.size() == 0)
    throw Exception("Both RealSets are empty.");
  return (rs0.size()*rs0.var()+rs1.size()*rs1.var())/(rs0.size()+rs1.size());
}

double
goose_weighted_mean(const RealSet& rs, const RealSet& wt)
{
  rs.empty_throw();
  rs.same_size_throw(wt);

  size_t N=rs.size();
  const double* d = rs.data();
  const double* w = wt.data();
  double sum = 0.0;
  for (size_t i=0; i<N; ++i)
    sum += d[i] * w[i];

  return sum/wt.sum();
}

// $Id: descriptive.cpp,v 1.15 1999/07/20 08:34:27 alstrup Exp $
