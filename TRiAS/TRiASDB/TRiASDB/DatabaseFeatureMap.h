// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 08/26/1998 11:41:27 PM
//
// @doc
// @module DatabaseFeatureMap.h | Declaration of the <c CDatabaseFeatureMap> class

#if !defined(_DATABASEFEATUREMAP_H__32E4EC79_3D14_11D2_9EB6_006008447800__INCLUDED_)
#define _DATABASEFEATUREMAP_H__32E4EC79_3D14_11D2_9EB6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols
#include "TRiASDBGuids.h"

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFeatureMap
class ATL_NO_VTABLE CDatabaseFeatureMap : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CDatabaseFeatureMap, &CLSID_DatabaseFeatureMap, &IID_ITRiASPropertyCallback>,
	public ITRiASPropertyCallback,
	public IObjectWithSite
{
public:
	CDatabaseFeatureMap()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CDatabaseFeatureMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_DATABASEFEATUREMAP)
	DECLARE_NOT_AGGREGATABLE(CDatabaseFeatureMap)

	BEGIN_COM_MAP(CDatabaseFeatureMap)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

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

protected:
	HRESULT GetDatabaseFeatureMap (VARIANT *pVal);

private:
	WTRiASObjects m_Objs;		// hängt an dieser Objektmenge
};

#endif // !defined(_DATABASEFEATUREMAP_H__32E4EC79_3D14_11D2_9EB6_006008447800__INCLUDED_)
