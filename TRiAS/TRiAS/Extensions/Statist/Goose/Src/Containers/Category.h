// This is -*- C++ -*-
// $Id: Category.h,v 1.2 1999/07/15 17:43:42 trow Exp $

/* Category.h
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


#ifndef _INC_CATEGORY_H
#define _INC_CATEGORY_H

#include <config.h>
#include <string>
#include <map>
#include <vector>

typedef int catcode_t;
const int ILLEGAL_CATCODE = -1;

class Category {
public:
  Category();
  Category(const string&);
  Category(const vector<string>&);
  Category(const string&, const vector<string>&);
  Category(const Category&);
  ~Category();

  unsigned size() const { return names_.size(); }

  typedef vector<string>::const_iterator const_iterator;
  const_iterator begin() const { return names_.begin(); }
  const_iterator end() const { return names_.end(); }

  bool have_element(const string&) const;
  bool have_element(catcode_t) const;

  catcode_t convert(const string&) const;
  const string& convert(catcode_t) const;

  catcode_t add(const string&);
  void add(const vector<string>&);

  void lock() { lock_ = true; }
  bool locked() const { return lock_; }
  
  bool strict() const { return strict_; }
  bool strict(bool x) { return strict_ = x; }

private:
  string label_;
  vector<string> names_;
  map<string, catcode_t> codes_;
  bool lock_, strict_;
};

#endif // _INC_CATEGORY_H

// $Id: Category.h,v 1.2 1999/07/15 17:43:42 trow Exp $
