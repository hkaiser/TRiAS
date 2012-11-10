// This is -*- C++ -*-
// $Id: goose.cpp,v 1.2 1999/03/16 18:29:32 alstrup Exp $

/* 
 * goose.cpp
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
 *
 * Developed by Havoc Pennington <hp@emccta.com>.
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

#include <stdio.h>
#include <config.h>

// This file is used to check the Goose version in goose.m4

static const int goose_major_version = GOOSE_MAJOR_VERSION;
static const int goose_minor_version = GOOSE_MINOR_VERSION;
static const int goose_micro_version = GOOSE_MICRO_VERSION;

// Returns an new-allocated error if there's a mismatch.
// This function isn't in a header, it's private in effect.
char*  
check_goose_version(int major, int minor, int micro)
{
  if ((goose_major_version > major) ||
      ((goose_major_version == major) && (goose_minor_version > minor)) ||
      ((goose_major_version == major) && (goose_minor_version == minor) && (goose_micro_version >= micro)))
    {
      return 0;
    }
  else 
    {
      char* buf = new char[1024];
      sprintf(buf, "Wanted Goose version %d.%d.%d or compatible, %d.%d.%d will not work.", major, minor, micro, goose_major_version, goose_minor_version, goose_micro_version);
      return buf;
    }
}


// $Id: goose.cpp,v 1.2 1999/03/16 18:29:32 alstrup Exp $

