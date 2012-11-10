// This is -*- C++ -*-
// $Id: ColumnDivider.h,v 1.2 1999/03/16 18:28:00 alstrup Exp $

/* 
 * ColumnDivider.h
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

#ifndef _INC_COLUMNDIVIDER_H
#define _INC_COLUMNDIVIDER_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include "stringtools.h"

using namespace std;

/*
 * Base class for column dividers.
 *
 * This class hierarchy provides a way to split up a line into columns.
 * Notice that this class does not concern itself with what the data
 * in a column means, only the issue of splitting up the data into
 * strings is addressed.
 */
class ColumnDivider {
public:
  virtual ~ColumnDivider()
  { }

  /*
   * Given a bunch of lines, try to set up automatically.
   * The paperwidth is the width of the input we have to cope with.
   * Sometimes, the headings will be wider, but the column dividier
   * has to handle that in a sane way anyway.
   */
  virtual void autosetup(string_tools::strings const & /* lines */, size_t /* paperwidth */) 
  { }

  /*
   * Splits up a line into separate columns according to the
   * behaviour defined.
   * If we encounter an error-situation, we throw an Exception.
   */
  virtual string_tools::strings split(string const & line) = 0;

  // How many columns?
  virtual size_t columns() const { return columns_; }
  virtual void set_columns(size_t c) { columns_ = c; }

  // How wide is a tab?
  virtual size_t tab_size() const { return tab_size_; }
  virtual void set_tab_size(size_t t) { tab_size_ = t; }

protected:
  ColumnDivider(size_t tabs = 8) : tab_size_(tabs), columns_(0)
  { }

private:
  size_t tab_size_;
  size_t columns_;
};


/*
 * A specialized column divider that handles fixed width columns.
 *
 * A column is defined by a character span.  As a further refinement,
 * we optionally allow columns to spill beyond their bounds.  In that
 * case, the columns are separated with white-space.
 */
class FixedColumns : public ColumnDivider {
public:
  typedef pair<size_t, size_t> Span;
  typedef vector<Span> Spans;

  FixedColumns(size_t tabsize = 8) : ColumnDivider(tabsize),
    handle_spill_(true) { }
  ~FixedColumns() { }

  void autosetup(string_tools::strings const & lines, size_t paperwidth);

  string_tools::strings split(string const & line);

  // We provide access to the setup-information
  Spans & spans() { return spans_; }
  Spans const & spans() const { return spans_; }

  bool handle_spill() { return handle_spill_; }
  void set_handle_spill(bool b) { handle_spill_ = b; }

private:
  // Counts how many non-white-space characters we have in a given column
  // but stops when threshold has been reached
  size_t countColumn(size_t pos, size_t threshold);

  // This is the setup-information
  Spans spans_;
  bool handle_spill_;

  // Housekeeping when doing autosetup
  string_tools::strings learn;
};


/*
 * A specialized column class that handles delimited columns.
 *
 * A delimiter is defined by two strings:
 * A fixed length obligatory string,
 * and a string containing a set of white-space characters that
 * are to be ignored.
 */
class DelimitDivider : public ColumnDivider {
public:
  DelimitDivider(size_t tabsize = 8) : 
    ColumnDivider(tabsize), delimiter_(";"), whitespace_(" \t") { }

  ~DelimitDivider() { }

  void autosetup(string_tools::strings const & lines, size_t paperwidth);

  string_tools::strings split(string const & l);

  // We provide access to the setup-information
  string const & delimiter() { return delimiter_; }
  void set_delimiter(string const & s) { delimiter_ = s; }

  string const & whitespace() { return whitespace_; }
  void set_whitespace(string const & s) { whitespace_ = s; }
private:
  typedef vector<size_t> Numbers;
  // Returns the most common element (linear time)
  size_t most_common(Numbers const &);

  string delimiter_;
  string whitespace_;
};

#endif
