// ----------------------------------------------------------------------
//
// fullTest - Test and illustrate each feature of the SIunits package.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//                                                                     \\
// NOTICE:                                                             \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//                                                                     \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// This test is ordered according to the appearance of each feature on
// the SIunits web page.  However, for the purposes of verifying correct
// operation, output functionality is used freely thoughout the test.
//
// ----------------------------------------------------------------------
//
// Note on operating this test:  The basic file should compile and 
// execute properly.  However, a key point of the package is to catch 
// mistaken code by detecting dimension inconsistencies.  The symbols
// MAKE_MISTAKE_1a and so forth may be #defined to cause each
// illustration of a mistake to be activated.
//
// This test includes anyModel.h, and is to be compiled with a 
// -DUSExxxModel selected from among:
//		USEstdModel
//		USErelModel
//		USEhepModel
//		USEqtmModel
//		USEnatModel
// If none of these are defined, USEstdModel will be defaulted to.
//
// ----------------------------------------------------------------------
//
// Note on results in VC++5.0 on NT:  Because of the lack of template 
// specialization compliance, dimension checking is not done in this
// environment, so enabling mistakes will NOT cause problems to be caught.
//
// Also, depending on the model used, 
//
// ----------------------------------------------------------------------


// Make sure one of the models is defined, and include anyModel.h
//
#ifndef USEstdModel
#ifndef USErelModel
#ifndef USEhepModel
#ifndef USEqtmModel
#ifndef USEnatModel
	#define USEstdModel
#endif
#endif
#endif
#endif
#endif

#include <SIUnits/anyModel.h>
  using namespace si;
  using namespace si::abbreviations;
  using namespace si::elements;

#include <iostream.h>
//  using std::cout;
//  using std::endl;

#include <ospace/std/string>
//  using std::string;


void test1() {

  // Test 1: Variables, Base Dimensions, and Base Units

  cout << "\n****** Test 1 ******\n\n";

  Length len1;
  Speed speed1;
  
  Mass mChamber1 ( 100 * kilogram ); 
	cout << "mChamber1 = " << mChamber1 << endl;
	cout << "should be equivalent to 100 kg \n";

  Velocity vel1 = 60.0 * mph;
	cout << "60 mph is " << vel1 << endl;
	cout << "should be equivalent to " << 60 * (mile/m)/(hour/second) 
					<< "m/s \n";
	cout << "(is also equal to " << vel1.measuredIn(km/hour) << 
					" km/hour)\n";

#ifdef MAKE_MISTAKE_1a
  Velocity vel1x = 50 * kilogram;
#endif

  // The base dimensions and samples of others
  Length l1 = 5*micron; 		cout << l1 << endl;
  Mass m1 = 1 * pound;  		cout << m1 << endl;
  Time t1 = 2 * day;			cout << t1 << endl;
  Current i1 = 5 * statampere;		cout << i1 << endl;
  Temperature k1 = 273 * kelvin;	cout << k1 << endl;
  AmountOfSubstance mol1 = 4 * mole;	cout << mol1 << endl;
  LuminousIntensity li1 = 12.5 * cd;	cout << li1 << endl;

  Angle ang1 = 72 * degree;		cout << ang1 << endl;
  Width wid1 = 1 * foot;		cout << wid1 << endl;
  Area  area1 = 30 * acre;		cout << area1 << endl;
  Volume vol1 = 4 * quart;		cout << vol1 << endl;
  Mileage mil1 = 30 * mile/gallon;	cout << mil1 << endl;
  ProbabilityDensity pd1 = .5 / cc;	cout << pd1 << endl;

  Frequency fq1 = 100 * hertz; 		cout << fq1 << endl;
  AngularAcceleration aacc1 = .2 * radian/second2; cout << aacc1 << endl;
  MomentOfInertia mi1 = 5 * kg * m2;	cout << mi1 << endl;
  Density den1 = 10 * gram/cc;		cout << den1 << endl;
  Acceleration acc1 = gravity; 		cout << acc1 << endl;
		// Note that gravitational acceleration is 
		// abbreviated gravity; g is gram.

  Enthalpy enth1 = 1.5 * J/kg;		cout << enth1 << endl;
  MagneticDipoleMoment mag1 = 4.6 * bohrmagneton;   cout << mag1 << endl;
  MagneticQuadrupoleMoment mqm1 = 1 * mu_B * meter; cout << mqm1 << endl;
  CurrentDensity cd1 = 3 * amp/cm2;	cout << cd1 << endl;
  Concentration conc1 = 5 * mol/cc;	cout << conc1 << endl;

  Charge q1 = 10* ePlus;		cout << q1 << endl;
  Momentum p1 = 10 * kg * m/s;		cout << p1 << endl;
  Force f1 = 2 * newton;		cout << f1 << endl;
  Action act1 = 100* planck;		cout << act1 << endl;
  Energy e1 = 12* erg;			cout << e1 << endl;
  Power pow1 = 4.6 * horsepower;	cout << pow1 << endl;
  Pressure pres1 = 1.3 * atm;		cout << pres1 << endl;
  Pressure pres1p = 1.0 * nt_pascal;	cout << pres1p << endl;
  ElectricDipoleMoment d1 = 36 * debye;	cout << d1 << endl;

} // test1


void test2() {

  // Test 2: Working with Dimensioned Quantities

  cout << "\n****** Test 2 ******\n\n";

  // copying and assignment
  Velocity v2a = c/10;
  Velocity v2b ( v2a );
	cout << "v2b in units of c is " << v2b.measuredIn(c) << endl;
	cout << "(should be .1) \n";
  v2b = v2a / 5;
	cout << "v2b in units of c is " << v2b.measuredIn(c) << endl;
	cout << "(should be .02) \n";

#ifdef MAKE_MISTAKE_2a
  Length len2a = 1.5 * m;
  Velocity v2c = len2a;
#endif 

  // Addition and subtraction
  Energy e2a = 4.2 * J;
  Energy e2b = 1000000 * erg; // this is .1 J
  Energy e2c = e2a + e2b;
	cout << "4.2 J + a million ergs is " << e2c << endl;
	cout << "should be 4.3 J \n";
  e2c += e2a;
  	cout << "Add another 4.2 J to get " << e2c << endl;
	cout << "should be 8.5 J \n";
  e2c = e2c - e2b;
  e2c -= e2a;
 	cout << "Now e2c is " << e2c << endl;
	cout << "should be 4.2 J \n";
  
  v2b = -v2a;
	cout << "v2b in units of c is " << v2b.measuredIn(c) << endl;
	cout << "(should be -.1)\n";

  Velocity v2x = -v2a;
  	cout << "v2x in units of c is " << v2x.measuredIn(c) << endl;
	cout << "(should be -.1)\n";

#ifdef MAKE_MISTAKE_2b
  Mass m2a = 4.5 * kg;
  Length len2b = 5.0 * m;
	cout << "The erroneous mass + length is " << (m2a + len2b) << endl; 
#endif 

  // Multiplication and division
  Force f2a = 6 * newton;
  Length len2c = 2 * meter;
  Energy e2d = f2a * len2c;
	cout << "e2d is " << e2d << endl;
	cout << "(should be 12 joules)\n";

#ifdef MAKE_MISTAKE_2c
  Momentum p2a = f2a * len2c;
	cout << "The erroneous momentum is " << p2a << endl;
#endif 

  Momentum p2b = e2d * 10 * s / m;
	cout << "p2b is " << p2b << endl;
	cout << "(should be 120 kg-m/s)\n";
	cout << "  this is " << p2b.measuredIn(bole) << " bole\n";

  e2d /= 3;
	cout << "e2d is " << e2d << endl;
	cout << "(should be 4 joules)\n";

#ifdef MAKE_MISTAKE_2d
  e2d *= p2b;
	cout << "Erroneous e2d *= p2b gives " << e2d << endl;
#endif 

  // sqrt and sqr
  Velocity v2d = sqrt ( e2d/kg );
	cout << "v2d is " << v2d << endl;
	cout << "(should be 2 m/s)\n";

  Width w2a = 5 * m;
  Area a2a = sqr(w2a);
	cout << "a2a is " << a2a << endl;
	cout << "(should be 25 m2)\n";

  // measuredIn() and pure()
  Time t2a = 120 * minute;
	cout << "t2a in hours is " << t2a.measuredIn(hour) << endl;
	cout << "(should be 2 hours)\n";

  double x2 = t2a.pure();
	cout << "t2a.pure() is " << t2a.pure() << endl;
	cout << "(should be 7200 in std model)\n";

#ifdef MAKE_MISTAKE_2e
	cout << "Erroneous measuredIn gives " << t2a.measuredIn(kg) << endl;
#endif 

} // test2



void test2s() {

  // Test 2s: Operations involving Scalar (Dim<0,0,...0>) quantities

  cout << "\n****** Test 3 ******\n\n";

  Number n(24);
  double d(12);
  float  f(6);
  int    i(3);
  double x;
  Number n2(10);

  // Addition and +=

  x = n + n;			cout << "n + n:   48 = " << x << endl;
  x = n + d;			cout << "n + d:   36 = " << x << endl;
  x = n + f;			cout << "n + f:   30 = " << x << endl;
  x = n + i;			cout << "n + i:   27 = " << x << endl;
  x = d + n;			cout << "d + n:   36 = " << x << endl;
  x = f + n;			cout << "f + n:   30 = " << x << endl;
  x = i + n;			cout << "i + n:   27 = " << x << endl;
  n += n2;			cout << "n += n2: 34 = " << n << endl;
  n += d;			cout << "n += d:  46 = " << n << endl;
  n += f;			cout << "n += f:  52 = " << n << endl;
  n += i;			cout << "n += i:  55 = " << n << endl;
  d += n;			cout << "d += n:  67 = " << d << endl;
  f += n;			cout << "f += n:  61 = " << f << endl;
  i += n;			cout << "i += n:  58 = " << i << endl;
  d = 12;
  f = 6;
  i = 3;

  // Subtraction and -=

  x = n - n2;			cout << "n - n2:  45 = " << x << endl;
  x = n - d;			cout << "n - d:   43 = " << x << endl;
  x = n - f;			cout << "n - f:   49 = " << x << endl;
  x = n - i;			cout << "n - i:   52 = " << x << endl;
  x = d - n;			cout << "d - n:  -43 = " << x << endl;
  x = f - n;			cout << "f - n:  -49 = " << x << endl;
  x = i - n;			cout << "i - n:  -52 = " << x << endl;
  n -= n2;			cout << "n -= n2: 45 = " << n << endl;
  n -= d;			cout << "n -= d:  33 = " << n << endl;
  n -= f;			cout << "n -= f:  27 = " << n << endl;
  n -= i;			cout << "n -= i:  24 = " << n << endl;
  d -= n;			cout << "d -= n: -12 = " << d << endl;
  f -= n;			cout << "f -= n: -18 = " << f << endl;
  i -= n;			cout << "i -= n: -21 = " << i << endl;

  // Unary + and -

  n = +n2;			cout << "+n2:     10 = " << n << endl;
  n = -n2;			cout << "-n2:    -10 = " << n << endl;

  // Multiplication and *=

  d = 12;
  f = 6;
  i = 3;
  n = 2;
  x = n * n;			cout << "n * n:    4 = " << x << endl;
  x = n * d;			cout << "n * d:   24 = " << x << endl;
  x = n * f;			cout << "n * f:   12 = " << x << endl;
  x = n * i;			cout << "n * i:    6 = " << x << endl;
  n = 4;
  x = d * n;			cout << "d * n:   48 = " << x << endl;
  x = f * n;			cout << "f * n:   24 = " << x << endl;
  x = i * n;			cout << "i * n:   12 = " << x << endl;
  n *= n2;			cout << "n *= n2: 40 = " << n << endl;
  n *= d;			cout << "n *= d: 480 = " << n << endl;
  n *= f;			cout << "n *= f:2880 = " << n << endl;
  n *= i;			cout << "n *= i:8640 = " << n << endl;
  n = 2;
  d *= n;			cout << "d *= n:  24 = " << d << endl;
  f *= n;			cout << "f *= n:  12 = " << f << endl;
  i *= n;			cout << "i *= n:   6 = " << i << endl;

  // Division and /=

  d = 12;
  f = 6;
  i = 3;
  n = 8640;
  x = n / n2;			cout << "n / n2: 864 = " << x << endl;
  x = n / d;			cout << "n / d:  720 = " << x << endl;
  x = n / f;			cout << "n / f: 1440 = " << x << endl;
  x = n / i;			cout << "n / i: 2880 = " << x << endl;
  n = 3;
  x = d / n;			cout << "d / n:    4 = " << x << endl;
  x = f / n;			cout << "f / n:    2 = " << x << endl;
  x = i / n;			cout << "i / n:    1 = " << x << endl;
  n = 8640;
  n /= n2;			cout << "n /= n2:864 = " << n << endl;
  n /= d;			cout << "n /= d:  72 = " << n << endl;
  n /= f;			cout << "n /= f:   6 = " << n << endl;
  n /= i;			cout << "n /= i:   2 = " << n << endl;
  n = 3;
  d /= n;			cout << "d /= n:   4 = " << d << endl;
  f /= n;			cout << "f /= n:   2 = " << f << endl;
  i /= n;			cout << "i /= n:   1 = " << i << endl;

  // sqrt() and sqr()

  d = 12;
  f = 6;
  i = 3;
  n = 25;
  x = sqrt(n);			cout << "sqrt(n):  5 = " << x << endl;
  x = sqr(n);			cout << "sqr(n):  25 = " << x << endl;

  // Nth<> pow and root

  n2 = 6;
  n = Nth<3>::pow(n2);		cout << "Nth<>pow(n)  216 = " << n << endl;
  n = Nth<3>::root(n);		cout << "Nth<>root(n)   6 = " << n << endl;
  n = 2;
  x = pow(n,d);			cout << "pow(n,d)    4096 = " << x << endl;
  // pow(n,i) and pow(n,f) should not work, 
  // for the same reason that pow(d,i) is ambiguous

  // Some standard math functions

  n = e;
  x = log(n);			cout << "log(n):   1 = " << x << endl;
  n = log(5.0);
  x = exp(n);			cout << "exp(n):   5 = " << x << endl;

  // measuredIn() and pure()

  n = 240;
  x = n.measuredIn(n2);		cout << "measuredIn(n2) 40 = " << x << endl;
  x = n.measuredIn(d);		cout << "measuredIn(d)  20 = " << x << endl;
  x = n.measuredIn(f);		cout << "measuredIn(f)  40 = " << x << endl;
  x = n.measuredIn(i);		cout << "measuredIn(i)  80 = " << x << endl;
  x = n.pure();			cout << "n.pure()      240 = " << x << endl;

  // Relationals

  n = 24;
  d = 12;
  f = 6;
  i = 3;

  if ( n <  n )			cout << "***** BAD ***** n<n " << endl;
  if ( n <  d )			cout << "***** BAD ***** n<d " << endl;
  if ( n <  f ) 		cout << "***** BAD ***** n<f " << endl;
  if ( n <  i )			cout << "***** BAD ***** n<i " << endl;
  if ( n <= n )			cout << "n <= n " << endl;
  if ( n <= d )			cout << "***** BAD ***** n<=d " << endl;
  if ( n <= f ) 		cout << "***** BAD ***** n<=f " << endl;
  if ( n <= i )			cout << "***** BAD ***** n<=i " << endl;
  if ( n == n )			cout << "n == n " << endl;
  if ( n == d )			cout << "***** BAD ***** n==d " << endl;
  if ( n == f )			cout << "***** BAD ***** n==f " << endl;
  if ( n == i )			cout << "***** BAD ***** n==i " << endl;
  if ( n != n )			cout << "***** BAD ***** n!=n " << endl;
  if ( n != d )			cout << "n != d " << endl;
  if ( n != f )			cout << "n != f " << endl;
  if ( n != i )			cout << "n != i " << endl;
  if ( n >= n )			cout << "n >= n " << endl;
  if ( n >= d )			cout << "n >= d " << endl;
  if ( n >= f )			cout << "n >= f " << endl;
  if ( n >= i )			cout << "n >= i " << endl;
  if ( n >  n )			cout << "***** BAD ***** n>n " << endl;
  if ( n >  d )			cout << "n >  d " << endl;
  if ( n >  f )			cout << "n >  f " << endl;
  if ( n >  i )			cout << "n >  i " << endl;

  if ( d <  n )			cout << "d <  n " << endl;
  if ( f <  n )			cout << "f <  n " << endl;
  if ( i <  n )			cout << "i <  n " << endl;
  if ( d <= n )			cout << "d <= n " << endl;
  if ( f <= n )			cout << "f <= n " << endl;
  if ( i <= n )			cout << "i <= n " << endl;
  if ( d == n )			cout << "***** BAD ***** d==n " << endl;
  if ( f == n )			cout << "***** BAD ***** f==n " << endl;
  if ( i == n )			cout << "***** BAD ***** i==n " << endl;
  if ( d != n )			cout << "d != n " << endl;
  if ( f != n )			cout << "f != n " << endl;
  if ( i != n )			cout << "i != n " << endl;
  if ( f >= n ) 		cout << "***** BAD ***** f>=n " << endl;
  if ( i >= n )			cout << "***** BAD ***** i>=n " << endl;
  if ( d >  n )			cout << "***** BAD ***** d>n " << endl;
  if ( f >  n ) 		cout << "***** BAD ***** f>n " << endl;
  if ( i >  n )			cout << "***** BAD ***** i>n " << endl;
 
} // test2s



void test3() {

  // Test 2: Physical Constants

  cout << "\n****** Test 3 ******\n\n";

  // Mathematical constants
  cout << "pi   = " << pi << endl;
  cout << "pi2  = " << pi2 << " (should be " << sqr(pi) << ")\n";
  cout << "e    = " << e << endl;
  cout << "gamma = " << gamma << endl;

  // Physics
  cout << "c    = " << c << endl;
  cout << "mu_0 = " << mu_0 << " (should be " << 4e-7*pi << ")\n";
  cout << "epsilon_0 = " << epsilon_0 << endl;
  cout << "mu_0 * epsilon_0 / c2 = " << mu_0 * epsilon_0 / c2 << endl;
  cout << "G_N  = " << G_N << endl;
  cout << "hBar = " << hBar << endl;
  cout << "m_e  = " << m_e.measuredIn(MeV/c2) << " MeV\n";
  cout << "m_p  = " << m_p.measuredIn(MeV/c2) << " MeV\n";
  cout << "m_n  = " << m_n.measuredIn(MeV/c2) << " MeV\n";
  cout << "m_mu = " << m_mu.measuredIn(MeV/c2) << " MeV\n";
  cout << "alpha= " << alpha << " (= 1/" << 1/alpha << ")\n";
  cout << "R_inf= " << R_inf << endl;
  cout << "Rydberg Energy = " << rydbergenergy << endl;

  cout << "eV   = " << eV << endl;
  cout << "mu_B = " << mu_B << endl;
  cout << "mu_N = " << mu_N << endl;
  cout << "r_e  = " << r_e  << endl;
  cout << "a_0  = " << a_0  << " (Bohr radius)\n";
  cout << "mu_p = " << mu_p.measuredIn(J/tesla) << " J/tesla\n";
  cout << "mu_n = " << mu_n.measuredIn(J/tesla) << " J/tesla\n";
  cout << "mu_mu= " << mu_mu.measuredIn(J/tesla) << " J/tesla\n";

  cout << "m_P  = " << m_P  << " (Planck mass)\n";
  cout << "l_P  = " << l_P  << " (Planck length)\n";
  cout << "t_P  = " << t_P  << " (Planck time)\n";


  // Chemistry
  cout << "N_A  = " << N_A << endl;
  cout << "R    = " << R   << "(molar gas constant)\n";
  cout << "k    = " << k   << endl;
  cout << "amu  = " << amu << endl;
  cout << "standard temperature = " << standardtemperature << endl;
  cout << "atmosphere = " << atmosphere << endl;


} // test3


void test4() {

  // Test 4: Variables, Base Dimensions, and Base Units

  cout << "\n****** Test 4 ******\n\n";

  // This test is somewhat moot on NT
  cout << "Units will not be output automatically in NT, and numerical\n";
  cout << "output expectations marked @ are not expected to be met on NT\n\n";
  
  // Base dimensions
  Length len4a = 1 * inch;
  cout << "len4a =   " << len4a << endl;
  cout << "should be .0254 m in stdModel \n";

  Length::showAs (foot, "'");
  Length len4b = 18*len4a;
  cout << "len4b =   " << len4b << endl;
  cout << "should be 1.5 ' @\n";

#ifdef MAKE_MISTAKE_4a
  Length::showAs (kg, "kilograms");
  cout << "len4b =   " << len4b << endl;
#endif

  // Non-base dimensions with initial display types
  Energy e4a = 1 * J;
  cout << "e4a =     " << e4a << endl;
  cout << "should be 1 J in stdModel \n";
  
  Energy::showAs(erg, "erg");
  Energy e4b = e4a/1000;
  cout << "e4b =     " << e4b << endl;
  cout << "should be 10000 erg @\n";
 
  // Non-base dimensions without initial display types
  Action a4a = 5 * J*s;
  cout << "a4a =     " << a4a << endl;
  cout << "should be 5 kg m^2 / s in stdModel \n";

  Action a4h = hBar;
  cout << "a4h =     " << a4h << endl;
  cout << "should be hBar, which is 1 in qtmModel \n";

  Action::showAs(g*sqr(cm)/s, "cgs-action-units");
  Action a4b = a4a / 1000;
  cout << "a4b =     " << a4b << endl;
  cout << "should be 50000 cgs-action-units @\n";
 
} // test4


void test5() {

  // Test 5: Power-of-ten prefixes

  cout << "\n****** Test 5 ******\n\n";

  // Standard SI prefixes
  Mass m5a = deka_ * g;
  cout << "One dekagram is " << m5a << endl;
  m5a = hecto_ * g;
  cout << "One hectogram is " << m5a << endl;
  m5a = kilo_ * g;
  cout << "One kilogram is " << m5a << endl;
  m5a = myria_ * g;
  cout << "One myriagram is " << m5a << endl;

  Frequency f5a = mega_ * Hz;
  cout << "One megahertz is  " << f5a << endl;
  f5a = giga_ * Hz;
  cout << "One gigahertz is  " << f5a << endl;
  f5a = tera_ * Hz;
  cout << "One terahertz is  " << f5a << endl;
  f5a = peta_ * Hz;
  cout << "One petahertz is  " << f5a << endl;
  f5a = exa_ * Hz;
  cout << "One exahertz is   " << f5a << endl;
  f5a = zetta_ * Hz;
  cout << "One zettahertz is " << f5a << endl;
  f5a = yotta_ * Hz;
  cout << "One yottahertz is " << f5a << endl;

  Length::showAs (meter, "m");
  Length l5a = deci_ * meter;
  cout << "One decimeter is  " << l5a << endl;
  l5a = centi_ * meter;
  cout << "One centimeter is " << l5a << endl;
  l5a = milli_ * meter;
  cout << "One millimeter is " << l5a << endl;
  l5a = micro_ * meter;
  cout << "One micrometer is " << l5a << endl;
  l5a = nano_ * meter;
  cout << "One nanometer is  " << l5a << endl;
  l5a = pico_ * meter;
  cout << "One picometer is  " << l5a << endl;
  l5a = femto_ * meter;
  cout << "One femtometer is " << l5a << endl;
  l5a = atto_ * meter;
  cout << "One attometer is  " << l5a << endl;
  l5a = yocto_ * meter;
  cout << "One yoctometer is " << l5a << endl;
 
  // Simple fractions and numbers
  Length l5b = hemi_ * meter;
  cout << "One hemi * meter is   " << l5b << endl;
  l5b = dozen * in;
  cout << "One dozen inches is   " << l5b.measuredIn(foot) << " foot\n";
  l5b = score*cm;
  cout << "One score cm is       " << l5b << endl;
  l5b = flock*cm;
  cout << "One flock cm is       " << l5b << endl;
  l5b = gross*cm;
  cout << "One gross cm is       " << l5b << endl;
  l5b = bakersdozen*cm;
  cout << "One bakersdozen cm is " << l5b << endl;
  l5b = quire*cm;
  cout << "One quire cm is       " << l5b << endl;
  l5b = ream*cm;
  cout << "One ream cm is        " << l5b << endl;
  l5b = hundred*cm;
  cout << "One hundred cm is     " << l5b << endl;
  l5b = thousand*cm;
  cout << "One thousand cm is    " << l5b << endl;
  l5b = million*cm;
  cout << "One million cm is     " << l5b << endl;
  l5b = billion*cm;
  cout << "One billion cm is     " << l5b << endl;
  l5b = trillion*cm;
  cout << "One trillion cm is    " << l5b << endl;
  l5b = quadrillion*cm;
  cout << "One quadrillion cm is " << l5b << endl;
  l5b = quintillion*cm;
  cout << "One quintillion cm is " << l5b << endl;
  l5b = sextillion*cm;
  cout << "One sextillion cm is  " << l5b << endl;
  l5b = septillion*cm;
  cout << "One septillion cm is  " << l5b << endl;
  l5b = octillion*cm;
  cout << "One octillion cm is   " << l5b << endl;
  l5b = nonillion*cm;
  cout << "One nonillion cm is   " << l5b << endl;
  l5b = decillion*cm;
  cout << "One decillion cm is   " << l5b << endl;
  l5b = googol*cm;
  cout << "One googol cm is   " << l5b << endl;

} // test5


void test6() {

  // Test 6: Powers and roots 

  cout << "\n****** Test 6 ******\n\n";

  // Nth<N>::pow
  Length l6a = 5 * m;
  Area a6a = Nth<2>::pow(l6a);
  cout << "Nth<2>::pow(" << l6a << ") = " << a6a << endl;
  Volume v6a = Nth<3>::pow(l6a);
  cout << "Nth<3>::pow(" << l6a << ") = " << v6a << endl;
  cout << "Nth<4>::pow(" << l6a << ") = " << Nth<4>::pow(l6a) << endl;
  cout << "Nth<5>::pow(" << l6a << ") = " << Nth<5>::pow(l6a) << endl;

  Speed sp6a = 20 * m/s;
  Enthalpy en6a = Nth<2>::pow(sp6a);
  cout << "Nth<2>::pow(" << sp6a << ") = " << en6a << endl;

#ifdef MAKE_MISTAKE_6a
  Area a6b = Nth<3>::pow(l6a);
  cout << "Nth<2>::pow(" << l6a << ") = " << a6b << endl;
#endif


} // test5

int main( int argc, char * argv[] )  {

  string hdr( argv[0] );
  if ( hdr.rfind('/') < hdr.length() )
    hdr = hdr.substr( 1+hdr.rfind('/') );
  cout << '\n' << hdr << "\n-----------" << endl;

  test1();
  test2();
  test2s();
  test3();
  test4();
  test5();
  test6();

  return  0;

}
