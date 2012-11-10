/*Translated by FOR_C, v3.1, on 04/11/91 at 14:48:07 */
/*FOR_C Options SET: c=2 cd do=rt ftn=l op=i s=dv str=l */

#include "tratasp.h"

#include <math.h>

/*+
 *       *****************************************************************
 *       *       Inzidenztest Testpunkt - Polygon mit Anfangsindex       *
 *       *****************************************************************
 *       Aufruf:               I=IGPPTED(XP,YP,X,Y,L1,L2)
 *       Aufrufparameter:      
 *         XP,YP -- Koordinaten des Testpunkts, r*8
 *         (X(L1),Y(L1),...,(X(L2-1),Y(L2-1)) -- Koordinaten der Eckpunkte
 *                                               des Polygonzugs in 
 *                                               mathematisch positiver
 *                                               Orientierung, r*8
 *         X(L2)=X(L1), Y(L2)=Y(L1)
 *         L1     -- Index Anfangspunktin den Feldern X(*),Y(*), I*4
 *         L2     -- Index Endpunktin den Feldern X(*),Y(*), I*4
 *       Rueckkehrparameter:
 *         IGPPTE = -1 -- Testpunkt liegt nicht im vom Polygonzug
 *                         umschlossenen Gebiet und inzidiert nicht den 
 *                         Polygonzug
 *         IGPPTE =  0 -- Testpunkt inzidiert Polygonzug
 *         IGPPTE = +1 -- Testpunkt liegt im vom Polygonzug umschlossenen
 *                        Gebiet
 *       Aufgabenstellung:
 *         IGPPTE ermittelt die Inzidenzcharakteristik des Testpunkts P
 *         bezueglich des geschlossenen Polygonzugs mit den Eckpunkten
 *         (X(L1),Y(L1)),...,(X(L2-1),Y(L2-1))
 *         Voraussetzung: der Polygonzug ist eine geschlossene, doppel-
 *         punktfreie und orientierbare Kurve
 *- */

#define ARITHIF(x) (((x) > 0. ? 1 : ((x) < 0. ? -1 : 0)) )

long igppted (double *xp, double *yp, double *x, double *y, long *l1, long *l2)
{
long int i, idi, igppte_v, j;
double idx, nx;

#ifdef DEBUG
//	fputs( "<+>igppte()\n", debug_fp );
#endif


	/*                                Startwerte */
	igppte_v = -1L;
	/*                                X-Komponente naechstgelegener SP */
	idx = 1.7e38;
	/*                                Index naechstgelegener SP */
	idi = 0L;
	/*                                Index aktueller SP */
	i = *l1 - 1L;
L_600:
	i = i + 1L;
	/*                                Endetest */
	if( i > *l2 )
		goto L_500;
	/*                                Lagetest EP(I) zur x-achsenparallelen */
L_601:
	switch( ARITHIF(y[i - 1L] - *yp) ){
		case -1: goto L_100;
		case  0: goto L_200;
		case  1: goto L_300;
		}
	/*                                Geraden gx */


	/* -- unterhalb gx */
L_100:
	i = i + 1L;
	/*                                Endetest */
	if( i > *l2 )
		goto L_500;
	/*                                Lagetest EP(I) zu gx */
	switch( ARITHIF(y[i - 1L] - *yp) ){
		case -1: goto L_100;
		case  0: goto L_200;
		case  1: goto L_400;
		}

	/* -- EP(I) auf gx, Lagetest EP(I) auf Strahl?
	 *                                Lagetest EP(I) zu XP */
L_200:
	switch( ARITHIF(x[i - 1L] - *xp) ){
		case -1: goto L_600;
		case  0: goto L_700;
		case  1: goto L_201;
		}
	/*                                SP rechts von IDI */
L_201:
	if( x[i - 1L] >= idx )
		goto L_600;
	/*                                SP(I) neuer naechstgelegener SP */
	idx = x[i - 1L];
	idi = i;
	goto L_600;

	/* -- oberhalb gx */
L_300:
	i = i + 1L;
	/*                                Endetest */
	if( i > *l2 )
		goto L_500;
	/*                                Lagetest EP(I) zu gx */
	switch( ARITHIF(y[i - 1L] - *yp) ){
		case -1: goto L_400;
		case  0: goto L_200;
		case  1: goto L_300;
		}

	/* -- Schnitt mit gx, Lagetest SP auf Strahl, Y(I-1)#YP#Y(I) */
L_400:
	if( x[i - 2L] < x[i - 1L] ){
		/*                                                    SP nicht naechstgel. */
		if( x[i - 1L] <= *xp || x[i - 2L] >= idx )
			goto L_601;
		}
	else{
		/*                                                    SP nicht naechstgel. */
		if( x[i - 2L] < *xp || x[i - 1L] > idx )
			goto L_601;
		}

	/* -- SP berechnen und Lagetest, Y(I)#Y(I-1) */
	nx = (x[i - 2L]*(y[i - 1L] - *yp) - x[i - 1L]*(y[i - 2L] - *yp))/
	 (y[i - 1L] - y[i - 2L]);
	switch( ARITHIF(nx - *xp) ){
		case -1: goto L_601;
		case  0: goto L_700;
		case  1: goto L_401;
		}
	/*                               SP rechts von IDI */
L_401:
	if( nx >= idx )
		goto L_601;
	/*                               SP ist neuer naechstgelegener SP */
	idx = nx;
	idi = i;
	goto L_601;

	/* -- abschliessender Inzidenztest
	 *                               keine Inzidenz Strahl - Polygonflaeche */
L_500:
	if( idi <= 0L )
{ 
#ifdef DEBUG
//		fputs( " <->igppte()\n", debug_fp );
#endif
		return( igppte_v );}
	/*                               SP kein Polygoneckpunkt */
	if( y[idi - 1L] != *yp ){
		igppte_v = iglaged ( xp, yp, &x[idi - 2L], &y[idi - 2L], &x[idi - 1L], 
		 &y[idi - 1L] );
#ifdef DEBUG
//		fputs( " <->igppte()\n", debug_fp );
#endif
		return( igppte_v );
		}
	j = idi - 1L;
	/*                               SP ist Polygonendpunkt */
	if( j < *l1 )
		j = *l2 - 1L;
	/*                                            Lage P zu STR(I-1,I) */
	i = iglaged( xp, yp, &x[j - 1L], &y[j - 1L], &x[idi - 1L], yp );
	/*                                                        Lage P zu STR(I,I+1) */
	igppte_v = iglaged( xp, yp, &x[idi - 1L], yp, &x[idi], &y[idi] );
	if( iglaged( &x[idi], &y[idi], &x[j - 1L], &y[j - 1L], &x[idi - 1L], 
	 yp ) >= 0L ){
		/*                                  konvexe Ecke */
		if( i < igppte_v )
			igppte_v = i;
		}
	else{
		/*                                  konkave Ecke */
		if( i > igppte_v )
			igppte_v = i;
		}
#ifdef DEBUG
	//fputs( " <->igppte()\n", debug_fp );
#endif
	return( igppte_v );

	/* -- SP auf Polygonzug */
L_700:
	igppte_v = 0L;
#ifdef DEBUG
	//fputs( " <->igppte()\n", debug_fp );
#endif
	return( igppte_v );
} /* end of function */


