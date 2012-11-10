// This is -*- C++ -*-
// $Id: constants.h,v 1.2 1999/03/16 18:29:31 alstrup Exp $

/* 
 * constants.h
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

#ifndef _INC_CONSTANTS_H
#define _INC_CONSTANTS_H

/*
  I can't believe that ANSI doesn't require this
  stuff to be in <math.h> (grumble...)

  Parameter values are copied from the math.h 
  that comes w/ the GNU C library or computed with
  Mathematica.
*/

#if defined PI
double const GOOSE_PI=PI;
#elif defined M_PI
double const GOOSE_PI=M_PI;
#else
double const GOOSE_PI=3.14159265358979323846;
#endif

#if defined SQRT2
double const GOOSE_SQRT2=SQRT2;
#elif defined M_SQRT2
double const GOOSE_SQRT2=M_SQRT2;
#else
double const GOOSE_SQRT2=1.41421356237309504880;
#endif

/* sqrt(2)/2 */
#if defined SQRTH
double const GOOSE_SQRTH=SQRTH;
#elif defined M_SQRTH
double const GOOSE_SQRTH=M_SQRTH;
#else
double const GOOSE_SQRTH=7.07106781186547524401E-1;
#endif

/* sqrt(2 pi) */
double const GOOSE_SQRT2PI=2.50662827463100050242;

/* log 2**1022 */
#if defined MAXLOG
double const GOOSE_MAXLOG=MAXLOG;
#elif defined M_MAXLOG
double const GOOSE_MAXLOG=M_MAXLOG;
#else
double const GOOSE_MAXLOG=7.08396418532264106224E2;
#endif

#endif // _INC_CONSTANTS_H

// $Id: constants.h,v 1.2 1999/03/16 18:29:31 alstrup Exp $
