// This is -*- C++ -*-
// $Id: test_G001.cpp,v 1.4 1999/03/16 18:29:40 alstrup Exp $

#include <iostream>
#include <Random.h>
#include <RealSet.h>
#include <LinearRegression.h>

Random rnd;

bool test(double m, double b, int N)
{
  const double x_rng = 5;
  const double err_sd = m * x_rng * 0.2;

  RealSet xset, yset;
  for(int i=0; i<N; ++i) {
    double x = rnd.random_uniform(0, x_rng);
    double y = m*x + b + rnd.random_normal(0, err_sd);
    xset.add(x);
    yset.add(y);
  }

  LinearRegression reg(xset,yset);

  cout << "True model: " << m << " x + " << b << " = y" << endl;
  cout << "Sampled " << N << " x-values in [0," << x_rng << "]" << endl;
  cout << "Sdev of error: " << err_sd << endl;
  cout << "Regression model: " << reg.slope() << " x + " << reg.intercept();
  cout << " = y" << endl;
  cout << "R=" << reg.R() << ", R^2=" << reg.R_sq() << endl;

  bool match = reg.slope_interval(0.995).contains(m)
    && reg.intercept_interval(0.995).contains(b);

  if (!match)
    cout << "The true model is not within the 99.5% range projected intervals." << endl;

  cout << endl;

  return match;
}

int main()
{
  int failures = 0;
  const int N = 1000;
  for(int i=0; i<N; ++i) {
    if (! test(rnd.random_uniform(-10,10),
	       rnd.random_uniform(-10,10),
	       rnd.random_integer(5,20)))
      ++failures;
  }

  // It would be troubling if the failure rate
  // were more than twice the expected value.
  if (failures/(double)N > 0.10)
    cout << "failure" << endl;
  return 0;
}


// $Id: test_G001.cpp,v 1.4 1999/03/16 18:29:40 alstrup Exp $
