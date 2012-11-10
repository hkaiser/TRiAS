///////////////////////////////////////////////////////////////////////////
// TRiASRelation.h : Declaration of the CTRiASRelation

#if !defined(_TRIASRELATION_H__7C8CB9BF_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASRELATION_H__7C8CB9BF_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASRelation
class ATL_NO_VTABLE CTRiASRelation : 
	public CReportErrorComCoClass<CTRiASRelation, &CLSID_TRiASRelation, &IID_ITRiASRelation>, 
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTRiASRelation>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public IDispatchImpl<ITRiASRelation, &IID_ITRiASRelation, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASRelation()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASRelation)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASRELATION)

	BEGIN_COM_MAP(CTRiASRelation)
		COM_INTERFACE_ENTRY(ITRiASRelation)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASRelation)
	END_CONNECTION_POINT_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASRelation
public:
};

#endif // !defined(_TRIASRELATION_H__7C8CB9BF_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
