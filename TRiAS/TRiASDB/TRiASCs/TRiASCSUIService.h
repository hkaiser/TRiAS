// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.10.2000 19:31:18 
//
// @doc
// @module TRiASCSUIService.h | Declaration of the <c CTRiASCSUIService> class

#if !defined(_TRIASCSUISERVICE_H__D29B4984_36E9_48C4_9EEC_C1F11EC17BED__INCLUDED_)
#define _TRIASCSUISERVICE_H__D29B4984_36E9_48C4_9EEC_C1F11EC17BED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSUIService
class ATL_NO_VTABLE CTRiASCSUIService : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASCSUIService, &CLSID_TRiASCSUIService>,
	public CErrSupport<CTRiASCSUIService, &IID_ITRiASCSUIService>,
	public IDispatchImpl<ITRiASCSUIService, &IID_ITRiASCSUIService, &LIBID_TRIASCS>
{
public:
	CTRiASCSUIService()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCSUIService)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSUISERVICE)
	DECLARE_NOT_AGGREGATABLE(CTRiASCSUIService)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTRiASCSUIService)
		COM_INTERFACE_ENTRY(ITRiASCSUIService)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASCSUIService
public:
	STDMETHOD(get_InputMask) (ITRiASCS *CoordSys, COORDELEMENT Element, BSTR *UIMask);
	STDMETHOD(get_InputMaskControl) (BSTR *UIGuid);
	STDMETHOD(get_Precision) (ITRiASCS *CoordSys, long *Prec);
	STDMETHOD(put_Precision) (ITRiASCS *CoordSys, long Prec);
	STDMETHOD(Format) (ITRiASCS *CoordSys, COORDELEMENT Element, double Value, BSTR *FormattedElement);
	STDMETHOD(Convert) (ITRiASCS *CoordSys, COORDELEMENT Element, BSTR Formatted, double *Value);
};

#endif // !defined(_TRIASCSUISERVICE_H__D29B4984_36E9_48C4_9EEC_C1F11EC17BED__INCLUDED_)
