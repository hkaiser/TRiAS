// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.05.2001 18:44:02 
//
// @doc
// @module IObjectWithSiteRowsetImpl.h | Declaration of the <c CIObjectWithSiteCommandImpl> class

#if !defined(_IOBJECTWITHSITEROWSETIMPL_H__B9457389_A6BC_4CAF_8AE5_AF788153D089__INCLUDED_)
#define _IOBJECTWITHSITEROWSETIMPL_H__B9457389_A6BC_4CAF_8AE5_AF788153D089__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

template<typename T, typename Base>
class ATL_NO_VTABLE IObjectWithSiteRowsetImpl :
	public Base
{
public:
	~IObjectWithSiteRowsetImpl()
	{
	CComPtr<IInternalConnection> pConn;
	T* pT = static_cast<T *>(this);

		if (pT -> m_spUnkSite != NULL)
		{
			if (SUCCEEDED(pT -> m_spUnkSite->QueryInterface(IID_IInternalConnection, (void **)&pConn)))
				pConn->ReleaseConnection();
		}
	}
	STDMETHOD(SetSite)(IUnknown* pCreator)
	{
	T* pT = static_cast<T *>(this);
	HRESULT hr = pT -> IRowsetCreatorImpl<T>::SetSite(pCreator);

		if (FAILED(hr)) return hr;
	
	CComPtr<IInternalConnection> pConn;
	
		if (pCreator != NULL) {
			hr = pCreator->QueryInterface(IID_IInternalConnection, (void **)&pConn);
			if (SUCCEEDED(hr))
				hr = pConn->AddConnection();
		}
		return hr;
	}
};

#endif // !defined(_IOBJECTWITHSITEROWSETIMPL_H__B9457389_A6BC_4CAF_8AE5_AF788153D089__INCLUDED_)
