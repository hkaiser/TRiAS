// This is -*- C++ -*-
// $Id: test_matrix.cpp,v 1.10 1999/07/09 18:43:27 trow Exp $

/* test_matrix.cpp
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
#include <math.h>
#include "Random.h"
#include "gala.h"

using namespace std;

void check(const GMat& M, const GMat& Minv) 
{
  GMat mii = Minv;
  mii.invert();
  bool problem = false;
  for(size_t i=0; i<mii.rows(); ++i)
    for(size_t j=0; j<mii.cols(); ++j)
      if (fabs(M(i,j) - mii(i,j)) > 1e-8)
	problem = true;
  cout << M.rows() << "x" << M.cols();
  if (problem)
    cout << "?????";
  cout << ' ';
  cout.flush();
}

int main()
{

  Random rnd;

  cout << endl << "Checking random examples... " << endl;
  const size_t M = 100;
  for(size_t i=2; i<=M; ++i) {
    GMat M(i,i), Minv(i,i);
    for(size_t r=0; r<i; ++r)
      for(size_t c=0; c<i; ++c) {
	M(r,c) = Minv(r,c) = rnd.random_normal();
      }
    Minv.invert();
    check(M, Minv);
  }

  cout << endl << endl << "Running inversion benchmark:" << endl << endl;
  
  const int N = 40;
  const int TRIALS = 10000;
  double m[N*N];
  GMat benchM(N,N);

  // First estimate time for creating the random matrix
  time_t ct1, ct2;
  cerr << "Timing overhead... " << endl;
  time(&ct1);
  for(int i=0; i<3*TRIALS; ++i) {
    rnd.random_normal_bulk(m,N*N);
    size_t j=0;
    for(size_t r=0; r<N; ++r)
      for(size_t c=0; c<N; ++c)
	benchM(r,c) = m[j++];
  }
  time(&ct2);

  time_t t1, t2;
  cerr << "Timing inversions..." << endl << endl;

  time(&t1);

  for(int i=0; i<TRIALS; ++i) {
    rnd.random_normal_bulk(m, N*N);
    size_t j=0;
    for(size_t r=0; r<N; ++r)
      for(size_t c=0; c<N; ++c)
	benchM(r,c) = m[j++];
    benchM.invert();
  }
  time(&t2);

  double adj_t = t2-t1 - (ct2-ct1)/3.0;

  cout << "Generated & inverted ";
  cout << TRIALS << " " << N << "x" << N << " matrices in ";
  cout << adj_t << " seconds." << endl; 
  cout << "Inversions/second = " << TRIALS/adj_t << endl;
  return 0;
}




// $Id: test_matrix.cpp,v 1.10 1999/07/09 18:43:27 trow Exp $
