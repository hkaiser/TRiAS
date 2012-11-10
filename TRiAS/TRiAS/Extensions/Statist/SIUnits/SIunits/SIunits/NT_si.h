#ifndef SI_H
#define SI_H


// ----------------------------------------------------------------------
//
// NT_si.h -- prepare for measurements a la Systeme Internationale d'Unites
//            (the International System of Units, also known as SI)
//
// NT Version:	No Complicated Templates
//				We still use templates to express 
//					Nth<n>root(d) and Nth<n>pow(d)
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//                                                                     \\
// NOTICE:                                                             \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//                                                                     \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// "In carrying out any calculation, always remember to attach the proper
// units to the final result, for the result is meaningless without this
// label. . . .  One way to spot an erroneous equation is to check the
// dimensions of all its terms. . . .  In any legitimate physical
// equation the dimensions of all the terms must be the same. . . .  You
// should check the dimensions of all the equations you use."
//				- Halliday & Resnick, 1970, pp. 35-6
//
// History:
//   19-Jan-1999  MF   Initial version from si.h, making extensive changes 
//			to bring VAL__ and Dim into one DimensionedQuantity
//			class.
//
//   22-Jan-1999  MF   Inserted ::sqrt in the definition of sqrt so as to
//			remove the infinite descent when sqrt is done.
//
//   25-Jan-1999  MF   Inserted dummy showAs() method to provide code
//			compatability.
//
//   26-Jan-1999  MF   Added operator=(Rep) to avoid awkwardness when
//			doing things like Length len = 2.
//
//   29-Jan-1999  MF   Replaced Number (which is also in dims) with Rep			     
//
// ----------------------------------------------------------------------

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

// ----------------------------------------------------------------------
// Prepare the si namespace:
// ----------------------------------------------------------------------


namespace si  {

  #include "wv.h"


  // --------------------------------------------------------------------
  // Define DimensionedQuantity class:
  // --------------------------------------------------------------------

  class DimensionedQuantity   {

  protected:

    // -----  Class characteristics:
    //
    typedef RepType Rep;                // our fundamental value type
    typedef DimensionedQuantity MyType; // corresponding to same type

    // -----  Instance data:
    //
    Rep n_;                       // our value

  public:

    // -----  Help debug template (Not pertainent in NT)
	static void ident( int p[8]) { p[1]=p[2]=p[3]=p[4]=p[5]=p[6]=p[7]=0; }

    // -----  Default constructor:
    //
    inline DimensionedQuantity( Rep n = Rep(0) ) : n_( n )  { }

    // -----  Copy constructor:
    //
    inline DimensionedQuantity( const DimensionedQuantity & v ) : 
			n_( v.pure() )  { }

    // -----  Conversion operator
	inline operator Rep() const { return n_; }

    // -----  Accessor:
    //
    inline Rep pure() const  { return  n_; }

#ifdef REMOVE
    // -----  Assignment:
    //
    inline MyType &  operator=( const MyType & rhs )  {
      n_ = rhs.n_;
      return  *this;
    }    
	
    inline MyType &  operator=( const Rep & rhs )  {
      n_ = rhs;
      return  *this;
    }
#endif

    // ----- Explicit conversion:
    //
    inline Rep  measuredIn( MyType desiredUnit ) const  {
      return  n_ / desiredUnit.n_;
    }

    // ----- Output operator:
    //
    friend inline std::ostream &  operator<<( std::ostream & os, MyType self )  {
      return  os << self.n_ << " ";
    }

    static inline void showAs(const MyType newUnit, const std::string & tag){}

    // -----  Binary += and -= operators:
    //
    inline MyType &  operator+=( MyType rhs )  { n_ += rhs.n_;  return  *this; }
    inline MyType &  operator-=( MyType rhs )  { n_ -= rhs.n_;  return  *this; }

    // -----  Scalar *= and /= operators:
    //
    inline MyType &  operator*= ( Rep rhs )  { n_ *= rhs;  return  *this; }
    inline MyType &  operator/= ( Rep rhs )  { n_ /= rhs;  return  *this; }

#ifdef REMOVE
    // ----- Relational operators:
    //
    inline bool operator== ( MyType rhs) const  { return  ( n_ == rhs.n_ ); }
    inline bool operator!= ( MyType rhs) const  { return  ( n_ != rhs.n_ ); }
    inline bool operator<  ( MyType rhs) const  { return  ( n_ <  rhs.n_ ); }
    inline bool operator<= ( MyType rhs) const  { return  ( n_ <= rhs.n_ ); }
    inline bool operator>  ( MyType rhs) const  { return  ( n_ >  rhs.n_ ); }
    inline bool operator>= ( MyType rhs) const  { return  ( n_ >= rhs.n_ ); }

    // -----  Unary + and - operators:
    //
    inline MyType  operator+() const  { return  MyType( + n_ ); }
    inline MyType  operator-() const  { return  MyType( - n_ ); }

    // -----  Binary + and - operators:
    //
    inline MyType  operator+ ( MyType rhs ) const  {
      return  MyType( n_ + rhs.n_ );
    }
    inline MyType  operator- ( MyType rhs ) const  {
      return  MyType( n_ - rhs.n_ );
    }

    // -----  (Right-hand) scalar * and / operators:
    //
    inline MyType operator* ( Rep rhs ) const  { return MyType( n_ * rhs ); }
    inline MyType operator/ ( Rep rhs ) const  { return MyType( n_ / rhs ); }

    // -----  (Left-hand) scalar * and / operators:
    //
    inline friend MyType  operator*( Rep lhs, MyType rhs)  {
      return  MyType( lhs * rhs.n_ );
    }
    inline friend MyType  operator/( Rep lhs, MyType rhs)  {
      return  ( lhs / rhs.n_ );
    }

    // -----  (Mixed-type) arithmetic operations:
    //
    
    inline MyType  operator* ( MyType rhs) const  {
      return  MyType ( Rep(n_ * rhs.pure()) );
    }
    inline MyType  operator/ ( MyType rhs) const  {
      return  MyType ( Rep(n_ / rhs.pure()) );
    }
#endif

#ifdef REMOVE_MAYBE
    // -----  Square:
    //    
    inline friend MyType  sqr( MyType self );

    // -----  Square root:
    //
    inline friend MyType  sqrt( MyType self );
#endif

#ifdef REMOVE_MAYBE
    // -----  Allow Nth roots and powers:
    //
    template < unsigned short int N >  maybe friend struct Nth;
#endif

  };  // class DimensionedQuantity


  // --------------------------------------------------------------------
  // Define (non)friend (non)templates for DimensionedQuantity
  // --------------------------------------------------------------------

  // -----  Square:
  //
  
  inline DimensionedQuantity sqr( DimensionedQuantity self )  {
    return DimensionedQuantity ( self.pure() * self.pure() );
  }

  // -----  Square root:
  //
  inline DimensionedQuantity sqrt( DimensionedQuantity self )  {
    return DimensionedQuantity ( ::sqrt(self.pure()) );
  }
 

  // --------------------------------------------------------------------
  // Define (non)friend struct Nth of DimensionedQuantity
  // --------------------------------------------------------------------

  template< unsigned short N >
  struct Nth  {

    // -----  Nth power
    //
    static inline DimensionedQuantity pow ( DimensionedQuantity self )  {
      return  DimensionedQuantity ( ::pow( self.pure(), N ) );
    }

    // -----  Nth root
    //
    static inline DimensionedQuantity root( DimensionedQuantity self )  {
      return  DimensionedQuantity 
			( ::pow( self.pure(), RepType(1.0)/RepType(N) ) );
    }

  };  // Nth

}  // namespace si



#endif  // SI_H
