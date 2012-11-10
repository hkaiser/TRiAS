// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.10.2000 13:55:56 
//
// @doc
// @module EllipsParams.h | Declaration of the <c CEllipsoidParams> class

#if !defined(_ELLIPSPARAMS_H__DF08FB10_1779_4236_BE02_577F86EF3C5F__INCLUDED_)
#define _ELLIPSPARAMS_H__DF08FB10_1779_4236_BE02_577F86EF3C5F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Quadrat
inline double Sqr(double x) { return x * x; }
inline double Cube(double x) { return x*x*x; }

///////////////////////////////////////////////////////////////////////////////
// Parameter des Ellipsoides
typedef struct tagELLIPSPAR {
	double	m_HA;		// Hauptachse, i.a. konstant bzw. gebenen
	double	m_f;		// Abplattung, i.a. konstant bzw. gegeben
	double	m_HB;		// Nebenachse: hb=(1-f)*ha
	double	m_e2;		// Exzentrizit‰t: e≤=2*f-f≤
	double	m_e12;		// 1-e≤
	double	m_e22;		// e'≤ = (ha≤-hb≤)/hb≤
} ELLIPSPAR;

///////////////////////////////////////////////////////////////////////////////
// Helper zur Berechnung von diversen Ellipsoid-Parametern
class CEllipsoidParams :
	public ELLIPSPAR
{
public:
	CEllipsoidParams() {}
	CEllipsoidParams(double ha, double f) 
	{
		m_HA = ha;
		m_f = f;
		Recompute();
	}
	~CEllipsoidParams() {}

	void SetMajorAxis (double dHa)
	{
		m_HA = dHa;
		Recompute();
	}
	void SetFlattening (double f)
	{
		m_f = f;
		Recompute();
	}
	void SetParams (double dHa, double df)
	{
		m_HA = dHa;
		m_f = df;
		Recompute();
	}

	double Ha() { return m_HA; }
	double Hb() { return m_HB; }
	double Flatening() { return m_f; }
	double OneF() { return sqrt(m_e12); }
	double Excentricity() { return m_e22; }

	bool IsEllipse() { return (0 != m_f) ? true : false; }
	double Radius (DIST_ACCURACY rgAcc, double dLat) 
	{
		switch (rgAcc) {
		case ACCURACY_SphericArithMean:
			return (m_HA + m_HB) / 2.;

		case ACCURACY_SphericGeomMean:
			return sqrt(m_HA * m_HB);

		case ACCURACY_SphericHarmMean:
			return 2. * m_HA * m_HB / (m_HA + m_HB);

		case ACCURACY_SphericVolume:
			return m_HA * (1. - m_e2 * ((1./6.) + m_e2 * ((5./72.) + m_e2 * (55./1296.))));
			
		case ACCURACY_SphericArea:
			return m_HA * (1. - m_e2 * ((1./6.) + m_e2 * ((17./360.) + m_e2 * (67./3024.))));

		case ACCURACY_SphericGeomMeanCurvatureRadii:
			return m_HA * sqrt(1 - m_e22) / (1 - m_e22 * Sqr(sin(dLat))) ;

		case ACCURACY_SphericMajorAxis:
		default:
			return m_HA;		// default liefert groﬂe Halbachse
		}
	}

protected:
	static double Ha (double ha, double f) { return (1 - f) * ha; }		// kleine Halbachse: hb = (1-f)*ha
	static double Flatening (double ha, double hb) { return (ha - hb)/ha; }		// Abplattung: f = (ha-hb)/ha
	static double Excentricity2 (double f) { return f * (2 - f); }				// Exzentrizit‰t: e≤ = 2*f-f≤
	static double Excentricity12 (double f) { return 1 - Excentricity2(f); }				// 1 - e≤
	static double Excentricity22 (double ha, double hb) { return Sqr(ha) / Sqr(hb) - 1; }	// e'≤ = (ha≤-hb≤)/hb≤

	void Recompute()
	{
		m_HB = Ha(m_HA, m_f);
		m_e2 = Excentricity2(m_f);
		m_e12 = Excentricity12(m_f);
		m_e22 = Excentricity22(m_HA, m_HB);
	}
};

#endif // !defined(_ELLIPSPARAMS_H__DF08FB10_1779_4236_BE02_577F86EF3C5F__INCLUDED_)
