// $Header: /TRiAS/TRiASDB/TDBGeo/TRiASCSStorageService.h 1	 15.06.98 21:26 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/13/1998 08:47:15 PM
//
// @doc
// @module TRiASCSStorageService.h | Helper zur Erzeugung von Geometrieobjekten

#if !defined(_TRIASCSSTORAGESERVICE_H__80B9A2F7_02B0_11D2_8650_00600875138A__INCLUDED_)
#define _TRIASCSSTORAGESERVICE_H__80B9A2F7_02B0_11D2_8650_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSStorageService
class ATL_NO_VTABLE CTRiASCSStorageService :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASCSStorageService, &CLSID_TRiASCSStorageService>,
	public CErrSupport<CTRiASCSStorageService, &IID_ITRiASCSStorageService>,
	public IDispatchImpl<ITRiASCSStorageService, &IID_ITRiASCSStorageService, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSStorageServiceGDO, &IID_ITRiASCSStorageServiceGDO, TLB_TDBGEO_SIGNAT>,
	public IDispatchImpl<ITRiASCSStorageServiceWks, &IID_ITRiASCSStorageServiceWks, TLB_TDBGEO_SIGNAT>
{
public:
	CTRiASCSStorageService()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCSSTORAGESERVICE)

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCSStorageService)
	BEGIN_COM_MAP(CTRiASCSStorageService)
		COM_INTERFACE_ENTRY(ITRiASCSStorageService)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASCSStorageService)
		COM_INTERFACE_ENTRY(ITRiASCSStorageServiceGDO)
		COM_INTERFACE_ENTRY(ITRiASCSStorageServiceWks)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASCSStorageService
public:
	STDMETHOD(GeometryToStorage)(/*[in]*/ GEOMETRYTYPE rgType, /*[in]*/ IDispatch * Geometry, /*[out, retval]*/ VARIANT * Blob);
	STDMETHOD(StorageToGeometry)(/*[in]*/ VARIANT Blob, /*[in, out]*/ GEOMETRYTYPE * prgType, /*[out, retval]*/ IDispatch * * Geometry);
	STDMETHOD(RetrieveType)(/*[in]*/ IDispatch * pIDisp, /*[out, retval]*/ GEOMETRYTYPE * prgType);
	STDMETHODIMP StorageToObject(VARIANT Blob, IDispatch **CoordSys);
	STDMETHODIMP ObjectToStorage(IDispatch *CoordSys, VARIANT *Blob);

// ITRiASCSStorageServiceGDO
	STDMETHOD(StorageToGeometryGDO)(VARIANT Blob, GEOMETRYTYPE * prgType, IDispatch * * Geometry);
	STDMETHOD(GeometryToStorageGDO)(GEOMETRYTYPE rgType, IDispatch * Geometry, VARIANT * Blob);

// ITRiASCSStorageServiceWks
	STDMETHODIMP StorageToGeometryWkb(VARIANT Blob, GEOMETRYTYPE *prgType, IDispatch **Geometry);
	STDMETHODIMP GeometryToStorageWkb(GEOMETRYTYPE rgType, IDispatch *Geometry, VARIANT *Blob);
	STDMETHODIMP StorageToGeometryWkt(BSTR Wkt, GEOMETRYTYPE *prgType, IDispatch **Geometry);
	STDMETHODIMP GeometryToStorageWkt(GEOMETRYTYPE rgType, IDispatch *Geometry, BSTR *Wkt);

// Helper Funktion
	static HRESULT RetrieveGeometryType (IDispatch * pIDisp, GEOMETRYTYPE * prgType);
};

#endif // !defined(_TRIASCSSTORAGESERVICE_H__80B9A2F7_02B0_11D2_8650_00600875138A__INCLUDED_)
