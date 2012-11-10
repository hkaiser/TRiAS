// ----------------------------------------------------------------------
//
// qtmModel.cc -- provide constants of nature and system of units
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
//   17-Apr-1998  WEB  Initial draft
//   17-Aug-1998  WEB  Factored out code common to all models
//   28-Jan-1999  WEB  Reduced default display units to GeV, mol, cd
//
// ----------------------------------------------------------------------


#include "qtmModel.h"


// -----  Ensure linkage to correct library:
//
bool const  si::qtmModelIsHere( true );


// -----  Unit measurements:
//
#include "allModel_cc"


// -----  Install the default display notation for the 7 base and 21 SI
// -----  derived dimensions and units that have special names and symbols:
//
bool si::prepareToDisplay()  {

  using namespace abbreviations;

  static bool didInit = false;
  if ( didInit )  return  didInit;
  didInit = true;

  #define init(dim,unit)                                        \
    if ( unit.pure() == 0 )                                     \
      std::cerr << "Unit " #unit " is not yet initialized!\n",  \
      didInit = false;						\
    if ( ! dim::initAs( unit, #unit ) )                         \
      std::cerr << "Can't init " #dim " with " #unit "!\n",     \
      didInit = false;						\

  // -----  Not needed; implicit
  //init(Number,           , Number(1) );  // also rad, sr, Gy, Sv, S, Wb, ohm

  init(Frequency           , GeV );  // also m, kg, s, A, J, K, F, V, Hz, Bq, H
  init(AmountOfSubstance   , mol );
  init(LuminousIntensity   , cd  );  // also lm

  //init(Force               , N   );  // also W, T
  //  presence of Newtons will confuse someone outputting Watts, etc.
  //init(Illuminance         , lx  );
  //init(Pressure            , Pa  );
  //  in this model, we really don't want anything but GeV's

  return  didInit;

}  // si::prepareToDisplay()
