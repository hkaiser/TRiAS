#include <iostream>
#include <math.h>
#include <specfns.h>

using namespace std;

/*

  Test the inv_normal_cdf() function.

*/

int main()
{
  int fail = 0;
  double max_err = 0;
  for(int i=-50; i<=50; ++i) {
    double x = i/10.0;
    double nx = normal_cdf(x);
    double inx = inv_normal_cdf(nx);
    double ninx = normal_cdf(inx);

    cout << x << " " << inx << " " << inx-x << " ";
    double err = fabs(inx-x);
    if (err > max_err) max_err = err;
    if (err > 1e-10) {
      cout << "failed";
      ++fail;
    }
    cout << endl;

    cout << nx << " " << ninx << " " << nx-ninx << " ";
    err = fabs(nx-ninx);
    if (err > max_err) max_err = err;
    if (err > 1e-10) {
      cout << "failed";
      ++fail;
    }
    cout << endl;

  }
  cout << "max error = " << max_err << endl;
  cout << "result: " << fail << " failures." << endl;
  return 0;
}
