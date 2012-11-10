// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 04.11.2002 19:51:29 
//
// @doc
// @module TRiASPropertyBagOnIPropertyBag.h | Declaration of the <c CTRiASPropertyBagOnIPropertyBag> class

#if !defined(_TRIASPROPERTYBAGONIPROPERTYBAG_H__FFF7E38F_9ACB_450B_9DD2_BE0984CF0511__INCLUDED_)
#define _TRIASPROPERTYBAGONIPROPERTYBAG_H__FFF7E38F_9ACB_450B_9DD2_BE0984CF0511__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyBag);

///////////////////////////////////////////////////////////////////////////////
// Wrapper Objekt für IPropertyBag
class ATL_NO_VTABLE CTRiASPropertyBagOnIPropertyBag :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ITRiASPropertyBag, &IID_ITRiASPropertyBag,
		&LIBID_TRiAS, TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>
{
public:
	CTRiASPropertyBagOnIPropertyBag() {}
	~CTRiASPropertyBagOnIPropertyBag() {}

	DECLARE_NO_REGISTRY()
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTRiASPropertyBagOnIPropertyBag)
		COM_INTERFACE_ENTRY(ITRiASPropertyBag)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASPropertyBag)
	END_COM_MAP()

	void SetPropertyBag (IPropertyBag *pIBag) { m_PropBag = pIBag; }
	ITRiASPropertyBag *GetPropertyBag() { return static_cast<ITRiASPropertyBag *>(this); }

// ITRiASPropertyBag 
public:
	STDMETHODIMP ReadProperty(BSTR bstrDataName, VARIANT vDefaultValue, VARIANT *pvData)
	{
	HRESULT hr = m_PropBag->Read(bstrDataName, pvData, NULL);

		if (FAILED(hr) && V_VT(&vDefaultValue) != VT_EMPTY)
			return VariantCopy(pvData, &vDefaultValue);

		return hr;
	}
	STDMETHODIMP WriteProperty(BSTR bstrDataName, VARIANT vData, VARIANT vDefaultValue)
	{
		return m_PropBag->Write(bstrDataName, &vData);
	}

private:
	WPropertyBag m_PropBag;
};

#endif // !defined(_TRIASPROPERTYBAGONIPROPERTYBAG_H__FFF7E38F_9ACB_450B_9DD2_BE0984CF0511__INCLUDED_)
