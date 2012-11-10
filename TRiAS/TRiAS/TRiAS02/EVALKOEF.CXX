// Inverse Matrix für Koordinatentransformation berechnen ---------------------
// File: EVALKOEF.CXX

#include "trias02p.hxx"

_TRIAS02_ENTRY 
ErrCode EXPORT02 EvalKoeffs (double *k11, double *k12, double *k21, double *k22) 
{
double DetA = *k11 * *k22 - *k12 * *k21;

	if (DetA != 0.0) {
	double temp = *k11;

		*k11 = *k22/DetA;
		*k22 = temp/DetA;
		*k12 = -(*k12/DetA);
		*k21 = -(*k21/DetA);
		return EC_OKAY;
	} else {
		return (ErrCode)db_error (EC_BadKoeffs, RC_MatrixEvalKoeffs);
	}
}


