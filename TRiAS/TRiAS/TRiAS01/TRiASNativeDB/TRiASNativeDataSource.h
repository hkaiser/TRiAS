// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 10.04.2001 13:48:01 
//
// @doc
// @module TRiASNativeDataSource.h | Declaration of the <c CTRiASNativeDataSource> class

#if !defined(_TRIASNATIVEDATASOURCE_H__DC67CA98_1C54_4519_89C1_2EA63777C512__INCLUDED_)
#define _TRIASNATIVEDATASOURCE_H__DC67CA98_1C54_4519_89C1_2EA63777C512__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASNativeDataSource

class ATL_NO_VTABLE CTRiASNativeDataSource : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTRiASNativeDataSource, &CLSID_TRiASNativeDataSource>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASNativeDataSource, &IID_ITRiASNativeDataSource, &LIBID_TRiASNativeDB, 
		TYPELIB_TRIASNATIVEDB_VERSION_MAJOR, TYPELIB_TRIASNATIVEDB_VERSION_MINOR>
{
public:
// Construction
	CTRiASNativeDataSource() {}
	~CTRiASNativeDataSource() {}

// Initialisation
	HRESULT FinalConstruct();
	void FinalRelease();

// Operations

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASNATIVEDATASOURCE)
	DECLARE_NOT_AGGREGATABLE(CTRiASNativeDataSource)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

// Interface map
	BEGIN_COM_MAP(CTRiASNativeDataSource)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASNativeDataSource)
	END_COM_MAP()

// Implementation
protected:
// Attributes

// Operations
	HRESULT OpenDatabase (LPCTSTR pcName, IStorage *pIStg, DWORD dwMode, HPROJECT *phPr);
	HRESULT OpenMetaDatabase (HPROJECT hPr, DWORD dwMode);
	HRESULT OpenStoragePbd (IStorage *pIStg, bool fReadOnly, HPROJECT *phPbdPr);
	HRESULT SaveMetaDatabase (HPROJECT hPr);

	HRESULT FullOpen (BSTR Name, DWORD dwMode, HPROJECT *pPrjHandle);

	HRESULT CreateMainDatabase (BSTR Name, UINT uiResID, bool fCompressed, os_string &rStr, IStorage **ppIStg);
	HRESULT CreateMetaDatabase (IStorage *pIStg, UINT uiResID, BOOL fCompressed, LPCTSTR pcName);

public:
// ISupportsErrorInfo
	STDMETHODIMP InterfaceSupportsErrorInfo(REFIID riid);

// ITRiASNativeDataSource
public:
	STDMETHOD(get_Classes)(/*[in]*/ INT_PTR hPr, /*[out, retval]*/ ITRiASEnumNativeIdents **pVal);
	STDMETHOD(get_Class)(/*[in]*/ INT_PTR PrjHandle, /*[in]*/ BSTR IdentName, /*[in]*/ VARIANT_BOOL fCaseSensitive, /*[out, retval]*/ INT_PTR *Val);
	STDMETHOD(get_Version)(/*[in]*/ INT_PTR hPrHandle, /*[out, retval]*/ BSTR *pbstrVersion);
	STDMETHOD(get_Name)(/*[in]*/ INT_PTR hPrHandle, /*[out, retval]*/ BSTR *pbstrName);
	STDMETHOD(get_OpenedRO)(/*[in]*/ INT_PTR PrjHandle, /*[out, retval]*/ VARIANT_BOOL *RO);
	STDMETHOD(get_CoordSystemWKT)(/*[in]*/ INT_PTR PrjHandle, /*[out]*/ UINT *puiEpsgId, /*[out, retval]*/ BSTR *CoordSystemWKT);
	STDMETHOD(get_DbmsVersion)(/*[out, retval]*/ BSTR *pbstrVersion);
	STDMETHOD(get_IdentsHaveDates)(INT_PTR PrjHandle, VARIANT_BOOL *HasDates);

	STDMETHOD(Open)(/*[in]*/ BSTR Name, /*[in]*/ DWORD dwMode, /*[in]*/ NATIVEOPENMODE dwOpenMode, /*[out, retval]*/ INT_PTR *PrjHandle);
	STDMETHOD(Close)(/*[in]*/ INT_PTR PrjHandle);
	STDMETHOD(Create)(BSTR Name, NATIVECREATEMODE Mode);
	STDMETHOD(Destroy)(BSTR Name);
	STDMETHODIMP Save(INT_PTR PrjHandle);

	STDMETHODIMP AddClass(INT_PTR PrjHandle, BSTR IdentName, INT_PTR *Val);
	STDMETHODIMP DestroyClass(INT_PTR PrjHandle, BSTR IdentName);
};

#endif // !defined(_TRIASNATIVEDATASOURCE_H__DC67CA98_1C54_4519_89C1_2EA63777C512__INCLUDED_)
