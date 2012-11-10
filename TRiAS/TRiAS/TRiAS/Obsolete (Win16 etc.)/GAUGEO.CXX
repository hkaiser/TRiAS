/*Translated by FOR_C, v3.1, on 08/27/91 at 08:22:36 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */

#include "triaspre.hxx"

#include <zforc.h>
/*+
 *       *****************************************************************
 *       * Gauss-Krueger zu geographischen Koordinaten                   *
 *       *****************************************************************
 *       (C)  ADW, ZENTRALINSTITUT FUER PHYSIK DER ERDE, BEREICH II
 *       Dokumentationsnummer: -
 *       Autor:                Major, Walter
 *       Datum:                30-Jan-91
 *       Modulname:            *** GAUGEO ***
 *       Routinenummer:        -
 *       Programmiersprache:   Fortran-77
 *       Verwendete Funktionen und Unterprogramme
 *       libF77      :         DSIN,DCOS,DTAN,DSQRT,DABS
 *       libpbv.a    :         -
 *       libgd.a     :         -
 *       libuni.a    :         -
 *       libdbn.a    :         -
 *       libdbr.a    :         -
 *       libzipedb.a :         -
 *       Common-Bloecke:       -
 *       -----------------------------------------------------------------
 *       Aufruf:               IRC=GAUGEO (HA,HB,STRBR,L0,M,X,Y,B,L)
 *
 *                             GAUGEO - FUNCTION                       I*4
 *                             IRC    - Rueckkehrcode                  I*4
 *
 *       Parameter:
 *               Input:     HA     - grosse Halbachse des Ellips. in m R*8
 *                          HB     - kleine Halbachse des Ellips. in m R*8
 *                          STRBR  - Streifenbreite in Grad            I*4
 *                          L0     - Mittelmeridian in Grad            I*4
 *                          M      - Vergroesserungsverhaeltnis        R*8
 *                          X      - Gauss-Krueger-Hochwert in m       R*8
 *                          Y      - Gauss-Krueger-Rechtswert in m     R*8
 *               Output:    B      - geogr. Breite des Pkt. in "       R*8
 *                          L      - geogr. Laenge des Pkt. in "       R*8
 *       Aufgabenstellung, Hintergrund:
 *          Die Funktionen GAUGEO.f (Gauss-Krueger-Koordinaten zu
 *          geographischen Koordinaten) und GEOGAU.f (geographische
 *          Koordinaten zu Gauss-Krueger-Koordinaten) sind nach
 *          den Formeln von K. Hubeny: 'Isotherme Koordinatensysteme
 *          und konforme Abbildungen des Rotationsellipsoides',
 *          Mitteilungen der geodaetischen Institute der TU Graz,
 *          Folge 27, 1977, S.49 f. und S.213ff. programmiert.
 *          Die Meridianbogenlaengen werden durch Integration aus
 *          Koenig/Weise: 'Mathematische Grundlagen der hoeheren
 *          Geodaesie und Kartographie', Springer Verlag, 1951, S.19
 *          erhalten.
 *          Die geographischen Koordinaten werden B und L, die des
 *          Mittelmeridians L0 genannt. Die Gauss-Krueger-Koordinaten
 *          werden mit X (Hochwert) und Y (Rechtswert) bezeichnet.
 *          Beide Formeln liefern bei Hin- und Rueckrechnung bei
 *          unserer geographischen Breite bis zu 3 Grad Abstand vom
 *          Mittelmeridian eine Genauigkeit unter 0.00001 mm, bei
 *          6 Grad Abstand in X knapp 1mm.
 *
 *          In GEOGAU werden die Koeffizienten der Potenzen von Delta L
 *          bei der Breite B gebildet (Glieder mit Potenzen von Delta B
 *          entfallen); die Meridinbogenlaenge G wird vom Aequator aus
 *          gerechnet.
 *          In GAUGEO wird bei der Fusspunktbreite BF (sie wird durch
 *          Iteration ermittelt) entwickelt.
 *       Fehlerbehandlung:
 *          GEOGAU=EOKAY   i.O.
 *                =EACHS   kleine Halbachse groesser grosse Halbachse
 *                =EBREIT  B0 groesser 90 Grad
 *                =EMASS   Vergroesserungsverhaeltnis=0
 *                =ESTRBR  falsche Sreifenbreite
 *       -----------------------------------------------------------------
 *- */

	/* PARAMETER translations */
#define	EACHS	(-1L)
#define	EBREIT	(-2L)
#define	EMASS	(-3L)
#define	EOKAY	0L
#define	ESTRBR	(-4L)
#define	P12	(1.0e0/12.0e0)
#define	P2	0.5e0
#define	P20	(1.0e0/20.0e0)
#define	P360	(1.0e0/360.0e0)
#define	P42	(1.0e0/42.0e0)
#define	P6	(1.0e0/6.0e0)
#define	PEPS	0.00001e0
#define	PRO	206264.8062471e0
#define HA	6377397.155e0
#define HB	6356078.96325e0
#define STRBR	3
#define MITMER	12
#define MASSTAB	1.0
	/* end of PARAMETER translations */

long gaugeo (double *x, double *y, double *b, double *l) {
long int kenn;
double 	a0, a10, a2, a4, a6, a8, b1, b2, b3, b4, b5, b6, b7, bf, bh1, 
	bh2, bh3, bh4, c, co, cor, e2, eta2, eta4, g, hm, n, n2, n3, 
	n4, n5, rkenn, rl0, t, t2, v, v2, vc, vc2, xi, y2, y4, y6, yi;

/* *** Eingabeparameter testen: */
//	if (HB > HA) 
	/* kleine Halbachse grî·er als gro·e Halbachse */
//		return EACHS;
//	if (*b >= 324000.0e0) 
	/* B grî·er 90 Grad */
//		return EBREIT;
//	if (MASSTAB == 0.0e0) 
	/* Division durch 0, Vergr.-verh. falsch */
//		return EMASS;
/* *** Streifenkennzahl: */
//	if (STRBR == 3L) {
	/* 3-Grad-Streifen */
		kenn = (MITMER/3L)*1000000;
		rkenn = kenn;
//	} else if (STRBR == 6L) {
	/* 6-Grad-Streifen */
//		kenn = ((MITMER + 3L)/6L)*1000000;
//		rkenn = kenn;
//	} else
	/* falsche Sreifenbreite */
//		return ESTRBR;
/* *** X,Y berechnen: */
	xi = *x/ MASSTAB;
	yi = (*y - rkenn - 500000.0e0)/ MASSTAB;
	yi = yi/1.0e5;
	y2 = yi*yi;
	y4 = y2*y2;
	y6 = y4*y2;
/* *** Laenge Bezugsmeridian: */
	rl0 = MITMER;
	rl0 = rl0*3600.0e0;
/* *** Ausgangswerte berechnen: */
	c = (HA/ HB) * HA;
	e2 = (HA * HA - HB * HB)/(HB * HB);
/* fuer Meridianbogenlaenge: */
	hm = (HA + HB)*P2;
	n = (HA - HB)/(HA + HB);
	n2 = n*n;
	n3 = n2*n;
	n4 = n3*n;
	n5 = n4*n;
	a0 = 1.0e0 + n2/4.0e0 + n4/64.0e0;
	a2 = 3.0e0*P2*(-n + n3/8.0e0 + n5/64.0e0);
	a4 = (15.0e0/16.0e0)*(n2 - n4/4.0e0);
	a6 = (35.0e0/48.0e0)*(-n3 + (5.0e0/16.0e0)*n5);
	a8 = (315.0e0/512.0e0)*n4;
	a10 = -(693.0e0/1280.0e0)*n5;
/* *** Iteration fuer G: */
	bf = xi/a0;
L_100:
	co = cos (bf);
	eta2 = e2*co*co;
	v2 = 1.0e0 + eta2;
	v = sqrt (v2);
	vc = v/c;
	g = hm * (a0*bf + a2*sin (2.0e0*bf) + a4*sin (4.0e0*bf) + 
		  a6*sin (6.0e0*bf) + a8*sin (8.0e0*bf) + a10*sin (10.0e0*bf));
	if (fabs (xi - g) > PEPS) {
		bf = bf + (xi - g)*vc*v2;
		goto L_100;
		/*                       ! mit verbessertem BF */
	}
/* *** Anfangswerte fÅr Fu·punktbreite: */
	cor = 1.0e0/co;
	t = tan (bf);
	t2 = t*t;
	eta4 = eta2*eta2;
	vc2 = vc*vc;
/* *** Koeffizienten berechnen:
 *    --- fuer B: */
	bh1 = 1.0e10*P2*vc2*t;
	b2 = bh1*(-1.0e0 - eta2);
	b4 = 5.0e0 + 3.0e0*t2 + 6.0e0*eta2 - 3.0e0*eta4 - 6.0e0*t2*eta2;
	b4 = b4 - 9.0e0*t2*eta4;
	b4 = P12*bh1*vc2*1.0e10*b4;
	b6 = -61.0e0 - 90.0e0*t2 - 45.0e0*t2*t2 - 92.0e0*eta2;
	b6 = b6 + 147.0e0*t2*eta2 + 45.0e0*t2*t2*eta2;
	b6 = P360*bh1*vc2*1.0e10*vc2*1.0e10*b6;
/*    --- fuer L: */
	b1 = vc*1.0e5*cor;
	bh2 = P6*vc2*1.0e10*b1;
	b3 = bh2*(-1.0e0 - 2.0e0*t2 - eta2);
	bh3 = P20*bh2*vc2*1.0e10;
	b5 = 5.0e0 + 28.0e0*t2 + 24.0e0*t2*t2 + 6.0e0*eta2 + 8.0e0*t2*eta2;
	b5 = b5*bh3;
	bh4 = P42*bh3*vc2*1.0e10;
	b7 = 61.0e0 - 662.0e0*t2 - 1320.0e0*t2*t2 - 720.0e0*t2*t2*t2;
	b7 = b7*bh4;
/* *** X berechnen: */
	*b = bf + b2*y2 + b4*y4 + b6*y6;
	*b = (*b * PRO);
/* *** Y berechnen: */
	*l = b1*yi + b3*y2*yi + b5*y4*yi + b7*y6*yi;
	*l = (*l * PRO + rl0);

return EOKAY;
} /* end of function */

