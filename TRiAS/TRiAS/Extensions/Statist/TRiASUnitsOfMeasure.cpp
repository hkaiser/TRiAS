// @doc 
// @module TRiASUnitsOfMeasure.h | Implementation of the <c CUnitsOfMeasure> class

#include "stdafx.h"

#include "StatistApp.h"
#include "TRiASUnitsOfMeasure.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASUnitsOfMeasure, CUnitsOfMeasure)

/////////////////////////////////////////////////////////////////////////////
// CUnitsOfMeasure

STDMETHODIMP CUnitsOfMeasure::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASUnitsOfMeasure
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CUnitsOfMeasure::GetUnitIDs(UNITTYPECONSTANTS UnitType, ITRiASUnitIDs **ppIUnitIDs)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	CHECKOUTPOINTER(ppIUnitIDs);

	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::GetUnitID(
	UNITTYPECONSTANTS UnitType, BSTR UnitName, VARIANT_BOOL CaseFlag, LONG *pUnit)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	CHECKOUTPOINTER(pUnit);

	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::GetUnitName(LONG UnitId, BSTR *pUnitName)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	CHECKOUTPOINTER(pUnitName);

	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::GetCompBaseUnit(UNITTYPECONSTANTS UnitType, LONG *pUnit)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	CHECKOUTPOINTER(pUnit);

	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::ConvertUnitToUnit(
	UNITTYPECONSTANTS UnitType, double ValueIn, LONG UnitIDFrom, LONG UnitIDTo, double *pValueOut)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	CHECKOUTPOINTER(pValueOut);

	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::AddUserDefinedUnit(
	UNITTYPECONSTANTS UnitType, BSTR UnitName, double NumCompBaseUnits, double UnitOffset, 
	BSTR bstrAppName, BSTR bstrAppVersion, LONG *pUnit)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	CHECKOUTPOINTER(pUnit);

	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::DeleteUserDefinedUnit(UNITTYPECONSTANTS UnitType, LONG UnitID, BSTR AppName, BSTR AppVersionStr)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	return S_OK;
}

STDMETHODIMP CUnitsOfMeasure::LoadUserDefinedUnits(BSTR AppName, BSTR AppVersionStr)
{
#if defined(_MFC_VER)
	AFX_MANAGE_STATE(AfxGetAppModuleState())
#endif // defined(_MFC_VER)
	return S_OK;
}
