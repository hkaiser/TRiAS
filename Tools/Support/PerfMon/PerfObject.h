// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:13:35 PM
//
// @doc
// @module PerfObject.h | Declaration of the <c CPerfObject> class

#if !defined(_PERFOBJECT_H__8FE6106B_9A8D_11D2_9F08_006008447800__INCLUDED_)
#define _PERFOBJECT_H__8FE6106B_9A8D_11D2_9F08_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <Com/PropertyMacros.h>

/////////////////////////////////////////////////////////////////////////////
// CPerfObject
class ATL_NO_VTABLE CPerfObject : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPerfObject, &CLSID_PerfObject>,
	public ISupportErrorInfo,
	public IPersistMemory,
	public IDispatchImpl<IPerfObject, &IID_IPerfObject, &LIBID_PerfMon>
{
public:
	CPerfObject() :
		m_fIsDirty(false), m_BaseIndex(0)
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFOBJECT)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfObject)

	BEGIN_COM_MAP(CPerfObject)
		COM_INTERFACE_ENTRY(IPerfObject)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistMemory)
		COM_INTERFACE_ENTRY2(IPersist, IPersistMemory)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		COM_TRY {
			THROW_FAILED_HRESULT(m_CounterDefs.LocalCreateInstance (CLSID_PerfCounterDefinitions));
			THROW_FAILED_HRESULT(m_InstanceDefs.LocalCreateInstance (CLSID_PerfInstanceDefinitions));
		} COM_CATCH;
		return S_OK;
	}
	void FinalRelease()
	{
		m_CounterDefs.Assign(NULL);
		m_InstanceDefs.Assign(NULL);
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistMemory
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(void *pvMem, ULONG cbSize);
	STDMETHOD(Save)(void *pvMem, BOOL fClearDirty, ULONG cbSize);
	STDMETHOD(GetSizeMax)(ULONG *pcbSize);
	STDMETHOD(InitNew)();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfObject
public:
	STDMETHOD(get_InstanceDefs)(/*[out, retval]*/ IPerfInstanceDefinitions * *pVal);
	STDMETHOD(get_CounterDefs)(/*[out, retval]*/ IPerfCounterDefinitions **pVal);

	STDMETHOD(AddInstanceDefinition)(/*[in]*/ BSTR Name, /*[out, retval]*/ IPerfInstanceDefinition **ppIInstanceDef);
	STDMETHOD(AddCounterDefinition)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Desc, /*[in]*/ BSTR HelpText, /*[in]*/ DETAILLEVEL Detail, /*[in]*/ LONG DefaultScale, /*[in]*/ COUNTERTYPE Type);
	STDMETHOD(AddCounter)(/*[in]*/ BSTR InstanceName, /*[in]*/ IPerfCollect *Collect);

	DECLARE_PROPERTY_ACCESS(Name, BSTR);
	DECLARE_PROPERTY_ACCESS(Description, BSTR);
	DECLARE_PROPERTY_ACCESS(HelpText, BSTR);
	DECLARE_PROPERTY_GET(BaseIndex, ULONG); 
	DECLARE_PROPERTY_ACCESS(ContextName, BSTR);

private:
	WPerfCounterDefinitions m_CounterDefs;
	WPerfInstanceDefinitions m_InstanceDefs;
	bool m_fIsDirty;

// Properties
	CComBSTR m_Name;
	CComBSTR m_Description;
	CComBSTR m_HelpText;

	ULONG m_BaseIndex;
	CComBSTR m_ContextName;
};

#endif // !defined(_PERFOBJECT_H__8FE6106B_9A8D_11D2_9F08_006008447800__INCLUDED_)
