// This is -*- C++ -*-
// $Id: hypergeom.cpp,v 1.3 1999/07/20 20:08:59 trow Exp $

/* 
 * hypergeom.cpp
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@emccta.com>
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

#include <config.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <iostream.h>
#include "specfns_protos.h"

/*
  Given a population of N objects, we divide them into two groups.
  Group A has n elements, while group B has N-n elements.  This
  functions gives the probability that, if we draw a sample of r
  elements (without replacement) from the population, the number of
  elements drawn from group A is between 0 and x.

  The pdf is given by
  \frac{\binom{n}{x} \binom{N-n}{r-x}}{\binom{N}{r}},
*/

double
hypergeometric_cdf(unsigned x, unsigned r, unsigned n, unsigned N)
{
  assert(n <= N);
  assert(r <= N);
  assert(x <= N);

  if (r+n>x+N) return 0;

  if (x > n)
    x = n;
  if (x > r)
    x = r;

  double log_h = 0, total = 0;

  unsigned i;
  if (r+n > N) {
    i = r+n-N;
    log_h = log_choose(n,r+n-N) - log_choose(N,r);
  } else {
    i = 0;
    unsigned m = N-n;
    for(unsigned j=0; j<r; ++j) 
      log_h += log(m-j) - log(N-j);
  }
  
  total += exp(log_h);

  // Next we use the recursion to tally up the cdf
  for(; i<x; ++i) {
    log_h += log(n-i) + log(r-i) - log(i+1) - log(N-n-r+i+1);
    total += exp(log_h);
  }
  
  return total;
}

/*
  Returns the minimal x such that H(x,r,n,N) <= p
*/
unsigned
inv_hypergeometric_cdf(double p, unsigned r, unsigned n, unsigned N)
{
  // Should check p and r,n,N for reasonableness.

  double log_h = 0, total = 0;
  unsigned x;

  if (r+n > N) {
    x = r+n-N;
    log_h = log_choose(n,r+n-N) - log_choose(N,r);
  } else {
    x = 0;
    unsigned m = N-n;
    for(unsigned j=0; j<r; ++j)
      log_h += log(m-j) - log(N-j);
  }

  total += exp(log_h);
  
  if (total > p) return 0;

  while (total <= p) {
    log_h += log(n-x) + log(r-x) - log(x+1) - log(N-n-r+x+1);
    total += exp(log_h);
    ++x;
  }
  if (total > p && x)
    --x;

  return x;
}



// $Id: hypergeom.cpp,v 1.3 1999/07/20 20:08:59 trow Exp $
