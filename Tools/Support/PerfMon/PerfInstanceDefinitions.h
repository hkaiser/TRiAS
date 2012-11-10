// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/28/1998 09:40:27 PM
//
// @doc
// @module PerfInstanceDefinitions.h | Declaration of the <c CPerfInstanceDefinitions> class

#if !defined(_PERFINSTANCEDEFINITIONS_H__467452A3_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _PERFINSTANCEDEFINITIONS_H__467452A3_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPerfInstanceDefinitions
class ATL_NO_VTABLE CPerfInstanceDefinitions : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPerfInstanceDefinitions, &CLSID_PerfInstanceDefinitions>,
	public ISupportErrorInfo,
	public IDynamicCollectionImpl<IPerfInstanceDefinition, &IID_IPerfInstanceDefinition, &LIBID_PerfMon, IPerfInstanceDefinitions, &IID_IPerfInstanceDefinitions>
{
public:
	CPerfInstanceDefinitions()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFINSTANCEDEFINITIONS)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfInstanceDefinitions)

	BEGIN_COM_MAP(CPerfInstanceDefinitions)
		COM_INTERFACE_ENTRY(IPerfInstanceDefinitions)
		COM_INTERFACE_ENTRY(IDynamicCollection)
		COM_INTERFACE_ENTRY(IStaticCollection)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfInstanceDefinitions
public:
};

#endif // !defined(_PERFINSTANCEDEFINITIONS_H__467452A3_9CBA_11D2_9F09_006008447800__INCLUDED_)
