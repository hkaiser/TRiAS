// This is -*- C++ -*-
// $Id: test_H001.cpp,v 1.5 1999/05/26 20:50:50 trow Exp $

#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <Random.h>
#include <RealSet.h>
#include <bootstrap.h>

inline double t()
{
  struct timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec + tv.tv_usec/1.0e+6;
}

void test(RealSet (*f)(size_t, const RealSet&, int))
{
  Random rnd;
  RealSet data;
  for(size_t i=0; i<500; ++i)
    data.add(rnd.random_normal(0.0, 1.0));
  
  double t1, t2;
  double peak_speed=0;
  int peak_thr=0;
  for (int thr=1; thr<4; ++thr) {
    cout << "threads=" << thr << " --> ";
    cout.flush();

    int count = 0;
    t1 = t();
    while ((t2=t())-t1 < 3) {
      RealSet boot1 = f(5000, data, thr);
      count += 5000;
    }

    double speed = count/(t2-t1);
    if (speed > peak_speed) {
      peak_speed = speed;
      peak_thr = thr;
    }

    cout << speed << " iters/sec (";
    cout << count << " iters, " << t2-t1 << " seconds)" << endl;
  }
  cout << "Peak speed: " << peak_speed << " iters/sec with " << peak_thr;
  cout << " thread";
  if (peak_thr > 1) cout << 's';
  cout << '.' << endl << endl;
}

main()
{
  cout << "Benchmarking resample_mean:" << endl;
  test(resample_mean);

  cout << "Benchmarking resample_median:" << endl;
  test(resample_median);

  cout << "Benchmarking resample_sdev:" << endl;
  test(resample_sdev);
 
  cout << "Benchmarking resample_skewness:" << endl;
  test(resample_skewness);

  cout << "Benchmarking resample_kurtosis:" << endl;
  test(resample_kurtosis);
}


// $Id: test_H001.cpp,v 1.5 1999/05/26 20:50:50 trow Exp $
