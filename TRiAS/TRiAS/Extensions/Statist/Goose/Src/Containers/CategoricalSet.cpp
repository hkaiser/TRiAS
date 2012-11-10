// This is -*- C++ -*-
// $Id: CategoricalSet.cpp,v 1.5 1999/07/15 17:43:42 trow Exp $

/* 
 * CategoricalSet.cpp
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
#include "CategoricalSet.h"

CategoricalSet::CategoricalSet(const Category& c) :
  DataSet_Typed<catcode_t>(314159),cat_(c)
{
  for(size_t i=0; i<cat_.size(); ++i)
    freq_.push_back(0);
}

CategoricalSet::~CategoricalSet()
{ }

CategoricalSet&
CategoricalSet::operator=(const CategoricalSet& cs)
{
  cat_ = cs.cat_;
  data_ = cs.data_;
  freq_ = cs.freq_;
  return *this;
}

void
CategoricalSet::reserve(unsigned R)
{
  data_.reserve(R);
}

void
CategoricalSet::resize(unsigned N)
{
  if (size() > N)
    remove(N, size()-1);
  else if (size() == N)
    clear();
  else
    throw Exception("\"Growing\" resize not defined for CategoricalSet");
}

void
CategoricalSet::add(catcode_t c)
{
  ++freq_[c];
  data_.add(c);
}

void
CategoricalSet::add_at(int i, catcode_t c)
{
  ++freq_[c];
  data_.add_at(i - min_index(), c);
}

void
CategoricalSet::set(int i, catcode_t c)
{
  --freq_[data_[i - min_index()]];
  ++freq_[c];
  data_[i - min_index()] = c;
}

catcode_t
CategoricalSet::data(int i) const
{
  return data_[i - min_index()];
}

void
CategoricalSet::remove(int i)
{
  --freq_[data_[i - min_index()]];
  data_.remove_at(i - min_index());
}

void
CategoricalSet::remove(int b, int e)
{
  for(int i=b; i<=e; ++i)
    --freq_[data_[i-min_index()]];
  data_.remove_at(b-min_index(), e-min_index());
}

void
CategoricalSet::clear()
{
  data_.clear();
  for(unsigned i=0; i<freq_.size(); ++i)
    freq_[i] = 0;
}

void
CategoricalSet::sort(int d)
{
  // Since we know the frequencies, we don't even need to do a sort.
  unsigned i = (d>=0) ? 0 : size()-1;
  for(unsigned j=0; j<freq_.size(); ++j)
    for(unsigned k=0; k<freq_[j]; ++k) {
      data_[i] = (catcode_t)j;
      (d>=0) ? ++i : --i;
    }
}

void
CategoricalSet::permute(const Permutation& p)
{
  if (size() != p.size())
    throw Exception("Permutation and data are not of the same size");

  p.permute(data_.data());
}

void
CategoricalSet::scramble_explicit(Random& rng)
{
  rng.scramble(data_.data(), data_.size());
}

void
CategoricalSet::reverse()
{
  data_.reverse();
}
// $Id: CategoricalSet.cpp,v 1.5 1999/07/15 17:43:42 trow Exp $
