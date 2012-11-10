///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASProperty.h | Declaration of the <c CTRiASProperty> class

#if !defined(_TRIASPROPERTY_H__6AA5EF95_9E55_11D1_BA1C_080036D63803__INCLUDED_)
#define _TRIASPROPERTY_H__6AA5EF95_9E55_11D1_BA1C_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASProperty

class ATL_NO_VTABLE CTRiASProperty : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IPersistStreamInit,
	public IObjectWithSite,
	public CReportErrorComCoClass<CTRiASProperty, &CLSID_TRiASProperty, &IID_ITRiASProperty>, 
	public IConnectionPointContainerImpl<CTRiASProperty>,
	public IDispatchImpl<ITRiASProperty, &IID_ITRiASProperty, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASProperty()
		: m_bstrName(g_cbNil), m_bstrDesc(g_cbNil),
		  m_fInherited(false), m_fNeedsSavingHelp(false),
		  m_fIsDirty(false), m_fIsInitialized(false)
	{
	}

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASProperty)

	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPROPERTY)
		
	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(CTRiASProperty)
		COM_INTERFACE_ENTRY(ITRiASProperty)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
		COM_INTERFACE_ENTRY_FUNC(IID_IPersistStreamInit, 
					offsetofclass(IPersistStreamInit, _ComMapClass),
					_Choice)
		COM_INTERFACE_ENTRY_FUNC(IID_IPersistStream, 
					offsetofclass(IPersistStreamInit, _ComMapClass),
					_Choice)
		COM_INTERFACE_ENTRY_FUNC(IID_IPersist, 
					offsetofclass(IPersist, _ComMapClass),
					_Choice)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASProperty)
	END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
	{
	}
	bool NeedsSavingHelp (void) { return m_fNeedsSavingHelp; }
	bool IsInitialized (void) { return m_fIsInitialized; }

// sonstige member
	HRESULT SetPropertySupportSite (ITRiASPropertyCallback *pISupport)
	{ 
		m_Support = pISupport;
		m_fNeedsSavingHelp = false;
		if (m_Support.IsValid()) {
		PROPERTY_TYPE rgType;
		
			if (SUCCEEDED(m_Support -> GetType (m_bstrName, &rgType)))
				m_fNeedsSavingHelp = (rgType & PROPERTY_TYPE_NeedsSavingHelp) ? true : false;
		}
		return S_OK;
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// IObjectWithSite
	STDMETHOD(SetSite)(IUnknown *pISite);
	STDMETHOD(GetSite)(REFIID riid, void **ppvSite);

// ITRiASProperty
public:
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(Refresh)();
	STDMETHOD(GetValueAndType)(/*[in, out]*/ VARIANT *pVal, /*[in, out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(SetValueAndType)(/*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(get_Type)(/*[out, retval]*/ PROPERTY_TYPE *pVal);
	STDMETHOD(put_Type)(/*[in]*/ PROPERTY_TYPE newVal);
	STDMETHOD(get_Inherited)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Value)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Value)(/*[in]*/ VARIANT newVal);

protected:
// Datamember
	CComBSTR m_bstrName;
	CComBSTR m_bstrDesc;
	bool m_fInherited;

	bool m_fNeedsSavingHelp;
	bool m_fIsDirty;
	bool m_fIsInitialized;

	WTRiASPropertyCallback m_Support;		// zuständig für diese Property
};

///////////////////////////////////////////////////////////////////////////////
// Version des PersistStream-Formates
const long PROPERTY_SIGNATURE = 0x504F5250L;		// "PROP"
const long PROPERTY_VERSION_MINOR_MASK = 0xff;
const long PROPERTY_VERSION_100 = 0x0100L;
const long PROPERTY_VERSION_101 = 0x0101L;			// ADDED: Description (#HK981109)
const long LASTKNOWN_PROPERTY_VERSION = PROPERTY_VERSION_101;

#endif // !defined(_TRIASPROPERTY_H__6AA5EF95_9E55_11D1_BA1C_080036D63803__INCLUDED_)
