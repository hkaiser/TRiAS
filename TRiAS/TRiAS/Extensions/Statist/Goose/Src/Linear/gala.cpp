// This is -*- C++ -*-
// $Id: gala.cpp,v 1.3 1999/07/14 15:49:51 trow Exp $

/* gala.cpp
 *
 * GALA is Goose's Adequate Linear Algebra system.
 * It isn't great.  It isn't good.  It is mearly adequate.
 *
 * Some of the matrix algorithms used here came from Golub & Van Loan's
 * "Matrix Computations", 3rd edition, Johns Hopkins University Press.
 * It is a good book.
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
#include <iomanip>
#include "gala.h"
#include "Exception.h"

GVec::GVec() : N_(0), data_(0)
{ }

GVec::GVec(unsigned N) : N_(0), data_(0)
{
  alloc(N);
  set_all(0.0);
}

GVec::GVec(const GVec& v) : N_(0), data_(0)
{
  alloc(v.size());
  copy(v);
}

//////////////////////////////////////////////////////////////////////

bool
GVec::is_zero() const
{
  for(unsigned i=0; i<size(); ++i)
    if (data_[i] != 0)
      return false;
  return true;
}

double
GVec::length_sq() const
{
  double run=0;
  for(unsigned i=0; i<size(); ++i) {
    double x = data_[i];
    run += x*x;
  }
  return run;
}

double
GVec::norm_L1() const
{
  double run=0;
  for(unsigned i=0; i<size(); ++i)
    run += fabs(data_[i]);
  return run/size();
}

double
GVec::norm_Linf() const
{
  double max=0;
  for(unsigned i=0; i<size(); ++i) {
    double x = fabs(data_[i]);
    if (max < x) max = x;
  }
  return max;
}

double
GVec::dot(const GVec& gv) const
{
  if (gv.size() != size()) {
    throw Exception("Vectors are not of same size");
  }
  double run=0;
  for(unsigned i=0; i<size(); ++i)
    run += data_[i] * gv.data_[i];
  return run;
}

double
GVec::angle(const GVec& gv) const
{
  if (is_zero() || gv.is_zero())
    throw Exception("Vector is zero");
  return acos(dot(gv) / (length() * gv.length()));
}

GVec&
GVec::operator+=(const GVec& gv)
{
  if (gv.size() != size()) {
    throw Exception("Vectors are not of same size");
  }
  for(unsigned i=0; i<size(); ++i)
    data_[i] += gv.data_[i];
  return *this;
}

GVec&
GVec::operator-=(const GVec& gv)
{
  if (gv.size() != size()) {
    throw Exception("Vectors are not of same size");
  }
  for(unsigned i=0; i<size(); ++i)
    data_[i] -= gv.data_[i];
  return *this;
}

GVec&
GVec::operator*=(double a)
{
  for(unsigned i=0; i<size(); ++i)
    data_[i] *= a;
  return *this;
}

GVec&
GVec::operator/=(double a)
{
  for(unsigned i=0; i<size(); ++i)
    data_[i] /= a;
  return *this;
}

//////////////////////////////////////////////////////////////////////

void
GVec::alloc(unsigned N) 
{
  if (N != size()) {
    delete [] data_;
    N_ = N;
    data_ = N_ ? new double[N_] : 0;
  }
}

void
GVec::copy(const GVec& v)
{
  if (v.size() != size()) {
    throw Exception("Vectors are not of same size");
  }
  memcpy(data_, v.data_, N_*sizeof(double));
}

ostream&
operator<<(ostream& out, const GVec& v)
{
  out << '(';
  for(unsigned i=0; i<v.size(); ++i) {
    if (i != 0) out << ' ';
    out << v[i];
  }
  out << ')';
  return out;
}

//////////////////////////////////////////////////////////////////////////////
/// GMat
//////////////////////////////////////////////////////////////////////////////

GMat::GMat()
{ }

GMat::GMat(unsigned i) 
{
  data_.set_size(i,i);
  set_zero();
}

GMat::GMat(unsigned i, unsigned j) 
{
  data_.set_size(i,j);
  set_zero();
}

GMat::GMat(const GMat& m) : data_(m.data_), LU_(m.LU_), LUperm_(m.LUperm_)
{ }

////////////////////////////////////////////////

void
GMat::transpose()
{
  if (is_square()) {
    for(unsigned i=0; i<rows(); ++i)
      for(unsigned j=i+1; j<cols(); ++j) {
	double x = entry(i,j);
	entry(i,j) = entry(j,i);
	entry(j,i) = x;
      }
  } else {
    RCMatrix<double> t;
    for(unsigned i=0; i<rows(); ++i)
      for(unsigned j=0; i<cols(); ++j)
	t.entry(j,i) = entry(i,j);
    data_ = t;
  }
  clear_LU();
}

GVec
GMat::operator()(const GVec& v) const
{
  if (v.size() != cols()) {
    throw Exception("Vector is not of correct size");
  }
  GVec w(rows());

  for(unsigned i=0; i<rows(); ++i) {
    double run = 0;
    for(unsigned j=0; j<cols(); ++j) 
      run += entry(i,j) * v[j];
    w[i] = run;
  }
  return w;
}

GMat&
GMat::operator*=(const GMat& m)
{
  if (cols() != m.rows()) {
    throw Exception("Sizes of matrices does not match");
  }
  RCMatrix<double> prod(rows(), m.cols());
  for(unsigned i=0; i<rows(); ++i) {
    for(unsigned j=0; j<m.cols(); ++j) {
      double run=0.0;
      for(unsigned k=0; k<cols(); ++k) {
	run += entry_const(i,k)*m.entry_const(k,j);
      }
      prod.entry(i,j) = run;
    }
  }
  clear_LU();
  data_ = prod;
  
  sanitize();

  return *this;
}

void
GMat::swap_rows(unsigned i, unsigned j)
{
  if (i>=rows() || j>=rows()) {
    throw Exception("Index out of range");
  }
  if (i == j)
    return;

  data_.prep_for_write();
  double* d = data_.data_unsafe();
  unsigned ind1 = data_.index(i,0);
  unsigned ind2 = data_.index(j,0);

  for(unsigned k=0; k<cols(); ++k) {
    double x = d[ind1];
    d[ind1] = d[ind2];
    d[ind2] = x;
    data_.incr_col(ind1);
    data_.incr_col(ind2);
  }

  clear_LU();
}

void
GMat::swap_cols(unsigned i, unsigned j)
{
  if (i>=cols() || j>=cols()) {
    throw Exception("Index out of range");
  }
  if (i == j)
    return;

  data_.prep_for_write();
  double* d = data_.data_unsafe();
  unsigned ind1 = data_.index(0,i);
  unsigned ind2 = data_.index(0,j);

  for(unsigned k=0; k<rows(); ++k) {
    double x = d[ind1];
    d[ind1] = d[ind2];
    d[ind2] = x;
    data_.incr_row(ind1);
    data_.incr_row(ind2);
  }

  clear_LU();
}

void
GMat::sanitize(double eps)
{
  // The numerical analysis gods will strike me down for this...

  double max=0;
  double* d = data_.data();
  unsigned N = data_.size();
  for (unsigned i=0; i<N; ++i) {
    double x = fabs(d[i]);
    if (max < x) max = x;
  }

  double tol = eps*max;
  for (unsigned i=0; i<N; ++i) 
    if (fabs(d[i]) < tol) d[i] = 0;

  clear_LU();
}

int
GMat::rank() const
{
  if (!is_square()) {
    throw Exception("Matrix is not square");
  }
  build_LU();
  int r = 0;
  for(unsigned i=0; i<rows(); ++i)
    if (LU_.entry(i,i) != 0) ++r;
  return r;
}

double
GMat::det() const
{
  if (!is_square()) {
    throw Exception("Matrix is not square");
  }

  build_LU();

  double d = rows() % 2 ? 1 : -1;
  for(unsigned i=0; i<rows(); ++i)
    d *= LU_.entry(i,i);
  return d;
}

GVec
GMat::solve(const GVec& b) const
{
  if (!is_square()) {
    throw Exception("Matrix is not square");
  }
  if (rows() != b.size()) {
    throw Exception("Vector is not of correct size");
  }

  build_LU();

  GVec a = b;
  const unsigned* pp = LUperm_.data_const();

  // apply gauss transforms and permutations
  for(unsigned k=0; k<rows()-1; ++k) {

    unsigned pk = pp[k];
    double x = a[k];
    a[k] = a[pk];
    a[pk] = x;

    for(unsigned i=k+1; i<rows(); ++i)
      a[i] -= a[k] * LU_.entry(i,k);
  }

  // do back-substitution
  a[rows()-1] /= LU_.entry(rows()-1,rows()-1);
  for(int i=rows()-2; i>=0; --i) {
    double x = a[i];
    for(unsigned j=(unsigned)i+1; j<rows(); ++j)
      x -= LU_.entry(i,j) * a[j];
    a[i] = x / LU_.entry(i,i);
  }
  return a;
}

void
GMat::invert()
{
  if (!is_square()) {
    throw Exception("Matrix is not square");
  }

  build_LU();

  GVec a(cols());
  const unsigned* pp = LUperm_.data_const();

  data_.prep_for_write();
  double* d = data_.data_unsafe();

  for(unsigned c=0; c<cols(); ++c) {
    // make basis vector
    a.set_basic(c);

    // apply gauss transforms and permutations
    for(unsigned k=0; k<rows()-1; ++k) {
      unsigned pk = pp[k];
      double x = a[k];
      a[k] = a[pk];
      a[pk] = x;

      for(unsigned i=k+1; i<rows(); ++i)
	a[i] -= a[k] * LU_.entry_const(i,k);
    }

    // do back-substitution
    a[rows()-1] /= LU_.entry_const(rows()-1,rows()-1);
    for(int i=rows()-2; i>=0; --i) {
      double x = a[i];
      for(unsigned j=(unsigned)i+1; j<rows(); ++j) {
	x -= LU_.entry_const(i,j) * a[j];
      }
      a[i] = x / LU_.entry_const(i,i);
    }

    // put "solved" column vector back into matrix
    unsigned ind = data_.index(0,c);
    for(unsigned r=0; r<rows(); ++r) {
      d[ind] = a[r];
      data_.incr_row(ind);
    }
  }
  
  clear_LU();
  
  sanitize();
}

////////////////////////////////////////////////

void
GMat::build_LU() const
{
  if (!is_square()) {
    throw Exception("Matrix is not square");
  }
  if (LU_.size())
    return;

  unsigned N = rows();

  /*
    Since we are creating LU_here locally, we can use our "unsafe" operations
    since we know it isn't aliased anywhere.
  */
  RCArray<unsigned> LUperm_here;
  RCMatrix<double> LU_here = data_;

  LU_here.prep_for_write();

  for(unsigned k=0; k<N-1; ++k) {

    // find largest element
    double max=0;
    unsigned max_ind=0;
    for(unsigned i=k; i<N; ++i) {
      double x = fabs(entry(i,k));
      if (max < x) {
	max_ind = i;
	max = x;
      }
    }
    LUperm_here.add(max_ind);

    // swap
    unsigned ind1 = LU_here.index(k,k);
    unsigned ind2 = LU_here.index(max_ind, k);
    for(unsigned i=k; i<cols(); ++i) {
      double x = LU_here.data_const()[ind1];
      LU_here.data_unsafe()[ind1] = LU_here.data_const()[ind2];
      LU_here.data_unsafe()[ind2] = x;
      LU_here.incr_col(ind1);
      LU_here.incr_col(ind2);
    }

    if (fabs(LU_here.entry_const(k,k)) > 1e-15) {

      double kk = LU_here.entry_const(k,k);
      for(unsigned i=k+1; i<rows(); ++i)
	LU_here.entry_unsafe(i,k) /= kk;

      for(unsigned i=k+1; i<rows(); ++i) {
	double ik = LU_here.entry_const(i,k);
	for(unsigned j=k+1; j<rows(); ++j)
	  LU_here.entry_unsafe(i,j) -= ik*LU_here.entry_const(k,j);
      }
    }
  }

  // Stupid compiler tricks
  ((GMat*)this)->LU_ = LU_here;
  ((GMat*)this)->LUperm_ = LUperm_here;
}

ostream&
operator<<(ostream& out, const GMat& m)
{
  for(unsigned r=0; r<m.rows(); ++r) {
    if (r == 0)
      out << '/';
    else if (r == m.rows()-1)
      out << '\\';
    else
      out << '|';
    out << " ";
    for(unsigned c=0; c<m.cols(); ++c) {
      out << setw(8) << m.entry_const(r,c) << " ";
    }
    if (r == 0)
      out << '\\';
    else if (r == m.rows()-1)
      out << '/';
    else
      out << '|';
    out << endl;
  }
  return out;
}

// $Id: gala.cpp,v 1.3 1999/07/14 15:49:51 trow Exp $
