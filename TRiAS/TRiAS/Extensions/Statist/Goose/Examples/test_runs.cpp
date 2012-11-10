// This is -*- C++ -*-
// $Id: test_runs.cpp,v 1.7 1999/03/16 18:27:47 alstrup Exp $

/* test_runs.cpp
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
#include "runs.h"
using namespace std;

void show(const RunsCount& r)
{
  cout << "Count: " << r.size() << endl;
  cout << " True: " << r.obs_true() << endl;
  cout << "False: " << r.obs_false() << endl;
  cout << " Runs: " << r.runs() << endl;
  cout << "    Z: " << r.z() << endl;
  cout << "p-val: " << r.p_value() << endl;
  cout << endl;
}

int main()
{
  RunsCount r;
  
  int foo[] = {0,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,-1};

  cout << " Obs: ";
  for(int i=0; foo[i] != -1; ++i) {
    bool x = foo[i];
    cout << (x ? "T" : "F") << " ";
    r.add(x);
  }
  cout << endl;
  show(r);

  r.clear();

  Random rnd;
  for(int i=0; i<1000; ++i) {
    bool x = rnd.random_bool();
    r.add(x);
  }

  show(r);

  RunsUpDown rud;
  for(int i=0; i<1000; ++i)
    rud.add(rnd.random_uniform());
  cout << rud.runs() << endl;
  cout << rud.z() << endl;
  return 0;
}


// $Id: test_runs.cpp,v 1.7 1999/03/16 18:27:47 alstrup Exp $
