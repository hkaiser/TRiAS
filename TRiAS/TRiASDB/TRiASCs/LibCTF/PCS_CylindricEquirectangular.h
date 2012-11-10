// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:17:01 
//
// @doc
// @module PCS_CylindricEquirectangular.h | Declaration of the <c CTPCSCylindricEquirectangular> class

#if !defined(_PCS_CYLINDRICEQUIRECTANGULAR_H__286B640B_87FE_42A1_BF54_2111BA6431DC__INCLUDED_)
#define _PCS_CYLINDRICEQUIRECTANGULAR_H__286B640B_87FE_42A1_BF54_2111BA6431DC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CTPCSCylindricEquirectangular : 
	public CTransform 
{
private:
	double m_latOrigin;
	double m_lonOrigin;
	double m_falseEasting;
	double m_falseNorthing;

public:
	CTPCSCylindricEquirectangular() :
		m_latOrigin(0),
		m_lonOrigin(0),
		m_falseEasting(0),
		m_falseNorthing(0)
	{
	}
	
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
};

#endif // !defined(_PCS_CYLINDRICEQUIRECTANGULAR_H__286B640B_87FE_42A1_BF54_2111BA6431DC__INCLUDED_)
