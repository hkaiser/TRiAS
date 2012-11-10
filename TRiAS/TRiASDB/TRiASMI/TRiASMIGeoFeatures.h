// $Header: $
// Copyright� 1998-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 21:21:48 
//
// This file was generated by the TRiASDB Data Server Wizard V1.02.103 (#HK000729)
//
// @doc
// @module TRiASMIGeoFeatures.h | Declaration of the <c CTRiASMIGeoFeatures> class

#if !defined(_TRIASMIGEOFEATURES_H__B33C6E5E_ADCE_4E6B_B716_37B8C2D3D27A__INCLUDED_)
#define _TRIASMIGEOFEATURES_H__B33C6E5E_ADCE_4E6B_B716_37B8C2D3D27A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASMIGeoFeatures
class ATL_NO_VTABLE CTRiASMIGeoFeatures : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASMIGeoFeatures, &CLSID_TRiASSimpleGeoFeatures>,
	public CErrSupport<CTRiASMIGeoFeatures, &IID_ITRiASFeatures>,
	public ITRiASFeaturesCallback
{
public:
	CTRiASMIGeoFeatures()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASMIGeoFeatures)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASMIGEOFEATURES_RGS)
	DECLARE_AGGREGATE_EX_SUPPORT();

	BEGIN_COM_MAP(CTRiASMIGeoFeatures)
		COM_INTERFACE_ENTRY(ITRiASFeaturesCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_THIS()

	// durch aggregiertes Objekt implementierte Interfaces
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeatures, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IDispatch, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeatures, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASFeatures BaseObjs;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseObjs.ppi()));
		return BaseObjs -> putref_FeaturesCallback(this);
	}
	void FinalRelease (void)
	{
		m_BaseUnk.Assign(NULL);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeaturesCallback
public:
	STDMETHOD(get_DefaultType)(BSTR *pbstrType);
	STDMETHOD(SetupFeatures)(IDispatch *pIObjs, SETUPFEATURESMODE rgMode);
	STDMETHOD(OnCreate)(VARIANT NameOrHandle, BSTR Type, FEATURETYPE rgType, ITRiASFeature **ppIFeat);
	STDMETHOD(OnDelete)(VARIANT vWhich);
	STDMETHOD(OnChanging)(CHANGEDFEATURES rgWhat, VARIANT vNewValue, VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(CHANGEDFEATURES rgWhat, VARIANT vOldValue);
	STDMETHOD(OnFinalRelease)();

private:
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeatures)
};

#endif // !defined(_TRIASMIGEOFEATURES_H__B33C6E5E_ADCE_4E6B_B716_37B8C2D3D27A__INCLUDED_)