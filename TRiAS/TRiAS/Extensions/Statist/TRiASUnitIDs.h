// @doc 
// @module TRiASUnitIDs.h | Declaration of the <c CUnitIDs> class

#if !defined(_TRIASUNITIDS_H__A2497E9E_EF70_11D2_9BE5_5AB320524153__INCLUDED_)
#define _TRIASUNITIDS_H__A2497E9E_EF70_11D2_9BE5_5AB320524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <Atl/Colltempl.h>

/////////////////////////////////////////////////////////////////////////////
// CUnitIDs
class ATL_NO_VTABLE CUnitIDs : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CUnitIDs, &CLSID_TRiASUnitIDs>,
	public CErrSupport<CUnitIDs, &IID_ITRiASUnitIDs>,
	public IStaticCollectionImpl<LONG, &LIBID_TRiASStatistics, 
		TYPELIB_STATIST_VERSION_MAJOR, TYPELIB_STATIST_VERSION_MINOR,
		ITRiASUnitIDs, &IID_ITRiASUnitIDs> 
{
public:
	CUnitIDs()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CUnitIDs)

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CUnitIDs)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CUnitIDs)
		COM_INTERFACE_ENTRY(ITRiASUnitIDs)
	END_COM_MAP()

// ITRiASUnitIDs
public:
};

#endif // !defined(_TRIASUNITIDS_H__A2497E9E_EF70_11D2_9BE5_5AB320524153__INCLUDED_)
