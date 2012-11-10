#ifndef SI_H
#define SI_H


// ----------------------------------------------------------------------
//
// si.h -- prepare for measurements a la Systeme Internationale d'Unites
//         (the International System of Units, also known as SI)
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
//   21-Apr-1998  WEB  Initial draft
//   08-May-1998  WEB  Reorganized
//   29-Jul-1998  WEB  Improved internal documentation
//   25-Nov-1998  WEB  Made return types const where appropriate
//   28-Jan-1998  WEB  Cleaned up Dim<...0,0,0,0,0,0,0> specialization;
//     initAs() is now protected; removed unneeded friendships
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
  using  std::sqrt;


  // --------------------------------------------------------------------
  // Identify the number of SI base quantities (dimensions):
  // --------------------------------------------------------------------

  enum { nBaseDims = 7 + 1 };  // account for a unitless dimension


  // --------------------------------------------------------------------
  // Anticipate a function to initialize default display units:
  // --------------------------------------------------------------------

  bool prepareToDisplay();



  // --------------------------------------------------------------------
  // Define Val__<> class:
  // --------------------------------------------------------------------

  template< class T = double, OutLook O = standardModel >
  class Val__  {

  protected:

    // ---  Class characteristics:
    //
    typedef T  Rep;                   // our fundamental value type
    enum { Model = O };              // our underlying model

    // ---  Class-wide data:
    //
    static Rep          per_[nBaseDims];   // default scale factors
    static std::string  tag_[nBaseDims];   // default unit denotations

    // ---  Instance data:
    //
    Rep n_;                          // our value

  public:

    // ---  Default constructor:
    //
    inline
    Val__( Rep n = Rep(0) ) : n_( n )  { }

    // ---  Copy constructor:
    //
    template< class T2 >
    inline
    Val__( Val__<T2,O> const & v ) : n_( v.pure() )  { }

    // ---  Accessor:
    //
    inline
    Rep const  pure() const  { return  n_; }

    // ---  Set default scale:
    //
    static
    void setScale( int dim, Val__<T> unit, std::string const & tag )  {
      (tag_[dim] = " ") += tag;  per_[dim] = unit.pure();
    }
    static
    bool initScale( int dim, Val__<T> unit, std::string const & tag )  {
      if ( per_[dim] == Rep(0) )
        return  (tag_[dim] = " ") += tag,  per_[dim] = unit.pure(),  true;
      else
        return  false;
    }

    // ---  Displayable conversion operator:
    //
    std::string  emit(
      Rep  per
    , std::string  tag
    , int d1, int d2, int d3, int d4, int d5, int d6, int d7
    )  {
      prepareToDisplay();
      int pow[nBaseDims] = { 1, d1, d2, d3, d4, d5, d6, d7 };

      if ( per == Rep(0) )  {  // no explicit units specified; use defaults
	std::ostringstream suffix;
	suffix << tag_[0];
	per = per_[0];

	for ( int d = 1;  d < nBaseDims;  ++d )  {
	  if  ( pow[d] > 0 )  {
	    suffix << tag_[d];
	    if ( pow[d] != 1 )
	      suffix << '^' << pow[d];
	    do  per *= per_[d];  while ( --pow[d] > 0 );
	  }
	}  // for

	for ( int d = 1;  d < nBaseDims;  ++d )  {
	  if  ( pow[d] < 0 )  {
	    suffix << tag_[d] << '^' << pow[d];
	    do  per /= per_[d];  while ( ++pow[d] < 0 );
	  }
	}  // for

	tag = suffix.str();
      }  // if

      std::ostringstream res;
      res  <<  (n_ / per)  <<  tag;
      return  res.str();

    }  // emit()


  };  // class Val__<>


  // ---  Prevent Val__<pointer> instantiation:
  //
  template< class T, OutLook O >
  class Val__<T*,O>  {
  private:
    ~Val__<T*,O>();
  };


  // ---  Provide Val__<>'s default unit conversions:
  //
  template< class T, OutLook O >
  typename Val__<T,O>::Rep  Val__<T,O>::per_[nBaseDims] =  {
    Rep( 1.0 )   // dimPure
  , Rep( 0.0 )   // dimLength
  , Rep( 0.0 )   // dimMass
  , Rep( 0.0 )   // dimTime
  , Rep( 0.0 )   // dimCurrent
  , Rep( 0.0 )   // dimTemperature
  , Rep( 0.0 )   // dimMolarity
  , Rep( 0.0 )   // dimLuminosity
  };


  // ---  Provide Val__<>'s default unit labels:
  //
  template< class T, OutLook O >
  std::string  Val__<T,O>::tag_[nBaseDims] =  {
    ""              // dimPure
  , "?m"            // dimLength
  , "?kg"           // dimMass
  , "?s"            // dimTime
  , "?A"            // dimCurrent
  , "?K"            // dimTemperature
  , "?mol"          // dimMolarity
  , "?cd"           // dimLuminosity
  };



  // --------------------------------------------------------------------
  // Define local notational abbreviations:
  // --------------------------------------------------------------------

  #define si7def(x)	\
    int x##1=0, int x##2=0, int x##3=0,	\
    int x##4=0, int x##5=0, int x##6=0, int x##7=0

  #define si7(x)	\
    x##1, x##2, x##3, x##4, x##5, x##6, x##7

  #define si7op(x, op, y)	\
    x##1##op##y##1, x##2##op##y##2, x##3##op##y##3, 	\
    x##4##op##y##4, x##5##op##y##5, x##6##op##y##6, x##7##op##y##7

  #define si7opL(x, op, y)	\
    x##1##op##y, x##2##op##y, x##3##op##y, 	\
    x##4##op##y, x##5##op##y, x##6##op##y, x##7##op##y

  #define sidiv(x,n) (x+(x>=0?n-1:1-n))/n

  #define si7frac(x,n)	\
    sidiv(x##1,n), sidiv(x##2,n), sidiv(x##3,n),	\
    sidiv(x##4,n), sidiv(x##5,n), sidiv(x##6,n), sidiv(x##7,n)



  // --------------------------------------------------------------------
  // Define Dim< T, O, p1,p2,p3,p4,p5,p6,p7 >:
  // --------------------------------------------------------------------

  template< class T = double, OutLook O = standardModel, si7def(p) >
  class Dim : public Val__<T,O>  {

  protected:

    // ---  Class characteristics:
    //
    enum { Model = Val__<T,O>::Model };
    typedef typename Val__<T,O>::Rep  Rep;
    typedef wv<O,Rep>                 WV;
    typedef Dim<T,O,si7(p)>           MyType;

    enum { d1 = p1, d2 = p2, d3 = p3, d4 = p4, d5 = p5, d6 = p6, d7 = p7 };

    // ---  Class-wide data:
    //
    static Rep          per_;         // default scale factor
    static std::string  tag_;         // default denotation

    // ----- Assign initial symbol for display:
    //
    static inline
    bool  initAs( MyType const newUnit, std::string const & tag )  {
      if ( per_ == Rep(0) )
        return  per_ = newUnit.n_,  (tag_ = " ") += tag,  true;
      else
        return  false;
    }
    friend bool prepareToDisplay();

  public:

    // ---  Help debug the template:
    static
    void ident( int p[8] )  {
      p[1] = d1, p[2] = d2, p[3] = d3,
      p[4] = d4, p[5] = d5, p[6] = d6, p[7] = d7;
    }

    // ---  Default constructor:
    //
    inline
    explicit Dim( Rep n = Rep(0) ) : Val__<T,O>( n )  {}

    // ---  Copy constructor:
    //
    template< class T2 >
    inline
    Dim( Dim<T2,O,si7(p)> const & orig ) : Val__<T,O>( orig.pure() )  {}

    // ---  Assignment:
    //
    inline
    MyType &  operator=( MyType const & rhs )  {
      n_ = rhs.n_;
      return  *this;
    }

    // ----- Assign new symbol for display:
    //
    static inline
    void  showAs()  {
      prepareToDisplay();
      per_ = Rep(0),  tag_ = " ???";
    }
    static inline
    void  showAs( MyType const newUnit, std::string const & tag )  {
      prepareToDisplay();
      per_ = newUnit.n_,  (tag_ = " ") += tag;
    }

    // ----- Explicit conversion:
    //
    inline
    Rep const  measuredIn( MyType desiredUnit ) const  {
      return  n_ / desiredUnit.n_;
    }

    // ----- Output operator:
    //
    friend
    inline std::ostream &  operator<<( std::ostream & os, MyType self )  {
      return  os << self.emit( MyType::per_, MyType::tag_, si7(self.d) ) ;
    }

    // ----- Relational operators:
    //
    inline bool operator== ( MyType rhs) const  { return  ( n_ == rhs.n_ ); }
    inline bool operator!= ( MyType rhs) const  { return  ( n_ != rhs.n_ ); }
    inline bool operator<  ( MyType rhs) const  { return  ( n_ <  rhs.n_ ); }
    inline bool operator<= ( MyType rhs) const  { return  ( n_ <= rhs.n_ ); }
    inline bool operator>  ( MyType rhs) const  { return  ( n_ >  rhs.n_ ); }
    inline bool operator>= ( MyType rhs) const  { return  ( n_ >= rhs.n_ ); }

    // ---  Unary + and - operators:
    //
    inline
    MyType const  operator+() const  { return  MyType( + n_ ); }
    inline
    MyType const  operator-() const  { return  MyType( - n_ ); }

    // ---  Binary += and -= operators:
    //
    inline MyType &  operator+=( MyType rhs )  { n_ += rhs.n_;  return  *this; }
    inline MyType &  operator-=( MyType rhs )  { n_ -= rhs.n_;  return  *this; }

    // ---  Binary + and - operators:
    //
    inline
    MyType const  operator+ ( MyType rhs ) const  {
      return  MyType( n_ + rhs.n_ );
    }
    inline
    MyType const  operator- ( MyType rhs ) const  {
      return  MyType( n_ - rhs.n_ );
    }

    // ---  Scalar *= and /= operators:
    //
    inline MyType &  operator*= ( Rep  rhs )  { n_ *= rhs;  return  *this; }
    inline MyType &  operator/= ( Rep  rhs )  { n_ /= rhs;  return  *this; }

    // ---  (Right-hand) scalar * and / operators:
    //
    inline
    MyType const  operator* ( Rep rhs ) const  { return MyType( n_ * rhs ); }
    inline
    MyType const  operator/ ( Rep rhs ) const  { return MyType( n_ / rhs ); }

    // ---  (Left-hand) scalar * and / operators:
    //
    inline friend
    MyType const  operator*( Rep lhs, MyType rhs)  {
      return  MyType( lhs * rhs.n_ );
    }
    inline friend
    Dim<Rep,O,si7(-p)> const  operator/( Rep lhs, MyType rhs)  {
      return  Dim<Rep,O,si7(-p)>( lhs / rhs.n_ );
    }

    // ---  (Mixed-type) arithmetic operations:
    //
    template< class T2, si7(int q) >
    inline
    Dim<Rep,O,si7op(p,+,q)> const  operator* ( Dim<T2,O,si7(q)> rhs) const  {
      return  Dim<Rep,O,si7op(p,+,q)>( Rep(n_ * rhs.pure()) );
    }
    template< class T2, si7(int q) >
    inline
    Dim<Rep,O,si7op(p,-,q)> const  operator/ ( Dim<T2,O,si7(q)> rhs) const  {
      return  Dim<Rep,O,si7op(p,-,q)>( Rep(n_ / rhs.pure()) );
    }

  };  // Dim<>



  // --------------------------------------------------------------------
  // Define data templates for Dim< T,O, p1,p2,p3,p4,p5,p6,p7 >:
  // --------------------------------------------------------------------

  template< class T, OutLook O, si7(int p) >
  typename Dim<T,O,si7(p)>::Rep  Dim<T,O,si7(p)>::per_ = Rep(0);

  template< class T, OutLook O, si7(int p) >
  std::string                    Dim<T,O,si7(p)>::tag_ = "???";



  // --------------------------------------------------------------------
  // Define templates for square and square root of any Dim<...>:
  // --------------------------------------------------------------------

  // ---  Square:
  //
  template< class T, OutLook O, si7(int q) >
  inline
  Dim<T,O,si7(2*q)> const  sqr( Dim<T,O,si7(q)> self )  {
    return  Dim<T,O,si7(2*q)>( self.pure() * self.pure() );
  }

  // ---  Square root:
  //
  template< class T, OutLook O, si7(int q) >
  inline
  Dim<T,O,si7frac(q,2)> const  sqrt( Dim<T,O,si7(q)> self )  {
    return  Dim<T,O,si7opL(q,/,2)>( std::sqrt(self.pure()) );
  }



  // --------------------------------------------------------------------
  // Define friend struct Nth of Dim< T,O, p1,p2,p3,p4,p5,p6,p7 >:
  // --------------------------------------------------------------------

  template< unsigned short N >
  struct Nth  {

    // ---  Nth power
    //
    template< class T, OutLook O, si7(int q) >
    static inline
    Dim<T,O,si7(N*q)> const  pow ( Dim<T,O,si7(q)> self )  {
      return  Dim<T,O,si7(N*q)>( std::pow( self.pure(), N ) );
    }

    // ---  Nth root
    //
    template< class T, OutLook O, si7(int q) >
    static inline
    Dim<T,O,si7frac(q,N)> const  root( Dim<T,O,si7(q)> self )  {
      return  Dim<T,O,si7opL(q,/,N)>( std::pow( self.pure(), T(1) / T(N) ) );
    }

  };  // Nth



  // --------------------------------------------------------------------
  // Define Dim< T, O, 0,0,0,0,0,0,0 > specialization:
  // --------------------------------------------------------------------

  template< class T, OutLook O >
  class Dim<T, O, 0,0,0,0,0,0,0> : public Val__<T,O>  {

  protected:

    // ---  Class characteristics:
    //
    typedef typename Val__<T,O>::Rep  Rep;
    typedef wv<O,Rep>                 WV;
    typedef Dim<T,O,0,0,0,0,0,0,0>    MyType;

    enum { d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, d7 = 0 };

    // ---  Class-wide data:
    //
    static Rep          per_;         // default scale factor
    static std::string  tag_;         // default denotation

    // ----- Assign initial symbol for display:
    //
    static inline
    bool  initAs( MyType const newUnit, std::string const & tag )  {
      if ( per_ == Rep(0) )
        return  per_ = newUnit.n_,  (tag_ = " ") += tag,  true;
      else
        return  false;
    }
    friend bool prepareToDisplay();

  public:

    // ---  Help debug the template:
    static void ident( int p[8] )  {
      p[1] = d1, p[2] = d2, p[3] = d3,
      p[4] = d4, p[5] = d5, p[6] = d6, p[7] = d7;
    }

    // ---  Default constructor, also used as conversion constructor:
    //
    inline Dim( Rep n = Rep(0) ) : Val__<T,O>( n )  {}

    // ---  Copy constructor:
    //
    template< class T2 >
    inline
    Dim( Dim<T2,O,0,0,0,0,0,0,0> const & orig ) : Val__<T,O>( orig.pure() )  {}

    // ---  Conversion operator:
    //
    inline operator Rep() const  { return  n_; }

    // ----- Assign new symbol for display:
    //
    static inline
    void  showAs()  {
      prepareToDisplay();
      per_ = Rep(0),  tag_ = " ???";
    }
    static inline
    void  showAs( MyType const newUnit, std::string const & tag )  {
      prepareToDisplay();
      per_ = newUnit.n_,  (tag_ = " ") += tag;
    }

    // ----- Explicit conversion:
    //
    inline
    Rep const  measuredIn( MyType desiredUnit ) const  {
      return  n_ / desiredUnit.n_;
    }

    // ----- Output operator:
    //
    friend inline
    std::ostream &  operator<<( std::ostream & os, MyType self )  {
      return  os << self.emit( MyType::per_, MyType::tag_, si7(self.d) ) ;
    }

    // ---  Binary += and -= operators:
    //
    inline MyType &  operator+=( MyType rhs )  { n_ += rhs.n_;  return  *this; }
    inline MyType &  operator-=( MyType rhs )  { n_ -= rhs.n_;  return  *this; }

    // ---  Scalar *= and /= operators:
    //
    inline MyType &  operator*= ( Rep rhs )  { n_ *= rhs;  return  *this; }
    inline MyType &  operator/= ( Rep rhs )  { n_ /= rhs;  return  *this; }

  };  // Dim<T, O, 0,0,0,0,0,0,0>



  // --------------------------------------------------------------------
  // Define data templates for Dim< T,O, 0,0,0,0,0,0,0 >:
  // --------------------------------------------------------------------

  template< class T, OutLook O >
  typename Dim<T,O,0,0,0,0,0,0,0>::Rep  Dim<T,O,0,0,0,0,0,0,0>::per_ = Rep(0);

  template< class T, OutLook O >
  std::string                           Dim<T,O,0,0,0,0,0,0,0>::tag_ = "???";



  // --------------------------------------------------------------------
  // Undefine local notational abbreviations:
  // --------------------------------------------------------------------

  #undef si7def
  #undef si7
  #undef si7op
  #undef si7opL
  #undef sidiv
  #undef si7frac


}  // namespace si



#endif  // SI_H
