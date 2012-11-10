// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.12.2002 13:30:42 
//
// @doc
// @module TRiASConnectionFilters.cpp | Definition of the <c CTRiASConnectionFilters> class

#include "stdafx.h"

#include "Wrapper.h"		// SmartIF's
#include "Strings.h"
#include "TRiASConnectionFilters.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASConnectionFilter);

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASConnectionFilters, CTRiASConnectionFilters)

/////////////////////////////////////////////////////////////////////////////
// CTRiASConnectionFilters

// FinalConstruct implementation
HRESULT CTRiASConnectionFilters::FinalConstruct()
{
	RETURN_FAILED_HRESULT(CComObjectRootEx<_ThreadModel>::FinalConstruct());
	RETURN_FAILED_HRESULT(IPersistStorageOMImpl<CTRiASConnectionFilters>::FinalConstruct());
	return S_OK;
}

// FinalRelease implementation
void CTRiASConnectionFilters::FinalRelease()
{
}

// Implementation of Add
STDMETHODIMP CTRiASConnectionFilters::Add(BSTR bstrName, ITRiASConnectionFilter **ppIFilter)
{
	if (NULL == ppIFilter)
		return E_POINTER;
	*ppIFilter = NULL;

	COM_TRY {
	WTRiASConnectionFilter Filter;

		THROW_FAILED_HRESULT(m_ObjMan -> CreateObject(CLSID_TRiASConnectionFilter, 
			bstrName, STGM_CREATE, Filter.ppu(), false));
		THROW_FAILED_HRESULT(Filter -> put_Name(bstrName));
		THROW_FAILED_HRESULT(Append (Filter));

		*ppIFilter = Filter.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASConnectionFilters::DeleteByIndex (VARIANT vIndex)
{
HRESULT hr = E_UNEXPECTED;

	COM_TRY {
	CComBSTR bstrName;
	CComVariant vObject;

		hr = collection_base_t::get_Item(vIndex, &vObject);
		if (S_OK == hr) {
			THROW_FAILED_HRESULT(vObject.ChangeType(VT_DISPATCH));
			THROW_FAILED_HRESULT(WTRiASConnectionFilter(V_DISPATCH(&vObject))
				-> get_Name(&bstrName));

			THROW_FAILED_HRESULT(hr = collection_base_t::DeleteByIndex(vIndex));
		}

		if (bstrName.Length() > 0)
		{
			THROW_FAILED_HRESULT(m_ObjMan -> DelObject (bstrName));
		}

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CTRiASConnectionFilters::DeleteByObject (IDispatch* pDispObj)
{
HRESULT hr = E_UNEXPECTED;

	COM_TRY {
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(WTRiASConnectionFilter(pDispObj) -> get_Name(&bstrName));
		THROW_FAILED_HRESULT(hr = collection_base_t::DeleteByIndex(CComVariant(bstrName)));
		if (S_OK == hr && bstrName.Length() > 0)
		{
			THROW_FAILED_HRESULT(m_ObjMan -> DelObject (bstrName));
		}

	} COM_CATCH;
	return hr;
}
