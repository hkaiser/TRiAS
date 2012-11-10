// This is -*- C++ -*-
// $Id: normal.h,v 1.2 1999/03/16 18:29:10 alstrup Exp $


/* normal.h
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

#ifndef _INC_NORMAL_H
#define _INC_NORMAL_H

#include "ConfInt.h"
#include "RealSet.h"

/*
 *  Inference about means for normally-distributed data
 */

ConfInt ci_mean(const RealSet&, double conf=0.95);
ConfInt ci_diff_mean(const RealSet&, const RealSet&, double conf=0.95);

#endif // _INC_NORMAL_H

// $Id: normal.h,v 1.2 1999/03/16 18:29:10 alstrup Exp $
