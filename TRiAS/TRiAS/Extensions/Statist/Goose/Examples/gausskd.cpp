// This is -*- C++ -*-
// $Id: gausskd.cpp,v 1.5 1999/03/16 18:27:35 alstrup Exp $

/* gausskd.cpp
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

#include <config.h>
#include <iostream>
#include <iomanip>
#include "RealSet.h"
#include "KernelDE.h"

using namespace std;

int main(int argc, char* argv[])
{
  double h = atof(argv[1]);
  RealSet ds;

  double x;
  while (cin.good()) {
    cin >> x;
    if (!cin.eof()) 
      ds.add(x);
  }

  KernelDE gkd(ds, h, 20, KernelDE::Gaussian);
  gkd.oversampled_dump(cout, 3);
  return 0;
}
