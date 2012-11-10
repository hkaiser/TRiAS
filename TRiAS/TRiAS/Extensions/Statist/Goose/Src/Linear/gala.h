// This is -*- C++ -*-
// $Id: gala.h,v 1.3 1999/07/14 15:49:51 trow Exp $

/* gala.h
 *
 * GALA is Goose's Adequate Linear Algebra system.
 * It isn't great.  It isn't good.  It is mearly adequate.
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

#ifndef _INC_GALA_H
#define _INC_GALA_H

#include <math.h>
#include "RCMatrix.h"

class GVec {
public:
  GVec();
  GVec(unsigned);
  GVec(unsigned, unsigned);
  GVec(const GVec&);
  ~GVec() { delete [] data_; }
  
  GVec& operator=(const GVec& v) { 
    if (data_ != v.data_) {
      alloc(v.size());
      copy(v);
    }
    return *this;
  }

  unsigned size() const { return N_; }
  double operator[](unsigned i) const { return data_[i]; }
  double& operator[](unsigned i) { return data_[i]; }

  void set_all(double x) { for(unsigned i=0; i<N_; ++i) data_[i] = x; }
  void set_zero() { set_all(0.0); }
  void set_basic(unsigned i) { set_zero(); data_[i] = 1; }

  bool is_zero() const;
  bool is_nonzero() const { return !is_zero(); }

  double length_sq() const; // == length squared
  double length() const { return sqrt(length_sq()); }

  double norm_L1() const;
  double norm_L2() const { return length(); }
  double norm_Linf() const;

  double dot(const GVec&) const;
  double angle(const GVec&) const;

  GVec& operator+=(const GVec&);
  GVec& operator-=(const GVec&);
  GVec& operator*=(double);
  GVec& operator/=(double);
  
private:
  void alloc(unsigned n);
  void copy(const GVec&);

  unsigned N_;
  double* data_;
};

inline GVec operator+(const GVec& a, const GVec& b)
{
  GVec c = a;
  c += b;
  return c;
}

inline GVec operator-(const GVec& a, const GVec& b)
{
  GVec c = a;
  c -= b;
  return c;
}

inline GVec operator*(double a, const GVec& v)
{
  GVec w = v;
  w *= a;
  return w;
}

inline GVec operator*(const GVec& v, double a)
{
  GVec w = v;
  w *= a;
  return w;
}

inline GVec operator/(const GVec& v, double a)
{
  GVec w = v;
  w /= a;
  return w;
}

ostream& operator<<(ostream&, const GVec&);

/////////////////////////////////////////////////////////////////////////////

class GMat {
public:
  GMat();
  GMat(unsigned); // assume square
  GMat(unsigned, unsigned);
  GMat(const GMat&);

  GMat& operator=(const GMat& m) {
    data_ = m.data_;
    LU_ = m.LU_;
    LUperm_ = m.LUperm_;
    return *this;
  }

  unsigned rows() const { return data_.rows(); }
  unsigned cols() const { return data_.cols(); }
  unsigned min_rc() const { return rows()>cols() ? cols() : rows(); }
  unsigned max_rc() const { return rows()<cols() ? cols() : rows(); }

  bool is_square() const { return rows() == cols(); }
  bool same_size_as(const GMat& m) const {
    return rows() == m.rows() && cols() == m.cols();
  }

  double operator()(unsigned r, unsigned c) const {
    return data_.entry(r,c);
  }
  double& operator()(unsigned r, unsigned c) {
    return data_.entry(r,c);
  }

  double entry(unsigned r, unsigned c) const { return operator()(r,c); }
  double entry_const(unsigned r, unsigned c) const { return operator()(r,c); }
  double& entry(unsigned r, unsigned c) { return operator()(r,c); }

  void set_all(double x) {
    for(unsigned i=0; i<data_.size(); ++i)
      data_.data()[i] = x;
  }
  void set_zero() { set_all(0); }
  void set_diagonal(double x) {
    set_zero();
    for(unsigned i=0; i<min_rc(); ++i)
      entry(i,i) = x;
  }
  void set_identity() { set_diagonal(1.0); }

  void transpose();
  void swap_rows(unsigned i, unsigned j);
  void swap_cols(unsigned i, unsigned j);
  void sanitize(double eps = 1e-15);

  GVec operator()(const GVec&) const;
  GMat& operator*=(const GMat&);

  int rank() const;
  double det() const;
  // Returns the vector a that solves the eqn Ma=b
  GVec solve(const GVec& b) const;
  void invert();

private:
  void build_LU() const;

  void clear_LU() {
    LU_.clear();
    LUperm_.clear();
  }

  void alloc(unsigned, unsigned);
  void copy(const GMat&);

  unsigned rows_, cols_;
  RCMatrix<double> data_;

  RCMatrix<double> LU_;    // We cache the LU decomposition...
  RCArray<unsigned> LUperm_; // ...and the row permutation info.
};

inline GMat operator*(GMat a, const GMat& b) {
  a *= b;
  return a;
}

ostream& operator<<(ostream&, const GMat&);


#endif // _INC_GALA_H

// $Id: gala.h,v 1.3 1999/07/14 15:49:51 trow Exp $
