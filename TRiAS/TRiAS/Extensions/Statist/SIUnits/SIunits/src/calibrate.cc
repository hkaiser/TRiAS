// ----------------------------------------------------------------------
//
// calibrate.cc - produce calibration for non-standard world views
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
//   31-Jul-1998  WEB  Initial draft
//   09-Feb-1999  WEB  Provide originating machine name along with the
//     timestamp; use o
//
// ----------------------------------------------------------------------



#include "stdModel.h"
using namespace si;
using namespace si::abbreviations;

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::left;
using std::setprecision;

#include <cmath>
using std::sqrt;

#include <time.h>
using std::time;
using std::ctime;

#include <sys/utsname.h>


double def_m, def_kg, def_s, def_A, def_K, def_mol, def_cd;
char * unit_m	= 0
,    * unit_kg	= 0
,    * unit_s	= 0
,    * unit_A	= 0
,    * unit_K	= 0
,    * unit_mol	= 0
,    * unit_cd	= 0
;


void emit1( char * name, double val, char * units )  {

  cout << "  static double const "
       << setw(7) << name
       << " = "
       << left << setw(23) << val
       << ";  // "
       << units
       << endl;

}  // emit1()


void emit( char namesp[] )  {

  cout << setprecision(18);

  cout << ""							<< endl;
  cout << "// ----------  " << namesp << ":"			<< endl;
  cout << "//"							<< endl;
  cout << "namespace " << namesp << "  {"			<< endl;
  emit1( "def_m"  , def_m  , unit_m   );
  emit1( "def_kg" , def_kg , unit_kg  );
  emit1( "def_s"  , def_s  , unit_s   );
  emit1( "def_A"  , def_A  , unit_A   );
  emit1( "def_K"  , def_K  , unit_K   );
  emit1( "def_mol", def_mol, unit_mol );
  emit1( "def_cd" , def_cd , unit_cd  );
  cout << "}  // " << namesp					<< endl;
  cout << ""							<< endl;

}  // emit()


void rel()  {

  // We will keep seconds as our fundamental time unit:
  //
  unit_s = "sec";
  def_s  = 1.0;

  // We desire to set lightspeed to 1.
  //   Thus c m/s = 1, so m = def_s / c:
  //
  unit_m = "light-sec";
  def_m  = 1.0 / c.measuredIn(m/s);

  // We now desire to express Mass in electronVolts(per c2).
  //   Since an electronVolt is some number, eV, of joules,
  //   and since 1 J = m2 kg / s2, we have kg = s2 / eV m2:
  //
  unit_kg = "eV";
  def_kg  = c2.measuredIn(m2/s2) * J.measuredIn(eV);

  // Remaining units will default to 1:
  unit_A   = "A";    def_A   = 1.0;
  unit_K   = "K";    def_K   = 1.0;
  unit_mol = "mol";  def_mol = 1.0;
  unit_cd  = "cd";   def_cd  = 1.0;

  // It's showtime:
  emit( "relModel" );

}  // rel()


void hep()  {

  // We will make nanoseconds our fundamental time unit:
  //
  unit_s = "ns";
  def_s  = s.measuredIn(ns);

  // We desire to set lightspeed to 1.
  //   Thus c m/s = 1, so m = def_s / c:
  //
  unit_m = "light-ns";
  def_m  = 1.0 / c.measuredIn(m/ns);

  // We now desire to express Mass in gigaelectronVolts(per c2).
  //   Since a gigaelectronVolt is some number, GeV, of joules,
  //   and since 1 J = m2 kg / s2, we have kg = s2 / GeV m2:
  //
  unit_kg = "GeV";
  //def_kg  = ( (def_s * def_s) / (GeV * def_m * def_m) ).pure();
  def_kg  = c2.measuredIn(m2/s2) * J.measuredIn(GeV);

  // We now desire to set Boltzmann's constant to 1.
  //   Since Boltzmann's constant is some number, k, of eV per Kelvin,
  //   we have k K = 1.
  //   To convert to GeV, we divide by 10e9 (= giga_), or multiply by nano_
  //
  unit_K = "GeV";
  def_K  = k.measuredIn(GeV/K);

  // Finally, we desire to set the positron charge to 1.
  // This will express Current in charge per Time.
  //   Since the positron charge is some number, ePlus, of coulombs,
  //   we have ePlus A s = 1, so A = 1 / ePlus def_s.
  //
  unit_A = "(ePlus/ns)";
  //def_A  = 1.0 / ( ePlus * def_s ).pure();
  def_A  = ns.measuredIn(s) * C.measuredIn(ePlus);

  // Remaining units will default to 1:
  unit_mol = "mol";  def_mol = 1.0;
  unit_cd  = "cd";   def_cd  = 1.0;

  // It's showtime:
  emit( "hepModel" );

}  // hep()


void qtm()  {

  // We will set Planck's constant (reduced) to 1.
  //   hBar[GeV s] GeV s = 1,
  //   so s = 1/hBar[GeV s]   GeV-1
  //
  unit_s = "(hBar/GeV)";
  def_s  = 1.0 / hBar.measuredIn(GeV*s);

  // We desire to set lightspeed to 1.
  //   c[m/s] m/s = 1
  //   so m = s/c[m/s]
  //   substituting s = 1/hBar[GeV s]  GeV-1 from above, we have
  //   m = 1/hBar[GeV s]  *  1/c[m/s]  GeV-1
  //
  unit_m = "(1/GeV)";
  def_m  = 1.0 / ( hBar.measuredIn(GeV*s) * c.measuredIn(m/s) );

  // We now desire to express Mass in gigaelectronVolts(per c2).
  //   from J = m2 kg / s2, we have
  //   J[GeV] = kg m2 / s2  GeV, or kg = J[GeV] s2 / m2  GeV
  //   substituting for s and m above, we get
  //   kg = J[GeV] 1/hBar[GeV s]^2   GeV-2         GeV
  //      / (1/hBar[GeV s] * 1/c[m/s])^2  GeV-2
  //   Cancelling gives  kg = J[GeV] / 1/c[m/s]^2   GeV
  //   or  kg = J[GeV] * c[m/s]^2    GeV
  //
  unit_kg = "GeV";
  def_kg  = c2.measuredIn(m2/s2) * J.measuredIn(GeV);

  // We now desire to set Boltzmann's constant to 1.
  //   So k[GeV/K] GeV / K = 1
  //   giving  K = k[GeV/K]   GeV
  //
  unit_K = "GeV";
  def_K  = k.measuredIn(GeV/K);

  // Now, we want mu_0 = 1.
  //   m0[N/A^2] N / A^2 = 1, or A^2 = m0[N/A^2] N
  //   Substituting def'n of N, we get
  //   A^2 = m0[N/A^2] kg m / s^2
  //   and substituting above def'ns of kg and m, we have
  //   A^2 = m0[N/A^2] J[GeV] * c[m/s]^2 GeV
  //       * 1/hBar[GeV s] * 1/c[m/s] GeV-1 / s^2
  //   Cancelling, we obtain
  //   A^2 = m0[N/A^2] J[GeV] c[m/s] / hBar[GeV s] s^2
  //   and substituting for s gives
  //   A^2 = m0[N/A^2] J[GeV] c[m/s] / hBar[GeV s] 1/hBar[GeV s]^2   GeV-2
  //   Simplifying gives
  //   A^2 = m0[N/A^2] J[GeV] c[m/s] hBar[GeV s]   GeV^2
  //
  unit_A = "GeV";
  def_A  = sqrt( mu_0.measuredIn(N/(A*A))
               * c.measuredIn(m/s)
               * hBar.measuredIn(GeV*s)
               * J.measuredIn(GeV)
               );

  // Remaining units will default to 1:
  unit_mol = "mol";  def_mol = 1.0;
  unit_cd  = "cd";   def_cd  = 1.0;

  // It's showtime:
  emit( "qtmModel" );

}  // qtm()


void nat()  {

  //
  unit_s = "Planck length/c";
  def_s  = c2.measuredIn(m2/s2)
         * sqrt( c.measuredIn(m/s)
               / ( hBar.measuredIn(J*s) * G_N.measuredIn(m3/(kg * s2))
                 )
               )
         ;

  //
  unit_m = "Planck length";
  def_m  = c.measuredIn(m/s)
         * sqrt( c.measuredIn(m/s)
               / ( hBar.measuredIn(J*s) * G_N.measuredIn(m3/(kg * s2))
                 )
               )
         ;

  //
  unit_kg = "Planck mass";
  //def_kg  = kg.measuredIn(Planck_mass);
  def_kg  = sqrt( G_N.measuredIn(m3/(kg * s2))
                / ( hBar.measuredIn(J*s) * c.measuredIn(m/s)
                  )
                )
          ;

  //
  unit_K = "Planck temperature";
  def_K  = k.measuredIn(J/K)
         * sqrt( G_N.measuredIn(m3/(kg * s2))
               / ( hBar.measuredIn(J*s) * c.measuredIn(m/s)
                 )
               )
         / c2.measuredIn(m2/s2)
         ;

  //
  unit_A = "Planck current";
  def_A  = sqrt( mu_0.measuredIn(N/(A*A))
               * G_N.measuredIn(m3/(kg * s2))
               )
         / c2.measuredIn(m2/s2)
         ;

  // Remaining units will default to 1:
  unit_mol = "mol";  def_mol = 1.0;
  unit_cd  = "cd";   def_cd  = 1.0;

  // It's showtime:
  emit( "natModel" );

}  // nat()



int main()  {

  time_t   now = time(0);
  char *   timestamp = ctime( &now );  timestamp[24] = '\0';
  utsname  sysinfo;  uname( &sysinfo );


  cout <<
"// ----------------------------------------------------------------------\n"
"//\n"
"// calibration - auto-generated file:  DO NOT MODIFY BY HAND!\n"
"//\n"
"//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\\\\n"
"//                                                                     \\\\\n"
"// NOTICE:                                                             \\\\\n"
"//   This file is part of \"The SI Library of Unit-Based Computation.\"  \\\\\n"
"//   See \"doc/README\" for copyright, license, and other information.   \\\\\n"
"//                                                                     \\\\\n"
"//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\\\\n"
"//\n"
"// Generated on " << (timestamp+4) << " by " << sysinfo.nodename << "\n"
"//\n"
"// ----------------------------------------------------------------------\n"
  ;

  rel();
  hep();
  qtm();
  nat();

  return 0;

}  // main()
