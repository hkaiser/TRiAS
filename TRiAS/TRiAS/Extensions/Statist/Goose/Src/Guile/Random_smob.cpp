// This is -*- C++ -*-
// $Id: Random_smob.cpp,v 1.2 1999/05/16 00:14:19 trow Exp $

/* 
 * Random_smob.cpp
 *
 * Copyright (C) 1999 EMC Capital Management
 *
 * Developed by Jon Trowbridge & Havoc Pennington
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


#include <Random.h>
#include "guilegoose.h"
#include "snarf.h"

static long random_tag_type;
#define SCM_TO_RANDOM(obj) (reinterpret_cast<Random*>(SCM_CDR(obj)))
#define RANDOM_P(obj) (SCM_NIMP(obj) && SCM_CAR(obj) == random_tag_type)

bool
scm_randomp(SCM obj)
{
  return RANDOM_P(obj);
}

Random*
scm2random(SCM obj)
{
  if (!RANDOM_P(obj)) return 0;
  return SCM_TO_RANDOM(obj);
}

SCM
random2scm(Random* rnd)
{
  SCM_DEFER_INTS;
  SCM smob;
  SCM_NEWCELL (smob);
  SCM_SETCDR (smob, rnd);
  SCM_SETCAR (smob, random_tag_type);
  SCM_ALLOW_INTS;
  return smob;
}

//////////////////////////////////////////////////////////////////////////////

static SCM
mark_random(SCM)
{
  return SCM_BOOL_F;
}

static scm_sizet
free_random(SCM obj)
{
  Random* rnd = SCM_TO_RANDOM(obj);
  SCM_DEFER_INTS;
  delete rnd;
  SCM_ALLOW_INTS;
  return 0;
}

static int
print_random(SCM, SCM port, scm_print_state*)
{
  scm_puts("<Random>", port);
  return 1;
}

static scm_smobfuns random_funcs = {
  mark_random, free_random, print_random, 0 };

//////////////////////////////////////////////////////////////////////////////

GOOSE_PROC(random_p, "random?",
	   1,0,0, (SCM x))
{
  return gh_bool2scm(RANDOM_P(x));
}

GOOSE_PROC(make_random, "make-random",
	   0,0,0, ())
{
  return random2scm(new Random);
}

GOOSE_PROC(seed_random, "seed-random!",
	   2,0,0, (SCM scm_rnd, SCM scm_seed))
{
  SCM_ASSERT(RANDOM_P(scm_rnd), scm_rnd, SCM_ARG1, str_seed_random);
  SCM_ASSERT(gh_exact_p(scm_seed), scm_seed, SCM_ARG2, str_seed_random);

  Random* rnd = SCM_TO_RANDOM(scm_rnd);
  int seed = gh_scm2int(scm_seed);
  rnd->seed((unsigned)seed);

  return scm_rnd;
}

GOOSE_PROC(random_int, "%random-integer!",
	   3,0,0, (SCM scm_rnd, SCM scm_a, SCM scm_b))
{
  SCM_ASSERT(RANDOM_P(scm_rnd), scm_rnd, SCM_ARG1, str_random_int);
  SCM_ASSERT(gh_exact_p(scm_a), scm_a, SCM_ARG2, str_random_int);
  SCM_ASSERT(gh_exact_p(scm_b), scm_b, SCM_ARG3, str_random_int);

  Random* rnd = SCM_TO_RANDOM(scm_rnd);
  int a = gh_scm2int(scm_a);
  int b = gh_scm2int(scm_b);
  int x = rnd->random_integer(a,b);
  return gh_int2scm(x);
}

GOOSE_PROC(random_uniform, "%random-uniform!",
	   3,0,0, (SCM scm_rnd, SCM scm_a, SCM scm_b))
{
  SCM_ASSERT(RANDOM_P(scm_rnd), scm_rnd, SCM_ARG1, str_random_uniform);
  SCM_ASSERT(gh_number_p(scm_a), scm_a, SCM_ARG2, str_random_uniform);
  SCM_ASSERT(gh_number_p(scm_b), scm_b, SCM_ARG3, str_random_uniform);

  Random* rnd = SCM_TO_RANDOM(scm_rnd);
  double a = gh_scm2double(scm_a);
  double b = gh_scm2double(scm_b);
  double x = rnd->random_uniform(a,b);
  return gh_double2scm(x);
}

GOOSE_PROC(random_normal, "%random-normal!",
	   3,0,0, (SCM scm_rnd, SCM scm_m, SCM scm_sd))
{
  SCM_ASSERT(RANDOM_P(scm_rnd), scm_rnd, SCM_ARG1, str_random_normal);
  SCM_ASSERT(gh_number_p(scm_m), scm_m, SCM_ARG2, str_random_normal);
  SCM_ASSERT(gh_number_p(scm_sd), scm_sd, SCM_ARG3, str_random_normal);

  Random* rnd = SCM_TO_RANDOM(scm_rnd);
  double m = gh_scm2double(scm_m);
  double sd = gh_scm2double(scm_sd);
  SCM_ASSERT(sd>0, scm_sd, SCM_OUTOFRANGE, str_random_normal);
  double x = rnd->random_normal(m, sd);
  return gh_double2scm(x);
}

GOOSE_PROC(random_bool, "%random-boolean!",
	   2,0,0, (SCM scm_rnd, SCM scm_p))
{
  SCM_ASSERT(RANDOM_P(scm_rnd), scm_rnd, SCM_ARG1, str_random_bool);
  SCM_ASSERT(gh_number_p(scm_p), scm_p, SCM_ARG2, str_random_bool);

  Random* rnd = SCM_TO_RANDOM(scm_rnd);
  double p = gh_scm2double(scm_p);
  SCM_ASSERT(0 <= p && p <= 1, scm_p, SCM_OUTOFRANGE, str_random_bool);
  bool x = rnd->random_bool(p);
  return gh_bool2scm(x);
}

void
scm_init_random()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  random_tag_type = scm_newsmob(&random_funcs);

#include "Random_smob.x"

}



// $Id: Random_smob.cpp,v 1.2 1999/05/16 00:14:19 trow Exp $
