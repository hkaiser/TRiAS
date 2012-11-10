#include <iostream>
#include <math.h>
#include <specfns.h>

using namespace std;

/*

  Test the log_gamma() function.
  We use values from the table in Abramowitz & Stegun.

  Since beta_function() and log_beta_function() are defined in terms of
  log_gamma(), this is serves to test those as well...

*/

double table[] = {
  1.025, -0.0139225067,
  1.050, -0.0268530725,
  1.085, -0.0433538143,
  1.115, -0.0560685568,
  1.210, -0.0882013651,
  1.365, -0.1168292401,
  1.450, -0.1214205907,
  1.500, -0.1207822376,
  1.585, -0.1143855058,
  1.670, -0.1017044301,
  1.735, -0.0880269286,
  1.910, -0.0353881118,
  1.990, -0.0041955291,
  2.000,  0.0,
  0 };

int main()
{
  int fail = 0;
  int i=0;
  while (table[i]) {
    double x = table[i];
    double gx = log_gamma(x);
    double pred_gx = table[i+1];
    cout << x << " " << gx << " " << pred_gx << " " << pred_gx-gx << " ";
    if (fabs(pred_gx - gx) > 5e-10) {
      cout << "failed";
      ++fail;
    }
    cout << endl;

    // Test recurrance \Gamma(z+1) = z \Gamma(z)
    for(int j=1; j<50; ++j) {
      pred_gx += log(x);
      x += 1.0;
      gx = log_gamma(x);

      cout << x << " " << gx << " " << pred_gx << " " << pred_gx-gx << " ";
      if (fabs(pred_gx - gx) > 5e-10) {
	cout << "failed";
	++fail;
      }
      cout << endl;
    }

    i += 2;
  }

  cout << "result: " << fail << " failures." << endl;
  return 0;
}
