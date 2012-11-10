// This is -*- C++ -*-
// $Id: Spearman.h,v 1.1 1999/07/14 14:22:20 alstrup Exp $

/* Spearman.h
 *
 * Copyright (C) 1999 Sophus Medical Aps.
 *
 * Developed by Mikkel Munck Rasmussen <mikkel@sophusmedical.dk>.
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

#ifndef _INC_SPEARMAN_H
#define _INC_SPEARMAN_H

#include <RealSet.h>
#include <specfns.h>

// Structure that contains the results from the Spearman test
struct SpearmanResult {
  double rs;         
  double rsCorrTies; 
  double t;          
  double tCorrTies;  
  double p;
  double pCorrTies;
  int df;
};

// Calculation of the "Spearman Rank Order Correlation Coefficient"
SpearmanResult spearman_Rocc(RealSet const & x, RealSet const & y);

#endif // _INC_SPERMAN_H
