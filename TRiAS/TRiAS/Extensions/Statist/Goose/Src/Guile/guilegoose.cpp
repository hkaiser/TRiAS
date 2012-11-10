// This is -*- C++ -*-
// $Id: guilegoose.cpp,v 1.8 1999/05/26 20:36:26 trow Exp $

/* 
 * guilegoose.cpp
 *
 * Copyright (C) 1998, 1999 EMC Capital Management
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

#include <string.h>
#include "guilegoose.h"

extern void scm_init_confint();
extern void scm_init_random();
extern void scm_init_realset();
extern void scm_init_linreg();
extern void scm_init_specfns();
extern void scm_init_asciiimport();
extern void scm_init_bootstrap();
extern void scm_init_pest();

void 
scm_init_goose()
{
  char bufA[128];
  strncpy(bufA, PREFIX, 127);
  char bufB[256];
  sprintf(bufB,"(define %%goose-prefix \"%s\")",bufA);
  gh_eval_str(bufB);

  scm_init_specfns();
  scm_init_confint();
  scm_init_random();
  scm_init_realset();
  scm_init_linreg();
  scm_init_asciiimport();
  scm_init_bootstrap();
  scm_init_pest();

  gh_eval_str("(load (string-append %goose-prefix \"/share/guile/goose/gooseboot.scm\"))");
}

void 
goose_scm_tagged_error(const char* tag, const char *subr, const char *msg)
{
  scm_error(gh_symbol2scm(const_cast<char*>(tag)), const_cast<char*>(subr), 
            "%s",
	    gh_list(gh_str02scm(const_cast<char*>(msg)), SCM_UNDEFINED),
	    gh_list(gh_str02scm(const_cast<char*>(msg)), SCM_UNDEFINED));
}

void 
goose_scm_error(const char *subr, const char *msg)
{
  goose_scm_tagged_error("goose-error", subr, msg);
}


