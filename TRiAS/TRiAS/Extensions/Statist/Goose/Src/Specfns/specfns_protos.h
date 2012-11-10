// This is -*- C++ -*-
// $Id: specfns_protos.h,v 1.3 1999/07/15 17:42:32 trow Exp $

#ifndef _INC_SPECFNS_PROTOS_H
#define _INC_SPECFNS_PROTOS_H

//  Prototypes for probability functions from the cephes library

/* Combinatorial functions */
double factorial(int n);
double log_factorial(int n);
double choose(int n, int k);
double log_choose(int n, int k);

/* Binomial distribution */
double bdtr(int k, int n, double p);
double bdtrc(int k, int n, double p); /* complemented */

/* Negative binomial distribution */
double nbdtr(int k, int n, double p);
double nbdtrc(int k, int n, double p); /* complemented */

/* Beta distribution */
double incbet(double a, double b, double x); /* incomplete beta intgral */
double incbi(double a, double b, double p); /* inv incomplete beta integral */

/* Chi-square distribution */
double chdtr(double df, double x);
double chdtrc(double df, double x); /* complemented */
double chdtri(double df, double p); /* inverse of complemented */

/* F distribution */
double fdtr(int df1, int df2, double x);
double fdtrc(int df1, int df2, double x); /* complemented */
double fdtri(int df1, int df2, double p); /* inverse of complemented */

/* Gamma function */
double gammafn(double x);
double lgam(double x);  /* log of gamma function */
double igam(double a, double x); /* incomplete gamma integral */
double igamc(double a, double x); /* complemented */
double igami(double a, double p); /* inverse incomplete gamma integral */

/* Gamma distribution */
double gdtr(double a, double b, double x);
double gdtrc(double a, double b, double x); /* complemented */

/* Normal distribution */
double ndtr(double x);
double ndtri(double p); /* inverse */

/* Poisson distribution */
double pdtr(int k, double m);
double pdtrc(int k, double m); /* complemented */
double pdtri(int k, double p); /* inverse */

/* Student's t distribution */
double stdtr(int k, double t);
double stdtri(int k, double p); /* inverse */


#endif // _INC_SPECFNS_PROTOS_H

// $Id: specfns_protos.h,v 1.3 1999/07/15 17:42:32 trow Exp $

