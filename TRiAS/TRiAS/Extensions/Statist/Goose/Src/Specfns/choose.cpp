// This is -*- C++ -*-
// $Id: choose.cpp,v 1.2 1999/03/16 18:28:39 alstrup Exp $

#include <config.h>
#include "mconf.h"

double
factorial(int n)
{
  static double lookup[24] = {
    1.,
    1.,
    2.,
    6.,
    24.,
    120.,
    720.,
    5040., 
    40320.,
    362880.,
    3628800.,
    39916800.,
    479001600.,
    6227020800.,
    87178291200.,
    1307674368000.,
    20922789888000.,
    355687428096000.,
    6402373705728000.,
    121645100408832000.,
    2432902008176640000.,
    51090942171709440000.,
    1124000727777607680000.,
    25852016738884976640000.
  };
  if (n < 0) {
    return mtherr("factorial", 1);
  } else if (n < 24)
    return lookup[n];
  else
    return floor(exp(log_factorial(n))+0.5);
}

double
log_factorial(int n)
{
  if (n < 0) {
    throw mtherr("log_factorial", 1);
  }
  return lgam(1.0+n);
}

double
choose(int n, int k)
{
  if (n < 1 || k < 0 || k > n)
    return 0;
  else if (k == 0 || k == n)
    return 1;
  else if (k == 1 || k == n-1)
    return n;
  else if (n < 13)
    return factorial(n)/(factorial(k)*factorial(n-k));
  else
    return floor(exp(log_choose(n,k))+0.5);
}

double
log_choose(int n, int k)
{
  return log_factorial(n) - log_factorial(k) - log_factorial(n-k);
}








// $Id: choose.cpp,v 1.2 1999/03/16 18:28:39 alstrup Exp $
