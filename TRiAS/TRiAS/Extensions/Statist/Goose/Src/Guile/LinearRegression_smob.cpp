// This is -*- C++ -*-
// $Id: LinearRegression_smob.cpp,v 1.4 1999/04/15 19:49:39 trow Exp $

/* 
 * LinearRegression_smob.cpp
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

#include <stdlib.h>
#include <LinearRegression.h>
#include "guilegoose.h"
#include "snarf.h"

static long linreg_type_tag;

#define SCM_TO_LINREG(obj) (reinterpret_cast<LinearRegression*>(SCM_CDR(obj)))
#define LINREG_P(value)    (SCM_NIMP (value) && SCM_CAR(value) == linreg_type_tag)

bool     
scm_linregp (SCM obj)
{
  return LINREG_P(obj);
}

LinearRegression* 
scm2linreg (SCM obj)
{
  if (!LINREG_P(obj)) return 0;
  return SCM_TO_LINREG(obj);
}

SCM      
linreg2scm (LinearRegression* lr)
{
  SCM_DEFER_INTS;
  SCM smob;
  SCM_NEWCELL (smob);
  SCM_SETCDR (smob, lr);
  SCM_SETCAR (smob, linreg_type_tag);
  SCM_ALLOW_INTS;
  return smob;
}

// This function should mark any SCM objects we reference,
//  at this time none. The return value is automatically marked 
//  by Guile, this is some kind of optimization; so we can
//  return one of the objects.
static SCM
mark_linreg (SCM obj)
{
  //  scm_gc_mark (image->name);
  //  return image->update_func;
  return SCM_BOOL_F; // not important
}

static scm_sizet
free_linreg (SCM obj)
{
  LinearRegression* lr = SCM_TO_LINREG(obj);

  // we return the number of bytes freed, for statistics;
  //  hopefully it doesn't have to be exact...
  scm_sizet size = sizeof (*lr);

  SCM_DEFER_INTS;

  // Here we do whatever we do when there are no more scheme objects
  // which refer to this timeseries.
  delete lr;

  SCM_ALLOW_INTS;

  return size;
}

static int
print_linreg (SCM obj, SCM port, scm_print_state *pstate)
{
  LinearRegression* rs = SCM_TO_LINREG(obj);

  char buffer[128];
  sprintf(buffer, "<linear-regression: y = %f x + %f, r = %f>",
	  rs->slope(), rs->intercept(), rs->correlation());
  scm_puts(buffer, port);

  /* non-zero means success */
  return 1;
}

static scm_smobfuns linreg_funcs = {
  mark_linreg, 
  free_linreg, 
  print_linreg, 
  0 // means we can never be equal? 
};

//////////////////////////////////////////////////////////////////////////////

GOOSE_PROC(linreg_p, "linear-regression?",
	   1,0,0, (SCM x))
{
  return gh_bool2scm(LINREG_P(x));
}

GOOSE_PROC(do_linreg, "linear-regression",
	   2,0,0, (SCM scm_x, SCM scm_y))
{
  SCM_ASSERT(scm_realsetp(scm_x), scm_x, SCM_ARG1, str_do_linreg);
  SCM_ASSERT(scm_realsetp(scm_y), scm_y, SCM_ARG2, str_do_linreg);

  RealSet* x = scm2realset(scm_x);
  RealSet* y = scm2realset(scm_y);



  LinearRegression* lr = new LinearRegression(*x, *y);

  SCM_DEFER_INTS;
  scm_done_malloc(sizeof(LinearRegression));
  SCM_ALLOW_INTS;

  return linreg2scm(lr);
}

GOOSE_PROC(linreg_slope, "linear-regression-slope",
	   1,0,0, (SCM scm_lr))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_slope);

  LinearRegression* lr = SCM_TO_LINREG(scm_lr);

  return gh_double2scm(lr->slope());
}

GOOSE_PROC(linreg_int, "linear-regression-intercept",
	   1,0,0, (SCM scm_lr))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_int);

  LinearRegression* lr = SCM_TO_LINREG(scm_lr);

  return gh_double2scm(lr->intercept());
}

GOOSE_PROC(linreg_corr, "linear-regression-correlation",
	   1, 0, 0, (SCM scm_lr))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_corr);

  LinearRegression* lr = SCM_TO_LINREG(scm_lr);

  return gh_double2scm(lr->correlation());
}

GOOSE_PROC(linreg_predict, "linear-regression-predict",
	   2,0,0,(SCM scm_lr, SCM scm_x))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_predict);
  SCM_ASSERT(gh_number_p(scm_x), scm_x, SCM_ARG2, str_linreg_predict);

  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  double x = gh_scm2double(scm_x);
  return gh_double2scm(lr->predict(x));
}

GOOSE_PROC(linreg_slope_ci, "linear-regression-slope-interval",
	   2,0,0, (SCM scm_lr, SCM scm_conf))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_slope_ci);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG2, str_linreg_slope_ci);
  
  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  double c = gh_scm2double(scm_conf);
  return confint2scm(lr->slope_interval(c));
}

GOOSE_PROC(linreg_int_ci, "linear-regression-intercept-interval",
	   2,0,0, (SCM scm_lr, SCM scm_conf))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_int_ci);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG2, str_linreg_int_ci);
  
  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  double c = gh_scm2double(scm_conf);
  return confint2scm(lr->intercept_interval(c));
}

GOOSE_PROC(linreg_corr_ci, "linear-regression-correlation-interval",
	   2,0,0, (SCM scm_lr, SCM scm_conf))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_corr_ci);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG2, str_linreg_corr_ci);
  
  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  double c = gh_scm2double(scm_conf);
  return confint2scm(lr->correlation_interval(c));
}

GOOSE_PROC(linreg_pred_ci, "linear-regression-predict-interval",
	   3,0,0, (SCM scm_lr, SCM scm_x, SCM scm_conf))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_pred_ci);
  SCM_ASSERT(gh_number_p(scm_x), scm_x, SCM_ARG2, str_linreg_pred_ci);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG3, str_linreg_pred_ci);
  
  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  double x = gh_scm2double(scm_x);
  double c = gh_scm2double(scm_conf);
  return confint2scm(lr->prediction_interval(x,c));
}

GOOSE_PROC(linreg_ind_t, "linear-regression-t",
	   1,0,0, (SCM scm_lr))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_ind_t);
  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  return gh_double2scm(lr->independence_t());
}

GOOSE_PROC(linreg_ind_p, "linear-regression-p",
	   1,0,0, (SCM scm_lr))
{
  SCM_ASSERT(LINREG_P(scm_lr), scm_lr, SCM_ARG1, str_linreg_ind_p);
  LinearRegression* lr = SCM_TO_LINREG(scm_lr);
  return gh_double2scm(lr->independence_p());
}

//////////////////////////////////////////////////////////////////////////////


void
scm_init_linreg()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  linreg_type_tag = scm_newsmob(&linreg_funcs);

#include "LinearRegression_smob.x"

}





// $Id: LinearRegression_smob.cpp,v 1.4 1999/04/15 19:49:39 trow Exp $
