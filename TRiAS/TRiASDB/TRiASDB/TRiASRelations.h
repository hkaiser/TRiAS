///////////////////////////////////////////////////////////////////////////
// TRiASRelations.h : Declaration of the CTRiASRelations

#if !defined(_TRIASRELATIONS_H__7C8CB9C0_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASRELATIONS_H__7C8CB9C0_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASRelations
class ATL_NO_VTABLE CTRiASRelations : 
	public CReportErrorComCoClass<CTRiASRelations, &CLSID_TRiASRelations, &IID_ITRiASRelations>,
	public ISupportErrorInfo,
	public CComObjectRootEx<CComObjectThreadModel>,
	public IDispatchImpl<ITRiASRelations, &IID_ITRiASRelations, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASRelations interface_t;
	typedef ITRiASRelation controlled_t;

	CTRiASRelations()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASRelations)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASRELATIONS)

	BEGIN_COM_MAP(CTRiASRelations)
		COM_INTERFACE_ENTRY(ITRiASRelations)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASRelations
public:
};

#endif // !defined(_TRIASRELATIONS_H__7C8CB9C0_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
