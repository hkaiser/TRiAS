// ----------------------------------------------------------------------
//
// NT_simath.h - math header file for si Library
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


#ifndef SI_H
  #include "si.h"
#endif


#include <cmath>


namespace si  {


  #define A1( f )			\
    inline  si::Number  f( const si::Number x )  {	\
      return  ::f( x.pure() );	\
    }
  
  
  #define A2( f )			\
    inline  si::Number  f( const si::Number x, const si::Number y )  {	\
      return  ::f( x.pure(), y.pure() );	\
    }
  
  
  // -----  Trigonometric:
  //
  A1( cos )		// cosine
  A1( sin )		// sine
  A1( tan )		// tangent
  
  // -----  Inverse trigonometric:
  //
  A1( acos )		// arc cosine
  A1( asin )		// arc sine
  A1( atan )		// arc tangent
  A2( atan2 )		// atan( arg1 / arg2 )
  
  // -----  Hyperbolic:
  //
  A1( cosh )		// hyperbolic cosine
  A1( sinh )		// hyperbolic sine
  A1( tanh )		// hyperbolic tangent
  
  // -----  Exponential and logarithmic:
  //
  A1( exp )		// exponential, base e
  A1( log )		// natural (base e) logarithm of positive arg
  A1( log10 )		// base 10 logarithm of positive arg
  
  // -----  Power:
  //
  A1( sqrt )		// square root of non-negative arg
  A2( pow )		// arg1 to the arg2 power
  
  // -----  Nearest integer, absolute value, and remaindering:
  //
  A1( abs )		// absolute value
  A1( fabs )		// same as abs()
  A1( ceil )		// smallest integral value not less than arg
  A1( floor )		// largest integral value not greater than arg
  A2( fmod )		// remainder of arg1 / arg2, same sign as arg1
  
  
  #undef A2
  #undef A1
  
  
}  // namespace si
