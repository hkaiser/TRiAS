// This is -*- C++ -*-
// $Id: zdouble.h,v 1.3 1999/07/20 08:34:28 alstrup Exp $

/* 
 * zdouble.h
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
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


#ifndef _INC_ZDOUBLE_H
#define _INC_ZDOUBLE_H

#include <string>
//using std::string;

void encode_double(double x, char* buffer);
double decode_double(const char*& buffer);

string encode_double(double x);
double decode_double(const string&);

#endif // _INC_ZDOUBLE_H

// $Id: zdouble.h,v 1.3 1999/07/20 08:34:28 alstrup Exp $
