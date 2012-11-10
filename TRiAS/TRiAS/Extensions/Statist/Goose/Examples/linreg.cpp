// This is -*- C++ -*-
// $Id: linreg.cpp,v 1.6 1999/03/16 18:27:37 alstrup Exp $

/* dataset1.cpp
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
#include "LinearRegression.h"

using namespace std;

int main()
{
  RealSet ds_x, ds_y;

  double x,y;

  while (cin.good()) {
    cin >> x;
    // I think that this is redundant, but I'm to dig out my copy of
    // Stroustrup and check how iostreams works...
    if (!cin.eof() && cin.good()) {
      cin >> y;
      if (!cin.eof()) {
	ds_x.add(x);
	ds_y.add(y);
      }
    }
  }

  LinearRegression lr;
  lr.model(ds_x,ds_y);
  ConfInt ci_s = lr.slope_interval(0.95);
  ConfInt ci_i = lr.intercept_interval(0.95);

  cout << endl;
  cout << "     Sample size: " << ds_x.size() << endl;
  cout << "  Model Equation: y = " << lr.slope();
  cout << " x + " << lr.intercept() << endl;
  cout << "               R: " << lr.R() << endl;
  cout << "             R^2: " << lr.R_sq() << endl;
  cout << "    Slope 95% CI: ( " << ci_s.low() << " , " << ci_s.high() << " )" << endl;
  cout << "Intercept 95% CI: ( " << ci_i.low() << " , " << ci_i.high() << " )" << endl;
  cout << "Independent?   t: " << lr.independence_t() << endl;
  cout << "               p: " << lr.independence_p() << endl;
  cout << endl;
  return 0;
}



