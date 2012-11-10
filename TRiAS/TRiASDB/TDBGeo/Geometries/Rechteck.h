// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 13:00:05 
//
// @doc
// @module Rechteck.h | Declaration of the <c CRechteck> class

#if !defined(_RECHTECK_H__60B8B97F_A650_4D71_B2ED_829C2EF40B9B__INCLUDED_)
#define _RECHTECK_H__60B8B97F_A650_4D71_B2ED_829C2EF40B9B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry  {

///////////////////////////////////////////////////////////////////////////////
// kleinstes umschlieﬂendes Rechteck eines geometrischen Objektes 
template <typename KoOrdT>
class WMObjRechteck 
{
protected:
	KoOrdT _XMin, _XMax;
	KoOrdT _YMin, _YMax;

public:
// Konstruktoren
	WMObjRechteck (KoOrdT XMin = 0, KoOrdT XMax = 0, KoOrdT YMin = 0, KoOrdT YMax = 0);
	WMObjRechteck (WMPunkt<KoOrdT> Pt, WMAusdehnung<KoOrdT> A);
	WMObjRechteck (WMPunkt<KoOrdT> Pt1, WMPunkt<KoOrdT> Pt2);
	WMObjRechteck (WMObjRechteck const &OC);
	~WMObjRechteck (void);

// Memberfunktionen
	KoOrdT &XMin();    // liefert Referenzen auf Attribute
	KoOrdT &XMax();
	KoOrdT &YMin();
	KoOrdT &YMax();

	KoOrdT const &XMin() const;    // liefert Referenzen auf Attribute
	KoOrdT const &XMax() const;
	KoOrdT const &YMin() const;
	KoOrdT const &YMax() const;

	void SetXMin(const KoOrdT &xmin);
	void SetXMax(const KoOrdT &xmax);
	void SetYMin(const KoOrdT &ymin);
	void SetYMax(const KoOrdT &ymax);

	KoOrdT Breite() const;
	KoOrdT Hoehe() const;

	WMObjRechteck InflateCont (int iPercent)	const;	// Container grˆﬂer/kleiner
	WMObjRechteck &ShiftCont (WMAusdehnung &A);		// Container verschieben

// wenn alle Werte oder die Abmessungen gleich 0 sind, dann ist der OC inValid
	bool isValid() const;

// Operator testet Verschnitt zweier WMObjRechteck
	bool Durchschnitt (WMObjRechteck& OC);	// mind. 1 Punkt gemeinsam (true)
	bool EpsDurchschnitt (WMObjRechteck& OC, KoOrdT lEpsX = iCoEps, KoOrdT lEpsY = iCoEps);
	bool DurchschnittsCont (WMObjRechteck& AC, WMObjRechteck& DC);

// obsolete
//	bool operator^ (WMObjRechteck &);			// Fl‰cheninhalt des Durchschnitts > 0 (true)
//	WMObjRechteck DurchschnittsCont (WMObjRechteck* pOC);
//	WMObjRechteck &operator+ (WMObjRechteck &);
//	void operator+= (WMObjRechteck &);
};

///////////////////////////////////////////////////////////////////////////////
// Vergleichsoperatoren
template <typename KoOrdT>
bool operator> (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2);

template <typename KoOrdT>
bool operator>= (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2);

template <typename KoOrdT>
bool operator< (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2);

template <typename KoOrdT>
bool operator<= (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2);

} // namespace trias_wmgeometry

#endif // !defined(_RECHTECK_H__60B8B97F_A650_4D71_B2ED_829C2EF40B9B__INCLUDED_)
