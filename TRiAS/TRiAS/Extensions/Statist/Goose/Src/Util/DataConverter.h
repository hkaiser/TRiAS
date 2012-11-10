// This is -*- C++ -*-

/* 
 * DataConverter.h
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

#ifndef _INC_DATACONVERTER_H
#define _INC_DATACONVERTER_H

#include <string>
#include <vector>

using namespace std;

/*
 * This is the base class for a DataConverter hierarchy
 * which can convert a internationalized/printable string 
 * representations of a value into a canonical string 
 * representation.
 */
class DataConverter {
public:
  virtual ~DataConverter() {}

  virtual DataConverter * clone() const {
    return new DataConverter();
  }

  /*
   * Parse a string and return the result in canonical format.
   *
   * We return the amount of the string that was not parsed in
   * 'remains'. The method should try hard to get some useful information
   * out of the string.
   * If the parsing fails, the returned string can be empty. 
   */
  virtual string to_canonical(string const & from, string & /* remains */) const { return from; }

  /*
   * Convert a canonical value into printable format.
   *
   * Notice that you can loose information in this format.
   */
  virtual string to_printable(string const & canonical) const { return canonical; }

  /* 
   * How likely is it that this string is of this type?
   * Returns a "probability" in the range [0,1], where 1.0 signifies
   * that the parse() method will be able to parse it without
   * any error.  0.0 signifies that parse() will not be able to do
   * much with the string.
   * This is used for identifying the type of strings.
   */
  virtual double identify(string const &) const { return 0.0; }

  // Set up parameters for string parsing from a bunch of examples
  virtual void autosetup(vector<string> const & /* learning */) { }

  // What kind of converter is this?
  virtual string kind() const { return "Data"; }
};

/* 
 * A real number.
 *
 * The canonical representation of a double is the one
 * which the %G printf format specifier produces.
 */
class RealConverter : public DataConverter {
public:
  RealConverter() : decimal_point("."), thousands_seperator(","), 
		    scientific_notation(false), precision(15) { }

  RealConverter(RealConverter const & r) : decimal_point(r.decimal_point), 
      thousands_seperator(r.thousands_seperator), 
      scientific_notation(r.scientific_notation), 
      precision(r.precision) { }

  DataConverter * clone() const {
    return new RealConverter(*this);
  }

  string to_canonical(string const & from, string & remains) const;
  string to_printable(string const & canonical) const;
  double identify(string const & v) const;
  void autosetup(vector<string> const & learning);
  string kind() const;

  // Special real methods
  string to_printable(double v) const;
  string to_canonical(double v) const;
  double to_real(string const & from) const;
  
  string get_decimal_point() const { return decimal_point; }
  void set_decimal_point(string const & p) { decimal_point = p; }

  string get_thousands_seperator() const { return thousands_seperator; }
  void set_thousands_seperator(string const & s) { thousands_seperator = s; }

  bool get_scientific_notation() const { return scientific_notation; }
  void set_scientific_notation(bool b) { scientific_notation = b; }

  int get_precision() const { return precision; }
  void set_precision(int p) { precision = p; }
private:
  double exponent_penalty(string const &) const;
  string decimal_point;
  string thousands_seperator;
  bool scientific_notation;
  int precision;
};


// A string
class StringConverter : public DataConverter {
public:
  StringConverter() { }
  StringConverter(StringConverter const & s) : quote(s.quote) { }

  DataConverter * clone() const {
    return new StringConverter(*this);
  }

  string to_canonical(string const & from, string & remains) const;
  string to_printable(string const & canonical) const;
  double identify(string const & v) const;
  void autosetup(vector<string> const & learning);
  string kind() const;

  // Special string methods

  // To ordinary string
  string to_string(string const &) const;

private:
  // Here, we should have information about quoting
  // strings, and how to escape strings
  string quote;
};

#endif // _INC_DATACONVERTER_H
