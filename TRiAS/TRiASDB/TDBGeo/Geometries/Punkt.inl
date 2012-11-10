// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 13:07:02 
//
// @doc
// @module Punkt.inl | Declaration of the <c CPunkt> class

#if !defined(_PUNKT_INL__2EEC6463_E188_4B25_9B5E_5828D32D3750__INCLUDED_)
#define _PUNKT_INL__2EEC6463_E188_4B25_9B5E_5828D32D3750__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
//
//	WMKoordinatenPaar - Grundklasse jedes GeometrieObjektes 
//
///////////////////////////////////////////////////////////////////////////////
template <typename KoOrdT>
inline
WMKoordinatenPaar<KoOrdT>::WMKoordinatenPaar() :
	_X(0), _Y(0) 
{
}

template <typename KoOrdT>
inline
WMKoordinatenPaar<KoOrdT>::WMKoordinatenPaar(KoOrdT x, KoOrdT y) : 
	_X(x), _Y(y) 
{
}

template <typename KoOrdT>
inline KoOrdT const &
WMKoordinatenPaar<KoOrdT>::Width() const 
{ 
	return _X; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMKoordinatenPaar<KoOrdT>::Height() const 
{ 
	return _Y; 
}

template <typename KoOrdT>
inline KoOrdT &
WMKoordinatenPaar<KoOrdT>::X() 
{ 
	return _X; 
}

template <typename KoOrdT>
inline KoOrdT &
WMKoordinatenPaar<KoOrdT>::Y() 
{ 
	return _Y; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMKoordinatenPaar<KoOrdT>::X() const
{ 
	return _X; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMKoordinatenPaar<KoOrdT>::Y() const
{ 
	return _Y; 
}

///////////////////////////////////////////////////////////////////////////////
//
//	WMAusdehnung - Größe eines Rechtecks 
//
///////////////////////////////////////////////////////////////////////////////
template <typename KoOrdT>
inline 
WMAusdehnung<KoOrdT>::WMAusdehnung() : 
	WMKoordinatenPaar<KoOrdT>() 
{
}

template <typename KoOrdT>
inline 
WMAusdehnung<KoOrdT>::WMAusdehnung(KoOrdT x, KoOrdT y) : 
	WMKoordinatenPaar<KoOrdT>(x, y) 
{
}

// Memberfunktionen
template <typename KoOrdT>
inline KoOrdT &
WMAusdehnung<KoOrdT>::Breite() 
{ 
	return this->X(); 
}

template <typename KoOrdT>
inline KoOrdT &
WMAusdehnung<KoOrdT>::Hoehe() 
{ 
	return this->Y(); 
}

///////////////////////////////////////////////////////////////////////////////
//
//	WMPunkt
//
///////////////////////////////////////////////////////////////////////////////
template <typename KoOrdT>
inline 
WMPunkt<KoOrdT>::WMPunkt() : 
	WMKoordinatenPaar<KoOrdT>() 
{
}

template <typename KoOrdT>
inline 
WMPunkt<KoOrdT>::WMPunkt(KoOrdT x, KoOrdT y) : 
	WMKoordinatenPaar<KoOrdT>(x, y) 
{
}

// Memberfunktionen
template <typename KoOrdT>
inline KoOrdT 
WMPunkt<KoOrdT>::GetX() const 
{ 
	return _X; 
}

template <typename KoOrdT>
inline KoOrdT 
WMPunkt<KoOrdT>::GetY() const 
{ 
	return _Y; 
}

template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> 
WMPunkt<KoOrdT>::GetCont() const
{ 
	return WMObjRechteck<KoOrdT>(GetX(), GetY(), GetX(), GetY()); 
}
	
template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::operator== (const WMPunkt& P) const 
{ 
	return (GetX() == P.GetX() && GetY() == P.GetY()); 
}

template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::operator!= (WMPunkt const &P) const
{ 
	return !(*this == P); 
}

template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::operator== (DoublePair const &DP) const 
{ 
	return (GetX() == DtoL(DP.X()) && GetY() == DtoL(DP.Y())); 
}

template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::operator!= (DoublePair const &DP) const
{ 
	return !(*this == DP); 
}

template <typename KoOrdT>
inline 	
WMPunkt<KoOrdT>::operator= (DoublePair const &rhs)
{
	X() = DtoL(rhs.X());
	Y() = DtoL(rhs.Y());
}

// Epsilon-Gleichheit zwischen this-EPunkt und P; wenn bEuklid == true, dann 
// wird die euklidische Norm verwendet, sonst die Maximum-Norm
template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::EpsGleich (WMPunkt const &P, double dEpsX, double dEpsY, 
	bool bEuklid) const
{
	if (bEuklid) {
	double dEps = (dEpsX + dEpsY) / 2.;

		return AbstandPktPktE(*this, P) <= dEps;
	}
	return KoOrdAbs(_X - P.GetX()) <= dEpsX && KoOrdAbs(_Y - P.GetY()) <= dEpsY;
}

// Epsilon-Ungleichheit zwischen this-EPunkt und P; wenn bEuklid == true 
// (default), dann wird die euklidische Norm verwendet, sonst die Maximum-Norm
template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::EpsUngleich (WMPunkt const &P, double dEpsX, double dEpsY, 
	bool bEuklid) const
{
	if (bEuklid) {
	double dEps = (dEpsX + dEpsY) / 2.;

		return AbstandPktPktE (*this, P) > dEps;
	}
	return KoOrdAbs(_X - P.GetX()) > dEpsX || KoOrdAbs(_Y - P.GetY()) > dEpsY;
}

// Epsilon-Gleichheit zwischen this-EPunkt und DoublePair DP; wenn 
// bEuklid == true (default), dann wird die euklidische Norm verwendet, sonst 
// die Maximum-Norm
template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::EpsGleich (DoublePair const &DP, double dEpsX, double dEpsY, 
	bool bEuklid) const
{
double dx = _X - DP.X();
double dy = _Y - DP.Y();

	if (bEuklid) {
	double dEps = (dEpsX + dEpsY) / 2.;

		return (dx*dx + dy*dy <= dEps*dEps);
	}
	return fabs(dx) <= dEpsX && fabs(dy) <= dEpsY;
}

// Vektordifferenz
template <typename KoOrdT>
inline WMPunkt<KoOrdT> 
WMPunkt<KoOrdT>::operator- (WMPunkt const &Pkt) const
{
	return WMPunkt(_X - Pkt.GetX(), _Y - Pkt.GetY());
}

// beide Punktkoordinaten ungültig machen
template <typename KoOrdT>
inline void
WMPunkt<KoOrdT>::UnValid()
{
	_X = _Y = std::numeric_limits<KoOrdT>::max();
}

// true, wenn Punkt ungültig, d.h. beide Punktkoordinaten ungültig, sonst false
template <typename KoOrdT>
inline bool
WMPunkt<KoOrdT>::operator!() const
{
	return 
		_X == std::numeric_limits<KoOrdT>::max() && 
		_Y == std::numeric_limits<KoOrdT>::max();
}

// true, wenn Punkt gültig, d.h. wenigstens eine Punktkoordinate gültig, sonst false
template <typename KoOrdT>
inline 
WMPunkt<KoOrdT>::operator bool() const
{
	return !*this;
}

// true, wenn wenigstens eine Punktkoordinate außerhalb des Intervalls <0; MAXKOORD>
template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::isBad (void) const
{
//	return (_X < 0 || _X > MAXKOORD || _Y < 0 || _Y > MAXKOORD);
	return false;
}

// Punkt liegt innerhalb des Containers OC (einschließlich auf dessen Rand), 
// dann Rückgabe von true
template <typename KoOrdT>
inline bool 
WMPunkt<KoOrdT>::PktInCont (WMObjRechteck<KoOrdT> const &OC) const
{
	if (_X >= OC.XMin() && _X <= OC.XMax() && _Y >= OC.YMin() && _Y <= OC.YMax())
		return true;
	return false;
}

// Enthaltensein eines Punktes in der Fläche, die durch eine geschlossene Kante bzw. eine
// Flächenkontur gebildet wird;
// bez. der Lage AUF dem this-Vektor wird mit einer dEps-Genauigkeit gearbeitet (02.06.99);
// return-Werte sind
//   INNERH   Punkt liegt innerhalb der Fläche
//   KONTUR   Punkt liegt auf Flächenrand
//   AUSSERH  Punkt liegt außerhalb der Fläche
//   OFFEN    Flächenrand nicht geschlossen bzw. entartete Fläche
template <typename KoOrdT>
inline WMPosit
WMPunkt<KoOrdT>::Position (WMKante<KoOrdT> const *pK, double dEps) const 
{
	_ASSERTE(NULL != pK);

long n = pK->ASP(); // Kantenlänge

	if (pK->SP(0) != pK->SP(n-1))	// Kante nicht geschlossen
		return OFFEN;

WMStrecke<KoOrdT> TLinie (*this, *this);		// Testlinie

	TLinie.EP().X() = std::numeric_limits<KoOrdT>::max();	// Testlinie soll waagrecht sein

long AnzSchn = 0;	// Zähler für echte Schnitte der Testlinie mit EKante K
long j = n-2;		// Index des letzten Konturpunktes, von dem bekannt ist, daß
					// er nicht auf der Testlinie liegt

	while (TLinie == pK->SP(j)) {
		j--;
		if (j < 0)
			return OFFEN;	// entartete Fläche, d.h. alle Punkte liegen auf einer Geraden,
							// die mit der Trägergeraden der TLinie identsch ist
	}

int r1, r2, r3;
double dAbst;		// absoluter Abstand von Punkt Pkt zur Strecke Str
DoublePair DP0, DP1, DP2;

	DP0.X() = _X;
	DP0.Y() = _Y;

	for (long i = 0; i < n-1; i++) {
	// Test, ob this-Punkt mit dEps-Genauigkeit AUF pK-Kante liegt
		DP1.X() = pK->SP(i).X();
		DP1.Y() = pK->SP(i).Y();
		DP2.X() = pK->SP(i+1).X();
		DP2.Y() = pK->SP(i+1).Y();
		AbstandPktStrecke (DP0, DP1, DP2, dAbst);
		if (dAbst < 0)
			return UNKLAR;
		if (dAbst <= dEps)
			return KONTUR;	// this-Punkt liegt mit dEps-Genauigkeit AUF pK-Kante

	// Im 1. Teil der nachfolgenden if-Anweisung wird der Fall behandelt, daß der nächste
	// Stützpunkt pK->SP(i) nicht auf der waagrechten Testlinie liegt.
	// Liegt pK->SP(i) auf der Testlinie (else-Zweig), wird pK->SP(i) i.a. ignoriert.
	// Liegt jedoch der zu testende Punkt im Dreieck pK->SP(i-1), pK->SP(i),
	// pK->SP(i+1), ergibt sich durch das Weglassen von pK->SP(i) eine
	// Fehlinterpretation. Deshalb ist dieser Fall gesondert abzutesten.
		if (!(TLinie == pK->SP(i))) {
		// Zähler inkrementieren, wenn echter Schnitt vorliegt, d. h. pK->SP(i) und
		// und pK->SP(j) auf verschiedenen Seiten der Testlinie liegen
			if (Intersection (
					pK->SP(i).X(), pK->SP(i).Y(), pK->SP(j).X(), pK->SP(j).Y(),
					TLinie.AP().X(), TLinie.AP().Y(), TLinie.EP().X(), TLinie.EP().Y()))
			{
				AnzSchn++;
			}
			j = i;
		}
		else {
		// pK->SP(i) liegt auf der Teststrecke
			r2 = TurnDirection (pK->SP(i).X(), pK->SP(i).Y(), pK->SP(i+1).X(), 
				pK->SP(i+1).Y(), _X, _Y);

			if (i > 0) {
				r1 = TurnDirection (pK->SP(i-1).X(), pK->SP(i-1).Y(), 
					pK->SP(i).X(), pK->SP(i).Y(), _X, _Y);
				r3 = TurnDirection (pK->SP(i+1).X(), pK->SP(i+1).Y(), 
					pK->SP(i-1).X(), pK->SP(i-1).Y(), _X, _Y);
			}
			else {
			// i = 0
				r1 = TurnDirection (pK->SP(n-2).X(), pK->SP(n-2).Y(), 
					pK->SP(0).X(), pK->SP(0).Y(), _X, _Y);
				r3 = TurnDirection (pK->SP(1).X(), pK->SP(1).Y(), 
					pK->SP(n-2).X(), pK->SP(n-2).Y(), _X, _Y);
			}

			if (r1 >= 0 && r2 >= 0 && r3 >= 0)	// konvexe Ecke der geschlossenen pK-EKante:
				return INNERH;					//  Punkt liegt innerhalb
			if (r1 <= 0 && r2 <= 0 && r3 <= 0)	// konkave Ecke der geschlossenen pK-EKante:
				return AUSSERH;					//  Punkt liegt außerhalb
		}

	}
	if (1 == AnzSchn % 2)        // ungerader Zähler bedeutet Enthaltensein
		return INNERH;
	return AUSSERH;
}

// Test, wie der this-EPunkt bez. der EKante pKt liegt;
// return-Werte sind
//   AUSSERH  Punkt liegt außerhalb der Kante
//   KONTUR   Punkt liegt auf einem  der beiden Endpunkte einer offenen Kante
//   INNERH   Punkt liegt "richtig" innerhalb der Kante (NICHT auf einem  der beiden Endpunkte
//            einer offenen Kante)
//   UNKLAR   Kante ist nicht definiert (NULL-Pointer)
template <typename KoOrdT>
inline WMPosit
WMPunkt<KoOrdT>::PunktAufKante (WMKante<KoOrdT>* pKt)
{
	_ASSERTE(pKt != 0);
	if (!PktInCont (pKt->GetCont()))
		return AUSSERH;	// this-EPunkt liegt nicht im pKt-Container

long lKL = pKt->ASP();

	if (pKt->SP(0) != pKt->SP(lKL-1) &&						// Kante offen
		(*this == pKt->SP(0) || *this == pKt->SP(lKL-1)))	// this-EPunkt == pKt-Randpunkt
	{
		return KONTUR;
	}
	for (long i = 0; i < lKL-1; i++) {
		if (0 == TurnDirection (pKt->SP(i).X(), pKt->SP(i).Y(), 
				pKt->SP(i+1).X(), pKt->SP(i+1).Y(), _X, _Y))
		{
			return INNERH;
		}
	}
	return AUSSERH;
}
	
// Lage des this-Punktes bezüglich der Fläche pFl; es werden auch Inseln von 
// pFl mit berücksichtigt, d.h. liegt this-EPunkt innerhalb einer pFl-Insel, 
// dann liegt this-EPunkt außerhalb von pFl
template <typename KoOrdT>
inline WMPosit 
WMPunkt<KoOrdT>::EnthaltenIn (WMFlaeche<KoOrdT>* pFl, void* pPSt)
{
	_ASSERTE(pFl != 0);

	if (!PktInCont(pFl->GetCont()))
		return AUSSERH;	// this-EPunkt liegt nicht im pFl-Container

int iKAnz = pFl->KantenAnz ();	// Anzahl der Konturen von pFl
WMPosit posLage;				// Lagemarkierung

	for (int i = 0; i < iKAnz; i++) {
		posLage = Position (&pFl->KA(i));    // Lagemarkierung

	// Test mit pFl-Innenkonturen (i > 0) nur erforderlich, wenn der Test mit 
	// der pFl-Außenkontur posLage == INNERH ergeben hat
		if (i == 0 && posLage != INNERH)
			return posLage;
			
		if (i > 0) {
		// pFl-Innenkonturen wurden noch mit herangezogen
		// für INNERH, KONTUR und ILLPARS ist alles klar
			if (posLage == INNERH || posLage == KONTUR || posLage == UNKLAR) {
			// vollständig innerhalb einer pFl-Insel heißt außerhalb der pFl-Fläche
				if (posLage == INNERH)
					posLage = AUSSERH;
				return posLage;
			}
		}
	// für AUSSERH ist posLage noch nicht eindeutig klärbar
	}

// dieser Programmteil wird nur erreicht, wenn this-EPunkt innerhalb der 
// Außenkontur liegt und bezüglich aller Innenkonturen (so es sie überhaupt 
// gibt) AUSSERH gilt, dann gilt INNERH
	return INNERH;
}

template <typename KoOrdT>
inline WMObjTyp 
WMPunkt<KoOrdT>::isA() const
{ 
	return OT_PUNKT; 
}

///////////////////////////////////////////////////////////////////////////////
//
//	ursprünglich friend-Funktionen vom WMPunkt
//
///////////////////////////////////////////////////////////////////////////////

// Abstand zwischen den Punkten AP und EP mit Maximum-Norm
template <typename KoOrdT>
inline KoOrdT 
AbstandPktPktM (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP)
{
KoOrdT dx = KoOrdAbs(EP.X() - AP.X());
KoOrdT dy = KoOrdAbs(EP.Y() - AP.Y());

	return dx > dy ? dx : dy;
}

// Abstand zwischen den Punkten (x1,y1) und (x2,y2) mit Maximum-Norm
template <typename KoOrdT>
inline KoOrdT 
AbstandPktPktM (KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2)
{
KoOrdT dx = KoOrdAbs(x2 - x1);
KoOrdT dx = KoOrdAbs(y2 - y1);

	return dx > dy ? dx : dy;
}

// Abstand zwischen den Punkten AP(x1,y1) und EP(x2,y2) mit euklidischer Norm
template <typename KoOrdT>
inline double 
AbstandPktPktE (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP)
{
double dx = EP.X() - AP.X();
double dy = EP.Y() - AP.Y();

	return sqrt(dx*dx + dy*dy);
}

// Abstand zwischen den Punkten (x1,y1) und (x2,y2) mit euklidischer Norm (als double-Wert)
template <typename KoOrdT>
inline double 
AbstandPktPktE (KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2)
{
double dx = x2 - x1;
double dy = y2 - y1;

	return sqrt(dx*dx + dy*dy);
}

// Kreuzprodukt zweier Vektoren mit Endpunkten Pkt1 und Pkt2
template <typename KoOrdT>
inline double 
KreuzProd (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2)
{
	return (double)Pkt1.X()*Pkt2.Y() - (double)Pkt2.X()*Pkt1.Y();
}

// Kollinearität von 3 Punkten (true), sonst false
template <typename KoOrdT>
inline bool 
Kollinear (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3)
{
double dx1 = Pkt2.X() - Pkt1.X();		// 04.06.98
double dy1 = Pkt2.Y() - Pkt1.Y();
double dx2 = Pkt3.X() - Pkt1.X();
double dy2 = Pkt3.Y() - Pkt1.Y();

	return (0.0 == dx1*dy2 - dx2*dy1);
}

template <typename KoOrdT>
inline bool 
Kollinear (KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2, KoOrdT x3, KoOrdT y3)
{
double dx1 = x2 - x1;
double dy1 = y2 - y1;
double dx2 = x3 - x1;
double dy2 = y3 - y1;

	return (0.0 == dx1*dy2 - dx2*dy1);
}

// Epsilon-Kollinearität von 3 Punkten (true), sonst false
template <typename KoOrdT>
inline bool 
EpsKollinear (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3, int iEpsilon)
{
double dAbst = 0;	// Länge des Lots

	if (WMStrecke<KoOrdT>(Pkt1, Pkt2).LotPktGerade(Pkt3, dAbst) && dAbst <= iEpsilon)
		return true;
	if (WMStrecke<KoOrdT>(Pkt1, Pkt3).LotPktGerade(Pkt2, dAbst) && dAbst <= iEpsilon)
		return true;
	if (WMStrecke<KoOrdT>(Pkt2, Pkt3).LotPktGerade(Pkt1, dAbst) && dAbst <= iEpsilon)
		return true;
	return false;
}

// 3 Punkte sind paarweise eps-verschieden (true), sonst false
template <typename KoOrdT>
inline bool 
PaarVergl (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3, int eps)
{
	return 
		AbstandPktPktE(Pkt1, Pkt2) > eps && 
		AbstandPktPktE(Pkt1, Pkt3) > eps &&
		AbstandPktPktE(Pkt2, Pkt3) > eps;
}

// für 3 Punkte gilt, daß P2 von P1 und P3 eps-verschieden ist (true), sonst false
template <typename KoOrdT>
inline bool 
MittVergl (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3, int eps)
{
	return 
		AbstandPktPktE(Pkt2, Pkt1) > eps &&
		AbstandPktPktE(Pkt2, Pkt3) > eps;
}

// Rechteck aus den 2 Punkten Pkt1 und Pkt2 bilden
template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> 
BuildRectangle (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2)
{
KoOrdT XMin = min(Pkt1.X(), Pkt2.X());
KoOrdT XMax = max(Pkt1.X(), Pkt2.X());
KoOrdT YMin = min(Pkt1.Y(), Pkt2.Y());
KoOrdT YMax = max(Pkt1.Y(), Pkt2.Y());

	return WMObjRechteck<KoOrdT>(XMin, XMax, YMin, YMax);
}

// Schwerpunkt des Dreiecks Pkt1-Pkt2-Pkt3
template <typename KoOrdT>
inline DoublePair 
SchwerPunkt (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> &Pkt3)
{
double xs = (Pkt1.X() + Pkt2.X() + Pkt3.X()) / 3.;
double ys = (Pkt1.Y() + Pkt2.Y() + Pkt3.Y()) / 3.;

	return DoublePair(xs, ys);
}

} // namespace trias_wmgeometry

#endif // !defined(_PUNKT_INL__2EEC6463_E188_4B25_9B5E_5828D32D3750__INCLUDED_)
