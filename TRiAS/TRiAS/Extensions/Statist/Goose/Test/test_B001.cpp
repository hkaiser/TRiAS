#include <iostream>
#include <math.h>
#include <specfns.h>

using namespace std;

/*

  Tests values of normal cdf, based on some randomly-selected
  table entries from Abramowitz & Setgun.

*/

bool
approx(double x, double y)
{
  return fabs(x-y) < 5e-4;
}

int main()
{
  if (  approx(normal_cdf( 0      ),   0.500) &&
	approx(normal_cdf( 0.10295),   0.541) &&
	approx(normal_cdf(-0.10295), 1-0.541) &&
	approx(normal_cdf( 1.02365),   0.847) &&
	approx(normal_cdf(-1.02365), 1-0.847) &&
	approx(normal_cdf( 0.38262),   0.649) &&
	approx(normal_cdf(-0.38262), 1-0.649)  )
    cout << "ok" << endl;
  else
    cout << "failed" << endl;
  
  return 0;  
}
