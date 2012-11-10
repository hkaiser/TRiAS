// @doc 
// @module TRiASStgProperty.cpp | Implementation of the <c CTRiASStgProperty> class
// @comm Das Objekt <o CTRiASStgProperty> implementiert die Projekt/Database-Property 'StgService',
// welche das aktuelle IStorage-Interface des Projektes/der Database liefert.
// Dieses Objekt ist lediglich lokal verfügbar (kein Eintrag in der Registry)

#include "stdafx.h"

#include "TRiASDBGuids.h"
#include "Strings.h"
#include "Wrapper.h"

#include "TRiASProjectStg.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASStgProperty, CTRiASStgProperty)

/////////////////////////////////////////////////////////////////////////////
// CTRiASStgProperty

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASStgProperty::PutValue (BSTR Name, VARIANT Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStgProperty::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASStgProperty::GetValue");

	_ASSERTE(!wcscmp (Name, g_cbStgService));	// muß "StgService" sein
	if (wcscmp (Name, g_cbStgService))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASStgProperty::GetValue");

WStorage Stg;
HRESULT hr = RetrieveStorage (Stg.ppi());

	if (SUCCEEDED(hr)) {
		V_VT(pVal) = VT_UNKNOWN;
		V_UNKNOWN(pVal) = Stg.detach();
	}
	return hr;
}

STDMETHODIMP CTRiASStgProperty::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStgProperty::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASStgProperty::GetType");

	_ASSERTE(!wcscmp (Name, g_cbStgService));	// muß "StgService" sein
	if (wcscmp (Name, g_cbStgService))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASStgProperty::GetType");

	*pVal = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CTRiASStgProperty::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASStgProperty::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASStgProperty::GetValueAndType");

	_ASSERTE(!wcscmp (Name, g_cbStgService));	// muß "StgService" sein
	if (wcscmp (Name, g_cbStgService))
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASStgProperty::GetValueAndType");

	COM_TRY {
	WStorage Stg;

		THROW_FAILED_HRESULT(RetrieveStorage (Stg.ppi()));

		V_VT(pVal) = VT_UNKNOWN;
		V_UNKNOWN(pVal) = Stg.detach();

		*pType = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);

	} COM_CATCH;

	return S_OK;
}

HRESULT CTRiASStgProperty::RetrieveStorage (IStorage **ppIStg)
{
	if (!m_Cont)
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	return m_Cont -> GetObjectStorage ((LPOLESTR)g_cbStgService, NULL, IID_IStorage, (LPVOID *)ppIStg);
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CTRiASStgProperty::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pISite)
		return pISite -> QueryInterface (m_Cont.ppi());
	else {
		m_Cont.Assign(NULL);
		return S_OK;
	}
}

STDMETHODIMP CTRiASStgProperty::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_Cont) 
		return REPORT_DBERROR(TRIASDB_E_PROPERTY_NOT_INITIALIZED);
	return m_Cont -> QueryInterface (riid, ppvSite);
}


STDMETHODIMP CTRiASStgProperty::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}
