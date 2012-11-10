// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.05.2001 11:14:34 
//
// @doc
// @module TRiASNativeAttributes.h | Declaration of the <c CTRiASNativeAttributes> class

#if !defined(_TRIASNATIVEATTRIBUTES_H__AEBF5E07_3E5F_4F36_99B1_9AC6EEA077C8__INCLUDED_)
#define _TRIASNATIVEATTRIBUTES_H__AEBF5E07_3E5F_4F36_99B1_9AC6EEA077C8__INCLUDED_

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
// CTRiASNativeAttributes
class ATL_NO_VTABLE CTRiASNativeAttributes : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASNativeAttributes, &CLSID_TRiASNativeAttributes>,
	public ISupportErrorInfo,
	public ICollectionOnSTLImpl<
		IDispatchImpl<ITRiASEnumNativeAttributes, &IID_ITRiASEnumNativeAttributes, &LIBID_TRiASNativeDB, 
			TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>, 
		vector<INT_PTR>, INT_PTR, _Copy<INT_PTR>,
		CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _CopyVariantFromPtr<INT_PTR>, vector<INT_PTR> > >
{
public:
	typedef ICollectionOnSTLImpl<
				IDispatchImpl<ITRiASEnumNativeAttributes, &IID_ITRiASEnumNativeAttributes, &LIBID_TRiASNativeDB, 
					TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>, 
				vector<INT_PTR>, INT_PTR, _Copy<INT_PTR>,
				CComEnumOnSTL<IEnumVARIANT, &IID_IEnumVARIANT, VARIANT, _CopyVariantFromPtr<INT_PTR>, vector<INT_PTR> > >
		_CollectionBase;

	CTRiASNativeAttributes()
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEATTRIBUTES)
//	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CTRiASNativeAttributes)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct();
	void FinalRelease();

	BEGIN_COM_MAP(CTRiASNativeAttributes)
		COM_INTERFACE_ENTRY(ITRiASEnumNativeAttributes)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASNativeAttributes
public:
	HRESULT FInit (HPROJECT hPr, INT_PTR lIdent);
	HRESULT __stdcall FInitItem (INT_PTR lMCode, DWORD dwObjTypes, UINT_PTR dwData);

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

#endif // !defined(_TRIASNATIVEATTRIBUTES_H__AEBF5E07_3E5F_4F36_99B1_9AC6EEA077C8__INCLUDED_)
