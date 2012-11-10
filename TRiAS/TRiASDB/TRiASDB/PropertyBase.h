// $Header: /TRiAS/TRiASDB/TRiASDB/PropertyBase.h 1     15.06.98 21:30 Hartmut Kaiser $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 06/10/1998 09:58:40 PM
//
// @doc
// @module PropertyBase.h | Implementation des <i ITRiASPropertyBase>- Interfaces

#if !defined(_PROPERTYBASE_H__6DFE6A83_0083_11D2_864A_00600875138A__INCLUDED_)
#define _PROPERTYBASE_H__6DFE6A83_0083_11D2_864A_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// FMTID für Speichern/Laden
// {7CD5571E-6427-11D2-9EDE-006008447800}
extern "C" const FMTID __declspec(selectany) FMTID_EnumProperties = 
	{0x7cd5571e,0x6427,0x11d2,{0x9e,0xde,0x00,0x60,0x08,0x44,0x78,0x00}};

///////////////////////////////////////////////////////////////////////////////
// Properties für ein Objekt verwalten
template<class C>
class ATL_NO_VTABLE CManagePropertyBase :
	public IDispatchImpl<ITRiASPropertyBase, &IID_ITRiASPropertyBase, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	STDMETHOD(get_Properties) (ITRiASProperties **pVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		RETURN_FAILED_HRESULT(((C *)this) -> IsInitialized());
		if (NULL == pVal) 
			return TRIASDB_E_INVALID_PARAMETER;
		if (!m_Properties.IsValid())
		{
			RETURN_FAILED_HRESULT(CreatePropertiesCollection());
		}
		_ASSERT(m_Properties.IsValid());
		return ClonePropertiesCollection(pVal);
	}

	STDMETHOD(put_Properties) (ITRiASProperties *pVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// bisherige Properties loslassen
		if (m_Properties.IsValid()) {
			m_Properties -> SetEventSink (((C *)this) -> GetUnknown(), VARIANT_FALSE);
			m_Properties.Assign(NULL);
		}

	// neue Properties erst bei der alten Objektmenge abmelden, dann hier anmelden
		RETURN_FAILED_HRESULT(pVal -> SetEventSink (NULL, VARIANT_FALSE));
		RETURN_FAILED_HRESULT(pVal -> SetEventSink (((C *)this) -> GetUnknown(), VARIANT_TRUE));
		m_Properties = pVal;

		return S_OK;
	}

	STDMETHOD(get_Property) (BSTR Which, ITRiASProperty **pVal)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState())
		RETURN_FAILED_HRESULT(((C *)this) -> IsInitialized());
		if (NULL == pVal) return TRIASDB_E_INVALID_PARAMETER;
		if (!m_Properties.IsValid())
		{
			RETURN_FAILED_HRESULT(CreatePropertiesCollection());
		}
		_ASSERT(m_Properties.IsValid());

		if (m_Properties.IsValid()) {
		CComVariant vWhich (Which);

			return m_Properties -> Item (vWhich, pVal);
		}
		return E_UNEXPECTED;
	}

protected:
// neue PropertiesCollection anlegen und initialisieren
	HRESULT CreatePropertiesCollection(bool fRefresh = true)
	{
	WTRiASProperties Props;

		COM_TRY {
		// Properties-Collection erzeugen und initialisieren
			if (!m_Properties) 
				m_Properties = WTRiASProperties(CLSID_TRiASProperties);

			THROW_FAILED_HRESULT(m_Properties -> SetEventSink (NULL, VARIANT_FALSE));
			THROW_FAILED_HRESULT(m_Properties -> SetEventSink (((C *)this) -> GetUnknown(), VARIANT_TRUE));
			if (fRefresh) {
				THROW_FAILED_HRESULT(((C *)this) -> RefreshingProperties());
				THROW_FAILED_HRESULT(m_Properties -> Refresh());			// Properties erstmalig einlesen
				THROW_FAILED_HRESULT(((C *)this) -> PropertiesRefreshed());
			}

		} COM_CATCH_OP(m_Properties.Assign(NULL));
		return S_OK;
	}

// PropertiesCollection clonen
	HRESULT ClonePropertiesCollection(ITRiASProperties **pVal)
	{
		if (!m_Properties)
			return E_UNEXPECTED;

	// macht das folgende Sinn ?
#if defined(_ATL_FREE_THREADED)
		return m_Properties -> _Clone (pVal);
#else
	__Interface<ITRiASProperties> Props (m_Properties);

		*pVal = Props.detach();
		return S_OK;
#endif // _ATL_FREE_THREADED
	}

// PropertiesCollection freigeben
	HRESULT FreePropertiesCollection()
	{
		if (m_Properties.IsValid()) {
			m_Properties -> SetEventSink (((C *)this) -> GetUnknown(), VARIANT_FALSE);
			m_Properties.Assign(NULL);
		}
		return S_OK;
	}

	ITRiASProperties *GetProperties() throw(_com_error &)
	{
		if (!m_Properties.IsValid())
		{
			THROW_FAILED_HRESULT(CreatePropertiesCollection());
		}
		_ASSERT(m_Properties.IsValid());
		return m_Properties;
	}
	HRESULT RefreshingProperties() { return S_OK; }		// Notanker
	HRESULT PropertiesRefreshed() { return S_OK; }		// Notanker

protected:
	WTRiASProperties m_Properties;	// alle zu diesem Objekt gehörenden Eigenschaften
};

#endif // !defined(_PROPERTYBASE_H__6DFE6A83_0083_11D2_864A_00600875138A__INCLUDED_)
