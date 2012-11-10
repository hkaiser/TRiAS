#include <config.h>
#include <iostream>
#include <gala.h>

/*

  Invert a specific matrix, check that the results match the
  expected results.

 */

int main()
{
  double mat[9] = { 1,  2,  0,
		    0,  4,  0,
		    7, -3,  9 };

  double inv[9] = {      1,     -0.5,      0,
		         0,     0.25,      0,
		    -7.0/9,  17.0/36,   1.0/9 };

  GMat M(3);
  GMat I(3);

  int j=0;
  for(size_t r=0; r<3; ++r)
    for(size_t c=0; c<3; ++c) {
      M(r,c) = mat[j];
      I(r,c) = inv[j];
      ++j;
    }

  M.invert();

  for(size_t r=0; r<3; ++r)
    for(size_t c=0; c<3; ++c) {
      if (fabs(M(r,c)-I(r,c)) > 1e-15) {
	cout << "failed" << endl;
      }
    }
  return 0;
}
