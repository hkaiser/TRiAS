// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.05.2001 11:08:42 
//
// @doc
// @module TRiASNativeAttribute.h | Declaration of the <c CTRiASNativeAttribute> class

#if !defined(_TRIASNATIVEATTRIBUTE_H__9F3E8D98_59CF_4365_AA04_6FAADD5561D1__INCLUDED_)
#define _TRIASNATIVEATTRIBUTE_H__9F3E8D98_59CF_4365_AA04_6FAADD5561D1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeAttribute

class ATL_NO_VTABLE CTRiASNativeAttribute : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASNativeAttribute, &CLSID_TRiASNativeAttribute>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASNativeAttribute, &IID_ITRiASNativeAttribute, &LIBID_TRiASNativeDB, 
		TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>
{
public:
// Construction
	CTRiASNativeAttribute() {}
	~CTRiASNativeAttribute() {}

// Initialisation
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEATTRIBUTE)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASNativeAttribute)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASNativeAttribute)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASNativeAttribute
	STDMETHODIMP get_Name(INT_PTR PrjHandle, INT_PTR Attrib, BSTR *Name);
	STDMETHODIMP put_Name(INT_PTR PrjHandle, INT_PTR Attrib, BSTR Name);
	STDMETHODIMP get_Description(INT_PTR PrjHandle, INT_PTR Attrib, BSTR *Desc);
	STDMETHODIMP put_Description(INT_PTR PrjHandle, INT_PTR Attrib, BSTR Desc);
	STDMETHODIMP get_Objects(INT_PTR PrjHandle, INT_PTR Ident, INT_PTR Attrib, BSTR Start, BSTR End, DBRANGEENUM rgRange, ITRiASEnumNativeObjects **ppVal);

	STDMETHODIMP GetMetaData(INT_PTR PrjHandle, INT_PTR Attrib, BSTR *Name, BSTR *Description);
	STDMETHODIMP SetMetaData(INT_PTR PrjHandle, INT_PTR Attrib, BSTR Name, BSTR Description);
};

#endif // !defined(_TRIASNATIVEATTRIBUTE_H__9F3E8D98_59CF_4365_AA04_6FAADD5561D1__INCLUDED_)
