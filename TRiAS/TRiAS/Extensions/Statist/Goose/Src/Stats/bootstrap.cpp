// This is -*- C++ -*-
// $Id: bootstrap.cpp,v 1.3 1999/07/09 18:40:21 trow Exp $

/* bootstrap.cpp
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
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
#include "bootstrap.h"
#ifdef HAVE_LIBPTHREAD
#include <pthread.h>
#endif

struct bootargs {
  size_t N;
  const RealSet* source_x;
  const RealSet* source_y;
  RealSet* target;
};

RealSet
call_inner_bootstrap(void* (fn)(void*), size_t N,
		     const RealSet* ds_x, const RealSet* ds_y,
		     int threads)
{
  if (ds_x && ds_y && ds_x->size() != ds_y->size())
    throw Exception("DataSets are not of the same size");

#ifdef HAVE_LIBPTHREAD
  if (threads > 1) {
    RealSet* targets = new RealSet[threads];
    bootargs* args = new bootargs[threads];
    pthread_t* th_ids = new pthread_t[threads];

    // Spawn the appropriate number of threads, assigning them each an
    // appropriate chunk of the job.
    size_t remaining = N;
    size_t chunk = N/threads;
    if (chunk == 0) chunk = 1;
    for(int i=0; i<threads; ++i) {

      if (chunk > remaining || i == threads-1)
	chunk = remaining;

      args[i].N = chunk;
      args[i].target = &(targets[i]);
      args[i].source_x = ds_x;
      args[i].source_y = ds_y;

      remaining -= chunk;

      pthread_create(&(th_ids[i]), NULL, fn,
		     (void*)&(args[i]));
    }

    // As each thread finishes, stuff its results into boot.
    RealSet boot;
    for(int i=0; i<threads; ++i) {
      pthread_join(th_ids[i], NULL);
      boot.append(targets[i]);
    }

    delete [] targets;
    delete [] args;
    delete [] th_ids;

    return boot;
  }
#endif
  RealSet boot;
  bootargs args = { N, ds_x, ds_y, &boot };
  fn(&args);
  return boot;
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

void*
inner_resample_mean(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src = b->source_x;
  RealSet* tgt = b->target;

  size_t dsN = src->size();
  const double* data = src->data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    double sum=0;
    rnd.random_integer_bulk(0, dsN-1, ind, dsN);
    for(size_t j=0; j<dsN; ++j)
      sum += data[ind[j]];
    tgt->add(sum / dsN);
  }

  delete [] ind;

  return 0;
}

RealSet
resample_mean(size_t N, const RealSet& ds, int threads)
{
  return call_inner_bootstrap(inner_resample_mean, N, &ds, 0, threads);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

void*
inner_resample_median(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src = b->source_x;
  RealSet* tgt = b->target;

  size_t dsN = src->size();
  const double* sdata = src->sorted_data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];
  int* count = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    rnd.random_integer_bulk(0, dsN-1, ind, dsN); // pre-generate indices
    memset(count, 0, dsN*sizeof(int));      // clear the count buffer
    
    for(size_t j=0; j<dsN; ++j)
      ++count[ind[j]];

    int run=0, target=(dsN-1)/2;
    size_t j=0;
    for(;j<dsN && run <= target; ++j)
      run += count[j];

    double med;
    if (dsN % 2 == 0 /* even */) {
      size_t jj=j-1;
      if(run - target == 1)
	while (count[++jj] == 0);
      med = (sdata[j-1] + sdata[jj])/2;
    } else {
      med = sdata[j-1];
    }
    tgt->add(med);
  }

  delete [] ind;
  delete [] count;

  return 0;
}

RealSet
resample_median(size_t N, const RealSet& ds, int threads)
{
  // Make sure the sorted data exists, since RealSet isn't thread safe (yet?)
  // We do the copy and this non-optimal sort (we lose the sort if ds wasn't
  // already sorted, which kinda sucks) just to make sure that the 
  // "transparent" sort doesn't get optimized away by an overzealous compiler
  // that believes our web of lies involving const.
  RealSet our_ds = ds;
  our_ds.sort();
  return call_inner_bootstrap(inner_resample_median, N, &our_ds, 0, threads);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

void*
inner_resample_sdev(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src = b->source_x;
  RealSet* tgt = b->target;

  size_t dsN = src->size();
  const double* data = src->data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    rnd.random_integer_bulk(0, dsN-1, ind, dsN);
    double sum=data[ind[0]], sumsq=0;
    for(size_t j=1; j<dsN; ++j) {
      double x = data[ind[j]];
      sum += x;
      sumsq += (x-sum/(j+1))*(x-(sum-x)/j);
    }
    tgt->add(sqrt(sumsq/dsN));
  }

  delete [] ind;

  return 0;
}

RealSet
resample_sdev(size_t N, const RealSet& ds, int threads)
{
  return call_inner_bootstrap(inner_resample_sdev, N, &ds, 0, threads);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

void*
inner_resample_skewness(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src = b->source_x;
  RealSet* tgt = b->target;

  size_t dsN = src->size();
  const double* data = src->data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    rnd.random_integer_bulk(0, dsN-1, ind, dsN);

    // First pass: find sum
    double sum=0;
    for(size_t j=0; j<dsN; ++j)
      sum += data[ind[j]];
    double mean = sum / dsN;

    double m2=0, m3=0;
    for(size_t j=0; j<dsN; ++j) {
      double x = data[ind[j]] - mean;
      double xx = x*x;
      m2 += xx;
      m3 += xx*x;
    }

    tgt->add(m3/pow(m2, 1.5));
  }

  delete [] ind;
  return 0;
}

RealSet
resample_skewness(size_t N, const RealSet& ds, int threads)
{
  return call_inner_bootstrap(inner_resample_skewness, N, &ds, 0, threads);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

void*
inner_resample_kurtosis(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src = b->source_x;
  RealSet* tgt = b->target;

  size_t dsN = src->size();
  const double* data = src->data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    rnd.random_integer_bulk(0, dsN-1, ind, dsN);

    // First pass: find sum
    double sum=0;
    for(size_t j=0; j<dsN; ++j)
      sum += data[ind[j]];
    double mean = sum / dsN;

    double m2=0, m4=0;
    for(size_t j=0; j<dsN; ++j) {
      double x = data[ind[j]] - mean;
      double xx = x*x;
      m2 += xx;
      m4 += xx*xx;
    }

    tgt->add(m4/(m2*m2));
  }
  
  delete [] ind;
  return 0;
}

RealSet
resample_kurtosis(size_t N, const RealSet& ds, int threads)
{
  return call_inner_bootstrap(inner_resample_kurtosis, N, &ds, 0, threads);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

void*
inner_resample_linreg_slope(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src_x = b->source_x;
  const RealSet* src_y = b->source_y;

  RealSet* tgt = b->target;

  size_t dsN = src_x->size();
  const double* data_x = src_x->data();
  const double* data_y = src_y->data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    rnd.random_integer_bulk(0, dsN-1, ind, dsN);
    double sumx=data_x[ind[0]], sumy=data_y[ind[0]], Sx=0, Sxy=0;
    double x,y,x0,y0;
    for(size_t j=1; j<dsN; ++j) {
      x = data_x[ind[j]];
      y = data_y[ind[j]];
      sumx += x;
      x0 = x - sumx/(j+1);
      y0 = y - sumy/j;
      sumy += y;
      Sx += x0 * (x - (sumx-x)/j);
      Sxy += x0 * y0;
    }
    tgt->add(Sxy/Sx);
  }

  delete [] ind;
  return 0;
}

RealSet
resample_linreg_slope(size_t N, const RealSet& ds_x, const RealSet& ds_y,
		       int threads)
{
  return call_inner_bootstrap(inner_resample_linreg_slope, N,
			      &ds_x, &ds_y, threads);
}

// We have some code duplication here
void*
inner_resample_linreg_corr(void* varg)
{
  bootargs* b = (bootargs*)varg;

  size_t N = b->N;
  if (N == 0) return 0;

  const RealSet* src_x = b->source_x;
  const RealSet* src_y = b->source_y;

  RealSet* tgt = b->target;

  size_t dsN = src_x->size();
  const double* data_x = src_x->data();
  const double* data_y = src_y->data();

  tgt->reserve(N);

  Random rnd;
  int* ind = new int[dsN];

  for(size_t i=0; i<N; ++i) {
    rnd.random_integer_bulk(0, dsN-1, ind, dsN);
    double sumx=data_x[ind[0]], sumy=data_y[ind[0]], Sx=0, Sy=0, Sxy=0;
    double x,y,x0,y0;
    for(size_t j=1; j<dsN; ++j) {
      x = data_x[ind[j]];
      y = data_y[ind[j]];
      sumx += x;
      x0 = x - sumx/(j+1);
      y0 = y - sumy/j;
      sumy += y;
      Sx += x0 * (x - (sumx-x)/j);
      Sxy += x0 * y0;
      Sy += (y - sumy/(j+1)) * y0;
    }
    double m = Sxy/Sx;
    double b = sumy/dsN - m*sumx/dsN;
    tgt->add(b*sqrt(Sx/Sy));
  }

  delete [] ind;
  return 0;
}

RealSet
resample_linreg_correlation(size_t N,
			     const RealSet& ds_x, const RealSet& ds_y,
			     int threads)
{
  return call_inner_bootstrap(inner_resample_linreg_corr, N,
			      &ds_x, &ds_y, threads);
}



/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///


// $Id: bootstrap.cpp,v 1.3 1999/07/09 18:40:21 trow Exp $
