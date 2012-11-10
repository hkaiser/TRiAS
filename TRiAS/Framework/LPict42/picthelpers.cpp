#include "stdafx.h"
#include <math.h>

void dbl2ratio( double d, ULONG& div, ULONG& denom ) {
	double		eps;
	ULONG		umax = UINT_MAX / 2;
	
	double	b;
	long	p_1, p_2;
	long	q_1, q_2;
	double	bdiff;
	long	k;

	div = denom = 0;
	if( 0.0 == d ) {
		return;
	}
	p_2 = 0; p_1 = 1;
	q_2 = 1; q_1 = 0;
	bdiff = 1/d;
	int	step = 0;
	for(;;) {
		b = 1 / bdiff;
		k = (long) floor( b );
		bdiff = b - k;
		div   = k * p_1 + p_2;
		denom = k * q_1 + q_2;
		eps = d - ( (double) div / (double) denom );
/*
		cout << step
			<< TAB << c.b
			<< TAB << c.bdiff
			<< TAB << c.k
			<< TAB << c.p
			<< TAB << c.q
			<< TAB << eps
			<< endl;
*/
		p_2 = p_1; p_1 = div;
		q_2 = q_1; q_1 = denom;
		eps = fabs( eps );
		if( eps < 1e-13 ) {
//			cerr << "break on eps" << endl;
			break;
		}
		if( div > umax || denom > umax ) {
//			cerr << "break on umax" << endl;
			break;
		}
		if( ++step > 20 ) {
//			cerr << "break on step" << endl;
			break;
		}
	}
}
