/*Translated by FOR_C, v3.1, on 04/11/91 at 10:26:07 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */

extern "C" {
	#include <math.h>
}

/*+
 *       *****************************************************************
 *       * geogr. Koordinaten zu Weltprojektion (nach Winkel)            *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: -
 *       Autor:                Major, Walter
 *       Datum:                11-Apr-91
 *       Modulname:            *** GEOWEL ***
 *       Routinenummer:        -
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         DSIN,DCOS,DACOS,DABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         -
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GEOWEL (B,L,X,Y)
 *
 *                             GEOWEL - FUNCTION                       I*4
 *                             IRC    - Rueckkehrcode                  I*4
 *
 *       Parameter:
 *               Input:     B      - geogr. Breite des Pkt. in Grad    R*8
 *                          L      - geogr. Laenge des Pkt. in Grad    R*8
 *               Output:    X      - Hochwert in m                     R*8
 *                          Y      - Rechtswert in m                   R*8
 *       Aufgabenstellung, Hintergrund:
 *          Die Funktion GEOWEL.f (geographische Koordinaten zu einer
 *          Weltdarstellung (Winkelscher Entwurf)) ist nach
 *          K. Wagner: Kartographische Netzentwuerfe, Bibliographisches
 *          Institut Leipzig, 1949, S.224 ff. programmiert.
 *          Die geographischen Koordinaten B und L werden als Kugelkoor-
 *          dinaten angenommen. B darf von -90 bis +90 Grad, L von -180
 *          bis +180 laufen.
 *          Die ebenen Koordinaten werden mit X (Hochwert) und Y
 *          (Rechtswert) bezeichnet. Der Koordinatenursprung fuer X und
 *          Y ist der Schnittpunkt vom Nullmeridian und dem Aequator.
 *       Fehlerbehandlung:
 *          GEOKEG=EOKAY  i.O.
 *                =EBREIT B>90,  B<-90
 *                =ELAEN  L>180, L<-180
 *       -----------------------------------------------------------------
 *- */

#include "ristypes.hxx"

	/* PARAMETER translations */
#define	EBREIT	(-2L)
#define	ELAEN	(-5L)
#define	EOKAY	0L
#define	N	0.766044443e0
#define	RHO	57.29577951e0
	/* end of PARAMETER translations */

void geowel (KoOrd *x, KoOrd *y) {
long double bb, cosa, cosd, da, db, lb;
long double b = (double)*y/1024000.0-90.0;
long double l = (double)*x/1024000.0-180.0;

/* / ** Eingabeparameter testen: 
	if (b > 90.0) b -= 180.0;
	if (b < -90.0) b += 180.0;
	if (l > 180.0) l -= 360.0;
	if (l < -180.0) l += 360.0;
*/

/* *** Anfangswerte setzen: */
	bb = fabs (b/RHO);
	lb = fabs ((l/(2*RHO)));
/* *** Projektion: */
	cosd = cos (bb) * cos (lb);
	db = acos (cosd);
	if (fabs (db) < 1.0e-10) {
	/* Div. durch Null ? */
		cosa = 0.0e0;
		da = 1.570796327e0;
	} else {
		cosa = sin (bb)/sin (db);
		da = acos (cosa);
	}

	*x = (KoOrd)((db*sin (da) + N*lb)*1024000.0);	// Rechtswert
	*y = (KoOrd)((db*cosa + bb)*512000.0);		// Hochwert
	if (l < 0.0e0) 
		*x = -(*x);	// negative L„nge
	if (b < 0.0e0) 
		*y = -(*y);	// negative Breite
}


