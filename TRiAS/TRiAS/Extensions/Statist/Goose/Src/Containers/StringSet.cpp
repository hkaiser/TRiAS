// This is -*- C++ -*-
// $Id: StringSet.cpp,v 1.5 1999/07/15 17:43:42 trow Exp $

/* 
 * StringSet.cpp
 *
 * Copyright (C) 1998 Asger Alstrup Nielsen
 *
 * Developed by Asger Alstrup Nielsen <alstrup@diku.dk>
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
#include "Exception.h"
#include "Permutation.h"
#include "StringSet.h"

const DataSet::type_t StringSet::typecode = 0xaaaaaa;

void
StringSet::resize(unsigned N)
{
  if (size() > N) {
    remove(N, size());
  } else {
    while(size() < N)
      add_string(string());
  }
}

void
StringSet::permute(const Permutation& p)
{
  if (size() != p.size())
    throw Exception("Permutation and data are not of the same size");

  p.permute(data_);
}

void
StringSet::scramble_explicit(Random& rnd)
{
  rnd.scramble(data_);
}

void
StringSet::reverse()
{
  size_t N = data_.size();
  size_t N2 = N/2;
  for(size_t i=0; i<N2; ++i) {
    string t = data_[i];
    data_[i] = data_[N-1-i];
    data_[N-1-i] = t;
  }
}

size_t
StringSet::max_length() const
{
  size_t max = 0;
  for(size_t i=0; i<data_.size(); ++i) {
    size_t len = data_[i].length();
    if (len > max) max = len;
  }
  return max;
}
