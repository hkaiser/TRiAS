// This is -*- C++ -*-
// $Id: fit.h,v 1.2 1999/03/16 18:29:04 alstrup Exp $

/* fit.h
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

#ifndef _INC_FIT_H
#define _INC_FIT_H

class GoodnessOfFit {
public:
  GoodnessOfFit() : cat_(0), est_(0), chi2_(0) { }

  void add_category(unsigned observed, double expected);
  void set_estimated_parameters(unsigned p) { est_ = p; }

  unsigned categories() const { return cat_; }
  unsigned estimated_parameters() const { return est_; }
  unsigned df() const { return cat_-est_-1; }
  double chi_sq() const { return chi2_; }
  double p_value() const;

  void clear() { cat_ = est_ = 0; chi2_ = 0; }

private:
  unsigned cat_, est_;
  double chi2_;
};

#endif // _INC_FIT_H

// $Id: fit.h,v 1.2 1999/03/16 18:29:04 alstrup Exp $
