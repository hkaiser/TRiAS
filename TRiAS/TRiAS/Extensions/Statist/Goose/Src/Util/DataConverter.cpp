// This is -*- C++ -*-

/* 
 * DataConverter.cpp
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
 * Copyright (C) 1998 Asger Alstrup Nielsen
 *
 * Developed by Havoc Pennington <hp@pobox.com>
 *          and Asger Alstrup Nielsen <alstrup@diku.dk>
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
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <cstring>
#include <cstdio>

#include "DataConverter.h"
#include "stringtools.h"

// Implementation of the RealConverter ---------------

string RealConverter::kind() const {
  return "Real";
}

// We get a canonical and want a printable
string RealConverter::to_printable(string const & from) const { 
  return to_printable(strtod(from.c_str(), 0));
}


// We get a printable version, and want a canonical returned
string RealConverter::to_canonical(const string & text, string & remains) const {
  // Fix decimal point
  string work = string_tool.replace(text, decimal_point, ".");

  // Remove thousands delimiters
  work = string_tool.replace(text, thousands_seperator, "");

  // Now convert the string into a double to see how much we can handle
  string canonical;
  errno = 0;
  char * upto;
  double d = strtod(work.c_str(), &upto);
  if (errno == 0) {
    // At least we got something
    canonical = to_canonical(d);
  } else {
    // Overflow or underflow.
    // We don't return anything
  }
  remains = work.c_str() + (upto - work.c_str());
  return canonical;
}


// Special real methods
string RealConverter::to_printable(double v) const {
  string format_specifier = "%." + string_tool.int2str(precision);
  if (scientific_notation) {
    format_specifier += "e";
  } else {
    format_specifier += "g";
  }
  char buf[100];
  sprintf(buf, format_specifier.c_str(), v);

  string result = buf;
  result = string_tool.replace(result, ".", decimal_point);

  if (! thousands_seperator.empty()) {
    // Add thousands seperators
    size_t pos = result.find(decimal_point);
    if (pos == result.npos) {
      pos = result.size();
    }
    while (pos >= 4) {
      pos -= 3;
      result.insert(pos, thousands_seperator);
    }
  }
  return result;
}


string RealConverter::to_canonical(double v) const {
  char buf[100];
  sprintf(buf, "%.15g", v);
  return buf;
}


double RealConverter::to_real(string const & from) const {
  string rest;
  string work = to_canonical(from, rest);
  return strtod(work.c_str(), 0);
}


double RealConverter::identify (string const & text) const {
  // TODO: Modify to handle setup information

  string s = text;

  double score = 1.0;

  // if we have an exponent, slice it off and check it
  size_t p = s.find_first_of("eE",0);
  if (p != s.npos) {
    string expo = s.substr(p);
    s.erase(p);
    score = score - exponent_penalty(expo);
  }

  // the empty string is not a real
  if (s.size() == 0)
    return 0.0;

  // check the mantissa
  double errors = 0;
  double ok = 0;
  bool seenDecPt = false;
  for(size_t i=0; i<s.size(); ++i) {
    char c = s[i];
    if (!(isdigit(c) ||
	  (c == '-' && i == 0) || // only allow negative in first place
	  (c == '.' && !seenDecPt))) // only one dec pt per mantissa
      errors++;
    else
      ok++;
    if (c == '.')
      seenDecPt = true;
  }
  score = score - (errors/ok);
  return (score >= 0.0) ? score : 0.0;
}


// How nice is this string as an exponent?
double RealConverter::exponent_penalty(string const & expo) const {
  if (expo.size() < 2) {
    // We loose 10% for missing stuff after e.
    return 0.10;
  }

  // make sure that both the 1e10, 1e+10 and 1e-10 type notation
  // is handled correctly
  if (expo[1] == '-' || expo[1] == '+') {
    if (expo.size() < 3) {
      // We loose 10% for exponent with sign, but without numbers
      return 0.10;
    }
  } else if (!isdigit(expo[1])) {
    // We have an exponent, but no numbers: Loose 10%
    return 0.10;
  }

  // make sure that the exponent contains only digits
  if (expo.find_first_not_of("0123456789",2) != expo.npos) {
    // We have an exponent, with some garbage: Loose 5%
    return 0.05;
  }
  return 0.0;
}


void RealConverter::autosetup(vector<string> const & /* learning */) {
  // TODO: Modify to extract setup information
}

// Implementation of the StringConverter ---------------

string StringConverter::kind() const {
  return "String";
}

string StringConverter::to_printable(string const & v) const {
//  return quote + v + quote;
  return v;
}

string StringConverter::to_canonical(string const & v, string & /* remains */) const {
  string result = v;
  if (!quote.empty()) {
    result = string_tool.trim(result, quote);
  }
  return result;
}

double StringConverter::identify(string const & v) const {
  if (!quote.empty()) {
    if (v.size() < 2 || string_tool.prefix(v, quote) || string_tool.suffix(v, quote)) {
      // We miss quotes - loose 10%
      return 0.9;
    }
  }
  return 1.0;
}

void StringConverter::autosetup(vector<string> const & learning) {
  double quotes = 0.0;
  for (vector<string>::const_iterator i = learning.begin();
       i != learning.end(); ++i) {
    if ((*i).size() >= 2 && (*i)[0] == '"' && *((*i).end()-1) == '"') {
      quotes += 1.0;
    }
  }
  quotes = quotes / learning.size();
  if (quotes > 0.80) {
    quote = "\"";
  }
}
