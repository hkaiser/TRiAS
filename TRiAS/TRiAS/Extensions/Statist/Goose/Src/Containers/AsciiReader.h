// This is -*- C++ -*-
// $Id: AsciiReader.h,v 1.5 1999/05/05 21:00:31 trow Exp $

/* 
 * AsciiReader.h
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

#ifndef _INC_ASCIIREADER_H
#define _INC_ASCIIREADER_H

#include <string>
#include <vector>
#include <algorithm>
#include "stringtools.h"
#include "WarningController.h"
#include <stdio.h>

using namespace std;

/*
 * Abstract base class for an ascii reader
 * This class abstracts the reading from an ascii source.
 * Any source should be able to reset it self to restart
 * from the beginning.
 */
class AsciiReader {
public:
  AsciiReader() { }
  virtual ~AsciiReader() { }
  virtual void restart(bool probingread = false) = 0;
  virtual string readline() = 0;
  virtual string comment() const { return comment_; }
  virtual void set_comment(string const & s) { comment_ = s; }
private:
  string comment_;
};


/*
 * Base class to abstract FILE* - fstream distinction
 */
class StreamAsciiReader : public AsciiReader {
public:
  StreamAsciiReader(WarningController & wc)
    : AsciiReader(), warningctrl_(&wc), primaryeol(string())
  { 
    restart(false);
  }

  void restart(bool caching_ = false);

  void warn(const string& msg);

  // Get next non-empty line, from cache if existant, or from the stream
  // We return an empty string when the end of the file is reached.
  string readline();

protected:
  virtual bool eof() = 0;
  virtual void read(char* buf, size_t size) = 0;
  virtual void getline(string & line, char term) = 0;

  WarningController * warningctrl_;

  // Number of ignored control-characters so far
  int control_chars;

  // The cache of read data is kept here. This way, we can support previews.
  typedef vector<string> LineCache;
  LineCache linecache;
  LineCache::iterator cache;
  bool caching;

  // How far are we in the file so far?
  size_t linenumber_;

  // A buffer of stuff that has been read from the stream, but not
  // broken into lines yet.  There is an implicit line-break at the
  // end of this string.
  string preread;

  // The eol-character from the first line in the file
  string primaryeol;
};


// An ascii reader for FILE*; fstream is kind of hosed on 
//  GNU platforms.
class FILEAsciiReader : public StreamAsciiReader {
public:
  FILEAsciiReader(FILE* f, WarningController& wc) 
    : StreamAsciiReader(wc), f_(f)
    {}
  
protected:  
  FILE* f_; 

  virtual bool eof() { return feof(f_); }
  virtual void read(char* buf, size_t size) {
    fread(buf, sizeof(char), size, f_);
    // Um, should check for errors.
  }
  // Not so efficient... hrm.
  virtual void getline(string & line, char term) {
    char next = '\0';
    while ((next = fgetc(f_)) != EOF)
      {
        if (next == term)
          {
            break;
          }
        line += next;
      }
  }
};

/*
 * Parameterized ascii file reader with caching, uses streams
 */
template<class _IStream>
class CachingAsciiReader : public StreamAsciiReader {
public:
  CachingAsciiReader(_IStream & s, WarningController & wc)
    : StreamAsciiReader(wc), input_stream_(&s)
  { 
  }

protected:
  virtual bool eof() { return input_stream_->eof(); }
  virtual void read(char* buf, size_t size) {
    input_stream_->read(buf, size);
  }

  virtual void getline(string & line, char term) {
      std::getline(*input_stream_, line, term);
  }

private:
  _IStream* input_stream_;

  
};


#endif
