// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.01.2002 16:51:31 
//
// @doc
// @module GeometryObjects.inl | Declaration of the <c CGeometryObjects> class

// WMObjRechteck und Elementarobjekte WMPunkt, WMKante, WMFlaeche
// Original: W. Mörtl

#if !defined(_GEOMETRYOBJECTS_INL__CF849E13_C644_4F1E_8321_1D89CDCCB031__INCLUDED_)
#define _GEOMETRYOBJECTS_INL__CF849E13_C644_4F1E_8321_1D89CDCCB031__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <math.h>
#include "GeometryObjects.h"

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen 
template <typename KoOrdT>
inline KoOrdT 
KoOrdAbs (KoOrdT x) 
{ 
	return x >= 0 ? x : -x; 
}

template <typename KoOrdT>
inline KoOrdT 
KoOrdMin (KoOrdT x, KoOrdT y) 
{ 
	return x < y ? x : y; 
}

template <typename KoOrdT>
inline KoOrdT KoOrdMax (KoOrdT x, KoOrdT y) 
{ 
	return x > y ? x : y; 
}

///////////////////////////////////////////////////////////////////////////////
// Konvertierung von double nach anderen Datentyp
template <typename KoOrdT>
inline KoOrdT 
DtoLH (double D)
{
	if (D > 0)
		return (KoOrdT)(D + 0.5);
	else
		return (KoOrdT)(D - 0.5);
}

template<>
inline double
DtoLH (double D)
{
	return D;
}

///////////////////////////////////////////////////////////////////////////////
//
//	WMObjekt - Gemeinsame Basisklasse für ElementarObjekte
//
///////////////////////////////////////////////////////////////////////////////
template <typename KoOrdT>
inline 
WMObjekt<KoOrdT>::WMObjekt()
{
}

template <typename KoOrdT>
inline 
WMObjekt<KoOrdT>::~WMObjekt()
{
}

template <typename KoOrdT>
inline bool 
WMObjekt<KoOrdT>::Clipping (WMObjekt<KoOrdT> *pEO, int iOT, 
	unsigned long ulLageAusw, WMClipListe<KoOrdT> &CL, int iSkip, WMPosit &Lage, 
	bool &bAbbr, void *pPSt)
{
	return true;	// intentionally left empty
}

template <typename KoOrdT>
inline bool 
WMObjekt<KoOrdT>::AddClipObjekt (WMClipListe<KoOrdT> &CL)
{
	return true;	// intentionally left empty
}

} // namespace trias_wmgeometry

///////////////////////////////////////////////////////////////////////////////
// sonstige Geometrien
#include "Geometries/BasicFunctions.inl"

#include "Geometries/Rechteck.inl"
#include "Geometries/Punkt.inl"
#include "Geometries/Strecke.inl"
#include "Geometries/MarkObjects.inl"
#include "Geometries/Kante.inl"
#include "Geometries/Flaeche.inl"

#include "Geometries/ErrorCorrection.inl"

#endif // !defined(_GEOMETRYOBJECTS_INL__CF849E13_C644_4F1E_8321_1D89CDCCB031__INCLUDED_)
