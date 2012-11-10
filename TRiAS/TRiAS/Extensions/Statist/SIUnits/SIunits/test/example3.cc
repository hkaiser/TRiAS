// ----------------------------------------------------------------------
//
// Example 3:  powers and roots
// 
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//                                                                     \\
// NOTICE:                                                             \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//                                                                     \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// ----------------------------------------------------------------------


#include "stdModel.h"
#include <iostream>


int main()  {

  using namespace si;                    // get most si:: symbols
  using namespace si::abbreviations;
  using namespace std;                   // get all std:: symbols

  Length::showAs( cm, "cm" );            // set default display units

  Length     edge( 2*cm );
  cout << Nth<3>::pow( edge ) << endl;   // display "8 cm^3"

  Volume     cube( 27*m3 );
  cout << Nth<3>::root( cube ) << endl;  // display "300 cm"

  Radius     r( 2*in );                  // Radius is Length
  Perimeter  p( 2 * pi * r );            // Perimeter is Length
  Area       c( pi * sqr(r) );           // a square Radius is an Area
  Diameter   d( sqrt(c / pi) );          // sqrt of an Area is OK
#ifdef MAKE_MISTAKES
  Length     huh( Nth<3>::root(c) );     // oops: cube root is not OK
#endif  // MAKE_MISTAKES

  return 0;

}  // main()
