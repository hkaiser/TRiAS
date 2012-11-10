// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 01:41:35 PM
//
// @doc
// @module PerfObjects.h | Declaration of the <c CPerfObjects> class

#if !defined(_PERFOBJECTS_H__46745268_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _PERFOBJECTS_H__46745268_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPerfObjects
class ATL_NO_VTABLE CPerfObjects : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPerfObjects, &CLSID_PerfObjects>,
	public ISupportErrorInfo,
	public IDynamicCollectionImpl<IPerfObject, &IID_IPerfObject, &LIBID_PerfMon, IPerfObjects, &IID_IPerfObjects>
{
public:
	CPerfObjects()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_PERFOBJECTS)
	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CPerfObjects)

	BEGIN_COM_MAP(CPerfObjects)
		COM_INTERFACE_ENTRY(IPerfObjects)
		COM_INTERFACE_ENTRY(IDynamicCollection)
		COM_INTERFACE_ENTRY(IStaticCollection)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfObjects
public:
};

#endif // !defined(_PERFOBJECTS_H__46745268_9CBA_11D2_9F09_006008447800__INCLUDED_)
