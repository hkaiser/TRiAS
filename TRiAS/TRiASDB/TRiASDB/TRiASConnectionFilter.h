// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.12.2002 14:18:23 
//
// @doc
// @module TRiASConnectionFilter.h | Declaration of the <c CTRiASConnectionFilter> class

#if !defined(_TRIASCONNECTIONFILTER_H__210A1129_86B3_4868_A5DF_7A4EEED4C122__INCLUDED_)
#define _TRIASCONNECTIONFILTER_H__210A1129_86B3_4868_A5DF_7A4EEED4C122__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// Versioning (CSaveObjectCollection)
#define CONNECTFILTER_VERSION_100		0x0100
#define CONNECTFILTER_VERSION_101		0x0101
#define CONNECTFILTER_LASTKNOWNVERSION	CONNECTFILTER_VERSION_101
#define CONNECTFILTER_MINORVERSIONMASK	0xff
#define CONNECTFILTER_SIGNATURE			0x49464F43		// COFI

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnectionFilter
class ATL_NO_VTABLE CTRiASConnectionFilter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CReportErrorComCoClass<CTRiASConnectionFilter, &CLSID_TRiASConnectionFilter, 
		&IID_ITRiASConnectionFilter>,
	public ISupportErrorInfo,
	public IPersistStreamInit,
	public IProvideClassInfo2Impl<&CLSID_TRiASConnectionFilter, &IID_ITRiASConnectionFilter, 
		&LIBID_TRiASDB, TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASConnectionFilter, &IID_ITRiASConnectionFilter, 
		&LIBID_TRiASDB, TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASConnectionFilter() :
		m_rgType(CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers),
		m_fIsInitialized(false), m_fIsDirty(false)
	{
	}
	~CTRiASConnectionFilter() {}

	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCONNECTIONFILTER)
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CTRiASConnectionFilter)
		COM_INTERFACE_ENTRY(ITRiASConnectionFilter)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IProvideClassInfo2)
		COM_INTERFACE_ENTRY(IProvideClassInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASConnectionFilter
public:
	STDMETHOD(get_Geometry)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Geometry)(/*[in]*/ IDispatch *pIGeometry);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHODIMP get_Type(CONNECTIONFILTERTYPE *prgType);
	STDMETHODIMP put_Type(CONNECTIONFILTERTYPE rgType);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

private:
	CComBSTR m_bstrName;
	WDispatch m_Geometry;
	CONNECTIONFILTERTYPE m_rgType;

	bool m_fIsInitialized;
	bool m_fIsDirty;
};

#endif // !defined(_TRIASCONNECTIONFILTER_H__210A1129_86B3_4868_A5DF_7A4EEED4C122__INCLUDED_)
