
// This is -*- C++ -*-
// $Id: RCArray.h,v 1.5 1999/07/07 05:07:16 trow Exp $

/* 
 * RCArray.h
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

#ifndef _INC_RCARRAY_H
#define _INC_RCARRAY_H

#include <iostream>
#include <stdio.h>

using namespace std;

/*
  A simple implementation of an array w/ reference counting and
  a facility to handle copy-on-write.

  This will break very badly if we try to use an RCArray<X> where X is
  a type that can't be copied w/ memcpy(), doesn't have a working operator=(),
  doesn't have a default constructor w/ no args, etc. etc.
 */

const unsigned rc_array_default_size = 256;

template<class X>
class RCArrayBody {
public:
  RCArrayBody() : refs_(0), size_(0), slots_(0), data_(0) { }
  ~RCArrayBody() { delete [] data_; }

  void add_ref() { ++refs_; }
  void remove_ref() { --refs_; }
  int refs() { return refs_; }

  unsigned size() const { return size_; }
  X* data() { return data_; }

  void reserve(unsigned N) {
    if (slots_ < N) {
      X* nd = new X[N];
      if (size_ && data_)
	memcpy(nd, data_, size_*sizeof(X));
      delete [] data_;
      data_ = nd;
      slots_ = N;
    }
  }

  void insure_size(unsigned N) {
    unsigned nslots_ = slots_ ? slots_ : rc_array_default_size;
    while (nslots_ < N) 
      nslots_ *= 2;
    if (nslots_ != slots_)
      reserve(nslots_);
  }

  void set_size(unsigned N) {
    insure_size(N);
    size_ = N;
  }

  void add(X x) {
    insure_size(size_+1);
    data_[size_++] = x;
  }

  void add_at(unsigned i, X x) {
    insure_size(size_+1);
    memmove(data_+i+1, data_+i, (size_-i)*sizeof(X));
    data_[i] = x;
    ++size_;
  }

  void add(X* xs, unsigned count) {
    insure_size(size_+count);
    memmove(data_ + size_, xs, count*sizeof(X));
    size_ += count;
  }
  
  void add_at(unsigned i, X* xs, unsigned count) {
    insure_size(size_+count);
    memmove(data_+i+count, data_+i, (size_-i)*sizeof(X));
    memmove(data_ + size_, xs, count*sizeof(X));
    size_ += count;
  }

  // Remove last entry only.
  void remove() { if (size_) --size_; }

  // Remove specific entry.
  void remove_at(unsigned i) { remove_at(i,i); }

  // Remove range of entries.
  void remove_at(unsigned i, unsigned j) {
    memmove(data_+i, data_+j+1, (size_-1-j)*sizeof(X));
    size_ -= j+1-i;
  }

  void reverse() {
    for(unsigned i=0; i<size_/2; ++i) {
      X t = data_[i];
      data_[i] = data_[size_-1-i];
      data_[size_-1-i] = t;
    }
  }
  
  RCArrayBody* clone() const {
    RCArrayBody* rc = new RCArrayBody;
    rc->size_ = size_;
    rc->slots_ = slots_;
    rc->data_ = new X[rc->slots_];
    memcpy(rc->data_, data_, rc->size_*sizeof(X));
    return rc;
  }

private:
  int refs_;
  unsigned size_, slots_;
  X* data_;
};

template<class X>
class RCArray {
public:
  RCArray() : body_(new RCArrayBody<X>) {
    body_->add_ref();
  }

  RCArray(const RCArray<X>& r) : body_(r.body_) {
    if (this == &r) return; // don't copy to ourself

    body_->add_ref();
  }

  ~RCArray() {
    body_->remove_ref();
    if (body_->refs() == 0) 
      delete body_;
  }

  RCArray& operator=(const RCArray<X>& r) {
    if (this == &r) return *this; // don't copy to ourself.

    body_->remove_ref();
    if (body_->refs() == 0)
      delete body_;
    body_ = r.body_;
    body_->add_ref();
    return *this;
  }

  void clear() {
    if (body_->size()) {
      body_->remove_ref();
      if (body_->refs() == 0)
	delete body_;
      body_ = new RCArrayBody<X>;
      body_->add_ref();
    }
  }

  void prep_for_write() {
    if (body_->refs() > 1) {
      body_->remove_ref();
      body_ = body_->clone();
      body_->add_ref();
    }
  }

  unsigned size() const { return body_->size(); }
  const X* data() const { return body_->data(); }
  X* data() {
    prep_for_write();
    return body_->data();
  }

  const X& operator[](unsigned i) const { return (body_->data())[i]; }
  X& operator[](unsigned i) { 
    prep_for_write();
    return (body_->data())[i];
  }

  // For When you want to be sure the data doesn't get copied, even if you are
  // calling from a non-const function.
  const X* data_const() const { return body_->data(); }
  
  void reserve(unsigned N) { body_->reserve(N); }
  void insure_size(unsigned N) { body_->insure_size(N); }
  void set_size(unsigned N) {
    prep_for_write();
    body_->set_size(N);
  }
  void add(X x) {
    prep_for_write();
    body_->add(x);
  }
  void add_at(unsigned i, X x) {
    prep_for_write();
    body_->add_at(i,x);
  }


  void add(X* xs, unsigned count) {
    prep_for_write();
    body_->add(xs,count);
  }

  void add_at(unsigned i, X* xs, unsigned count) {
    prep_for_write();
    body_->add_at(i,xs,count);
  }

  void remove() {
    prep_for_write();
    body_->remove();
  }

  void remove_at(unsigned i, unsigned j) {
    prep_for_write();
    body_->remove_at(i,j);
  }

  void remove_at(unsigned i) {
    prep_for_write();
    body_->remove_at(i);
  }

  void reverse() {
    prep_for_write();
    body_->reverse();
  }

  void spew(ostream& out) const {
    const X* d = data();
    for(unsigned i=0; i<size(); ++i)
      out << d[i] << " ";
    out << endl;
  }

private:
  RCArrayBody<X>* body_;
};

#endif // _INC_RCARRAY_H

// $Id: RCArray.h,v 1.5 1999/07/07 05:07:16 trow Exp $
