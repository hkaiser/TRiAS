/*Translated by FOR_C, v3.1, on 04/16/91 at 14:32:21 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */

#include "tratasp.h"

#include <math.h>

/*+
 *       Aufruf:               R=GINHED(EOX,EOY,L1,L2)
 *       Parameter:            
 * -- Aufrufparameter:
 *    EOX(L1),EOY(L1),...,EOX(L2),EOY(L2) -- Stuetzpunkte des EO, R*8,
 *             EOX(L2)=EOX(L1) und EOY(L2)=EOY(L1) wird vorausgesetzt
 *    L1   -- Index 1. Stuetzpunkt des EO, I*4
 *    L2   -- Index letzter Stuetzpunkt des EO, I*4
 * -- Rueckkehrparameter:
 *    GINHE -- 2-facher vorzeichenbehafteter Flaecheninhalt, R*8
 *             GINHE > 0 -- EO mathematisch positiv orientiert
 *             GINHE < 0 -- EO mathematisch negativ orientiert
 *
 *       Aufgabenstellung:
 * -- GINHE berechnet den 2-fachen vorzeichenbehafteten Flaecheninhalt
 *    des vom geschlossenen Polygonzug EO(L1...L2) umschlossenen, be-
 *    schraenkten Gebiets:
 *
 *         2F = x1*(y2-yn)+x2*(y3-y1)+...+xn*(y1-y(n-1)))
 *
 *    EO(L1) = EO(L2) wird vorausgesetzt.
 *       -----------------------------------------------------------------
 *- */

double /*FUNCTION*/ ginhed(double *eox, double *eoy, long *l1, long *l2)
{
long int _do0, i, i_;
double ginhe_v;

/* Startwert */
	ginhe_v = eox[*l2 - 1L]*(eoy[*l1] - eoy[*l2 - 2L]);

/* Fl„cheninhalt */
	for (i = *l1 + 1L, _do0 = *l2 - 1L; i <= _do0; i++) {
		i_ = i - 1;
		ginhe_v = ginhe_v + eox[i_]*(eoy[i_ + 1L] - eoy[i_ - 1L]);
	}

return( ginhe_v );
} /* end of function */

