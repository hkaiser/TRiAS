// @doc 
// @module TRiASVariantProperty.cpp | Implementation of the <c CTRiASVariantPropertyBase> 
// and <c CTRiASVariantProperty> classes

#include "stdafx.h"

#include <Com/VariantHelpers.h>

#include "Strings.h"
#include "Wrapper.h"
#include "TRiASDBDispIds.h"

#include "TRiASVariantProperty.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASVariantProperty);
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASAutoSaveProperty);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASVariantProperty::Dump()
{
	return S_OK;
}

HRESULT CTRiASAutoSaveProperty::Dump()
{
CComVariant Value("<Unknown>");

	USES_CONVERSION;
	if (SUCCEEDED(m_Value.ChangeType (VT_BSTR)))
		Value = m_Value;

os_string str (OLE2A(V_BSTR(&Value)));

	D_OUT(1) <<
		"\tCTRiASAutoSaveProperty: pending " << str << "\r\n" <<
	D_END;
	return S_OK;
}
#endif // defined(_DUMP_PENDING_OBJECTS)

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASVariantProperty, CTRiASVariantProperty)
RT_OBJECT_ENTRY(CLSID_TRiASAutoSaveProperty, CTRiASAutoSaveProperty)

///////////////////////////////////////////////////////////////////////////////
// Tearoff-Objekt, welches ITRiASValueEvents abfangen kann
STDMETHODIMP CTRiASValueEventSink::ModifyingValue (BSTR Name, VARIANT_BOOL *pVal)
{
	return m_pOwner -> Fire_ModifyingProperty (Name, pVal);
}

STDMETHODIMP CTRiASValueEventSink::ValueToModify (BSTR Name)
{
	return m_pOwner -> Fire_PropertyToModify (Name);
}

STDMETHODIMP CTRiASValueEventSink::ValueModified (BSTR Name)
{
	return m_pOwner -> Fire_PropertyModified (Name);
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASVariantProperty::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return TRIASDB_E_INVALID_PARAMETER;

	*pClassID = CLSID_TRiASVariantProperty;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASAutoSaveProperty::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return TRIASDB_E_INVALID_PARAMETER;

	*pClassID = CLSID_TRiASAutoSaveProperty;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASVariantPropertyBase

///////////////////////////////////////////////////////////////////////////////
// ITRiASPropertyEvents
inline 
HRESULT CTRiASVariantPropertyBase::Fire_ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	if (m_PropEvents.IsValid())
		return m_PropEvents -> ModifyingProperty (Name, pVal);
	return S_OK;
}

inline 
HRESULT CTRiASVariantPropertyBase::Fire_PropertyToModify (BSTR Name)
{
	if (m_PropEvents.IsValid())
		return m_PropEvents -> PropertyToModify (Name);
	return S_OK;
}

inline 
HRESULT CTRiASVariantPropertyBase::Fire_PropertyModified (BSTR Name)
{
	if (m_PropEvents.IsValid())
		return m_PropEvents -> PropertyModified (Name);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASVariantPropertyBase::PutValue (BSTR Name, VARIANT Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_ModifyingProperty (Name, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToModify (Name));

// eigentliche Operation
	if (0 != m_dwCookie && (V_ISUNKNOWN(&m_Value) || V_ISDISPATCH(&m_Value))) {
		AtlUnadvise(V_UNKNOWN(&m_Value), IID_ITRiASValueEvents, m_dwCookie);
		m_dwCookie = 0;
	}

	RETURN_FAILED_HRESULT(m_Value.Copy(&Value));
	
	if (V_ISUNKNOWN(&m_Value) || V_ISDISPATCH(&m_Value))
		AtlAdvise (V_UNKNOWN(&m_Value), GetUnknown(), IID_ITRiASValueEvents, &m_dwCookie);

// Event hinterher
	RETURN_FAILED_HRESULT(Fire_PropertyModified (Name));
	return S_OK;
}

STDMETHODIMP CTRiASVariantPropertyBase::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return TRIASDB_E_INVALID_PARAMETER;

CComVariant val (m_Value);

	return val.Detach (pVal);
}

STDMETHODIMP CTRiASVariantPropertyBase::PutType (BSTR Name, PROPERTY_TYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_ModifyingProperty (Name, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToModify (Name));

	m_rgType = newVal;

// Event hinterher
	RETURN_FAILED_HRESULT(Fire_PropertyModified (Name));
	return S_OK;
}

STDMETHODIMP CTRiASVariantPropertyBase::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return TRIASDB_E_INVALID_PARAMETER;

	*pVal = m_rgType;
	return S_OK;
}

STDMETHODIMP CTRiASVariantPropertyBase::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_ModifyingProperty (Name, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToModify (Name));

// eigentliche Aktion
	if (0 != m_dwCookie && (V_ISUNKNOWN(&m_Value) || V_ISDISPATCH(&m_Value))) {
		AtlUnadvise(V_UNKNOWN(&m_Value), IID_ITRiASValueEvents, m_dwCookie);
		m_dwCookie = 0;
	}

	m_rgType = Type;
	RETURN_FAILED_HRESULT(m_Value.Copy(&Val));

	if (V_ISUNKNOWN(&m_Value) || V_ISDISPATCH(&m_Value))
		AtlAdvise (V_UNKNOWN(&m_Value), GetUnknown(), IID_ITRiASValueEvents, &m_dwCookie);

// Event hinterher
	RETURN_FAILED_HRESULT(Fire_PropertyModified (Name));
	return S_OK;
}

STDMETHODIMP CTRiASVariantPropertyBase::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return TRIASDB_E_INVALID_PARAMETER;

	RETURN_FAILED_HRESULT(GetType (Name, pType));

CComVariant val (m_Value);

	return val.Detach (pVal);
}

STDMETHODIMP CTRiASVariantPropertyBase::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Ein Objekt (IDispatch) welches in einem VariantProperty gespeichert ist, kann
// eine Funktion [id(DISPID_PROPERTYREFRESH)] HRESULT Refresh(); unterstützen.
	COM_TRY {
	CComVariant vData;

		if (SUCCEEDED(vData.ChangeType (VT_DISPATCH, &m_Value))) 
			_com_dispatch_method(
				V_DISPATCH(&vData), DISPID_PROPERTYREFRESH, DISPATCH_METHOD, 
				VT_EMPTY, NULL, L"");

	} COM_CATCH_IGNORE;
	return S_OK;
}

HRESULT CTRiASVariantPropertyBase::ShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Ein Objekt (IDispatch) welches in einem VariantProperty gespeichert ist, kann
// eine Funktion [id(DISPID_PROPERTYSHUTDOWN)] HRESULT ShutDown(); unterstützen.
	COM_TRY {
	CComVariant vData;

		if (SUCCEEDED(vData.ChangeType (VT_DISPATCH, &m_Value))) 
			_com_dispatch_method(
				V_DISPATCH(&vData), DISPID_PROPERTYSHUTDOWN, DISPATCH_METHOD, 
				VT_EMPTY, NULL, L"");

	} COM_CATCH_IGNORE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CTRiASVariantPropertyBase::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pISite) {
	// Parent kann 'ITRiASPropertyEvents' unterstützen
		pISite -> QueryInterface(m_PropEvents.ppi());
		return m_PropEvents.IsValid() ? S_OK : S_FALSE;
	} else {
	// am Connectionpoint abmelden
		if (0 != m_dwCookie && (V_ISUNKNOWN(&m_Value) || V_ISDISPATCH(&m_Value))) {
			AtlUnadvise(V_UNKNOWN(&m_Value), IID_ITRiASValueEvents, m_dwCookie);
			m_dwCookie = 0;
		}

	// Parent freigeben
		m_PropEvents.Assign(NULL);
		return S_OK;
	}
}

STDMETHODIMP CTRiASVariantPropertyBase::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_PropEvents) 
		return TRIASDB_E_PROPERTY_NOT_INITIALIZED;
	return m_PropEvents -> QueryInterface (riid, ppvSite);
}

///////////////////////////////////////////////////////////////////////////////
// CTRiASAutoSaveProperty
STDMETHODIMP CTRiASAutoSaveProperty::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return TRIASDB_E_INVALID_PARAMETER;

	*pVal = PROPERTY_TYPE(m_rgType|PROPERTY_TYPE_NeedsSavingHelp);
	return S_OK;
}

