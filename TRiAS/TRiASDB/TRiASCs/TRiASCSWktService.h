// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.01.2001 21:49:15 
//
// @doc
// @module TRiASCSWktService.h | Declaration of the <c CTRiASCSWktService> class

#if !defined(_TRIASCSWKTSERVICE_H__55CD2457_8870_4497_AD5D_0D5AFFB3D66A__INCLUDED_)
#define _TRIASCSWKTSERVICE_H__55CD2457_8870_4497_AD5D_0D5AFFB3D66A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSWktService
class ATL_NO_VTABLE CTRiASCSWktService : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASCSWktService, &CLSID_TRiASCSWktService>,
	public CErrSupport<CTRiASCSWktService, &IID_ITRiASCSWktService>,
	public IDispatchImpl<ITRiASCSWktService, &IID_ITRiASCSWktService, &LIBID_TRIASCS>
{
public:
	CTRiASCSWktService()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCSWktService)

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSWKTSERVICE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTRiASCSWktService)
		COM_INTERFACE_ENTRY(ITRiASCSWktService)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASCSWktService
public:
	STDMETHOD(CreateFromWkt)(/*[in]*/ BSTR bstrWktCS, /*[out, retval]*/ ITRiASCS **ppICS);
	STDMETHOD(ExportAsWkt)(/*[in]*/ ITRiASCS *pCS, /*[out, retval]*/ BSTR *pbstrWktCS);

protected:
	HRESULT RetrieveProjectedName(ITRiASCS *pICS, BSTR *pbstrName);
	HRESULT ExportGeographicSystem(ITRiASCSGCS *pIGCS, BSTR *pbstrGCS);
	HRESULT ExportProjectionParams(ITRiASCSPCS *pIPCS, BSTR *pbstrParams);
};

#endif // !defined(_TRIASCSWKTSERVICE_H__55CD2457_8870_4497_AD5D_0D5AFFB3D66A__INCLUDED_)
