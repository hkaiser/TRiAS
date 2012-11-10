// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.01.2000 13:20:46 
//
// @doc
// @module LIBCTFImpl.h | Helper definitions for CTransform

#include "../TRiASCS.hmc"
#include "../TRiASCS.h"

///////////////////////////////////////////////////////////////////////////////
// Helper constants and functions
const double HAWGS84 = 6378137.0;
const double fWGS84	= 1/298.257223563;
const double EPSLN = 1.0e-10;

///////////////////////////////////////////////////////////////////////////////
// 
#include "libCTF.h"

///////////////////////////////////////////////////////////////////////////////
// Helper constants and functions
const double PI = tcsPI;
const double HALF_PI = tcsHalfPI;
const double TWO_PI = tcsTwoPI;

inline double SQUARE(double x) { return x * x; }
inline double CUBE(double x) { return x * x * x; }
inline double QUAD(double x) { return x * x * x * x; }

///////////////////////////////////////////////////////////////////////////////
// ECEF transformations
void LLH2XYZ (ELLIPSPAR const& el, LPTCSDBLCOORD coord);
void XYZ2LLH (ELLIPSPAR const& el, LPTCSDBLCOORD coord);

///////////////////////////////////////////////////////////////////////////////
// from gctpc/cproj.c

// Function to adjust a longitude angle to range from -180 to 180 radians
// Parameters:
//  double x;		// Angle in radians
extern "C" double adjust_lon (double x);	

// Function to compute the constant small m which is the radius of
// a parallel of latitude, phi, divided by the semimajor axis.
// Parameters:
//  double eccent;	// Eccentricity of the spheroid
//  double sinphi;	// Sine of the latitude
//  double sinphi;	// Cosine of the latitude
extern "C" double msfnz (double eccent, double sinphi, double cosphi);

// Function to compute the constant small t for use in the forward
// computations in the Lambert Conformal Conic and the Polar
// Stereographic projections.
// Parameters:
//  double eccent;	// Eccentricity of the spheroid
//  double phi;		// Latitude phi
//  double sinphi;	// Sine of the latitude
extern "C" double tsfnz (double eccent, double phi, double sinphi);

// Function to compute the latitude angle, phi2, for the inverse of the
// Lambert Conformal Conic and Polar Stereographic projections.
// Parameters:
//  double eccent;	// Spheroid eccentricity
//  double ts;		// Constant value t
//  long *pflag;	// Error flag number
extern "C" double phi2z (double eccent, double ts, long *pflag);
