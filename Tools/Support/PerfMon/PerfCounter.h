// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 01:44:26 PM
//
// @doc
// @module PerfCounter.h | Declaration of the <c CPerfCounter> class

#if !defined(_PERFCOUNTER_H__46745269_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _PERFCOUNTER_H__46745269_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <classics/atomic_counter.h>

/////////////////////////////////////////////////////////////////////////////
// CPerfCounter
class ATL_NO_VTABLE CPerfCounter : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IPersistMemory,
	public IDispatchImpl<IPerfCounter, &IID_IPerfCounter, &LIBID_PerfMon>
{
public:
	CPerfCounter() :
		m_fIsDirty(false), m_Type(0)
	{
	}

	BEGIN_COM_MAP(CPerfCounter)
		COM_INTERFACE_ENTRY(IPerfCounter)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistMemory)
		COM_INTERFACE_ENTRY2(IPersist, IPersistMemory)
	END_COM_MAP()

// IPersistMemory
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(void *pvMem, ULONG cbSize);
	STDMETHOD(InitNew)();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfCounter
public:
	DECLARE_PROPERTY_ACCESS(Type, COUNTERTYPE);
	DECLARE_PROPERTY_ACCESS(Name, BSTR);
	DECLARE_PROPERTY_ACCESS(ContextName, BSTR);

protected:
	bool m_fIsDirty;

// Properties
	COUNTERTYPE m_Type;
	CComBSTR m_Name;
	CComBSTR m_ContextName;
	WPerfContextHelper m_Ctx;
};

class ATL_NO_VTABLE CPerfCounterInt32 : 
	public CPerfCounter,
	public CComCoClass<CPerfCounterInt32, &CLSID_PerfCounterInt32>
{
public:
	CPerfCounterInt32() :
		m_Value(NULL)
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFCOUNTERINT32)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfCounterInt32)

	BEGIN_COM_MAP(CPerfCounterInt32)
		COM_INTERFACE_ENTRY2(IUnknown, IDispatch)
		COM_INTERFACE_ENTRY_CHAIN(CPerfCounter)
	END_COM_MAP()

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistMemory
	STDMETHOD(Save)(void *pvMem, BOOL fClearDirty, ULONG cbSize);
	STDMETHOD(GetSizeMax)(ULONG *pcbSize);

// IPerfCounter
public:
	STDMETHOD(Increment)(/*[in, optional, defaultvalue(1)]*/ LONG Delta);
	STDMETHOD(Step)();
	STDMETHOD(get_Value)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Value)(/*[in]*/ VARIANT newVal);

private:
	classics::atomic_counter_ptr<long> m_Value;
};

class ATL_NO_VTABLE CPerfCounterInt64 : 
	public CPerfCounter,
	public CComCoClass<CPerfCounterInt64, &CLSID_PerfCounterInt64>
{
public:
	CPerfCounterInt64() :
		m_Value(0), m_pValue(NULL)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_PERFCOUNTERINT64)
	DECLARE_NOT_AGGREGATABLE(CPerfCounterInt64)

	BEGIN_COM_MAP(CPerfCounterInt64)
		COM_INTERFACE_ENTRY2(IUnknown, IDispatch)
		COM_INTERFACE_ENTRY_CHAIN(CPerfCounter)
	END_COM_MAP()

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistMemory
	STDMETHOD(Save)(void *pvMem, BOOL fClearDirty, ULONG cbSize);
	STDMETHOD(GetSizeMax)(ULONG *pcbSize);

// IPerfCounter
public:
	STDMETHOD(Increment)(/*[in, optional, defaultvalue(1)]*/ LONG Delta);
	STDMETHOD(Step)();
	STDMETHOD(get_Value)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Value)(/*[in]*/ VARIANT newVal);

private:
	LONGLONG m_Value;
	LONGLONG *m_pValue;
};

#endif // !defined(_PERFCOUNTER_H__46745269_9CBA_11D2_9F09_006008447800__INCLUDED_)
