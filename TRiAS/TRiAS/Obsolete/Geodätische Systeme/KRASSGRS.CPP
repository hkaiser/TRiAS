// Transformation Krassovsky<-->GRS80 
// File: KrassGrs.cpp

#include "begeodp.hxx"
#include "ctfgeogk.h"

#define	DX		24.0
#define	DY		(-123.0)
#define	DZ		(-94.0)

#define	EPS		(-0.02/RHOS)
#define	OMEG	(0.13/RHOS)
#define	PHI		(0.25/RHOS)

#define	MA		(1.0+1.1e-6)

void KrassGrs80 (double dHoch, double dRechts, long double *pdHochOut, long double *pdRechtsOut)
{
long double dX, dY, dZ;
long double dXG, dYG, dZG;
long double dTmp;

	geodrei (HA_KRASSOVSKY, HB_KRASSOVSKY, dHoch, dRechts, 0.0, &dX, &dY, &dZ);
	transfo (dX, dY, dZ, &dXG, &dYG, &dZG);
	dreigeo (HA_ETRS89, HB_ETRS89, dXG, dYG, dZG, pdHochOut, pdRechtsOut, &dTmp);
}

void Grs80Krass (double dHoch, double dRechts, long double *pdHochOut, long double *pdRechtsOut)
{
long double dX, dY, dZ;
long double dXG, dYG, dZG;
long double dTmp;

	geodrei (HA_ETRS89, HB_ETRS89, dHoch, dRechts, 0.0, &dX, &dY, &dZ);
	invtransfo (dX, dY, dZ, &dXG, &dYG, &dZG);
	dreigeo (HA_KRASSOVSKY, HB_KRASSOVSKY, dXG, dYG, dZG, pdHochOut, pdRechtsOut, &dTmp);
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen
void geodrei (double ha, double hb, double rb, double rl, double h, 
			  long double *x, long double *y, long double *z)
{
double ee = ((ha*ha) - (hb*hb))/(ha*ha);

	rb /= RHOS;
	rl /= RHOS;
	
double bsin = sin (rb);
double bcos = cos (rb);
double rn = ha/(sqrt (1.0e0 - (ee * bsin*bsin)));

	*x = (rn + h) * bcos * cos (rl);
	*y = (rn + h) * bcos * sin (rl);
	*z = ((rn * (1.0 - ee)) + h) * bsin;
}

void transfo (double xk, double yk, double zk, long double *xg, long double *yg, long double *zg)
{
	*xg = MA*xk		+ OMEG*yk	- PHI*zk	+ DX;
	*yg = -OMEG*xk	+ MA*yk		+ EPS*zk	+ DY;
	*zg = PHI*xk	- EPS*yk	+ MA*zk		+ DZ;
}

void invtransfo (double xg, double yg, double zg, long double *xk, long double *yk, long double *zk)
{
	xg -= DX;
	yg -= DY;
	zg -= DZ;

	*xk = MA*xg		- OMEG*yg	+ PHI*zg;
	*yk = OMEG*xg	+ MA*yg		- EPS*zg;
	*zk = -PHI*xg	+ EPS*yg	+ MA*zg;
}

void dreigeo (double ha, double hb, double x, double y, double z, 
			  long double *rb, long double *rl, long double *h)
{
double ee = ((ha*ha) - (hb*hb))/(ha*ha);
double eps = 0.000001e0;
double rbalt = 4.0e0;
double bsin = 0.8e0;

	*rl = atan (y / x);

double rn;

	while (true) {
		rn = ha/(sqrt (1.0 - (ee*bsin*bsin)));

		*rb = atan ((z + (ee*rn*bsin))/(sqrt ((x*x) + (y*y))));
		if (fabs ((rbalt - *rb) * RHOS) < eps) 
			break;
		rbalt = *rb;
		bsin = sin (*rb);
	}

	*rl *= RHOS;
	*h = (sqrt ((x*x) + (y*y))/cos (*rb)) - rn;
	*rb *= RHOS;
}

