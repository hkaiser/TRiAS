/*Translated by FOR_C, v3.1, on 02/21/91 at 11:53:01 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *                                                          ### IGLAGE ###
 *       *****************************************************************
 *       * Lagecharakteristik eines Punktes zu einer gerichteten Geraden *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, Bereich 2
 *       Dokumentationsnummer: AD-610-A64518
 *       Autor:                Dr. Oppitz, K.        
 *       Datum:                02-JUN-89
 *       Version:              2-6-89-IGLAGE
 *       Modulname:            *** IGLAGE ***
 *       Programmiersprache:   Fortran-77
 *       -----------------------------------------------------------------
 *       Aufruf:               I=IGLAGE(PX,PY,AX,AY,EX,EY)
 *       Aufrufparameter:
 *         PX,PY -- Koordinaten des Testpunkts P
 *         AX,AY -- Koordinaten des Anfangspunkts eines Richtungsvektors
 *                  der Geraden g
 *         EX,EY -- Koordinaten des Endpunkts eines Richtungsvektors
 *                  der Geraden g
 *       Rueckkehrparameter:
 *         IGLAGE = -1 -- P liegt links von g in Richtung AE
 *         IGLAGE =  0 -- P inzidiert g
 *         IGLAGE = +1 -- P liegt rechts von g in Richtung AE
 *       Aufgabenstellung:
 *         Ermittlung der Lagecharakteristik eines Testpunkts P bezueglich
 *         einer gerichteten Geraden g
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

long FUNCTYPE iglage (long *px, long *py, long *ax, long *ay, long *ex, long *ey)
{
double dRes = double(*px - *ax)*double(*ay - *ey) + double(*py - *ay)*double(*ex - *ax);

	if (dRes < 0) return -1;
	if (dRes > 0) return 1;

return 0;
}


