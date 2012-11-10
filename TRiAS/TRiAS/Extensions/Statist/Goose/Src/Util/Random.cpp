// This is -*- C++ -*-
// $Id: Random.cpp,v 1.3 1999/07/07 05:09:08 trow Exp $

/* 
 * Random.cpp
 *
 * Copyright (C) 1998 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@emccta.com>. 
 *
 * Why count on the C libraries random()?  Instead, we use the very cool
 * Mersenne Twister method of Matsumoto and Nishimura, as described in
 * their paper "Mersenne Twister: A 623-dimensionally equidistributed uniform
 * pseudorandom number generator", appearing in "ACM Transactions on 
 * Modeling and Computer Simulations: Special Issue on Uniform Random Number
 * Generation" (early 1998).
 *
 * The code we use for generating uniform random numbers in Random is
 * based on the LGPLed code I found in a file named "mt19937-2.c",
 * which was Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura, and
 * said that it was "Coded by Takuji Nishimura, considering the suggestions
 * by Topher Cooper and Marc Rieffel in July-Aug. 1997."  Very similar
 * code also appears in the above-mentioned article.
 *
 * I've reorganized the code.
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
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef HAVE_LIBPTHREAD
#include <pthread.h>
#endif

#ifndef WIN32
#include <unistd.h>
#endif

#include <math.h>
#include "Random.h"

Random common_random;

const unsigned N=624;
const unsigned M=397;
const unsigned MATRIX_A = 0x9908b0df;
const unsigned UPPER_MASK = 0x80000000;
const unsigned LOWER_MASK = 0x7fffffff;
const unsigned mag01[2]={0x0, MATRIX_A};

/* Tempering parameters */   
const unsigned TEMPERING_MASK_B = 0x9d2c5680;
const unsigned TEMPERING_MASK_C = 0xefc60000;
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

void
Random::seed(unsigned s)
{
  if (mt_ == 0)
    mt_ = new unsigned[N];

#ifdef WIN32
  while (s == 0) {
#pragma warning("Fix this! (Asger)")
    // This sucks big-time
    s = (unsigned) time(0);
  }
#else
  while (s == 0) { // 0 is an invalid seed value

    // This, of course, sucks... but if we get interrupted in our read
    // from /dev/random below and don't get a full unsigned worth of random
    // bytes, we want to have *something* non-zero filling up s.
    s = (unsigned)getpid() ^ (unsigned)time(0);

#ifdef HAVE_LIBPTHREAD
    // If we are using threads on a system w/o /dev/random, and if two threads
    // both try to generate one of these "magic seeds" at exactly the same
    // time, we don't want them both getting identical rngs.
    s ^= (unsigned)pthread_self();
#endif

    // I love /dev/random... but if we are on a system that doesn't support
    // it, this open will fail and we'll have to make due with the crappy
    // "randomness" from the above.
    int fd = open("/dev/random", O_RDONLY);
    if (fd != -1) {
      // Can we be interrupted in this read?  I guess so, so we'll settle for
      // some randomness, if not a full sizeof(s)-bytes worth...
      while (read(fd, &s, sizeof(s)) == 0);
      close(fd);
    }
  }
#endif

  mt_[0] = s & 0xffffffff;
  for(mti_=1; mti_<N; ++mti_)
    mt_[mti_] = (69069 * mt_[mti_-1]) & 0xffffffff;
}

unsigned
Random::random()
{
  if (mt_ == 0)
    seed(0);

  if (mti_ >= N)
    stir();

  unsigned y = mt_[mti_++];
  y ^= TEMPERING_SHIFT_U(y);
  y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
  y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
  y ^= TEMPERING_SHIFT_L(y);

  return y;
}

void
Random::random_bulk(unsigned* buffer, size_t count)
{
  if (mt_ == 0)
    seed(0);

  for(size_t i=0; i<count; ++i) {
    if (mti_ >= N)
      stir();

    unsigned y = mt_[mti_++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    buffer[i] = y;
  }
}

void
Random::random_integer_bulk(int a, int b, int* buffer, size_t count)
{
  if (mt_ == 0)
    seed(0);

  for(size_t i=0; i<count;) {
    if (mti_ >= N)
      stir();

    unsigned y = mt_[mti_++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    if (y != UINT_MAX) {
      buffer[i] = a + (int)((b-a+1)*(y*ONE_OVER_UINT_MAX));
      ++i;
    }
  }
}

void
Random::random_uniform_bulk(double* buffer, size_t count)
{
  if (mt_ == 0)
    seed(0);

  for(size_t i=0; i<count; ++i) {
    if (mti_ >= N)
      stir();

    unsigned y = mt_[mti_++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    buffer[i] = y * ONE_OVER_UINT_MAX;
  }
}

void
Random::random_uniform_bulk(double a, double b,
			    double* buffer, size_t count)
{
  random_uniform_bulk(buffer, count);
  for(size_t i=0; i<count; ++i)
    buffer[i] = a+(b-a)*buffer[i];
}

void
Random::random_uniform_open_bulk(double* buffer, size_t count)
{
  if (mt_ == 0)
    seed(0);

  for(size_t i=0; i<count;) {
    if (mti_ >= N)
      stir();

    unsigned y = mt_[mti_++];
    y ^= TEMPERING_SHIFT_U(y);
    y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
    y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
    y ^= TEMPERING_SHIFT_L(y);
    if (y != 0 && y != UINT_MAX) {
      buffer[i] = y * ONE_OVER_UINT_MAX;
      ++i;
    }
  }
  
}

void
Random::random_uniform_open_bulk(double a, double b,
				 double* buffer, size_t count)
{
  random_uniform_open_bulk(buffer, count);
  for(size_t i=0; i<count; ++i)
    buffer[i] = a+(b-a)*buffer[i];
}

double
Random::random_normal()
{
  if (have_extra_normal_) {
    have_extra_normal_ = false;
    return extra_normal_;
  }
  double v1, v2, r;
  do { 
    v1 = random_uniform(-1,1);
    v2 = random_uniform(-1,1);
    r = v1*v1+v2*v2;
  } while (r >= 1.0);
  double fac = sqrt(-2*log(r)/r);
  have_extra_normal_ = true;
  extra_normal_ = v1*fac;
  return v2*fac;
}

void
Random::random_normal_bulk(double* buffer, size_t count)
{
  // With the Box-Muller method, we need an average of 4/pi = 1.273...
  // uniform random numbers between -1 and 1 to generate each normally
  // distributed random number.  We go ahead and generate approx 4/3 = 1.333...
  // uniform random numbers for each normally distributed number we need,
  // to give ourselves a bit of breathing room.
  size_t uN = 2 + 4*count/3 + ((4*count/3) % 2); 
  if (uN % 2) ++uN; // must always be even
  double* uni = 0;
  size_t up=uN;
  
  for(size_t i=0; i<count/2; ++i) {
    double v1, v2, r;
    do {
      if (up >= uN) {
	if (uni == 0) 
	  uni = new double[uN];
	else if (uN > 10) {
	  // If this isn't the first time around, shrink uN so that we
	  // only generate a few normal deviates at a time...
	  uN = 10;
	}
	random_uniform_bulk(-1,1,uni,uN);
	up=0;
      }
      v1 = uni[up++];
      v2 = uni[up++];
      r = v1*v1+v2*v2;
    } while (r >= 1.0);
    double fac = sqrt(-2*log(r)/r);
    buffer[2*i] = v1*fac;
    if (2*i+1 < count)
      buffer[2*i+1] = v2*fac;
  }
  delete [] uni;
}

void
Random::random_normal_bulk(double m, double sd,
		      double* buffer, size_t count)
{
  random_normal_bulk(buffer, count);
  for(size_t i=0; i<count; ++i)
    buffer[i] = m+sd*buffer[i];
}

void
Random::stir()
{
  unsigned kk, y;

  for(kk=0;kk<N-M;++kk) {
    y = (mt_[kk]&UPPER_MASK)|(mt_[kk+1]&LOWER_MASK);
    mt_[kk] = mt_[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
  }

  for (;kk<N-1;kk++) {
    y = (mt_[kk]&UPPER_MASK)|(mt_[kk+1]&LOWER_MASK);
    mt_[kk] = mt_[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1];
  }

  y = (mt_[N-1]&UPPER_MASK)|(mt_[0]&LOWER_MASK);
  mt_[N-1] = mt_[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
  
  mti_ = 0;
}




// $Id: Random.cpp,v 1.3 1999/07/07 05:09:08 trow Exp $
