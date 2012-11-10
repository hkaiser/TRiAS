// This is -*- C++ -*-
// $Id: test_regression.cpp,v 1.10 1999/03/16 18:27:45 alstrup Exp $

/* test_regression.cpp
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
#include "RealSet.h"
#include "Random.h"
#include "LinearRegression.h"
#include "PolynomialRegression.h"

using namespace std;

int main()
{
  Random rnd;

  RealSet indep, dep;

  for(int i=0; i<100; ++i) {
    double x = rnd.random_uniform(-10,10);
    double y = 2*x*x*x + 3*x - 7 + rnd.random_normal(0,0.5);
    indep.add(x);
    dep.add(y);
  }

  cout << "  true model: y = -7 + 3 x + 2 x^3" << endl;

  LinearRegression linreg;
  linreg.model(indep, dep);

  cout << "linear model: y = " << linreg.intercept() << " + ";
  cout << linreg.slope() << " x";
  cout << " (r = " << linreg.correlation() << ")" << endl;

  PolynomialRegression polyreg;
  polyreg.model(indep, dep, 3);

  cout << "  poly model: y = ";
  for(unsigned i=0; i<=polyreg.degree(); ++i) {
    if (i) cout << " + ";
    cout << polyreg.coefficient(i);
    if (i) cout << " x^" << i;
  }
  cout << endl;
  return 0;
}



// $Id: test_regression.cpp,v 1.10 1999/03/16 18:27:45 alstrup Exp $
