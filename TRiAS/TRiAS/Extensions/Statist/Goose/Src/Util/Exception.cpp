// This is -*- C++ -*-
// $Id: Exception.cpp,v 1.1 1999/07/09 19:44:32 trow Exp $

/* 
 * Exception.cpp
 *
 * Copyright (C) 1998, 1999 Asger Alstrup Nielsen
 *
 * Developed by Asger Alstrup Nielsen <alstrup@diku.dk> and
 * Jon Trowbridge <trow@emccta.com>.
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
#include <Exception.h>
#include <stringtools.h>

Exception_IndexOutOfBounds::Exception_IndexOutOfBounds(int ind,
						       int low, int hi) :
  Exception()
{
  string c = "Index value is ";
  c += string_tool.int2str(ind);
  c += ", must be between ";
  c += string_tool.int2str(low);
  c += " and ";
  c += string_tool.int2str(hi);
  set_cause(c);
}

Exception_MustBeNonZero::Exception_MustBeNonZero(const string& s) :
  Exception(s + " must be non-zero")
{ }

Exception_MustBePositive::Exception_MustBePositive(const string& s) :
  Exception(s + " must be positive")
{ }

Exception_IllegalSize::Exception_IllegalSize(int sz) : Exception()
{
  string c;

  // Try to generate a reasonable error message.

  if (sz == 0) {
    c = "A non-zero size is required.";
  } else {
    c = string_tool.int2str(sz);
    if (sz < 0)
      c += ", being negative,";
    c += " is an illegal size in this context.";
  }
  set_cause(c);
}

Exception_SizesDoNotMatch::Exception_SizesDoNotMatch()
{
  set_cause("Sizes do not match.");
}

Exception_InternalError::Exception_InternalError()
{
  set_cause("*** Internal Error ***");
}


// $Id: Exception.cpp,v 1.1 1999/07/09 19:44:32 trow Exp $
