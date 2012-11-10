// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 28.02.2002 18:30:52 
//
// @doc
// @module DS_Through7Parameter.h | Declaration of the <c CDS_Through7Parameter> class

#if !defined(_DS_THROUGH7PARAMETER_H__56224970_5933_4786_A49D_16BB4BD75C81__INCLUDED_)
#define _DS_THROUGH7PARAMETER_H__56224970_5933_4786_A49D_16BB4BD75C81__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Position Vector Transformation
class CTDSThrough7ParameterPositionVector : 
	public CTransform  
{
protected:
	ELLIPSPAR m_WGS84;
	ELLIPSPAR m_DstSys;
	double m_dx, m_dy, m_dz;
	double m_rx, m_ry, m_rz;
	double m_ds;

public:
	CTDSThrough7ParameterPositionVector() :
		m_dx(0), m_dy(0), m_dz(0), m_rx(0), m_ry(0), m_rz(0), m_ds(0)
	{
		m_WGS84.m_HA = HAWGS84;
		m_WGS84.m_f	= fWGS84;
		m_WGS84.m_HB = HB(HAWGS84, fWGS84); 
		m_WGS84.m_e2 = E2(fWGS84); 
		m_WGS84.m_e12 = E12(fWGS84); 
		m_WGS84.m_e22 = E22(HAWGS84, HB(HAWGS84, fWGS84));  
	} 
	virtual ~CTDSThrough7ParameterPositionVector() {}

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

inline 
HRESULT CTDSThrough7ParameterPositionVector::SetModelParameters() 
{
	m_DstSys = m_WGS84;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Coordinate Frame Rotation Transformation
// (unterscheidet sich vom 'Position Vector Transformation' Algorithmus 
// lediglich durch den Drehwinkel der Rotation)
class CTDSThrough7ParameterCoordFrameRot :
	public CTDSThrough7ParameterPositionVector
{
public:
	CTDSThrough7ParameterCoordFrameRot() {}
	virtual ~CTDSThrough7ParameterCoordFrameRot() {}

	virtual	HRESULT SetParameters (long nParams, double *pParam); 
	virtual	HRESULT GetDefaults (long nParams, double *pParam); 
};

#endif // !defined(_DS_THROUGH7PARAMETER_H__56224970_5933_4786_A49D_16BB4BD75C81__INCLUDED_)
