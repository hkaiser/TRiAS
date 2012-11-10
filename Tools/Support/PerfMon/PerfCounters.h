// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/28/1998 11:57:00 PM
//
// @doc
// @module PerfCounters.h | Declaration of the <c CPerfCounters> class

#if !defined(_PERFCOUNTERS_H__467452A7_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _PERFCOUNTERS_H__467452A7_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPerfCounters
class ATL_NO_VTABLE CPerfCounters : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPerfCounters, &CLSID_PerfCounters>,
	public ISupportErrorInfo,
	public IDynamicCollectionImpl<IPerfCounter, &IID_IPerfCounter, &LIBID_PerfMon, IPerfCounters, &IID_IPerfCounters>
{
public:
	CPerfCounters()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFCOUNTERS)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfCounters)

	BEGIN_COM_MAP(CPerfCounters)
		COM_INTERFACE_ENTRY(IPerfCounters)
		COM_INTERFACE_ENTRY(IDynamicCollection)
		COM_INTERFACE_ENTRY(IStaticCollection)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfCounters
public:
};

#endif // !defined(_PERFCOUNTERS_H__467452A7_9CBA_11D2_9F09_006008447800__INCLUDED_)
