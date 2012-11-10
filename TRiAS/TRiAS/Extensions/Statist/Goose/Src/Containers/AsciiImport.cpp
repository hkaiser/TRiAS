// This is -*- C++ -*-
// $Id: AsciiImport.cpp,v 1.8 1999/05/17 23:52:07 hp Exp $

/* 
 * AsciiImport.cpp
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
#include "AsciiImport.h"
#include "RealSet.h"
#include "StringSet.h"

void AsciiImport::autosetup(int learn_lines) {
  warning_controller().sleep();

  if (heading_lines() == -1) {
    autosetup_heading_lines();
  }

  // Now, skip the headings while keeping track of the maximum width
  ascii_reader().restart(true);
  paperwidth = 0;
  for (int i=0; i < heading_lines(); ++i) {
    size_t l = string_tool.expand_tabs(ascii_reader().readline(), 
				       tab_size()).length();
    if (l == 0) return;
    if (l > paperwidth) paperwidth = l;
  }

  // Then collect the learning material
  learning_lines.clear();
  for (int i=0; i < learn_lines; ++i) {
    string line = ascii_reader().readline();
    if (line.empty()) break;
    size_t width = string_tool.expand_tabs(line, tab_size()).length();
    if (width > paperwidth) paperwidth = width;
    learning_lines.push_back(line);
  }

  // Now, determine and setup the kind of column divider we have
  if (column_divider_ == 0) {
    autosetup_column_divider();
  } else {
    column_divider().autosetup(learning_lines, paperwidth);
  }
  // Set up the data converters
  autosetup_dataconverters();
  // And finally, set up the data sets
  autosetup_datasets();
  warning_controller().wake_up();
}

// This imports the data
void AsciiImport::import(int lines) {
  ascii_reader().restart(lines != -1);

  // Reset performance results
  missing_ = 0;
  errors_ = 0;
  correct_ = 0;

  // First, we create the empty headings
  headings().clear();
  while (headings().size() <= column_divider().columns()) {
    headings().push_back(string());
  }

  // Then we read the headings
  for (int i=0; i < heading_lines(); ++i) {
    string line = ascii_reader().readline();
    if (line.empty())
      break;
    string_tools::strings cols = column_divider().split(line);
    string superflous = enforceSize(cols);
    for (size_t j=0; j < cols.size(); ++j) {
      headings()[j] = string_tool.concatenate_words(headings()[j], cols[j]);
      // If there was superflous text, add it into the heading
      if (!superflous.empty() && j == cols.size() - 1) {
	headings()[j] = string_tool.concatenate_words(headings()[j], superflous);
      }
    }
  }

  for (unsigned int i=0; i < column_divider().columns(); ++i) {
    datasets()[i]->set_label(headings()[i]);
  }

  if (progress_ != 0)
    {
      progress_->start();
      progress_->set_operation("Reading file...");
    }

  // And then the data
  int l = 0;
  while (l < lines || lines == -1) {
    if (progress_ != 0)
      {
        if (l % 100 == 0) // should really be based on time, but.
          {
            if (progress_->cancelled())
              break; // stop the loop

            if (lines == -1)
              {
                progress_->pulse();
              }
            else
              {
                progress_->set_percent(float(l)/float(lines));
              }
          }
      }

    // Get a row
    string line = ascii_reader().readline();

    if (line.empty())
      break;
    ++l;

    // Split it up
    string_tools::strings cols = column_divider().split(line);
    string superflous = enforceSize(cols);
    if (!superflous.empty()) {
      ++errors_;
      warning_controller().warn(string("Ignoring superflous text '") + superflous + string("'"));
    }

    // And feed it into the container
    for (size_t i=0; i < cols.size(); ++i) {
      string canonical_value;
      if (cols[i].empty()) {
	++missing_;
      } else {
	string superflous;
	canonical_value = dataconverters()[i]->to_canonical(cols[i], superflous);
	if (superflous == cols[i]) {
	  ++errors_;
	  warning_controller().warn(string("Error parsing string '") + cols[i] + string("'"));
	} else if (!superflous.empty()) {
	  warning_controller().warn(string("Superflous chars '") + superflous + 
				    string("' parsing string '") + cols[i] + string("'"));
	  // We count it as a half correct
	  ++correct_;
	} else {
	  // A correct gets two points
	  ++correct_;
	  ++correct_;
	}
      }
      if (canonical_value.empty() && !datasets()[i]->support_missing()) {
	// If we didn't get any value, and do not support missing data,
	// and give a warning to this effetc
	warning_controller().warn(string("Using default value in row ") 
				  + string_tool.int2str(datasets()
							[i]->size() + 1) 
				  + string(" column ")
				  + string_tool.int2str(i)
				  + string(" because of missing data."));
      }
      datasets()[i]->push_back(canonical_value);
    }
  }

  if (progress_ != 0)
    progress_->stop();
}


string AsciiImport::enforceSize(string_tools::strings & result) {
  string msg;
  size_t size = column_divider().columns();
  // Is the size correct?
  if (result.size() != size) {
    string empty;
    while (result.size() < size) {
      result.push_back(empty);
    }
    while (result.size() > size) {
      string last=result.back();
      result.pop_back();
      if (!msg.empty()) {
	msg = string("' '") + msg;
      }
      msg = last + msg;
    }
  }
  return msg;
}


// Try to determine number of heading lines
void AsciiImport::autosetup_heading_lines() {
  // Algorithm:  When the number of numbers in a line
  // is higher than the number of letters, we have data.
  // The characters ',', '.', 'e', 'E', tab and space
  // are judged ambigious, and thus not included in either count.
  ascii_reader().restart(true);

  set_heading_lines(0);
  for (int i=0; i < 10; ++i) {
    string line = ascii_reader().readline();
    if (line.empty()) 
      return;
    size_t count_of_number_chars = 0;
    size_t count_of_heading_chars = 0;
    for (size_t j = 0; j < line.length(); ++j) {
      char buf[2]; buf[0] = line[j]; buf[1] = 0;
      if (string_tool.is_number_char(buf))
	++count_of_number_chars;
      else if (!string_tool.ambigious_number_char(buf)) 
	++count_of_heading_chars;
    }
    if (count_of_number_chars > count_of_heading_chars) {
      set_heading_lines(i);
      return;
    }
  }
  warning_controller().warn("Confused about headings. Assuming there are no headings.");
  set_heading_lines(0);
}


// Try to determine the best column divider setup
void AsciiImport::autosetup_column_divider()
{
  // If we have one, get rid of it
  if (column_divider_ != 0) {
    delete column_divider_;
    column_divider_ = 0;
  }

  // We have to decide which kind of divider we want
  // Algorithm:  Try all available kinds, and then
  // choose the one with the best performance
  DataConverters original_dataconverters = dataconverters();
  Datasets original_datasets = datasets();

  FixedColumns * fixed = new FixedColumns(tab_size());
  fixed->autosetup(learning_lines, paperwidth);
  column_divider_ = fixed;
  autosetup_dataconverters();
  autosetup_datasets();
  import(learning_lines.size());
  int score = correct() - errors();
  dataconverters_ = original_dataconverters;
  datasets_ = original_datasets;
  
  DelimitDivider * delimit = new DelimitDivider();
  delimit->autosetup(learning_lines, paperwidth);
  column_divider_ = delimit;
  autosetup_dataconverters();
  autosetup_datasets();
  import(learning_lines.size());
  dataconverters_ = original_dataconverters;
  datasets_ = original_datasets;

  if (score >= int(correct() - errors())) {
    column_divider_ = fixed;
    delete delimit;
  } else {
    column_divider_ = delimit;
    delete fixed;
  }
}


// Try to setup the best data converters for each column
void AsciiImport::autosetup_dataconverters() {

  for (size_t i=dataconverters().size(); i < column_divider().columns(); ++i) {
    vector<string> training_column;
    for (string_tools::strings::const_iterator j = learning_lines.begin(); 
         j != learning_lines.end(); ++j) {
      string line = *j;
      string_tools::strings cols = column_divider().split(line);
      string superflous = enforceSize(cols);
      training_column.push_back(cols[i]);
    }

    // Now try each DataConvert until we find the best
    RealConverter realconverter;
    realconverter.autosetup(training_column);
    double score = 0.0;
    for (vector<string>::const_iterator i= training_column.begin();
         i != training_column.end(); ++i) {
      score += realconverter.identify(*i);
    }

//    warning_controller().warn("Score for column " + string_tool.int2str(i) + " is: " + 
//                            string_tool.int2str(int(score * 100.0)));

    score = score / training_column.size();
    if (score >= 0.80) {
      RealConverter * type = new RealConverter;
      type->autosetup(training_column);
      dataconverters().push_back(type);
      RealSet * data = new RealSet;
      datasets().push_back(data);
    } else {
      StringConverter * type = new StringConverter;
      type->autosetup(training_column);
      dataconverters().push_back(type);

      StringSet * data = new StringSet;
      datasets().push_back(data);
    }
  }
}

void AsciiImport::autosetup_datasets() {
}

void 
AsciiImport::delete_dataconverters(DataConverters& dc)
{
  DataConverters::iterator i = dc.begin();
  while (i != dc.end())
    {
      delete *i;
      ++i;
    }
}
