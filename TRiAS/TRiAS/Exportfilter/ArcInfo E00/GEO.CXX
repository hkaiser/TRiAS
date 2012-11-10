/*
File: GEO.CXX

Berechnen von
	- Labelpunkt eines Polygons,
	- Fächeninhalt,
	- Flächen-Schwerpunkt,
	- Flächen-Umfang bzw. Länge einer Linie.

Erarbeitet: J. Benkenstein, W. Mörtl		Begonnen am: 8. Mai 1993
											Stand vom: 29. April 1996
*/

#include "stdafx.h"               

// #HK960812
	#include <float.h>				// DBL_MAX
	#include <math.h>				// sqrt ()

#include <attribs.hxx>				// VisInfo ...
#include <ristypes.hxx>				// OT_FLAECHE
#include <impexp.hxx>				// IdentDescription, GSTRUCT

#include "geo.hxx"					// zugeh. Header-File

//  Konstanten
const short DreickSize = 4;			// Anz. der Punkte für Dreieck

//  lokale Funktionen
short BewegRicht_real (double x1, double y1, double x2, double y2,
					   double x3, double y3);
					   
#ifndef __NT__
#define HUGE __huge
#else
#define HUGE
#endif					   

//  liegt Punkt in der Fläche ?
//  +1 innerhalb
//   0 auf dem Rand
//  -1 außerhalb
//  -2 Fläche ist nicht geschlossen
short Position_real (double &x, double &y,		// Punkt-Koordinaten
					 GSTRUCT &GS,				// Masche
					 long Count,				// Anz. Stützpunkte
					 long lActInd = 0);			// akt. Index

ErrCode SchwerPunkt (GSTRUCT &GS,				// beinhaltet Geoemetrie-Vektor
					 double &FlI,				// vorzeichenbeh. Flächeninhalt
					 double &Xs,				// Ergebniskoordinaten,
					 double &Ys,				// im Fehlerfall 0,0
					 long Count,				// Anzahl der Stützpunkte
					 long AktIndex) {			// aktueller Index
//  Anfangswerte setzen
	Xs = Ys = FlI = 0;

//  prüfe Parameter der Fläche
	if (Count < 4)						// wenigstens 4 Stützpunkte
		return EC_ILLPARS;
	if (((double HUGE *)GS.x) [AktIndex] != ((double HUGE *)GS.x) [AktIndex + Count - 1] ||
		((double HUGE *)GS.y) [AktIndex] != ((double HUGE *)GS.y) [AktIndex + Count - 1]) // wenn AnfPkt != EndPkt
		return EC_ILLPARS;

//  kleinste X/Y-Koordinate bestimmen
	double XMin = DBL_MAX;
	double YMin = DBL_MAX;
	long MaxIndex = AktIndex + Count;
	for (long Index = AktIndex; Index < MaxIndex; Index++) {
		if (((double HUGE *)GS.x) [Index] < XMin)
			XMin = ((double HUGE *)GS.x) [Index];
		if (((double HUGE *)GS.y) [Index] < YMin)
			YMin = ((double HUGE *)GS.y) [Index];
	}

// Schwerpunkt u. Flächeninhalt berechnen
   double Xsi, Ysi, Inh;		// Schwerpunkt-Koordinaten, Flä.-Inhalt
   MaxIndex--;						// letzte Punkt wird innerhalb der Schleife gel.
   for (long i = AktIndex;		// Punkt-Index
		i < MaxIndex; i++) {		// für alle Punkte der Folge
	//		akt. Koordinaten lesen
		double X1 = double (((double HUGE *)GS.x) [i] - XMin),
			   Y1 = double (((double HUGE *)GS.y) [i] - YMin),
			   X2 = double (((double HUGE *)GS.x) [i+1] - XMin),
			   Y2 = double (((double HUGE *)GS.y) [i+1] - YMin);

	//		Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {		   // wenn Berechnung möglich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) /
						(3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 *Y2)) /
						(3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;

		} else
			Xsi = Ysi = Inh = 0;	  // alle Werte 0 setzen

	//		Zwischenwerte aktualisieren
		Xs += Xsi * Inh;			  // Schwerpunkt
		Ys += Ysi * Inh;
		FlI += Inh;					  // Inhalt der Fläche
	}

//  Endkoordinaten berechnen
	Xs = (Xs / FlI) + XMin;
	Ys = (Ys / FlI) + YMin;

	return EC_OKAY;
}

//  Berechne die Länge eines gegebenen Vektor
double Laenge (GSTRUCT GS, long Count, long AktIndex) {
//  Prüfe Parameter
	if (Count < 2)
		return 0;

	long MaxIndex = AktIndex + Count - 1;
	double dLa = 0;
	double dTmp = 0;
	for (long i = AktIndex; i < MaxIndex; i++) {
	// = Wurzel ((x2 - x1) ^2 + (y2 - y1) ^2)
		dTmp  = (sqrt((((double HUGE *)GS.x)[i+1]*((double HUGE *)GS.x)[i+1]) + (((double HUGE *)GS.x)[i]*
			  ((double HUGE *)GS.x)[i]) - (2*(((double HUGE *)GS.x)[i+1]*((double HUGE *)GS.x)[i]))+
			  (((double HUGE *)GS.y)[i+1]*((double HUGE *)GS.y)[i+1]) + (((double HUGE *)GS.y)[i]*
			  ((double HUGE *)GS.y)[i]) - (2*(((double HUGE *)GS.y)[i+1]*((double HUGE *)GS.y)[i]))));
		if (dTmp > 0)
			dLa += dTmp;
	}
	
	return dLa;
}

/*
Berechnet den vorzeichenbehafteten Inhalt einer Fläche,
der bei einem Fehler gleich 0 ist.

Inhalt > 0 --> Verlauf der Fläche im math. positiven Drehsinn
Inhalt < 0 --> negativer Drehsinn (im Uhrzeigersinn)
Formel: Anfangswert + Summe über alle x(n) * (y(n+1) - y(n-1)) von n = 1
		bis Anzahl Punkte (AP) - 2, mit den Punkten P0, P1, ... P(AP-1) und
		dem Anfangswert = x(AP-1) * (y1 - y(AP-2))
*/
double FlInhalt  (GSTRUCT &GS,			// beinhaltet Geoemetrie-Vektor
				  long Count,			// Anzahl der Stützpunkte
				  long AktIndex) {  // aktueller Index
//  prüfe Parameter der Fläche
	if (Count < 4)					// wenigstens 4 Stützpunkte
		return 0;
	if (((double HUGE *)GS.x) [AktIndex] != ((double HUGE *)GS.x) [AktIndex + Count - 1] ||
		((double HUGE *)GS.y) [AktIndex] != ((double HUGE *)GS.y) [AktIndex + Count - 1]) // wenn AnfPkt != EndPkt
		return 0;

//  berechne Anfangswert der Fläche
	long MaxIndex = AktIndex + Count - 1;
	double Fl = ((double HUGE *)GS.x) [MaxIndex] * (((double HUGE *)GS.y) [1] - ((double HUGE *)GS.y) [MaxIndex - 1]);

//  berechne Summe
	for (long i = AktIndex ; i < MaxIndex; i++)
		Fl += ((double HUGE *)GS.x) [i] * (((double HUGE *)GS.y) [i+1] - ((double HUGE *)GS.y) [i-1]);

	return (Fl / 2);		// Inhalt halbieren und zurück
}

/* Bewegungsrichtung, wenn man bei 3 gegebenen real-Punkten vom ersten, zum
   zweiten und dann zum dritten geht; Rückgabewert ist
   +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
	  bei Kollinearität, wenn Pkt2 zwischen Pkt1 und Pkt3 liegt bzw.
	  bei Pkt1==Pkt2
   -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
	  bei Kollinearität, wenn Pkt1 zwischen Pkt3 und Pkt2 liegt
	0 bei Kollinearität, wenn Pkt3 zwischen Pkt1 und Pkt2 liegt bzw.
	  bei Pkt1==Pkt3, Pkt2==Pkt3, Pkt1==Pkt2==Pkt3  */
short BewegRicht_real (double x1, double y1, double x2, double y2,
					   double x3, double y3) {
	double dx1 = x2 - x1;
	double dy1 = y2 - y1;
	double dx2 = x3 - x1;
	double dy2 = y3 - y1;

	if (dx1*dy2 > dy1*dx2)
		return +1;
	if (dx1*dy2 < dy1*dx2)
		return -1;
	if (dx1*dx2 < 0 || dy1*dy2 < 0)
		return -1;
	if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
		return +1;
	return 0;
} // Ende BewegRicht_real

// Enthaltensein eines real-Punktes in der Fläche, die durch eine geschlossene
// Kante bzw. eine Maschenkontur gebildet wird; Rückgabewert ist
//   +1: Punkt liegt innerhalb der Fläche
//	  0: Punkt liegt auf Flächenrand
//   -1: Punkt liegt außerhalb der Fläche
//   -2: Flächenrand nicht geschlossen
// Der real-Punkt ist der Anfangspunkt einer waagrechten Testlinie, deren
// Endpunkt "unendlich" weit rechts liegt.
short Position_real (double &x, double &y,		// Punkte-Koordinaten
					 GSTRUCT &GS,				// Masche
					 long n, 					// Anz. Stützpunkte
					 long lActInd)
{					 
	if (n < 4)							// wenigstens 4 Stützpunkte
		return -2;
	if (((double HUGE *)GS.x) [lActInd] != ((double HUGE *)GS.x) [lActInd + n - 1] ||
		((double HUGE *)GS.y) [lActInd] != ((double HUGE *)GS.y) [lActInd + n - 1])   // wenn AnfPkt != EndPkt
		return -2;

	long AnzSchn = 0;		// Zähler für echte Schnitte der Testlinie mit Kante
	long j = lActInd + n-2;	// Index des letzten Konturpunktes, von dem bekannt ist, daß
							// er nicht auf der Testlinie liegt

	while (BewegRicht_real (x, y, DBL_MAX, y, ((double HUGE *)GS.x) [j], ((double HUGE *)GS.y) [j]) == 0) 
	{
		j--;
		if (j < 0)
			return -2;		// entartete Fläche, d.h. alle Punkte liegen auf einer Geraden,
							// die mit der Trägergeraden der TLinie identsch ist
	}
        
	short r1, r2, r3, r4;		// Hilfswerte für Bewegungsrichtung        
	for (long i = lActInd; i < lActInd + n-1; i++) 
	{
	//	Test, ob Punkt auf Kante liegt
		if (BewegRicht_real (((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i],
			((double HUGE *)GS.x) [i+1], ((double HUGE *)GS.y) [i+1], x, y) == 0)
			return 0;		// Punkt liegt auf Kante

		//  Im 1. Teil der nachfolgenden if-Anweisung wird der Fall
		//  behandelt, daß der nächste Stützpunkt GS[i] nicht auf
		//  der waagrechten Testlinie liegt.
		//  Liegt GS[i] auf der Testlinie (else-Zweig), wird GS[i] i.a.
		//  ignoriert. Es kann aber der Spezialfall auftreten, daß
		//  durch das Weglassen von GS[i] der zu testende Punkt
		//  scheinbar außerhalb der betrachteten Fläche liegt. Deshalb
		//  ist in diesem Fall zu klären, ob der zu testende Punkt
		//  im Dreieck GS[i-1], GS[i], GS[i+1] liegt.
		if (BewegRicht_real (x, y, DBL_MAX, y, ((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i]) != 0) {
			r1 = BewegRicht_real (((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i], 
				 ((double HUGE *)GS.x) [j],((double HUGE *)GS.y) [j], x, y);
			r2 = BewegRicht_real (((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i], 
				 ((double HUGE *)GS.x) [j], ((double HUGE *)GS.y) [j], DBL_MAX, y);
			r3 = BewegRicht_real (x, y, DBL_MAX, y, ((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i]);
			r4 = BewegRicht_real (x, y, DBL_MAX, y, ((double HUGE *)GS.x) [j], ((double HUGE *)GS.y) [j]);
			j = i;

			//		Zähler inkrementieren, wenn echter Schnitt zwischen
			//		Strecke (GS[i], GS[j]) und Teststrecke vorliegt
			if ((r1 * r2 <= 0) && (r3 * r4 <= 0))
				AnzSchn++;
		} else {		// GS[i] liegt auf der Teststrecke
			r2 = BewegRicht_real (((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i], 
				 ((double HUGE *)GS.x) [i+1], ((double HUGE *)GS.y) [i+1], x, y);
			if (i > 0) {
				r1 = BewegRicht_real (((double HUGE *)GS.x) [i-1], ((double HUGE *)GS.y) [i-1], 
					 ((double HUGE *)GS.x) [i], ((double HUGE *)GS.y) [i], x, y);
				r3 = BewegRicht_real (((double HUGE *)GS.x) [i+1], ((double HUGE *)GS.y) [i+1], 
				  	 ((double HUGE *)GS.x) [i-1], ((double HUGE *)GS.y) [i-1], x, y);
			} else {		// i = 0
				r1 = BewegRicht_real (((double HUGE *)GS.x) [lActInd + n-2], ((double HUGE *)GS.y) [lActInd + n-2], 
				  	 ((double HUGE *)GS.x) [0], ((double HUGE *)GS.y) [0], x, y);
				r3 = BewegRicht_real (((double HUGE *)GS.x) [1], ((double HUGE *)GS.y) [1], 
					 ((double HUGE *)GS.x) [lActInd + n-2], ((double HUGE *)GS.y) [lActInd + n-2], x, y);
			}

			if (r1 >= 0 && r2 >= 0 && r3 >= 0)		// Punkt liegt innerhalb
				return 1;
		}
	}

	if (AnzSchn & 1)		  // ungerader Zähler bedeutet Enthaltensein
		return +1;

		return -1;

}   // Position_real

//  Schwerpunkt ggf. korrigieren:
//		+ Test: Punkt in Fläche ? wenn ja, dann zurück
//		+ suche Punkt mit kleinsten x-Koordinate
//		+ bilden von diesem Punkt ausgehend ein Dreieck, dessen
//		+ 2. Punkt dieser Punkt ist
//		+ gebe den Schwerpunkt dieses Dreiecks als neuen Schwerpunkt zurück
void CheckLabelPoint (double &Xs, double &Ys, GSTRUCT &GS)
{
	long *pCnt = GS.cnt;	// Anzahl der Stützpunkte der äußeren Masche

//  liegt Punkt innerhalb äußerer Masche ?
	short Result = Position_real (Xs, Ys, GS, *pCnt);
	if (Result == -2)		// keine Fläche
		return;
                   
	short sIlands = 0;			                                        
//	Test: liegt Punkt innerhalb evtl. vorhandener Inseln	                                        
	if (Result == 1)		// Punkt liegt in der äußeren Masche
	{                   
		for (long lActInd = *pCnt; *++pCnt; lActInd += *pCnt)
		{	                
			sIlands++;
			if ((Result = Position_real (Xs, Ys, GS, *pCnt, lActInd)) != -1)
				break;			// Punkt liegt nicht außerhalb der Insel		
		}                                                               
	}
	
//	alles OK ?
	if (((sIlands == 0) && (Result == 1)) || 		// nur äußere Masche ex., die Label innen hat
	     ((sIlands > 0) && (Result == -1)))			// auch letzte Insel hat Label außerhalb
		return;	
                                        
//  suche kleinste x-Koordinate
	long Index = 0;
	long FoundIndex = 0;
	double Xmin = DBL_MAX;
	long Count = *GS.cnt;
	for (; Index < Count; Index++) {
		if (((double HUGE *)GS.x) [Index] < Xmin) {
			Xmin = ((double HUGE *)GS.x) [Index];
			FoundIndex = Index;
		}
	}

//  ggf. vorigen und nächsten Index korrigieren
	long NextIndex = FoundIndex == Count - 1 ? 1 : FoundIndex + 1;
	long PrevIndex = FoundIndex == 0 ? Count - 2 : FoundIndex - 1;

	double X [DreickSize];		// Vektor des zu ber. Dreiecks
	double Y [DreickSize];

//  Vektor init.
	X [1] = ((double HUGE *)GS.x) [FoundIndex];		// mittlerer Punkt ist der gefundene
	Y [1] = ((double HUGE *)GS.y) [FoundIndex];

	X [0] = X [3] = ((double HUGE *)GS.x) [PrevIndex];		// AP == EP
	Y [0] = Y [3] = ((double HUGE *)GS.y) [PrevIndex];

	X [2] = ((double HUGE *)GS.x) [NextIndex];
	Y [2] = ((double HUGE *)GS.y) [NextIndex];

	GSTRUCT NewGS;
	NewGS.x = (double *) &X;
	NewGS.y = (double *) &Y;
	double FlI = 0;

//  ber. Schwerpunkt dieses Dreiecks
	SchwerPunkt (NewGS, FlI, Xs, Ys, DreickSize);
}

void CheckLabelPoint (double &Xs, double &Ys,				// alter neuer SPunkt
		      		  double *pX, double *pY, long lCnt)
{
	if (!pX || !pY || !lCnt)
		return;

	GSTRUCT gs;
	memset (&gs, 0, sizeof (gs));
	gs.GSize = lCnt;
	gs.x = pX;
	gs.y = pY;
	gs.Typ = OT_FLAECHE;
	long Cnt [2];
	Cnt [0] = lCnt;
	Cnt [1] = 0;
	gs.cnt = Cnt;

	CheckLabelPoint (Xs, Ys, gs);
}	