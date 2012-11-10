// This is -*- C++ -*-
// $Id: specfns.h,v 1.7 1999/07/20 20:08:59 trow Exp $

#ifndef _INC_SPECFNS_H
#define _INC_SPECFNS_H

/*
  
  Maybe it is because I'm too young, and missed out on programming in
  the age when Fortran was king, but function names like "gdtr" and
  "chdtri" really leave me cold.  I'd rather just type some more
  characters, which (to me) is well worth not having to remember all
  of those damn abbreviated names.

  (Until I go to my grave, I'm going to remember that character 191 on
  the TRS-80 gave you the solid white rectangle.  And wasn't it "call
  -151" that got you into the Apple II+'s low-level monitor thing?)

 */

#include "specfns_protos.h"

inline double binomial_cdf(int k, int n, double x) { return bdtr(k,n,x); }
inline double neg_binomial_cdf(int k, int n, double x) { return nbdtr(k,n,x); }

// Choice is good.
inline double chisq_cdf(double df, double x) { return chdtr(df,x); }
inline double chi_square_cdf(double df, double x) { return chdtr(df,x); }
inline double inv_chisq_cdf(double df, double x) { return chdtri(df,1-x); }
inline double inv_chi_square_cdf(double df, double x) { return chdtri(df,1-x); }

inline double F_cdf(int df1, int df2, double x) { return fdtr(df1,df2,x); }
inline double inv_F_cdf(int df1, int df2, double p) { return fdtri(df1,df2,1-p);}

inline double log_gamma(double x) { return lgam(x); }
inline double incomplete_gamma(double a, double x) { return igam(a,x); }
inline double inv_incomplete_gamma(double a, double p) { return igami(a,p); }

inline double gamma_cdf(double a, double b, double x) { return gdtr(a,b,x); }

// Default assumption is mean=0, sdev=1
inline double normal_cdf(double x) { return ndtr(x); }
inline double normal_cdf(double low_x, double high_x) { return ndtr(high_x) - ndtr(low_x); }
inline double inv_normal_cdf(double p) { return ndtri(p); }
// Convenience routines for other values of the mean and sdev
inline double normal_cdf(double m, double s, double x) {
  return s > 0 ? ndtr((x-m)/s) : (x<m ? 0 : (x>m ? 1 : 0.5));
}
inline double normal_cdf(double m, double s, double low_x, double high_x) {
  return ndtr((high_x-m)/s) - ndtr((low_x-m)/s);
}
inline double inv_normal_cdf(double m, double s, double p) {
  return m + s*ndtri(p);
}

inline double poisson_cdf(int k, double x) { return pdtr(k,x); }
inline double inv_poisson_cdf(int k, double p) { return pdtri(k,p); }

// You can use it either way...
inline double students_cdf(int df, double t) { return stdtr(df,t); }
inline double students_cdf(int df, double low_t, double high_t) { return stdtr(df, high_t) - stdtr(df, low_t); }
inline double t_cdf(int df, double t) { return stdtr(df,t); }
inline double t_cdf(int df, double low_t, double high_t) { return stdtr(df, high_t) - stdtr(df, low_t); }
inline double inv_students_cdf(int df, double p) { return stdtri(df,p); }
inline double inv_t_cdf(int df, double p) { return stdtri(df,p); }


double hypergeometric_cdf(unsigned x, unsigned r, unsigned n, unsigned N);
unsigned inv_hypergeometric_cdf(double p, unsigned r, unsigned n, unsigned N);


#endif // _INC_SPECFNS_H

// $Id: specfns.h,v 1.7 1999/07/20 20:08:59 trow Exp $
