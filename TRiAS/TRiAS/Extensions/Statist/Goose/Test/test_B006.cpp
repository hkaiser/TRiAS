#include <iostream>
#include <math.h>
#include <specfns.h>

using namespace std;

/*

  Tests students_cdf and inv_students_cdf

*/

double student_table[] = {
  3,   1.00, 0.8044988905221146790,
  20,  0.50, 0.6887340788594885,
  16, -0.50, 0.3119407776500231,
  1,   0.25, 0.5779791303773693,
  2,  -3.00, 0.04773298313335456603,
  0 };


int main()
{
  int fail = 0;
  int j=0;

  while (student_table[j] != 0) {
    int df = (int)student_table[j];
    double t = student_table[j+1];
    double val = student_table[j+2];
    double x = students_cdf(df,t);
    double invx = inv_students_cdf(df, val);

    cout << df << " " << t << " " << val << " : ";
    cout << x << " " << fabs(x-val) << " : ";
    cout << invx << " " << fabs(t-invx);
    if (fabs(x - val) > 1e-15 || fabs(t-invx) > 1e-15) {
      cout << " failed";
      ++fail;
    }
    cout << endl;

    t = -t;
    val = 1-val;
    x = students_cdf(df, t);

    cout << df << " " << t << " " << val << " " << x << " " << x-val << " ";
    if (fabs(x - val) > 1e-15) {
      cout << " failed";
      ++fail;
    }
    cout << endl;

    j += 3;
  }
  cout << "result: " << fail << " failures." << endl;
  return 0;
}
