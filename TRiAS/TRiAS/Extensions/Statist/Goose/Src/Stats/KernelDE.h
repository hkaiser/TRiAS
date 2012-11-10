// This is -*- C++ -*-
// $Id: KernelDE.h,v 1.2 1999/03/16 18:28:49 alstrup Exp $



#ifndef _INC_KERNELDE_H
#define _INC_KERNELDE_H

/* 
 * GaussianKD.h
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

#include "MetaCurve.h"
#include "RealSet.h"

class KernelDE : public MetaCurve {
public:
  enum kernel_t { Epanechnikov, Biweight, Triweight, Gaussian, Uniform };

  KernelDE(const RealSet& ds, double h,
	   size_t N = 100, kernel_t type = Gaussian);

protected:
  double calc(double x);

private:
  RealSet ds_;
  double h_;
  kernel_t type_;

};


#endif // _INC_KERNELDE_H

// $Id: KernelDE.h,v 1.2 1999/03/16 18:28:49 alstrup Exp $
