// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 13:09:03 
//
// @doc
// @module Strecke.inl | Declaration of the <c CStrecke> class

#if !defined(_STRECKE_INL__1688CD4C_15D7_4884_9E21_A40DC837D0CA__INCLUDED_)
#define _STRECKE_INL__1688CD4C_15D7_4884_9E21_A40DC837D0CA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
//	Strecke
//	Eine Strecke ist der Teil einer Geraden zwischen einem Anfangs- und einem 
//	Endpunkt. Die Richtung verläuft vom Anfangs- zum Endpunkt
///////////////////////////////////////////////////////////////////////////////
template <typename KoOrdT>
inline 
WMStrecke<KoOrdT>::WMStrecke() :
	_AP(0, 0), _EP(0, 0)
{
}

template <typename KoOrdT>
inline 
WMStrecke<KoOrdT>::WMStrecke (KoOrdT Xa, KoOrdT Ya, KoOrdT Xe, KoOrdT Ye) :
	_AP(Xa, Ya), _EP(Xe, Ye)
{
}

template <typename KoOrdT>
inline 
WMStrecke<KoOrdT>::WMStrecke (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP) :
	_AP(AP), _EP(EP)
{
}

template <typename KoOrdT>
inline 
WMStrecke<KoOrdT>::~WMStrecke()
{
}

// Zugriffsfunktionen
template <typename KoOrdT>
inline WMPunkt<KoOrdT> &
WMStrecke<KoOrdT>::AP()
{
	return _AP;
}

template <typename KoOrdT>
inline WMPunkt<KoOrdT> const &
WMStrecke<KoOrdT>::AP() const
{
	return _AP;
}

template <typename KoOrdT>
inline WMPunkt<KoOrdT> &
WMStrecke<KoOrdT>::EP()
{
	return _EP;
}

template <typename KoOrdT>
inline WMPunkt<KoOrdT> const &
WMStrecke<KoOrdT>::EP() const
{
	return _EP;
}

// Berechnung der y-Koordinate eines Punktes auf der Strecke bei gegebenem 
// x-Wert. true, wenn Koordinate berechenbar, sonst false
template <typename KoOrdT>
inline bool 
WMStrecke<KoOrdT>::YWert (KoOrdT x, KoOrdT &y) const
{
KoOrdT x1 = _AP.X();
KoOrdT y1 = _AP.Y();
KoOrdT x2 = _EP.X();
KoOrdT y2 = _EP.Y();

	if (x < min(x1, x2) || x > max(x1, x2))
		return false;

	if (x1 == x2)
		y = y1;
	else
		y = DtoL((double)(x - x1) * (double)(y2 - y1) / (double)(x2 - x1)) + y1;
	return true;
}

// Die Container zweier Strecken (this-Strecke und die durch Anfangspunkt AP 
// und Endpunkt EP definierte Strecke) haben wenigstens einen Punkt gemeinsam 
// (true), sonst false
template <typename KoOrdT>
inline bool 
WMStrecke<KoOrdT>::ContainerSchnitt (WMPunkt<KoOrdT> const &AP, 
	WMPunkt<KoOrdT> const &EP) const
{
KoOrdT xmin1 = min (_AP.X(), _EP.X());	// min. x-Koordinate,
KoOrdT xmax1 = max (_AP.X(), _EP.X());	// max. x-Koordinate,
KoOrdT ymin1 = min (_AP.Y(), _EP.Y());	// min. y-Koordinate,
KoOrdT ymax1 = max (_AP.Y(), _EP.Y());	// max. y-Koordinate des Containers der this-Strecke
KoOrdT xmin2 = min (AP.X(), EP.X());
KoOrdT xmax2 = max (AP.X(), EP.X());
KoOrdT ymin2 = min (AP.Y(), EP.Y());
KoOrdT ymax2 = max (AP.Y(), EP.Y());

	return xmax1 >= xmin2 && xmax2 >= xmin1 && ymax1 >= ymin2 && ymax2 >= ymin1;
}
	
// Berechnung eines bzw. zweier gemeinsamer Punkte von zwei Strecken (this-
// Strecke und die durch Anfangspunkt AP und Endpunkt EP definierte Strecke) 
// unter Berücksichtigung einer möglichen
// Epsilon-Abweichung; return-Werte sind
//   KEINE      Strecken schneiden sich nicht, GP1 und GP2 unbestimmt
//   ECHT       Strecken schneiden sich, GP1 enthält Schnittpunkt, GP2 
//				unbestimmt
//   RAND       Strecken berühren sich in jeweils genau einem Endpunkt, GP1 
//				enthält Berührungspunkt, GP2 unbestimmt
//   INNEN      Endpunkt der einen Strecke liegt im "Inneren" der anderen 
//				Strecke, GP1 enthält Berührungspunkt, GP2 unbestimmt
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander, GP1 
//				und GP2 sind die beiden Endpunkte des gemeinsamen Bereiches
template <typename KoOrdT>
inline WMSchnittErg 
WMStrecke<KoOrdT>::EpsGemeinsamePunkte (
	WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
	DoublePair &GP1, DoublePair &GP2, double dEpsX, double dEpsY) const
{
double dEps = max(dEpsX, dEpsY);	// 28.01.98

	if (_AP.EpsGleich(_EP, dEpsX, dEpsY, false) || 
		AP.EpsGleich(EP, dEpsX, dEpsY, false))	// 28.01.98
	{
		return KEINE;	// eine der beiden Strecken ist Eps-entartet
	}

// ein echter Schnitt geht vor allen anderen Tests (09.02.98)
	if (ECHT == Gemeinsam0 (AP, EP, GP1))
		return ECHT;
		
double dAStr;	// Abstand von _AP zur Strecke Str
double dEStr;	// Abstand von _EP zur Strecke Str
double dAthis;	// Abstand von AP zur this-Strecke
double dEthis;	// Abstand von EP zur this-Strecke

	AbstandPktStrecke (DoublePair(_AP.X(),_AP.Y()), DoublePair(AP.X(), AP.Y()),
		DoublePair(EP.X(),EP.Y()), dAStr);
	AbstandPktStrecke (DoublePair(_EP.X(),_EP.Y()), DoublePair(AP.X(), AP.Y()),
		DoublePair(EP.X(),EP.Y()), dEStr);
	AbstandPktStrecke (DoublePair(AP.X(),AP.Y()), DoublePair(_AP.X(), _AP.Y()),
		DoublePair(_EP.X(),_EP.Y()), dAthis);
	AbstandPktStrecke (DoublePair(EP.X(),EP.Y()), DoublePair(_AP.X(), _AP.Y()),
		DoublePair(_EP.X(),_EP.Y()), dEthis);

int iAnz = 0;		// Anzahl der Abstände, die höchstens dEps sind

	if (dAStr <= dEps) iAnz++;
	if (dEStr <= dEps) iAnz++;
	if (dAthis <= dEps) iAnz++;
	if (dEthis <= dEps) iAnz++;

	switch (iAnz) {
	case 0:	// Strecken schneiden sich nicht (KEINE) oder richtig (ECHT)
			// ECHT w.o. (09.02.98)
		return KEINE;

	case 1:	// Innenberührung (INNEN) oder Überlappung (UEBERLAPP)
		return Gemeinsam1 (AP, EP, GP1, GP2, dAStr, dEStr, dAthis, dEthis, dEps);

	case 2:	// Randberührung (RAND) oder Überlappung (UEBERLAPP)
		return Gemeinsam2 (AP, EP, GP1, GP2, dAStr, dEStr, dAthis, dEthis, dEps);

	case 3:	// Überlappung (UEBERLAPP)
		if (dAStr > dEps || dEStr > dEps) {
			GP1.X() = AP.X();
			GP1.Y() = AP.Y();
			GP2.X() = EP.X();
			GP2.Y() = EP.Y();
			return UEBERLAPP;
		}

	// dAthis > dEps oder dEthis > dEps
		GP1.X() = _AP.X();
		GP1.Y() = _AP.Y();
		GP2.X() = _EP.X();
		GP2.Y() = _EP.Y();
		return UEBERLAPP;
		
	case 4:	// Überlappung (UEBERLAPP)
		GP1.X() = _AP.X();
		GP1.Y() = _AP.Y();
		GP2.X() = _EP.X();
		GP2.Y() = _EP.Y();
		return UEBERLAPP;
	}
	
// Fehlerhafter Parameter in Routine Strecke::EpsGemeinsamePunkte
	_ASSERTE(false);
	return KEINE;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
}

// Hilfsroutine für EpsGemeinsamePunkte(), wenn keine der Abstände höchstens 
// dEps lang ist
template <typename KoOrdT>
inline WMSchnittErg 
WMStrecke<KoOrdT>::Gemeinsam0 (WMPunkt<KoOrdT> const &AP, 
	WMPunkt<KoOrdT> const &EP, DoublePair &GP1) const
{
	if ((TurnDirection(_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), AP.X(), AP.Y()) *
		 TurnDirection(_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), EP.X(), EP.Y()) > 0) ||
	    (TurnDirection(AP.X(), AP.Y(), EP.X(), EP.Y(), _AP.X(), _AP.Y()) *
		 TurnDirection(AP.X(), AP.Y(), EP.X(), EP.Y(), _EP.X(), _EP.Y()) > 0))
	{
		return KEINE;
	}
	GP1 = StreckenSchnittPunkt (_AP, _EP, AP, EP);
	return ECHT;
}

// Hilfsroutine für EpsGemeinsamePunkte(), wenn genau ein Abstand höchstens 
// dEps lang ist
template <typename KoOrdT>
inline WMSchnittErg 
WMStrecke<KoOrdT>::Gemeinsam11(
	WMPunkt<KoOrdT> const &AP, DoublePair &GP1, DoublePair &GP2) const
{
double dx = GP1.X() - AP.X();
double dy = GP1.Y() - AP.Y();

// das Radizieren auf beiden Seiten spare ich mir
	if (dx*dx + dy*dy <= 2.*dEps*dEps) {
		GP1.X() = AP.X();
		GP1.Y() = AP.Y();
		return INNEN;
	}
	GP2.X() = AP.X();
	GP2.Y() = AP.Y();
	return UEBERLAPP;
}

template <typename KoOrdT>
inline WMSchnittErg 
WMStrecke<KoOrdT>::Gemeinsam1 (
	WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
	DoublePair &GP1, DoublePair &GP2, double dAStr, double dEStr, 
	double dAthis, double dEthis, double dEps) const
{
	if ((TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), AP.X(), AP.Y()) *
		 TurnDirection (_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), EP.X(), EP.Y()) > 0) ||
	    (TurnDirection (AP.X(), AP.Y(), EP.X(), EP.Y(), _AP.X(), _AP.Y()) *
		 TurnDirection (AP.X(), AP.Y(), EP.X(), EP.Y(), _EP.X(), _EP.Y()) > 0))
	{
	// gemeinsamer Punkt zwischen Str1- und Str2-Strecke
		if (dAStr <= dEps) {
			GP1.X() = _AP.X();
			GP1.Y() = _AP.Y();
			return INNEN;
		}
		if (dEStr <= dEps) {
			GP1.X() = _EP.X();
			GP1.Y() = _EP.Y();
			return INNEN;
		}
		if (dAthis <= dEps) {
			GP1.X() = AP.X();
			GP1.Y() = AP.Y();
			return INNEN;
		}
	
	// es bleibt nur noch dEthis <= dEps
		_ASSERTE(dEthis <= dEps);
		GP1.X() = EP.X();
		GP1.Y() = EP.Y();
		return INNEN;
	}
	
// Str1- und Str2-Strecke haben einen gemeinsamen Punkt
	GP1 = StreckenSchnittPunkt (_AP, _EP, AP, EP);	// gemeinsamer Punkt beider Strecken
	if (dAStr <= dEps) 
		return Gemeinsam11(_AP, GP1, GP2);

	if (dEStr <= dEps) 
		return Gemeinsam11(_EP, GP1, GP2);

	if (dAthis <= dEps)	
		return Gemeinsam11(AP, GP1, GP2);

// es bleibt nur noch dEthis <= dEps
	_ASSERTE(dEthis <= dEps);
	return Gemeinsam11(EP, GP1, GP2);
}

// Hilfsroutine für EpsGemeinsamePunkte(), wenn genau zwei Abstände höchstens 
// dEps lang ist
template <typename KoOrdT>
inline WMSchnittErg 
WMStrecke<KoOrdT>::Gemeinsam2 (
	WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
	DoublePair &GP1, DoublePair &GP2, double dAStr, double dEStr, 
	double dAthis, double dEthis, double dEps) const
{
	if (dAStr <= dEps) {
		GP1.X() = _AP.X();
		GP1.Y() = _AP.Y();
		if (_AP.EpsGleich (AP, dEps, dEps) || _AP.EpsGleich (EP, dEps, dEps))
			return RAND;

		if (dEStr <= dEps) {
			GP2.X() = _EP.X();
			GP2.Y() = _EP.Y();
			return UEBERLAPP;
		}
		if (dAthis <= dEps) {
			GP2.X() = AP.X();
			GP2.Y() = AP.Y();
			return UEBERLAPP;
		}
	
	// es bleibt nur noch dEthis <= dEps
		_ASSERTE(dEthis <= dEps);
		GP2.X() = EP.X();
		GP2.Y() = EP.Y();
		return UEBERLAPP;
	}

	if (dEStr <= dEps) {
		GP1.X() = _EP.X();
		GP1.Y() = _EP.Y();
		if (_EP.EpsGleich (AP, dEps, dEps) || _EP.EpsGleich (EP, dEps, dEps))
			return RAND;

		if (dAStr <= dEps) {
			GP2.X() = _AP.X();
			GP2.Y() = _AP.Y();
			return UEBERLAPP;
		}
		if (dAthis <= dEps) {
			GP2.X() = AP.X();
			GP2.Y() = AP.Y();
			return UEBERLAPP;
		}
	
	// es bleibt nur noch dEthis <= dEps
		_ASSERTE(dEthis <= dEps);
		GP2.X() = EP.X();
		GP2.Y() = EP.Y();
		return UEBERLAPP;
	}

	if (dAthis <= dEps) {
		GP1.X() = AP.X();
		GP1.Y() = AP.Y();
		if (AP.EpsGleich (_AP, dEps, dEps) || AP.EpsGleich (_EP, dEps, dEps))
			return RAND;

		if (dEthis <= dEps) {
			GP2.X() = EP.X();
			GP2.Y() = EP.Y();
			return UEBERLAPP;
		}
		if (dAStr <= dEps) {
			GP2.X() = _AP.X();
			GP2.Y() = _AP.Y();
			return UEBERLAPP;
		}
	
	// es bleibt nur noch dEStr <= dEps
		_ASSERTE(dEStr <= dEps);
		GP2.X() = _EP.X();
		GP2.Y() = _EP.Y();
		return UEBERLAPP;
	}

// es bleibt nur noch dEthis <= dEps
	_ASSERTE(dEthis <= dEps);
	GP1.X() = EP.X();
	GP1.Y() = EP.Y();
	if (EP.EpsGleich (_AP, dEps, dEps) || EP.EpsGleich (_EP, dEps, dEps))
		return RAND;

	if (dAthis <= dEps)	{
		GP2.X() = AP.X();
		GP2.Y() = AP.Y();
		return UEBERLAPP;
	}
	if (dAStr <= dEps) {
		GP2.X() = _AP.X();
		GP2.Y() = _AP.Y();
		return UEBERLAPP;
	}

// es bleibt nur noch dEStr <= dEps
	_ASSERTE(dEStr <= dEps)
	GP2.X() = _EP.X();
	GP2.Y() = _EP.Y();
	return UEBERLAPP;
}
	
// Pkt liegt auf der euklidischen Strecke einschließlich der beiden Endpunkte 
// (true), sonst false, für Anfangs- und Endpunkt der Strecke sowie fraglichen 
// Punkt muß gelten TurnDirection (AP, EP, Pkt) == 0, dies impliziert die 
// Kollinearität
template <typename KoOrdT>
inline bool 
WMStrecke<KoOrdT>::operator== (WMPunkt<KoOrdT> const &Pkt) const
{
	return 0 == TurnDirection(_AP.X(), _AP.Y(), _EP.X(), _EP.Y(), Pkt.X(), Pkt.Y());
}

// (absolute) Länge d des Lots von Punkt Pt auf die Trägergerade der this-
// Strecke. Wird true zurückgegeben, dann ist der Abstand zur Trägergeraden der 
// this-Strecke bestimmbar, bei false ist die this-Strecke entartet (Anfangs- 
// und Endpunkt fallen zusammen). d ist dabei unbestimmt.
template <typename KoOrdT>
inline bool 
WMStrecke<KoOrdT>::LotPktGerade (WMPunkt<KoOrdT> const &Pt, double &d) const
{
	if (Pt == _AP || Pt == _EP)	{
		d = 0.0;
		return true;
	}

// Koordinaten des Lotpunktes von Pt auf die Trägergerade der this-Strecke
double xl, yl;	

	if (!GeradenLotPunkt(Pt.X(), Pt.Y(), _AP.X(), _AP.Y(), _EP.X(), _EP.Y(), xl, yl))
		return false;

double dx = Pt.X() - xl;
double dy = Pt.Y() - yl;

	d = sqrt(dx*dx + dy*dy);
	return true;
}

// (absolute) Länge d des Lots von Punkt Pt auf die this-Strecke (mit Maximum-
// Norm). Wird true zurückgegeben, dann ist der Abstand zur this-Strecke 
// bestimmbar, bei false gilt der berechnete Abstand nur für die Trägergerade, 
// nicht aber für die Strecke. Ist die this-Strecke entartet (Anfangs- und 
// Endpunkt fallen zusammen), wird ebenfalls false zurückgegeben. d ist dabei 
// negativ. In LPkt wird der Lotpunkt von Pt auf Trägergerade der this-Strecke 
// zurückgegeben.
template <typename KoOrdT>
inline bool 
WMStrecke<KoOrdT>::LotPktStreckeM (
	WMPunkt<KoOrdT> const &Pt, KoOrdT &d, WMPunkt<KoOrdT> &LPkt) const
{
	if (Pt == _AP) {
		d = 0;
		LPkt = _AP;
		return true;
	}
	if (Pt == _EP) {
		d = 0;
		LPkt = _EP;
		return true;
	}

// Koordinaten des Lotpunktes von Pt auf die Trägergerade der this-Strecke
double xl, yl;

	if (!GeradenLotPunkt (Pt.X(), Pt.Y(), _AP.X(), _AP.Y(), _EP.X(), 
			_EP.Y(), xl, yl))
	{
		d = -1;
		return false;
	}

double dx = fabs (Pt.X() - xl);
double dy = fabs (Pt.Y() - yl);

	if (dx > dy) 
		d = DtoL(dx);
	else 
		d = DtoL(dy);

	LPkt.X() = DtoL(xl);
	LPkt.Y() = DtoL(yl);

	if (_AP.X() == _EP.X() &&	// senkrechte Strecke (28.07.98)
		min(_AP.Y(), _EP.Y()) <= LPkt.Y() && 
			LPkt.Y() <= max (_AP.Y(), _EP.Y()))
	{
		return true;
	}
	if (_AP.Y() == _EP.Y() &&	// waagrechte Strecke
		min(_AP.X(), _EP.X()) <= LPkt.X() && 
			LPkt.X() <= max (_AP.X(), _EP.X()))
	{
		return true;
	}

// Normalfall (schräge Strecke)
	if (min(_AP.X(), _EP.X()) <= LPkt.X() && 
			LPkt.X() <= max(_AP.X(), _EP.X()) &&
		min(_AP.Y(), _EP.Y()) <= LPkt.Y() && 
			LPkt.Y() <= max(_AP.Y(), _EP.Y()))
	{
		return true;
	}
	return false;
}

// (absolute) Länge d des Lots von Punkt Pt auf die this-Strecke (mit 
// euklidischer Norm);
// Wird true zurückgegeben, dann ist der Abstand zur this-Strecke bestimmbar, 
// bei false gilt der berechnete Abstand nur für die Trägergerade, nicht aber 
// für die Strecke. Ist die this-Strecke entartet (Anfangs- und Endpunkt fallen 
// zusammen), wird ebenfalls false zurückgegeben. d ist dabei negativ.
// In LPkt werden die Koordinaten im double-Format des Lotpunktes von Pt auf 
// Trägergerade der this-Strecke zurückgegeben.
template <typename KoOrdT>
inline bool 
WMStrecke<KoOrdT>::LotPktStreckeE (
	WMPunkt<KoOrdT> const &Pt, double &d, DoublePair &LPkt) const
{
	if (Pt == _AP) {
		d = 0.0;
		LPkt.X() = _AP.X();
		LPkt.Y() = _AP.Y();
		return true;
	}

	if (Pt == _EP) {
		d = 0.0;
		LPkt.X() = _EP.X();
		LPkt.Y() = _EP.Y();
		return true;
	}

	if (!GeradenLotPunkt(Pt.X(), Pt.Y(), _AP.X(), _AP.Y(), _EP.X(), _EP.Y(),
			LPkt.X(),LPkt.Y()))
	{
		d = -1.;
		return false;
	}

double dx = LPkt.X() - Pt.X();
double dy = LPkt.Y() - Pt.Y();

	d = sqrt(dx*dx + dy*dy);

	if (_AP.X() == _EP.X() &&	// senkrechte Strecke (28.07.98)
		min(_AP.Y(), _EP.Y()) <= LPkt.Y() && 
			LPkt.Y() <= max(_AP.Y(), _EP.Y()))
	{
		return true;
	}

	if (_AP.Y() == _EP.Y() &&	// waagrechte Strecke
		min(_AP.X(), _EP.X()) <= LPkt.X() && 
			LPkt.X() <= max(_AP.X(), _EP.X()))
	{
		return true;
	}

// Normalfall (schräge Strecke)
	if (min(_AP.X(), _EP.X()) <= LPkt.X() && 
			LPkt.X() <= max(_AP.X(), _EP.X()) &&
		min(_AP.Y(), _EP.Y()) <= LPkt.Y() && 
			LPkt.Y() <= max(_AP.Y(), _EP.Y()))
	{
		return true;
	}
	return false;
} 

///////////////////////////////////////////////////////////////////////////////
// ursprünglich friend-Funktionen von WMStrecke
// Mittelpunkt der Strecke Pkt1-Pkt2 (als 2 double-Werte)
template <typename KoOrdT>
inline void 
Mitte (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	double &xm, double &ym)
{
double x1 = Pkt1.X();
double y1 = Pkt1.Y();
double x2 = Pkt2.X();
double y2 = Pkt2.Y();

	xm = (x1 + x2) / 2.;
	ym = (y1 + y2) / 2.;
}

// Koordinaten des Teilungspunktes DPT der Strecke DP1-DP2, der die Strecke
// im Verhältnis m:n = dLambda teilt
template <typename KoOrdT>
inline void 
StreckenTeilung (DoublePair const &DP1, DoublePair const &DP2, 
	DoublePair &DPT, double dLambda)
{
double x1 = DP1.X();
double y1 = DP1.Y();
double x2 = DP2.X();
double y2 = DP2.Y();

	DPT.X() = (x1 + dLambda*x2) / (1.0 + dLambda);
	DPT.Y() = (y1 + dLambda*y2) / (1.0 + dLambda);
}

// Durch Anfangspunkt AP und Endpunkt EP ist eine Strecke gegeben. Gesucht ist 
// ein auf dieser Strecke liegender Punkt TPkt, der von AP eine Entfernung von 
// dTeilLaenge hat. Ist Streckenlänge == 0 oder dTeilLaenge > Streckenlänge, 
// wird false zurückgegeben, sonst true.
template <typename KoOrdT>
inline bool 
StreckenTeilung (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, 
	double dTeilLaenge, WMPunkt<KoOrdT> &TPkt)
{
double dStrLaenge = AbstandPktPktE(AP, EP);	// Länge der Strecke AP-EP

	if (dStrLaenge == 0 ||			// entartete Strecke
		dTeilLaenge > dStrLaenge)	// Teilstrecke zu lang, d.h. Strecke kann nicht geteilt werden
	{
		return false;
	}

	if (dTeilLaenge == 0) {
		TPkt = AP;
		return true;
	}
	if (dTeilLaenge == dStrLaenge) {
		TPkt = EP;
		return true;
	}

double m = dTeilLaenge;					// m und n stehen für das Verhältnis, in dem
double n = dStrLaenge - dTeilLaenge;	//  die Streckenlänge geteilt werden soll

	TPkt.X() = DtoL((AP.X() * n + EP.X() * m) / dStrLaenge);
	TPkt.Y() = DtoL((AP.Y() * n + EP.Y() * m) / dStrLaenge);
	return true;
} 

// Lotpunkt LPkt ermitteln, der sich ergibt, wenn von Pkt auf die Strecke AP-EP 
// das Lot gefällt wird. Wird true zurückgegeben, dann liegt der Lotpunkt auf 
// der Strecke (einschl. Anfangs- und Endpunkt), bei false liegt der Lotpunkt 
// nur auf der Trägergerade, nicht aber auf der Strecke. Ist die Strecke 
// entartet (Anfangs- und Endpunkt fallen zusammen), wird ebenfalls
// false zurückgegeben.
template <typename KoOrdT>
inline bool 
LotPunkt (WMPunkt<KoOrdT> const&Pkt, WMPunkt<KoOrdT> const&AP, 
	WMPunkt<KoOrdT> const &EP, WMPunkt<KoOrdT> &LPkt)
{
	if (Pkt == AP) {
		LPkt = AP;
		return true;
	}
	if (Pkt == EP) {
		LPkt = EP;
		return true;
	}

// Koordinaten des Lotpunktes von Pkt auf die Trägergerade der Strecke AP-EP
double xl, yl;	

	if (!GeradenLotPunkt (Pkt.X(), Pkt.Y(), AP.X(), AP.Y(), EP.X(), EP.Y(), 
			xl, yl))
	{
		return false;
	}

	LPkt.X() = DtoL(xl);
	LPkt.Y() = DtoL(yl);

	if (AP.X() == EP.X() &&	// senkrechte Strecke (28.07.98)
		min(AP.Y(), EP.Y()) <= LPkt.Y() && 
			LPkt.Y() <= max(AP.Y(), EP.Y()))
	{
		return true;
	}
	if (AP.Y() == EP.Y() &&	// waagrechte Strecke
		min(AP.X(), EP.X()) <= LPkt.X() && 
			LPkt.X() <= max(AP.X(), EP.X()))
	{
		return true;
	}

// Normalfall (schräge Strecke)
	if (min(AP.X(), EP.X()) <= LPkt.X() && 
			LPkt.X() <= max(AP.X(), EP.X()) &&
		min(AP.Y(), EP.Y()) <= LPkt.Y() && 
			LPkt.Y() <= max(AP.Y(), EP.Y()))
	{
		return true;
	}
	return false;
}

// (absolute) Länge d des Lots von Punkt Pkt auf die Strecke AP-EP (mit 
// euklidischer Norm);
// Wird true zurückgegeben, dann ist der Abstand zur Strecke bestimmbar, bei 
// false gilt der berechnete Abstand nur für die Trägergerade, nicht aber für 
// die Strecke. Ist die Strecke entartet (Anfangs- und Endpunkt fallen zusammen), 
// wird ebenfalls false zurückgegeben. d ist dabei negativ.
template <typename KoOrdT>
inline bool 
LotStrecke (WMPunkt<KoOrdT> const &Pkt, 
	WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP, double &d)
{
	if (AP == EP) {	// Strecke entartet
		_ASSERTE(AP != EP);		// Fehlermeldung aus IdenticalPoints
		d = -1.0;
		return false;
	}
	if (Pkt == AP || Pkt == EP)	{
		d = 0.0;
		return true;
	}

// Koordinaten des Lotpunktes von Pkt auf die Trägergerade der Strecke AP-EP
double xl, yl;

	if (!GeradenLotPunkt (Pkt.X(), Pkt.Y(), AP.X(), AP.Y(), EP.X(), EP.Y(), 
			xl, yl))
	{
		d = -1.0;
		return false;
	}

double dx = xl - Pkt.X();
double dy = yl - Pkt.Y();

	d = sqrt (dx*dx + dy*dy);

	if (AP.X() == EP.X() &&	// senkrechte Strecke (28.07.98)
		min(AP.Y(), EP.Y()) <= yl && 
			yl <= max(AP.Y(), EP.Y()))
	{
		return true;
	}
	if (AP.Y() == EP.Y() &&	// waagrechte Strecke
		min(AP.X(), EP.X()) <= xl && 
			xl <= max(AP.X(), EP.X()))
	{
		return true;
	}

// Normalfall (schräge Strecke)
	if (min(AP.X(), EP.X()) <= xl && 
			xl <= max(AP.X(), EP.X()) &&
		min(AP.Y(), EP.Y()) <= yl && 
			yl <= max(AP.Y(), EP.Y()))
	{
		return true;
	}
	return false;
}

// (absolute) Länge d des Lots von Punkt Pt auf die this-Strecke (mit 
// euklidischer Norm);
// Wird true zurückgegeben, dann ist der Abstand zur this-Strecke bestimmbar, 
// bei false gilt der berechnete Abstand nur für die Trägergerade, nicht aber 
// für die Strecke. Ist die this-Strecke entartet (Anfangs- und Endpunkt fallen 
// zusammen), wird ebenfalls false zurückgegeben. d ist dabei negativ.
// In LPkt werden die Koordinaten im double-Format des Lotpunktes von Pt auf 
// Trägergerade der this-Strecke zurückgegeben.
inline bool 
LotStrecke (DoublePair const &DP0, DoublePair const &DP1, 
	DoublePair const &DP2, double &d)
{
	if (DP1.X() == DP2.X() && DP1.Y() == DP2.Y()) {	// Strecke entartet
		_ASSERTE(!(DP1.X() == DP2.X() && DP1.Y() == DP2.Y()));		// Fehlermeldung aus IdenticalPoints
		d = -1.;
		return false;
	}

// evtl. beim Vergleich der double-Werte "Rauschen" mit dREps berücksichtigen 
	if ((DP0.X() == DP1.X() && DP0.Y() == DP1.Y()) ||	// DP0 == DP1
		(DP0.X() == DP2.X() && DP0.Y() == DP2.Y()))		// DP0 == DP2
	{
		d = 0.0;
		return true;
	}

double xl, yl;	// Koordinaten des Lotpunktes von DP0 auf die Trägergerade der Strecke DP1-DP2

	if (!GeradenLotPunkt (DP0.X(), DP0.Y(), DP1.X(), DP1.Y(), DP2.X(), DP2.Y(),
			xl, yl))
	{
		d = -1.0;
		return false;
	}

double dx = xl - DP0.X();
double dy = yl - DP0.Y();

	d = sqrt (dx*dx + dy*dy);

	if (fabs(DP1.X() - DP2.X()) <= dREps &&	// senkrechte Strecke (01.04.99)
		min(DP1.Y(), DP2.Y()) <= yl && 
			yl <= max(DP1.Y(), DP2.Y()))
	{
		return true;
	}

	if (fabs(DP1.Y() - DP2.Y()) <= dREps &&	// waagerechte Strecke (01.04.99)
		min (DP1.X(), DP2.X()) <= xl && 
			xl <= max(DP1.X(), DP2.X()))
	{
		return true;
	}

// Normalfall (schräge Strecke)
	if (min(DP1.X(), DP2.X()) <= xl && 
			xl <= max(DP1.X(), DP2.X()) &&
		min(DP1.Y(), DP2.Y()) <= yl && 
			yl <= max(DP1.Y(), DP2.Y()))
	{
		return true;
	}
	return false;
}

// (absoluter) double-Abstand d des Punktes DP0 von der Strecke DP1-DP2 
// (mit euklidischer Norm); Ist i.a. das Lot auf die Strecke. Läßt sich dies 
// nicht fällen (sondern nur auf die Trägergerade), wird der Abstand zum 
// nächstgelegenen Endpunkt der this-Strecke ermittelt. Ist die this-Strecke 
// entartet (Anfangs- und Endpunkt fallen zusammen), wird false
// zurückgegeben, sonst true.
inline bool 
AbstandPktStrecke (DoublePair const &DP0, DoublePair const &DP1, 
	DoublePair const &DP2, double &d)
{
	if (LotStrecke (DP0, DP1, DP2, d))	// gesuchter Abstand = Länge d des Lots
		return true;

	if (d < 0.0)	// this-Strecke entartet
		return false;

// von Punkt DP0 konnte nur auf die Trägergerade, nicht auf die Strecke selbst 
// das Lot gefällt werden; deshalb Suche des Abstands zum nächstgelegenen 
// Endpunkt der Strecke DP1-DP2
double dx1 = DP1.X() - DP0.X();
double dy1 = DP1.Y() - DP0.Y();
double d1 = sqrt (dx1*dx1 + dy1*dy1);
double dx2 = DP2.X() - DP0.X();
double dy2 = DP2.Y() - DP0.Y();
double d2 = sqrt (dx2*dx2 + dy2*dy2);

	d = min(d1, d2);
	return true;
}

// Wert zwischen 0 und 360, der nicht gleich dem Winkel ist, den eine Strecke 
// (x1,y1)-(x2,y2) mit der Waagerechten bildet, der jedoch die gleiche 
// Ordnungseigenschaft wie dieser Winkel besitzt
inline double 
QuasiWinkel (double x1, double y1, double x2, double y2)
{
	_ASSERTE(x1 != x2 || y1 != y2);

double dx = x2 - x1;
double ax = fabs(dx);
double dy = y2 - y1;
double ay = fabs(dy);
double t = (ax + ay == 0.0) ? 0.0 : dy/(ax+ay);

	if (dx < 0.0)
		t = 2.0 - t;
	else if (dy < 0.0)
		t = 4.0 + t;

	return t * 90.0;
} 

// eine meiner wichtigsten Routinen, in der jede Menge Kreativität steckt

// nachfolgende Routine wird bei Test auf Überschneidung der Strecken zweier 
// Kanten, NICHT beim Test auf Selbstinzidenz (und Konturinzidenz) eingesetzt
// Lage der 2 Strecken AP1-EP1 und AP2-EP2 zueinander
//   KEINE      Strecken schneiden sich nicht
//   ECHT       Strecken schneiden sich
//   RAND       Strecken berühren sich in jeweils genau einem Randpunkt
//   INNEN      Randpunkt der einen Strecke liegt im "Inneren" der anderen Strecke
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander
// die gemeinsamen Punkte werden in GP1 (GP2) zurückgegeben
template <typename KoOrdT>
inline WMSchnittErg 
GemeinsamePunkte (
	WMPunkt<KoOrdT> const &AP1, WMPunkt<KoOrdT> const &EP1, 
	WMPunkt<KoOrdT> const &AP2,	WMPunkt<KoOrdT> const &EP2, 
	DoublePair &GP1, DoublePair &GP2)
{
// durch die Rundung der Stützpunktkoordinaten von double auf KoOrd können bei 
// der von TRiAS verwendeten Vektordarstellung folgende Probleme auftreten:
// 1. die Strecken AP1-EP1 bzw. AP2-EP2 können entartet sein
	if (AP1 == EP1 || AP2 == EP2)
		return KEINE;

// 2. ein Stützpunkt, der eigentlich exakt AUF einer Strecke eines anderen 
// Objektes liegen müßte, liegt leicht DANEBEN, weil eben an genau dieser Stelle 
// kein Punkt mit GANZZAHLIGEN Koordinaten liegen kann;
// deshalb wird bei der Testung, wie 2 Strecken zueinander liegen, nicht das 
// übliche Verfahren mit den Kreuzprodukten von Vektordifferenzen verwendet, 
// weil dabei Fehlinterpretationen auftreten können, z. B.
//	scheinbar ECHT		tatsächlich INNEN
//	scheinbar KEINE		tatsächlich INNEN bzw. UEBERLAPP
//	scheinbar RAND		tatsächlich UEBERLAPP
// Um diese Dreckeffekte zu umgehen, wird folgendermaßen vorgegangen: Es wird 
// von dem Endpunkt der einen Strecke das Lot auf die jeweils andere Strecke 
// gefällt. Ist die Länge des Lots unterhalb eines vorgegebenen Epsilons, dann 
// gehe ich davon aus, daß besagter Endpunkt auf der anderen Strecke liegen 
// müßte und nur deshalb dort nicht liegt, weil dort kein Punkt mit ganzzahligen 
// Koordinaten liegen kann.
double dAbst;	// Abstand für Routine LotStrecke()

// RAND oder UEBERLAPP
	if (AP1 == AP2)	{
		GP1 = DoublePair (AP1.X(), AP1.Y());
		if (LotStrecke (EP1, AP2, EP2, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair(EP1.X(), EP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (EP2, AP1, EP1, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair(EP2.X(), EP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

	if (AP1 == EP2)	{
		GP1 = DoublePair (AP1.X(), AP1.Y());
		if (LotStrecke (EP1, AP2, EP2, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair (EP1.X(), EP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (AP2, AP1, EP1, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair (AP2.X(), AP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == AP2) {
		GP1 = DoublePair (EP1.X(), EP1.Y());
		if (LotStrecke (AP1, AP2, EP2, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair (AP1.X(), AP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (EP2, AP1, EP1, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair (EP2.X(), EP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == EP2)	{
		GP1 = DoublePair (EP1.X(), EP1.Y());
		if (LotStrecke (AP1, AP2, EP2, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair (AP1.X(), AP1.Y());
			return UEBERLAPP;
		}

		if (LotStrecke (AP2, AP1, EP1, dAbst) && dAbst < dGlEps) {
			GP2 = DoublePair (AP2.X(), AP2.Y());
			return UEBERLAPP;
		}
		return RAND;
	}

// UEBERLAPP
int iAnz = 0;		// Anzahl der "Fast-Berührungen"

	if (LotStrecke (AP1, AP2, EP2, dAbst) && dAbst < dGlEps) {
		GP1 = DoublePair (AP1.X(), AP1.Y());
		iAnz++;
	}

	if (LotStrecke (EP1, AP2, EP2, dAbst) && dAbst < dGlEps) {
		if (0 == iAnz)
			GP1 = DoublePair (EP1.X(), EP1.Y());
		else
			GP2 = DoublePair (EP1.X(), EP1.Y());
		iAnz++;
		if (2 == iAnz) 
			return UEBERLAPP;
	}

	if (LotStrecke (AP2, AP1, EP1, dAbst) && dAbst < dGlEps) {
		if (0 == iAnz)
			GP1 = DoublePair (AP2.X(), AP2.Y());
		else
			GP2 = DoublePair (AP2.X(), AP2.Y());
		iAnz++;
		if (2 == iAnz) 
			return UEBERLAPP;
	}

	if (LotStrecke (EP2, AP1, EP1, dAbst) && dAbst < dGlEps) {
		if (0 == iAnz)
			GP1 = DoublePair (EP2.X(), EP2.Y());
		else
			GP2 = DoublePair (EP2.X(), EP2.Y());
		iAnz++;
	}

	if (2 == iAnz) 
		return UEBERLAPP;

// ECHT, INNEN/*, RAND*/ oder UEBERLAPP
	if (Intersection (AP1.X(), AP1.Y(), EP1.X(), EP1.Y(), AP2.X(), AP2.Y(), 
			EP2.X(), EP2.Y()))
	{
		if (0 == iAnz) {
			GP1 = StreckenSchnittPunkt (AP1, EP1, AP2, EP2);
/*
erst einmal doch nicht (20.10.98)
Text aus GeometrieModule.doc:
Wenn sich 2 Strecken schneiden, muß auch hier mit dem zulässigen "Rauschen" 
getestet werden, ob der Schnittpunkt eigentlich doch nur ein inneliegender oder 
Randpunkt ist. 
		// 07.10.98
		// die nachfolgenden 2 if-Anweisungen wurden als Abwehrstrategie gegen 
		// Dreckeffekte eingefügt, die durch Rundung von double auf KoOrd 
		// entstehen können;
		// AUCH hier muß noch mit dem Epsilon "dGlEps" getestet werden, ob der 
		// Schnittpunkt GP1 eigentlich doch nur ein inneliegender oder 
		// Randpunkt ist
			if (AP1.EpsGleich (GP1) || EP1.EpsGleich (GP1))
			{
				if (AP2.EpsGleich (GP1) || EP2.EpsGleich (GP1))
					return RAND;
				return INNEN;
			}

			if (AP2.EpsGleich (GP1) || EP2.EpsGleich (GP1))
			{
				if (AP1.EpsGleich (GP1) || EP1.EpsGleich (GP1))
					return RAND;
				return INNEN;
			}
*/
			return ECHT;
		}

		GP2 = StreckenSchnittPunkt (AP1, EP1, AP2, EP2);

	double dx = GP2.X() - GP1.X();
	double dy = GP2.Y() - GP1.Y();

	// sqrt auf beiden Seiten spare ich mir (07.10.98)
		if (dx*dx + dy*dy < dGlEps*dGlEps)
			return INNEN;
		return UEBERLAPP;
	}
	if (1 == iAnz) 
		return INNEN;

// Strecken schneiden sich nicht
	return KEINE;
} 

// nachfolgende Routine wird bei Test auf Selbstinzidenz (und Konturinzidenz) 
// eingesetzt, NICHT beim Test auf Überschneidung der Strecken zweier Kanten
// Lage der 2 Strecken AP1-EP1 und AP2-EP2 zueinander
//   KEINE      Strecken schneiden sich nicht
//   ECHT       Strecken schneiden sich
//   RAND       Strecken berühren sich in jeweils genau einem Randpunkt
//   INNEN      Randpunkt der einen Strecke liegt im "Inneren" der anderen Strecke
//   UEBERLAPP  Strecken liegen teilweise oder vollständig übereinander
// die gemeinsamen Punkte werden in GP1 (GP2) zurückgegeben
template <typename KoOrdT>
inline WMSchnittErg 
GemeinsamePunkte (
	WMPunkt<KoOrdT> const &AP1, WMPunkt<KoOrdT> const &EP1, 
	WMPunkt<KoOrdT> const &AP2, WMPunkt<KoOrdT> const &EP2,
	WMPunkt<KoOrdT> &GP1, WMPunkt<KoOrdT> &GP2)
{
	if (AP1 == EP1 || AP2 == EP2)
		return KEINE;

// RAND oder UEBERLAPP
	if (AP1 == AP2) {
		GP1 = AP1;
		if (Kollinear (EP1, AP2, EP2)) {
			GP2 = EP1;
			return UEBERLAPP;
		}

		if (Kollinear (EP2, AP1, EP1)) {
			GP2 = EP2;
			return UEBERLAPP;
		}
		return RAND;
	}

	if (AP1 == EP2) {
		GP1 = AP1;
		if (Kollinear (EP1, AP2, EP2)) {
			GP2 = EP1;
			return UEBERLAPP;
		}

		if (Kollinear (AP2, AP1, EP1)) {
			GP2 = AP2;
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == AP2) {
		GP1 = EP1;
		if (Kollinear (AP1, AP2, EP2)) {
			GP2 = AP1;
			return UEBERLAPP;
		}

		if (Kollinear (EP2, AP1, EP1)) {
			GP2 = EP2;
			return UEBERLAPP;
		}
		return RAND;
	}

	if (EP1 == EP2) {
		GP1 = EP1;
		if (Kollinear (AP1, AP2, EP2)) {
			GP2 = AP1;
			return UEBERLAPP;
		}

		if (Kollinear (AP2, AP1, EP1)) {
			GP2 = AP2;
			return UEBERLAPP;
		}
		return RAND;
	}


// INNEN oder UEBERLAPP
int iAnz = 0;		// Anzahl der Kollinearitäten

	if (Kollinear (AP1, AP2, EP2)) {
		GP1 = AP1;
		iAnz++;
	}

	if (Kollinear (EP1, AP2, EP2)) {
		if (0 == iAnz)
			GP1 = EP1;
		else
			GP2 = EP1;
		iAnz++;
		if (2 == iAnz) 
			return UEBERLAPP;
	}

	if (Kollinear (AP2, AP1, EP1)) {
		if (0 == iAnz)
			GP1 = AP2;
		else
			GP2 = AP2;
		iAnz++;
		if (2 == iAnz) 
			return UEBERLAPP;
	}

	if (Kollinear (EP2, AP1, EP1)) {
		if (0 == iAnz)
			GP1 = EP2;
		else
			GP2 = EP2;
		iAnz++;
	}

	if (2 == iAnz) 
		return UEBERLAPP;
	if (1 == iAnz) 
		return INNEN;

// ECHT oder KEINE
	if (Intersection (AP1.X(), AP1.Y(), EP1.X(), EP1.Y(), AP2.X(), AP2.Y(), 
			EP2.X(), EP2.Y()))
	{
	DoublePair GP = StreckenSchnittPunkt (AP1, EP1, AP2, EP2);

		GP1.X() = DtoL(GP.X()); 
		GP1.Y() = DtoL(GP.Y()); 
		return ECHT;
	}
	return KEINE;
} 

// Berechnung des Schnitt- oder Berührungspunktes der 2 Strecken AP1-EP1 und 
// AP2-EP2; hierbei wird vorausgesetzt, daß beide Strecken genau einen Punkt 
// gemeinsam haben
template <typename KoOrdT>
inline DoublePair 
StreckenSchnittPunkt (
	WMPunkt<KoOrdT> const &AP1, WMPunkt<KoOrdT> const &EP1, 
	WMPunkt<KoOrdT> const &AP2, WMPunkt<KoOrdT> const &EP2)
{
	if (AP1 == AP2 || AP1 == EP2)
		return DoublePair (AP1.X(), AP1.Y());

	if (EP1 == AP2 || EP1 == EP2)
		return DoublePair (EP1.X(), EP1.Y());

// Koordinaten des Schnittpunktes der Trägergeraden der beiden Strecken AP1-EP1
// und AP2-EP2
double xs, ys;

	if (GeradenSchnittPunkt (AP1.X(), AP1.Y(), EP1.X(), EP1.Y(), AP2.X(), 
			AP2.Y(), EP2.X(), EP2.Y(), xs, ys))
	{
	// entscheidende Erweiterung:
	// es wird getestet, ob der double-Schnittpunkt (xs, ys) nach Rundung auf 
	// KoOrd mit einem Streckenendpunkt zusammenfällt; ist dies der Fall, wird 
	// dieser Endpunkt zurückgegeben
	WMPunkt<KoOrdT> GP (DtoL(xs), DtoL(ys));

		if (GP == AP1 || GP == EP1 || GP == AP2 || GP == EP2)
			return DoublePair (GP.X(), GP.Y());
		return DoublePair (xs, ys);
	}

// hierhin dürfte das Programm gar nicht mehr kommen !!!!
	_ASSERTE(false);
	return DoublePair(std::numeric_limits<KoOrdT>::max(), 
		std::numeric_limits<KoOrdT>::max());
}

// Berechnung des Schnittpunktes (xs,ys) zweier Geraden, die jeweils durch 2 
// Punkte (x11,y11) und (x21,y21) bzw. (x12,y12) und (x22,y22) gegeben sind; 
// wird false zurückgegeben, ist der Schnittpunkt nicht ermittelbar, xs und ys 
// sind dann unbestimmt
inline bool 
GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
	double x12, double y12, double x22, double y22, double &xs, double &ys)
{
double a1 = y21 - y11;
double b1 = x11 - x21;
double a2 = y22 - y12;
double b2 = x12 - x22;
double dNenner = a1*b2 - a2*b1;

// wenn beide Geraden identisch oder parallel sind bzw. wenn ein (oder beide) Punktepaare
// zu einem Punkt zusammenfallen, ist der Schnittpunkt nicht ermittelbar
	if (0.0 == dNenner) 
		return false;

double c1 = -y11*b1 - x11*a1;
double c2 = -y12*b2 - x12*a2;

	xs = (c2*b1 - c1*b2) / dNenner;
	ys = (c1*a2 - c2*a1) / dNenner;

	return true;
}

// Berechnung des Schnittpunktes (xs,ys) zweier Geraden, die durch 2 Punkte 
// (x11,y11) und (x21,y21) bzw. einen Punkt (x2,y2) und den Anstieg dAnst 
// gegeben sind; wird false zurückgegeben, ist der Schnittpunkt nicht 
// ermittelbar; xs und ys sind dann unbestimmt
inline bool 
GeradenSchnittPunkt (double x11, double y11, double x21, double y21,
	double x2, double y2, double dAnst, double &xs, double &ys)
{
double a1 = y21 - y11;
double b1 = x11 - x21;
double a2, b2;

	if (dAnst < std::numeric_limits<double>::max()) {
	// 2. Gearde nicht senkrecht		
		a2 = dAnst;		//double a2 = y22 - y2;		
		b2 = -1.0;		//double b2 = x2 - x22;
	}
	else {
	// 2. Gerade senkrecht
		a2 = 1.0;		// Wert beliebig, da er herausgekürzt wird
		b2 = 0.0;
	}

double dNenner = a1*b2 - a2*b1;

// wenn beide Geraden identisch oder parallel sind bzw. wenn das Punktepaare zu einem Punkt
// zusammenfällt, ist der Schnittpunkt nicht ermittelbar
	if (0.0 == dNenner) 
		return false;

double c1 = -y11*b1 - x11*a1;
double c2 = -y2*b2 - x2*a2;

	xs = (c2*b1 - c1*b2) / dNenner;
	ys = (c1*a2 - c2*a1) / dNenner;
	return true;
}

// Berechnung des Lotpunktes (xl,yl) vom Punkt (xp,yp) auf eine Gerade g1, die 
// durch die 2 Punkte (x1,y1) und (x2,y2) gegeben ist; wird false zurückgegeben, 
// ist der Lotpunkt nicht ermittelbar, xl und yl sind dann unbestimmt
inline bool 
GeradenLotPunkt (double xp, double yp, double x1, double y1,
	double x2, double y2, double& xl, double& yl)
{
double a1 = y1 - y2;	// Parameter für allgemeine Gleichung a1*x+b1*y+c1=0 der Geraden g1	
double b1 = x2 - x1;	// (werden aus Zwei-Punkte-Gleichung ermittelt)

	if (0.0 == a1 && 0.0 == b1)	{
	// Gerade g1 ist zu einem Punkt entartet, damit kein Lotpunkt ermittelbar
		return false;
	}
	if (a1 != 0) {
	// g1 nicht waagerecht
	double c1 = -x1*a1 - y1*b1;
	double a2, b2, c2;	// Parameter für allgemeine Gleichung a2*x+b2*y+c2=0 
						// der Geraden g2, die senkrecht auf g1 steht und durch 
						// Punkt (xp,yp) geht (werden aus Punkt- Richtungs-
						// Gleichung ermittelt)

		a2 = b1 / a1;
		b2 = -1;
		c2 = yp - a2*xp;

	// Hilfsgröße (wird genau dann Null, wenn beide Geraden parallel sind); 
	// dies dürfte hier aber nicht zutreffen, da g2 so konstruiert wurde, 
	// daß g2 auf g1 senkrecht steht
	double dNenner = a1*b2 - a2*b1;
				
		if (0.0 == dNenner)
		{
			_ASSERTE(dNenner != 0.0);
			return false;
		}

		xl = (b1*c2 - b2*c1) / dNenner;	// x-Koordinate bzw.
		yl = (a2*c1 - a1*c2) / dNenner;	// y-Koordinate des Schnittpunktes von g1 und g2
	}
	else {
	// g1 waagerecht, damit g2 senkrecht
		xl = xp;
		yl = y1;
	}
	return true;
}

// Berechnung des POSITIVEN Winkels im Bogenmaß (d.h. zwischen 0 ... 2*Pi), den 
// die 3 Punkte P0(x0,y0), P1(x1,y1) und P2(x2,y2) bilden; es wird der Winkel 
// berechnet, der dadurch entsteht, daß die Strecke P1-P2 im mathematisch 
// positiven Sinn solange um P1 gedreht wird, bis sie auf der Strecke P0-P1 
// liegt; ist mindestens eine der beiden Strecken zu einem Punkt entartet, 
// wird false zurückgegeben; dWinkel ist in diesem Fall unbestimmt
template <typename KoOrdT>
inline bool 
Winkel (KoOrdT x0, KoOrdT y0, KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2,
	double &dWinkel)
{
// es muß gelten P0 != P1 und P1 != P2
	if ((x0 == x1 && y0 == y1) || (x1 == x2 && y1 == y2)) {
	// mindestens eine der beiden Strecken ist zu einem Punkt entartet
		return false;
	}

double dx1 = x1 - x0;	// "double", weil atan() ein double-Argument verlangt und
double dy1 = y1 - y0;	// damit die nachfolgenden Divisionen double-Ergebnisse liefern
double dx2 = x2 - x1;
double dy2 = y2 - y1;

	if (0.0 == dx1) {	
	// Strecke P0-P1 steht senkrecht
		if (dx2 != 0.0) {
		// Strecke P1-P2 steht NICHT senkrecht
			dWinkel = atan (dy2/dx2);

		// Ergebnis von atan() liegt im Bereich von -Pi/2 bis Pi/2, deshalb kann 
		// in ALLEN Fällen bei der nachfolgenden Winkelberechnung SUBTRAHIERT werden
			if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
				dWinkel = 0.5*Pi - dWinkel;	// konvexe Ecke 
			else
				dWinkel = 1.5*Pi - dWinkel;	// konkave Ecke 
		}
		else {	
		// BEIDE Strecken stehen senkrecht
			if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
				dWinkel = Pi;	// die Strecken liegen hintereinander, aber exakt auf einer
								// Geraden
			else
				dWinkel = 0.;	// eine Strecke liegt exakt auf bzw. in der anderen
		}
		return true;
	}

	if (0. == dx2) {
	// Strecke P1-P2 steht senkrecht
		dWinkel = atan (dy1/dx1);
		if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
			dWinkel += 0.5*Pi;	// konvexe Ecke
		else
			dWinkel += 1.5*Pi;	// konkave Ecke
		return true;
	}

// die Strecken stehen senkrecht aufeinander
// (an dieser Stelle wird der Genauigkeit wegen bewußt nicht mit den durch Division
// ermittelten Werte m1 und m2 getestet)
	if (dy1*dy2 == -dx1*dx2) {
		if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
			dWinkel = 0.5*Pi;	// konvexe Ecke
		else
			dWinkel = 1.5*Pi;	// konkave Ecke 
		return true;
	}

double m1 = dy1 / dx1;	// die Anstieg der Strecke P0-P1	
double m2 = dy2 / dx2;	// die Anstieg der Strecke P1-P2

	dWinkel = atan ((m1 - m2) / (1. + m1*m2));
	if (0.0 == dWinkel)	{	// die Strecken haben den gleichen Anstieg
		if (1 == TurnDirection (x0, y0, x1, y1, x2, y2))
			dWinkel = Pi;	// die Strecken liegen hintereinander, aber exakt auf einer Geraden
		return true;
	}

	if (dWinkel < 0.0) 
		dWinkel += Pi;	// Winkel soll IMMER positiv sein
	if (-1 == TurnDirection (x0, y0, x1, y1, x2, y2))
		dWinkel += Pi;	// konkave Ecke 
	return true;
} 

} // namespace trias_wmgeometry

#endif // !defined(_STRECKE_INL__1688CD4C_15D7_4884_9E21_A40DC837D0CA__INCLUDED_)
