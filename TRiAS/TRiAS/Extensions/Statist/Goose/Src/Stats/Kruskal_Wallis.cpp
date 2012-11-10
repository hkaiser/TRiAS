// This is -*- C++ -*-
// $Id: Kruskal_Wallis.cpp,v 1.2 1999/07/15 17:14:10 trow Exp $

/* Kruskal_Wallis.cpp
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
// "Kruskal-Wallias one-way analysis of variance by ranks"

// See "Nonparametric statistics for the Behavioral sciences",
// Sidney Siegel, N. John Castellan, Jr., McGRAW-HILL, ISBN 0-07-100326-6

#include "config.h"
#include "Kruskal_Wallis.h"
#include <vector>
#include <iostream>

using namespace std;

KruskalWallisResult KruskalWallis(vector<RealSet> const & v1) {

  //      Equation used to calculate KW when ties are not occuring
  //
  //                        k              2  
  //               12       __    R_average    
  //     KW = (----------  \    -----------j--) - 3(N - 1)
  //            N(N + 1)   /__         n     
  //                       j=1          J
  //

  KruskalWallisResult result;
  vector<unsigned int> n;     // Contains the number of cases in each sample or group
  unsigned int k;             // Number of samples or groups
  unsigned int N;             // Number of cases in the combined sample(the sum of the n's)
  vector<double> R_average;   // Average of the ranks in each sample or group
  double R_average_total;     // Average of the ranks in the combined samples
  
  RealSet v1_ranked;

  k = v1.size();
  // Lets calculate how many elements there are in
  // each element in v1 and store the values in rSizes
  for(unsigned int v1Count= 0; v1Count < v1.size(); v1Count++){
    n.push_back(v1[v1Count].size());
  }
  
  // Lets combine all the samples in 'v1' and store them in 'v1_ranked'
  for(unsigned int nCount = 0; nCount < n.size(); nCount++){
    for(unsigned int rCount = 0; rCount < v1[nCount].size(); rCount++){
      v1_ranked.add(v1[nCount].data(rCount));
    }
  }
  
  N = v1_ranked.size();
  Permutation p1 = v1_ranked.sorting_permutation();
  v1_ranked.permute(p1);
  v1_ranked.rank();
  
  vector<unsigned int> groupsTied;
  unsigned int sumTies = 0;
  for(unsigned int countv1 = 0; countv1 < N; countv1++){
    sumTies = 1;
    for(;v1_ranked.data(countv1) == v1_ranked.data(countv1 +1);countv1++){
      sumTies++;
    }
    if (sumTies != 1) {
      groupsTied.push_back(sumTies);
    }
  }
  
  p1.invert();
  v1_ranked.permute(p1);
  
  unsigned int rSCount;
  unsigned int v1rCount = 0;
  for(unsigned int rVCount = 0; rVCount < n.size(); rVCount++){
    rSCount = 0;
    R_average.push_back(0.0);
    for(;rSCount < n[rVCount];rSCount++){
      R_average[rVCount] = R_average[rVCount] + v1_ranked.data(v1rCount);
      v1rCount++;
    }
    result.rank_sums.push_back(R_average[rVCount]);
    R_average[rVCount] = R_average[rVCount] / n[rVCount];		
  }
  
  // Let's calculate R_average_total
  R_average_total = (N + 1.0) / 2.0;
  
  //Now for the calculation of KW 
  double Sumnj = 0;
  for(unsigned int j = 0; j < k; j++){
    Sumnj = Sumnj + (R_average[j] - R_average_total) * (R_average[j] - R_average_total) * n[j];
  }
  
  result.kw = (Sumnj * (12.0/ (N*(N + 1.0))));
  
  unsigned int GTsize = groupsTied.size();
  double tmpGTdata = 0;
  double T;
  
  T = 0.0;
  for(unsigned int countT = 0; countT < GTsize; countT++){ // lets calculate Tx
    tmpGTdata = groupsTied[countT];
    T = T + (tmpGTdata * tmpGTdata * tmpGTdata - tmpGTdata);
  } 	
  if (result.kw == 0.0){
    result.kw_Corr_Ties = -1;  // If kw equals zero, it´s not possible to
    result.p_Corr_Ties = -1;   // calculate any of the values relating to ties
  }	
  else{
    result.kw_Corr_Ties = result.kw / (1.0 - (T / (N * N * N - N)));
    result.p_Corr_Ties = 1.0 - chi_square_cdf(k - 1,result.kw_Corr_Ties);
  }
  result.p = 1.0 - chi_square_cdf(k - 1, result.kw);
  result.df = k - 1;
  return result;
};
