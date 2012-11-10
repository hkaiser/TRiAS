// This is -*- C++ -*-
// $Id: bootstrap_wrap.cpp,v 1.2 1999/05/17 23:52:13 hp Exp $

/* 
 * bootstrap_wrap.cpp
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

#include <bootstrap.h>
#include "guilegoose.h"
#include "snarf.h"

static int thread_default = 1;
/*
  This is here to protect you from doing something stupid by mistake.
  (If you have more than 128 CPUs, you'll need to bump this up and
  recompile.)
*/
const int max_threads_allowed = 128;

GOOSE_PROC(resamp_thread_def, "resample-thread-default",
	   0,0,0, ())
{
  return gh_int2scm(thread_default);
}

GOOSE_PROC(resamp_thread_def_bang, "resample-thread-default!",
	   1,0,0, (SCM scm_th))
{
  SCM_ASSERT(gh_exact_p(scm_th), scm_th, SCM_ARG1, str_resamp_thread_def_bang);
  int th = gh_scm2int(scm_th);
  SCM_ASSERT(th > 0 && th <= max_threads_allowed,
	     scm_th, SCM_OUTOFRANGE, str_resamp_thread_def_bang);
  thread_default = th;

  return SCM_UNSPECIFIED;
}

GOOSE_PROC(resamp_mean, "resample-mean",
	   2,1,0, (SCM scm_rs, SCM scm_N, SCM scm_th))
{
  SCM_ASSERT(scm_realsetp(scm_rs), scm_rs, SCM_ARG1, str_resamp_mean);
  SCM_ASSERT(gh_exact_p(scm_N), scm_N, SCM_ARG2, str_resamp_mean);

  // Extract the number of iterations.
  int N = gh_scm2int(scm_N);
  SCM_ASSERT(N>0, scm_N, SCM_OUTOFRANGE, str_resamp_mean);

  // Extract the number of threads, if different from the default.
  int th = thread_default;
  if (!SCM_UNBNDP(scm_th)) {
    SCM_ASSERT(gh_exact_p(scm_th), scm_th, SCM_ARG3, str_resamp_mean);
    th = gh_scm2int(scm_th);
    SCM_ASSERT(th > 0 && th <= max_threads_allowed,
	       scm_th, SCM_OUTOFRANGE, str_resamp_mean);
  }

  RealSet* out = new RealSet;

  *out = resample_mean((size_t)N, *scm2realset(scm_rs), th);

  return realset2scm(out);
}

GOOSE_PROC(resamp_med, "resample-med",
	   2,1,0, (SCM scm_rs, SCM scm_N, SCM scm_th))
{
  SCM_ASSERT(scm_realsetp(scm_rs), scm_rs, SCM_ARG1, str_resamp_med);
  SCM_ASSERT(gh_exact_p(scm_N), scm_N, SCM_ARG2, str_resamp_med);

  // Extract the number of iterations.
  int N = gh_scm2int(scm_N);
  SCM_ASSERT(N>0, scm_N, SCM_OUTOFRANGE, str_resamp_med);

  // Extract the number of threads, if different from the default.
  int th = thread_default;
  if (!SCM_UNBNDP(scm_th)) {
    SCM_ASSERT(gh_exact_p(scm_th), scm_th, SCM_ARG3, str_resamp_med);
    th = gh_scm2int(scm_th);
    SCM_ASSERT(th > 0 && th <= max_threads_allowed,
	       scm_th, SCM_OUTOFRANGE, str_resamp_med);
  }

  RealSet* out = new RealSet;

  *out = resample_median((size_t)N, *scm2realset(scm_rs), th);

  return realset2scm(out);
}

GOOSE_PROC(resamp_sdev, "resample-sdev",
	   2,1,0, (SCM scm_rs, SCM scm_N, SCM scm_th))
{
  SCM_ASSERT(scm_realsetp(scm_rs), scm_rs, SCM_ARG1, str_resamp_sdev);
  SCM_ASSERT(gh_exact_p(scm_N), scm_N, SCM_ARG2, str_resamp_sdev);

  // Extract the number of iterations.
  int N = gh_scm2int(scm_N);
  SCM_ASSERT(N>0, scm_N, SCM_OUTOFRANGE, str_resamp_sdev);

  // Extract the number of threads, if different from the default.
  int th = thread_default;
  if (!SCM_UNBNDP(scm_th)) {
    SCM_ASSERT(gh_exact_p(scm_th), scm_th, SCM_ARG3, str_resamp_sdev);
    th = gh_scm2int(scm_th);
    SCM_ASSERT(th > 0 && th <= max_threads_allowed,
	       scm_th, SCM_OUTOFRANGE, str_resamp_sdev);
  }

  RealSet* out = new RealSet;

  *out = resample_sdev((size_t)N, *scm2realset(scm_rs), th);

  return realset2scm(out);
}

void
scm_init_bootstrap()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

#include "bootstrap_wrap.x"
}



// $Id: bootstrap_wrap.cpp,v 1.2 1999/05/17 23:52:13 hp Exp $
