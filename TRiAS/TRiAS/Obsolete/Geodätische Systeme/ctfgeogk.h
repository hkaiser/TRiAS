// File: CtfGeoGK.h

#if !defined(_CTFGEOGK_H)
#define _CTFGEOGK_H

///////////////////////////////////////////////////////////////////////////////
// Parameter der Koordinatentransformationen 
#define HA_BESSEL		6377397.155
#define HB_BESSEL		6356078.96282
#define KS_BESSEL		1.0
#define DEF_MERIDIAN_BESSEL		12
#define DEF_STRBREITE_BESSEL	3

#define HA_KRASSOVSKY	6378245.0
#define HB_KRASSOVSKY	6356863.01877
#define KS_KRASSOVSKY	1.0
#define DEF_MERIDIAN_KRASSOVSKY	9
#define DEF_STRBREITE_KRASSOVSKY	6

#define HA_ETRS89		6378137.0
#define HB_ETRS89		6356752.31414
#define KS_ETRS89		0.9996
#define DEF_MERIDIAN_ETRS89		9
#define DEF_STRBREITE_ETRS89	6

///////////////////////////////////////////////////////////////////////////////
// sonstige Konstantendefinitionen
const double PI = 4 * atan(1.0);
const double RHOS = (60.0*60.0*180.0)/PI;
//#define	RHOS	206264.8062471e0

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen
void geodrei (double ha, double hb, double rb, double rl, double h, long double *x, long double *y, long double *z);
void dreigeo (double ha, double hb, double x, double y, double z, long double *rb, long double *rl, long double *h);

void transfo (double xk, double yk, double zk, long double *xg, long double *yg, long double *zg);
void invtransfo (double xk, double yk, double zk, long double *xg, long double *yg, long double *zg);

void modko_B (long double B, long double L, long double *dHwert, long double *dRwert);

///////////////////////////////////////////////////////////////////////////////
// eigentliche Transformation
void KrassGrs80 (double dHoch, double dRechts, long double *pdHochOut, long double *pdRechtsOut);
void Grs80Krass (double dHoch, double dRechts, long double *pdHochOut, long double *pdRechtsOut);

void geogau (double, double, short, short, double, double, double, long double *, long double *);
void gaugeo (double, double, short, short, double, double, double, long double *, long double *);

#endif // _CTFGEOGK_H
