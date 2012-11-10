// This is -*- C++ -*-
// $Id: jack_test.cpp,v 1.9 1999/03/16 18:27:36 alstrup Exp $

/* jack_test.cpp
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
#include "jackknife.h"

using namespace std;

int main()
{
  RealSet ds;
  for(int i=1; i<=6; ++i) ds.add(i);
  RealSet jack = jackknife_median(ds);
  for(size_t i=0; i<jack.size(); ++i)
    cout << jack.data(i) << endl;
  return 0;
}


// $Id: jack_test.cpp,v 1.9 1999/03/16 18:27:36 alstrup Exp $
