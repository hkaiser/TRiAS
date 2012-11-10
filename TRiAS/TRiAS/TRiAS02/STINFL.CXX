/*Translated by FOR_C, v3.1, on 02/25/91 at 13:57:10 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dv str=l */
/*+
 *       *****************************************************************
 *       * Strecke in Flaeche (Rechteck, Container) ?                    *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: AE4-610-A75018
 *       Autor:                Major, Walter; Dr.Barthelmes, Franz
 *       Datum:                16-Mai-90
 *       Modulname:            *** STINFL ***
 *       Routinenummer:        3012
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         DFLOAT,ISIGN,SIGN
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         -
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               LTEST=STINFL(IX1,IY1,IX2,IY2,IXC1,IYC1,
 *                                                              IXC3,IYC3)
 *                             STINFL - FUNCTION                       L
 *
 *       Parameter:            IX1    - X von Streckenanfang           I*4
 *                             IY1    - Y von Streckenanfang           I*4
 *                             IX2    - X von Streckenende             I*4
 *                             IY2    - Y von Streckenende             I*4
 *                             IXC1   - Xmin der Flaeche               I*4
 *                             IYC1   - Ymin der Flaeche               I*4
 *                             IXC3   - Xmax der Flaeche               I*4
 *                             IYC3   - Ymax der Flaeche               I*4
 *       Aufgabenstellung:
 *          logische Funktion zur Feststellung, ob eine mit dem Anfangs-
 *          punkt (X1,Y1) und Endpunkt (X2,Y2) gegebenen Strecke mit
 *          einer durch 2 Punkte Xmin, Ymin und Xmax, Ymax definierten
 *          achsenparallelen Flaeche (Rechteck, Container) inzidiert
 *          (.TRUE.) oder nicht (.FALSE.).
 *       Fehlerbehandlung:
 *          -
 *       -----------------------------------------------------------------
 *- */

#include "trias02p.hxx"

long FUNCTYPE stinfl (long *ix1, long *iy1, long *ix2, long *iy2, 
		      long *ixc1, long *iyc1, long *ixc3, long *iyc3)
{
long idx, idy;
double rdx, rdxa, rdxb, rdy, rdya, rdyb, rpa, rpb;

	/**** ein Streckenendpunkt im Container ?: */
	if ((*ix1 >= *ixc1) && (*ix1 <= *ixc3) && 
	    (*iy1 >= *iyc1) && (*iy1 <= *iyc3))
		return TRUE;	// AnfangsPunkt auf Rand oder im Container

	if ((*ix2 >= *ixc1) && (*ix2 <= *ixc3) && 
		 (*iy2 >= *iyc1) && (*iy2 <= *iyc3))
		return TRUE;	// EndPunkt auf Rand oder im Container 

// beide Streckenendpunkte links, rechts, oberhalb, unterhalb Container ?
	if ((*ix1 < *ixc1) && (*ix2 < *ixc1))
		return FALSE;	// X der Strecke < X des Containers

	if ((*ix1 > *ixc3) && (*ix2 > *ixc3)) 
		return FALSE;	// X der Strecke > X des Containers

	if ((*iy1 < *iyc1) && (*iy2 < *iyc1))
		return FALSE;	// Y der Strecke < Y des Containers

	if ((*iy1 > *iyc3) && (*iy2 > *iyc3))
		return FALSE;	// Y der Strecke > Y des Containers
	
	idx = *ix2 - *ix1;
	idy = *iy2 - *iy1;

// Fall, wenn DX oder DY = 0 (Strecke senkrecht bzw. waagerecht)
	if ((idx == 0) || (idy == 0))
		return TRUE;	// Strecke auf Rand oder durch Container

// Strecke schneidet Teilstueck des Containers ab oder nicht
// Pinzip: gegenseitige Lage eines Punktepaares und einer Geraden,
//         die durch 2 Punkte bestimmt ist !
	rdx = (double)idx;
	rdy = (double)idy;
	if (sign (idx) == sign (idy)) {
		rdxa = (double)(*ixc3 - *ix1);
		rdya = (double)(*iyc1 - *iy1);
		rdxb = (double)(*ixc1 - *ix1);
		rdyb = (double)(*iyc3 - *iy1);
	}
	else {
		rdxa = (double)(*ixc1 - *ix1);
		rdya = (double)(*iyc1 - *iy1);
		rdxb = (double)(*ixc3 - *ix1);
		rdyb = (double)(*iyc3 - *iy1);
	}
	rpa = rdx*rdya - rdy*rdxa;
	rpb = rdx*rdyb - rdy*rdxb;
	if(rpa == 0.0 || rpb == 0.0)
		return TRUE;	// Strecke auf Eckpunkt des Containers

	if (sign (rpa) == sign (rpb))
		return FALSE;	// Strecke auﬂerhalb des Containers

return TRUE;		// Strecke durch Container
}


