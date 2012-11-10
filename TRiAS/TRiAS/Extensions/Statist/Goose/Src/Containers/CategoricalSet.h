// This is -*- C++ -*-
// $Id: CategoricalSet.h,v 1.4 1999/07/15 17:43:42 trow Exp $

/* 
 * CategoricalSet.h
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


#ifndef _INC_CATEGORICALSET_H
#define _INC_CATEGORICALSET_H

#include <RCArray.h>
#include <Permutation.h>
#include <Exception.h>
#include "DataSet.h"
#include "Category.h"

class CategoricalSet : public DataSet_Typed<catcode_t> {
public:
  CategoricalSet(const Category&);
  CategoricalSet(const CategoricalSet&);
  virtual ~CategoricalSet();

  CategoricalSet& operator=(const CategoricalSet&);

  const Category& category() const { return cat_; }

  unsigned size() const { return data_.size(); }
  void reserve(unsigned R);
  void resize(unsigned N);

  void add(catcode_t);
  void add_at(int, catcode_t);
  void set(int, catcode_t);
  catcode_t data(int) const;

  void remove(int);
  void remove(int b, int e);
  void clear();
    
  void sort(int dir = 1);
  Permutation sorting_permutation(int dir = 1) const;
  void permute(const Permutation&);
  void scramble_explicit(Random&);
  void reverse();

  
  unsigned frequency(catcode_t c) const { return freq_[c]; }
  double proportion(catcode_t c) const { return freq_[c]/(double)size(); }

  unsigned string_frequency(const string& s) const {
    return frequency(from_string(s));
  }
  double string_proportion(const string& s) const {
    return proportion(from_string(s));
  }
  
protected:
  string to_string(catcode_t c) const { return cat_.convert(c); }
  catcode_t from_string(const string& s) const { return cat_.convert(s); }

private:
  Category cat_;
  RCArray<catcode_t> data_;
  vector<unsigned> freq_;
};

#endif // _INC_CATEGORICALSET_H

// $Id: CategoricalSet.h,v 1.4 1999/07/15 17:43:42 trow Exp $
