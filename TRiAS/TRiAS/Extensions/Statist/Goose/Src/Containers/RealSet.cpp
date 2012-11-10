// This is -*- C++ -*-
// $Id: RealSet.cpp,v 1.13 1999/07/20 20:52:09 trow Exp $

/* 
 * RealSet.cpp
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
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>
#include <zdouble.h>
#include "RealSet.h"

// some random number...
const DataSet::type_t RealSet::typecode = 0xeaeff;

RealSet::RealSet() : DataSet_Typed<double>(RealSet::typecode), epsilon_(1e-8)
{
  clear();
}

RealSet::RealSet(const RealSet& ds)
  : DataSet_Typed<double>(RealSet::typecode)
{
  copy(ds);
}

RealSet&
RealSet::operator=(const RealSet& ds)
{
  copy(ds);
  return *this;
}

const double*
RealSet::sorted_data() const
{
  if (size() == 0) return 0; 
  if (sdata_.size()) return sdata_.data();

  sdata_ = data_;
  double* s = sdata_.data();
  const unsigned N = sdata_.size();

  if (sortedness() == 0) {
    ::sort(s, s+N, less<double>());
  } else if (sortedness() == -1) {
    for(unsigned i=0; i<N/2; ++i) {
      double t = s[i];
      s[i] = s[N-1-i];
      s[N-1-i] = t;
    }
  }

  return (const double*)s;
}

unsigned
RealSet::greater_than(double x) const
{
  if (size() == 0 || max() <= x) return 0;
  if (min() > x) return size();

  const double* d = sorted_data();
  const unsigned N = size();
  unsigned i=0, j=N-1;

  for(;;) {
    unsigned mid=(i+j)/2;
    if (mid == N-1) --mid;
    if (d[mid] <= x && x < d[mid+1])
      return N-mid-1;
    else if (d[mid] > x) 
      j = mid;
    else
      i = mid;
  }
}

unsigned
RealSet::less_than(double x) const
{
  if (size() == 0 || min() >= x) return 0;
  if (max() < x) return size();

  const double* d = sorted_data();
  const unsigned N = size();
  unsigned i=0, j=N-1;

  for(;;) {
    unsigned mid=(i+j)/2;
    if (mid == N-1) --mid;
    if (d[mid] < x && x <= d[mid+1])
      return mid+1;
    else if (d[mid] >= x)
      j = mid;
    else
      i = mid;
  }
}

void
RealSet::reserve(unsigned R)
{
  data_.reserve(R);
}

void
RealSet::resize(unsigned N)
{
  if (size() > N) {
    remove(N, size());
  } else {
    while(size() < N)
      add(0.0);
  }
}

void
RealSet::add(double x)
{
  update_add(x);
  data_.add(x);
  if (sortedness_ > 0)
    sdata_ = data_;
  else
    sdata_.clear();
}

void
RealSet::add_at(int i, double x)
{
#ifdef REALSET_BOUNDS_CHECKING
  if (! in_bounds(i))
    throw Exception_IndexOutOfBounds(i, min_index(), max_index());
#endif

  update_add(x);
  data_.add_at(i - min_index(),x);
  recalc_sortedness(); // sortedness will be wrong from update_add().
  if (sortedness_ > 0)
    sdata_ = data_;
  else
    sdata_.clear();
}

void
RealSet::remove(int i)
{
#ifdef REALSET_BOUNDS_CHECKING
  if (! in_bounds(i))
    throw Exception_IndexOutOfBounds(i, min_index(), max_index());
#endif

  update_remove(data(i));
  data_.remove_at(i - min_index());

  // Remember, removing an element preserves sortedness.  The only possible
  // change is to bring an unsorted list into a sorted state.
  if (sortedness_ == 0)
    recalc_sortedness();

  if (sortedness_ > 0)
    sdata_ = data_;
  else
    sdata_.clear();
}

void
RealSet::add(double* xs, size_t count)
{
  data_.add(xs,count);
  recalc();
}
void
RealSet::add_at(int i, double* xs, size_t count)
{
#ifdef REALSET_BOUNDS_CHECKING
  if (! in_bounds(i))
    throw Exception_IndexOutOfBounds(i,min_index(), max_index());
#endif
  if (i == max_index())
    add(xs, count);
  else {
    data_.add_at(i - min_index(),xs,count);
    recalc();
  }
}

void
RealSet::remove(int i, int j)
{
  if (i > j)
    throw Exception("Illegal range");

#ifdef REALSET_BOUNDS_CHECKING
  if (! in_bounds(j))
    throw Exception_IndexOutOfBounds(j,min_index(),max_index());
#endif

  data_.remove_at(i-min_index(), j-min_index());
  recalc();
}

void
RealSet::set(int i, double x)
{
#ifdef REALSET_BOUNDS_CHECKING
  if (! in_bounds(i))
    throw Exception_IndexOutOfBounds(i,min_index(),max_index());
#endif

  data_.data()[i - min_index()] = x;
  recalc();
}

void
RealSet::set(int i, const double* xs, size_t count)
{
#ifdef REALSET_BOUNDS_CHECKING
  if (! in_bounds(i))
    throw Exception_IndexOutOfBounds(i,min_index(),max_index());
  if (! in_bounds(i+count-1))
    throw Exception_IndexOutOfBounds(i+count-1,min_index(),max_index());
#endif
    
  double* array = data_.data();
  unsigned j = 0;
  while (j < count) {
    array[i+j - min_index()] = xs[j];
    ++j;
  }
  recalc();
}

void
RealSet::clear()
{
  set_offset(0);
  data_.clear();
  sdata_.clear();
  mean_ = sumsq_ = 0;
  sortedness_ = 2; // constant
}

void
RealSet::append(const RealSet& ds)
{
  // clearly, this could be optimized...

  // By saving N before we iterate, we should properly handle
  // the case where &ds == this.
  const double* d = ds.data();
  const unsigned N = ds.size();
  for(unsigned i=0; i<N; ++i)
    add(d[i]);
}

/*
void
RealSet::apply(double (*fn)(double))
{
  double* d = data_.data();
  for(size_t i=0; i<size(); ++i)
    d[i] = fn(d[i]);
  recalc();
}
*/

void
RealSet::linear_transform(double a, double b)
{
  double* d = data_.data();
  const unsigned N = size();

  for(unsigned i=0; i<N; ++i) 
    d[i] = a*d[i]+b;

  
  double m1 = a*min_+b, m2 = a*max_+b;
  min_ = m1<m2 ? m1 : m2;
  max_ = m1<m2 ? m2 : m1;

  mean_ = a*mean_+b;
  sumsq_ *= a*a;
  if (a<0 && sortedness_ != 2)
    sortedness_ = -sortedness_;

  if (sdata_.size()) {
    double* s = sdata_.data();
    // linearly transform our sdata buffer
    for(unsigned i=0; i<N; ++i)
      s[i] = a*s[i]+b;

    // if a<0, reverse the sdata to preserve sortedness
    if (a<0) {
      for(unsigned i=0; i<N/2; ++i) {
	double t=s[i];
	s[i]=s[N-1-i];
	s[N-1-i]=t;
	}
    }
  }
}

void
RealSet::log_transform()
{
  // We should throw an exception here...
  if (min() <= 0) {
    clear();
    return;
  }

  const unsigned N = size();
  double* d = data_.data();
  for (unsigned i=0; i<N; ++i)
    d[i] = log(d[i]);

  if (have_sorted_data()) {
    double* sd = sdata_.data();
    for (unsigned i=0; i<N; ++i)
      sd[i] = log(sd[i]);
  }

  recalc_saving_sorted();
}

void
RealSet::exp_transform()
{
  const unsigned N = size();
  double* d = data_.data();
  for (unsigned i=0; i<N; ++i)
    d[i] = exp(d[i]);

  if (have_sorted_data()) {
    double* sd = sdata_.data();
    for (unsigned i=0; i<N; ++i)
      sd[i] = exp(sd[i]);
  }
  
  recalc_saving_sorted();
}

void
RealSet::logit_transform()
{
  // We should throw an exception here...
  if (min() <= 0 || max() >= 1) {
    clear();
    return;
  }

  // This could be optimized to preserve sorted data.
  double* d = data_.data();
  const unsigned N = size();
  for(unsigned i=0; i<N; ++i)
    d[i] = log(d[i]/(1-d[i]));

  recalc();
}

void
RealSet::fabs_transform()
{
  // This could be optimized to preserve sorted data.

  // Check for the cases that require less work
  if (max() <= 0) {
    linear_transform(-1, 0);
  } else if (min() < 0) {
    const unsigned N = size();
    double* d = data_.data();
    for(unsigned i=0; i<N; ++i)
      d[i] = fabs(d[i]);
    recalc();
  }
}

void
RealSet::deviations_transform(double y)
{
  double* d = data_.data();
  const unsigned N = size();
  for(unsigned i=0; i<N; ++i)
    d[i] = fabs(d[i]-y);
  recalc();
}

void
RealSet::reverse()
{
  if (sortedness_ == 2) return;

  double* d = data_.data();
  const unsigned N = size();

  for(unsigned i=0; i<N/2; ++i) {
    double t = d[i];
    d[i] = d[N-i-1];
    d[N-1-i] = t;
  }
  sortedness_ = -sortedness_;
}

void
RealSet::sort(int dir)
{
  // If we are already sorted properly, ignore
  if (sortedness_ == 2 || 
      (sortedness_ == 1 && dir >= 0) ||
      (sortedness_ == -1 && dir < 0))
    return;

  // If we have sorted data already, use it!
  if (dir >= 0 && sdata_.size()) {
    data_ = sdata_;
    sortedness_ = 1;
    return;
  }

  // If we are being asked to "opposite-sort" already-sorted data, do so
  // via reverse()
  if ((dir >= 0 && sortedness_ == -1) || (dir < 0 && sortedness_ == 1)) {
    reverse();
  } else if (dir >= 0) {
    // Otherwise there is no avoiding it, so just sort the data...
    double* d = data_.data();
    ::sort(d, d+size(), less<double>());
    sortedness_ = 1;
  } else {
    double* d = data_.data();
    ::sort(d, d+size(), greater<double>());
    sortedness_ = -1;
  }

  if (sortedness_ > 0)
    sdata_ = data_;
}

void
RealSet::scramble_explicit(Random& rnd)
{
  if (size() == 0 || sortedness_ == 2) return;

  rnd.scramble(data_.data(), size());

  recalc_sortedness();
}

void
RealSet::permute(const Permutation& p)
{
  if (size() != p.size())
    throw Exception("Permutation and data are not of the same size");
  
  double* d = data_.data();
  p.permute(d);

  recalc_sortedness();
}

void
RealSet::rank()
{
  pair<double,int>* rankdata = new pair<double,int>[size()];
  double* d = data_.data();
  const unsigned N = size();

  for(unsigned i1=0; i1<N; ++i1) {
    rankdata[i1].first = d[i1];
    rankdata[i1].second = i1;
  }

  ::sort(rankdata, rankdata+N, less< pair<double,int> >());

  // set ranks, handling ties by the usual convention
  unsigned count=1;
  for(unsigned i=0; i<N; /* increment down below */ ) {
    unsigned j=i+1;
    unsigned count2=0;
    while (j < N && are_equal(rankdata[i].first, rankdata[j].first)) {
      ++j;
      ++count2;
    }
    while (i != j)
      rankdata[i++].first = (2*count + count2)/2.0; // we increment i here
    count += 1+count2;
  }

  for(unsigned i=0; i<N; ++i)
    d[rankdata[i].second] = rankdata[i].first;

  recalc(); // This could be optimized...

  delete [] rankdata;
}

void
RealSet::standardize()
{
  const double m = mean();
  const double s = sdev();
  const unsigned N = size();
  double* d = data_.data();
  for(unsigned i=0; i<N; ++i)
    d[i] = (d[i]-m)/s;
  if (have_sorted_data()) {
    double* sd = sdata_.data();
    for(unsigned i=0; i<N; ++i)
      sd[i] = (sd[i]-m)/s;
  }
  recalc_saving_sorted();
}

Permutation
RealSet::sorting_permutation(int dir) const
{
  Permutation p;
  const unsigned N = size();

  if (sortedness_ == 2 ||
      (dir >= 0 && sortedness_ == 1) ||
      (dir < 0 && sortedness_ == -1)) {

    p.set_identity(N);

  } else if ((dir > 0 && sortedness_ == -1) ||
	     (dir < 0 && sortedness_ == 1)) {

    p.set_reverse(N);

  } else {

    pair<double,unsigned>* tmp = new pair<double,unsigned>[N];
    unsigned* tmp2 = new unsigned[N];
    const double* d = data_.data();
    for (unsigned i=0; i<N; ++i) {
      tmp[i].first = d[i];
      tmp[i].second = i;
    }

    if (dir >= 0) 
      ::sort(tmp, tmp+N, less< pair<double,unsigned> >());
    else
      ::sort(tmp, tmp+N, greater< pair<double,unsigned> >());

    for(unsigned i=0; i<N; ++i)
      tmp2[tmp[i].second] = i;

    p.initialize(size(), tmp2);
    delete [] tmp;
    delete [] tmp2;
  }

  return p;
}

void
RealSet::add_compressed(const string& s)
{
  const char* buffer = s.c_str();
  const char* eob = buffer + s.size();
  while (buffer < eob) 
    add(decode_double(buffer));
}

void
RealSet::write_xml(ostream& out, bool compress) const
{
  out << "<realset label=\"" << label() << "\" size=" << size();
  if (compress)
    out << " compressed";
  out << ">" << endl;

  const double* d = data_.data();
  const unsigned N = size();

  if (compress) {
    // This is bigger than necessary.
    char buffer[16];
    memset(buffer,0,16);

    for(unsigned i=0; i<N; ++i) {
      encode_double(d[i], buffer);
      out << buffer;
      if (i % 7 == 6)
	out << endl;
    }
    if (N % 7)
      out << endl;
  } else {
    int old_prec = out.precision();
    out.precision(17);
    for(unsigned i=0; i<N; ++i)
      out << d[i] << endl;
    out.precision(old_prec);
  }

  out << "</realset>" << endl;
}

void
RealSet::update_add(double x)
{
  // update statistics /////

  const unsigned N = size();

  if (N == 0 || x < min_)
    min_ = x;
  if (N == 0 || x > max_)
    max_ = x;

  double old_mean = mean_;
  mean_ += (x - mean_)/(N+1);
  if (N > 0) {
    sumsq_ += (x-mean_)*(x-old_mean); // cool, huh?

    // Update sortedness flag
    if (sortedness_) {
      const double* d = data_.data_const();
      double prev = d[N-1];
      if (sortedness_ == 2) { // constant
	if (prev < x)
	  sortedness_ = 1;
	else if (prev > x)
	  sortedness_ = -1;
      } else if (sortedness_ == 1) { // ascending
	if (prev > x)
	  sortedness_ = 0;
      } else if (sortedness_ == -1) { // descending
	if (prev < x)
	  sortedness_ = 0;
      }
    }
  }
}

void
RealSet::update_remove(double x)
{
  const unsigned N = size()-1;
  double old_mean = mean_;
  mean_ += (mean_ - x)/N;
  if (N > 0)
    sumsq_ -= (x-old_mean)*(x-mean_);

  if (N != 0) {
    const double* d = data_.data_const();
    const unsigned NN = size();
    if (min_ == x) {
      bool skip_x = true;
      min_ = d[0];
      if (x == d[0]) {
	min_ = d[1];
	skip_x = false;
      }
      for(unsigned i=1; i<NN; ++i) {
	if (d[i] == x && skip_x) {
	  skip_x = false;
	  continue;
	}
	if (min_ > d[i])
	  min_ = d[i];
      }
    }
    if (max_ == x) {
      bool skip_x = true;
      max_ = d[0];
      if (x == d[0]) {
	max_ = d[1];
	skip_x = false;
      }
      for(unsigned i=1; i<NN; ++i) {
	if (d[i] == x && skip_x) {
	  skip_x = false;
	  continue;
	}
	if (max_ < d[i])
	  max_ = d[i];
      }
    }
  }
  // Leaves sortedness in fubared state.
}

// There is some code duplication between these and add(), but calling a
// recalc() should be a lot more efficient than just repeatedly add()-ing
// the numbers if you've been fiddling directly with data_.

void
RealSet::recalc_sortedness()
{
  sortedness_ = 2;
  const double* d = data_.data_const();
  const unsigned N = data_.size();

  for(unsigned i=1; i<N && sortedness_; ++i) {
    double x = d[i];
    double prev = d[i-1];
    if (sortedness_ == 2) {
      if (prev < x)
	sortedness_ = 1;
      else if (prev > x)
	sortedness_ = -1;
    } else if (sortedness_ == 1) {
      if (prev > x)
	sortedness_ = 0;
    } else if (sortedness_ == -1) {
      if (prev < x)
	sortedness_ = 0;
    }
  }
}

void
RealSet::recalc()
{
  recalc_saving_sorted();
  sdata_.clear();
}

void
RealSet::recalc_saving_sorted()
{
  mean_ = sumsq_ = 0;
  sortedness_ = 2;
  if (size() == 0) return;

  const double* d = data_.data_const();
  const unsigned N = data_.size();

  min_ = max_ = d[0];
  double old_mean;
  for (unsigned i=0; i<N; ++i) {
    double x = d[i];
    if (min_ > x) min_ = x;
    if (max_ < x) max_ = x;
    old_mean = mean_;
    mean_ += (x - mean_)/(i+1);
    if (i>0) {
      sumsq_ += (x-mean_)*(x-old_mean);
      if (sortedness_) {
	double prev = d[i-1];
	if (sortedness_ == 2) {
	  if (prev < x)
	    sortedness_ = 1;
	  else if (prev > x)
	    sortedness_ = -1;
	} else if (sortedness_ == 1) {
	  if (prev > x)
	    sortedness_ = 0;
	} else if (sortedness_ == -1) {
	  if (prev < x)
	    sortedness_ = 0;
	}
      }
    }
  }

  sdata_.clear();
}

void
RealSet::copy(const RealSet& ds)
{
  if (this == &ds) return; // can't copy ourselves.

  clear();
  set_label(ds.label());
  data_ = ds.data_;
  sdata_ = ds.sdata_;
  min_ = ds.min_;
  max_ = ds.max_;
  mean_ = ds.mean_;
  sumsq_ = ds.sumsq_;
  sortedness_ = ds.sortedness_;
  epsilon_ = ds.epsilon_;
}



// $Id: RealSet.cpp,v 1.13 1999/07/20 20:52:09 trow Exp $

