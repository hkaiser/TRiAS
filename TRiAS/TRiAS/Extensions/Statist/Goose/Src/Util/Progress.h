// This is -*- C++ -*-
// $Id: Progress.h,v 1.2 1999/04/07 20:38:58 hp Exp $

/* 
 * Progress.h
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
 *
 * Developed by Havoc Pennington <hp@pobox.com>
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

#ifndef _INC_PROGRESS_H
#define _INC_PROGRESS_H

// Abstract interface to a progress meter.
class GooseProgress {
public:
  virtual void start() = 0; // Fire up the progress meter
  virtual void stop() = 0;  // shut it down

  // If we set percent, we know at this time how much is remaining.
  // If we pulse, we don't.
  virtual void set_percent(double percent) = 0; // [0.0,1.0]
  virtual void pulse() = 0;
  
  // The algorithm displaying progress should check this to see if the
  // user has cancelled, and abort if so and if possible.
  virtual bool cancelled() = 0;

  // Set the name of the operation being performed.
  virtual void set_operation(const string& opname) = 0;

};

#endif // _INC_PROGRESS_H

// $Id: Progress.h,v 1.2 1999/04/07 20:38:58 hp Exp $
