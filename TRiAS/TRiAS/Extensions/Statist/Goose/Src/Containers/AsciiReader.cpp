// This is -*- C++ -*-
// $Id: AsciiReader.cpp,v 1.2 1999/07/20 08:34:26 alstrup Exp $

/* 
 * AsciiReader.cpp
 *
 * Copyright (C) 1998,1999 Asger Alstrup Nielsen
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
#include "AsciiReader.h"

void
StreamAsciiReader::restart(bool caching_)
{
  warningctrl_->reset();
  linenumber_ = 0;
  control_chars = 0;
  caching = caching_;
  cache = linecache.begin();
  // We don't erase the "preread" string, because that is not broken yet
}

void
StreamAsciiReader::warn(const string& msg)
{
  if (caching)
    return;
  warningctrl_->warn(string("Line ") + string_tool.int2str(linenumber_) +
		     string(": ") + msg);
}

string
StreamAsciiReader::readline()
{
  string line;
  // Do we have the line in the line-cache?
  bool got_from_cache = false;
  if (cache != linecache.end()) {
    line = *cache;
    ++cache;
    got_from_cache = true;
  } else {
    // No, get it from the stream.
    
    // This is the first line, so let's guess what the eol character is
    // by using the first encounter of "\r" or "\n" as eol character.
    // We do this to avoid that the "getline" below will eat the entire file
    // when the eol-character is the wrong one.
    if (primaryeol.empty()) {
      int count = 0;
      char linebuf[81];
      bool found = false;
      while (count < 100 && !found) {
	if (eof())
	  return string();
	
	for (int f=0; f<81; ++f) {
	  linebuf[f] = '\0';
	}
	read((char *) linebuf, 80); // note: 80. leave null termination.
	
	line = linebuf;
	found = int(line.find_first_of("\r\n")) != -1;
	preread += line;
	// redundant: line.erase(line.begin(), line.end());
	++count;
      } 
      if (count == 100) {
	throw Exception("No end of line found within the first 8000 characters. "
			"This is probably a binary file.");
      }
      primaryeol = line[line.find_first_of("\r\n")];
      if (!eof()) {
	// The preread has to end a line
	getline(line, primaryeol[0]);
	preread += line;
	// redundant: line.erase(line.begin(), line.end());
      }
    }
    if (preread.empty()) {
      if (eof()) 
	return string();
      getline(preread, primaryeol[0]);
    }
    // Handle DOS style line endings better (i.e. line-numbers)
    if (primaryeol[0] == '\r' && preread[0] == '\n') {
      preread.erase(preread.begin());
    }
    line = preread;
    // Maybe we have other kinds of line-breaks in here as well
    int pos = line.find_first_of("\r\n");
    if (pos != -1) {
      line.erase(pos, line.length() - pos);
      preread.erase(0, pos+1);
    } else {
      preread.erase(preread.begin(), preread.end());
    }
  }
  
  // At this point, we have the line
  linenumber_++;
  if (caching && !got_from_cache) {
    linecache.push_back(line);
    cache = linecache.end();
  }
  // Handle comments
  if (!comment().empty() && int(line.find(comment())) != -1) {
    line.erase(line.find(comment()), line.length() - line.find(comment()));
  }
  
  // Filter out control characters
  while (true) {
    int pos = line.find_first_of("\x01\x02\x03\x04\x05\x06\x07"
				 "\x08\x0b\x0c\x0e\x0f"
				 "\x10\x11\x12\x13\x14\x15\x16\x17"
				 "\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f");
    if (pos == -1)
      break;
    line.erase(pos, 1);
    ++control_chars;
    if (control_chars == 50) {
      warn("This looks like a binary file.  50 control characters met.");
    }
  }
  
  if (string_tool.cut(line).empty()) {
    return readline();
  }
  return line;
}


// $Id: AsciiReader.cpp,v 1.2 1999/07/20 08:34:26 alstrup Exp $
