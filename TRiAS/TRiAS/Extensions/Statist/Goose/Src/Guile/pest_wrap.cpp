// This is -*- C++ -*-
// $Id: pest_wrap.cpp,v 1.1 1999/05/26 20:36:27 trow Exp $

/* 
 * pest_wrap.cpp
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

#include <parametric_estimation.h>
#include "guilegoose.h"
#include "snarf.h"

GOOSE_PROC(pest_normal_mean, "pest-normal-mean",
	   4,0,0, (SCM scm_m, SCM scm_sd, SCM scm_N, SCM scm_conf))
{
  SCM_ASSERT(gh_number_p(scm_m), scm_m, SCM_ARG1, str_pest_normal_mean);
  SCM_ASSERT(gh_number_p(scm_sd), scm_sd, SCM_ARG2, str_pest_normal_mean);
  SCM_ASSERT(gh_exact_p(scm_N), scm_N, SCM_ARG3, str_pest_normal_mean);

  ConfInt ci;

  try {
    ci = pest_normal_mean(gh_scm2double(scm_m),
			  gh_scm2double(scm_sd),
			  gh_scm2int(scm_N),
			  gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_normal_mean);

  return confint2scm(ci);
}

GOOSE_PROC(pest_d_mean_eq_sd,
	   "pest-normal-difference-of-means-equal-sdev",
	   6,0,0,
	   (SCM scm_m1, SCM scm_m2, SCM scm_sd,
	    SCM scm_N1, SCM scm_N2, SCM scm_conf))
{
  SCM_ASSERT(gh_number_p(scm_m1), scm_m1, SCM_ARG1, str_pest_d_mean_eq_sd);
  SCM_ASSERT(gh_number_p(scm_m2), scm_m2, SCM_ARG2, str_pest_d_mean_eq_sd);
  SCM_ASSERT(gh_number_p(scm_sd), scm_sd, SCM_ARG3, str_pest_d_mean_eq_sd);
  SCM_ASSERT(gh_exact_p(scm_N1), scm_N1, SCM_ARG4, str_pest_d_mean_eq_sd);
  SCM_ASSERT(gh_exact_p(scm_N2), scm_N2, SCM_ARG5, str_pest_d_mean_eq_sd);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG6, str_pest_d_mean_eq_sd);

  ConfInt ci;
  
  try {
    ci = pest_normal_difference_of_means_equal_sdev(gh_scm2double(scm_m1),
						    gh_scm2double(scm_m2),
						    gh_scm2double(scm_sd),
						    gh_scm2int(scm_N1),
						    gh_scm2int(scm_N2),
						    gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_d_mean_eq_sd);

  return confint2scm(ci);
}

GOOSE_PROC(pest_normal_var, "pest-normal-variance",
	   3,0,0, (SCM scm_v, SCM scm_N, SCM scm_conf))
{
  SCM_ASSERT(gh_number_p(scm_v), scm_v, SCM_ARG1, str_pest_normal_var);
  SCM_ASSERT(gh_exact_p(scm_N), scm_N, SCM_ARG2, str_pest_normal_var);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG3, str_pest_normal_var);

  ConfInt ci;
  
  try {
    ci = pest_normal_variance(gh_scm2double(scm_v),
			      gh_scm2int(scm_N),
			      gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_normal_var);

  return confint2scm(ci);
}

GOOSE_PROC(pest_normal_corr, "pest-normal-correlation",
	   3,0,0, (SCM scm_r, SCM scm_N, SCM scm_conf))
{
  SCM_ASSERT(gh_number_p(scm_r), scm_r, SCM_ARG1, str_pest_normal_corr);
  SCM_ASSERT(gh_exact_p(scm_N), scm_N, SCM_ARG2, str_pest_normal_corr);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG3, str_pest_normal_corr);

  ConfInt ci;

  try {
    ci = pest_normal_correlation(gh_scm2double(scm_r),
				 gh_scm2int(scm_N),
				 gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_normal_corr);

  return confint2scm(ci);
}

GOOSE_PROC(pest_bin_p_normal_approx, "pest-binomial-p-normal-approx",
	   3,0,0, (SCM scm_suc, SCM scm_try, SCM scm_conf))
{
  SCM_ASSERT(gh_exact_p(scm_suc), scm_suc, SCM_ARG1,
	     str_pest_bin_p_normal_approx);
  SCM_ASSERT(gh_exact_p(scm_try), scm_try, SCM_ARG2,
	     str_pest_bin_p_normal_approx);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG3,
	     str_pest_bin_p_normal_approx);

  ConfInt ci;
  
  try {
    ci = pest_binomial_p_normal_approx(gh_scm2int(scm_suc),
				       gh_scm2int(scm_try),
				       gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_bin_p_normal_approx);

  return confint2scm(ci);
}

GOOSE_PROC(pest_bin_p_normal_approx_alt, "pest-binomial-p-normal-approx-alt",
	   3,0,0, (SCM scm_suc, SCM scm_try, SCM scm_conf))
{
  SCM_ASSERT(gh_exact_p(scm_suc), scm_suc, SCM_ARG1,
	     str_pest_bin_p_normal_approx_alt);
  SCM_ASSERT(gh_exact_p(scm_try), scm_try, SCM_ARG2,
	     str_pest_bin_p_normal_approx_alt);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG3,
	     str_pest_bin_p_normal_approx_alt);

  ConfInt ci;
  
  try {
    ci = pest_binomial_p_normal_approx_alt(gh_scm2int(scm_suc),
					   gh_scm2int(scm_try),
					   gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_bin_p_normal_approx_alt);

  return confint2scm(ci);
}

GOOSE_PROC(pest_bin_p_arcsin, "pest-binomial-p-arcsin-method",
	   3,0,0, (SCM scm_suc, SCM scm_try, SCM scm_conf))
{
  SCM_ASSERT(gh_exact_p(scm_suc), scm_suc, SCM_ARG1,
	     str_pest_bin_p_arcsin);
  SCM_ASSERT(gh_exact_p(scm_try), scm_try, SCM_ARG2,
	     str_pest_bin_p_arcsin);
  SCM_ASSERT(gh_number_p(scm_conf), scm_conf, SCM_ARG3,
	     str_pest_bin_p_arcsin);

  ConfInt ci;
  
  try {
    ci = pest_binomial_p_arcsin_method(gh_scm2int(scm_suc),
				       gh_scm2int(scm_try),
				       gh_scm2double(scm_conf));
  } GOOSE_CATCH(str_pest_bin_p_normal_approx_alt);
  
  return confint2scm(ci);
}

void
scm_init_pest()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

#include "pest_wrap.x"
}

// $Id: pest_wrap.cpp,v 1.1 1999/05/26 20:36:27 trow Exp $
