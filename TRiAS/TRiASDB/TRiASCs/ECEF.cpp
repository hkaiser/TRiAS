// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 28.02.2002 16:30:47 
//
// @doc
// @module ECEF.cpp | Definition of the <c CECEF> class

// http://www.utexas.edu/depts/grg/gcraft/notes/datum/datum.html
// http://www.utexas.edu/depts/grg/gcraft/notes/datum/gif/llhxyz.gif

#include "stdafx.h"
#include "LibCTF/LibCTFImpl.h"

///////////////////////////////////////////////////////////////////////////////
// 
//	X = (N + h) * cos(Lat) * cos(Lon)
//	Y = (N + h) * cos(Lat) * sin(Lon)
//	Z = (N * (1 - e²) + h) * sin(Lat)
//	X,Y,Z ECEF Koordinaten
//	N = N(phi) = a / sqrt( 1-e²*sin²(phi) ) 

void LLH2XYZ (ELLIPSPAR const& el, LPTCSDBLCOORD coord) 
{
double Lon = coord->c1;
double Lat = coord->c2;
double Hgt = coord->h;
double N = sin( Lat );

	N *= N;
	N *= el.m_e2;
	N = 1 - N;
	N = sqrt( N );
	N = el.m_HA / N;

double NandH = N + Hgt;
double X = NandH * cos( Lat ) * cos( Lon );
double Y = NandH * cos( Lat ) * sin( Lon );
double Z = ( N * el.m_e12 + Hgt ) * sin( Lat );

	coord->c1 = X;
	coord->c2 = Y;
	coord->h = Z;
}

///////////////////////////////////////////////////////////////////////////////
// 
void XYZ2LLH (ELLIPSPAR const& el, LPTCSDBLCOORD coord) 
{
double X = coord->c1;
double Y = coord->c2;
double H = coord->h;
double p = sqrt( X * X + Y * Y );
double t = atan2( H * el.m_HA, p * el.m_HB );
double cos3t = cos( t );
double sin3t = sin( t );

	cos3t = cos3t * cos3t * cos3t;
	sin3t = sin3t * sin3t * sin3t;

double Lat = atan2( H + el.m_e22 * el.m_HB * sin3t, p - el.m_e2 * el.m_HA * cos3t );
double N = sin( Lat );

	N *= N;
	N *= el.m_e2;
	N = 1 - N;
	N = sqrt( N );
	N = el.m_HA / N;

double	Lon = atan2( Y, X );

	H = p;
	H /= cos( Lat );
	H -= N;
	coord->c1 = Lon;
	coord->c2 = Lat;
	coord->h = H;
}

