// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 02.05.2002 19:48:48 
//
// @doc
// @module DummyUIOwner.cpp | Definition of the <c CDummyUIOwner> class

#include "stdafx.h"
#include "TRSABIS.h"
#include "DummyUIOwner.h"

/////////////////////////////////////////////////////////////////////////////
// CDummyUIOwner

STDMETHODIMP CDummyUIOwner::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IDummyUIOwner,
		&IID_DToolBarUIOwner
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// Implementation of SetToolBarUIOwnerSite
STDMETHODIMP CDummyUIOwner::SetToolBarUIOwnerSite(int uiID, DControlToolBar *pIToolBar)
{
	if (!m_TargetUIOwner.IsValid())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(m_TargetUIOwner -> SetToolBarUIOwnerSite(uiID, pIToolBar));
	return S_OK;
}

// Implementation of UpdateUI
STDMETHODIMP CDummyUIOwner::UpdateUI(DTRiASCmdUI *pICmdUI)
{
	if (!m_TargetUIOwner.IsValid())
		return E_UNEXPECTED;
	if (NULL == pICmdUI)
		return E_POINTER;

	if (m_fDebugMode) {
	// der Einfachheit halber alles freischalten
		RETURN_FAILED_HRESULT(pICmdUI ->put_IsEnabled (VARIANT_TRUE));
	}
	else {
	// einfach weiterleiten
		RETURN_FAILED_HRESULT(m_TargetUIOwner -> UpdateUI(pICmdUI));
	}
	return S_OK;
}

// Implementation of GetDescription
STDMETHODIMP CDummyUIOwner::GetDescription(int uiID, BSTR *pbstrDesc)
{
	if (!m_TargetUIOwner.IsValid())
		return E_UNEXPECTED;
	if (NULL == pbstrDesc)
		return E_POINTER;

	if (m_fDebugMode) {
	// kein Beschreibung liefern
		*pbstrDesc = SysAllocString(L"");
	}
	else {
	// einfach weiterleiten
		RETURN_FAILED_HRESULT(m_TargetUIOwner -> GetDescription(uiID, pbstrDesc));
	}
	return S_OK;
}

// Implementation of FireCommand
STDMETHODIMP CDummyUIOwner::FireCommand(int uiID, int nCode)
{
	if (!m_TargetUIOwner.IsValid())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(m_TargetUIOwner -> FireCommand(uiID, nCode));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Property Debugmode entscheidet, wie sich dieses objekt verhält
STDMETHODIMP CDummyUIOwner::get_DebugMode(VARIANT_BOOL *pVal)
{
	if (NULL == pVal)
		return E_POINTER;
	*pVal = m_fDebugMode;
	return S_OK;
}

STDMETHODIMP CDummyUIOwner::put_DebugMode(VARIANT_BOOL newVal)
{
	m_fDebugMode = newVal;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// muß als erste Funtion gerufen werden (Initialisierung)
STDMETHODIMP CDummyUIOwner::putref_TargetUIOwner(IDispatch *newVal)
{
	if (NULL != newVal) {
	// versuchen Target zuzuweisen
		RETURN_FAILED_HRESULT(newVal -> QueryInterface(m_TargetUIOwner.ppi()));
	}
	else {
	// Target freigeben
		m_TargetUIOwner.Assign(NULL);
	}
	return S_OK;
}
