// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.12.2002 13:30:54 
//
// @doc
// @module TRiASConnectionFilters.h | Declaration of the <c CTRiASConnectionFilters> class

#if !defined(_TRIASCONNECTIONFILTERS_H__715B61E6_1B5E_461B_8E9D_3B83001DB903__INCLUDED_)
#define _TRIASCONNECTIONFILTERS_H__715B61E6_1B5E_461B_8E9D_3B83001DB903__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <idl/Collection.h>
#include <Atl/CollTempl.h>

#include "resource.h"			// main symbols
#include "PersistStgImpl.h"		// IPersistStorageOMImpl

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnectionFilters
class ATL_NO_VTABLE CTRiASConnectionFilters : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASConnectionFilters, &CLSID_TRiASConnectionFilters>,
	public IPersistStorageOMImpl<CTRiASConnectionFilters>,
	public IDynamicCollectionImpl<ITRiASConnectionFilter, &IID_ITRiASConnectionFilter,
		&LIBID_TRiASDB, TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASConnectionFilters, &IID_ITRiASConnectionFilters, 
		&LIBID_TRiASDB, TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASConnectionFilters interface_t;
	typedef ITRiASConnectionFilter controlled_t;
	typedef IDynamicCollectionImpl<ITRiASConnectionFilter, &IID_ITRiASConnectionFilter,
		&LIBID_TRiASDB, TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
		collection_base_t;

	CTRiASConnectionFilters()
	{
	}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCONNECTIONFILTERS)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTRiASConnectionFilters)
		COM_INTERFACE_ENTRY(ITRiASConnectionFilters)
		COM_INTERFACE_ENTRY(IDynamicCollection)
		COM_INTERFACE_ENTRY(IStaticCollection)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASConnectionFilters)
		COM_INTERFACE_ENTRY_IID(IID_IPersistStorage, IPersistStorageOMImpl<CTRiASConnectionFilters>)
		COM_INTERFACE_ENTRY2_IID(IID_IPersist, IPersist, IPersistStorageOMImpl<CTRiASConnectionFilters>)
	END_COM_MAP()

    HRESULT _Add (IDispatch* pDispObj, VARIANT_BOOL fFullAdd)
	{
		_ASSERTE(fFullAdd);
		RETURN_FAILED_HRESULT(this->InitAppend(pDispObj));
		return S_OK;
	}
    STDMETHOD(DeleteByIndex) (VARIANT Index);
    STDMETHOD(DeleteByObject) (IDispatch* pDispObj);

// must be implemented for IPersistStorageOMImpl<>
	LPCTSTR GetDescription() const 
		{ return g_cbTRiASConnectionFilters; }

// ITRiASConnectionFilters
public:
	STDMETHODIMP Add(BSTR Name, ITRiASConnectionFilter **ppIFilter);
};

#endif // !defined(_TRIASCONNECTIONFILTERS_H__715B61E6_1B5E_461B_8E9D_3B83001DB903__INCLUDED_)
