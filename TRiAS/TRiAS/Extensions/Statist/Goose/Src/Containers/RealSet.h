// This is -*- C++ -*-
// $Id: RealSet.h,v 1.13 1999/07/20 20:52:09 trow Exp $

/* 
 * RealSet.h
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

#ifndef _INC_REALSET_H
#define _INC_REALSET_H

#define REALSET_BOUNDS_CHECKING 1

#include <math.h>
#include <string>
#include <iostream>
#include "stringtools.h"
#include "RCArray.h"
#include "Permutation.h"
#include "Exception.h"
#include "DataSet.h"
#include "DataConverter.h"

using namespace std;

class RealSet : public DataSet_Typed<double>  {
public:
  static const DataSet::type_t typecode;

  RealSet();
  RealSet(const RealSet&);
  virtual ~RealSet() { }

  RealSet& operator=(const RealSet&);

  DataSet * clone() const {
    return new RealSet(*this);
  }

  unsigned size() const { return data_.size(); }
  void empty_throw() const {
    if (size() == 0) throw Exception("RealSet is empty.");
  }
  void same_size_throw(const RealSet& rs) const {
    if (size() != rs.size())
      throw Exception("RealSets are not of the same size.");
  }

  void reserve(unsigned R); 
  void resize(unsigned N);
  void clear();

  // Return a permutation that will, when applied, bring the RealSet into
  // sorted order.  (Does not sort the RealSet, just produces instructions
  // for how to do so!)
  Permutation sorting_permutation(int dir = 1) const;

  void permute(const Permutation&);

  // RealSet specific methods

  const double* data() const { return data_.data(); }

  double data(int i) const { 
#ifdef REALSET_BOUNDS_CHECKING
    if (! in_bounds(i))
      throw Exception_IndexOutOfBounds(i, min_index(), max_index());
#endif
    return (data_.data())[i - min_index()];
  }

  const double* sorted_data() const;
  double sorted_data(int i) const {
#ifdef REALSET_BOUNDS_CHECKING
    if (i<0 || i >= (int)size())
      throw Exception_IndexOutOfBounds(i, 0, size()-1);
#endif
    return sorted_data()[i];
  }

  // You can get back garbage if you, for example, take the min() of
  // an empty dataset.
  double min() const { return min_; }
  double max() const { return max_; }
  double mean() const { return mean_; }
  double sum() const { return size()*mean(); }
  double sumsq() const { return sumsq_; }
  double var() const { empty_throw(); return sumsq()/size(); }
  double vars() const { empty_throw(); return sumsq()/(size()-1); }
  double sdev() const { empty_throw(); return sqrt(sumsq()/size()); }
  double sdevs() const {
    if (size() < 2)
      throw Exception("RealSet much contain at least two values.");
    return sqrt(sumsq()/(size()-1));
  }
  
  int sortedness() const { return sortedness_; }
  bool increasing() const { return sortedness_ == 1; }
  bool decreasing() const { return sortedness_ == -1; }
  bool unordered() const { return sortedness_ == 0; }
  bool constant() const { return sortedness_ == 2; }

  unsigned greater_than(double x) const;
  unsigned less_than(double x) const ;
  unsigned between(double a, double b) const {
    return size()-less_than(a)-greater_than(b);
  }
  unsigned equal_to(double x) const {
    return size()-less_than(x)-greater_than(x);
  }

  // Implementation of typed interface inherited from DataSet_Typed
  void add(double);
  //  void add(string const & s) { DataSet_Typed<double>::add(s); }
  void add_at(int i, double);
  //  void add_at(int i, string const & s) { DataSet_Typed<double>::add_at(i, s); }
  void set(int i, double);
  void remove(int i);
  void remove(int i, int j);

  void add(double*, size_t count);
  void add_at(int i, double*, size_t count);
  void set(int i, const double*, size_t count);

  void append(const RealSet&);

//  This case is covered by the template, and thus ambigious... (Asger)
//  void apply(double (*)(double));

  template<class FuncObj>
  void apply(FuncObj f) {
    double* d = data_.data();
    unsigned N = size();
    for(unsigned i=0; i<N; ++i)
      d[i] = f(d[i]);
    recalc();
  }

  // transform by x -> ax+b
  void linear_transform(double a, double b);
  // transform by x -> log(x) (natural log, of course...)
  void log_transform();
  void exp_transform();
  void logit_transform();
  void fabs_transform();
  void deviations_transform(double y);  // transforms by x -> |x-y|

  void reverse();
  void scramble_explicit(Random&);
  void sort(int dir = 1);
  void rank();
  void standardize();

  template<class FuncObj>
  RealSet& dual_apply(FuncObj f, const RealSet& rs) {
    same_size_throw(rs);
    double* d1 = data_.data();
    const double* d2 = rs.data_.data();
    unsigned N = size();
    for(unsigned i=0; i<N; ++i)
      d1[i] = f(d1[i],d2[i]);
    recalc();
    return *this;
  }

private:

  class Inner_Add {
  public:
    double operator()(double x, double y) const { return x+y; }
  };

  class Inner_Subtract {
  public:
    double operator()(double x, double y) const { return x-y; }
  };

  class Inner_Multiply {
  public:
    double operator()(double x, double y) const { return x*y; }
  };

public:

  RealSet& operator+=(const RealSet& rs) {
    return dual_apply(Inner_Add(), rs);
  }
  RealSet& operator-=(const RealSet& rs) {
    return dual_apply(Inner_Subtract(), rs);
  }
  RealSet& operator*=(const RealSet& rs) {
    return dual_apply(Inner_Multiply(), rs);
  }

  double epsilon() const { return epsilon_; }
  void set_epsilon(double e) { epsilon_ = e; }

  void add_compressed(const string& s);
  void write_xml(ostream& out, bool compress = true) const;

protected:
  string to_string(double x) const {
    return real_converter.to_canonical(x);
  }
  double from_string(const string& s) const {
    return real_converter.to_real(s);
  }

private:
  void update_add(double);
  void update_remove(double);
  void recalc_sortedness();
  void recalc();
  void recalc_saving_sorted();
  void copy(const RealSet&);

  // convenience routines...
  bool is_zero(double x) const { return fabs(x) < epsilon_; }
  bool are_equal(double x, double y) const { return is_zero(x-y); }
  bool is_positive(double x) const { return x > epsilon_; }

  RealConverter real_converter;

  RCArray<double> data_;

  bool have_sorted_data() const { return sdata_.size() > 0; }

  mutable RCArray<double> sdata_;

  double min_, max_, mean_;
  // If we call our data values x_1,...,x_N, then sumsq_ contains
  // \sum_{i=0}^N(x_i-\mu)^2, where \mu is the mean of the x_i.
  double sumsq_;

  // sortedness == +1 if data is increasing
  //            == -1 if data is decreasing
  //            ==  0 if data is unordered
  //            == +2 if the data is constant (a bad hack)
  int sortedness_;

  double epsilon_;
};

#endif // _INC_REALSET_H

// $Id: RealSet.h,v 1.13 1999/07/20 20:52:09 trow Exp $
