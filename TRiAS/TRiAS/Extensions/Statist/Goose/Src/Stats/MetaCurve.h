// This is -*- C++ -*-
// $Id: MetaCurve.h,v 1.2 1999/03/16 18:28:53 alstrup Exp $

/* 
 * MetaCurve.cpp
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

#ifndef _INC_METACURVE_H
#define _INC_METACURVE_H

#include <stdlib.h>

using namespace std;

class MetaCurve {
public:
  MetaCurve();
  virtual ~MetaCurve();

  enum interpolation_t { NONE, NEAREST, LINEAR, QUADRATIC };
  void set_interpolation(interpolation_t i) { interp_ = i; }

  double value(double x);

  // Increase sample size by a factor of q
  void enhance(size_t q);

  // Dump q times as many points as there are sample points, evenly spaced.
  void oversampled_dump(ostream& out, size_t q = 3);

protected:
  void set_range(double x0, double x1);

  void set_y_min(double y0) {
    have_y_min_ = true;
    y_min_ = y0;
  }
  void set_y_max(double y1) {
    have_y_max_ = true;
    y_min_ = y1;
  }

  double y_clip(double y) {
    if (have_y_min_ && y < y_min_)
      y = y_min_;
    else if (have_y_max_ && y > y_max_)
      y = y_max_;
    return y;
  }

  void set_sample_count(size_t N);

  virtual double calc(double) = 0;

private:
  
  double linear_interp(double x,
		       double x1, double y1,
		       double x2, double y2) const;
  double quadratic_interp(double x,
			  double x1, double y1,
			  double x2, double y2,
			  double x3, double y3) const;

  // Isn't bit-twiddling fun!
  bool have_in_buffer(size_t i) const {
    return (calcbits_[i/sizeof(unsigned)] & (1 << (i % sizeof(unsigned))))==1;
  }

  void put_in_buffer(size_t i, double x) {
    calcbits_[i/sizeof(unsigned)] |= (1 << (i % sizeof(unsigned)));
    y_buffer_[i] = x;
  }

  interpolation_t interp_;
  double x_min_, x_max_, x_freq_;

  bool have_y_min_;
  double y_min_;

  bool have_y_max_;
  double y_max_;

  size_t N_;
  unsigned* calcbits_;
  double* y_buffer_;
};

#endif // _INC_METACURVE_H

// $Id: MetaCurve.h,v 1.2 1999/03/16 18:28:53 alstrup Exp $
