// This is -*- C++ -*-
// $Id: gala1.cpp,v 1.7 1999/03/16 18:27:34 alstrup Exp $

/* 
 * gala1.cpp
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
#include <time.h>
#include "Random.h"
#include "gala.h"

using namespace std;

int main()
{
  GMat k(3), ki(3), kk(3);
  k(0,0) = 1;
  k(0,1) = 2;
  k(2,0) = 7;
  k(1,1) = 4;
  k(2,2) = 9;
  k(2,1) = -3;
  cout << k << endl;
  ki = k;
  ki.invert();
  cout << ki << endl;
  cout << k << endl;
  kk = k;
  kk *= ki;
  cout << kk << endl;
  exit(0);

  const size_t N = 50;
  const size_t trials = 10000;
  Random rnd;

  GMat m(N,N);
  GVec v(N);
  for(size_t i=0; i<m.rows(); ++i) {
    for(size_t j=0; j<m.cols(); ++j)
      m(i,j) = rnd.random_uniform(-1,1);
    v[i] = rnd.random_uniform(-5,5);
  }

  time_t t1,t2;
  time(&t1);
  for(size_t i=0; i<trials; ++i) {
    GVec w = m.solve(v);
  }
  time(&t2);

  cout << trials << " trials" << endl;
  cout << t2-t1 << " sec elapsed" << endl;
  cout << trials/(double)(t2-t1) << " soln/sec" << endl;

  return 0;
}




// $Id: gala1.cpp,v 1.7 1999/03/16 18:27:34 alstrup Exp $
