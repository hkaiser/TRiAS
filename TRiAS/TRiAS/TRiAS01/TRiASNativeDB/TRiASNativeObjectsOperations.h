// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.05.2001 19:45:32 
//
// @doc
// @module TRiASNativeObjectsOperations.h | Declaration of the <c CTRiASNativeObjectsOperations> class

#if !defined(_TRIASNATIVEOBJECTSOPERATIONS_H__767429B1_5FC0_415D_91FF_E2B5154DC5A0__INCLUDED_)
#define _TRIASNATIVEOBJECTSOPERATIONS_H__767429B1_5FC0_415D_91FF_E2B5154DC5A0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeObjectsOperations

class ATL_NO_VTABLE CTRiASNativeObjectsOperations : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASNativeObjectsOperations, &CLSID_TRiASNativeObjectsOperations>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASNativeObjectsOperations, &IID_ITRiASNativeObjectsOperations, &LIBID_TRiASNativeDB, 
			TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>
{
public:
// Construction
	CTRiASNativeObjectsOperations() {}
	~CTRiASNativeObjectsOperations() {}

// Initialisation
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEOBJECTSOPERATIONS)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASNativeObjectsOperations)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASNativeObjectsOperations)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASNativeObjectsOperations
	STDMETHODIMP Union(ITRiASEnumNativeObjects *Objs1, ITRiASEnumNativeObjects *Objs2, ITRiASEnumNativeObjects **ObjsOut);
	STDMETHODIMP Intersection(ITRiASEnumNativeObjects *Obj1, ITRiASEnumNativeObjects *Objs2, ITRiASEnumNativeObjects **ObjsOut);
	STDMETHODIMP Difference(ITRiASEnumNativeObjects *Obj1, ITRiASEnumNativeObjects *Objs2, ITRiASEnumNativeObjects **ObjsOut);
	STDMETHODIMP SymmetricDifference(ITRiASEnumNativeObjects *Obj1, ITRiASEnumNativeObjects *Objs2, ITRiASEnumNativeObjects **ObjsOut);
	STDMETHODIMP Includes(ITRiASEnumNativeObjects *Objs1, ITRiASEnumNativeObjects *Objs2, VARIANT_BOOL *Includes);
};

#endif // !defined(_TRIASNATIVEOBJECTSOPERATIONS_H__767429B1_5FC0_415D_91FF_E2B5154DC5A0__INCLUDED_)
