// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 13:56:50 
//
// @doc
// @module TRiASNativeIdents.h | Declaration of the <c CTRiASNativeIdents> class

#if !defined(_TRIASNATIVEIDENTS_H__DD15598D_11F0_46E6_8D28_652E3C19B30C__INCLUDED_)
#define _TRIASNATIVEIDENTS_H__DD15598D_11F0_46E6_8D28_652E3C19B30C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "Util.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeIdents

class ATL_NO_VTABLE CTRiASNativeIdents : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASNativeIdents, &CLSID_TRiASNativeIdents>,
	public ISupportErrorInfo,
	public ICollectionOnSTLImpl<
		IDispatchImpl<ITRiASEnumNativeIdents, &IID_ITRiASEnumNativeIdents, &LIBID_TRiASNativeDB, 
			TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>, 
		vector<INT_PTR>, INT_PTR, _Copy<INT_PTR>,
		CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _CopyVariantFromPtr<INT_PTR>, vector<INT_PTR> > >
{
public:
	typedef ICollectionOnSTLImpl<
				IDispatchImpl<ITRiASEnumNativeIdents, &IID_ITRiASEnumNativeIdents, &LIBID_TRiASNativeDB, 
					TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>, 
				vector<INT_PTR>, INT_PTR, _Copy<INT_PTR>,
				CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _CopyVariantFromPtr<INT_PTR>, vector<INT_PTR> > >
		_CollectionBase;

	CTRiASNativeIdents()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEIDENTS)
//	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CTRiASNativeIdents)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

	BEGIN_COM_MAP(CTRiASNativeIdents)
		COM_INTERFACE_ENTRY(ITRiASEnumNativeIdents)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASNativeIdents
public:
	HRESULT FInit (HPROJECT hPr);
	HRESULT __stdcall FInitItem (INT_PTR lIdent, DWORD dwObjTypes, UINT_PTR dwData);

// thread save collection methods
	STDMETHOD(get_Count)(long* pcount)
	{
	ObjectLock l(this);

		return _CollectionBase::get_Count(pcount);
	}
	STDMETHOD(get_Item)(long Index, INT_PTR *pvar)
	{
	ObjectLock l(this);

		return _CollectionBase::get_Item(Index, pvar);
	}
	STDMETHOD(get__NewEnum)(IUnknown** ppUnk)
	{
	ObjectLock l(this);

		return _CollectionBase::get__NewEnum(ppUnk);
	}
};

#endif // !defined(_TRIASNATIVEIDENTS_H__DD15598D_11F0_46E6_8D28_652E3C19B30C__INCLUDED_)
