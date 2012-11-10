// This is -*- C++ -*-
// $Id: Kruskal_Wallis.h,v 1.1 1999/07/14 14:22:19 alstrup Exp $

/* Kruskal_Wallis.h
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

#ifndef _INC_KRUSKAL_WALLIS_H
#define _INC_KRUSKAL_WALLIS_H

#include <RealSet.h>
#include <specfns.h>

// Structure that contains the results from the test
struct KruskalWallisResult {
  vector<double> rank_sums;
  double kw;            // The Kruskall Wallis statistic
  double kw_Corr_Ties;  // The Kruskall Wallis statistic corrected for ties
  double p;             // P-value
  double p_Corr_Ties;   // P-value corrected for ties
  int df;               // Degrees of freedom
};

// Calculation of the "Kruskal-Wallias one-way analysis of variance by ranks"
KruskalWallisResult KruskalWallis(vector<RealSet> const &  v1);
#endif // _INC_KRUSKAL_WALLIS_H
