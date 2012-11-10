// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 11:51:33 
//
// @doc
// @module TRiASNativeIdent.h | Declaration of the <c CTRiASNativeIdent> class

#if !defined(_TRIASNATIVEIDENT_H__9BC43668_03AA_4484_9B0B_AE53E094805D__INCLUDED_)
#define _TRIASNATIVEIDENT_H__9BC43668_03AA_4484_9B0B_AE53E094805D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeIdent

class ATL_NO_VTABLE CTRiASNativeIdent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASNativeIdent, &CLSID_TRiASNativeIdent>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASNativeIdent, &IID_ITRiASNativeIdent, &LIBID_TRiASNativeDB, 
		TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>
{
public:
// Construction
	CTRiASNativeIdent() {}
	~CTRiASNativeIdent() {}

// Initialisation
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEIDENT)
	DECLARE_NOT_AGGREGATABLE(CTRiASNativeIdent)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASNativeIdent)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASNativeIdent)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations

// Interfaces
public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASNativeIdent
	STDMETHODIMP get_Name(INT_PTR PrjHandle, INT_PTR Ident, BSTR *Name);
	STDMETHODIMP put_Name(INT_PTR PrjHandle, INT_PTR Ident, BSTR Name);
	STDMETHODIMP get_OKS(INT_PTR PrjHandle, INT_PTR Ident, BSTR *OKS);
	STDMETHODIMP put_OKS(INT_PTR PrjHandle, INT_PTR Ident, BSTR OKS);
	STDMETHODIMP get_Description(INT_PTR PrjHandle, INT_PTR Ident, BSTR *Desc);
	STDMETHODIMP put_Description(INT_PTR PrjHandle, INT_PTR Ident, BSTR Desc);
	STDMETHODIMP get_Attributes (INT_PTR PrjHandle, INT_PTR Ident, ITRiASEnumNativeAttributes **ppVal);
	STDMETHODIMP get_Objects(INT_PTR PrjHandle, INT_PTR Ident, DWORD dwTypes, ITRiASExpression *pIExpr, ITRiASEnumNativeObjects **ppVal);
	STDMETHODIMP get_Types(INT_PTR hPrjHandle, INT_PTR lIdent, DWORD *pdwTypes);
	STDMETHODIMP get_Counts(INT_PTR PrjHandle, INT_PTR Ident, DWORD *pdwPoints, DWORD *pdwLines, DWORD *pdwAreas, DWORD *pdwTexts, DWORD *pdwCounts);
	STDMETHODIMP get_CreationDate(INT_PTR PrjHandle, INT_PTR Ident, DATE *CreationDate);
	STDMETHODIMP get_ModificationDate(INT_PTR PrjHandle, INT_PTR Ident, DATE *ModificationDate);
	STDMETHODIMP get_Guid(INT_PTR PrjHandle, INT_PTR Ident, GUID *Guid);

	STDMETHODIMP GetAttribute(INT_PTR hPrjHandle, INT_PTR lIdent, BSTR bstrName, VARIANT_BOOL fCaseSensitive, INT_PTR *plMCode);
	STDMETHODIMP PutAttribute(INT_PTR hPrjHandle, INT_PTR lIdent, BSTR bstrName, INT_PTR *plMCode);
	STDMETHODIMP DestroyAttribute(INT_PTR PrjHandle, INT_PTR Ident, BSTR AttribName);
	STDMETHODIMP GetMetaData(INT_PTR PrjHandle, INT_PTR Ident, BSTR *Name, BSTR *Description, BSTR *OKS);
	STDMETHODIMP SetMetaData(INT_PTR PrjHandle, INT_PTR Ident, BSTR Name, BSTR Description, BSTR OKS);
};

#endif // !defined(_TRIASNATIVEIDENT_H__9BC43668_03AA_4484_9B0B_AE53E094805D__INCLUDED_)
