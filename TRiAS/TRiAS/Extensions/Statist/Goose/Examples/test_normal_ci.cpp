// This is -*- C++ -*-
// $Id: test_normal_ci.cpp,v 1.9 1999/03/16 18:27:44 alstrup Exp $

/* test_normal_ci.cpp
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
#include "normal.h"

using namespace std;

int main()
{
  const int trials=1000;
  const double conf=0.98;
  int acc=0;

  Random rnd;  

  /*
   * Construct two RealSets with known mean (=0), then get a conf interval
   * for the difference in their means and see how often it contains 0.
   * The % of the time that 0 is in our interval should equal the confidence
   * level attached to our interval (+/- the usual error).
   */

  for(int t=0; t<trials; ++t) {
    RealSet ds1, ds2;
    for(int i=0; i<1000; ++i) {
      ds1.add(rnd.random_normal());
      ds2.add(rnd.random_normal());
    }
    ConfInt e = ci_diff_mean(ds1, ds2, conf);
    if (e.contains(0)) ++acc;
  }

  double p = acc/(double)trials;
  double pse = sqrt(p*(1-p)/trials);
  ConfInt pe;
  pe.set_by_error(p,3*pse);

  cout << "  Trials: " << trials << endl;
  cout << "    Hits: " << acc << endl;
  cout << "Accuracy: " << pe.low() << " - " << pe.high() << endl;
  cout << "Exp Rate: " << conf << endl;
  cout << "Correct?: " << (pe.contains(conf) ? "yes" : "no") << endl;
  return 0;
}



// $Id: test_normal_ci.cpp,v 1.9 1999/03/16 18:27:44 alstrup Exp $
