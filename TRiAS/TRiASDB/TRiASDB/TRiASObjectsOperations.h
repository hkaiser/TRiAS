// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 11/16/1998 01:45:59 PM
//
// @doc
// @module TRiASObjectsOperations.h | Allgemeine Operationen über Objektmengen

#if !defined(_TRIASOBJECTSOPERATIONS_H__F45F28D9_7D2F_11D2_9EF6_006008447800__INCLUDED_)
#define _TRIASOBJECTSOPERATIONS_H__F45F28D9_7D2F_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Klasse implementiert die eigentliche Funktionalität für beide Varianten
// (CComCoClass und CComTearOffObject)
class ATL_NO_VTABLE CTRiASObjectsOperationsFunc :
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASObjectsOperations, &IID_ITRiASObjectsOperations, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASObjectsOperationsFunc()
	{
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASObjectsOperations
public:
	STDMETHOD(Includes)(/*[in]*/ ITRiASObjects *Objs1, /*[in]*/ ITRiASObjects *Objs2, /*[out, retval]*/ VARIANT_BOOL *Includes);
	STDMETHOD(SymmetricDifference)(/*[in]*/ ITRiASObjects *Obj1, /*[in]*/ ITRiASObjects *Objs2, /*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTSCOLLECTIONTYPE rgType, /*[out, retval]*/ ITRiASObjects **ObjsOut);
	STDMETHOD(Difference)(/*[in]*/ ITRiASObjects *Obj1, /*[in]*/ ITRiASObjects *Objs2, /*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTSCOLLECTIONTYPE rgType, /*[out, retval]*/ ITRiASObjects **ObjsOut);
	STDMETHOD(Intersection)(/*[in]*/ ITRiASObjects *Obj1, /*[in]*/ ITRiASObjects *Objs2, /*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTSCOLLECTIONTYPE rgType, /*[out, retval]*/ ITRiASObjects **ObjsOut);
	STDMETHOD(Union)(/*[in]*/ ITRiASObjects *Objs1, /*[in]*/ ITRiASObjects *Objs2, /*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTSCOLLECTIONTYPE rgType, /*[out, retval]*/ ITRiASObjects **ObjsOut);
	STDMETHOD(MakeNewObjects)(/*[in]*/ IDispatch *Parent, /*[in]*/ BSTR Name, /*[in]*/ BSTR Type, /*[in]*/ OBJECTSCOLLECTIONTYPE CollType, /*[out, retval]*/ ITRiASObjects **ObjsOut);
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsOperations (separat instantiierbar)
class CTRiASObjects;		// forward decl only

class ATL_NO_VTABLE CTRiASObjectsOperationsTearOff : 
	public CComTearOffObjectBase<CTRiASObjects>,
	CTRiASObjectsOperationsFunc
{
public:
	CTRiASObjectsOperationsTearOff()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASObjectsOperationsTearOff)
	BEGIN_COM_MAP(CTRiASObjectsOperationsTearOff)
		COM_INTERFACE_ENTRY(ITRiASObjectsOperations)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASObjectsOperations (separat instantiierbar)
class ATL_NO_VTABLE CTRiASObjectsOperations : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASObjectsOperations, &CLSID_TRiASObjectsOperations>,
	CTRiASObjectsOperationsFunc
{
public:
	CTRiASObjectsOperations()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASObjectsOperations)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASOBJECTSOPERATIONS)

	BEGIN_COM_MAP(CTRiASObjectsOperations)
		COM_INTERFACE_ENTRY(ITRiASObjectsOperations)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
	{
	}
};

#endif // !defined(_TRIASOBJECTSOPERATIONS_H__F45F28D9_7D2F_11D2_9EF6_006008447800__INCLUDED_)
