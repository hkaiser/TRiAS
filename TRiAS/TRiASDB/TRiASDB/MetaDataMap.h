// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.06.2000 14:51:37 
//
// @doc
// @module MetaDataMap.h | Declaration of the <c CMetaDataMap>,
// <c CObjectsMetaDataMap> and <c CFeatureMetaDataMap> classes

#if !defined(_METADATAMAP_H__1C28592D_EDA1_4379_87A2_8B94E7AF859B__INCLUDED_)
#define _METADATAMAP_H__1C28592D_EDA1_4379_87A2_8B94E7AF859B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'
#import "tlb/TRiASMDS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Dispatch);
DefineSmartInterface(TRiASMDSMap);

/////////////////////////////////////////////////////////////////////////////
// CFeatureMetaDataMap
class ATL_NO_VTABLE CMetaDataMap : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CMetaDataMap, &CLSID_TRiASMetaDataMap, &IID_ITRiASPropertyCallback>,
	public ITRiASPropertyCallback,
	public ITRiASValueEvents,
	public IObjectWithSite
{
public:
	CMetaDataMap() :
		m_dwCookie(0L)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CMetaDataMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_METADATAMAP_RGS)
	DECLARE_NOT_AGGREGATABLE(CMetaDataMap)

	BEGIN_COM_MAP(CMetaDataMap)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(ITRiASValueEvents)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
		_ASSERTE(0 == m_dwCookie);
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

// ITRiASValueEvents
	STDMETHOD(ModifyingValue)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ValueToModify)(/*[in]*/ BSTR Name);
	STDMETHOD(ValueModified)(/*[in]*/ BSTR Name);

protected:
	HRESULT GetFeatureMetaDataMap (VARIANT *pVal);
	HRESULT ReleaseFeatureMetaDataMap();
	HRESULT GenerateUniqueMapName();

private:
	WDispatch m_Target;			// hängt an diesem Objekt
	WTRiASMDSMap m_Map;			// gecachete Map
	CComBSTR m_bstrName;
	DWORD m_dwCookie;
};

#endif // !defined(_METADATAMAP_H__1C28592D_EDA1_4379_87A2_8B94E7AF859B__INCLUDED_)
