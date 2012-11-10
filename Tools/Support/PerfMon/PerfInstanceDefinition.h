// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:26:32 PM
//
// @doc
// @module PerfInstanceDefinition.h | Declaration of the <c CPerfInstanceDefinition> class

#if !defined(_PERFINSTANCEDEFINITION_H__8FE61072_9A8D_11D2_9F08_006008447800__INCLUDED_)
#define _PERFINSTANCEDEFINITION_H__8FE61072_9A8D_11D2_9F08_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPerfInstanceDefinition
class ATL_NO_VTABLE CPerfInstanceDefinition : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPerfInstanceDefinition, &CLSID_PerfInstanceDefinition>,
	public ISupportErrorInfo,
	public IPersistMemory,
	public IDispatchImpl<IPerfInstanceDefinition, &IID_IPerfInstanceDefinition, &LIBID_PerfMon>
{
public:
	CPerfInstanceDefinition() :
		m_fIsDirty(false), m_pITargetObject(NULL)
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFINSTANCEDEFINITION)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfInstanceDefinition)

	BEGIN_COM_MAP(CPerfInstanceDefinition)
		COM_INTERFACE_ENTRY(IPerfInstanceDefinition)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistMemory)
		COM_INTERFACE_ENTRY2(IPersist, IPersistMemory)
	END_COM_MAP()

	HRESULT FinalConstruct ()
	{
		COM_TRY {
			m_Counters.LocalCreateInstance(CLSID_PerfCounters);
		} COM_CATCH;
		return S_OK;
	}
	void FinalRelease()
	{
		m_Counters.Assign(NULL);
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

// IPerfInstanceDefinition
public:
	STDMETHOD(get_Counters)(/*[out, retval]*/ IPerfCounters * *pVal);
	STDMETHOD(get_Counter)(/*[in]*/ BSTR Name, /*[out, retval]*/ IPerfCounter * *pVal);
	STDMETHOD(putref_TargetObject)(/*[in]*/ IPerfObject * newVal);

	DECLARE_PROPERTY_ACCESS(Name, BSTR);
	DECLARE_PROPERTY_ACCESS(ContextName, BSTR);

protected:
	HRESULT RegenerateCounters();

private:
	WPerfCounters m_Counters;
	bool m_fIsDirty;

// Properties
	CComBSTR m_Name;
	IPerfObject *m_pITargetObject;
	CComBSTR m_ContextName;
};

#endif // !defined(_PERFINSTANCEDEFINITION_H__8FE61072_9A8D_11D2_9F08_006008447800__INCLUDED_)
