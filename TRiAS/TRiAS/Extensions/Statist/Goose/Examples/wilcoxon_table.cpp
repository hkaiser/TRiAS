// This is -*- C++ -*-
// $Id: wilcoxon_table.cpp,v 1.3 1999/04/08 18:09:47 trow Exp $

#include <math.h>
#include <iostream>
#include <specfns.h>
#include "wilcoxon.h"

double foo[] = {4.9, 6.0, 6.9, 17.6, 4.5, 12.3, 5.7, 5.3, 9.6, 13.5, 15.7, 7.7, -1};

main()
{
  /*
  RealSet rs;
  int i=0;
  while (foo[i] > 0)
    rs.add(foo[i++]);

  cout << wilcoxon_statistic(rs, 12.0) << endl;
  */
  
  for (unsigned n=1; n<51; ++n) {
    double max_err = 0;
    for (unsigned k=0; k<=n*(n+1)/2; ++k) {
      double p = wilcoxon_noties_cdf(n,k);
      double pest = normal_cdf((k+0.5-0.25*n*(n+1))/sqrt((n/24.0)*(n+1)*(2*n+1)));
      double err = fabs(p-pest);
      if (err > max_err) max_err = err;
    }
    cout << n << " " << max_err << endl;
  }
   
}




// $Id: wilcoxon_table.cpp,v 1.3 1999/04/08 18:09:47 trow Exp $
