/*Translated by FOR_C, v3.1, on 04/16/91 at 14:31:43 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */

#include "tratasp.h"

#include <math.h>

/*+
 *       Aufruf:               CALL IGUMOED (EOX,EOY,L1,L2)
 *       Parameter:            
 * -- Aufrufparameter:
 *    EOX(L1),EOY(L1),...,EOX(L2),EOY(L2) -- StÅtzpunkte des Polygonzugs,
 *                                           r*8
 *    L1   -- Anfangsindex des Polygonzugs, I*4
 *    L2   -- Endindex des Polygonzugs, I*4
 * -- Rueckkehrparameter:
 *    EOX(L1),EOY(L1),...,EOX(L2),EOY(L2) -- Stuetzpunkte des umorientier-
 *                                           ten Polygonzugs, r*8
 *
 *       Aufgabenstellung:
 * -- IGUMOE kehrt den Orientierungssinn des Polygonzugs EO(L1...L2) um
 */

void /*FUNCTION*/ igumoed (double *eox, double *eoy, long *l1, long *l2)
{
long int _do0, i, i_;
double ih;

	for (i = *l1, _do0 = (*l1 + *l2)/2L; i <= _do0; i++) {
		i_ = i - 1;

		ih = eox[*l2 - (i - *l1) - 1L];
		eox[*l2 - (i - *l1) - 1L] = eox[i_];
		eox[i_] = ih;

		ih = eoy[*l2 - (i - *l1) - 1L];
		eoy[*l2 - (i - *l1) - 1L] = eoy[i_];
		eoy[i_] = ih;
	}
}

