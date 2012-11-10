// This is -*- C++ -*-
// $Id: WarningController.h,v 1.3 1999/03/30 00:44:08 hp Exp $

/* 
 * WarningController.h
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

#ifndef _INC_WARNINGCONTROLLER_H
#define _INC_WARNINGCONTROLLER_H

#include <string>
#include <iostream>
#include "Exception.h"

using namespace std;

/*
 * Abstract base class for warning controller.
 */
class WarningController {
public:
  WarningController(int warn = -1, int see_warns = -1)
    : warns(0), warnings_(warn), see_warnings_(see_warns)
  { }

  virtual ~WarningController() { }

  virtual void reset() {
    warns = 0;
  }

  // Present a warning
  virtual void warn(string const & message) = 0;

  // How many warnings do we tolerate?
  int warnings() const { return warnings_; }
  void set_warnings(int w) { warnings_ = w; }

  // How many warnings do we present?
  int see_warnings() const { return see_warnings_; }
  void set_see_warnings(int sw) { see_warnings_ = sw; }

  // Go to sleep -- ignore all warnings
  void sleep() { 
    last_see_warnings_ = see_warnings_;
    see_warnings_ = 0;
  }

  // Wake up -- take care of warnings again
  void wake_up() { see_warnings_ = last_see_warnings_; }
protected:
  // Number of warnings/errors issued so far
  int warns;

private:
  // Number of warnings to tolerate
  // If this is -1, we tolerate all warnings
  int warnings_;

  // Number of warnings to present to the user
  // If this is -1, we show all warnings
  int see_warnings_;

  // Temporary holder while sleeping
  int last_see_warnings_;
};

/*
 * Warnings reporting class.
 * This class handles the reporting of warnings.
 */
template<class _GUI>
class GUIWarningController : public WarningController {
public:
  GUIWarningController(_GUI & g, int warns = -1, int see_warns = -1)
    : WarningController(warns, see_warns), gui_(&g)
  { 
    reset();
  }

  // Present a warning to the user
  void warn(string const & message) {
    ++warns;

    if (see_warnings() == -1 || warns <= see_warnings()) {
     gui() << message << "\n";
      if (warns == see_warnings() && (warnings() > see_warnings() || warnings() == -1)) {
	gui() << "From now on, warnings are ignored.\n";
      }
    }

    if (warns > warnings() && warnings() != -1) {
      throw Exception("Too many warnings.");
    }
  }
private:
  _GUI & gui() { return *gui_; }

  // This is what we communicate with
  _GUI * gui_;
};

typedef GUIWarningController<ostream> StreamWarnings;

#include <vector>

// Pile all the warnings into a list.
class StackWarningController : public WarningController {
public:
  StackWarningController() {
    reset();
  }

  virtual void warn(string const & message) {
    ++warns;

    if (see_warnings() == -1 || warns <= see_warnings()) {
      warning_stack_.push_back(message);
      if (warns == see_warnings() && (warnings() > see_warnings() || warnings() == -1)) {
        warning_stack_.push_back("Additional warnings ignored.");
      }
    }

    // we just don't honor the "warnings limit" for now.
  }

  const vector<string>& get_warnings() { return warning_stack_; }

private:
  vector<string> warning_stack_;
};

#endif
