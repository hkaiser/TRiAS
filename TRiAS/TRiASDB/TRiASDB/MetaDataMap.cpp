// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 08/26/1998 11:46:12 PM
//
// @doc
// @module MetaDataMap.cpp | Implementation of the <c CMetaDataMap>,
// <c CObjectsMetaDataMap> and <c CFeatureMetaDataMap> classes

#include "stdafx.h"

#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>

#include "Strings.h"
#include "MetaDataMap.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASMetaDataMap, CMetaDataMap)

/////////////////////////////////////////////////////////////////////////////
// CFeatureMetaDataMap
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASPropertyEvents);
DefineSmartInterface(TRiASObjects);

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CMetaDataMap::PutValue (BSTR Name, VARIANT Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CMetaDataMap::GetValue (BSTR Name, VARIANT *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return E_POINTER;

	_ASSERTE(!wcscmp (Name, g_cbMetaDataMap));	// muß "FeatureMap" sein
	if (wcscmp (Name, g_cbMetaDataMap))
		return TRIASDB_E_INVALID_PARAMETER;

	if (SUCCEEDED(GenerateUniqueMapName())) {
		RETURN_FAILED_HRESULT(GetFeatureMetaDataMap (pVal));
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMetaDataMap::PutType (BSTR Name, PROPERTY_TYPE Value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CMetaDataMap::GetType (BSTR Name, PROPERTY_TYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal)
		return E_POINTER;

	_ASSERTE(!wcscmp (Name, g_cbMetaDataMap));	// muß "MetaDataMap" sein
	if (wcscmp (Name, g_cbMetaDataMap))
		return TRIASDB_E_INVALID_PARAMETER;

	*pVal = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	return S_OK;
}

STDMETHODIMP CMetaDataMap::PutValueAndType(BSTR Name, VARIANT Val, PROPERTY_TYPE Type)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CMetaDataMap::GetValueAndType(BSTR Name, VARIANT * pVal, PROPERTY_TYPE * pType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Name || NULL == pVal || NULL == pType)
		return E_POINTER;

	_ASSERTE(!wcscmp (Name, g_cbMetaDataMap));	// muß "MetaDataMap" sein
	if (wcscmp (Name, g_cbMetaDataMap))
		return TRIASDB_E_INVALID_PARAMETER;

	*pType = PROPERTY_TYPE(PROPERTY_TYPE_Dynamic|PROPERTY_TYPE_ReadOnly);
	if (SUCCEEDED(GenerateUniqueMapName())) {
		RETURN_FAILED_HRESULT(GetFeatureMetaDataMap (pVal));
		return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP CMetaDataMap::SetSite (IUnknown *pISite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL != pISite)
		return pISite -> QueryInterface(m_Target.ppi());
	else {
		RETURN_FAILED_HRESULT(ReleaseFeatureMetaDataMap());
		m_Target.Assign(NULL);
		return S_OK;
	}
}

STDMETHODIMP CMetaDataMap::GetSite (REFIID riid, void **ppvSite)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_Target.IsValid()) 
		return TRIASDB_E_PROPERTY_NOT_INITIALIZED;
	return m_Target -> QueryInterface (riid, ppvSite);
}

STDMETHODIMP CMetaDataMap::Refresh(BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helper
HRESULT CMetaDataMap::GetFeatureMetaDataMap (VARIANT *pVal)
{
	if (!m_Target.IsValid())
		return TRIASDB_E_PROPERTY_NOT_INITIALIZED;

	COM_TRY {
	WTRiASConnection Parent;
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Target, Parent.ppi()));
		THROW_FAILED_HRESULT(GetProperties (Parent, Props.ppi()));

	WTRiASMDSMap Map (GetProperty (Props, m_bstrName, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab

	// MetaDataMap ggf. erzeugen
		if (!Map.IsValid()) {
		// Map an der Connection neu wegschreiben (ist nach SaveAs des Projektes notwendig,
		// da die Connection dabei sämtliche Properties freigibt)

		// Events vorher
		CComBool fVal;
			
			THROW_FAILED_HRESULT(ModifyingValue (m_bstrName, &fVal)); 
			if (fVal)
				return S_FALSE;
			THROW_FAILED_HRESULT(ValueToModify (m_bstrName));

			if (!m_Map.IsValid()) {
			// Map neu erzeugen
				Map = WTRiASMDSMap(CLSID_TRiASMDSMap);

			// beim Connectionpoint für Modifikationen anmelden
				_ASSERTE(0 == m_dwCookie);
				THROW_FAILED_HRESULT(AtlAdvise (Map, GetUnknown(), IID_ITRiASValueEvents, &m_dwCookie));
				m_Map = Map;
 			} 
 			else {
 			// gecachte Map verwenden
 				Map = m_Map;
 			}
			SetProperty (Props, m_bstrName, Map, true);

		// Event hinterher
			THROW_FAILED_HRESULT(ValueModified (m_bstrName));
		} 
		else if (!m_Map.IsValid()) {
		// eben für selbiges CTRiASProject::SaveAs die Map hier festhalten
			if (0 == m_dwCookie) {	// ggf. nach Wiedereröffnen neu verbunden
				THROW_FAILED_HRESULT(AtlAdvise (Map, GetUnknown(), IID_ITRiASValueEvents, &m_dwCookie));
			}
			m_Map = Map;
		}

	// Resultat zurückliefern
	CComVariant Val (m_Map);

		THROW_FAILED_HRESULT(Val.Detach(pVal));

	} COM_CATCH;
	return S_OK;
}

HRESULT CMetaDataMap::ReleaseFeatureMetaDataMap()
{
	if (!m_Target.IsValid())
		return TRIASDB_E_PROPERTY_NOT_INITIALIZED;

	COM_TRY {
	WTRiASConnection Parent;
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Target, Parent.ppi()));
		THROW_FAILED_HRESULT(GetProperties (Parent, Props.ppi()));

	// Events vorher
	CComBool fVal;
		
		THROW_FAILED_HRESULT(ModifyingValue (m_bstrName, &fVal)); 
		if (fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(ValueToModify (m_bstrName));

	// MetaDataMap beim ConnPnt abmelden
		_ASSERTE(m_Map.IsValid());
		_ASSERTE(0 != m_dwCookie);

		AtlUnadvise(m_Map, IID_ITRiASValueEvents, m_dwCookie);
		m_dwCookie = 0;

	// Property wieder freigeben
		THROW_FAILED_HRESULT(DelProperty (Props, m_bstrName));

	// Event hinterher
		THROW_FAILED_HRESULT(ValueModified (m_bstrName));

		m_Map.Assign(NULL);
		m_bstrName.Empty();

	} COM_CATCH;
	return S_OK;
}

HRESULT CMetaDataMap::GenerateUniqueMapName()
{
	if (!m_bstrName || 0 == m_bstrName.Length()) {
		_ASSERTE(m_Target.IsValid());

	CComBSTR bstrTable, bstrName (g_cbMetaDataMap);

	WTRiASObjects Objs;
	WTRiASDatabase DBase;

		if (SUCCEEDED(m_Target -> QueryInterface(Objs.ppi()))) {
		// Bezugsobjekt ist eine Objektklasse (FeatureMetaDataMap)
		HRESULT hr = Objs -> get_TableName(&bstrTable);

			if (FAILED(hr)) 
				return hr;		// nicht während der Initialisierung
			bstrTable.Append (L":");
			bstrTable.AppendBSTR (bstrName);

		} else if (SUCCEEDED(m_Target -> QueryInterface(DBase.ppi()))) {
		// Bezugsobjekt ist die Datenbank (ObjectsmetaDataMap)
			bstrTable = bstrName;

		} else
			return E_NOINTERFACE;

	DWORD dwHash = LHashValOfName (LOCALE_SYSTEM_DEFAULT, bstrTable);
	OLECHAR cbBuffer[_MAX_PATH];

		_ultow (dwHash, cbBuffer, 16);
		wcscat (cbBuffer, bstrTable);
		m_bstrName = cbBuffer;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASValueEvents abfangen und direkt zur Connection weiterleiten
STDMETHODIMP CMetaDataMap::ModifyingValue (BSTR Name, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_Target.IsValid());
	COM_TRY {
	WTRiASConnection Parent;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Target, Parent.ppi()));
		THROW_FAILED_HRESULT(WTRiASPropertyEvents(Parent) -> ModifyingProperty (Name, pVal));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CMetaDataMap::ValueToModify (BSTR Name)
{
	_ASSERTE(m_Target.IsValid());
	COM_TRY {
	WTRiASConnection Parent;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Target, Parent.ppi()));
		THROW_FAILED_HRESULT(WTRiASPropertyEvents(Parent) -> PropertyToModify (Name));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CMetaDataMap::ValueModified (BSTR Name)
{
	_ASSERTE(m_Target.IsValid());
	COM_TRY {
	WTRiASConnection Parent;

		THROW_FAILED_HRESULT(FindSpecificParent (m_Target, Parent.ppi()));
		THROW_FAILED_HRESULT(WTRiASPropertyEvents(Parent) -> PropertyModified (Name));

	} COM_CATCH;
	return S_OK;
}



