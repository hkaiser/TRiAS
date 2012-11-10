// ----------------------------------------------------------------------
//
// NT_wv.h - world views for si dimensions and units
//    NT Version: No Templates used
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//								       \\
// NOTICE:							       \\
//   This file is part of "The SI Library of Unit-Based Computation."  \\
//   See "doc/README" for copyright, license, and other information.   \\
//								       \\
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\\
//
// History:
//   19-Jan-1999  MF   Initial version taken from wv.h
//   21-Jan-1999  MF   Provided pre-definition of OutLook via kludge,
//			to compensate for lack of template specialization
//
// ----------------------------------------------------------------------


#ifdef SI_wv_OutLook
enum OutLook  {
  standardModel
, relativityModel
, highenergyModel
, quantumModel
, naturalModel
};
#else // Not SI_wv_OutLook

#include "calibration"

struct wv {

  enum BaseDims  {
    dimPure,	dimLength, dimMass,  dimTime,
    dimCurrent, dimTemp,   dimSubst, dimLI
  };

  inline static RepType scale_ (unsigned int d) {
      switch(ourModel) {
	case standardModel: return RepType (1);
	case relativityModel: {
	    switch(d) {
		case dimLength: return RepType(relModel::def_m);
		case dimMass:	return RepType(relModel::def_kg);
		case dimTime:	return RepType(relModel::def_s);
		case dimCurrent:return RepType(relModel::def_A);
		case dimTemp:	return RepType(relModel::def_K);
		case dimSubst:	return RepType(relModel::def_mol);
		case dimLI:	return RepType(relModel::def_cd);
		default:	return RepType(1);
	    }
	}
	case highenergyModel: {
	    switch(d) {
		case dimLength: return RepType(hepModel::def_m);
		case dimMass:	return RepType(hepModel::def_kg);
		case dimTime:	return RepType(hepModel::def_s);
		case dimCurrent:return RepType(hepModel::def_A);
		case dimTemp:	return RepType(hepModel::def_K);
		case dimSubst:	return RepType(hepModel::def_mol);
		case dimLI:	return RepType(hepModel::def_cd);
		default:	return RepType(1);
	    }
	}
	case quantumModel: {
	    switch(d) {
		case dimLength: return RepType(qtmModel::def_m);
		case dimMass:	return RepType(qtmModel::def_kg);
		case dimTime:	return RepType(qtmModel::def_s);
		case dimCurrent:return RepType(qtmModel::def_A);
		case dimTemp:	return RepType(qtmModel::def_K);
		case dimSubst:	return RepType(qtmModel::def_mol);
		case dimLI:	return RepType(qtmModel::def_cd);
		default:	return RepType(1);
	    }
	}
	case naturalModel: {
	    switch(d) {
	    case dimLength: return RepType(natModel::def_m);
		case dimMass:	return RepType(natModel::def_kg);
		case dimTime:	return RepType(natModel::def_s);
		case dimCurrent:return RepType(natModel::def_A);
		case dimTemp:	return RepType(natModel::def_K);
		case dimSubst:	return RepType(natModel::def_mol);
		case dimLI:	return RepType(natModel::def_cd);
		default:	return RepType(1);
	    } // switch(d)
	} // case naturalModel
	default: return RepType(1);
      } // switch (ourModel)
  } // wv::scale_(d)

}; // wv


#endif // End of not-SI_wv_OutLook ifdef
