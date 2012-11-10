// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 13:07:54 
//
// @doc
// @module Strecke.h | Declaration of the <c CStrecke> class

#if !defined(_STRECKE_H__6C94DA19_375E_41E2_B4C4_3B93D3A9EAC5__INCLUDED_)
#define _STRECKE_H__6C94DA19_375E_41E2_B4C4_3B93D3A9EAC5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Strecke
//	Eine Strecke ist der Teil einer Geraden zwischen einem Anfangs- und einem 
//	Endpunkt. Die Richtung verläuft vom Anfangs- zum Endpunkt
template <typename KoOrdT>
class WMStrecke
{
private:
// Datenelemente
	WMPunkt<KoOrdT> _AP;	    // Anfangspunkt
	WMPunkt<KoOrdT> _EP;	    // Endpunkt

public:
// Konstruktoren 
	WMStrecke (void);
	WMStrecke (KoOrdT Xa, KoOrdT Ya, KoOrdT Xe, KoOrdT Ye);
	WMStrecke (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP);
	~WMStrecke();

// Zugriffsfunktionen
	WMPunkt<KoOrdT> &AP();	 // lesen Anfangs- und
	WMPunkt<KoOrdT> const &AP() const;
	WMPunkt<KoOrdT> &EP();	 // Endpunkt der Strecke
	WMPunkt<KoOrdT> const &EP() const;

// Berechnung der y-Koordinate eines Punktes auf der Strecke bei gegebenem x-Wert
	bool YWert (KoOrdT x, KoOrdT &y) const;

// Die Container zweier Strecken haben wenigstens einen Punkt gemeinsam
	bool ContainerSchnitt (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP) const;
	
// Berechnung eines bzw. zweier gemeinsamer Punkte von zwei Strecken
	WMSchnittErg EpsGemeinsamePunkte (
		WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
		DoublePair &GP1, DoublePair &GP2, double dEpsX, double dEpsY) const;

// Hilfsroutinen für EpsGemeinsamePunkte()
	WMSchnittErg Gemeinsam0 (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
		DoublePair &GP1) const;
	WMSchnittErg Gemeinsam1 (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
		DoublePair &GP1, DoublePair &GP2, double dAStr, double dEStr, 
		double dAthis, double dEthis, double dEps) const;
	WMSchnittErg Gemeinsam11(WMPunkt<KoOrdT> const &AP, DoublePair &GP1, 
		DoublePair &GP2) const;
	WMSchnittErg Gemeinsam2 (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
		DoublePair &GP1, DoublePair &GP2, double dAStr, double dEStr, 
		double dAthis, double dEthis, double dEps) const;
	
// Pkt liegt auf der euklidischen Strecke einschließlich der beiden Endpunkte (true), sonst false
	bool operator == (WMPunkt<KoOrdT> const &Pkt) const;

// Länge des Lots von Punkt Pt auf die Trägergerade der this-Strecke
	bool LotPktGerade (WMPunkt<KoOrdT> const &Pt, double &d) const;
	
// Länge des Lots von Punkt Pt auf die this-Strecke
	bool LotPktStreckeM (WMPunkt<KoOrdT> const &Pt, KoOrdT &d, 
		WMPunkt<KoOrdT> &LPkt) const;
	bool LotPktStreckeE (WMPunkt<KoOrdT> const &Pt, double &d, 
		DoublePair &LPkt) const;
};

///////////////////////////////////////////////////////////////////////////////
// ursprünglich friend-Funktionen von WMStrecke
// Mittelpunkt der Strecke Pkt1-Pkt2 (als 2 double-Werte)
template <typename KoOrdT>
void Mitte (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	double &xm, double &ym);

// Teilungspunkt der Strecke DP1-DP2
template <typename KoOrdT>
void StreckenTeilung (DoublePair const &DP1, DoublePair const &DP2, 
	DoublePair &DPT, double dLambda);

// Teilungspunkt TPkt der Strecke AP-EP
template <typename KoOrdT>
bool StreckenTeilung (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
	double dTeilLaenge, WMPunkt<KoOrdT> &TPkt);

// Lotpunkt LPkt von Pkt auf Strecke AP-EP
template <typename KoOrdT>
bool LotPunkt (WMPunkt<KoOrdT> const &Pkt, WMPunkt<KoOrdT> const &AP, 
	WMPunkt<KoOrdT> const &EP, WMPunkt<KoOrdT> &LPkt);

// (absolute) Länge d des Lots von Punkt Pkt auf die Strecke AP-EP 
// (mit euklidischer Norm)
template <typename KoOrdT>
bool LotStrecke (WMPunkt<KoOrdT> const &Pkt, WMPunkt<KoOrdT> const &AP, 
	WMPunkt<KoOrdT> const &EP, double &d);

// (absolute) Länge d des Lots von Punkt DP0 auf die Strecke DP1-DP2 
// (mit euklidischer Norm)
bool LotStrecke (DoublePair const &DP0, DoublePair const &DP1, 
	DoublePair const &DP2,	double &d);

// (absoluter) double-Abstand d des Punktes DP0 von der Strecke DP1-DP2 (mit euklidischer Norm)
bool AbstandPktStrecke (DoublePair const &DP0, DoublePair const &DP1, 
	DoublePair const &DP2, double &d);

// Quasi-Winkel (Wert zwischen 0 und 360)
double QuasiWinkel (double x1, double y1, double x2, double y2);

// Lage zweier Strecken zueinander und evtl. Ermittlung der gemeinsamen Punkte
template <typename KoOrdT>
WMSchnittErg GemeinsamePunkte (
	WMPunkt<KoOrdT> const &AP1, WMPunkt<KoOrdT> const &EP1, 
	WMPunkt<KoOrdT> const &AP2,	WMPunkt<KoOrdT> const &EP2, 
	DoublePair &GP1, DoublePair &GP2);
template <typename KoOrdT>
WMSchnittErg GemeinsamePunkte (
	WMPunkt<KoOrdT> const &AP1, WMPunkt<KoOrdT> const &EP1, 
	WMPunkt<KoOrdT> const &AP2, WMPunkt<KoOrdT> const &EP2,
	WMPunkt<KoOrdT> &GP1, WMPunkt<KoOrdT> &GP2);

// Berechnung des Schnitt- oder Berührungspunktes zweier Strecken
template <typename KoOrdT>
DoublePair StreckenSchnittPunkt (
	WMPunkt<KoOrdT> const &AP1, WMPunkt<KoOrdT> const &EP1, 
	WMPunkt<KoOrdT> const &AP2, WMPunkt<KoOrdT> const &EP2);

// Berechnung des Schnittpunktes (xs,ys) zweier Geraden
bool GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
	double x12, double y12, double x22, double y22, double &xs, double &ys);
bool GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
	double x2, double y2, double dAnst, double &xs, double &ys);

// Berechnung des Lotpunktes (xl,yl) vom Punkt (xp,yp) auf eine Gerade
bool GeradenLotPunkt (double xp, double yp, double x1, double y1,
	double x2, double y2, double& xl, double& yl);

// Berechnung des Winkels, den die 3 Punkte P0(x0,y0), P1(x1,y1) und P2(x2,y2) 
// bilden
template <typename KoOrdT>
bool Winkel (KoOrdT x0, KoOrdT y0, KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2,
	double &dWinkel);

// Test, ob die beiden Punkte (x0,y0) und (y0,y1) identisch sind
//bool IdenticalPoints (double x0, double y0, double x1, double y1);

} // namespace trias_wmgeometry

#endif // !defined(_STRECKE_H__6C94DA19_375E_41E2_B4C4_3B93D3A9EAC5__INCLUDED_)
