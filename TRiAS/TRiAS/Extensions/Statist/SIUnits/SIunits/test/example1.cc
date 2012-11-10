// ----------------------------------------------------------------------
//
// Example 1: fundamentals of instantiation/initialization
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


int main()  {

  using namespace si;     // make most si:: symbols available
  using namespace si::abbreviations;

  // Successful instantiations:
  //
  Length  d1;              // initialized to 0 meters by default
  Length  d2( 2.5 );       // 2.5 meters; same as 2.5 * m
  Length  d3( 1.2 * cm );  // 1.2 centimeters; recorded as .012 * m
  Length  d4( 5 * d3 );    // equivalent to 6.0 centimeters
  Length  d5( 1.23 * pico_ * meter ); // 1.23e-12 * m
  Length  d6( d2 + d3 );   // all dimensions match

  // Bad instantiation attempts; all detected at compile-time:
  //
#ifdef MAKE_MISTAKES
  Length  d7( d2 * d3 );   // oops: an Area can't initialize a Length
  Length  d8 = 3.5;        // oops: 3.5 is not a Length
  Length  d9;              // so far so good, ...
          d9 = 3.5;        // ... oops: 3.5 is still not a Length
#endif  // MAKE_MISTAKES

  return 0;

}  // main()
