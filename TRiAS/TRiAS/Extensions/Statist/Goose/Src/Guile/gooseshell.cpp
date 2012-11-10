// This is -*- C++ -*-
// $Id: gooseshell.cpp,v 1.2 1999/03/16 18:28:25 alstrup Exp $

/* 
 * gooseshell.cpp
 *
 * Copyright (C) 1998 EMC Capital Management
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

#include "guilegoose.h"

static void
real_main(void* closure, int argc, char* argv[])
{
  scm_init_goose();

  gh_eval_str("(set-repl-prompt! \"goose> \")");

  scm_shell(argc, argv);
}

int
main(int argc, char* argv[])
{
  scm_boot_guile(argc, argv, real_main, 0);
  return 0; // never reached
}





