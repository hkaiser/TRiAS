// This is -*- C++ -*-
// $Id: ConfInt.h,v 1.2 1999/03/16 18:29:19 alstrup Exp $

/* 
 * ConfInt.h
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

#ifndef _INC_ConfInt_H
#define _INC_ConfInt_H

#include <math.h>

class ConfInt {
public:
  ConfInt() : inited_(false) { }

  ConfInt(const ConfInt& e) : inited_(e.inited_)
    { 
      if (inited_) {
	lo_ = e.lo_;
	est_ = e.est_;
	hi_ = e.hi_;
	conf_ = e.conf_;
      }
    }

  void set(double l, double e, double h, double c = 0) {
    if (l <= e && e <= h) {
      inited_ = true;
      lo_ = l;
      est_ = e;
      hi_ = h;
      conf_ = c;
    }
  }

  void set_by_error(double e, double err, double c = 0) {
    inited_ = true;
    est_ = e;
    err = fabs(err);
    lo_ = e-err;
    hi_ = e+err;
    conf_ = c;
  }

  void set_by_errors(double e, double err_lo, double err_hi, double c=0) {
    inited_ = true;
    est_ = e;
    lo_ = e-fabs(err_lo);
    hi_ = e+fabs(err_hi);
    conf_ = c;
  }

  void set_confidence(double c) { conf_ = c; }

  bool initialized() const { return inited_; }

  // We should throw some sort of an exception if we access these for
  // an uninitialized interval.
  double low() const {
    if (!inited_) throw("ConfInt is not initialized");
    return lo_;
  }
  double est() const {
    if (!inited_) throw("ConfInt is not initialized");
    return est_;
  }
  double high() const {
    if (!inited_) throw("ConfInt is not initialized");
    return hi_;
  }
  double width() const {
    if (!inited_) throw("ConfInt is not initialized");
    return hi_-lo_;
  }
  bool symmetric() const {
    if (!inited_) throw("ConfInt is not initialized");
    return fabs(hi_ + lo_ - 2*est_) < 1e-8 * (hi_-lo_);
  }

  double confidence() const {
    if (!inited_) throw("ConfInt is not initialized");
    return conf_;
  }

  bool contains(double x) const {
    if (!inited_) throw("ConfInt is not initialized");
    return lo_ <= x && x <= hi_;
  }

private:
  bool inited_;
  double lo_, est_, hi_, conf_;
};

#endif // _INC_ConfInt_H

// $Id: ConfInt.h,v 1.2 1999/03/16 18:29:19 alstrup Exp $
