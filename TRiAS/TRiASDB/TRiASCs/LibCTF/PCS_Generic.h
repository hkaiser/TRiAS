// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:15:41 
//
// @doc
// @module PCS_Generic.h | Declaration of the <c CTPCSGeneric> class

#if !defined(_PCS_GENERIC_H__136BA120_7C7B_4BA7_94F7_47702DCE1398__INCLUDED_)
#define _PCS_GENERIC_H__136BA120_7C7B_4BA7_94F7_47702DCE1398__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CTPCSGeneric : 
	public CTransform 
{
private:
	bool m_fIsInitialized;

	double m_dK11, m_dK12, m_dK21, m_dK22, m_dOX, m_dOY;
	double m_dInvK11, m_dInvK12, m_dInvK21, m_dInvK22;

public:
	CTPCSGeneric()
		: m_fIsInitialized(false)
	{
		m_dK11 = m_dK22 = 1.0;
		m_dK12 = m_dK21 = m_dOX = m_dOY = 0.0;
		m_dInvK11 = m_dInvK22 = 1.0;
		m_dInvK12 = m_dInvK21 = 0.0;
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
};

#endif // !defined(_PCS_GENERIC_H__136BA120_7C7B_4BA7_94F7_47702DCE1398__INCLUDED_)
