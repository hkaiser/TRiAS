// This is -*- C++ -*-
// $Id: wilcoxon.cpp,v 1.6 1999/07/14 15:49:34 trow Exp $

/* wilcoxon.cpp
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

#include <config.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <math.h>
#include <limits.h>
#include <specfns.h>
#include "descriptive.h"
#include "wilcoxon.h"

double
wilcoxon_statistic(const RealSet& data, double center)
{
  // Build set of ranked deviations deviations
  RealSet ranks = data;
  ranks.deviations_transform(center);
  ranks.spew(cout);
  ranks.rank();

  double ranks_plus=0;

  const double* d = data.data();
  const double* r = ranks.data();
  unsigned count=0;
  for(size_t i=0; i<data.size(); ++i) {
    if (d[i] > center)
      ranks_plus += r[i];
    else if (d[i] == center) {
      // Otherwise we split the difference.  This insures that
      // ranks_plus + ranks_minus always equals the right thing.
      // (Of course, this occurs with probability 0, so it shouldn't
      // matter :-)
      ranks_plus += r[i]/2;
    }
  }

  return ranks_plus;
}

double
wilcoxon_noties_cdf(unsigned n, unsigned k)
{
  // This is fine as an initial fault-size. (unless you have some sort of
  // funky 128-bit integers that you are using, in which case you will have
  // have to up this value.  But that sort of thing wasn't really an issue
  // in 1999, when this code was written.)  If your unsigned long is 64 bits,
  // this is actually the correct fault-size.  If it is 32 bits, your fault
  // size will get reset to 40.
  static unsigned fault_size = 73;

  // If we can, we try to calculate an exact distribution.
  if (n <= fault_size) {

    size_t N = (n+1)*n/2+1;
    if (k >= N) return 1.0;

    unsigned long* bufferA = new unsigned long[N];
    unsigned long* bufferB = new unsigned long[N];
    for(size_t i=0; i<N; ++i)
      bufferA[i] = bufferB[i] = 0;
    bufferA[0] = bufferA[1] = 1;

    bool fault = false;
    unsigned j=1;
    while (!fault && j<n) {
      size_t psize = (j+1)*j/2+1;
      ++j;
      
      for(size_t i=0; !fault && i<psize; ++i) {
	if (bufferB[i] > ULONG_MAX - bufferA[i] ||
	    bufferB[i+j] > ULONG_MAX - bufferA[i]) {
	  fault = true;
	  fault_size = j;
	} else {
	  bufferB[i] += bufferA[i];
	  bufferB[i+j] += bufferA[i];
	  bufferA[i] = 0;
	}
      }

      unsigned long* tmp = bufferB;
      bufferB = bufferA;
      bufferA = tmp;
    }

    double repl = 0;
    if (!fault) {
      for(size_t i=0; i<=k; ++i)
	repl += bufferA[i];
      repl /= pow(2,(int)n);
    }

    delete [] bufferA;
    delete [] bufferB;

    if (!fault) return repl;
  }

  // The maximum error on this normal approximation rapidly approaches
  // $\exp(-5/2 - \log n)$ as $n$ increases.
  const double m = 0.25*n*(n+1);
  const double sd = sqrt((n/24.0)*(n+1)*(2*n+1));

  // The 0.5 term here is a continuity correction.
  return normal_cdf((k+0.5-m)/sd);
}

double
wilcoxon_general_cdf(const RealSet& rs, double x)
{
  if (rs.size() > 20) {
    // How good is this normal approximation?
    double m = rs.sum()/2.0;
    double sd = goose_rms(rs)/2.0;
    return normal_cdf((x-m)/sd);
  }

  // There must be a better algorithm than this brute-force approach...
  // Something like the above could be used, but with map instead of
  // a linear array lookup.
  const unsigned N = 1 << rs.size();
  const double* d = rs.sorted_data();
  unsigned count = 0;
  for(unsigned i=0; i<N; ++i) {
    unsigned j = i;
    double sum = 0;
    size_t rnk_index = 0;
    while (j) {
      if (j&1) sum += d[rnk_index];
      j = j>>1;
      ++rnk_index;
    }
    if (sum <= x) ++count;
  }
  return count / (double)N;
}



// $Id: wilcoxon.cpp,v 1.6 1999/07/14 15:49:34 trow Exp $
