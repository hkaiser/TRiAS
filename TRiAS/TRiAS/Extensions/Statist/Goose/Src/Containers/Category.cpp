// This is -*- C++ -*-
// $Id: Category.cpp,v 1.2 1999/07/20 08:34:26 alstrup Exp $

/* Category.cpp
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


#include <config.h>
#include <Exception.h>
#include "Category.h"

const char* default_label = "Unlabelled Category";

Category::Category() : label_(default_label), lock_(false), strict_(false)
{ }

Category::Category(const string& s) : label_(s), lock_(false), strict_(false)
{ }

Category::Category(const vector<string>& c) : 
  label_(default_label), lock_(false), strict_(false)
{
  add(c);
}

Category::Category(const string& s, const vector<string>& c) :
  label_(s), lock_(false), strict_(false)
{
  add(c);
}

Category::Category(const Category& c) : label_(c.label_),
  names_(c.names_), codes_(c.codes_), lock_(true), strict_(c.strict_)
{
  if (! c.locked())
    throw Exception("Illegal copy on unlocked Category");
}

Category::~Category()
{

}

bool
Category::have_element(const string& s) const
{
  return codes_.find(s) != codes_.end();
}

bool
Category::have_element(catcode_t c) const
{
  return c >= 0 && c < (int)names_.size();
}

catcode_t
Category::convert(const string& s) const
{
  map<string, catcode_t>::const_iterator i = codes_.find(s);
  if (i != codes_.end())
    return (*i).second;
  if (strict())
    throw Exception("Unknown category element: " + s);
  return ILLEGAL_CATCODE;
}

const string&
Category::convert(catcode_t c) const
{
  static string out_of_range = "[Out-of-range category code]";
  if (!have_element(c)) {
    if (strict())
      throw Exception("Out-of-range category code");
    return out_of_range;
  }
  return names_[c];
}


catcode_t
Category::add(const string& s)
{
  if (have_element(s)) {
    if (strict())
      throw Exception("Duplicate category element: " + s);
    return convert(s);
  }

  catcode_t c = names_.size();
  codes_[s] = c;
  names_.push_back(s);
  return c;
}

void
Category::add(const vector<string>& v)
{
  for(size_t i=0; i<v.size(); ++i)
    add(v[i]);
}

// $Id: Category.cpp,v 1.2 1999/07/20 08:34:26 alstrup Exp $
