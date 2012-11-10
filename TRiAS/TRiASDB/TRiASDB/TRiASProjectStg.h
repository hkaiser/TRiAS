///////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASStgProperty.h | Declaration of the <c CTRiASStgProperty>

#if !defined(_TRIASPROJECTSTG_H__910C1737_6680_11D1_972F_00A024D6F582__INCLUDED_)
#define _TRIASPROJECTSTG_H__910C1737_6680_11D1_972F_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(OleItemContainer);		// WOleItemContainer

/////////////////////////////////////////////////////////////////////////////
// CTRiASStgProperty

class ATL_NO_VTABLE CTRiASStgProperty : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CReportErrorComCoClass<CTRiASStgProperty, &CLSID_TRiASStgProperty, &IID_ITRiASPropertyCallback>,
	public ITRiASPropertyCallback,
	public IObjectWithSite
{
public:
	typedef CComCoClass<CTRiASStgProperty, &CLSID_TRiASStgProperty> base_t;

	CTRiASStgProperty()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASStgProperty)

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSTGPROPERTY)
	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CTRiASStgProperty)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_GET_CONTROLLING_UNKNOWN()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
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
	HRESULT RetrieveStorage (IStorage **ppIStg);

private:
	WOleItemContainer m_Cont;
};

#endif // !defined(_TRIASPROJECTSTG_H__910C1737_6680_11D1_972F_00A024D6F582__INCLUDED_)
