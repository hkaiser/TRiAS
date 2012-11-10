// This is -*- C++ -*-
// $Id: DataSet.cpp,v 1.6 1999/07/20 21:20:04 trow Exp $

/* 
 * DataSet.cpp
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
#include "DataSet.h"

int DataSet::default_offset_ = 0;
const DataSet::type_t DataSet::invalid_typecode = 0x0;

// Useful for debugging
void DataSet::spew(ostream& out, char sep) const {
  int i0 = min_index(), i1 = max_index();
  for(int i=i0; i<=i1; ++i)
    out << as_string(i) << sep;
  if (sep != '\n') out << endl;
}


// $Id: DataSet.cpp,v 1.6 1999/07/20 21:20:04 trow Exp $
