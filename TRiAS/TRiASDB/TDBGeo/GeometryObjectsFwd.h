// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 03.02.2002 15:25:43 
//
// @doc
// @module GeometryObjectsFwd.h | Declaration of the <c CGeometryObjectsFwd> class

#if !defined(_GEOMETRYOBJECTSFWD_H__20214822_E3D1_429F_9E1F_D7BFEF36E8DA__INCLUDED_)
#define _GEOMETRYOBJECTSFWD_H__20214822_E3D1_429F_9E1F_D7BFEF36E8DA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Vorabdeklarationen
template <typename KoOrdT = double> class WMObjekt;
template <typename KoOrdT = double> class WMObjRechteck;
template <typename KoOrdT = double> class WMKoordinatenPaar;
template <typename KoOrdT = double> class WMPunkt;
template <typename KoOrdT = double> class WMKante;
template <typename KoOrdT = double> class WMFlaeche;
template <typename KoOrdT = double> class WMAusdehnung;
template <typename KoOrdT = double> class WMPunktVec;
template <typename KoOrdT = double> class WMStrecke;

template <typename KoOrdT = double> class WMClipListe;
class WMMarkVertex;
class WMMarkLine;

enum OGCWMPosit;

} // namespace trias_wmgeometry

#endif // !defined(_GEOMETRYOBJECTSFWD_H__20214822_E3D1_429F_9E1F_D7BFEF36E8DA__INCLUDED_)
