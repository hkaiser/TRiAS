/*Translated by FOR_C, v3.2 (B), on 05/28/91 at 09:31:18 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

	/* PARAMETER translations */
#define	SHDIDN	6L
#define	WNRECW	1018L
	/* end of PARAMETER translations */

#include "ris.h"
#include "zipedb.h"
#include "zforc.h"

long /*FUNCTION*/ FUNCTYPE
get4b(zvmi, minf, k)
long int *zvmi, minf[], *k;
{
long int dbami[2], get4b_v, irc, l, mi[SIZMI];


	/*       K.Kurth
	 *       datum:31.05.90
	 *
	 *       Aufgabe :
	 *               Zusammenstellen der MI aus DB in Feld MINF ab 
	 *               Position k pro MK (Pointer zvmi) fuer MI
	 *               mit 4Byte je Einzelinformation 
	 *               (Typ 1:integer*4/Typ 2:real*4).
	 *               Neue Position im Feld Minf (k) nach Fuellen
	 *               uebergeben
	 * */


	/*------ k=mk # k+1=typ # k+2=wf -------- */
	irc = EOKAY;
	get4b_v = EOKAY;
	dbami[0L] = NMI;
	/****    wf=0 */
	minf[*k + 1L] = 0L;
	/****    Position im MI-Feld */
	l = *k + 3L;
	/*--------MI-Wertebearbeitung-------- */
L_10:
	dbami[1L] = *zvmi;
	if (l > minf[0L]) {
		/******** MI-Feld zu klein/Wiederholung *** */
		get4b_v = WDHLG;
		return( get4b_v );
	}
	/****    Lesen MI-Satz */
	irc = zread( dbami, mi );
	if (irc != EOKAY) 
		goto L_100;
	/****    wf=wf+1 */
	minf[*k + 1L] = minf[*k + 1L] + 1L;
	*zvmi = mi[ZNMI - 1L];
	/*------Merkmalswert---- */
	minf[l - 1L] = mi[MW - 1L];
	l = l + 1L;
	if (*zvmi > 0L) 
		goto L_10;
	*k = l;
	/****    neue Laenge MI-Feld gesamt */
	minf[1L] = *k - 3L;
L_100:
	get4b_v = irc;
	return( get4b_v );
} /* end of function */

