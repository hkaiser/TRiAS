// This is -*- C++ -*-
// $Id: specfns_smob.cpp,v 1.6 1999/04/22 18:58:21 trow Exp $

/* 
 * specfns_smob.cpp
 *
 * Copyright (C) 1999 EMC Capital Management
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

#include <specfns.h>
#include "guilegoose.h"

SCM
scm_cdf_binomal(SCM sk, SCM sn, SCM sx)
{
  SCM_ASSERT(gh_exact_p(sk), sk, SCM_ARG1, "cdf-binomial");
  SCM_ASSERT(gh_exact_p(sn), sn, SCM_ARG2, "cdf-binomial");
  SCM_ASSERT(gh_number_p(sx), sx, SCM_ARG3, "cdf-binomial");

  int k = gh_scm2int(sk);
  int n = gh_scm2int(sn);
  double x = gh_scm2double(sx);
  double p = binomial_cdf(k,n,x);
  
  return gh_double2scm(p);
}

SCM
scm_cdf_neg_binomal(SCM sk, SCM sn, SCM sx)
{
  SCM_ASSERT(gh_exact_p(sk), sk, SCM_ARG1, "cdf-neg-binomial");
  SCM_ASSERT(gh_exact_p(sn), sn, SCM_ARG2, "cdf-neg-binomial");
  SCM_ASSERT(gh_number_p(sx), sx, SCM_ARG3, "cdf-neg-binomial");

  int k = gh_scm2int(sk);
  int n = gh_scm2int(sn);
  double x = gh_scm2double(sx);
  double p = neg_binomial_cdf(k,n,x);

  return gh_double2scm(p);
}

SCM
scm_cdf_chi_square(SCM sdf, SCM sx)
{
  SCM_ASSERT(gh_exact_p(sdf), sdf, SCM_ARG1, "cdf-chi-square");
  SCM_ASSERT(gh_number_p(sx), sx, SCM_ARG2, "cdf-chi-square");

  int df = gh_scm2int(sdf);
  double x = gh_scm2double(sx);
  double p = chi_square_cdf(df,x);

  return gh_double2scm(p);
}

SCM
scm_inv_cdf_chi_square(SCM sdf, SCM sp)
{
  SCM_ASSERT(gh_exact_p(sdf), sdf, SCM_ARG1, "inv-cdf-chi-square");
  SCM_ASSERT(gh_number_p(sp), sp, SCM_ARG2, "inv-cdf-chi-square");

  int df = gh_scm2int(sdf);
  double p = gh_scm2double(sp);
  double x = inv_chi_square_cdf(df,p);

  return gh_double2scm(x);
}

SCM
scm_cdf_F(SCM sdf1, SCM sdf2, SCM sx)
{
  SCM_ASSERT(gh_exact_p(sdf1), sdf1, SCM_ARG1, "cdf-F");
  SCM_ASSERT(gh_exact_p(sdf2), sdf2, SCM_ARG2, "cdf-F");
  SCM_ASSERT(gh_number_p(sx), sx, SCM_ARG3, "cdf-F");

  int df1 = gh_scm2int(sdf1);
  int df2 = gh_scm2int(sdf1);
  double x = gh_scm2double(sx);
  double p = F_cdf(df1,df2,x);

  return gh_double2scm(p);
}

SCM
scm_inv_cdf_F(SCM sdf1, SCM sdf2, SCM sp)
{
  SCM_ASSERT(gh_exact_p(sdf1), sdf1, SCM_ARG1, "inv-cdf-F");
  SCM_ASSERT(gh_exact_p(sdf2), sdf2, SCM_ARG2, "inv-cdf-F");
  SCM_ASSERT(gh_number_p(sp), sp, SCM_ARG3, "inv-cdf-F");

  int df1 = gh_scm2int(sdf1);
  int df2 = gh_scm2int(sdf1);
  double p = gh_scm2double(sp);
  double x = inv_F_cdf(df1,df2,p);

  return gh_double2scm(x);
}

// missing various gamma-related functions

SCM
scm_cdf_normal(SCM sm, SCM ssd, SCM sx)
{
  SCM_ASSERT(gh_number_p(sm), sm, SCM_ARG1, "cdf-normal");
  SCM_ASSERT(gh_number_p(ssd), ssd, SCM_ARG2, "cdf-normal");
  SCM_ASSERT(gh_number_p(sx), sx, SCM_ARG3, "cdf-normal");

  double m = gh_scm2double(sm);
  double sd = gh_scm2double(ssd);
  double x = gh_scm2double(sx);
  double p = normal_cdf(m,sd,x);

  return gh_double2scm(p);
}

SCM
scm_inv_cdf_normal(SCM sm, SCM ssd, SCM sp)
{
  SCM_ASSERT(gh_number_p(sm), sm, SCM_ARG1, "inv-cdf-normal");
  SCM_ASSERT(gh_number_p(ssd), ssd, SCM_ARG2, "inv-cdf-normal");
  SCM_ASSERT(gh_number_p(sp), sp, SCM_ARG3, "inv-cdf-normal");

  double m = gh_scm2double(sm);
  double sd = gh_scm2double(ssd);
  double p = gh_scm2double(sp);
  double x = inv_normal_cdf(m,sd,p);

  return gh_double2scm(x);
}

SCM
scm_cdf_t(SCM sdf, SCM sx)
{
  SCM_ASSERT(gh_exact_p(sdf), sdf, SCM_ARG1, "cdf-t");
  SCM_ASSERT(gh_number_p(sx), sx, SCM_ARG2, "cdf-t");

  int df = gh_scm2int(sdf);
  double x = gh_scm2double(sx);
  double p = t_cdf(df,x);

  return gh_double2scm(p);
}

SCM
scm_inv_cdf_t(SCM sdf, SCM sp)
{
  SCM_ASSERT(gh_exact_p(sdf), sdf, SCM_ARG1, "inv-cdf-t");
  SCM_ASSERT(gh_number_p(sp), sp, SCM_ARG2, "inv-cdf-t");

  int df = gh_scm2int(sdf);
  double p = gh_scm2double(sp);
  double x = inv_t_cdf(df,p);

  return gh_double2scm(x);
}

//////////////////////////////////////////////////////////////////////////////

#define RECAST(x) reinterpret_cast<long int(*)()>(x)

void
scm_init_specfns()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  scm_make_gsubr("cdf-binomial", 3, 0, 0, RECAST(scm_cdf_binomal));
  scm_make_gsubr("cdf-neg-binomial", 3, 0, 0, RECAST(scm_cdf_neg_binomal));

  scm_make_gsubr("cdf-chi-square", 2, 0, 0, RECAST(scm_cdf_chi_square));
  scm_make_gsubr("inv-cdf-chi-square", 2, 0, 0, RECAST(scm_inv_cdf_chi_square));

  scm_make_gsubr("cdf-F", 3, 0, 0, RECAST(scm_cdf_F));
  scm_make_gsubr("inv-cdf-F", 3, 0, 0, RECAST(scm_inv_cdf_F));


  scm_make_gsubr("cdf-t", 2, 0, 0, RECAST(scm_cdf_t));
  scm_make_gsubr("inv-t-normal", 2, 0, 0, RECAST(scm_inv_cdf_t));
  scm_make_gsubr("cdf-normal", 3, 0, 0, RECAST(scm_cdf_normal));
  scm_make_gsubr("inv-cdf-normal", 3, 0, 0, RECAST(scm_inv_cdf_normal));
}



// $Id: specfns_smob.cpp,v 1.6 1999/04/22 18:58:21 trow Exp $
