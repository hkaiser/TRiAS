// This is -*- C++ -*-
// $Id: HoleSet.h,v 1.6 1999/07/15 17:43:42 trow Exp $

/* 
 * HoleSet.h
 *
 * Copyright (C) 1999 Asger Alstrup Nielsen
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

#ifndef _INC_HOLESET_H
#define _INC_HOLESET_H

#include <string>
#include "DataConverter.h"
#include "DataSet.h"

//using std::string;

class Permutation;

/*
 * Adds support for missing data to any existing DataSet
 * that provides the dataset_type typedef.
 */
template<class Set>
class HoleSet : public DataSet {
public:

  HoleSet() : DataSet(DataSet::invalid_typecode) { }
  HoleSet(HoleSet * h) 
      : DataSet(DataSet::invalid_typecode), mapping(h->mapping),   
        all_data_(h->all_data_), dataset_(h->dataset_)
  { }

  // This is sort of a sick hack since DataSet requires us to define a
  // typecode. We just define it to be the invalid type marker;
  // shouldn't do type ID on a HoleSet for now.  I think there's a
  // better way, but not implemented yet.


  virtual ~HoleSet() { }

  DataSet * clone() const {
    return new HoleSet(*this);
  }

  bool support_missing() const { return true; }
  unsigned size() const { return mapping.size(); }

  // Make sure we have allocated room for at least N entries
  virtual void reserve(unsigned N) {
    dataset_.reserve(N - (mapping.size() - dataset_.size()) );
    mapping.reserve(N);
  }

  virtual void resize(unsigned N) {
    if (size() > N) {
      remove(N, size()-1);
    } else {
      while(size() < N)
	add_string(string());
    }
  }

  virtual void add_string(string const & str) {
    if (str.empty()) {
      // We are asked to add a hole at the end
      mapping.push_back(-1);
    } else {
      // We are asked to add data at the end
      mapping.push_back(dataset_.size());
      dataset_.add_string(str);
    }
  }

  virtual void add_string_at(int i, string const & str) {
    // We are asked to add data at the end
    if (i == max_index()) {
      add_string(str);
    } else if (str.empty()) {
      // We are asked to insert a hole somewhere
      mapping.insert(mapping.begin() + i - min_index(), -1);
    } else {
      // We are asked to insert a element somewhere

      // First, determine where we should insert it in the host
      // This is done by scanning up and down simultaneously
      // until we find a real element
      int down = i, up = i + 1;
      int host_position = -1;
      while (down >= 0 || up < int(size())) {
	if (down >= 0) {
	  if (mapping[down] != -1) {
	    host_position = mapping[down] + 1;
	    break;
	  }
  	  --down;
	}

	if (up < int(size())) {
	  if (mapping[up] != -1) {
	    host_position = mapping[up];
	    break;
	  }
	  ++up;
	}
      }

      if (host_position == -1) {
        // We have nothing but holes, so we just add it as first element 
	// in the host
	host_position = 0;
      }

      // Now, add the element in the host
      dataset_.add_string_at(host_position, str);

      // Then, increase the mapping index value of following real elements
      for (vector<int>::iterator index=mapping.begin() + i;
	   index != mapping.end(); ++index) {
	     if (*index != -1)
	       ++(*index);
      }

      // And finally, we insert the new mapping
      mapping.insert(mapping.begin() + i, host_position);
    }
  }

  virtual void set_string(int i, string const & str) {
    if (!str.empty() && mapping[i - min_index()] != -1) {
      // We are asked to replace existing data with new data
      set_string(mapping[i - min_index()], str);
    } else {
      // We handle it by first removing the element
      // and then inserting the new one
      erase(i);
      add_string_at(i, str);
    }
  }

  // Get i-th elem as a canonical string
  virtual string as_string(int i) const {
    if (mapping[i - min_index()] == -1) {
      return string();
    } else {
      return dataset_.as_string(mapping[i - min_index()]);
    }
  }

  // Removal interface
  virtual void remove(int i) {
    cout << "Slet kaldt med " << i << ":" << endl;
    contents();
    if (i > max_index()) {
      return;
    } else if (i == max_index()) {
      // Removing the last element
      if (mapping[i - min_index()] != -1) {
	dataset_.pop_back();
      }
      mapping.pop_back();
    } else {
      if (mapping[i - min_index()] != -1) {
	dataset_.remove(mapping[i - min_index()]);
	// Decrease the mapping index value of following real elements
	for (vector<int>::iterator index=mapping.begin() + i - min_index();
	     index != mapping.end(); ++index) {
	       if (*index != -1)
		 --(*index);
	}
      }
      mapping.erase(mapping.begin() + i - min_index());
    }
    contents();
    cout << "Slet slut" << endl;
  }

  virtual void remove(int begin, int end) {
    cout << "Slet område kaldt med " << begin << "-" << end << endl;
    for (int i = end; i >= begin; --i) {
      remove(i);
    }
    cout << "Slet område slut" << endl;
  }

  virtual void clear() {
    dataset_.clear();
    mapping.clear();
  }
  
  // Methods to rearrange our data
  virtual void permute(const Permutation& p) {
    // TODO
  }
  virtual void scramble_explicit(Random&) {
    // TODO
  }
  virtual void reverse() {
    // TODO
  }

  // Provide access to all elements in one giant swoop
  vector<typename Set::value_type const *> const & all_data() const {
    all_data_.clear();
    all_data_.reserve(size());
    for (vector<int>::const_iterator i = mapping.begin(); i != mapping.end() ; ++i) {
      if (*i == -1) {
	all_data_.push_back(0);
      } else {
	all_data_.push_back(dataset_.data(*i)+mapping[i]);
      }
    }
    return all_data_;
  }

  // Provide access to the dataset with the statistics
  Set const & dataset() const {
    return dataset_;
  }

private:
  // Maps coordinates from missing dataset to
  // dataset without missing data.
  // Missing elements have the coordinate -1.
  vector<int> mapping;
  // This contains
  vector<typename Set::value_type const *> all_data_;
  // Here we keep the host
  Set dataset_;

public:
  void contents() {
    cout << "Contents:" << endl;
    int n = min_index();
    for (vector<int>::const_iterator i = mapping.begin();
         i != mapping.end(); ++i) {
	cout << n << "->" << *i;
	if (*i != -1) {
	  cout << "=" << dataset_.data(*i);
	}
	cout << endl;
	++n;
    }
  }

};


#endif
