// This is -*- C++ -*-
// $Id: runs.h,v 1.4 1999/05/26 14:03:18 trow Exp $

/* runs.cc
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

#ifndef _INC_RUNS_H
#define _INC_RUNS_H

#include <ConfInt.h>
#include "RealSet.h"

// For a given sequence length N and probability p, returns an array of
// length N-1 containing the exact pdf or cdf for the number of runs in
// a set of N trials w/ probability p of success.
double* runs_exact_pdf_array(unsigned N, double p);
double* runs_exact_cdf_array(unsigned N, double p);

ConfInt runs_exact_interval(unsigned N, double p, double conf);

// Returns the exact probability of <= k runs in N trials with probability p.
double runs_exact_cdf(unsigned N, double p, unsigned k);

// Returns the standard normal approximation of the probability of <= k
// runs in N trials with probability p.
double runs_approx_cdf(unsigned N, double p, unsigned k);


class RunsCount {
public:
  RunsCount() : size_(0), t_(0), f_(0), runs_(0) { }

  size_t size() const { return size_; }
  size_t obs(bool x) const { return  x ? t_ : f_; }
  size_t obs_true() const { return t_; }
  size_t obs_false() const { return f_; }
  size_t runs() const { return runs_; }

  double runs_mean() const;
  double runs_sdev() const;
  double z() const {
    double s = runs_sdev();
    if (s <= 0.0)
      throw Exception("runs_sdev is not positive");
    return (runs()-runs_mean())/s;
  }
  double p_value() const;

  void add(bool);

  void add(const RealSet& ds, bool (*d)(double)) {
    for(size_t i=0; i<ds.size(); ++i)
      add(d(ds.data(i)));
  }

  template<class Decide>
  void add(const RealSet& ds, Decide d) {
    for(size_t i=0; i<ds.size(); ++i)
      add(d(ds.data(i)));
  }

  void clear() { size_ = t_ = f_ = runs_ = 0; }

private:
  size_t size_, t_, f_, runs_;
  bool last_;
};

class RunsUpDown {
public:
  RunsUpDown() : size_(0), runs_(0), last_(0), constant_(true) { }

  size_t size() const { return size_; }
  size_t runs() const { return runs_; }

  double runs_mean() const;
  double runs_sdev() const;
  double z() const {
    double s = runs_sdev();
    if (s <= 0.0)
      throw Exception("runs_sdev is not positive");
    return (runs()-runs_mean())/s; 
  }
  double p_value() const;

  void add(double);
  void add(const RealSet& ds) {
    for(size_t i=0; i<ds.size(); ++i)
      add(ds.data(i));
  }

  void clear() {
    size_ = runs_ = 0;
    constant_ = true;
  }

private:
  size_t size_, runs_;
  double last_;
  bool last_higher_, constant_;
};

#endif // _INC_RUNS_H

// $Id: runs.h,v 1.4 1999/05/26 14:03:18 trow Exp $
