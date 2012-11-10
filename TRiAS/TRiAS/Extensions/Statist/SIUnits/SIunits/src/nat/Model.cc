// ----------------------------------------------------------------------
//
// natModel.cc -- provide constants of nature and system of units
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
//
// ----------------------------------------------------------------------


#include "natModel.h"


// -----  Ensure linkage to correct library:
//
bool const  si::natModelIsHere( true );


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
  //init(Number,           , Number(1) );  // also rad, sr, Gy & Sv
  //  as well as m, kg, s, J, K, C, Hz, Bq, F, S, V, N, lx, ohm, H, W, Wb, T, Pa

  init(AmountOfSubstance   , mol );
  init(LuminousIntensity   , cd  );  // also lm

  return  didInit;

}  // si::prepareToDisplay()
