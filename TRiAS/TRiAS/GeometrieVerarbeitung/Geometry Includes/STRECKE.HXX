// Geometrieobjekt Strecke
// File: STRECKE.HXX
// W. Mörtl

#ifndef _STRECKE_HXX
#define _STRECKE_HXX

// Strecke
//   Eine Strecke ist der Teil einer Geraden zwischen einem Anfangs- und einem Endpunkt.
//   Die Richtung verläuft vom Anfangs- zum Endpunkt
class _GEOMETR_ENTRY Strecke
{
// friend-Funktionen
// Mittelpunkt der Strecke Pkt1-Pkt2 (als 2 double-Werte)
_GEOMETR_ENTRY friend void Mitte (EPunkt& Pkt1, EPunkt& Pkt2, double& xm, double& ym);

// Teilungspunkt der Strecke DP1-DP2
_GEOMETR_ENTRY friend void StreckenTeilung (DoublePair DP1, DoublePair DP2, DoublePair& DPT,
											double dLambda);

// Teilungspunkt TPkt der Strecke AP-EP
_GEOMETR_ENTRY friend bool StreckenTeilung (EPunkt& AP, EPunkt& EP, double dTeilLaenge,
											EPunkt& TPkt);

// Lotpunkt LPkt von Pkt auf Strecke AP-EP
_GEOMETR_ENTRY friend bool LotPunkt (EPunkt& Pkt, EPunkt& AP, EPunkt& EP, EPunkt& LPkt);

// (absolute) Länge d des Lots von Punkt Pkt auf die Strecke AP-EP (mit euklidischer Norm)
_GEOMETR_ENTRY friend bool LotStrecke (EPunkt& Pkt, EPunkt& AP, EPunkt& EP, double& d);

// (absolute) Länge d des Lots von Punkt DP0 auf die Strecke DP1-DP2 (mit euklidischer Norm)
_GEOMETR_ENTRY friend bool LotStrecke (DoublePair DP0, DoublePair DP1, DoublePair DP2,
									   double& d);

// (absoluter) double-Abstand d des Punktes DP0 von der Strecke DP1-DP2 (mit euklidischer Norm)
_GEOMETR_ENTRY friend bool AbstandPktStrecke (DoublePair DP0, DoublePair DP1, DoublePair DP2,
											  double& d);

// Quasi-Winkel (Wert zwischen 0 und 360)
_GEOMETR_ENTRY friend double QuasiWinkel (double x1, double y1, double x2, double y2);

// Lage zweier Strecken zueinander und evtl. Ermittlung der gemeinsamen Punkte
_GEOMETR_ENTRY friend SchnittErg GemeinsamePunkte (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2,
												 EPunkt& EP2, DoublePair& GP1, DoublePair& GP2);
SchnittErg friend GemeinsamePunkte (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2, EPunkt& EP2,
									EPunkt& GP1, EPunkt& GP2);

// Berechnung des Schnitt- oder Berührungspunktes zweier Strecken
_GEOMETR_ENTRY friend DoublePair StreckenSchnittPunkt (EPunkt& AP1, EPunkt& EP1, EPunkt& AP2,
													   EPunkt& EP2);

// Berechnung des Schnittpunktes (xs,ys) zweier Geraden
_GEOMETR_ENTRY friend bool GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
					   double x12, double y12, double x22, double y22, double& xs, double& ys);
_GEOMETR_ENTRY friend bool GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
								   double x2, double y2, double dAnst, double& xs, double& ys);

// Berechnung des Lotpunktes (xl,yl) vom Punkt (xp,yp) auf eine Gerade
_GEOMETR_ENTRY friend bool GeradenLotPunkt (double xp, double yp, double x1, double y1,
											double x2, double y2, double& xl, double& yl);

// Berechnung des Winkels, den die 3 Punkte P0(x0,y0), P1(x1,y1) und P2(x2,y2) bilden
_GEOMETR_ENTRY friend bool Winkel (KoOrd x0, KoOrd y0, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
								   double& dWinkel);

// Test, ob die beiden Punkte (x0,y0) und (y0,y1) identisch sind
friend bool IdenticalPoints (double x0, double y0, double x1, double y1);


private:
// Datenelemente
	EPunkt _AP;	    // Anfangspunkt
	EPunkt _EP;	    // Endpunkt

public:
// Konstruktoren 
	Strecke (void) : _AP (0,0), _EP (0,0) {}			// default-Konstruktor
	Strecke (KoOrd Xa, KoOrd Ya, KoOrd Xe, KoOrd Ye)	// Koordinaten übergeben
			: _AP (Xa, Ya), _EP (Xe, Ye) {}		
	Strecke (const EPunkt& AP, const EPunkt& EP)			// Punkte direkt übergeben
			: _AP (AP), _EP (EP) {}	

// Zugriffsfunktionen
	EPunkt& AP (void) { return _AP; }	 // lesen Anfangs- und
	EPunkt& EP (void) { return _EP; }	 // Endpunkt der Strecke

// Implementierungsfunktionen
// Berechnung der y-Koordinate eines Punktes auf der Strecke bei gegebenem x-Wert
	bool YWert (KoOrd x, KoOrd& y);

// Die Container zweier Strecken haben wenigstens einen Punkt gemeinsam
	bool ContainerSchnitt (EPunkt& AP, EPunkt& EP);
	
// Berechnung eines bzw. zweier gemeinsamer Punkte von zwei Strecken
	SchnittErg EpsGemeinsamePunkte (EPunkt& AP, EPunkt& EP, DoublePair& GP1, DoublePair& GP2,
									double dEpsX, double dEpsY);

// Hilfsroutinen für EpsGemeinsamePunkte()
	SchnittErg Gemeinsam0 (EPunkt& AP, EPunkt& EP, DoublePair& GP1);
	SchnittErg Gemeinsam1 (EPunkt& AP, EPunkt& EP, DoublePair& GP1, DoublePair& GP2, double dAStr,
						   double dEStr, double dAthis, double dEthis, double dEps);
	SchnittErg Gemeinsam2 (EPunkt& AP, EPunkt& EP, DoublePair& GP1, DoublePair& GP2, double dAStr,
						   double dEStr, double dAthis, double dEthis, double dEps);
	
// Pkt liegt auf der euklidischen Strecke einschließlich der beiden Endpunkte (true), sonst false
	bool operator == (EPunkt& Pkt);

// Länge des Lots von Punkt Pt auf die Trägergerade der this-Strecke
	bool LotPktGerade (EPunkt& Pt, double& d);
	
// Länge des Lots von Punkt Pt auf die this-Strecke
	bool LotPktStrecke (EPunkt& Pt, KoOrd& d, EPunkt& LPkt);
	bool LotPktStrecke (EPunkt& Pt, double& d, DoublePair& LPkt);

// Destruktor
	~Strecke (void) {}
};

#endif // _STRECKE_HXX
