// This is -*- C++ -*-
// $Id: RealSet_smob.cpp,v 1.11 1999/07/09 19:45:15 trow Exp $

/* 
 * RealSet_smob.cpp
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

#include <RealSet.h>
#include <descriptive.h>
#include "guilegoose.h"
#include "snarf.h"

// This is used to decide whether to delete the realset
//  when we free the smob
template <class T>
class OwnerPtr 
{
public:
  OwnerPtr(T* t) : ptr_(t), owned_(true) {}
  ~OwnerPtr() {}

  T* ptr() { return ptr_; }
  
  void disown() { owned_ = false; }

  bool owned() { return owned_; }

private:
  T* const ptr_;
  bool owned_;
};


static long realset_type_tag;

#define SCM_TO_OWNERREALSET(obj) (reinterpret_cast<OwnerPtr<RealSet>*>(SCM_CDR(obj)))
#define SCM_TO_REALSET(obj) (SCM_TO_OWNERREALSET(obj)->ptr())
#define REALSET_P(value)    (SCM_NIMP (value) && SCM_CAR(value) == realset_type_tag)

bool     
scm_realsetp (SCM obj)
{
  return REALSET_P(obj);
}

RealSet* 
scm2realset (SCM obj)
{
  if (!REALSET_P(obj)) return 0;
  return SCM_TO_REALSET(obj);
}

SCM      
realset2scm (RealSet* rs)
{
  SCM_DEFER_INTS;
  OwnerPtr<RealSet>* op = new OwnerPtr<RealSet>(rs);
  scm_done_malloc(sizeof(OwnerPtr<RealSet>));
  SCM smob;
  SCM_NEWCELL (smob);
  SCM_SETCDR (smob, op);
  SCM_SETCAR (smob, realset_type_tag);
  SCM_ALLOW_INTS;
  return smob;
}

SCM 
realset2scm_handle(RealSet* rs)
{
  SCM obj = realset2scm(rs);
  SCM_TO_OWNERREALSET(obj)->disown(); // so we won't destroy it.
  return obj;
}

// This function should mark any SCM objects we reference,
//  at this time none. The return value is automatically marked 
//  by Guile, this is some kind of optimization; so we can
//  return one of the objects.
static SCM
mark_realset (SCM obj)
{
  //  scm_gc_mark (image->name);
  //  return image->update_func;
  return SCM_BOOL_F; // not important
}

static scm_sizet
free_realset (SCM obj)
{
  OwnerPtr<RealSet>* op = SCM_TO_OWNERREALSET(obj);

  // we return the number of bytes freed, for statistics;
  //  hopefully it doesn't have to be exact...
  scm_sizet size = sizeof(OwnerPtr<RealSet>); 

  SCM_DEFER_INTS;

  if (op->owned())
    {
      RealSet* rs = op->ptr();
      delete op;
      delete rs;
      size += sizeof (RealSet);
    }

  SCM_ALLOW_INTS;

  return size;
}

static int
print_realset (SCM obj, SCM port, scm_print_state *pstate)
{
  RealSet* rs = SCM_TO_REALSET(obj);

  string rep = "<";

  if (rs->label().size()) {
    rep += "RealSet `";
    rep += rs->label();
    rep += "'";
  } else {
    rep += "Unnamed RealSet";
  }
  rep += " (";
  if (rs->size()) {
    char buf[128];
    sprintf(buf, "size=%u", rs->size());
    rep += buf;
  } else {
    rep += "empty";
  }
  rep += ")>";

  scm_puts (const_cast<char*>(rep.c_str()), port);

  /* non-zero means success */
  return 1;
}

static scm_smobfuns realset_funcs = {
  mark_realset, 
  free_realset, 
  print_realset, 
  0 // means we can never be equal? 
};

//////////////////////////////////////////////////////////////////////////////

GOOSE_PROC(realsetp, "realset?",
	   1,0,0, (SCM x))
{
  return gh_bool2scm(REALSET_P(x));
}

GOOSE_PROC(make_realset, "make-realset",
	   0,0,1, (SCM scm_l))
{   
  SCM_DEFER_INTS;

  RealSet* rs = new RealSet;

  // Note that we would NOT do this if merely creating a handle.
  scm_done_malloc(sizeof(RealSet));

  SCM_ALLOW_INTS;

  if (! SCM_UNBNDP(scm_l)) {
    while(!gh_null_p(scm_l)) {
      SCM scm_x = gh_car(scm_l);
      SCM_ASSERT(gh_number_p(scm_x), scm_x,
		 "Non-numeric values can't be added to a realset",
		 str_make_realset);
      double x = gh_scm2double(scm_x);
      rs->add(x);
      scm_l = gh_cdr(scm_l);
    }
  }

  return realset2scm(rs);
}

GOOSE_PROC(rs_label, "realset-label",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_label);
  RealSet* rs = scm2realset(scm_rs);
  return gh_str02scm((char*)rs->label().c_str());
}

GOOSE_PROC(rs_set_label, "realset-set-label!",
	   2,0,0, (SCM scm_rs, SCM scm_lab))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_set_label);
  SCM_ASSERT(gh_string_p(scm_lab), scm_lab, SCM_ARG2, str_rs_set_label);
  int len;
  char* foo = gh_scm2newstr(scm_lab, &len);
  string lab(foo);
  free(foo);
  scm2realset(scm_rs)->set_label(lab);
  return scm_rs;
}

GOOSE_PROC(realset_clone, "realset-clone",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_clone);
  RealSet* rs = new RealSet(*scm2realset(scm_rs));
  return realset2scm(rs);
}

GOOSE_PROC(realset_add, "realset-add!",
	   1,0,1, (SCM scm_rs, SCM scm_l))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_add);
  
  RealSet* rs = scm2realset(scm_rs);

  while(!gh_null_p(scm_l)) {
    SCM scm_x = gh_car(scm_l);
    SCM_ASSERT(gh_number_p(scm_x), scm_x,
	       "Non-numeric arguments are not allowed in realset-add!",
	       str_realset_add);
    double x = gh_scm2double(scm_x);
    rs->add(x);
    scm_l = gh_cdr(scm_l);
  }
  
  return scm_rs;
}

GOOSE_PROC(realset_append, "realset-append!",
	   2,0,0, (SCM scm_rs, SCM scm_app))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_append);
  SCM_ASSERT(REALSET_P(scm_app), scm_app, SCM_ARG2, str_realset_append);

  RealSet* rs = scm2realset(scm_rs);
  RealSet* app = scm2realset(scm_app);
  rs->append(*app);

  return scm_rs;
}

GOOSE_PROC(realset_size, "realset-size",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_size);
  RealSet* rs = scm2realset(scm_rs); 
  int n = rs->size();
  return gh_int2scm(n);
}

GOOSE_PROC(realset_ref, "realset-ref",
	   2,0,0, (SCM scm_rs, SCM scm_i))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_ref);
  SCM_ASSERT(gh_exact_p(scm_i), scm_i, SCM_ARG2, str_realset_ref);
  RealSet* rs = scm2realset(scm_rs); 
  int i = gh_scm2int(scm_i);
  SCM_ASSERT(i>=0 && i < (int)(rs->size()), scm_i, SCM_OUTOFRANGE,
	     str_realset_ref);
  double x = rs->data(i);
  return gh_double2scm(x);
}

GOOSE_PROC(realset_sorted_ref, "realset-sorted-ref",
	   2,0,0, (SCM scm_rs, SCM scm_i))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_sorted_ref);
  SCM_ASSERT(gh_exact_p(scm_i), scm_i, SCM_ARG2, str_realset_sorted_ref);
  RealSet* rs = scm2realset(scm_rs); 
  int i = gh_scm2int(scm_i);
  SCM_ASSERT(i>=0 || i < (int)(rs->size()), scm_i, SCM_OUTOFRANGE,
	     str_realset_sorted_ref);
  double x = rs->sorted_data(i);
  return gh_double2scm(x);
}

// Behold the perversity of macros within macros!
// Normally I'm opposed to this sort of thing, but in this case...
#define RSFUNC(fn, str) \
GOOSE_PROC(rsfunc_##fn, str, 1,0,0, (SCM scm_rs)) \
{ \
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rsfunc_##fn); \
  RealSet* rs = scm2realset(scm_rs); \
  double x=0; \
  try { x = goose_##fn(*rs); } GOOSE_CATCH(str_rsfunc_##fn);\
  return gh_double2scm(x); \
}

RSFUNC(min, "realset-min")
RSFUNC(max, "realset-max")
RSFUNC(range, "realset-range")
RSFUNC(sum, "realset-sum")
RSFUNC(mean, "realset-mean")
RSFUNC(var, "realset-var")
RSFUNC(sdev, "realset-sdev")
RSFUNC(sdevs, "realset-sdevs")

GOOSE_PROC(realset_percentile, "realset-percentile",
	   2,0,0, (SCM scm_rs, SCM scm_p))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_percentile);
  SCM_ASSERT(gh_number_p(scm_p), scm_p, SCM_ARG2, str_realset_percentile);

  double x=0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    double p = gh_scm2double(scm_p);
    x = goose_percentile(*rs, p);
  } GOOSE_CATCH(str_realset_percentile);

  return gh_double2scm(x);
}

RSFUNC(med, "realset-med")
RSFUNC(q1, "realset-q1")
RSFUNC(q3, "realset-q3")
RSFUNC(iqr, "realset-iqr")

GOOSE_PROC(realset_decile, "realset-decile",
	   2,0,0, (SCM scm_rs, SCM scm_i))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_realset_decile);
  SCM_ASSERT(gh_exact_p(scm_i), scm_i, SCM_ARG2, str_realset_decile);

  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    int i = gh_scm2int(scm_i);
    x = goose_decile(*rs, i);
  } GOOSE_CATCH(str_realset_decile);

  return gh_double2scm(x);
}

GOOSE_PROC(mean_trimmed, "realset-mean-trimmed",
	   2,1,0, (SCM scm_rs, SCM scm_l, SCM scm_r))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_mean_trimmed);
  SCM_ASSERT(gh_exact_p(scm_l), scm_l, SCM_ARG2, str_mean_trimmed);
  SCM_ASSERT(SCM_UNBNDP(scm_r) || gh_exact_p(scm_r),
	     scm_r, SCM_ARG2, str_mean_trimmed);
  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    int l = gh_scm2int(scm_l);
    int r = SCM_UNBNDP(scm_r) ? l : gh_scm2int(scm_r);
    x = goose_mean_trimmed(*rs,l,r);
  } GOOSE_CATCH(str_mean_trimmed);

  return gh_double2scm(x); 
}

GOOSE_PROC(mean_winsorized, "realset-mean-winsorized",
	   2,1,0, (SCM scm_rs, SCM scm_l, SCM scm_r))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_mean_winsorized);
  SCM_ASSERT(gh_exact_p(scm_l), scm_l, SCM_ARG2, str_mean_winsorized);
  SCM_ASSERT(SCM_UNBNDP(scm_r) || gh_exact_p(scm_r),
	     scm_r, SCM_ARG2, str_mean_winsorized);
  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    int l = gh_scm2int(scm_l);
    int r = SCM_UNBNDP(scm_r) ? l : gh_scm2int(scm_r);
    x = goose_mean_winsorized(*rs,l,r);
  } GOOSE_CATCH(str_mean_winsorized);

  return gh_double2scm(x); 
}

GOOSE_PROC(moment, "realset-moment",
	   2,1,0, (SCM scm_rs, SCM scm_k, SCM scm_x))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_moment);
  SCM_ASSERT(gh_exact_p(scm_k), scm_k, SCM_ARG2, str_moment);
  SCM_ASSERT(SCM_UNBNDP(scm_x) || gh_number_p(scm_x), scm_x, SCM_ARG3,
	     str_moment);
  double m = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    int k = gh_scm2int(scm_k);
    double x = SCM_UNBNDP(scm_x) ? rs->mean() : gh_scm2double(scm_x);
    m = goose_moment(*rs,k,x);
  } GOOSE_CATCH(str_moment);

  return gh_double2scm(m);
}

RSFUNC(gmean, "realset-gmean")
RSFUNC(hmean, "realset-hmean")
RSFUNC(rms, "realset-rms")
RSFUNC(meandev, "realset-meandev")
RSFUNC(meddev, "realset-meddev")
RSFUNC(kurtosis, "realset-kurtosis")
RSFUNC(skewness, "realset-skewness")
RSFUNC(excess_kurtosis, "realset-excess-kurtosis")
RSFUNC(momental_skewness, "realset-momental-skewness")
RSFUNC(durbin_watson, "realset-durbin-watson")
RSFUNC(AR1_independence_z, "realset-AR1-independence-z")

GOOSE_PROC(autocorr, "realset-autocorr",
	   2,0,0, (SCM scm_rs, SCM scm_lag))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_autocorr);
  SCM_ASSERT(gh_exact_p(scm_lag), scm_lag, SCM_ARG2, str_autocorr);

  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    int lag = gh_scm2int(scm_lag);
    SCM_ASSERT(lag>=0 && lag<(int)rs->size()-3, scm_lag,
	       SCM_OUTOFRANGE, str_autocorr);
    x = goose_autocorr(*rs,lag);
  } GOOSE_CATCH(str_autocorr);

  return gh_double2scm(x);
}

GOOSE_PROC(autocorr_z, "realset-autocorr-z",
	   2,0,0, (SCM scm_rs, SCM scm_lag))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_autocorr_z);
  SCM_ASSERT(gh_exact_p(scm_lag), scm_lag, SCM_ARG2, str_autocorr_z);

  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    int lag = gh_scm2int(scm_lag);
    SCM_ASSERT(lag>=0 && lag<(int)rs->size()-3, scm_lag,
	       SCM_OUTOFRANGE, str_autocorr_z);
    x = goose_autocorr_z(*rs, lag);
  } GOOSE_CATCH(str_autocorr_z);
    
  return gh_double2scm(x);
}

GOOSE_PROC(cvm, "realset-cramer-von-mises",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_cvm);
  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    x = goose_cramer_vos_mises(*rs);
  } GOOSE_CATCH(str_cvm);

  return gh_double2scm(x);
}

GOOSE_PROC(anddar, "realset-anderson-darling",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_anddar);
  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    x = goose_anderson_darling(*rs);
  } GOOSE_CATCH(str_cvm);

  return gh_double2scm(x);
}

GOOSE_PROC(gmeanthresh, "realset-gmean-threshold",
	   2,0,0, (SCM scm_rs, SCM scm_c))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_gmeanthresh);
  SCM_ASSERT(gh_number_p(scm_c), scm_c, SCM_ARG2, str_gmeanthresh);

  double c = gh_scm2double(scm_c);
  SCM_ASSERT(c >= 0 && c <= 1, scm_c, SCM_OUTOFRANGE, str_gmeanthresh);
  double x = 0;
  try {
    RealSet* rs = scm2realset(scm_rs);
    x = goose_gmean_threshold(*rs, c);
  } GOOSE_CATCH(str_gmeanthresh);

  return gh_double2scm(x);
}

GOOSE_PROC(covar, "realset-covar",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_covar);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_covar);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_covar(*rs1, *rs2);
  } GOOSE_CATCH(str_covar);

  return gh_double2scm(x);
}

GOOSE_PROC(corr, "realset-corr",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_corr);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_corr);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_corr(*rs1, *rs2);
  } GOOSE_CATCH(str_corr);

  return gh_double2scm(x);
}

GOOSE_PROC(spearrho, "realset-spearman-rho",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_spearrho);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_spearrho);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_spearman_rho(*rs1, *rs2);
  } GOOSE_CATCH(str_spearrho);

  return gh_double2scm(x);
}

GOOSE_PROC(kentau, "realset-kendall-tau",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_kentau);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_kentau);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_kendall_tau(*rs1, *rs2);
  } GOOSE_CATCH(str_kentau);

  return gh_double2scm(x);
}

GOOSE_PROC(edf_Dp, "realset-EDF-D+",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_edf_Dp);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_edf_Dp);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_EDF_D_plus(*rs1, *rs2);
  } GOOSE_CATCH(str_edf_Dp);

  return gh_double2scm(x);
}

GOOSE_PROC(edf_Dm, "realset-EDF-D-",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_edf_Dm);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_edf_Dm);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_EDF_D_minus(*rs1, *rs2);
  } GOOSE_CATCH(str_edf_Dm);

  return gh_double2scm(x);
}


GOOSE_PROC(edf_D, "realset-EDF-D",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_edf_D);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_edf_D);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_EDF_D(*rs1, *rs2);
  } GOOSE_CATCH(str_edf_D);

  return gh_double2scm(x);
}

GOOSE_PROC(edf_kv, "realset-EDF-kuiper-V",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_edf_kv);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_edf_kv);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_EDF_kuiper_V(*rs1, *rs2);
  } GOOSE_CATCH(str_edf_kv);

  return gh_double2scm(x);
}

GOOSE_PROC(pooled_mean, "realset-pooled-mean",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_pooled_mean);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_pooled_mean);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_pooled_mean(*rs1, *rs2);
  } GOOSE_CATCH(str_pooled_mean);

  return gh_double2scm(x);
}

GOOSE_PROC(pooled_var, "realset-pooled-var",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs1), scm_rs1, SCM_ARG1, str_pooled_var);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG2, str_pooled_var);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_pooled_var(*rs1,*rs2);
  } GOOSE_CATCH(str_pooled_var);
  return gh_double2scm(x);
}

GOOSE_PROC(wtd_mean, "realset-weighted-mean",
	   2,0,0, (SCM scm_rs1, SCM scm_rs2))
{
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs1, SCM_ARG1, str_wtd_mean);
  SCM_ASSERT(REALSET_P(scm_rs2), scm_rs2, SCM_ARG1, str_wtd_mean);
  double x = 0;
  try {
    RealSet* rs1 = scm2realset(scm_rs1);
    RealSet* rs2 = scm2realset(scm_rs2);
    x = goose_weighted_mean(*rs1, *rs2);
  } GOOSE_CATCH(str_wtd_mean);

  return gh_double2scm(x);
}

GOOSE_PROC(rs_sort, "realset-sort!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_sort);
  RealSet* rs = scm2realset(scm_rs);
  rs->sort();
  return scm_rs;
}

GOOSE_PROC(rs_lin_trans, "realset-linear-transform!",
	   3,0,0, (SCM scm_rs, SCM scm_a, SCM scm_b))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_lin_trans);
  SCM_ASSERT(gh_number_p(scm_a), scm_a, SCM_ARG2, str_rs_lin_trans);
  SCM_ASSERT(gh_number_p(scm_b), scm_b, SCM_ARG3, str_rs_lin_trans);
  RealSet* rs = scm2realset(scm_rs);
  double a = gh_scm2double(scm_a);
  double b = gh_scm2double(scm_b);
  rs->linear_transform(a,b);
  return scm_rs;
}

GOOSE_PROC(rs_log_trans, "realset-log-transform!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_log_trans);
  RealSet* rs = scm2realset(scm_rs);
  rs->log_transform();
  return scm_rs;
}


GOOSE_PROC(rs_exp_trans, "realset-exp-transform!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_exp_trans);
  RealSet* rs = scm2realset(scm_rs);
  rs->exp_transform();
  return scm_rs;
}

GOOSE_PROC(rs_logit_trans, "realset-logit-transform!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_logit_trans);
  RealSet* rs = scm2realset(scm_rs);
  rs->logit_transform();
  return scm_rs;
}

GOOSE_PROC(rs_reverse, "realset-reverse!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_reverse);
  RealSet* rs = scm2realset(scm_rs);
  rs->reverse();
  return scm_rs;
}

GOOSE_PROC(rs_scramble, "realset-scramble!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_scramble);
  RealSet* rs = scm2realset(scm_rs);
  rs->scramble();
  return scm_rs;
}

GOOSE_PROC(rs_rank, "realset-rank!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_rank);
  RealSet* rs = scm2realset(scm_rs);
  rs->rank();
  return scm_rs;
}

GOOSE_PROC(rs_std, "realset-standardize!",
	   1,0,0, (SCM scm_rs))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_std);
  RealSet* rs = scm2realset(scm_rs);
  rs->standardize();
  return scm_rs;
}

GOOSE_PROC(rs_gt, "realset-greater-than",
	   2,0,0, (SCM scm_rs, SCM scm_x))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_gt);
  SCM_ASSERT(gh_number_p(scm_x), scm_x, SCM_ARG2, str_rs_gt);
  RealSet* rs = scm2realset(scm_rs);
  double x = gh_scm2double(scm_x);
  return gh_int2scm(rs->greater_than(x));
}

GOOSE_PROC(rs_lt, "realset-less-than",
	   2,0,0, (SCM scm_rs, SCM scm_x))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_lt);
  SCM_ASSERT(gh_number_p(scm_x), scm_x, SCM_ARG2, str_rs_lt);
  RealSet* rs = scm2realset(scm_rs);
  double x = gh_scm2double(scm_x);
  return gh_int2scm(rs->less_than(x));
}

GOOSE_PROC(rs_between, "realset-between",
	   3,0,0, (SCM scm_rs, SCM scm_x, SCM scm_y))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_between);
  SCM_ASSERT(gh_number_p(scm_x), scm_x, SCM_ARG2, str_rs_between);
  SCM_ASSERT(gh_number_p(scm_y), scm_y, SCM_ARG3, str_rs_between);
  RealSet* rs = scm2realset(scm_rs);
  double x = gh_scm2double(scm_x);
  double y = gh_scm2double(scm_y);
  return gh_int2scm(rs->between(x,y));
}

GOOSE_PROC(rs_eq, "realset-equal-to",
	   2,0,0, (SCM scm_rs, SCM scm_x))
{
  SCM_ASSERT(REALSET_P(scm_rs), scm_rs, SCM_ARG1, str_rs_eq);
  SCM_ASSERT(gh_number_p(scm_x), scm_x, SCM_ARG2, str_rs_eq);
  RealSet* rs = scm2realset(scm_rs);
  double x = gh_scm2double(scm_x);
  return gh_int2scm(rs->equal_to(x));
}

GOOSE_PROC(rs_set_add, "realset+",
	   2,0,0, (SCM rs1, SCM rs2))
{
  SCM_ASSERT(REALSET_P(rs1), rs1, SCM_ARG1, str_rs_set_add);
  SCM_ASSERT(REALSET_P(rs2), rs2, SCM_ARG1, str_rs_set_add);

  RealSet* rs = 0;
  try {
    // Crap: potential memory leak if something throws.
    rs = new RealSet(*scm2realset(rs1));
    *rs += *scm2realset(rs2);
  } GOOSE_CATCH(str_rs_set_add);
  
  return realset2scm(rs);
}

GOOSE_PROC(rs_set_sub, "realset-",
	   2,0,0, (SCM rs1, SCM rs2))
{
  SCM_ASSERT(REALSET_P(rs1), rs1, SCM_ARG1, str_rs_set_sub);
  SCM_ASSERT(REALSET_P(rs2), rs2, SCM_ARG1, str_rs_set_sub);

  RealSet* rs = 0;
  try {
    // Crap: potential memory leak if something throws.
    rs = new RealSet(*scm2realset(rs1));
    *rs -= *scm2realset(rs2);
  } GOOSE_CATCH(str_rs_set_sub);
  
  return realset2scm(rs);
}

GOOSE_PROC(rs_set_mul, "realset*",
	   2,0,0, (SCM rs1, SCM rs2))
{
  SCM_ASSERT(REALSET_P(rs1), rs1, SCM_ARG1, str_rs_set_mul);
  SCM_ASSERT(REALSET_P(rs2), rs2, SCM_ARG1, str_rs_set_mul);

  RealSet* rs = 0;
  try { 
    // Crap: potential memory leak if something throws.
    rs = new RealSet(*scm2realset(rs1));
    *rs *= *scm2realset(rs2);
  } GOOSE_CATCH(str_rs_set_mul);
  
  return realset2scm(rs);
}


//////////////////////////////////////////////////////////////////////////////

void
scm_init_realset()
{
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  realset_type_tag = scm_newsmob(&realset_funcs);

#include "RealSet_smob.x"

}


// $Id: RealSet_smob.cpp,v 1.11 1999/07/09 19:45:15 trow Exp $
