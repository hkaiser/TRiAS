// $Header: $
// Copyright� 1998-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 25.02.2002 16:45:45 
//
// This file was generated by the TRiASDB Data Server Wizard V1.02.117 (#HK010502)
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR 
// PURPOSE.
//
// @doc
// @module TDBPGISFeature.h | Implementation of the <c CTDBPGISFeature> class

#if !defined(_TDBPGISFEATURE_H__980AEDB1_B2C9_4B4A_A799_295C5F3876E5__INCLUDED_)
#define _TDBPGISFEATURE_H__980AEDB1_B2C9_4B4A_A799_295C5F3876E5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTDBPGISFeature

class ATL_NO_VTABLE CTDBPGISFeature : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTDBPGISFeature, &CLSID_TDBPGISFeature>,
	public CErrSupport<CTDBPGISFeature, &IID_ITRiASFeature>,
	public ITRiASFeatureCallback
{
public:
	CTDBPGISFeature()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTDBPGISFeature)

	DECLARE_REGISTRY_RESOURCEID(IDR_TDBPGISFEATURE_RGS)
	DECLARE_AGGREGATE_EX_SUPPORT();

	BEGIN_COM_MAP(CTDBPGISFeature)
		COM_INTERFACE_ENTRY(ITRiASFeatureCallback)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)

	// durch aggregiertes Objekt implementierte Interfaces
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASFeature, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_ITRiASBase, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IDispatch, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_EX(IID_IConnectionPointContainer, m_BaseUnk.p)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)		// alles andere nicht gesondert behandeln
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		RETURN_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASFeature, CLSCTX_ALL, GetControllingUnknown()));

	WTRiASFeature BaseFeat;

		RETURN_FAILED_HRESULT(m_BaseUnk -> QueryInterface(BaseFeat.ppi()));
		return BaseFeat -> putref_FeatureCallback(this);
	}
	void FinalRelease (void)
	{
		m_BaseUnk.Assign(NULL);
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeatureCallback
	STDMETHOD(get_DefaultType)(/*[out, retval]*/ BSTR *pbstrType);
	STDMETHOD(SetupFeature)(/*[in]*/ SETUPFEATUREMODE rgWhat);
	STDMETHOD(Update)(/*[in]*/ ITRiASObject *Obj, /*[in]*/ VARIANT Val);
	STDMETHOD(Eval)(/*[in]*/ ITRiASObject *Obj, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(EvalEx)(/*[in]*/ ITRiASObject *Obj, /*[in, out]*/ SAFEARRAY **ppConstraints, /*[out, retval]*/ VARIANT *Val);
	STDMETHOD(OnChanging)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vNewValue, /*[out, retval]*/ VARIANT_BOOL *pDisAllow);
	STDMETHOD(OnChanged)(/*[in]*/ CHANGEDFEATURE rgWhat, /*[in]*/ VARIANT vOldValue);
	STDMETHOD(Clone)(/*[out, retval]*/ ITRiASFeature **ppIFeat);
	STDMETHOD(OnFinalRelease)();


protected:
	HRESULT OnChangedName();
	HRESULT OnChangedDescription();
	HRESULT OnChangedHandle();
	HRESULT OnChangedROMode();
	HRESULT OnChangedType();

private:
	WUnknown m_BaseUnk;				// aggregiertes Objekt (TRiASFeature)
};

#endif // !defined(_TDBPGISFEATURE_H__980AEDB1_B2C9_4B4A_A799_295C5F3876E5__INCLUDED_)