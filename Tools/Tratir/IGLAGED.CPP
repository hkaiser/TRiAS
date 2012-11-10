
#include "tratasp.h"

#include <math.h>

/*+
 *       Aufruf:               I=IGLAGED(PX,PY,AX,AY,EX,EY)
 *       Aufrufparameter:
 *         PX,PY -- Koordinaten des Testpunkts P, r*8
 *         AX,AY -- Koordinaten des Anfangspunkts eines Richtungsvektors
 *                  der Geraden g, r*8
 *         EX,EY -- Koordinaten des Endpunkts eines Richtungsvektors
 *                  der Geraden g, r*8
 *       Rueckkehrparameter:
 *         IGLAGE = -1 -- P liegt links von g in Richtung AE, i*4
 *         IGLAGE =  0 -- P inzidiert g
 *         IGLAGE = +1 -- P liegt rechts von g in Richtung AE
 *       Aufgabenstellung:
 *         Ermittlung der Lagecharakteristik eines Testpunkts P bezueglich
 *         einer gerichteten Geraden g
 *- */

#define ARITHIF(x) (((x) > 0. ? 1L : ((x) < 0. ? -1L : 0L)))

long iglaged (double *px, double *py, 
	      double *ax, double *ay, 
	      double *ex, double *ey)
{
double tstVal = (*px - *ax)*(*ay - *ey) + (*py - *ay)*(*ex - *ax);

	return ARITHIF(tstVal);
}

