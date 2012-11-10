// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.01.2002 13:03:11 
//
// @doc
// @module TRiASSpatialRelationService.h | Declaration of the <c CTRiASSpatialRelationService> class

#if !defined(_TRIASSPATIALRELATIONSERVICE_H__DF3ABA23_D0D7_4B60_89C5_A67455CC53A3__INCLUDED_)
#define _TRIASSPATIALRELATIONSERVICE_H__DF3ABA23_D0D7_4B60_89C5_A67455CC53A3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "GeometryObjectsFwd.h"

using namespace trias_wmgeometry;

/////////////////////////////////////////////////////////////////////////////
// CTRiASSpatialRelationService

class ATL_NO_VTABLE CTRiASSpatialRelationService : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASSpatialRelationService, &CLSID_TRiASSpatialRelationService>,
	public CErrSupport<CTRiASSpatialRelationService, &IID_ITRiASSpatialRelationService>,
	public IDispatchImpl<ITRiASSpatialRelationService, &IID_ITRiASSpatialRelationService, 
		TLB_TDBGEO_SIGNAT>
{
public:
	typedef double KoOrdT;		// Koordinatentyp

// Construction
	CTRiASSpatialRelationService() {}
	~CTRiASSpatialRelationService() {}

// Initialisation
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASSPATIALRELATIONSERVICE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASSpatialRelationService)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASSpatialRelationService)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations
	HRESULT ConvertToGeometry (IDispatch *pIGeometry, WMObjekt<KoOrdT> **ppGeometry);
	HRESULT CalcTopRelation(WMObjekt<KoOrdT> *pObj1, WMObjekt<KoOrdT> *pObj2, 
		OGCWMPosit *prgPosition);
	HRESULT ConvertToPoint (IDispatch *pIGeometry, WMObjekt<KoOrdT> **ppGeometry);
	HRESULT ConvertToLine (IDispatch *pIGeometry, WMObjekt<KoOrdT> **ppGeometry);
	HRESULT ConvertToArea (IDispatch *pIGeometry, WMObjekt<KoOrdT> **ppGeometry);

	HRESULT RetrieveCSGuid(VARIANT vCSArg, CIID *pGuid);

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

	STDMETHODIMP putref_TransformPipe(/*[in]*/ ITRiASCSTransform *newVal);
	STDMETHODIMP get_TransformPipe(/*[out, retval]*/ ITRiASCSTransform **pVal);

// ITRiASSpatialRelationService
	STDMETHODIMP Equals(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *equals);
	STDMETHODIMP Touches(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *touches);
	STDMETHODIMP Contains(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *contains);
	STDMETHODIMP Within(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *within);
	STDMETHODIMP Disjoint(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *disjoint);
	STDMETHODIMP Crosses(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *crosses);
	STDMETHODIMP Overlaps(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *overlaps);
	STDMETHODIMP Intersects(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, VARIANT_BOOL *intersects);
	STDMETHODIMP Relate(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, SPATIALRELATION Pattern, VARIANT_BOOL *isrelated);
	STDMETHODIMP GetSpatialRelation(VARIANT vCsOne, IDispatch *GeomOne, VARIANT vCsTwo, IDispatch *GeomTwo, SPATIALRELATION *Pattern);

private:
	WTRiASCSTransform m_CSS;
};

#endif // !defined(_TRIASSPATIALRELATIONSERVICE_H__DF3ABA23_D0D7_4B60_89C5_A67455CC53A3__INCLUDED_)
