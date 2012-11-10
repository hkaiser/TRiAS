// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.06.2000 14:51:37 
//
// @doc
// @module FeatureMetaDataMap.h | Declaration of the <c CFeatureMetaDataMap> class

#if !defined(_FEATUREMETADATAMAP_H__1C28592D_EDA1_4379_87A2_8B94E7AF859B__INCLUDED_)
#define _FEATUREMETADATAMAP_H__1C28592D_EDA1_4379_87A2_8B94E7AF859B__INCLUDED_

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
// {733F03EE-CECA-4E3B-ACEF-0920F7DB996F}
extern "C" const IID __declspec(selectany) CLSID_FeatureMetaDataMap = 
	{0x733f03ee,0xceca,0x4e3b,{0xac,0xef,0x09,0x20,0xf7,0xdb,0x99,0x6f}};

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASMDSMap);

/////////////////////////////////////////////////////////////////////////////
// CFeatureMetaDataMap
class ATL_NO_VTABLE CFeatureMetaDataMap : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CFeatureMetaDataMap, &CLSID_FeatureMetaDataMap>,
	public CErrSupport<CFeatureMetaDataMap, &IID_ITRiASPropertyCallback>,
	public ITRiASPropertyCallback,
	public ITRiASValueEvents,
	public IObjectWithSite
{
public:
	CFeatureMetaDataMap() :
		m_dwCookie(0L)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CFeatureMetaDataMap)

	DECLARE_REGISTRY_RESOURCEID(IDR_FEATUREMETADATAMAP_RGS)
	DECLARE_NOT_AGGREGATABLE(CFeatureMetaDataMap)

	BEGIN_COM_MAP(CFeatureMetaDataMap)
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
	WTRiASObjects m_Objs;		// hängt an dieser Objektmenge
	WTRiASMDSMap m_Map;			// gecachete Map
	CComBSTR m_bstrName;
	DWORD m_dwCookie;
};

#endif // !defined(_FEATUREMETADATAMAP_H__1C28592D_EDA1_4379_87A2_8B94E7AF859B__INCLUDED_)
