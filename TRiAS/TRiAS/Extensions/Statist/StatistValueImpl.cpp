// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.01.2001 11:05:45 
//
// @doc
// @module StatistValueImpl.cpp | Declaration of several statistics classes

/////////////////////////////////////////////////////////////////////////////
// CStatistValue
inline 
STDMETHODIMP CStatistValue::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGenericStatistics
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// implementation
inline 
HRESULT CStatistValue::AddValue(double dValue, VARIANT vData)
{
	_ASSERTE(m_CumPts.IsValid());
	return m_CumPts -> AddValue(dValue, vData);
}

inline 
HRESULT CStatistValue::RemoveValue(double dValue)
{
	_ASSERTE(m_CumPts.IsValid());
	return m_CumPts -> RemoveValue(dValue);
}

inline 
HRESULT CStatistValue::Reset()
{
	_ASSERTE(m_CumPts.IsValid());
	return m_CumPts -> Reset();
}

