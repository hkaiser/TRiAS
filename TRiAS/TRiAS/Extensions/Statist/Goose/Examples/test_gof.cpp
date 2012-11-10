// This is -*- C++ -*-
// $Id: test_gof.cpp,v 1.6 1999/03/16 18:27:42 alstrup Exp $

/* test_gof.cpp
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
#include "Random.h"
#include "fit.h"

using namespace std;

void bin_test(int bins, int samples)
{
  Random rnd;
  unsigned* b = new unsigned[bins];
  for(int i=0; i<bins; ++i)
    b[i] = 0;

  for(int i=0; i<samples; ++i) {
    int j=(int)(rnd.random_uniform(0.0,bins));
    ++b[j];
  }

  GoodnessOfFit gof;
  for(int i=0; i<bins; ++i)
    gof.add_category(b[i], samples*(1.0/bins));

  cout << "bins=" << bins << " samples=" << samples << " chi_sq=" << gof.chi_sq() << " p=" << gof.p_value() << endl;

  delete [] b;
}

int main()
{
  for(int i=2; i<10; ++i)
    bin_test(i,1000000);
  return 0;
}




// $Id: test_gof.cpp,v 1.6 1999/03/16 18:27:42 alstrup Exp $
