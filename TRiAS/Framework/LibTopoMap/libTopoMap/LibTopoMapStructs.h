// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 22.03.2002 14:50:01 
//
// @doc
// @module LibTopoMapStructs.h | Declaration of the <c CLibTopoMapStructs> class

#if !defined(_LIBTOPOMAPSTRUCTS_H__8EBFAC6F_DD04_457E_A061_D6D8C8416ACA__INCLUDED_)
#define _LIBTOPOMAPSTRUCTS_H__8EBFAC6F_DD04_457E_A061_D6D8C8416ACA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Ein Punkt in der Geographie

typedef	struct GEOPOINT {
	double	X;
	double	Y;
	double	Z;
	
	GEOPOINT() { X = Y = Z = 0; }
	GEOPOINT(double const& x, double const& y, double z = 0) 
	{ 
		X = x; Y = y; Z = z; 
	}
} GEOPOINT;

typedef vector< GEOPOINT >				GEOPOINTList;

/////////////////////////////////////////////////////////////////////////
// Eine Ausdehnung in der Geographie

typedef	struct GEOSIZE {
	double	dX;
	double	dY;
	GEOSIZE() { dX = dY = 0; }
	GEOSIZE(double const& dx, double const& dy ) {dX=dx;dY=dy;}
} GEOSIZE;

typedef vector< GEOSIZE >				GEOSIZEList;

/////////////////////////////////////////////////////////////////////////
// Ein (G)round (C)ontrol (P)oint

typedef struct GCP 
{
	GEOPOINT m_ptGeoCoord;
	GEOPOINT m_ptPictPoint;

	GCP();
	GCP(GEOPOINT const& p1, GEOPOINT const& p2);
	void Clear();
} GCP;

typedef vector<GCP> GCPList;

inline GCP::GCP() 
{ 
	Clear();
}

inline 
GCP::GCP(GEOPOINT const& worldPoint, GEOPOINT const& filePoint) 
{
	m_ptGeoCoord = worldPoint;
	m_ptPictPoint = filePoint;
}

inline 
void GCP::Clear() 
{
	m_ptGeoCoord = GEOPOINT();
	m_ptPictPoint = GEOPOINT();
}

#endif // !defined(_LIBTOPOMAPSTRUCTS_H__8EBFAC6F_DD04_457E_A061_D6D8C8416ACA__INCLUDED_)
