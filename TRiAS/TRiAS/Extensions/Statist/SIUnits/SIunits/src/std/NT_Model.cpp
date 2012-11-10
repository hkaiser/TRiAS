// ----------------------------------------------------------------------
//
// NT_stdModel.cc -- provide constants of nature and system of units
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
//   21-Jan-1999  MF   Initial version 
//   03-Feb-1999  MF   Proper linkage insurance
//
// ----------------------------------------------------------------------

#include <SIUnits/stdModel.h>

// -----  Ensure linkage to correct library:
//
namespace si {
const bool stdModelIsHere( true );
}

// -----  Unit measurements:
//
#include <SIUnits/allModel_cc>




