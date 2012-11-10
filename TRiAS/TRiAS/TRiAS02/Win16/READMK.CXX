/*Translated by FOR_C, v3.2 (B), on 05/28/91 at 10:45:56 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fcrt.h>
/******************************************************************
 ****                                                           ***
 ****         FUNCTION   READMK (WHLG,ZVMKO,ON)                 ***
 ****         DATENBASIS   BEREICH II                           ***
 ****         12.07.89     KUPPER                               ***
 ****         02.04.90                                          ***
 ****                                                           ***
 ****************************************************************** */
	/* PARAMETER translations */
#define	ROUTCD	5001L
#define	SHDIDN	6L
#define	WNRECW	1018L
	/* end of PARAMETER translations */

#include "zipedb.h"
#include "ris.h"
#include "zforc.h"

long /*FUNCTION*/ FUNCTYPE
readmk(whlg, mkvmo, on)
long int *whlg, *mkvmo, on[];
{
long int dbavmo[2], irc, k, readmk_v, vmo[SIZVMO]; 


	/*  READMK SUCHT ZU EINEM VORGEGEBENEN EP IN DIE VMKO
	 *  ALLE DAZUGEHOERIGEN OBJEKTE HERAUS UND SPEICHERT
	 *  SIE IM FELD  ON  AB ON(3) EIN.
	 *
	 *  LRC = 0    O.K.
	 *
	 *  LRC < 0    FELD ON IST VOLL BELEGT, ES SIND NOCH
	 *             OBJEKTE VORHANDEN
	 *
	 *  LRC > 0    FEHLER
	 *
	 *
	 *  ON(1) =    MAX. LAENGE DES FELDES, WIRD DURCH DAS
	 *             HAUPTPROGRAMM BELEGT.
	 *
	 *  ON(2) =    AKTUELLE LAENGE, ERGIBT SICH AUS DER
	 *             ANZAHL DER GEFUNDENEN OBJEKTE. BELE-
	 *             GUNG ERFOLGT IN READMK.
	 *
	 *  MKVMO=    EINTRITTSPUNKT IN DIE OBJ.KETTE DER VMKO
	 *
	 *
	 * */

	if (on[0L] < 3L) {
		readmk_v = ENODIM;
		db_error (ENODIM, ROUTCD);
		return( readmk_v );
	}
	on[1L] = 0L;
	dbavmo[0L] = NVMO;
	dbavmo[1L] = *mkvmo;

	irc = EOKAY;
	readmk_v = EOKAY;
	*whlg = 0L;
	k = 1L;
	/*  VMKO-SATZ */
L_30:
	;
	irc = zread( dbavmo, vmo );
	if (irc != EOKAY) {
		readmk_v = irc;
		return( readmk_v );
	}
	on[k + 1L] = vmo[ZVMOO - 1L];
	/*   ZOL */
	on[1L] = on[1L] + 1L;
	k = k + 1L;
	dbavmo[1L] = vmo[ZNVMO - 1L];
	/*   ZNS IN VMKO */
	if (dbavmo[1L] == 0L) 
		return( readmk_v );
	if (on[1L] + 3L > on[0L]) {
		*whlg = -1L;
		*mkvmo = dbavmo[1L];
		return( readmk_v );
	}
	goto L_30;
} /* end of function */

