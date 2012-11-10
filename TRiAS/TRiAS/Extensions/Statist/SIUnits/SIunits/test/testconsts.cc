// ----------------------------------------------------------------------
//
// testconsts.cc - verify certain constants of nature
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//                                                                     \\
// NOTICE:                                                             \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//                                                                     \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// History:
//   03-Aug-1998  WEB  Initial draft
//   02-Nov-1998  WEB  Omit pathname
//
// ----------------------------------------------------------------------



#include "anyModel.h"
#include <string>
#include <iostream>
#include <iomanip>


int main( int argc, char * argv[] )  {

  using namespace si;
  using namespace si::abbreviations;
  using namespace si::elements;

  using std::string;

  using std::cout;
  using std::endl;

  using std::setw;

  #define NL cout << endl;


  NL;
  string hdr( argv[0] );
  if ( hdr.rfind('/') < hdr.length() )
    hdr = hdr.substr( 1+hdr.rfind('/') );
  cout << hdr
       << "\n-------------" << endl;

  NL;
  cout << "Length ..........  " << Length           (1) << endl;
  cout << "Mass ............  " << Mass             (1) << endl;
  cout << "Time ............  " << Time             (1) << endl;
  cout << "Current .........  " << Current          (1) << endl;
  cout << "Temperature .....  " << Temperature      (1) << endl;
  cout << "AmountOfSubstance  " << AmountOfSubstance(1) << endl;
  cout << "LuminousIntensity  " << LuminousIntensity(1) << endl;

  NL;
  cout << "meter .....  " << meter    << endl;
  cout << "kilogram ..  " << kilogram << endl;
  cout << "second ....  " << second   << endl;
  cout << "ampere ....  " << ampere   << endl;
  cout << "kelvin ....  " << kelvin   << endl;
  cout << "mole ......  " << mole     << endl;
  cout << "candela ...  " << candela  << endl;

  NL;
  cout << "joule .....  " << joule           << endl;
  cout << "eV ........  " << electronvolt    << endl;
  cout << "meter^2 ...  " << (meter*meter)   << endl;
  cout << "second^2 ..  " << (second*second) << endl;

  NL;
  cout << "pi = " << pi << endl;
  cout << "   = " << pi.measuredIn(one) << " units" << endl;

  NL;
  cout << "c = " << c << endl;
  cout << "  = " << c.measuredIn(meter/second) << " m/s" << endl;

  NL;
  cout << "k = " << k << endl;
  cout << "  = " << k.measuredIn(joule/kelvin) << " J/K" << endl;

  NL;
  cout << "ePlus = " << ePlus << endl;
  cout << "      = " << ePlus.measuredIn(coulomb) << " coulomb" << endl;

  NL;
  cout << "hBar = " << hBar << endl;
  cout << "     = " << hBar.measuredIn(joule*second) << " J*s" << endl;

  NL;
  cout << "mu_0 = " << mu_0 << endl;
  cout << "     = " << mu_0.measuredIn(N/(A*A)) << " N/(A2)" << endl;
  cout << "eps_0 = " << epsilon_0 << endl;
  cout << "      = " << epsilon_0.measuredIn(F/m) << " F/m" << endl;

  NL;
  cout << "1/alpha = " << (4*pi*epsilon_0*hBar*c/(ePlus*ePlus)) << endl;
  cout << "        = " << 1/alpha.measuredIn(one) << " " << endl;

  NL;
  cout << "Planck mass = " << planckmass << endl;
  cout << "            = " << planckmass.measuredIn(kg) << " kg" << endl;

  NL;
  cout << "G = " << G_N << endl;
  cout << "  = " << G_N.measuredIn(m3/(kg * s*s)) << " m3/kg s2" << endl;

  NL;
  Charge const  q1( A*s * esu.measuredIn(C) );
  Force  const  f12( (q1 * q1 / cm2) / (4*pi*epsilon_0) );
  cout << "q1  = " << q1.measuredIn(esu) << endl;
  cout << "f12 = " << f12.measuredIn(dyne) << endl;

  NL;
  AtomicWeight::showAs( g/mol, "g/mol" );
  cout << "hydrogen is element # " << hydrogen.atomicnumber << endl;
  AtomicWeight const  wt( hydrogen.atomicweight );
  cout << "\n       has atomic weight " << wt << endl;
  cout << "\n       which is " << wt.measuredIn(g/mol) << " g/mol" << endl;

  NL;
  CustomDimension( HyperVolume, 4, 0, 0, 0, 0, 0, 0 );
  HyperVolume const  unitTesseract( meter * meter * meter * meter );

  return 0;

}  // main()
