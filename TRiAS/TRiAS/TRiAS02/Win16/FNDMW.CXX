/*Translated by FOR_C, v3.2 (B), on 05/28/91 at 09:26:24 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcrt.h>
	/* PARAMETER translations */
#define	ROUTCD	5002
#define	SHDIDN	6
#define	WNRECW	1018
	/* end of PARAMETER translations */

#include "zipedb.h"
#include "ris.h"
#include "zforc.h"

long /*FUNCTION*/ FUNCTYPE
fndmw(mko, zmkl, ty, tkz, wie, on)
long int *mko, *zmkl, *ty;
char *tkz[2];
double wie[];
long int on[];
{
LOGICAL32 itst;
long int _do0, _do1, _l0, _l1, dbami[2], dbamkl[2], dbaobl[2], dbavom[2], 
	 fndmw_v, i, i_, imkl, irc, k, k_, mi[SIZMI], *mir, 
	 obl[SIZOBL], *rw, vom[SIZVOM];
int (*w_notfound)(int, int, ...);
int (*dummy)(int, int, ...);
float *r4;
double miw, *rwi;
double _e1[1], _e0[1];
	/* EQUIVALENCE translations */
mir = (long*)_e1;
r4 = (float*)_e1;
rw = (long*)_e0;
rwi = (double*)_e0;
	/* end of EQUIVALENCE translations */


	/*   DATENBASIS    KUPPER  29.06.88  BEREICH II
	 *               VERSION:  02.04.90
	 *
	 *   FNDMW SUCHT OBJEKTNUMMERN EINES MERKMALSKODES
	 *   NACH EINER BESTIMMTEN MERKMALSINFORMATION HERAUS
	 * */


	irc = EOKAY;
	dbamkl[0L] = NMKL;
	dbavom[0L] = NVOM;
	dbami[0L] = NMI;
	dbaobl[0L] = NOBL;
	dbamkl[1L] = 0L;

	for (k = 3L, _do0 = on[1L] + 2L; k <= _do0; k++) {
		k_ = k - 1;
		dbaobl[1L] = on[k_];
		irc = zread( dbaobl, obl );
		if (irc != EOKAY) {
			fndmw_v = irc;
			return( fndmw_v );
		}
		if (obl[ZOVOM - 1L] == 0L) 
			goto L_102;
		/*       Objekt hat keine Merkmale: */
		dbavom[1L] = obl[ZOVOM - 1L];

L_41:
		irc = zread( dbavom, vom );
		if (irc != EOKAY) {
			fndmw_v = irc;
			return( fndmw_v );
		}
		imkl = vom[ZVOMMK - 1L];
		err_install (WNTFND, (int(*)(int,int,...))0, &w_notfound);
		irc = zfind( dbamkl, ADR(_l0,SMK), (char *)mko );
		err_install (WNTFND, w_notfound, &dummy);
		if (irc == EOKAY)
			goto L_55;
		if (irc == WNTFND) {
			fndmw_v = WNOMK;
			db_error (WNOMK, ROUTCD);
		} else {
			goto L_102;
		}
		return( fndmw_v );
		/*   ZMK   */
L_55:
		if (imkl == *zmkl) {
			if (wie[0L] == -1.0 && wie[1L] == -1.0)
				goto L_30;
			/*                                        MK GEF./KEIN WI GES. */
			dbami[1L] = vom[ZVOMMI - 1L];
			/*                                        ZWERT */
L_44:
			irc = zread( dbami, mi );
			if (irc != EOKAY) {
				fndmw_v = irc;
				return( fndmw_v );
			}
			if (*ty == 3L) {
				/*                                        NAECHSTER WERT */
				rw[0L] = mi[MW - 1L];
				rw[1L] = mi[MW];
				miw = *rwi;
			} else{
				if (*ty == 2L) {
					*mir = mi[MW - 1L];
					miw = *r4;
				} else{
					if (*ty == 1L)
						miw = mi[MW - 1L];
				}
			}
			if (wie[0L] == -1.0)
				goto L_35;
			itst = mitst (&wie[0L], &miw, ty, tkz[0]);
			if (!itst)
				goto L_39;
L_35:
			if (wie[1L] == -1.0)
				goto L_30;
			itst = mitst (&wie[1L], &miw, ty, tkz[1]);
			if (itst)
				goto L_30;
L_39:
			if (mi[ZNMI - 1L] > 0L) {
				dbami[1L] = mi[ZNMI - 1L];
				goto L_44;
			}
			on[k_] = -1L;
			goto L_30;
		} else{
			dbavom[1L] = vom[ZNMK - 1L];
			if (dbavom[1L] != 0L)
				goto L_41;
			/*                                        ZNMK */
		}
L_102:
		on[k_] = -1L;
L_30:
		;
	}
	k = 0L;
	for (i = 3L, _do1 = on[1L] + 2L; i <= _do1; i++) {
		i_ = i - 1;
		if (on[i_] != -1L) {
			k = k + 1L;
			on[k + 1L] = on[i_];
		}
	}
	on[1L] = k;
	fndmw_v = irc;
	return( fndmw_v );
} /* end of function */

