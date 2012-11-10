// @doc 
// @module TRiASUnitsOfMeasure.h | Declaration of the <c CUnitsOfMeasure> class

#if !defined(_TRIASUNITSOFMEASURE_H__A2497E9F_EF70_11D2_9BE5_5AB320524153__INCLUDED_)
#define _TRIASUNITSOFMEASURE_H__A2497E9F_EF70_11D2_9BE5_5AB320524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUnitsOfMeasure
class ATL_NO_VTABLE CUnitsOfMeasure : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CUnitsOfMeasure, &CLSID_TRiASUnitsOfMeasure>,
	public CErrSupport<CUnitsOfMeasure, &IID_ITRiASUnitsOfMeasure>,
	public IDispatchImpl<ITRiASUnitsOfMeasure, &IID_ITRiASUnitsOfMeasure, 
		&LIBID_TRiASStatistics,
		TYPELIB_STATIST_MAJOR_VERSION, TYPELIB_STATIST_MINOR_VERSION>
{
public:
	CUnitsOfMeasure()
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CUnitsOfMeasure)
	DECLARE_REGISTRY_RESOURCEID(IDR_UNITSOFMEASURE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CUnitsOfMeasure)
		COM_INTERFACE_ENTRY(ITRiASUnitsOfMeasure)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASUnitsOfMeasure
public:
	STDMETHOD(AddUserDefinedUnit)(/*[in]*/ UNITTYPECONSTANTS UnitType, /*[in]*/ BSTR UnitName, /*[in]*/ double NumCompBaseUnits, /*[in]*/ double UnitOffset, /*[in]*/ BSTR bstrAppName, /*[in]*/ BSTR bstrAppVersion, /*[out,retval]*/ LONG *pUnit);
	STDMETHOD(DeleteUserDefinedUnit)(/*[in]*/ UNITTYPECONSTANTS UnitType, /*[in]*/ LONG UnitID, /*[in]*/ BSTR AppName, /*[in]*/ BSTR AppVersionStr);
	STDMETHOD(LoadUserDefinedUnits)(/*[in]*/ BSTR AppName, /*[in]*/ BSTR AppVersionStr);

	STDMETHOD(GetUnitIDs)(/*[in]*/ UNITTYPECONSTANTS UnitType, /*[out, retval]*/ITRiASUnitIDs **ppIUnitIDs);
	STDMETHOD(GetUnitID)(/*[in]*/ UNITTYPECONSTANTS UnitType, /*[in]*/ BSTR UnitName, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL CaseFlag, /*[out, retval]*/ LONG *pUnit);
	STDMETHOD(GetUnitName)(/*[in]*/ LONG UnitId, /*[out, retval]*/ BSTR *UnitName);
	STDMETHOD(GetCompBaseUnit)(/*[in]*/ UNITTYPECONSTANTS UnitType, /*[out, retval]*/ LONG *Unit);
	STDMETHOD(ConvertUnitToUnit)(/*[in]*/ UNITTYPECONSTANTS UnitType, /*[in]*/ double ValueIn, /*[in]*/ LONG UnitIDFrom, /*[in]*/ LONG UnitIDTo, /*[out, retval]*/ double *pValueOut);
};

#endif // !defined(_TRIASUNITSOFMEASURE_H__A2497E9F_EF70_11D2_9BE5_5AB320524153__INCLUDED_)
