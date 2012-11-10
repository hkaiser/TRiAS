///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASVariantProperty.h | Declaration of the <c CTRiASVariantPropertyBase> 
// and <c CTRiASVariantProperty> classes

#if !defined(_TRIASVARIANTPROPERTY_H__8C34B586_9FBA_11D1_BA1E_080036D63803__INCLUDED_)
#define _TRIASVARIANTPROPERTY_H__8C34B586_9FBA_11D1_BA1E_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"				// main symbols

#pragma warning (disable: 4192)		// automatically excluding 'bla' while importing type library 'bla'
#import "tlb/TRiASMDS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASPropertyEvents);		// WTRiASPropertyEvents

///////////////////////////////////////////////////////////////////////////////
// Tearoff-Objekt, welches ITRiASValueEvents abfangen kann
class CTRiASVariantPropertyBase;
class ATL_NO_VTABLE CTRiASValueEventSink :
	public CComTearOffObjectBase<CTRiASVariantPropertyBase>,
	public ITRiASValueEvents
{
public:
	CTRiASValueEventSink() 
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASValueEventSink)

	BEGIN_COM_MAP(CTRiASValueEventSink)
		COM_INTERFACE_ENTRY(ITRiASValueEvents)
	END_COM_MAP()

public:
// ITRiASValueEvents
	STDMETHOD(ModifyingValue)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ValueToModify)(/*[in]*/ BSTR Name);
	STDMETHOD(ValueModified)(/*[in]*/ BSTR Name);
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASVariantPropertyBase
class ATL_NO_VTABLE CTRiASVariantPropertyBase : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASPropertyCallback, 
	public IObjectWithSite,
	public IPersist
{
public:
	friend CTRiASValueEventSink;

	CTRiASVariantPropertyBase() :
		m_rgType(PROPERTY_TYPE_Normal), m_dwCookie(0)
	{
	}
	~CTRiASVariantPropertyBase()
	{
		_ASSERTE(0 == m_dwCookie);		// muß abgemeldet sein
	}

	BEGIN_COM_MAP(CTRiASVariantPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY_TEAR_OFF(IID_ITRiASValueEvents, CTRiASValueEventSink)
	END_COM_MAP()

// IObjectWithSite
	STDMETHOD(SetSite)(IUnknown *pISite);
	STDMETHOD(GetSite)(REFIID riid, void **ppvSite);

// ITRiASPropertySupport
public:
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

protected:
	inline HRESULT Fire_ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal);
	inline HRESULT Fire_PropertyToModify (BSTR Name);
	inline HRESULT Fire_PropertyModified (BSTR Name);

	HRESULT ShutDown();

protected:
	CComVariant m_Value;		// Wert dieser Property
	PROPERTY_TYPE m_rgType;		// Typ dieser Property
	DWORD m_dwCookie;			// evtl. Cookie für ITRiASValueEvents
	WTRiASPropertyEvents m_PropEvents;
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASVariantProperty
class ATL_NO_VTABLE CTRiASVariantProperty : 
	public CTRiASVariantPropertyBase,
	public CComCoClass<CTRiASVariantProperty, &CLSID_TRiASVariantProperty>
{
public:
	CTRiASVariantProperty() {}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASVariantProperty)
	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASVARIANTPROPERTY)

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
	{
		CTRiASVariantPropertyBase::ShutDown();
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASAutoSaveProperty
class ATL_NO_VTABLE CTRiASAutoSaveProperty : 
	public CTRiASVariantPropertyBase,
	public CComCoClass<CTRiASAutoSaveProperty, &CLSID_TRiASAutoSaveProperty>
{
public:
	CTRiASAutoSaveProperty() 
	{
		m_rgType = PROPERTY_TYPE_NeedsSavingHelp;
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASAutoSaveProperty)
	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASAUTOSAVEPROPERTY)

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
	{
		CTRiASVariantPropertyBase::ShutDown();
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// ITRiASPropertySupport
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
};

#endif // !defined(_TRIASVARIANTPROPERTY_H__8C34B586_9FBA_11D1_BA1E_080036D63803__INCLUDED_)
