// This is -*- C++ -*-
// $Id: bootstrap.h,v 1.2 1999/03/16 18:28:59 alstrup Exp $


/* bootstrap.h
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

#ifndef _INC_BOOTSTRAP_H
#define _INC_BOOTSTRAP_H

#include "RealSet.h"

RealSet resample_mean(size_t, const RealSet&, int threads=1);
RealSet resample_median(size_t, const RealSet&, int threads=1);
RealSet resample_sdev(size_t, const RealSet&, int threads=1);
RealSet resample_skewness(size_t, const RealSet&, int threads=1);
RealSet resample_kurtosis(size_t, const RealSet&, int threads=1);
RealSet resample_linreg_slope(size_t,
			      const RealSet& x, const RealSet& y,
			      int threads=1);
RealSet resample_linreg_correlation(size_t, 
				    const RealSet& x, const RealSet& y,
				    int threads=1);

#endif // _INC_BOOTSTRAP_H

// $Id: bootstrap.h,v 1.2 1999/03/16 18:28:59 alstrup Exp $
