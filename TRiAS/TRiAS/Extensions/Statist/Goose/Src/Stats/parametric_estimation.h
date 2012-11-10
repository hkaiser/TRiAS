// This is -*- C++ -*-
// $Id: parametric_estimation.h,v 1.5 1999/08/07 05:55:03 trow Exp $

/* 
 * parametric_estimation.h
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
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

/*

  Goose offers access to these functions for convenience, since it is
  sometimes convenient to be able to access this information directly,
  rather than having to build up some sort of RealSet object.  (Of course,
  the RealSet versions of these functions just call these guys, plugging
  in the appropriate values calculated from the data they contain.)

*/

#ifndef _INC_PARAMETRIC_ESTIMATION_H
#define _INC_PARAMETRIC_ESTIMATION_H

#include <ConfInt.h>
#include <RealSet.h>

// Type encoding alternative hypothesis for inference.

enum althyp_t { ALT_NOT_EQUAL, ALT_LESS_THAN, ALT_GREATER_THAN };

/*
  Inference for normally-distributed data.
*/

ConfInt pest_normal_mean(double mean, double sdev, unsigned samples,
			       double conf = 0.95);
ConfInt pest_normal_mean(const RealSet&, double conf = 0.95);

ConfInt pest_normal_difference_of_means_equal_sdev(double mean1, double mean2,
						   double sdev,
						   unsigned N1, unsigned N2,
						   double conf = 0.95);
ConfInt pest_normal_difference_of_means_equal_sdev(const RealSet&,
						   const RealSet&,
						   double conf = 0.95);

ConfInt pest_normal_variance(double var, unsigned samples, double conf = 0.95);
ConfInt pest_normal_variance(const RealSet&, double conf = 0.95);

ConfInt pest_normal_correlation(double r, unsigned samples, double conf=0.95);
ConfInt pest_normal_correlation(const RealSet&, const RealSet&,
				double conf = 0.95);

// t-test

class TTest {
public:
  TTest(const RealSet& rs, double h, althyp_t = ALT_NOT_EQUAL);

  unsigned sample_size() const { return N_; }
  unsigned df() const { return N_-1; }

  double est_mean() const { return em_; }
  double est_stderr() const { return ese_; }
  double hyp_mean() const { return hm_; }

  double t() const { return t_; }
  double p() const { return p_; }

  althyp_t althyp() const { return ah_; }
  bool two_sided() const { return ah_ == ALT_NOT_EQUAL; }
  bool one_sided() const { return !two_sided(); }
  
private:
  althyp_t ah_;
  unsigned N_;
  double em_, ese_, hm_;
  double t_, p_;

};

// F-test for equal variance

class EqualVarianceTest {
public:
  EqualVarianceTest(const RealSet& rs1, const RealSet& rs2,
		    althyp_t = ALT_NOT_EQUAL);

  double est_var1() const { return ev1_; }
  double est_var2() const { return ev2_; }
  double F() const { return F_; }
  double p() const { return p_; }

  althyp_t althyp() const { return ah_; }
  bool two_sided() const { return ah_ == ALT_NOT_EQUAL; }
  bool one_sided() const { return !two_sided(); }

private:
  althyp_t ah_;
  double ev1_, ev2_;
  double F_, p_;
};


/*
  Different ways of estimating the probability of success from a sequence
  of trials.
*/

ConfInt pest_binomial_p_normal_approx(unsigned sucesses, unsigned trials,
				      double conf);
ConfInt pest_binomial_p_normal_approx_alt(unsigned sucesses, unsigned trials,
					  double conf);
ConfInt pest_binomial_p_arcsin_method(unsigned sucesses, unsigned trials,
				      double conf);

ConfInt pest_binomial_difference_of_p_normal_approx(unsigned suc1,
						    unsigned suc2,
						    unsigned tri1,
						    unsigned tri2,
						    double conf);


#endif // _INC_PARAMETRIC_ESTIMATION_H

// $Id: parametric_estimation.h,v 1.5 1999/08/07 05:55:03 trow Exp $
