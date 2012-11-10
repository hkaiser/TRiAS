// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/27/1998 11:42:10 PM
//
// @doc
// @module PerfCounterDefinitions.h | Declaration of the <c CPerfCounterDefinitions> class

#if !defined(_PERFCOUNTERDEFINITIONS_H__467452A0_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _PERFCOUNTERDEFINITIONS_H__467452A0_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPerfCounterDefinitions
class ATL_NO_VTABLE CPerfCounterDefinitions : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPerfCounterDefinitions, &CLSID_PerfCounterDefinitions>,
	public ISupportErrorInfo,
	public IDynamicCollectionImpl<IPerfCounterDefinition, &IID_IPerfCounterDefinition, &LIBID_PerfMon, IPerfCounterDefinitions, &IID_IPerfCounterDefinitions>
{
public:
	CPerfCounterDefinitions()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFCOUNTERDEFINITIONS)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfCounterDefinitions)

	BEGIN_COM_MAP(CPerfCounterDefinitions)
		COM_INTERFACE_ENTRY(IPerfCounterDefinitions)
		COM_INTERFACE_ENTRY(IDynamicCollection)
		COM_INTERFACE_ENTRY(IStaticCollection)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfCounterDefinitions
public:
};

#endif // !defined(_PERFCOUNTERDEFINITIONS_H__467452A0_9CBA_11D2_9F09_006008447800__INCLUDED_)
