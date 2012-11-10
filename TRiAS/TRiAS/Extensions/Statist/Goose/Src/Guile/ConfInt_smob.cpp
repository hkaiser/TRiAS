// This is -*- C++ -*-
// $Id: ConfInt_smob.cpp,v 1.3 1999/04/15 19:48:39 trow Exp $

/* 
 * ConfInt_smob.cpp
 *
 * Copyright (C) 1999 EMC Capital Management
 *
 * Developed by Jon Trowbridge
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

#include <stdlib.h>
#include <ConfInt.h>
#include "guilegoose.h"

static long confint_type_tag;

#define SCM_TO_CONFINT(obj) (reinterpret_cast<ConfInt*>(SCM_CDR(obj)))
#define CONFINT_P(obj) (SCM_NIMP(obj) && SCM_CAR(obj) == confint_type_tag)

bool
scm_CONFINT_P(SCM obj)
{
  return CONFINT_P(obj);
}

ConfInt*
scm2confint(SCM obj)
{
  if (!CONFINT_P(obj)) return 0;
  return SCM_TO_CONFINT(obj);
}

SCM
confint2scm(const ConfInt& ci)
{
  SCM_DEFER_INTS;
  SCM smob;
  SCM_NEWCELL (smob);
  SCM_SETCDR (smob, new ConfInt(ci));
  SCM_SETCAR (smob, confint_type_tag);
  scm_done_malloc(sizeof(ConfInt));
  SCM_ALLOW_INTS;
  return smob;
}

static SCM
mark_confint(SCM)
{
  return SCM_BOOL_F;
}

static scm_sizet
free_confint(SCM obj)
{
  ConfInt* ci = SCM_TO_CONFINT(obj);
  scm_sizet size = sizeof(*ci);
  SCM_DEFER_INTS;
  delete ci;
  SCM_ALLOW_INTS;
  return size;
}

static int
print_confint(SCM obj, SCM port, scm_print_state* pstate)
{
  ConfInt* ci = SCM_TO_CONFINT(obj);
  char buffer[128];
  if (ci->initialized())
    sprintf(buffer, "[ %f : %f : %f ]", ci->low(), ci->est(), ci->high());
  else
    sprintf(buffer,"[ * : * : * ]");
  scm_puts(buffer, port); // This sucks, but works for now
  return 1;
}

static scm_smobfuns confint_funcs = {
  mark_confint, free_confint, print_confint, 0
};

/////////////////////////////////////////////////////////////////////////////

static SCM
confintp(SCM x)
{
  return gh_bool2scm(CONFINT_P(x));
}

static SCM
confint_low(SCM x)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-low");
  ConfInt* ci = scm2confint(x);
  return gh_double2scm(ci->low());
}

static SCM
confint_high(SCM x)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-high");
  ConfInt* ci = scm2confint(x);
  return gh_double2scm(ci->high());
}

static SCM
confint_estimate(SCM x)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-estimate");
  ConfInt* ci = scm2confint(x);
  return gh_double2scm(ci->est());
}

static SCM
confint_confidence(SCM x)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-confidence");
  ConfInt* ci = scm2confint(x);
  return gh_double2scm(ci->confidence());
}

static SCM
confint_width(SCM x)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-width");
  ConfInt* ci = scm2confint(x);
  return gh_double2scm(ci->width());
}

static SCM
confint_symmetric_p(SCM x)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-symmetric?");
  ConfInt* ci = scm2confint(x);
  return gh_bool2scm(ci->symmetric());
}

static SCM
confint_contains_p(SCM x, SCM p)
{
  SCM_ASSERT(CONFINT_P(x), x, SCM_ARG1, "confint-contains?");
  SCM_ASSERT(gh_number_p(p), p, SCM_ARG2, "confint-contains?");
  ConfInt* ci = scm2confint(x);
  double v = gh_scm2double(p);
  return gh_bool2scm(ci->contains(v));
}


/////////////////////////////////////////////////////////////////////////////

#define RECAST(x) reinterpret_cast<long int(*)()>(x)

void
scm_init_confint()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  confint_type_tag = scm_newsmob(&confint_funcs);

  scm_make_gsubr("confint?", 1, 0, 0, RECAST(confintp));

  scm_make_gsubr("confint-low", 1, 0, 0, RECAST(confint_low));
  scm_make_gsubr("confint-high", 1, 0, 0, RECAST(confint_high));
  scm_make_gsubr("confint-estimate", 1, 0, 0, RECAST(confint_estimate));
  scm_make_gsubr("confint-confidence", 1, 0, 0, RECAST(confint_confidence));
  scm_make_gsubr("confint-width", 1, 0, 0, RECAST(confint_width));

  scm_make_gsubr("confint-symmetric?", 1, 0, 0,
		 RECAST(confint_symmetric_p));
  scm_make_gsubr("confint-contains?", 2, 0, 0, RECAST(confint_contains_p));

}





// $Id: ConfInt_smob.cpp,v 1.3 1999/04/15 19:48:39 trow Exp $
