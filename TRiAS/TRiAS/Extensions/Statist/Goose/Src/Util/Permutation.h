// This is -*- C++ -*-
// $Id: Permutation.h,v 1.4 1999/07/15 17:44:13 trow Exp $

/* 
 * Permutation.h
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

#ifndef _INC_PERMUTATION_H
#define _INC_PERMUTATION_H

#include "RCArray.h"
#include "Random.h"
#include "Exception.h"

using namespace std;

class Permutation {
public:
  Permutation();
  Permutation(unsigned size);
  Permutation(const Permutation&);

  Permutation& operator=(const Permutation&);
  
  unsigned size() const { return perm_.size(); }
  const unsigned* map() const { return perm_.data(); }
  // note: no bounds checking
  unsigned map(unsigned i) const { return (perm_.data())[i]; }

  void initialize(unsigned N, unsigned*);

  unsigned cycle_count() const { calc_cycles(); return cyclerep_.size(); }
  unsigned orbit_size(unsigned) const;
  unsigned order() const; // In the sense of group theory...

  void set_identity(unsigned size);
  void set_shift(unsigned size, int k);
  void set_reverse(unsigned size);
  void scramble_explicit(Random&);
  void scramble() { scramble_explicit(common_random); }

  void pretranspose(unsigned i, unsigned j);
  void posttranspose(unsigned i, unsigned j);
  void precompose(const Permutation&);
  void postcompose(const Permutation&);
  void invert();

  // WARNING: We assume that this points to an array of at least size()
  // X's.  X should be a type that can be copied by operator=().
  // The nice thing about using our cycle decomposition is that we can
  // permute the array in O(N) time without having to do any buffer copies.
  template<class X>
  void permute(X* x) const {
    calc_cycles();
    for(unsigned i=0; i<cyclerep_.size(); ++i) {
      unsigned j = (cyclerep_.data())[i];
      if (j != map(j)) {
	unsigned start = j;
	X tmp = x[j];
      do {
	X tmp2 = x[map(j)];
	x[map(j)] = tmp;
	tmp = tmp2;
      } while ((j = map(j)) != start);
      }
    }
  }

  template<class X>
  void permute(vector<X>& v) const {
    if (size() != v.size())
      throw Exception_SizesDoNotMatch();
    // We assume that vector is implemented in one contiguous block of
    // memory...
    permute(&(v[0]));
  }

  // some output that is useful for debugging (and not much else)
  void spew(ostream& out) const;
  void spew_cycles(ostream& out) const;

private:
  void calc_cycles() const;

  RCArray<unsigned> perm_;
  RCArray<unsigned> cyclerep_;
};

#endif // _INC_PERMUTATION_H

// $Id: Permutation.h,v 1.4 1999/07/15 17:44:13 trow Exp $
