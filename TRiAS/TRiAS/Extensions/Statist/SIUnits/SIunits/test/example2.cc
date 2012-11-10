// ----------------------------------------------------------------------
//
// Example 2:  computation and output
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

  using namespace si;             // get most si:: symbols
  using namespace si::abbreviations;
  using namespace std;            // get all std:: symbols

  // Display with default labels:
  //
  cout << inch << endl;           // display "0.0254 m"

  // Prefer centimeter labels from now on:
  //
  Length::showAs( cm, "cm" );     // set default display units
  cout << inch << endl;           // display "2.54 cm"

  // Compute/display:
  //
  Length  len( 2*cm );
  Width   wid( 3*cm );             // Width is a synonym for Length
  Area    a( len * wid );
  cout << a << endl;              // display "6 cm^2"

  // Prefer to label Area in square meters:
  //
  Area::showAs( m*m, "m2" );      // set default display units
  cout << a << endl;              // display "0.0006 m2"
  cout << a*4 << endl;            // display "0.0024 m2"

  // But a volume reverts:
  //
  cout << a * 4*cm << endl;       // display "24 cm^3"

  return 0;

}  // main()
