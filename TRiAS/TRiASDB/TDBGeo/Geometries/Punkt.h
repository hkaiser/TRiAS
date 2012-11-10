// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 13:06:12 
//
// @doc
// @module Punkt.h | Declaration of the <c CPunkt> class

#if !defined(_PUNKT_H__DB8B76D2_27A0_4F60_978F_341B1EC5D90B__INCLUDED_)
#define _PUNKT_H__DB8B76D2_27A0_4F60_978F_341B1EC5D90B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry { 

///////////////////////////////////////////////////////////////////////////////
// WMKoordinatenPaar - Grundklasse jedes GeometrieObjektes 
template <typename KoOrdT>
class WMKoordinatenPaar 
{
protected:
	KoOrdT _X;
	KoOrdT _Y;

public:
// Konstruktoren
	WMKoordinatenPaar();
	WMKoordinatenPaar(KoOrdT x, KoOrdT y);

	KoOrdT const &Width() const;
	KoOrdT const &Height() const;
	KoOrdT &X();
	KoOrdT &Y();
	KoOrdT const &X() const;
	KoOrdT const &Y() const;
};

typedef WMKoordinatenPaar<double> DoublePair;

///////////////////////////////////////////////////////////////////////////////
// WMAusdehnung - Größe eines Rechtecks 
template <typename KoOrdT>
class WMAusdehnung : 
	public WMKoordinatenPaar<KoOrdT> 
{
public:
// Konstruktoren
	WMAusdehnung();
	WMAusdehnung(KoOrdT x, KoOrdT y);

// Memberfunktionen
	KoOrdT &Breite();     // liefern Attributwerte
	KoOrdT &Hoehe();
};

///////////////////////////////////////////////////////////////////////////////
// WMPunkt 
template <typename KoOrdT>
class WMPunkt : 
	public WMObjekt<KoOrdT>,
	public WMKoordinatenPaar<KoOrdT>
{
public:
// Konstruktoren
	WMPunkt();
	WMPunkt(KoOrdT x, KoOrdT y);

// Memberfunktionen
	KoOrdT GetX() const;	// liefern Attributwerte
	KoOrdT GetY() const;

	WMObjRechteck<KoOrdT> GetCont() const;

	bool operator== (WMPunkt const &P) const;
	bool operator!= (WMPunkt const &P) const;

	bool operator== (DoublePair const &DP) const;
	bool operator!= (DoublePair const &DP) const;

	operator= (DoublePair const &rhs);

	bool EpsGleich (WMPunkt const &P, double dEpsX = dGlEps, double dEpsY = dGlEps, 
		bool bEuklid = true) const;
	bool EpsUngleich (WMPunkt const &P, double dEpsX = dGlEps, double dEpsY = dGlEps, 
		bool bEuklid = true) const;
	bool EpsGleich (DoublePair const &DP, double dEpsX = dGlEps, double dEpsY = dGlEps, 
		bool bEuklid = true) const;

	WMPunkt operator- (WMPunkt const &) const;        // Vektordifferenz
	void UnValid();		// beide Punktkoordinaten auf LONG_MAX setzen

// true, wenn Punkt ungültig, d.h. beide Punktkoordinaten = LONG_MAX, sonst false
	bool operator!() const;

// true, wenn Punkt gültig, d.h. wenigstens eine Punktkoordinate != LONG_MAX, sonst false
	operator bool() const;

// true, wenn wenigstens eine Punktkoordinate außerhalb des Intervalls <0; MAXKOORD>
	bool isBad (void) const;

// Enthaltensein eines Punktes in einem Container
	bool PktInCont (WMObjRechteck<KoOrdT> const &OC) const;
	
// Enthaltensein eines Punktes in der Fläche, die durch eine geschlossene Kante bzw.
// eine Flächenkontur gebildet wird
	WMPosit Position (WMKante<KoOrdT> const *pK, double dEps = dGlEps/*0.0*/) const;

// Test, wie der this-WMPunkt bez. der WMKante pKt liegt
	WMPosit PunktAufKante (WMKante<KoOrdT>* pKt);
	
// Definition der virtuellen Funktionen der Basisklasse WMObjekt
	WMObjTyp isA (void) const;				// liefert ObjektTyp
	WMPosit EnthaltenIn (WMFlaeche<KoOrdT>* pFS, void* pPSt = 0);
};

///////////////////////////////////////////////////////////////////////////////
// Funktionen für die Arbeit mit WMPunkt'en
// Abstand zwischen den Punkten AP und EP mit Maximum-Norm
template <typename KoOrdT>
KoOrdT AbstandPktPktM (WMPunkt<KoOrdT> const &P1, WMPunkt<KoOrdT> const &P2);
template <typename KoOrdT>
KoOrdT AbstandPktPktM (KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2);

// Abstand zwischen den Punkten AP(x1,y1) und EP(x2,y2) mit euklidischer Norm
template <typename KoOrdT>
double AbstandPktPktE (WMPunkt<KoOrdT> const &AP, WMPunkt<KoOrdT> const &EP);
template <typename KoOrdT>
double AbstandPktPktE (KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2);

// Kreuzprodukt zweier Vektoren mit Endpunkten Pkt1 und Pkt2
template <typename KoOrdT>
double KreuzProd (WMPunkt<KoOrdT> const &P1, WMPunkt<KoOrdT> const &P2);

// Kollinearität von 3 Punkten (true), sonst false
template <typename KoOrdT>
bool Kollinear (WMPunkt<KoOrdT> const &P1, WMPunkt<KoOrdT> const &P2, 
	WMPunkt<KoOrdT> const &P3);
template <typename KoOrdT>
bool Kollinear (KoOrdT x1, KoOrdT y1, KoOrdT x2, KoOrdT y2, KoOrdT x3, KoOrdT y3);

// Epsilon-Kollinearität von 3 Punkten (true), sonst false
template <typename KoOrdT>
bool EpsKollinear (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3, int iEpsilon = iKoEps);

// 3 Punkte sind paarweise eps-verschieden (true), sonst false
template <typename KoOrdT>
bool PaarVergl (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3, int eps);

// für 3 Punkte gilt, daß P2 von P1 und P3 eps-verschieden ist (true), sonst false
template <typename KoOrdT>
bool MittVergl (WMPunkt<KoOrdT> const &Pkt1, WMPunkt<KoOrdT> const &Pkt2, 
	WMPunkt<KoOrdT> const &Pkt3, int eps);

// Rechteck aus den 2 Punkten Pkt1 und Pkt2 bilden
template <typename KoOrdT>
WMObjRechteck<KoOrdT> BuildRectangle (WMPunkt<KoOrdT> const &Pkt1, 
	WMPunkt<KoOrdT> const &Pkt2);

// Schwerpunkt des Dreiecks Pkt1-Pkt2-Pkt3
template <typename KoOrdT>
DoublePair SchwerPunkt (WMPunkt<KoOrdT> &Pkt1, WMPunkt<KoOrdT> &Pkt2, 
	WMPunkt<KoOrdT> &Pkt3);

} // namespace trias_wmgeometry

#endif // !defined(_PUNKT_H__DB8B76D2_27A0_4F60_978F_341B1EC5D90B__INCLUDED_)
