// This is -*- C++ -*-
// $Id: descriptive.h,v 1.9 1999/08/07 05:55:03 trow Exp $

/* descriptive.h
 *
 * Copyright (C) 1998, 1999 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@emccta.com>.
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

#ifndef _INC_DESCRIPTIVE_H
#define _INC_DESCRIPTIVE_H

#include <RealSet.h>

double goose_min(const RealSet&);
double goose_max(const RealSet&);
double goose_range(const RealSet&);
double goose_sum(const RealSet&);
double goose_mean(const RealSet&);
double goose_var(const RealSet&);
double goose_vars(const RealSet&);
double goose_sdev(const RealSet&);
double goose_sdevs(const RealSet&);
double goose_mean(const RealSet&);
double goose_percentile(const RealSet&, double p);
double goose_med(const RealSet&);
double goose_q1(const RealSet&);
double goose_q3(const RealSet&);
double goose_iqr(const RealSet&);
double goose_decile(const RealSet&, int i);
double goose_mean_trimmed(const RealSet&, size_t l, size_t r);
double goose_mean_winsorized(const RealSet&, size_t l, size_t r);
double goose_moment(const RealSet&, unsigned k, double x);
double goose_gmean(const RealSet&);
double goose_hmean(const RealSet&);
double goose_rms(const RealSet&);
double goose_meandev(const RealSet&);
double goose_meddev(const RealSet&);
double goose_kurtosis(const RealSet&);
double goose_skewness(const RealSet&);
double goose_excess_kurtosis(const RealSet&);
double goose_momental_skewness(const RealSet&);
double goose_durbin_watson(const RealSet&);
double goose_AR1_independence_z(const RealSet&);
double goose_autocorr(const RealSet&, size_t lag);
double goose_autocorr_z(const RealSet&, size_t lag);
double goose_cramer_vos_mises(const RealSet&);
double goose_anderson_darling(const RealSet&);
double goose_gmean_threshold(const RealSet&, double c);
double goose_mean_threshold_percentage(const RealSet&, double c);
double goose_gmean_threshold_percentage(const RealSet&, double c);

double goose_covar(const RealSet&, const RealSet&);
double goose_corr(const RealSet&, const RealSet&);
double goose_spearman_rho(const RealSet&, const RealSet&);
double goose_kendall_tau(const RealSet&, const RealSet&);

void goose_EDF_D_both(const RealSet&, const RealSet&,
		      double& d_plus, double& d_minus);
double goose_EDF_D_plus(const RealSet&, const RealSet&);
double goose_EDF_D_minus(const RealSet&, const RealSet&);
double goose_EDF_D(const RealSet&, const RealSet&);
double goose_EDF_kuiper_V(const RealSet&, const RealSet&);

double goose_pooled_mean(const RealSet&, const RealSet&);
double goose_pooled_var(const RealSet&, const RealSet&);
double goose_weighted_mean(const RealSet&, const RealSet&);





#endif // _INC_DESCRIPTIVE_H

// $Id: descriptive.h,v 1.9 1999/08/07 05:55:03 trow Exp $








