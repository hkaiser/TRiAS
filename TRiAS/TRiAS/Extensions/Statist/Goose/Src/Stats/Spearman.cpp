// This is -*- C++ -*-
// $Id: Spearman.cpp,v 1.3 1999/07/21 08:53:17 alstrup Exp $

/* Spearman.cpp
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

//  Nonparametric statistic utility for calculation of the 
// "Spearman Rank Order Correlation Coefficient"

// See "Nonparametric statistics for the Behavioral sciences",
// Sidney Siegel, N. John Castellan, Jr., McGRAW-HILL, ISBN 0-07-100326-6

#include "config.h"
#include "Spearman.h"
#include <vector>
#include <iostream>

using namespace std;

SpearmanResult spearman_Rocc(RealSet const & v1, RealSet const & v2) {
  SpearmanResult result;	
  
  RealSet v1_ranked = v1;
  unsigned int N = v1_ranked.size();
  Permutation p1 = v1_ranked.sorting_permutation();
  
  v1_ranked.permute(p1);
  v1_ranked.rank();
  
  vector<unsigned int> v1GT; // This vector contains the number of ties for each tied value in v1
  vector<unsigned int> v2GT; // This vector contains the number of ties for each tied value in v2
  
  unsigned int sumTies = 0;
  for(unsigned int countv1 = 0; countv1 < N; countv1++){
    sumTies = 1;
    for(;v1_ranked.data(countv1) == v1_ranked.data(countv1 +1);countv1++){
      sumTies++;
    }
    if (sumTies != 1) {
      v1GT.push_back(sumTies);
    }
  }
  
  p1.invert();
  v1_ranked.permute(p1);
  RealSet v2_ranked = v2;
  Permutation p2 = v2_ranked.sorting_permutation();
  v2_ranked.permute(p2);
  v2_ranked.rank();
  
  for(unsigned int countv2 = 0; countv2 < N; countv2++){
    sumTies = 1;
    for(;v2_ranked.data(countv2) == v2_ranked.data(countv2 + 1);countv2++){
      sumTies++;
    }
    if (sumTies != 1) {
      v2GT.push_back(sumTies);
    }         
  }
  
  p2.invert();
  v2_ranked.permute(p2);
  
  double Tx = 0;
  double Ty = 0;
  int tmpGTdata = 0;
  
  unsigned int GTsize = v1GT.size();
  for(unsigned countTx = 0; countTx < GTsize; countTx++){ // lets calculate Tx
    tmpGTdata = v1GT[countTx];
    Tx = Tx + (tmpGTdata * tmpGTdata * tmpGTdata - tmpGTdata);
  } 	
  
  GTsize = v2GT.size();
  tmpGTdata = 0;
  for(unsigned countTy = 0; countTy < GTsize; countTy++){  // lets calculate Ty
    int tmpGTdata = v2GT[countTy];
    Ty = Ty + (tmpGTdata * tmpGTdata * tmpGTdata - tmpGTdata);
  }
  
  RealSet d2;	
  for(unsigned int it = 0; it < N; it++) {
    double d = (v1_ranked.data(it) - v2_ranked.data(it));
    d2.add(d * d);
  }
  
  double sumd2 = 0;
  for(unsigned int i = 0; i < N; i++){
    sumd2 = sumd2 + d2.data(i);
  }
  
  double Ex2;
  double Ey2;	
		
  Ex2 = (N * N * N - N - Tx) / 12;
  Ey2 = (N * N * N - N - Ty) / 12;
  
  result.df = N - 2;

  if ((Ex2 == 0.0) || (Ey2 == 0.0)){
    result.rs = -1.0;                      // If all the elemnts of v1 or v2 are equal, it doesn't make 
    result.t = -1.0;                       // sense to do af spearman's test and we do not calculate 
    result.p = -1.0;                       // anything but the 'degree of freedom' df
    result.rsCorrTies = -1.0;              // We will therefore just assign -1.0 to all the other
    result.tCorrTies = -1.0;               // results
    result.pCorrTies = -1.0;
  } else {
    result.rs = 1 - ((sumd2 * 6) / (N * N * N - N));
    result.rsCorrTies = (Ex2 + Ey2 - sumd2) / (2 * sqrt(Ex2 * Ey2));      
    if (result.rs == 1.0){  
      result.t = -1.0;         // If rs equals -1.0 division by zero would occur
      result.tCorrTies = -1.0; // and we cannot calculate t and p.
      result.p = -1.0;
      result.pCorrTies = -1.0;
    } else {
      result.t = result.rs * (sqrt((N - 2) / (1.0 - (result.rs * result.rs))));
      result.tCorrTies = result.rsCorrTies * (sqrt((N - 2) / 
			 (1.0 - (result.rsCorrTies * result.rsCorrTies))));
      result.pCorrTies = students_cdf(result.df, -result.tCorrTies);
      result.p = students_cdf(result.df, -result.t);
    }   
  }
  return result;
}
