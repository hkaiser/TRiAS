#ifndef RELMODEL_H
#define RELMODEL_H


// ----------------------------------------------------------------------
//
// relModel.h -- set up so as to Length identical to Time
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
  enum { ourModel = relativityModel };


  // -----  Provide the standard dimensions, units, and constants:
  //
  #include "allModel_h"


  // -----  Specialize showAs<>() for base dimensions:
  //
  template<>
  inline void Length::showAs( Length newUnit, std::string const & tag )  {
    prepareToDisplay();
    Length::setScale( WV::dimLength, newUnit.n_, tag );
  }
  template<>
  inline void Mass::showAs( Mass newUnit, std::string const & tag )  {
    prepareToDisplay();
    Mass::setScale( WV::dimMass, newUnit.n_, tag );
  }
  template<>
  inline void Current::showAs( Current newUnit, std::string const & tag )  {
    prepareToDisplay();
    Current::setScale( WV::dimCurrent, newUnit.n_, tag );
  }
  template<>
  inline void Temperature::showAs( Temperature newUnit, std::string const & tag )  {
    prepareToDisplay();
    Temperature::setScale( WV::dimTemp, newUnit.n_, tag );
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
  inline bool Length::initAs( Length const newUnit, std::string const & tag )  {
    return  Length::initScale( WV::dimLength, newUnit.n_, tag );
  }
  template<>
  inline bool Mass::initAs( Mass const newUnit, std::string const & tag )  {
    return  Mass::initScale( WV::dimMass, newUnit.n_, tag );
  }
  template<>
  inline bool Current::initAs( Current const newUnit, std::string const & tag )  {
    return  Current::initScale( WV::dimCurrent, newUnit.n_, tag );
  }
  template<>
  inline bool Temperature::initAs( Temperature const newUnit, std::string const & tag )  {
    return  Temperature::initScale( WV::dimTemp, newUnit.n_, tag );
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
  extern bool const  relModelIsHere;
  bool const  relModelNeeded( relModelIsHere );


}  // namespace si


#endif  // RELMODEL_H

