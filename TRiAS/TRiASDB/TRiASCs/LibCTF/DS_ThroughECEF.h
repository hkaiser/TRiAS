// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:18:27 
//
// @doc
// @module DS_ThroughECEF.h | Declaration of the <c CTDSThroughECEF> class

#if !defined(AFX_DS_THROUGHECEF_H__8EE5B366_FAE8_11D1_8F55_0060085FC1CE__INCLUDED_)
#define AFX_DS_THROUGHECEF_H__8EE5B366_FAE8_11D1_8F55_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTDSThroughECEF : 
	public CTransform  
{
private:
	ELLIPSPAR m_WGS84;
	ELLIPSPAR m_DstSys;
	double m_dx, m_dy, m_dz;

public:
	CTDSThroughECEF() 
		: m_dx(0), m_dy(0), m_dz(0)
	{
		m_WGS84.m_HA = HAWGS84;
		m_WGS84.m_f	= fWGS84;
		m_WGS84.m_HB = HB(HAWGS84, fWGS84); 
		m_WGS84.m_e2 = E2(fWGS84); 
		m_WGS84.m_e12 = E12(fWGS84); 
		m_WGS84.m_e22 = E22(HAWGS84, HB(HAWGS84, fWGS84));  
	} 
	virtual ~CTDSThroughECEF() {}

	virtual HRESULT SetModelParameters ();
	virtual HRESULT SetModelParameters2 (double HA2, double f2); 
	virtual	HRESULT SetParameters (long nParams, double *pParam); 
	virtual	HRESULT GetDefaults (long nParams, double *pParam); 
	virtual HRESULT Transform (long nCoords, LPTCSDBLCOORD pData); 
	virtual HRESULT TransformInverse (long nCoords, LPTCSDBLCOORD pData); 
	virtual HRESULT IsValid ();

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

inline HRESULT CTDSThroughECEF::SetModelParameters() 
{
	m_DstSys = m_WGS84;
	return S_OK;
}

#endif // !defined(AFX_DS_THROUGHECEF_H__8EE5B366_FAE8_11D1_8F55_0060085FC1CE__INCLUDED_)
