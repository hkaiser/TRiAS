// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 08/26/1998 11:46:12 PM
//
// @doc
// @module DatabaseFeatureMap.cpp | Implementation of the <c CDatabaseFeatureMap> class

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"
#include "GlobalVars.h"

#include <Com/PropertyHelper.h>

#include "DatabaseFeatureMap.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_DatabaseFeatureMap, CDatabaseFeatureMap)

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFeatureMap
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASObjectHandleMap);

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CDatabaseFeatureMap::PutValue (BSTR Name, VARIANT Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CDatabaseFeatureMap::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CDatabaseFeatureMap::GetValue");

	_ASSERTE(!wcscmp (Name, g_cbFeatureMap));	// muß "FeatureMap" sein
	if (wcscmp (Name, g_cbFeatureMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CDatabaseFeatureMap::GetValue");

	return GetDatabaseFeatureMap (pVal);
}

STDMETHODIMP CDatabaseFeatureMap::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CDatabaseFeatureMap::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CDatabaseFeatureMap::GetType");

	_ASSERTE(!wcscmp (Name, g_cbFeatureMap));	// muß "FeatureMap" sein
	if (wcscmp (Name, g_cbFeatureMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CDatabaseFeatureMap::GetValue");

	*pVal = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CDatabaseFeatureMap::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CDatabaseFeatureMap::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CDatabaseFeatureMap::GetType");

	_ASSERTE(!wcscmp (Name, g_cbFeatureMap));	// muß "FeatureMap" sein
	if (wcscmp (Name, g_cbFeatureMap))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CDatabaseFeatureMap::GetValue");

	*pType = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return GetDatabaseFeatureMap (pVal);
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CDatabaseFeatureMap::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pISite)
		return pISite -> QueryInterface(m_Objs.ppi());
	else {
		m_Objs.Assign(NULL);
		return S_OK;
	}
}

STDMETHODIMP CDatabaseFeatureMap::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_Objs) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	return m_Objs -> QueryInterface (riid, ppvSite);
}

STDMETHODIMP CDatabaseFeatureMap::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Helper
HRESULT CDatabaseFeatureMap::GetDatabaseFeatureMap (VARIANT *pVal)
{
	if (!m_Objs.IsValid())
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);

	COM_TRY {
	WTRiASDatabase Parent;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Objs, Parent.ppi()));

	WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbFeatureMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	CComVariant Val (Map);

		THROW_FAILED_HRESULT(Val.Detach(pVal));

	} COM_CATCH;
	return S_OK;
}
