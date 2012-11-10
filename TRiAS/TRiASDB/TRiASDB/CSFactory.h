// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 09/10/1998 03:27:18 PM
//
// @doc
// @module CSFactory.h | Description goes here

#if !defined(_CSFACTORY_H__4480D1A6_481C_11D2_9EBF_006008447800__INCLUDED_)
#define _CSFACTORY_H__4480D1A6_481C_11D2_9EBF_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// benötigte TLB's
#import "Tlb/TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids \
	exclude("IStaticCollection", "IEnumCoordSystemNames")

/////////////////////////////////////////////////////////////////////////////
// CCSFactory
class CCSFactory 
{
public:
	CCSFactory() :
		m_fIsUserDefined(false), m_fIsTransverseMercator(false), m_fIsCassiniSoldner(false),
		m_dMeridian(0.0), m_dBreite(0.0), m_dFalseX(0.0), m_dFalseY(0.0), 
		m_dScale(1.0), m_dZoneWidth(0.0), m_rgType(tcsCS_Undefined),
		m_rgDatum(tcsGD_WorldGeodeticSystem1984),
		m_rgProj(tcsPA_Undefined)
	{
	}
	~CCSFactory() {}

	HRESULT RetrieveCS (ITRiASPropertyBase *pIPropBase, ITRiASCS **ppICS);
	HRESULT ReInitCS (ITRiASPropertyBase *pIPropBase, ITRiASCS *pICS);

// Zugriffsfunktionen
	bool IsTransverseMercator() { return m_fIsTransverseMercator; }
	bool IsCassiniSoldner() { return m_fIsCassiniSoldner; }
	bool IsUserDefined() { return m_fIsUserDefined; }
	bool IsProjected() { return tcsCS_Projected == m_rgType ? true : false; }

	TRIASCSTYPE GetType() { return m_rgType; }
	TRIASCSGEODETICDATUM GetGeodDatum() { return m_rgDatum; }
	TRIASCSPROJECTIONALGORITHM GetProjectionAlgorithm() { return m_rgProj; }
	TRIASCSPRIMEMERIDIAN GetPrimeMeridian() { return tcsPM_Greenwich; }

	TRIASCSUNITOFANGLE GetUnitOfAngle() { return tcsUOA_Second; }
	TRIASCSUNITOFLENGTH GetUnitOfLength() { return tcsUOL_Metre; }

	double GetLongitude() { return m_dMeridian; }
	double GetLatitude() { return m_dBreite; }
	double GetScaleFactor() { return m_dScale; }
	double GetFalseX() { return m_dFalseX; }
	double GetFalseY() { return m_dFalseY; }
	double GetZoneWidth() { return m_dZoneWidth; }

protected:
	HRESULT InitDataFromProject (void);

	double RetrieveLongitude();		// Meridian bestimmen
	double RetrieveLatitude();		// Breite bestimmen
	double RetrieveFalseX();		// FalseX bestimmen
	double RetrieveFalseY();		// FalseY bestimmen
	double RetrieveScaleAtNaturalOrigin (double dScaleDefault = 1.0);		// Stauchungsfaktor bestimmen
	TRIASCSGEODETICDATUM RetrieveDHDNDatum();

private:
// Parameter der Koordinatentransformation
	TRIASCSTYPE m_rgType;
	TRIASCSGEODETICDATUM m_rgDatum;
	TRIASCSPROJECTIONALGORITHM m_rgProj;

	double m_dMeridian;
	double m_dBreite;
	double m_dFalseX;
	double m_dFalseY;
	double m_dScale;
	double m_dZoneWidth;

	bool m_fIsUserDefined;
	bool m_fIsTransverseMercator;
	bool m_fIsCassiniSoldner;

	WTRiASProperties m_Props;
};

#endif // !defined(_CSFACTORY_H__4480D1A6_481C_11D2_9EBF_006008447800__INCLUDED_)
