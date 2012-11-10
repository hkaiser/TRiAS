// This is -*- C++ -*-
// $Id: stringtools.h,v 1.2 1999/03/16 18:29:34 alstrup Exp $

/* 
 * stringtools.h
 *
 * Copyright (C) 1998 Asger Alstrup Nielsen
 *
 * Developed by Asger Alstrup Nielsen <alstrup@diku.dk>
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

#ifndef _INC_STRINGTOOLS_H
#define _INC_STRINGTOOLS_H

#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

/*
 * This is a struct that keeps a bunch of useful string manipulation routines.
 * By using a template, we can more easily add support for strings of
 * wide characters later.  (Though as it stands, I'm sure that several of
 * these functions are char-string specific.)
 *
 * We create a dummy instance of this struct for notational convenience.
 */
template<class str>
struct basic_string_tools {

  // A vector of strings
  typedef vector<str> strings;

  static str trim(const str& s, const str& trim_chars = " \t");
  static str cut(const str& s, const str& trim_chars = " \t");
  static str rcut(const str& s, const str& trim_chars = " \t"); 
  static str concatenate_words(const str& s1, const str& s2);
  
  static str to_upper(const str& s);
  static str to_lower(const str& s);

  static str substring(const str& s, size_t i1, size_t i2);
  static void split(const str& s, const str& delimiter,
		    str& head, str& tail,
		    bool keep_delimiter_in_tail = false);

  static bool prefix(const str& s, const str& prefix) {
    return s.find(prefix) == 0;
  }

  static bool suffix(const str& s, const str& prefix) {
    return s.rfind(prefix) == (s.size() - prefix.size());
  }

  // Replace all instances of a string with another string
  static str replace(str const & line, str const & from, str const & to) {
    if (from == to || from.empty())
      return line;
    str l = line;
    size_t pos = 0;
    while(true) {
      pos = l.find(from, pos);
      if (pos == l.npos)
	break;
      l.erase(pos, from.size());
      l.insert(pos, to);
      pos += to.size();
    }
    return l;
  }

  /*
   * Convert an integer to a string
   *
   * int2str(10) = "10";
   */
  static str int2str(int v) {
    char buf[10];
    sprintf(buf, "%d", v);
    return str(buf);
  }

  static str int2str(unsigned int v) {
    char buf[10];
    sprintf(buf, "%u", v);
    return str(buf);
  }

  static str expand_tabs(const str& line, size_t tab_size = 8);

  static bool is_number_char(str c) { return isdigit(c[0]); }

  // Could this character be part of a line of numbers,
  // but also is it also likely to be part of a line of headings?
  static bool ambigious_number_char(str c) {
    return c[0] == '.' || c[0] == ',' || c[0] == 'e' || c[0] == 'E' 
      || c[0] == '+' || c[0] == '-' || c[0] == ' ' || c[0] == '\t';
  }
};

typedef basic_string_tools<string> string_tools;
extern string_tools string_tool;

//////////////////////////////////////////////////////////////////////////////

/*
 * Trims characters off at both ends of the string.
 *
 * trim("  abc  ") == "abc" == trim("..abc..", ".");
 */
template<class str>
str
basic_string_tools<str>::trim(const str& s, const str& trim_chars)
{
  return cut(rcut(s, trim_chars), trim_chars);
}

/*
 * Cuts characters off at the front of the string.
 *
 * cut("  abc  ") == "abc  " == cut("..abc..", "abc..");
 */
template<class str>
str
basic_string_tools<str>::cut(const str& s, const str& trim_chars)
{
  if (trim_chars.empty() || s.empty() ||
      s.find_first_of(trim_chars) == s.npos) return s;
  str work = s;
  size_t pos = work.find_first_not_of(trim_chars);
  if (pos == work.npos) 
    work.erase(work.begin(), work.end());
  else if (pos != 0) 
    work.erase(0, pos);

  return work;
}

/*
 * Cuts characters off at the end of the string.
 *
 * rcut("  abc  ") == "  abc" == rcut("..abc..", "..abc");
 */
template<class str>
str
basic_string_tools<str>::rcut(const str& s, const str& trim_chars)
{
  if (trim_chars.empty() || s.empty() ||
      s.find_first_of(trim_chars) == s.npos) return s;
  str work = s;
  size_t pos = work.find_last_not_of(trim_chars);
  if (pos != work.npos) {
    work = substring(work, 0, pos);
  } else {
    // It seems that my STL library is buggy, so we need this:
    work = substring(work, 0, work.find_first_of(trim_chars) - 1);
    // rather than work.clear();
  }
  return work;
}

/*
 * Adds two strings such that it looks nice.
 *
 * concatenate_words("This", "is a test") == "This is a test";
 * concatenate_words("Empty", "") == "Empty";
 * concatenate_words("", "Empty") == "Empty";
 * concatenate_words("", "") == "";
 * concatenate_words(" This ", " is a test ") == "This is a test";
 */
template<class str>
str
basic_string_tools<str>::concatenate_words(const str& s1, const str& s2)
{
  str work = trim(s1);
  if (!work.empty()) {
    work += ' ';
  }
  work += cut(s2);
  return rcut(work);
}

template<class str>
str
basic_string_tools<str>::to_upper(const str& s)
{
  str t = s;
  for(size_t i=0; i<t.size(); ++i)
    if (islower(t[i])) t[i] = toupper(t[i]);
  return t;
}

template<class str>
str
basic_string_tools<str>::to_lower(const str& s)
{
  str t = s;
  for(size_t i=0; i<t.size(); ++i)
    if (isupper(t[i])) t[i] = tolower(t[i]);
  return t;
}

/*
 * Extract a piece of a string.
 * Contrary to the STL substr, this method takes two
 * indexes, rather than an index and a length.
 *
 * Also, indexes beyond the end of the string are handled
 * in a tolerant manner.
 */
template<class str>
str
basic_string_tools<str>::substring(const str& s, size_t i1, size_t i2)
{
  if (i1 >= s.length() || i1 > i2) 
    return str();
  
  if (i2 >= s.length()) 
    i2 = s.length() - 1;
  
  str result = s.substr(i1, (i2-i1) + 1);
  return result;
}

/*
 * Split a string at a given delimiter.
 *
 * str head, tail;
 * split("This is a -!- test -!-", "-!-", head, tail);
 * head == "This is a " ; tail == " test -!-";
 * split("This is a -!- test -!-", "-!-", head, tail, true);
 * head == "This is a " ; tail == "-!- test -!-";
 * split("This is a test", "-!-", head, tail);
 * head == "This is a test" ; tail == "";
 */
template<class str>
void
basic_string_tools<str>::split(const str& s, const str& delimiter,
			       str& head, str& tail,
			       bool keep_delimiter_in_tail)
{
  size_t pos = s.find(delimiter);
  if (pos == s.npos) {
    head = s;
    tail = str();
  } else {
    head = pos == 0 ? string() : substring(s, 0,pos-1);
     if (!keep_delimiter_in_tail) 
      pos += delimiter.length();
     tail = substring(s, pos, s.length());
  }
}

/*
 * Expand tabs
 */
template<class str>
str
basic_string_tools<str>::expand_tabs(const str& line, size_t tab_size)
{
  str l = line;
  size_t pos;
  while( (pos = l.find("\t")) != l.npos ) {
    int amount = tab_size - (pos % tab_size);
    l.erase(pos, 1);
    l.insert(pos, amount, ' ');
  }
  return l;
}

#endif
