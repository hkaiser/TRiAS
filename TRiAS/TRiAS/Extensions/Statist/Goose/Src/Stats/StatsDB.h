// This is -*- C++ -*-
// $Id: StatsDB.h,v 1.2 1999/03/16 18:28:57 alstrup Exp $

/* 
 * StatsDB.h
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
 *
 * Developed by Havoc Pennington <hp@emccta.com>
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

#ifndef _INC_STATSDB_H
#define _INC_STATSDB_H

#include "RealSet.h"
#include <map>
#include <vector>

// StatsDB lets you dynamically handle a list of available
//  statistics, so you don't have to hardcode a bunch of RealSet
//  operations. It helps decouple your application from the library.
// However, it can't handle stats that take special arguments or 
//  otherwise require special casing.

class StatsDB {
public:
  StatsDB();
  ~StatsDB();

  double statistic(const string& key, const RealSet& ds) const;
  double statistic(const string& key, 
		   const RealSet & ds1, const RealSet& ds2) const;
  
  typedef vector<string>::const_iterator const_iterator;
  
  const_iterator single_begin() const;
  const_iterator double_begin() const;

  const_iterator single_end() const;
  const_iterator double_end() const;

  typedef double (*single_ds_stat_func)(const RealSet & ds);
  typedef double (*double_ds_stat_func)(const RealSet & ds1, 
					const RealSet & ds2);
  
  void add(const string& name, single_ds_stat_func f);
  void add(const string& name, double_ds_stat_func f);

  typedef double (RealSet::* single_ds_stat_member)() const;
  typedef double (RealSet::* double_ds_stat_member)(const RealSet & ds) const;

  // These are only used by the library, when items are added to RealSet.  
  void add(const string& name, single_ds_stat_member f);
  void add(const string& name, double_ds_stat_member f);

private:  

  class SingleEntry {
  public:
    virtual double apply(const RealSet & ds) = 0;
  };

  class MemberSingleEntry : public SingleEntry {
  public:
    MemberSingleEntry(single_ds_stat_member f) : f_(f) {}
    double apply(const RealSet & ds) { return (ds.*f_)(); }
  private:
    single_ds_stat_member f_;
  };

  class FunctionSingleEntry : public SingleEntry {
  public:
    FunctionSingleEntry(single_ds_stat_func f) :  f_(f) {}
    double apply(const RealSet & ds) { return f_(ds); }
  private:
    single_ds_stat_func f_;
  };
  
  class DoubleEntry {
  public:
    virtual double apply(const RealSet & ds1, const RealSet & ds2) = 0;
  };

  class MemberDoubleEntry : public DoubleEntry {
  public:
    MemberDoubleEntry(double_ds_stat_member f) : f_(f) {}
    double apply(const RealSet & ds1, const RealSet & ds2) { return (ds1.*f_)(ds2); }
  private:
    double_ds_stat_member f_;
  };


  class FunctionDoubleEntry : public DoubleEntry {
  public:
    FunctionDoubleEntry(double_ds_stat_func f) :  f_(f) {}
    double apply(const RealSet & ds1, const RealSet & ds2) { return f_(ds1,ds2); }
  private:
    double_ds_stat_func f_;
  };

  // map by itself could be made to work, but this is simpler.
  vector<string> single_keys_;
  vector<string> double_keys_;

  map<string,SingleEntry*> single_entries_;
  map<string,DoubleEntry*> double_entries_;  
};

#endif // _STATSDB_H

// $Id: StatsDB.h,v 1.2 1999/03/16 18:28:57 alstrup Exp $
