// This is -*- C++ -*-
// $Id: StringSet.h,v 1.8 1999/07/21 08:53:16 alstrup Exp $

/* 
 * StringSet.h
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

#ifndef _INC_STRINGSET_H
#define _INC_STRINGSET_H

#include <vector>
#include "DataSet.h"

/*
 * StringSet correctly derives from DataSet, not from DataSet_Typed<string>,
 * since it doesn't need a string->type translation layer.
 */

class StringSet : public DataSet {
public:
  static const DataSet::type_t typecode;

  StringSet() : DataSet(typecode) {
	  set_offset(0);
  }
  StringSet(const StringSet& s) : DataSet(typecode) { 
    data_ = s.data_; set_label(s.label());
	set_offset(s.min_index());
  }
  ~StringSet() { }
  StringSet& operator=(const StringSet& s) {
    if (&s != this) 
      data_ = s.data_;
    return *this;
  }

  DataSet * clone() const {
    return new StringSet(*this);
  }

  bool support_missing() const { return true; }

  unsigned size() const { return data_.size(); }
  void reserve(unsigned N) { data_.reserve(N); } 
  void resize(unsigned N);

  void add_string(const string& s) { data_.push_back(s); }
  void add_string_at(int i, const string& s) {
    data_.insert(data_.begin() + i - min_index(), s);
  }
  void set_string(int i, const string& s) { data_[i - min_index()] = s; }
  string as_string(int i) const { return data_[i - min_index()]; }
  const string& get_string(int i) const { return data_[i - min_index()]; }

  void remove(int i) { data_.erase(data_.begin() + i - min_index()); }
  void remove(int b, int e) {
    data_.erase(data_.begin() + b - min_index(),
		data_.begin() + e - min_index());
  }
  void clear() { data_.clear(); }

  void permute(const Permutation&);
  void scramble_explicit(Random&);
  void reverse();

  // Length of the longest string
  size_t max_length() const;

private:
  vector<string> data_;
};

#endif
