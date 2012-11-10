// This is -*- C++ -*-
// $Id: Permutation.cpp,v 1.4 1999/07/21 08:53:18 alstrup Exp $

/* 
 * Permutation.cpp
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
#include <iostream>
#include <string>
#include "Exception.h"
#include "Random.h"
#include "Permutation.h"

Permutation::Permutation()
{ }

Permutation::Permutation(unsigned N)
{
  set_identity(N);
}

Permutation::Permutation(const Permutation& p) :
  perm_(p.perm_), cyclerep_(p.cyclerep_)
{ }

Permutation&
Permutation::operator=(const Permutation& p)
{
  perm_ = p.perm_;
  cyclerep_ = p.cyclerep_;
  return *this;
}

void
Permutation::initialize(unsigned N, unsigned* d)
{
  char* seen = new char[N];
  memset(seen, 0, N*sizeof(char));

  cyclerep_.clear();
  perm_.clear();
  perm_.reserve(N);
  for(unsigned i=0; i<N; ++i) {
    
    // Throw if we are being fed something that isn't a
    // permutation on 0...(N-1)
    if (d[i] >= N)
      throw Exception_IndexOutOfBounds(d[i],0,N-1);
    if (seen[d[i]])
      throw Exception("Repeated value in permutation definition.");
    seen[d[i]] = 1;
    perm_.add(d[i]);
  }
  delete [] seen;
}

unsigned
Permutation::orbit_size(unsigned i) const
{
  unsigned count=0;
  unsigned j=i;
  do {
    ++count;
    j = map(j);
  } while (j != i);
  return count;
}

// The order of a permutation = the lcm of the size of the orbits
unsigned
Permutation::order() const
{
  calc_cycles();
  unsigned lcm = 1;
  for(unsigned i=0; i<cyclerep_.size(); ++i) {
    unsigned os = orbit_size((cyclerep_.data())[i]);
    
    // Euclid is the man
    unsigned a = lcm < os ? lcm : os;
    unsigned b = lcm < os ? os : lcm;
    unsigned r;
    while ((r = b % a) != 0) {
      b = a;
      a = r;
    }

    lcm = lcm*os/a;
  }

  return lcm;
}

void
Permutation::set_identity(unsigned N)
{
  if (N == 0) throw Exception_IllegalSize(0);

  perm_.clear();
  perm_.reserve(N);
  for(unsigned i=0; i<N; ++i)
    perm_.add(i);
  cyclerep_ = perm_;
}

void
Permutation::set_shift(unsigned N, int k)
{
  if (N == 0) throw Exception_IllegalSize(0);

  perm_.clear();
  perm_.reserve(N);
  while (k < 0) k += N;
  for(unsigned i=0; i<N; ++i)
    perm_.add((i+k) % N);
  
  cyclerep_.clear();
}

// The reverse permutation (1 2 3 .. N -> N .. 3 2 1) is pretty much the
// worst case in terms of our cyclerep_ notation, as it consists of N/2
// disjoint transpositions.  Ugh.
void
Permutation::set_reverse(unsigned N)
{
  if (N == 0) throw Exception_IllegalSize(0);

  perm_.clear();
  perm_.reserve(N);
  for(unsigned i=0; i<N; ++i)
    perm_.add(N-1-i);

  cyclerep_.clear();
}

void
Permutation::scramble_explicit(Random& rnd)
{
  if (size() < 2) return;
  unsigned* d = perm_.data();
  for(unsigned i=0; i<size()-1; ++i) {
    unsigned j = rnd.random_integer(i,size()-1);
    if (i != j) {
      unsigned t = d[i];
      d[i] = d[j];
      d[j] = t;
    }
  }
  cyclerep_.clear();
}

void
Permutation::pretranspose(unsigned i, unsigned j)
{
  if (size() == 0)
    throw Exception_IllegalSize(0);
  if (i >= size())
    throw Exception_IndexOutOfBounds(i,0,size()-1);
  if (j >= size())
    throw Exception_IndexOutOfBounds(j,0,size()-1);

  if (i == j) return;

  unsigned* d = perm_.data();
  unsigned t = d[i];
  d[i] = d[j];
  d[j] = t;
}

void
Permutation::posttranspose(unsigned i, unsigned j)
{
  if (size() == 0)
    throw Exception_IllegalSize(0);
  if (i >= size())
    throw Exception_IndexOutOfBounds(i,0,size()-1);
  if (j >= size())
    throw Exception_IndexOutOfBounds(j,0,size()-1);

  if (i == j) return;

  unsigned* d = perm_.data();
  unsigned n=0, N=size();
  while (n<N && d[n] != i && d[n] != j) ++n;
  if (n == N) throw Exception_InternalError();

  if (d[n] == i) { // Found i, search for instance of j.
    d[n] = j;
    ++n;
    while (n<N && d[n] != j) ++n;
    d[n] = i;
  } else if (d[n] == j) { // Found j, search for instance of i.
    d[n] = i;
    ++n;
    while (n<N && d[n] != i) ++n;
    d[n] = j;
  } else {
    throw Exception_InternalError();
  }
}

void
Permutation::precompose(const Permutation& p)
{
  if (size() != p.size())
    throw Exception_SizesDoNotMatch();

  unsigned* tmp = new unsigned[size()];
  for(unsigned i=0; i<size(); ++i)
    tmp[i] = map(p.map(i));

  unsigned* d = perm_.data();
  for(unsigned i=0; i<size(); ++i)
    d[i] = tmp[i];

  delete [] tmp;
  cyclerep_.clear();
}

void
Permutation::postcompose(const Permutation& p)
{
  if (size() != p.size())
    throw Exception_SizesDoNotMatch();

  unsigned* tmp = new unsigned[size()];
  for(unsigned i=0; i<size(); ++i)
    tmp[i] = p.map(map(i));

  unsigned* d = perm_.data();
  for(unsigned i=0; i<size(); ++i)
    d[i] = tmp[i];

  delete [] tmp;
  cyclerep_.clear();
}

void
Permutation::invert()
{
  unsigned* tmp = new unsigned[size()];
  for(unsigned i=0; i<size(); ++i)
    tmp[map(i)] = i;

  unsigned* d = perm_.data();
  for(unsigned i=0; i<size(); ++i)
    d[i] = tmp[i];

  delete [] tmp;
  // cyclerep_ is invariant under inversion...
}

void
Permutation::spew(ostream& out) const
{
  for(unsigned i=0; i<size(); ++i)
    out << i << " => " << map(i) << endl;
}

void
Permutation::spew_cycles(ostream& out) const
{
  calc_cycles();
  bool id = true;
  for(unsigned i=0; i<cyclerep_.size(); ++i) {
    unsigned start = (cyclerep_.data())[i];
    if (map(start) != start) { // don't display singleton cycles
      id = false;
      unsigned j = start;
      out << "( ";
      do {
	out << j << " ";
	j = map(j);
      } while (j != start);
      out << ")";
    }
  }
  if (id)
    out << "(identity)";
}

// For a random permutation, the average # of cycles is very small,
// even for permutations on very large sets.  (It would be interesting
// to know the asymptotics of this number as N -> infinity.  If there
// are any group theorists or combinatorics people out there reading
// this who know the answer, drop me an e-mail at trow@emccta.com and
// let me know...
void
Permutation::calc_cycles() const
{
  if (cyclerep_.size())
    return;

  RCArray<unsigned> proxy;
  // Better to use char than bool, since bool is the size of an int on
  // some architectures...
  char* seen = new char[size()];
  memset(seen, 0, size()*sizeof(char)); // sizeof(char)==1 in ANSI, no?
  for(unsigned i=0; i<size(); ++i) {
    if (! seen[i]) {
      proxy.add(i);
      unsigned j=i;
      do {
	seen[j] = 1;
	j = map(j);
      } while (! seen[j]);
    }
  }
  delete [] seen;

  // It isn't nice to fool the compiler!
  ((Permutation*)this)->cyclerep_ = proxy;
}


// $Id: Permutation.cpp,v 1.4 1999/07/21 08:53:18 alstrup Exp $

