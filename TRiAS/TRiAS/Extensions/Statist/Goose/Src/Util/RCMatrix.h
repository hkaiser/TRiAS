// This is -*- C++ -*-
// $Id: RCMatrix.h,v 1.3 1999/07/07 05:07:16 trow Exp $

/* 
 * RCMatrix.h
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

#ifndef _INC_RCMATRIX_H
#define _INC_RCMATRIX_H

/*
  A very simple implementation of a matrix w/ reference counting.
*/

#include "RCArray.h"

template<class X>
class RCMatrixBody {
public:
  RCMatrixBody() : refs_(0), rows_(0), cols_(0), size_(0), data_(0) { }
  ~RCMatrixBody() { delete [] data_; }

  void add_ref() { ++refs_; }
  void remove_ref() { --refs_; }
  int refs() { return refs_; }

  unsigned rows() const { return rows_; }
  unsigned cols() const { return cols_; }
  unsigned size() const { return size_; }
  X* data() { return data_; }

  void set_size(unsigned r, unsigned c) {
    delete [] data_;
    rows_ = r;
    cols_ = c;
    size_ = r*c;
    data_ = new X[size_];
  }

  RCMatrixBody* clone() const {
    RCMatrixBody* rc = new RCMatrixBody;
    rc->set_size(rows(), cols());
    memcpy(rc->data_, data_, rc->size()*sizeof(X));
    return rc;
  }

private:
  int refs_;
  unsigned rows_, cols_, size_;
  X* data_;
};

template<class X>
class RCMatrix {
public:
  RCMatrix() : body_(new RCMatrixBody<X>) {
    body_->add_ref();
  }

  RCMatrix(unsigned r, unsigned c) : body_(new RCMatrixBody<X>) {
    body_->add_ref();
    body_->set_size(r,c);
  }

  RCMatrix(const RCMatrix<X>& r) : body_(r.body_) {
    body_->add_ref();
  }

  ~RCMatrix() {
    body_->remove_ref();
    if (body_->refs() == 0)
      delete body_;
  }

  RCMatrix& operator=(const RCMatrix<X>& r) {
    body_->remove_ref();
    if (body_->refs() == 0)
      delete body_;
    body_ = r.body_;
    body_->add_ref();
    return *this;
  }

  void clear() {
    if (body_->rows() || body_->cols())
      body_->remove_ref();
    if (body_->refs() == 0)
      delete body_;
    body_ = new RCMatrixBody<X>;
    body_->add_ref();
  }

  void prep_for_write() {
    if (body_->refs() > 1) {
      body_->remove_ref();
      body_ = body_->clone();
      body_->add_ref();
    }
  }

  void set_size(unsigned r, unsigned c) {
    prep_for_write();
    body_->set_size(r,c);
  }

  unsigned rows() const { return body_->rows(); }
  unsigned cols() const { return body_->cols(); }
  unsigned size() const { return body_->size(); }

  const X* data() const { return body_->data(); }
  const X* data_const() const { return body_->data(); }
  X* data() {
    prep_for_write();
    return body_->data();
  }
  X* data_unsafe() { return body_->data(); }

  unsigned index(unsigned r, unsigned c) const { return r*cols()+c; }
  void incr_row(unsigned& i) const { i += cols(); }
  void incr_col(unsigned& i) const { ++i; }

  X entry(unsigned r, unsigned c) const { return data()[index(r,c)]; }
  X entry_const(unsigned r, unsigned c) const { return data()[index(r,c)]; }
  X& entry(unsigned r, unsigned c) { return data()[index(r,c)]; }
  X& entry_unsafe(unsigned r, unsigned c) { return data_unsafe()[index(r,c)]; }

private:
  RCMatrixBody<X>* body_;
};

#endif // _INC_RCMATRIX_H

// $Id: RCMatrix.h,v 1.3 1999/07/07 05:07:16 trow Exp $
