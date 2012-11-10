// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 13:01:31 
//
// @doc
// @module Rechteck.inl | Declaration of the <c CRechteck> class

#if !defined(_RECHTECK_INL__ABE95CD1_B91C_45E4_B76B_10CA128251E2__INCLUDED_)
#define _RECHTECK_INL__ABE95CD1_B91C_45E4_B76B_10CA128251E2__INCLUDED_

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
//	WMRechteck - kleinstes umschließendes Rechteck eines geometrischen Objektes 
//
///////////////////////////////////////////////////////////////////////////////
template <typename KoOrdT>
inline
WMObjRechteck<KoOrdT>::WMObjRechteck (
	KoOrdT XMin, KoOrdT XMax, KoOrdT YMin, KoOrdT YMax) :
		_XMin(XMin), _XMax(XMax), _YMin(YMin), _YMax(_YMax)
{
}

template <typename KoOrdT>
inline
WMObjRechteck<KoOrdT>::WMObjRechteck (WMPunkt<KoOrdT> Pt, WMAusdehnung<KoOrdT> A) :
	_XMin(Pt.X()), _XMax(_XMin+A.Breite()), 
	_YMin(Pt.Y()), _YMax(_YMin+A.Hoehe())
{
}

template <typename KoOrdT>
inline
WMObjRechteck<KoOrdT>::WMObjRechteck (WMPunkt<KoOrdT> Pt1, WMPunkt<KoOrdT> Pt2) :
	_XMin(Pt1.X()), _XMax(Pt2.X()), _YMin(Pt1.Y()), _YMax(Pt2.Y())
{
}

template <typename KoOrdT>
inline
WMObjRechteck<KoOrdT>::WMObjRechteck (const WMObjRechteck &OC) :
	_XMin(OC._XMin), _XMax(OC._XMax), _YMin(OC._YMin), _YMax(OC._YMax)
{
}

template <typename KoOrdT>
inline
WMObjRechteck<KoOrdT>::~WMObjRechteck (void) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen
template <typename KoOrdT>
inline KoOrdT &
WMObjRechteck<KoOrdT>::XMin() 
{ 
	return _XMin; 
}

template <typename KoOrdT>
inline KoOrdT &
WMObjRechteck<KoOrdT>::XMax() 
{ 
	return _XMax; 
}

template <typename KoOrdT>
inline KoOrdT &
WMObjRechteck<KoOrdT>::YMin() 
{ 
	return _YMin; 
}

template <typename KoOrdT>
inline KoOrdT &
WMObjRechteck<KoOrdT>::YMax() 
{ 
	return _YMax; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMObjRechteck<KoOrdT>::XMin() const
{ 
	return _XMin; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMObjRechteck<KoOrdT>::XMax() const
{ 
	return _XMax; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMObjRechteck<KoOrdT>::YMin() const
{ 
	return _YMin; 
}

template <typename KoOrdT>
inline KoOrdT const &
WMObjRechteck<KoOrdT>::YMax() const
{ 
	return _YMax; 
}

template <typename KoOrdT>
inline void
WMObjRechteck<KoOrdT>::SetXMin(const KoOrdT &xmin) 
{ 
	_XMin = xmin; 
}

template <typename KoOrdT>
inline void
WMObjRechteck<KoOrdT>::SetXMax(const KoOrdT &xmax) 
{ 
	_XMax = xmax; 
}

template <typename KoOrdT>
inline void
WMObjRechteck<KoOrdT>::SetYMin(const KoOrdT &ymin) 
{ 
	_YMin = ymin; 
}

template <typename KoOrdT>
inline void
WMObjRechteck<KoOrdT>::SetYMax(const KoOrdT &ymax) 
{ 
	_YMax = ymax; 
}

template <typename KoOrdT>
inline KoOrdT 
WMObjRechteck<KoOrdT>::Breite() const 
{ 
	return KoOrdAbs(_XMax-_XMin); 
}

template <typename KoOrdT>
inline KoOrdT 
WMObjRechteck<KoOrdT>::Hoehe() const 
{ 
	return KoOrdAbs(_YMax-_YMin); 
}

// Container größer/kleiner
template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> 
WMObjRechteck<KoOrdT>::InflateCont (int iPercent)	const
{
	KoOrdT dX = ((XMax()-XMin()) * iPercent)/200;
	KoOrdT dY = ((YMax()-YMin()) * iPercent)/200;
	return WMObjRechteck (XMin()-dX, XMax()+dX, YMin()-dY, YMax()+dY);
}

// Container verschieben
template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> &
WMObjRechteck<KoOrdT>::ShiftCont (WMAusdehnung<KoOrdT> &A)
{
	XMin() += A.Breite();
	XMax() += A.Breite();
	YMin() += A.Hoehe();
	YMax() += A.Hoehe();
	return *this;
}

// wenn alle Werte oder die Abmessungen gleich 0 sind, dann ist der OC inValid
template <typename KoOrdT>
inline bool
WMObjRechteck<KoOrdT>::isValid() const 
{ 
	return !(0 == _XMax-_XMin && 0 == _YMax-_YMin); 
}

///////////////////////////////////////////////////////////////////////////////
// Operator testet Verschnitt zweier WMObjRechtecke, liefert, ob Flächeninhalt 
// des Durchschnitts > 0 (true)
//template <typename KoOrdT>
//inline bool 
//WMObjRechteck::operator^ (WMObjRechteck &)
//{
//}

// 2 Container haben mindestens 1 Punkt gemeinsam (true), sonst false
template <typename KoOrdT>
inline bool 
WMObjRechteck<KoOrdT>::Durchschnitt (WMObjRechteck& OC)
{
	return (_XMax >= OC._XMin && OC._XMax >= _XMin &&
			_YMax >= OC._YMin && OC._YMax >= _YMin);
}

// 2 Container haben nach Zugabe einer Eps-Toleranz (sowohl in x- als auch 
// in y-Richtung) mindestens 1 Punkt gemeinsam (true), sonst false
template <typename KoOrdT>
inline bool 
WMObjRechteck<KoOrdT>::EpsDurchschnitt (WMObjRechteck& OC, KoOrdT lEpsX, KoOrdT lEpsY)
{
	return (_XMax+lEpsX >= OC._XMin && OC._XMax+lEpsX >= _XMin &&
			_YMax+lEpsY >= OC._YMin && OC._YMax+lEpsY >= _YMin);
}

// Durchschnitt zweier Container ermitteln und als neuen Container in pDC 
// zurückgeben. Der Durchschnittscontainer kann zu einem Punkt oder einer Kante 
// entarten. Haben beide Ausgangscontainer keinen einzigen Punkt gemeinsam, 
// wird false zurückgegeben, sonst true
template <typename KoOrdT>
inline bool 
WMObjRechteck<KoOrdT>::DurchschnittsCont (WMObjRechteck& AC, WMObjRechteck& DC)
{
	DC.SetXMin (max (_XMin, AC._XMin));
	DC.SetXMax (min (_XMax, AC._XMax));
	DC.SetYMin (max (_YMin, AC._YMin));
	DC.SetYMax (min (_YMax, AC._YMax));
	if (DC.XMin() <= DC.XMax() && DC.YMin() <= DC.YMax())
		return true;
	return false;
}

//WMObjRechteck DurchschnittsCont (WMObjRechteck* pOC);
//WMObjRechteck &operator+ (WMObjRechteck &);
//void operator+= (WMObjRechteck &);

///////////////////////////////////////////////////////////////////////////////
// Vergleichsoperatoren
template <typename KoOrdT>
inline
bool operator> (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2)
{
	return !(O1 <= O2);
}

template <typename KoOrdT>
inline
bool operator>= (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2)
{
	return (O1.XMin() <= O2.XMin() && O1.XMax() >= O2.XMax() &&
			O1.YMin() <= O2.YMin() && O1.YMax() >= O2.YMax());
}

template <typename KoOrdT>
inline
bool operator< (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2)
{
	return !(O1 >= O2);
}

template <typename KoOrdT>
inline
bool operator<= (WMObjRechteck<KoOrdT> &O1, WMObjRechteck<KoOrdT> &O2)
{
	return (O1.XMin() >= O2.XMin() && O1.XMax() <= O2.XMax() &&
			O1.YMin() >= O2.YMin() && O1.YMax() <= O2.YMax());
}

} // namespace trias_wmgeometry

#endif // !defined(_RECHTECK_INL__ABE95CD1_B91C_45E4_B76B_10CA128251E2__INCLUDED_)
