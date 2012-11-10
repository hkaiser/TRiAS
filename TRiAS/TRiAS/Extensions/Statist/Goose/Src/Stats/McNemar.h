// This is -*- C++ -*-
// $Id: McNemar.h,v 1.2 1999/07/19 13:21:47 alstrup Exp $

/* McNemar.h
 *
 * Copyright (C) 1999 Sophus Medical Aps.
 *
 * Developed by Mikkel Munck Rasmussen <mikkel@sophusmedical.dk>.
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

#ifndef _INC_MCNEMAR_H
#define _INC_MCNEMAR_H

#include <RealSet.h>
#include <specfns.h>

// Structure that contains the results from the test
struct McNemarResult {
  double X2;
  double X2c;
  double p;
  double pc;
};

// Calculation of the McNemar change test
McNemarResult McNemar(double A, double D);

#endif // _INC_MCNEMAR_H
