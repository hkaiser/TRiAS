// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 07/10/1998 10:45:00 PM
//
// @doc
// @module TRiASConnectionCTF.h | Declaration of the <c CTRiASConnectionCTF> class

#if !defined(_TRIASCONNECTIONCTF_H__B22F49A6_1833_11D2_9E90_006008447800__INCLUDED_)
#define _TRIASCONNECTIONCTF_H__B22F49A6_1833_11D2_9E90_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnectionCTF
class ATL_NO_VTABLE CTRiASConnectionCTF : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASPropertyCallback, 
	public IObjectWithSite,
	public CReportErrorComCoClass<CTRiASConnectionCTF, &CLSID_TRiASCTFConnection, &IID_ITRiASPropertyCallback>
{
public:
	CTRiASConnectionCTF()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCONNECTIONCTF)
	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CTRiASConnectionCTF)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}

// ITRiASPropertyCallback
public:
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

// IObjectWithSite
	STDMETHOD(SetSite)(IUnknown *pISite);
	STDMETHOD(GetSite)(REFIID riid, void **ppvSite);

private:
	WTRiASConnection m_Conn;
};

#endif // !defined(_TRIASCONNECTIONCTF_H__B22F49A6_1833_11D2_9E90_006008447800__INCLUDED_)
