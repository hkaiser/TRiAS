// This is -*- C++ -*-
// $Id: StatsDB.cpp,v 1.2 1999/03/16 18:28:56 alstrup Exp $

/* 
 * StatsDB.cpp
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

#include <config.h>
#include "StatsDB.h"

struct SingleEntryInfo { 
  StatsDB::single_ds_stat_member f;
  string name;
};

struct DoubleEntryInfo {
  StatsDB::double_ds_stat_member f;
  string name;
};

StatsDB::StatsDB()
{
  add("Minimum",		    &RealSet::min);
  add("Maximum",		    &RealSet::max);
//  add("Range",			    &RealSet::range);
  add("Sum",			    &RealSet::sum);
  add("Mean",			    &RealSet::mean);
  add("Variance",		    &RealSet::var);
  add("Standard Deviation",	    &RealSet::sdev);
  add("Sample Standard Deviation",  &RealSet::sdevs);
//  add("Median",			    &RealSet::med);
//  add("Q1",			    &RealSet::q1);
//  add("Q3",			    &RealSet::q3);
//  add("Interquartile Range",	    &RealSet::iqr);
//  add("Geometric Mean",		    &RealSet::gmean);
//  add("Harmonic Mean",		    &RealSet::hmean);
//  add("Root Mean Square",	    &RealSet::rms);
//  add("Mean Deviation",		    &RealSet::meandev);
//  add("Median Deviation",	    &RealSet::meddev);
//  add("Kurtosis",		    &RealSet::kurtosis);
//  add("Skewness",		    &RealSet::skewness);
//  add("Excess Kurtosis",	    &RealSet::excess_kurtosis);
// this calls skewness
//  add("Momental Skewness",	    &RealSet::momental_skewness);

//  add("Covariance",		    &RealSet::covar);
//  add("Correlation",		    &RealSet::corr);
//  add("Pooled Mean",		    &RealSet::pooled_mean);
//  add("Pooled Variance",	    &RealSet::pooled_var);
//  add("Weighted Mean",		    &RealSet::weighted_mean);
}

StatsDB::~StatsDB()
{
  map<string,SingleEntry*>::iterator i = single_entries_.begin();
  while (i != single_entries_.end()) {
    delete (*i).second;
    ++i;
  }

  map<string,DoubleEntry*>::iterator j = double_entries_.begin();
  while (j != double_entries_.end()) {
    delete (*j).second;
    ++j;
  }
}

double StatsDB::statistic(const string& key, const RealSet& ds) const
{
  map<string,SingleEntry*>::const_iterator i = single_entries_.find(key);
  
  if (i == single_entries_.end()) {
    throw Exception("Key " + key + " not found.");
  }
  else {
    return (*i).second->apply(ds);
  }
}

double StatsDB::statistic(const string& key, 
			  const RealSet & ds1, const RealSet& ds2) const
{
  map<string,DoubleEntry*>::const_iterator i = double_entries_.find(key);
  
  if (i == double_entries_.end()) {
    throw Exception("Key " + key + " not found.");
  }
  else {
    return (*i).second->apply(ds1,ds2);
  }
} 

StatsDB::const_iterator StatsDB::single_begin() const
{
  return single_keys_.begin();
}

StatsDB::const_iterator StatsDB::double_begin() const
{
  return double_keys_.begin();
}


StatsDB::const_iterator StatsDB::single_end() const
{
  return single_keys_.end();
}

StatsDB::const_iterator StatsDB::double_end() const
{
  return double_keys_.end();
}


void StatsDB::add(const string& name, single_ds_stat_func f)
{
  SingleEntry* se = new FunctionSingleEntry(f);
  single_keys_.push_back(name);
  single_entries_[name] = se;
}

void StatsDB::add(const string& name, double_ds_stat_func f)
{
  DoubleEntry* se = new FunctionDoubleEntry(f);
  double_keys_.push_back(name);
  double_entries_[name] = se;
}


void StatsDB::add(const string& name, single_ds_stat_member f)
{
  SingleEntry* se = new MemberSingleEntry(f);
  single_keys_.push_back(name);
  single_entries_[name] = se;
}

void StatsDB::add(const string& name, double_ds_stat_member f)
{
  DoubleEntry* se = new MemberDoubleEntry(f);
  double_keys_.push_back(name);
  double_entries_[name] = se;
}


// $Id: StatsDB.cpp,v 1.2 1999/03/16 18:28:56 alstrup Exp $
