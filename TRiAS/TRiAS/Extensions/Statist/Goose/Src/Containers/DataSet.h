// This is -*- C++ -*-
// $Id: DataSet.h,v 1.7 1999/07/20 21:20:04 trow Exp $

/* 
 * DataSet.h
 *
 * Copyright (C) 1998, 1999 Asger Alstrup Nielsen
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

#ifndef _INC_DATASET_H
#define _INC_DATASET_H

#include <string>
#include "Random.h"

//using std::string;

class Permutation;

/*
 * Base class for container sets.
 */
class DataSet {
public:
  
  virtual ~DataSet() { }

  // Method to clone a DataSet
  virtual DataSet * clone() const = 0;

  // Does this set support missing elements in the middle?
  virtual bool support_missing() const { return false; }

  const string& label() const { return label_; }
  void set_label(string const & s) { label_ = s; }

  virtual unsigned size() const = 0;
  int offset() const { return offset_; }
  int min_index() const { return offset_; }
  int max_index() const { return offset_ + size() - 1; }
  void set_offset(int off) { offset_ = off; }
  void shift_offset(int delta) { offset_ += delta; }

  bool in_bounds(int i) const { return min_index() <= i && i <= max_index(); }

  virtual bool empty() const { return size() == 0; }

  // Make sure we have allocated room for at least N entries
  virtual void reserve(unsigned N) = 0;

  // Resize the set to be exactly N entries
  virtual void resize(unsigned N) = 0;

  // String interface
  virtual void add_string(const string&) = 0;
  virtual void add_string_at(int index, const string&) = 0;
  virtual void set_string(int index, const string&) = 0;
  // Get i-th elem as a canonical string
  virtual string as_string(int index) const = 0;

  // Removal interface
  virtual void remove(int index) = 0;
  virtual void remove(int begin, int end) = 0;
  virtual void clear() = 0;

  // STL-ish functions & synonyms
  virtual void erase(int i) { remove(i); }
  virtual void erase(int i, unsigned j) { remove(i, j); }
  virtual void push_back(const string& s) { add_string(s); }
  virtual void pop_back() { if (!empty()) remove(size()-1); }

  // Methods to rearrange our data
  virtual void permute(const Permutation&) = 0;
  virtual void scramble_explicit(Random&) = 0;
  void scramble() { scramble_explicit(common_random); }
  virtual void reverse() = 0;

  // Useful for debugging
  virtual void spew(ostream& out, char sep = ' ') const;

  // Runtime type flags. Woo-hoo!
  typedef unsigned int type_t;

  type_t type() const { return type_; }

  static const type_t invalid_typecode;
  static int default_offset() { return default_offset_; }
  static void set_default_offset(int x) { default_offset_ = x; }
  
protected:
  DataSet(type_t type) : type_(type), offset_(default_offset_) {}

private:
  string label_;
  const type_t type_;

  int offset_;
  static int default_offset_;
};

/*
 * Extends a DataSet with a typed interface
 */
template<class X>
class DataSet_Typed : public DataSet {
public:
  typedef DataSet_Typed<X> dataset_type;
  typedef X value_type;

  DataSet_Typed(DataSet::type_t type) : DataSet(type) {}
  virtual ~DataSet_Typed() { }

  // Typed add interface
  virtual void add(X) = 0;
  virtual void add_at(int index, X) = 0;
  virtual void set(int index, X) = 0;
  virtual X data(int i) const = 0;

  // STL-ish synonyms
  virtual void push_back(X x) { add(x); }

  // Implementation of string add interface
  // Maybe these should have bounds checking?
  virtual void add_string(const string& s) { add(from_string(s)); }
  virtual void add_string_at(int i, const string& s) { add_at(i, from_string(s)); }
  virtual void set_string(int i, const string& s) { set(i, from_string(s)); }
  virtual string as_string(int i) const { return to_string(data(i)); }

protected:
  virtual string to_string(X) const = 0;
  virtual X from_string(const string&) const = 0;
};

#endif
