// This is -*- C++ -*-
// $Id: rand1.cpp,v 1.9 1999/03/16 18:27:39 alstrup Exp $

/* rand1.cpp
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
#include <iostream>
#include "Random.h"

using namespace std;

int main(int argc, char* argv[])
{
  int count = 0;

  if (argc == 2) 
    count = atoi(argv[1]);

  if (count <= 0)
    count = 100;

  Random rnd;

  for(int i=0;i<count;++i)
    cout << rnd.random_normal() << " ";
  cout << endl;
  return 0;
}


// $Id: rand1.cpp,v 1.9 1999/03/16 18:27:39 alstrup Exp $
