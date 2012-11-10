#ifndef QTMMODEL_H
#define QTMMODEL_H


// ----------------------------------------------------------------------
//
// qtmModel.h -- set up so as to unify Length, Time, Mass, Temp, & Current
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
//   09-May-1998  WEB  Initial draft, based on prior experiments
//   17-Aug-1998  WEB  Factored out code common to all models
//   24-Aug-1998  WEB  Factored out more by introducing ourModel
//
// ----------------------------------------------------------------------


#ifndef SIMODEL_H
  #define SIMODEL_H
#else
  #error "Attempted to #include multiple model headers."
#endif


#include "si.h"


namespace si  {


  // -----  Decide underlying type and model:
  //
  typedef double  RepType;
  enum { ourModel = quantumModel };


  // -----  Provide the standard dimensions, units, and constants:
  //
  #include "allModel_h"


  // -----  Specialize showAs<>() for base dimensions:
  //
  template<>
  inline void Frequency::showAs( Frequency newUnit, std::string const & tag )  {
    prepareToDisplay();
    Frequency::setScale( WV::dimLength, newUnit.n_, tag );
  }
  template<>
  inline void Molarity::showAs( Molarity newUnit, std::string const & tag )  {
    prepareToDisplay();
    Molarity::setScale( WV::dimSubst, newUnit.n_, tag );
  }
  template<>
  inline void Luminosity::showAs( Luminosity newUnit, std::string const & tag )  {
    prepareToDisplay();
    Luminosity::setScale( WV::dimLI, newUnit.n_, tag );
  }


  // -----  Specialize initAs<>() for base dimensions:
  //
  template<>
  inline bool Frequency::initAs( Frequency const newUnit, std::string const & tag )  {
    return  Frequency::initScale( WV::dimLength, newUnit.n_, tag );
  }
  template<>
  inline bool Molarity::initAs( Molarity const newUnit, std::string const & tag )  {
    return  AmountOfSubstance::initScale( WV::dimSubst, newUnit.n_, tag );
  }
  template<>
  inline bool Luminosity::initAs( Luminosity const newUnit, std::string const & tag )  {
    return  Luminosity::initScale( WV::dimLI, newUnit.n_, tag );
  }


  // -----  Ensure linkage to correct library:
  //
  extern bool const  qtmModelIsHere;
  bool const  qtmModelNeeded( qtmModelIsHere );


}  // namespace si


#endif  // QTMMODEL_H
