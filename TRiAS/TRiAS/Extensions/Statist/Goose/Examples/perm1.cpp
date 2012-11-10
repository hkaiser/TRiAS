// This is -*- C++ -*-
// $Id: perm1.cpp,v 1.5 1999/03/16 18:27:38 alstrup Exp $

/* 
 * perm1.cpp
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
#include "Permutation.h"

using namespace std;

int main()
{
  const size_t N = 12;
  Permutation p(N);

  /*
  size_t d[N];
  for(size_t i=0; i<N; ++i)
    d[i] = i;
  */

  p.scramble();
  cout << "Cycles = " << p.cycle_count() << endl;
  cout << " Order = " << p.order() << endl;
  //  p.permute(d);

  //  p.spew(cout);
  //  cout << endl;
    p.spew_cycles(cout);
  cout << endl;
  

  /*
  for(size_t i=0; i<N; ++i)
    cout << d[i] << " ";
  cout << endl;
  */
  return 0;
}




// $Id: perm1.cpp,v 1.5 1999/03/16 18:27:38 alstrup Exp $
