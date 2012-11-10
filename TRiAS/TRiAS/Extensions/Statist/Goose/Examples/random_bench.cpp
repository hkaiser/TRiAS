// This is -*- C++ -*-
// $Id: random_bench.cpp,v 1.11 1999/07/09 18:43:27 trow Exp $

/* random_bench.cpp
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
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Random.h"

using namespace std;

int main()
{
  const int N = 50000000;
  const size_t block=100000;
  unsigned x=0;
  time_t t1, t2, t3, t4, t5, t6;

//  double b[block];
//  unsigned bb[block];
  int bi[block];

  Random rnd;
  rnd.seed(10);
  time(&t5);
  for(size_t i=0; i<N/block; ++i)
    rnd.random_integer_bulk(0,100, bi, block);
  time(&t6);

  cout << "   Normal block: " << t6-t5 << endl;  

  time(&t3);
  for(size_t i=0; i<N/block; ++i)
    for(size_t j=0; j<block; ++j)
      bi[j] = rnd.random_integer(0,100);
  time(&t4);

  cout << "    Normal loop: " << t4-t3 << endl;
  
  time(&t1);
  for(size_t i=0; i<N/block; ++i)
    for(size_t j=0; j<block; ++j)
      bi[j] = 0;
  time(&t2);

  cout << "   Control loop: " << t2-t1 << endl;
  return 0;
}




// $Id: random_bench.cpp,v 1.11 1999/07/09 18:43:27 trow Exp $
