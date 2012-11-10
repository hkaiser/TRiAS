// This is -*- C++ -*-
// $Id: ColumnDivider.cpp,v 1.2 1999/03/16 18:27:59 alstrup Exp $

/* 
 * ColumnDivider.cpp
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

#include <config.h>
#include "ColumnDivider.h"
#include <algorithm>

// #include <iostream>

void FixedColumns::autosetup(string_tools::strings const & lines, size_t paperwidth) { 
  spans_.clear();
  // If we don't get any learning material, we define the
  // column to be the entire line
  if (lines.empty()) {
    Span s(0, paperwidth);
    spans_.push_back(s);
    set_columns(1);
    return;
  }

  learn = lines;
  // Expand tabs
  for (string_tools::strings::iterator i = learn.begin(); i < learn.end(); ++i) {
    *i = string_tool.expand_tabs(*i, tab_size());
  }

  // How much non-whitespace is allowed in an empty column?
  size_t threshold = size_t(learn.size() * 0.05);
  if (learn.size() >= 10) {
    threshold += 1;    // We cut some slack
  }

  // TODO: Refine this algorithm by first collecting the numbers
  // for each column.  Then iterate over the numbers to filter
  // out too small columns.  Then iterate to find the break-points
  // in the middle of empty spans if no bias exist.
  // When we have bias, we want to be more clever:
  // We want to break [4 4 4 0 0 1 4 4] as [4 4 4] [0 0 1 4 4].
  // We want to break [4 4 1 0 0 4 4 4] as [4 4 1 0 0] [4 4 4].

  bool lastempty = true;
  size_t colstart = 0;
  bool open = false;

  for (size_t i=0; i <= paperwidth; ++i) {
    bool empty = countColumn(i, threshold) <= threshold;

    if (!empty)
      open = true;
    else if (!lastempty) {
      // We demand that a column is at least two characters wide
      if ((i-1) - colstart > 1) {
	Span s(colstart, i-1);
	spans_.push_back(s);
	colstart = i;
	open = false;
      }
    }
    lastempty = empty;
  }
  if (open) {
    Span s(colstart, paperwidth);
    spans_.push_back(s);
  } else {
    spans_.back().second = paperwidth;
  }
  set_columns(spans_.size());

#if 0
  for (Spans::const_iterator i= spans_.begin(); i != spans_.end(); i++) {
    cout << "[" << i->first << ", " << i->second << "] ";
  }
  cout << endl;
#endif
}

// Counts how many non-white-space characters we have in a particular column
// If the count surpassed a threshold, we return the threshold
size_t FixedColumns::countColumn(size_t col, size_t threshold) {
  size_t not_whitespace = 0;
  for (string_tools::strings::iterator j = learn.begin(); j < learn.end(); ++j) {
    if (col < (*j).length() && (*j)[col] != ' ') {
      ++not_whitespace;
      if (not_whitespace > threshold)
	return not_whitespace;
    }
  }
  return not_whitespace;
}

// Split a line into strings
string_tools::strings FixedColumns::split(string const & line) {
  string l = string_tool.expand_tabs(line, tab_size());

  string_tools::strings result;
  for (Spans::const_iterator s = spans().begin(); s < spans().end(); ++s) {
    size_t from = (*s).first;
    size_t to = (*s).second;
    string col;
    if (from < l.length()) {
      if (to > l.length())
	to = l.length() - 1;
      col = string_tool.substring(l, from, to);
      if (handle_spill() && l[to] != ' ') {
	// Ok, we have to handle spilling.
	++to;
	while (l[to] != ' ' && to < l.length()) {
	  col += l[to];
	  l.erase(to, 1);
	}
      }
    }
    result.push_back(col);
  }
  return result;
}



void DelimitDivider::autosetup(string_tools::strings const & lines, size_t paperwidth) { 
  // Without learning material, we assume whitespace is the delimiter
  // and we only have one column
  if (lines.empty()) {
    set_delimiter(" "); 
    set_whitespace(" \t");
    set_columns(1);
    return;
  }

  // Else, we try each delimiter, and chooses the one with most columns
  string_tools::strings delimiters;
  string_tools::strings whitespaces;
  delimiters.push_back(";");  whitespaces.push_back(" \t");
  delimiters.push_back(":");  whitespaces.push_back(" \t");
  delimiters.push_back("/");  whitespaces.push_back(" \t");
  delimiters.push_back("|");  whitespaces.push_back(" \t");
  delimiters.push_back("*");  whitespaces.push_back(" \t");
  delimiters.push_back(",");  whitespaces.push_back(" \t");
  delimiters.push_back(" ");  whitespaces.push_back(" \t");
  delimiters.push_back("\t"); whitespaces.push_back(" \t");

  size_t most_columns = 0;
  size_t most_frequent = 0;
  int best_delimiter = 0;
  // How many of the training-lines had this number of columns?
  Numbers delimiter_frequency;
  for (size_t i = 0 ; i < delimiters.size(); ++i) {
    set_delimiter(delimiters[i]);
    set_whitespace(whitespaces[i]);

//    cout << "Delimiter: '" << delimiter() << "' Whitespace: '" << whitespace() << "':\n";

    // The number of columns for each training-line
    Numbers columns;
    for (string_tools::strings::const_iterator l=lines.begin(); l < lines.end(); ++l) {
      size_t cols = split(*l).size();
      columns.push_back(cols);
//      cout << cols << " ";
    }
    // The number of columns for this delimiter is the one
    // that appears the most
    size_t most_com = most_common(columns);
    size_t frequency = count(columns.begin(), columns.end(), most_com);
//    cout << " most common: " << most_com << " freq: " << frequency << "\n";
    if (most_com > 1 && frequency > most_frequent) {
      most_columns = most_com;
      best_delimiter = i;
      most_frequent = frequency;
    }
  }

#if 0
  cout << "Most columns: " << most_columns << " frequency: " << most_frequent
       << " delimiter '" << delimiters[best_delimiter].c_str() << "' whitespace '"
       << whitespaces[best_delimiter].c_str() << "'\n";
#endif

  set_delimiter(delimiters[best_delimiter]);
  set_whitespace(whitespaces[best_delimiter]);
  set_columns(most_columns);
}

// Returns the most common value in a list
size_t DelimitDivider::most_common(Numbers const & list) {
  size_t max_value = *max_element(list.begin(), list.end());

  Numbers frequency(max_value + 1, 0);
  for (Numbers::const_iterator i = list.begin(); i < list.end(); ++i) {
    ++frequency[*i];
  }

  return max_element(frequency.begin(), frequency.end()) - frequency.begin();
}

string_tools::strings DelimitDivider::split(string const & l) {
  // TODO: Add the special handling such that a delimiter ", "
  //       with whitespace " \t" will make the delimiter match ",\t" too.
  // This is needed to be able to handle strings like "12,2, 23,0, 25,2, 23,0"

  string line = l;
  string_tools::strings result;
  while (!line.empty()) {
    string col;
    string_tool.split(line, delimiter(), col, line);
    col = string_tool.trim(col, whitespace());
    result.push_back(col);
//       cout << "<" << col.c_str() << ">";
    line = string_tool.cut(line, whitespace());
  }
//    cout << "\n";
  return result;
}
