// This is -*- C++ -*-
// $Id: CochranQ.cpp,v 1.2 1999/07/15 17:14:10 trow Exp $

/* CochranQ.cpp
 *
 * Copyright (C) 1999 Sophus Medical Aps
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

// Nonparametric statistic utility for calculation of the 
// Calculation of the "Cochran Q test"

// See "Nonparametric statistics for the Behavioral sciences",
// Sidney Siegel, N. John Castellan, Jr., McGRAW-HILL, ISBN 0-07-100326-6

#include "config.h"
#include "CochranQ.h"
#include <vector>
 
CochranQResult CochranQ(vector<RealSet> const & v1) {
  CochranQResult result;
  double Li = 0.0;
  double LiTmp = 0.0;
  double Li2 = 0.0;
  double nrOfElements = v1.size();
  double sizeOfElements = v1[0].size();
  vector<size_t> Gj(nrOfElements);
  double Gj2 = 0.0;
  for(size_t itSize = 0; itSize < sizeOfElements; itSize++){
    for(size_t itNr = 0; itNr < nrOfElements; itNr++){
      LiTmp = LiTmp + v1[itNr].data(itSize);
      Gj[itNr] = Gj[itNr] + (size_t)(v1[itNr].data(itSize));
    }
    Li = Li + LiTmp;
    Li2 = Li2 + (LiTmp * LiTmp);
    LiTmp = 0.0;
  }
  for(size_t itGj = 0; itGj < Gj.size(); itGj++){
    Gj2 = Gj2 + (Gj[itGj] * Gj[itGj]);
  }
  result.df = (int)(nrOfElements - 1.0);
  result.Q = (result.df * ((nrOfElements * Gj2) - (Li * Li))) / ((nrOfElements * Li) - Li2);
  result.p = 1.0 - chi_square_cdf(result.df, result.Q);
  return result;
}


