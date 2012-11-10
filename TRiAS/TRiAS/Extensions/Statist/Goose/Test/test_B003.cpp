#include <iostream>
#include <math.h>
#include <specfns.h>

using namespace std;

/*
  
  Check factorial and log_factorial functions.

*/

int main()
{
  int fail = 0;
  double x = 1;
  double lx = 0;
  for(int i=1; i<170; ++i) {
    x *= i;
    lx += log(i);

    double fact = factorial(i);
    double lfact = log_factorial(i);

    cout << i << " : ";
    cout << x << " " << fact << " " << x-fact << " : ";
    cout << lx << " " << lfact << " " << lx-lfact << " : ";
    if (fabs((x - fact)/fact) > 1e-8 || fabs(lx - lfact) > 1e-8) {
      cout << "failed" << endl;
      ++fail;
    }
    cout << endl;

  }
  cout << "result: " << fail << " failures." << endl;
  return 0;
}
