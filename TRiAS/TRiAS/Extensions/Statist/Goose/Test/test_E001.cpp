// This is -*- C++ -*-
// $Id: test_E001.cpp,v 1.10 1999/06/03 15:06:11 trow Exp $

#include <config.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <functional>
#include <descriptive.h>
#include <Random.h>
#include <RealSet.h>

extern "C" {
  // Grr... I hate the -ansi flag.
#ifdef HAVE_ISNAN
  int isnan(double x);
#endif

#ifdef HAVE_ISINF
  int isinf(double x);
#endif
}

Random rnd;

bool check(const char* s, double x, double y)
{
  if ((1+fabs(x-y))/(1+fabs(x)+fabs(y))-1 > 1e-10) {
    cout << "failed on " << s << " : ";
    cout << "cached=" << x << ", should be " << y << endl;
    cout << fabs(x-y) << " " << fabs(x)+fabs(y) << " ";
    cout << fabs(x-y)/(fabs(x)+fabs(y)) << endl;
    return false;
  }
  return true;
}

bool coherent(const RealSet& rs)
{
  if (rs.size() == 0) return true;

  bool correct=true;

  for(size_t i=0; i<rs.size(); ++i) {
    
#ifdef HAVE_ISNAN
    if (isnan(rs.data(i))) {
      cout << "NAN at pos " << i << " in data" << endl;
      correct = false;
    } 
#endif

#ifdef HAVE_ISINF
    if (isinf(rs.data(i))) {
      cout << "Inf at pos " << i << " in data" << endl;
      correct = false;
    }
#endif

#ifdef HAVE_ISNAN
    if (isnan(rs.sorted_data(i))) {
      cout << "NAN at pos " << i << " in sorted data" << endl;
      correct = false;
    } 
#endif
    
#ifdef HAS_ISINF
    if (isinf(rs.sorted_data(i))) {
      cout << "Inf at pos " << i << " in sorted data" << endl;
      correct = false;
    }
#endif

  }

  double min=rs.data(0), max=rs.data(0), sum=rs.data(0), var=0;
  for(size_t i=1; i<rs.size(); ++i) {
    double x = rs.data(i);
    if (x < min) min = x;
    if (x > max) max = x;
    sum += x;
    var += (x-sum/(i+1))*(x-(sum-x)/i);
  }
  double mean = sum / rs.size();
  double sdev = sqrt(var/rs.size());

  correct &= check("Min", rs.min(), min);
  correct &= check("Max", rs.max(), max);
  correct &= check("Mean", rs.mean(), mean);
  correct &= check("Sdev", rs.sdev(), sdev);

  // Check that the sorted data is actually sorted.
  double prev = rs.sorted_data(0);
  for(size_t i=1; i<rs.size(); ++i) {
    if (prev > rs.sorted_data(i)) {
      cout << "failure: sorted_data() is unsorted at " << i << endl;
      correct = false;
      break;
    }
    prev = rs.sorted_data(i);
  }

  // Check that the data and the sorted data are the same...
  double* d = new double[rs.size()];
  memcpy(d, rs.data(), rs.size() * sizeof(double));
  sort(d, d+rs.size(), less<double>());
  int mismatch_count=0;
  for(size_t i=0; i<rs.size(); ++i)
    if (fabs(d[i] - rs.sorted_data(i)) > 1e-15) {
      if (mismatch_count == 0)
	cout << "Mismatch between data() and sorted_data()!" << endl;
      ++mismatch_count;
      cout << "failed at " << i << ": ";
      cout << d[i] << " vs " << rs.sorted_data(i) << endl;
      correct = false;
    }
  if (mismatch_count > 0) {
    cout << mismatch_count << " mismatches total." << endl;
    for(size_t i=0; i<rs.size(); ++i)
      cout << i << " " << d[i] << " " << rs.sorted_data(i) << endl;
  }
  delete [] d;

  return correct;
}

void add_one(RealSet& rs)
{
  cout << "add_one()" << endl;
  if (rs.size() < 2)
    rs.add(rnd.random_uniform());
  else
    rs.add(rnd.random_uniform(rs.min()-goose_range(rs),
			      rs.max()+goose_range(rs)));
}

void add_one_inside(RealSet& rs)
{
  cout << "add_one_inside()" << endl;
  if (rs.size() < 2)
    rs.add(rnd.random_uniform());
  else {
    size_t i = rnd.random_integer(0, rs.size()-1);
    rs.add_at(i, rnd.random_uniform(rs.min()-goose_range(rs),
				    rs.max()+goose_range(rs)));
  }
}

void add_many(RealSet& rs)
{
  cout << "add_many()" << endl;
  double a=0, b=1;
  if (rs.size() > 1) {
    a = rs.min()-goose_range(rs);
    b = rs.max()+goose_range(rs);
  }
  double x[10];
  for(size_t i=0; i<10; ++i)
    x[i] = rnd.random_uniform(a,b);

  rs.add(x, 10);
}

void add_many_inside(RealSet& rs)
{
  cout << "add_many_inside()" << endl;
  double a=0, b=1;
  if (rs.size() > 1) {
    a = rs.min()-goose_range(rs);
    b = rs.max()+goose_range(rs);
  }
  double x[10];
  for(size_t i=0; i<10; ++i)
    x[i] = rnd.random_uniform(a,b);

  if (rs.size() > 0) {
    size_t i = rnd.random_integer(0, rs.size()-1);
    rs.add_at(i, x, 10);
  } else {
    rs.add(x, 10);
  }
}

void remove_one(RealSet& rs)
{
  if (rs.size() == 0) return;
  cout << "remove_one()" << endl;
  size_t i = rnd.random_integer(0,rs.size()-1);
  rs.remove(i);
}

void remove_many(RealSet& rs)
{
  cout << "remove_many()" << endl;
  if (rs.size() > 0) {
    size_t a = rnd.random_integer(0, rs.size()-1);
    size_t b = rnd.random_integer(0, rs.size()-1);
    if (b<a) {
      size_t t=a;
      a=b;
      b=t;
    }
    rs.remove(a,b);
  }
}

void set_one(RealSet& rs)
{
  if (rs.size() == 0) return;

  cout << "set_one()" << endl;

  size_t i = rnd.random_integer(0,rs.size()-1);
  double x = rnd.random_uniform(rs.min()-goose_range(rs),
				rs.max()+goose_range(rs));
  rs.set(i,x);
}

void apply_sin(RealSet& rs)
{
  cout << "apply_sin()" << endl;
  rs.apply(sin);
}

void sort_forward(RealSet& rs)
{
  cout << "sort_forward()" << endl;
  rs.sort(+1);
}

void sort_backward(RealSet& rs)
{
  cout << "sort_backward()" << endl;
  rs.sort(-1);
}

void scramble(RealSet& rs)
{
  cout << "scramble()" << endl;
  rs.scramble();
}

void reverse(RealSet& rs)
{
  cout << "reverse()" << endl;
  rs.reverse();
}

void rank(RealSet& rs)
{
  cout << "rank()" << endl;
  rs.rank();
}

void standardize(RealSet& rs)
{
  if (rs.size() > 2) {
    cout << "standardize()" << endl;
    rs.standardize();
  }
}

void sin_and_exp_transform(RealSet& rs)
{
  cout << "sin_and_exp_transform()" << endl;
  rs.apply(sin);
  rs.exp_transform();
}

void deviations_transform(RealSet& rs)
{
  cout << "deviations_transform(3.14159)" << endl;
  rs.deviations_transform(3.14159);
}

int main()
{
  typedef void (*op_t)(RealSet&);
  op_t ops[] = {
    add_one, add_many, add_one_inside, add_many_inside,
    remove_one, remove_many,
    set_one,
    apply_sin,
    sort_forward, sort_backward, scramble, reverse, rank,
    standardize, sin_and_exp_transform, deviations_transform,
    0 };

  size_t N = 0;
  while (ops[N]) ++N;


  RealSet rs;

  int iter=0;
  do {
    ++iter;
    cout << "(" << iter << ") ";
    op_t fn = ops[rnd.random_integer(0,N-1)];
    fn(rs);
  } while (coherent(rs) && iter<(int)N*2000);
  return 0;
}




// $Id: test_E001.cpp,v 1.10 1999/06/03 15:06:11 trow Exp $
