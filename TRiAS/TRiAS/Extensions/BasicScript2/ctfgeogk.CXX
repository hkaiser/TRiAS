//
//    gaugeo

#include "bscriptp.hxx"

#include <math.h>

/* 		Original Walter:
               Input:     HA     - grosse Halbachse des Ellips. in m R*8
                          HB     - kleine Halbachse des Ellips. in m R*8
                          STRBR  - Streifenbreite in Grad            I*4
                          L0     - Mittelmeridian in Grad            I*4
                          M      - Vergroesserungsverhaeltnis        R*8
                          X      - Gauss-Krueger-Hochwert in m       R*8
                          Y      - Gauss-Krueger-Rechtswert in m     R*8
               Output:    B      - geogr. Breite des Pkt. in "       R*8
                          L      - geogr. Laenge des Pkt. in "       R*8
       Aufgabenstellung, Hintergrund:
          Die Funktionen GAUGEO.f (Gauss-Krueger-Koordinaten zu
          geographischen Koordinaten) und GEOGAU.f (geographische
          Koordinaten zu Gauss-Krueger-Koordinaten) sind nach
          den Formeln von K. Hubeny: 'Isotherme Koordinatensysteme
          und konforme Abbildungen des Rotationsellipsoides',
          Mitteilungen der geodaetischen Institute der TU Graz,
          Folge 27, 1977, S.49 f. und S.213ff. programmiert.
          Die Meridianbogenlaengen werden durch Integration aus
          Koenig/Weise: 'Mathematische Grundlagen der hoeheren
          Geodaesie und Kartographie', Springer Verlag, 1951, S.19
          erhalten.
          Die geographischen Koordinaten werden B und L, die des
          Mittelmeridians L0 genannt. Die Gauss-Krueger-Koordinaten
          werden mit X (Hochwert) und Y (Rechtswert) bezeichnet.
          Beide Formeln liefern bei Hin- und Rueckrechnung bei
          unserer geographischen Breite bis zu 3 Grad Abstand vom
          Mittelmeridian eine Genauigkeit unter 0.00001 mm, bei
          6 Grad Abstand in X knapp 1mm.

          In GEOGAU werden die Koeffizienten der Potenzen von Delta L
          bei der Breite B gebildet (Glieder mit Potenzen von Delta B
          entfallen); die Meridinbogenlaenge G wird vom Aequator aus
          gerechnet.
          In GAUGEO wird bei der Fusspunktbreite BF (sie wird durch
          Iteration ermittelt) entwickelt.   				*/

// Gaugeo - Gauß/Krüger in geodätische Koordinaten ----------------------------
extern "C"
void PASCAL gaugeo (double ha, double hb, short strbr, short l0, 
		    double Hwert, double Rwert, 
		    long double *Breite, long double *Laenge)
{
long double cor,t,t2,eta4,vc2,bh1,bh2,bh3,bh4,p2,p12,p20,p42,p360,p6;
long double peps,v,co,e2,g,bf,eta2,hm,v2,vc,c;
long double n,n2,n3,n4,n5;
long double A[6];
long double kennz,xi,yi,y2,y4,y6,rl0,m;
long double PRO,B[7];

	m = 1.0;
	PRO = 206264.8062471;
	kennz = ((l0+(strbr-3))/strbr)*1000000;		// Streifenkennzahl
	p2 = 0.5;

//     *** X,Y berechnen:

        xi = Hwert/m;
        yi = (Rwert-kennz-500000.0)/(m*100000.0);
        y2 = yi*yi;
        y4 = y2*y2;
        y6 = y4*y2;

//    *** Laenge Bezugsmeridian:

        rl0 = l0;
	rl0 = rl0*3600.0;

//
//     Startwerte
//
	n = (ha-hb)/(ha+hb);
	n2 = n*n;
	n3 = n2*n;
	n4 = n3*n;
	n5 = n4*n;
	A[0] = 1.0+n2/4.0+n4/64.0;
	A[1] = 3.0*p2*(-n+n3/8.0+n5/64.0);
	A[2] = (15.0/16.0)*(n2-n4/4.0);
	A[3] = (35.0/48.0)*(-n3+(5.0/16.0)*n5);
	A[4] = (315.0/512.0)*n4;
	A[5] = -(693.0/1280.0)*n5;

//
//	Iteration fuer G
//

	peps = 0.00001;

/*     *** Ausgangswerte berechnen: 					*/

	c = (ha/hb)*ha;
	e2 = (ha*ha-hb*hb)/(hb*hb);

/*                        fuer Meridianbogenlaenge:  			*/
	hm = (ha+hb)*p2;

//	Anfangsbedingungen

	g = 0.0;
	bf = 0.0;
	v2 = 1.0;
	vc = 1.0/A[0];
	while ((fabsl (xi-g)) > peps) {
		bf = bf+(xi-g)*vc*v2;
		co = cosl (bf);
        	eta2 = e2*co*co;
        	v2 = 1.0+eta2;
        	v = sqrtl (v2);
        	vc = v/c;
        	g = A[0]*bf+A[1]*sinl(2.0*bf)+A[2]*sinl(4.0*bf);
        	g = g+A[3]*sinl(6.0*bf)+A[4]*sinl(8.0*bf)+A[5]*sinl(10.0*bf);
        	g = hm*g;
	}

//      Anfangswerte fuer Fusspunktbreite,Koeff. berechnen
//	Koeffizienten

	p2 = 1.0/2.0;
	p6 = 1.0/6.0;
	p12 = 1.0/12.0;
	p20 = 1.0/20.0;
	p42 = 1.0/42.0;
	p360 = 1.0/360.0;

/*      Anfangswerte fuer Fußpunktbreite:    */

        cor = 1.0/co;
        t = tanl (bf);
        t2 = t*t;
        eta4 = eta2*eta2;
        vc2 = vc*vc;

/*      Koeffizienten berechnen für B:				*/

        bh1 = 10000000000.0*p2*vc2*t;
        B[1] = bh1 * (-1.0 - eta2);
        B[3] = 5.0 + 3.0*t2 + 6.0*eta2 - 3.0*eta4 - 6.0*t2*eta2;
        B[3] = B[3] - 9.0*t2*eta4;
        B[3] = p12*bh1*vc2*10000000000.0*B[3];
        B[5] = -61.0 - 90.0*t2 - 45.0*t2*t2 - 92.0*eta2;
        B[5] = B[5] + 147.0*t2*eta2 + 45.0*t2*t2*eta2;
        B[5] = p360*bh1*vc2*10000000000.0*vc2*10000000000.0*B[5];

/*      Koeffizienten berechnen für L  				*/

        B[0] = vc*100000.0*cor;
        bh2 = p6*vc2*10000000000.0*B[0];
        B[2] = bh2 * (-1.0 - 2.0*t2 - eta2);
        bh3 = p20*bh2*vc2*10000000000.0;
        B[4] = 5.0 + 28.0*t2 + 24.0*t2*t2 + 6.0*eta2 + 8.0*t2*eta2;
        B[4] = B[4]*bh3;
        bh4 = p42*bh3*vc2*10000000000.0;
        B[6] = 61.0 - 662.0*t2 - 1320.0*t2*t2 - 720.0*t2*t2*t2;
        B[6] = B[6]*bh4;

// Hochwert (X)berechnen:

        *Breite = (bf + B[1]*y2 + B[3]*y4 + B[5]*y6) * PRO;

// RechtsWert (Y) berechnen:

//      *Laenge = (B[0]*yi+B[2]*y2*yi+B[4]*y4*yi+B[6]*y6*yi)*PRO+rl0;
	*Laenge = (B[0] + B[2]*y2 + B[4]*y4 + B[6]*y6) * yi * PRO + rl0;
}

// Geodätische Koordinaten in Gauß/Krüger -------------------------------------
extern "C"
void PASCAL geogau (double ha, double hb, short strbr, short l0, 
		    double Breite, double Laenge, 
		    long double *Hwert, long double *Rwert)
{
long double t,t2,eta4,v2,bh1,bh2,bh3,bh4,p2,p12,p20,p42,p30,p6;
long double v,co,co2,e2,g,eta2,hm,cv,c;
long double n,n2,n3,n4,n5;
long double A[6];
long double kennz,rl0,m,db,dl,dl2,dl4,dl6;
long double PRO,B[7];

	m = 1.0;
	PRO = 206264.8062471;

//
//	Koeffizienten
//
	p2 = 1.0/2.0;
	p6 = 1.0/6.0;
	p12 = 1.0/12.0;
	p20 = 1.0/20.0;
	p42 = 1.0/42.0;
	p30 = 1.0/30.0;

// *** Delta B und Delta L berechnen (im Bogenmass):

        db = Breite/PRO;
        rl0 = l0;
        rl0 = rl0*3600.0;
        dl = (Laenge-rl0)/PRO;
        dl2 = dl*dl;
        dl4 = dl2*dl2;
        dl6 = dl4*dl2;

// StreifenKennzahl
	kennz = ((l0+(strbr-3))/strbr)*1000000;

/* Ausgangswerte berechnen: 					*/

	c = (ha/hb)*ha;
	e2 = (ha*ha-hb*hb)/(hb*hb);

/* Meridianbogenlaenge:  			*/

	hm = (ha+hb)*p2;

// Startwerte
	n = (ha-hb)/(ha+hb);
	n2 = n*n;
	n3 = n2*n;
	n4 = n3*n;
	n5 = n4*n;

	A[0] = 1.0+n2/4.0+n4/64.0;
	A[1] = 3.0*p2*(-n+n3/8.0+n5/64.0);
	A[2] = (15.0/16.0)*(n2-n4/4.0);
	A[3] = (35.0/48.0)*(-n3+(5.0/16.0)*n5);
	A[4] = (315.0/512.0)*n4;
	A[5] = -(693.0/1280.0)*n5;

        g = A[0]*db + A[1]*sinl(2.0*db) + A[2]*sinl(4.0*db);
        g += A[3]*sinl(6.0*db) + A[4]*sinl(8.0*db) + A[5]*sinl(10.0*db);
        g *= hm;

// für gegebene Breite

        co = cosl (Breite/PRO);
        co2 = co*co;
        t = tanl (Breite/PRO);
        t2 = t*t;
        eta2 = e2*co2;
        eta4 = eta2*eta2;
        v2 = 1.0+eta2;
        v = sqrtl (v2);
        cv = c/v;

// Koeffizienten für X berechnen:

        B[1] = p2*cv*t*co2;
        bh1 = p12*B[1]*co2;
        B[3] = bh1* (5.0 - t2 + 9.0*eta2 + 4.0*eta4);
        B[5] = p30*bh1*co2* (61.0 - 58.0*t2 + t2*t2);

// Koeffizienten für Y berechnen

        B[0] = cv*co;
        bh2 = p6*B[0]*co2;
        B[2] = bh2 * (1.0 - t2 + eta2);
        bh3 = p20*bh2*co2;
        B[4] = bh3 * (5.0 - 18.0*t2 + t2*t2+ 14.0*eta2 - 58.0*t2*eta2);
        bh4 = p42*bh3*co2;
        B[6] = bh4 * (61.0 - 479.0*t2 + 179.0*t2*t2 - t2*t2*t2);

// Hochwert (X) berechnen:

	*Hwert = (g + B[1]*dl2 + B[3]*dl4 + B[5]*dl6) * m;

// Rechtwert (Y) berechnen:

//	*Rwert = (B[0]*dl+B[2]*dl2*dl+B[4]*dl4*dl+B[6]*dl6*dl)*m;
	*Rwert = (B[0] + B[2]*dl2 + B[4]*dl4 + B[6]*dl6) * dl * m;
	*Rwert += 500000.0+kennz;
}
