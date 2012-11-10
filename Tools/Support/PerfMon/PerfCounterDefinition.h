// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:14:33 PM
//
// @doc
// @module PerfCounterDefinition.h | Declaration of the <c CPerfCounterDefinition> class

#if !defined(_PERFCOUNTERDEFINITION_H__8FE6106E_9A8D_11D2_9F08_006008447800__INCLUDED_)
#define _PERFCOUNTERDEFINITION_H__8FE6106E_9A8D_11D2_9F08_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinitionBase
class ATL_NO_VTABLE CPerfCounterDefinitionBase : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IPersistMemory,
	public IDispatchImpl<IPerfCounterDefinition, &IID_IPerfCounterDefinition, &LIBID_PerfMon>
{
public:
	CPerfCounterDefinitionBase() :
		m_fIsDirty(false), m_BaseIndex(0), m_pITargetObject(NULL)
	{
	}

	BEGIN_COM_MAP(CPerfCounterDefinitionBase)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistMemory)
		COM_INTERFACE_ENTRY2(IPersist, IPersistMemory)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}

// IPersistMemory
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(void *pvMem, ULONG cbSize);
	STDMETHOD(Save)(void *pvMem, BOOL fClearDirty, ULONG cbSize);
	STDMETHOD(GetSizeMax)(ULONG *pcbSize);
	STDMETHOD(InitNew)();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfCounterDefinition
public:
	STDMETHOD(putref_TargetObject)(/*[in]*/ IPerfObject * newVal);

	DECLARE_PROPERTY_ACCESS(Name, BSTR);
	DECLARE_PROPERTY_ACCESS(Description, BSTR);
	DECLARE_PROPERTY_ACCESS(HelpText, BSTR);
	DECLARE_PROPERTY_ACCESS(Detail, DETAILLEVEL);
	DECLARE_PROPERTY_ACCESS(Type, COUNTERTYPE);
	DECLARE_PROPERTY_ACCESS(DefaultScale, LONG);
	DECLARE_PROPERTY_GET(BaseIndex, ULONG); 
	DECLARE_PROPERTY_ACCESS(ContextName, BSTR);

protected:
	bool m_fIsDirty;

// Properties
	CComBSTR m_Name;
	CComBSTR m_Description;
	CComBSTR m_HelpText;
	DETAILLEVEL m_Detail;
	COUNTERTYPE m_Type;
	LONG m_DefaultScale;

	ULONG m_BaseIndex;
	IPerfObject *m_pITargetObject;
	CComBSTR m_ContextName;
};

/////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinition
class ATL_NO_VTABLE CPerfCounterDefinition : 
	public CPerfCounterDefinitionBase,
	public CComCoClass<CPerfCounterDefinition, &CLSID_PerfCounterDefinition>
{
public:
	CPerfCounterDefinition() 
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFCOUNTERDEFINITION)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfCounterDefinition)

	BEGIN_COM_MAP(CPerfCounterDefinition)
		COM_INTERFACE_ENTRY(IPerfCounterDefinition)
		COM_INTERFACE_ENTRY_CHAIN(CPerfCounterDefinitionBase)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPerfCounterDefinition
public:
	STDMETHOD(CreateCounter)(/*[out, retval]*/ IPerfCounter **ppICounter);
};

/////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinition
class ATL_NO_VTABLE CPerfCounterDefinitionCollect : 
	public CPerfCounterDefinitionBase,
	public CComCoClass<CPerfCounterDefinitionCollect, &CLSID_PerfCounterDefinitionCollect>
{
public:
	CPerfCounterDefinitionCollect() 
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfCounterDefinitionCollect)

	BEGIN_COM_MAP(CPerfCounterDefinitionCollect)
		COM_INTERFACE_ENTRY(IPerfCounterDefinition)
		COM_INTERFACE_ENTRY_CHAIN(CPerfCounterDefinitionBase)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPerfCounterDefinition
public:
	STDMETHOD(CreateCounter)(/*[out, retval]*/ IPerfCounter **ppICounter);
};

#endif // !defined(_PERFCOUNTERDEFINITION_H__8FE6106E_9A8D_11D2_9F08_006008447800__INCLUDED_)
