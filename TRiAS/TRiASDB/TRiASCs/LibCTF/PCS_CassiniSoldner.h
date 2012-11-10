// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.01.2001 12:36:28 
//
// @doc
// @module PCS_CassiniSoldner.h | Declaration of the <c CPCS_CassiniSoldner> class

#if !defined(_PCS_CASSINISOLDNER_H__76FC9EAD_62EA_4C45_91A4_68ACAF8458E7__INCLUDED_)
#define _PCS_CASSINISOLDNER_H__76FC9EAD_62EA_4C45_91A4_68ACAF8458E7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CTPCSCassiniSoldner : 
	public CTransform 
{
private:
	bool m_fIsInitialized;

	double m_latOrigin;
	double m_lonOrigin;
	double m_falseEasting;
	double m_falseNorthing;

public:
	CTPCSCassiniSoldner() :
		m_fIsInitialized(false),
		m_latOrigin(0), m_lonOrigin(0), m_falseEasting(0), m_falseNorthing(0)
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
	HRESULT esogeo (double Y, double X, double &rB, double &rL);
	HRESULT geoeso (double B, double L, double &rY, double &rX);
};

#endif // !defined(_PCS_CASSINISOLDNER_H__76FC9EAD_62EA_4C45_91A4_68ACAF8458E7__INCLUDED_)
