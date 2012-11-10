// This is -*- C++ -*-
// $Id: AsciiImport.h,v 1.4 1999/03/30 01:38:22 hp Exp $

/* 
 * AsciiImport.h
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

#ifndef _INC_ASCIIIMPORT_H
#define _INC_ASCIIIMPORT_H

#include <string>
#include <vector>
#include <algorithm>
#include "DataSet.h"
#include "DataConverter.h"
#include "stringtools.h"
#include "ColumnDivider.h"
#include "AsciiReader.h"
#include "WarningController.h"
#include "Progress.h"

using namespace std;


/*
 * Class that handles import of ASCII files with data in columns.
 *
 * The specification for this file is found in the white paper found 
 * in doc/ascii_import.txt.
 * 
 * This class is a one-shot use class: each instance is used to
 * import one file.  If you want to import another file, or redo the
 * import of a file, you have to create a new AsciiImport instance.
 * One exception is that we support dynamic previews of a portion
 * of the text, and then the life-cycle goes like this:
 *
 *  AsciiImport importer(ascii_reader, warning_controller);
 *  importer.autosetup();  // Try to set up parameters in an intelligent way
 *  importer.import(20);   // Import 20 lines with these parameters
 *  // Display result in importer.headings() and importer.datasets().
 *  // Tweak parameters including importer.column_divider() and
 *  // importer.dataconverters();
 *  importer.import(20);   // Re-import the first 20 lines with the new setup
 *  // Display the new result
 *  // and continue to refine until satisfied with the preview
 *  importer.import();     // and finally import the entire text
 */
class AsciiImport {
public:
  typedef vector<string> Headings;
  typedef vector<DataSet *> Datasets;
  typedef vector<DataConverter *> DataConverters;

  AsciiImport(AsciiReader & ar, WarningController & wc, GooseProgress* gp = 0)
    : ascii_reader_(&ar), warning_controller_(&wc), progress_(gp),
      column_divider_(0), missing_(0), errors_(0), correct_(0), 
      tab_size_(8), paperwidth(0)
  { 
    set_heading_lines(-1);
    ascii_reader().restart(false);
  }

  /*
   * This will read learn_lines lines of data of the file and use that 
   * to set up a bunch of parameters in a hopefully intelligent manner.
   * All read data will be cached for later use.
   */
  void autosetup(int learn_lines = 20);

  /*
   * This will import the text.
   * It works from the beginning of the stream, even if we have
   * read from the stream earlier.
   *
   * At most "lines" number of lines will be read (not counting any headings.)
   * If lines is -1, we read the entire file (this can only be done once.)
   * If lines is positive, we cache the lines for later use; beware of large 
   * imports.)
   *
   * Any imported data will be added at the end of the datasets.
   */
  void import(int lines = -1);

  // Access to the ascii reader for good manners
  AsciiReader & ascii_reader() { return *ascii_reader_; }
  AsciiReader const & ascii_reader() const { return *ascii_reader_; }

  // Access to the warning controller for good manners
  WarningController & warning_controller() { return *warning_controller_; }
  WarningController const & warning_controller() const { return *warning_controller_; }

  /*
   * The specification of how a line is split into columns is
   * handled by the ColumnDivider instance.  We provide access to
   * it so that a user can fine-tune the behaviour of the splitting.
   */
  ColumnDivider & column_divider() { return *column_divider_; }
  ColumnDivider const & column_divider() const { return *column_divider_; }
  void set_column_divider(ColumnDivider & d) { column_divider_ = &d; }

  // The parsing of the values in each column is handled by a DataConverter
  DataConverters & dataconverters() { return dataconverters_; }
  DataConverters const & dataconverters() const { return dataconverters_; }

  // User is responsible for deleting these (I think - Asger?), and
  // typically you don't want them; this convenience function blows
  // them away.
  // AsciiImport::delete_dataconverters(ai.dataconverters())
  
  static void delete_dataconverters(DataConverters& dc);
  
  // The headings of each column
  Headings & headings() { return headings_; }
  Headings const & headings() const { return headings_; }

  // The values kept in each column is handled by a container
  // User must free this stuff too!
  Datasets & datasets() { return datasets_; }
  Datasets const & datasets() const { return datasets_; }

  // Performance parameter: Number of missing elements while importing
  size_t missing() const { return missing_; }

  // Performance parameter: Number of errors while importing
  size_t errors() const { return errors_; }

  // Performance parameter: How many numbers did we get in?
  size_t correct() const { return correct_; }

  // Set-up information
  // Number of lines with headings
  int heading_lines() const { return heading_lines_; }
  void set_heading_lines(int n) { heading_lines_ = n; }

  // Size in characters of tabs
  size_t tab_size() const { return tab_size_; }
  void set_tab_size(size_t t) { tab_size_ = t; }

#if 0
  // We could provide a way to serialize the setup-information
  // and this could serve as the "meta-comment" mechanism as
  // was discussed on the Goose-mailing list.
  // I haven't implemented these, but feel welcome to do it. 
  //
  // I don't think it's a good idea to do it into the ASCII files, but
  // having a way to serialize the setup is useful in other
  // situations as well. (Asger)
  friend ostream & operator << (ostream &, AsciiImport const &);
  friend istream & operator >> (istream &, AsciiImport &);
#endif

private:
  // Check that we got all the columns we need
  // If we got too few, we add empty ones.
  // If we got too many, we cut them off, and return
  // the superflous text.
  string enforceSize(string_tools::strings & result);

  // Try to guess the number of heading lines in the file.
  void autosetup_heading_lines();

  // Try to guess the best kind of column divider.
  void autosetup_column_divider();

  // Try to guess the best kind of data format converters.
  void autosetup_dataconverters();

  // Try to guess the best kind of container
  void autosetup_datasets();

  // This is what we communicate with
  AsciiReader * ascii_reader_;
  WarningController * warning_controller_;

  GooseProgress* progress_;

  // These provide customization of the import
  ColumnDivider * column_divider_;
  DataConverters dataconverters_;

  // These hold the imported data
  Headings headings_;
  Datasets datasets_;

  // Information about the performance of parsing
  size_t missing_; // Missing elements
  size_t errors_; // Errors while importing
  size_t correct_; // Number of element correctly imported

  // How wide is a tab?
  size_t tab_size_;

  // How many lines should we use as headings?
  // If this is -1, autosetup() will try to autodetect.
  int heading_lines_;

  // Here, we keep the learning material
  string_tools::strings learning_lines;
  size_t paperwidth;
};

#endif
