// This is -*- C++ -*-
// $Id: DateSet.cpp,v 1.5 1999/07/15 17:43:42 trow Exp $

/* 
 * DateSet.cpp
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
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

#ifndef WIN32

#include <algorithm>
#include <Permutation.h>
#include <Random.h>
#include "DateSet.h"

const DataSet::type_t DateSet::typecode = 0xdddddd;

void
DateSet::add(GDate dt)
{
  data_.add(dt);
}

void
DateSet::add_at(int i, GDate dt)
{
  data_.add_at(i - min_index(), dt);
}

void
DateSet::set(int i, GDate dt)
{
  data_[i - min_index()] = dt;
}

GDate
DateSet::data(int i) const
{
  return data_[i - min_index()];
}

void
DateSet::remove(int i)
{
  data_.remove_at(i - min_index());
}

void
DateSet::remove(int b, int e)
{
  data_.remove_at(b - min_index(), e - min_index());
}

void
DateSet::clear()
{
  data_.clear();
}

class GDate_cmp {
public:
  bool operator()(const GDate& a, const GDate& b) const {
    return g_date_compare((GDate*)&a,(GDate*)&b) == -1;
  }
};

void
DateSet::sort()
{
  if (!sorted_) 
    ::sort(data_.data(), data_.data()+data_.size(), GDate_cmp());
  sorted_ = true;
}

void
DateSet::permute(const Permutation& p)
{
  if (p.size() != size())
    throw Exception_SizesDoNotMatch();
  p.permute(data_.data());
}

void
DateSet::scramble_explicit(Random& rnd)
{
  rnd.scramble(data_.data(), data_.size());
}

void
DateSet::reverse()
{
  data_.reverse();
}

string
DateSet::to_string(GDate dt) const
{
  gchar buffer[32];
  g_date_strftime(buffer, 32, "%Y-%m-%d", &dt); // Hard-wired, for now...
  return string(buffer);
}

GDate
DateSet::from_string(const string& str) const
{
  GDate dt;
  g_date_set_parse(&dt, str.c_str());
  return dt;
}

#endif

// $Id: DateSet.cpp,v 1.5 1999/07/15 17:43:42 trow Exp $
