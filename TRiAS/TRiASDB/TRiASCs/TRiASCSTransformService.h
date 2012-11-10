// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 07.02.2002 23:25:32 
//
// @doc
// @module TRiASCSTransformService.h | Declaration of the <c CTRiASCSTransformService> class

#if !defined(_TRIASCSTRANSFORMSERVICE_H__57A61EE0_C657_4374_8929_E81BC0C2A7ED__INCLUDED_)
#define _TRIASCSTRANSFORMSERVICE_H__57A61EE0_C657_4374_8929_E81BC0C2A7ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSTransformService

class ATL_NO_VTABLE CTRiASCSTransformService : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCSTransformService, &CLSID_TRiASCSTransformService>,
	public CErrSupport<CTRiASCSTransformService, &IID_ITRiASCSTransformService>,
	public IDispatchImpl<ITRiASCSTransformService, &IID_ITRiASCSTransformService, &LIBID_TRIASCS>
{
public:
// Construction
	CTRiASCSTransformService();
	~CTRiASCSTransformService();

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSTRANSFORMSERVICE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// Interface map
	BEGIN_COM_MAP(CTRiASCSTransformService)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASCSTransformService)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASCSTransformService
	STDMETHODIMP Transform(IDispatch *Geometry, BSTR CoordSysGuid, ITRiASCSTransform *CTF);
	STDMETHODIMP TransformInverse(IDispatch *Geometry, BSTR CoordSysGuid, ITRiASCSTransform *CTF);
	STDMETHODIMP TransformPts(BSTR strGUID, ITRiASCSTransform *CTF, VARIANT InPoints, VARIANT *OutPoints);
	STDMETHODIMP TransformInversePts(BSTR strGUID, ITRiASCSTransform *CTF, VARIANT InPoints, VARIANT *OutPoints);
	STDMETHODIMP EnumCoordSystemNames(IEnumCoordSystemNames **ppIEnum);
};

#endif // !defined(_TRIASCSTRANSFORMSERVICE_H__57A61EE0_C657_4374_8929_E81BC0C2A7ED__INCLUDED_)
