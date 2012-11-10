// ----------------------------------------------------------------------
//
// wv.h - world views for si dimensions and units
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
//   19-May-1998  WEB  Initial draft
//   30-Jul-1998  WEB  Completed set of world views
//
// ----------------------------------------------------------------------



enum OutLook  {
  standardModel
, relativityModel
, highenergyModel
, quantumModel
, naturalModel
};


#include "calibration"


// -----  generic class:
//
template< OutLook O, class RepType >  struct wv  {};



// -----  standard world view:
// Assume all basic dimensions are independent.
//
template< class RepType >  struct wv<standardModel,RepType>  {

enum BaseDims  {
  dimPure,    dimLength, dimMass,  dimTime,
  dimCurrent, dimTemp,   dimSubst, dimLI
};

  template< int p1, int p2, int p3, int p4, int p5, int p6, int p7 >
  struct D  {
    enum  {
      d1 = p1
    , d2 = p2
    , d3 = p3
    , d4 = p4
    , d5 = p5
    , d6 = p6
    , d7 = p7
    };
  };  // D<>

  static inline RepType scale_( unsigned int d )  {
    return  RepType(1);
  }  // scale_()

};  // wv<standardModel>


// -----  relativistic physics world view:
// Assume lightspeed to be 1:
// in consequence, Length and Time dimensions merge.
// Also merge LuminousIntensity with W/sr = J/s = m2 kg / s3 = kg/s in relModel.
//
template< class RepType >  struct wv<relativityModel,RepType>  {

enum BaseDims  {
  dimPure,    dimLength, dimMass,  dimTime,
  dimCurrent, dimTemp,   dimSubst, dimLI
};

  template< int p1, int p2, int p3, int p4, int p5, int p6, int p7 >
  struct D  {
    enum  {
      d1 = p1+p3
    , d2 = p2
    , d3 = 0
    , d4 = p4
    , d5 = p5
    , d6 = p6
    , d7 = p7
    };
  };  // D<>

  static inline RepType scale_( unsigned int d )  {
    using namespace relModel;
    switch ( d )  {
      case dimLength  : return  RepType(def_m);
      case dimMass    : return  RepType(def_kg);
      case dimTime    : return  RepType(def_s);
      case dimCurrent : return  RepType(def_A);
      case dimTemp    : return  RepType(def_K);
      case dimSubst   : return  RepType(def_mol);
      case dimLI      : return  RepType(def_cd);
      default         : return  RepType(1);
    }  // switch
  }  // scale_()

};  // wv<relativityModel>


// -----  high-enery physics world view:
// Assume lightspeed to be 1:
// in consequence, Length and Time dimensions merge,
// Also merge Temperature dimension with Mass dimension.
// Also merge LuminousIntensity with W/sr = J/s = m2 kg / s3 = kg/s in relModel.
// Finally, merge Molarity into Dimensionless.
//
template< class RepType >  struct wv<highenergyModel,RepType>  {

enum BaseDims  {
  dimPure,    dimLength, dimMass,  dimTime,
  dimCurrent, dimTemp,   dimSubst, dimLI
};

  template< int p1, int p2, int p3, int p4, int p5, int p6, int p7 >
  struct D  {
    enum  {
      d1 = p1+p3-p4
    , d2 = p2+p5
    , d3 = 0
    , d4 = p4
    , d5 = 0
    , d6 = p6
    , d7 = p7
    };
  };  // D<>

  static inline RepType scale_( unsigned int d )  {
    using namespace hepModel;
    switch ( d )  {
      case dimLength  : return  RepType(def_m);
      case dimMass    : return  RepType(def_kg);
      case dimTime    : return  RepType(def_s);
      case dimCurrent : return  RepType(def_A);
      case dimTemp    : return  RepType(def_K);
      case dimSubst   : return  RepType(def_mol);
      case dimLI      : return  RepType(def_cd);
      default         : return  RepType(1);
    }  // switch
  }  // scale_()

};  // wv<highenergyModel>


// -----  quantum physics world view:
// Assume both lightspeed and Planck's constant to be 1:
// in consequence, Length, Time, Temperature, Mass dimensions merge,
// and Current dimension becomes Pure.
//
template< class RepType >  struct wv<quantumModel,RepType>  {

enum BaseDims  {
  dimPure,    dimLength, dimMass,  dimTime,
  dimCurrent, dimTemp,   dimSubst, dimLI
};

  template< int p1, int p2, int p3, int p4, int p5, int p6, int p7 >
  struct D  {
    enum  {
      d1 = -p1+p2-p3+p4+p5
    , d2 = 0
    , d3 = 0
    , d4 = 0
    , d5 = 0
    , d6 = p6
    , d7 = p7
    };
  };  // D<>

  static inline RepType scale_( unsigned int d )  {
    using namespace qtmModel;
    switch ( d )  {
      case dimLength  : return  RepType(def_m);
      case dimMass    : return  RepType(def_kg);
      case dimTime    : return  RepType(def_s);
      case dimCurrent : return  RepType(def_A);
      case dimTemp    : return  RepType(def_K);
      case dimSubst   : return  RepType(def_mol);
      case dimLI      : return  RepType(def_cd);
      default         : return  RepType(1);
    }  // switch
  }  // scale_()

};  // wv<quantumModel>


// -----  natural (unitless) world view:
// Assume lightspeed, Planck's constant, and the gravitational constant to be 1:
// in consequence, all dimensions merge into Dimensionless.
//
template< class RepType >  struct wv<naturalModel,RepType>  {

enum BaseDims  {
  dimPure,    dimLength, dimMass,  dimTime,
  dimCurrent, dimTemp,   dimSubst, dimLI
};

  template< int p1, int p2, int p3, int p4, int p5, int p6, int p7 >
  struct D  {
    enum  { d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = p6, d7 = p7 };
  };  // D<>

  static inline RepType scale_( unsigned int d )  {
    using namespace natModel;
    switch ( d )  {
      case dimLength  : return  RepType(def_m);
      case dimMass    : return  RepType(def_kg);
      case dimTime    : return  RepType(def_s);
      case dimCurrent : return  RepType(def_A);
      case dimTemp    : return  RepType(def_K);
      case dimSubst   : return  RepType(def_mol);
      case dimLI      : return  RepType(def_cd);
      default         : return  RepType(1);
    }  // switch
  }  // scale_()

};  // wv<naturalModel>
