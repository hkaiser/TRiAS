// This is -*- C++ -*-
// $Id: Exception.h,v 1.4 1999/07/09 19:44:32 trow Exp $

/* 
 * Exception.h
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

#ifndef _INC_EXCEPTION_H
#define _INC_EXCEPTION_H

#include <string>

using namespace std;

// Base class for exceptions

class Exception {
public:
  Exception() : cause_("?") { }
  Exception(string const & s) : cause_(s) { }

  virtual ~Exception() { }

  virtual string const & what() const { return cause_; }

protected:
  void set_cause(const string& s) { cause_ = s; }

private:
  string cause_;
};

// Some useful types of exceptions

class Exception_IndexOutOfBounds : public Exception {
public:
  Exception_IndexOutOfBounds(int ind, int low, int hi);
};

class Exception_MustBeNonZero : public Exception {
public:
  Exception_MustBeNonZero(const string& s);
};

class Exception_MustBePositive : public Exception {
public:
  Exception_MustBePositive(const string& s);
};

class Exception_IllegalSize : public Exception {
public:
  Exception_IllegalSize(int sz);
};

class Exception_SizesDoNotMatch : public Exception {
public:
  Exception_SizesDoNotMatch();
};

class Exception_InternalError : public Exception {
public:
  Exception_InternalError();
};

#endif
