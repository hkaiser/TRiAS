// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:12:50 
//
// @doc
// @module PCS_GaussKrueger.h | Declaration of the <c CTPCSGaussKrueger> class

#if !defined(_PCS_GAUSSKRUEGER_H__C72A8425_312B_4024_9B00_575DD106BDCF__INCLUDED_)
#define _PCS_GAUSSKRUEGER_H__C72A8425_312B_4024_9B00_575DD106BDCF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__) 
#endif

class CTPCSGaussKrueger : 
	public CTransform 
{
private:
	double m_latOrigin;
	double m_lonOrigin;
	double m_scaleAtOrigin;
	double m_falseEasting;
	double m_falseNorthing;
	int m_iZoneWidth;

	static const double m_p2, m_p12, m_p20, m_p30, m_p42, m_p360, m_p6;

	void geogau  (ELLIPSPAR const &el, double B, double L, double &H, double &R);
	void gaugeo  (ELLIPSPAR const &el, double H, double R, double &B, double &L);

/////////////////////////////////////////////////////////////////
// [entry(0x00000000) const short tcsPP_TransverseMercator_LatitudeOfNaturalOrigin = 1;
// [entry(0x00000001) const short tcsPP_TransverseMercator_LongitudeOfNaturalOrigin = 2;
// [entry(0x00000002) const short tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin = 5;
// [entry(0x00000003) const short tcsPP_TransverseMercator_FalseEasting = 6;
// [entry(0x00000004) const short tcsPP_TransverseMercator_FalseNorthing = 7;

	HRESULT GetLonOriginGK (double dX, double &rdLonOrigin);
	HRESULT GetFalseEastingGK (double dX, double &rdFalseEasting);
	HRESULT GetLonOriginGeod (double dX, double &rdLonOrigin);
	HRESULT GetFalseEastingGeod (double dX, double &rdFalseEasting);

public:
	CTPCSGaussKrueger() :
		m_latOrigin(0), m_lonOrigin(0), m_scaleAtOrigin(1),
		m_falseEasting(0), m_falseNorthing(0), m_iZoneWidth(0)
	{
	}

	virtual	HRESULT SetParameters (long nParams, double *pParam) ;
	virtual	HRESULT GetDefaults (long nParams, double *pParam) ;
	virtual HRESULT Transform (long nCoords, LPTCSDBLCOORD pData) ;
	virtual HRESULT TransformInverse (long nCoords, LPTCSDBLCOORD pData) ;
	virtual HRESULT IsValid ();

// UIHelper
	virtual HRESULT get_InputMask (COORDELEMENT rgElement, BSTR *pbstrMask);

#if defined(_USE_OGC_COMPATIBILITY)
// ISpatialReference
//	virtual HRESULT get_Name(BSTR *pbstrName);
//	virtual HRESULT put_Name(BSTR bstrName);
//	virtual HRESULT get_Code(long *plCode);
//	virtual HRESULT put_Code(long lCode);
//	virtual HRESULT get_Abbreviation(BSTR *pbstrAbbrev);
//	virtual HRESULT put_Abbreviation(BSTR bstrAbbrev);
//	virtual HRESULT get_WellKnownText(BSTR *pbstrWkt);
#endif // defined(_USE_OGC_COMPATIBILITY)
};

const double ARC_PI = 180.0 / tcsPI;

inline 
HRESULT CTPCSGaussKrueger::GetLonOriginGK (double dX, double &rdLonOrigin)
{
	if (3 == m_iZoneWidth)
		rdLonOrigin = ((int)( dX / (1000000.0 * m_scaleXOut) ) * 3) * (m_scaleXIn / ARC_PI);
	else
		rdLonOrigin = ((int)( dX / (1000000.0 * m_scaleXOut) ) * 6 - 3) * (m_scaleXIn / ARC_PI);

	return S_OK;
}

inline 
HRESULT CTPCSGaussKrueger::GetFalseEastingGK (double dX, double &rdFalseEasting)
{
	rdFalseEasting = ((int)( dX / (1000000.0 * m_scaleXOut) ) * 1000000.0 + 500000.0) * m_scaleXOut;
	return S_OK;
}

inline 
HRESULT CTPCSGaussKrueger::GetLonOriginGeod (double dX, double &rdLonOrigin)
{
	if (3 == m_iZoneWidth)
		rdLonOrigin = ((int)( ((dX * (ARC_PI / m_scaleXIn)) + 1.5) / 3 ) * 3) * (m_scaleXIn / ARC_PI);
	else
		rdLonOrigin = ((int)( dX * (ARC_PI / m_scaleXIn) / 6 ) * 6 + 3) * (m_scaleXIn / ARC_PI);

	return S_OK;
}

inline 
HRESULT CTPCSGaussKrueger::GetFalseEastingGeod (double dX, double &rdFalseEasting)
{
	if (3 == m_iZoneWidth)
		rdFalseEasting = ((int)( ((dX * (ARC_PI / m_scaleXIn)) + 1.5) / 3 ) * 1000000.0 + 500000.0) * m_scaleXOut;
	else
		rdFalseEasting = ((int)( dX * (ARC_PI / m_scaleXIn) / 6 + 1.0 ) * 1000000.0 + 500000.0) * m_scaleXOut;

	return S_OK;
}


#endif // !defined(_PCS_GAUSSKRUEGER_H__C72A8425_312B_4024_9B00_575DD106BDCF__INCLUDED_)
