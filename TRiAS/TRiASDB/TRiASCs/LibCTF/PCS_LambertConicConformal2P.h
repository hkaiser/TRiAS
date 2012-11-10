// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.01.2000 13:15:12 
//
// @doc
// @module PCS_LambertConicConformal2P.h | Declaration of the <c CTPCSLambertConicConformal2P> class

#if !defined(_PCS_LAMBERTCONICCONFORMAL2P_H__BF818135_5EA5_45EC_8662_237F0B0B9D3F__INCLUDED_)
#define _PCS_LAMBERTCONICCONFORMAL2P_H__BF818135_5EA5_45EC_8662_237F0B0B9D3F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CTPCSLambertConicConformal2P : 
	public CTransform 
{
private:
	bool m_fIsInitialized;

	double m_latOrigin;
	double m_lonOrigin;
	double m_falseEasting;
	double m_falseNorthing;
	double m_firstParallel;
	double m_secondParallel;

	double m_es;				// eccentricity squared
	double m_e;					// eccentricity
	double m_ns;				// ratio of angle between meridian
	double m_f0;				// flattening of ellipsoid
	double m_rh;				// height above ellipsoid

public:
	CTPCSLambertConicConformal2P() :
		m_fIsInitialized(false),
		m_latOrigin(0), m_lonOrigin(0), m_falseEasting(0), m_falseNorthing(0),
		m_firstParallel(0), m_secondParallel(0),
		m_es(0), m_e(0), m_ns(0), m_f0(0), m_rh(0)
	{
	}
	HRESULT IsInitialized() { return m_fIsInitialized ? S_OK : S_FALSE; }

	virtual	HRESULT SetParameters(long nParams, double *pParam);
	virtual	HRESULT GetDefaults(long nParams, double *pParam);
	virtual HRESULT Transform(long nCoords, LPTCSDBLCOORD pData);
	virtual HRESULT TransformInverse(long nCoords, LPTCSDBLCOORD pData);
	virtual HRESULT IsValid();

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

protected:
	HRESULT EvalParams();	// weitere Parameter berechnen
};

#endif // !defined(_PCS_LAMBERTCONICCONFORMAL2P_H__BF818135_5EA5_45EC_8662_237F0B0B9D3F__INCLUDED_)
