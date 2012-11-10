// This is -*- C++ -*-
// $Id: Random.h,v 1.3 1999/07/07 05:09:08 trow Exp $

/* 
 * Random.h
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

#ifndef _INC_RANDOM_H
#define _INC_RANDOM_H

#include <limits.h>
#include <vector>
#include <algorithm>

using namespace std;

const double ONE_OVER_UINT_MAX = 1.0/UINT_MAX;
const unsigned HALF_UINT_MAX = UINT_MAX/2;

class Random {
public:
  Random() : mt_(0), mti_(0) { }
  ~Random() { delete [] mt_; }

  void seed(unsigned);

  unsigned random();
  void random_bulk(unsigned*, size_t);

  int random_integer(int a, int b) {
    unsigned r;
    do { r = random(); } while (r == UINT_MAX);
    return a + (int)((b-a+1)*(r*ONE_OVER_UINT_MAX));
  }
  void random_integer_bulk(int a, int b, int*, size_t);

  // Picks doubles in the interval [0,1] or [a,b]
  double random_uniform() { return random()*ONE_OVER_UINT_MAX; }
  double random_uniform(double a, double b) { return a+(b-a)*random_uniform();}
  void random_uniform_bulk(double*, size_t);
  void random_uniform_bulk(double a, double b, double*, size_t);

  // Picks doubles in the interval (0,1) or (a,b)
  double random_uniform_open() {
    unsigned r;
    do { r = random(); } while (r == 0 || r == UINT_MAX);
    return r * ONE_OVER_UINT_MAX;
  }
  double random_uniform_open(double a, double b) {
    return a+(b-a)*random_uniform_open();
  }
  void random_uniform_open_bulk(double*, size_t);
  void random_uniform_open_bulk(double a, double b, double* , size_t);
  
  double random_normal();
  double random_normal(double m, double sd) { return m+sd*random_normal(); }
  void random_normal_bulk(double*, size_t);
  void random_normal_bulk(double m, double sd, double*, size_t);

  bool random_bool() { return random() < HALF_UINT_MAX; }
  bool random_bool(double p_true) { return random_uniform() < p_true; }

  // Things will end badly if operator= doesn't work properly for class X.
  template<class X> void scramble(X* data, size_t N)
  {
    if (N < 2) return;
    for(size_t i=0; i<N-1; ++i) {
      size_t j = random_integer(i, N-1);
      swap(data[i], data[j]);
    }
  }

  template<class X> void scramble(vector<X>& data)
  {
    size_t N = data.size();
    if (N < 2) return;
    for(size_t i=0; i<N-1; ++i) {
      size_t j = random_integer(i, N-1);
      swap< vector<X> >((vector<X> &)data[i], (vector<X> &)data[j]);
    }
  }
    
private:
  void stir();

  unsigned* mt_;
  unsigned mti_;

  double extra_normal_;
  bool have_extra_normal_;
};

// Yikes!  Global data!
extern Random common_random;

#endif // _INC_RANDOM_H

// $Id: Random.h,v 1.3 1999/07/07 05:09:08 trow Exp $
