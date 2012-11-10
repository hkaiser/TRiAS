// This is -*- C++ -*-
// $Id: DateSet.h,v 1.9 1999/07/15 17:43:42 trow Exp $

/* 
 * DateSet.h
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@emccta.com>
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


#ifndef _INC_DATESET_H
#define _INC_DATESET_H

#ifndef WIN32
#include <glib.h>
#include <RCArray.h>
#include <Exception.h>
#include <DataConverter.h>
#include "DataSet.h"

class Permutation;
class Random;

class DateSet : public DataSet_Typed<GDate> {
public:
  static const DataSet::type_t typecode;

  DateSet() : DataSet_Typed<GDate>(typecode) {}
  DateSet(DateSet const & d) 
     : DataSet_Typed<GDate>(typecode), data_(d.data_), 
       min_(d.min_), max_(d.max_), sorted_(d.sorted_)
  { 
    set_label(d.label());
  }
   
  DataSet * clone() const {
    return new DateSet(*this);
  }

  unsigned size() const { return data_.size(); }
  void reserve(unsigned N) { data_.reserve(N); }
  void resize(unsigned N) { }

  void add(GDate);
  void add_at(int, GDate);
  void set(int i, GDate);
  GDate data(int i) const;

  void remove(int i);
  void remove(int begin, int end);
  void clear();

  void sort();
  void permute(const Permutation&);
  void scramble_explicit(Random&);
  void reverse();
  
protected:
  string to_string(GDate) const;
  GDate from_string(const string&) const;

private:
  RCArray<GDate> data_;
  GDate min_, max_;
  bool sorted_;
};

#endif
#endif // _INC_DATESET_H

// $Id: DateSet.h,v 1.9 1999/07/15 17:43:42 trow Exp $
