// This is -*- C++ -*-
// $Id: normality_testing.h,v 1.1 1999/03/31 20:11:45 trow Exp $

/* normality_testing.h
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

#ifndef _INC_NORMALITY_TESTING_H
#define _INC_NORMALITY_TESTING_H

#include <RealSet.h>

double shapiro_wilks_royden_approx(const RealSet& rs);

#endif // _INC_NORMALITY_TESTING_H

// $Id: normality_testing.h,v 1.1 1999/03/31 20:11:45 trow Exp $
