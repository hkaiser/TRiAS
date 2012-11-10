// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 10:55:46 
//
// @doc
// @module TRiASNativeObject.h | Declaration of the <c CTRiASNativeObject> class

#if !defined(_TRIASNATIVEOBJECT_H__CDD1A0A0_CFF7_489F_AB95_C43B7C756237__INCLUDED_)
#define _TRIASNATIVEOBJECT_H__CDD1A0A0_CFF7_489F_AB95_C43B7C756237__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeObject

class ATL_NO_VTABLE CTRiASNativeObject : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASNativeObject, &CLSID_TRiASNativeObject>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASNativeObject, &IID_ITRiASNativeObject, &LIBID_TRiASNativeDB, 
		TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>
{
public:
// Construction
	CTRiASNativeObject()
	{
	}
	~CTRiASNativeObject()
	{
	}

// Initialisation
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEOBJECT)
	DECLARE_NOT_AGGREGATABLE(CTRiASNativeObject)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASNativeObject)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASNativeObject)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASNativeObject
	STDMETHODIMP get_Guid(INT_PTR PrjHandle, INT_PTR Obj, BSTR *Guid);
	STDMETHODIMP put_Guid(INT_PTR PrjHandle, INT_PTR Obj, BSTR Guid);
	STDMETHODIMP get_Attribute(INT_PTR PrjHandle, INT_PTR Obj, INT_PTR Attrib, BSTR *AttrVal);
	STDMETHODIMP put_Attribute(INT_PTR PrjHandle, INT_PTR Obj, INT_PTR Attrib, BSTR AttrVal);

	STDMETHODIMP GetGeometry(INT_PTR PrjHandle, INT_PTR Obj, BSTR GeomName, SAFEARRAY **ppGeom);
	STDMETHODIMP PutGeometry(INT_PTR PrjHandle, INT_PTR Obj, DWORD dwType, BSTR GeomName, SAFEARRAY *pGeom);
	STDMETHODIMP GetGeometryWKT(INT_PTR PrjHandle, INT_PTR Obj, BSTR GeomName, BSTR *GeomWKT);
	STDMETHODIMP PutGeometryWKT(INT_PTR PrjHandle, INT_PTR Obj, DWORD ObjType, BSTR GeomName, BSTR GeomWKT);
};

#endif // !defined(_TRIASNATIVEOBJECT_H__CDD1A0A0_CFF7_489F_AB95_C43B7C756237__INCLUDED_)
