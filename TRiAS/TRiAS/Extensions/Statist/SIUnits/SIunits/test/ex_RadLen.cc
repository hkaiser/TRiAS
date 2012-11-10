// ----------------------------------------------------------------------
//
// ex_RadLen - Compute energy loss due to bremsstrahlung for an electron
//             traversing a thickness of a given material.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//                                                                     \\
// NOTICE:                                                             \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//                                                                     \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// Reference:
//   See section 23.4 of Review of Particle Physics.  We ignore f(Z).
//
// ----------------------------------------------------------------------


#include "stdModel.h"
  using namespace si;
  using namespace si::abbreviations;
  using namespace si::elements;

#include <iostream>


Energy finalEnergy(
  Element const &  element
, Density const    density
, Length  const    thickness
, Energy  const    initialEnergy
)  {

  // Obtain the pertinent information about the given substance:
  //
  AtomicWeight const  A = element.atomicweight;
  AtomicNumber const  Z = element.atomicnumber;

  // Calculate Tsai's constants:
  //
  Number const  L_rad  = log( 184.15 / pow(Z, 1./3) );
  Number const  Lp_rad = log( 1194.  / pow(Z, 2./3) );

#if defined ERRONEOUS

  // Calculate the "radiation length":
  //
  Length const  X_0
	// Error 1:
	// The nomenclature is misleading -- it's not a length at all!
	// A radiation length is a distance that has been adjusted
	// for the density of the material; it is a Length * Density
	// = Length * Mass per Volume = Mass per Area = AreaDensity
	// that gives an effective thickness.

    = ( 4 * alpha * r_e * r_e )
    * ( N_A / A )
    * ( Z * Z * L_rad  +  Z * Lp_rad );
	// Error 2:
	// Now a transcription error is exposed;
	// while the formula is correct, it produces 1 / X_0.

  // Determine the remaining energy:
  //
  return  initialEnergy
	* exp( - thickness / X_0 );
	// Error 3:
	// Finally, we have a physics error, resulting from
	// the conceptual error suggested by the nomenclature!
	// We do use the thickness, but it must be adjusted for density.

#else  // ! defined ERRONEOUS

  // Calculate the "radiation length":
  //
  AreaDensity const  X_0 = 1 / ( ( 4 * alpha * r_e * r_e )
	                      * ( N_A / A )
	                      * ( Z * Z * L_rad + Z * Lp_rad)
	                      );

  // Determine the remaining energy:
  //
  return  initialEnergy
	* exp( - thickness * density / X_0 );
 
#endif  // ERRONEOUS

}  // finalEnergy()



int main() {

  Density    d   = 0.534 * g/cc;
  Thickness  t   = 25    * cm  ;
  Energy     e_0 = 100   * MeV ;

  Energy     e_f = finalEnergy( lithium, d, t, e_0 );

  Density  ::showAs( g/cc, "g/cc" );
  Thickness::showAs( cm  , "cm"   );
  Energy   ::showAs( MeV , "MeV"  );

  std::cout << "Lithium:\n"
            << "  density      = " << d   << '\n'
	    << "  thickness    = " << t   << '\n'
	    << "  init energy  = " << e_0 << '\n'
	    << "  final energy = " << e_f << '\n'
	    ;

  return  0;
  
}  // main()
