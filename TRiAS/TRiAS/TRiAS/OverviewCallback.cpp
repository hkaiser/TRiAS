// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.03.2001 14:43:07 
//
// @doc
// @module LegendeCallback.cpp | Definition of the <c COverviewCallback> class

#include "triaspre.hxx"
#include "OverviewCallback.h"

// ISupportsErrorInfo
STDMETHODIMP COverviewCallback::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_ITabWindowCallback ? S_OK : S_FALSE;
}

// Implementation of AddTabWindow
STDMETHODIMP COverviewCallback::AddTabWindow()
{
	if (DEX_IsOverviewActive()) {
	BOOL fVisible = TRUE;

		DEX_IsOverViewBarVisible(fVisible);
		if (!fVisible) 
			m_pCmdTarget -> PostEvent(WM_COMMAND, IDM_SHOWOVERVIEW);		// nur wieder anzeigen
		else
			return S_FALSE;		// do nothing
	} else
		m_pCmdTarget -> PostEvent(WM_COMMAND, IDM_OVERVIEW);				// neu erzeugen
	return S_OK;
}

// Implementation of DeleteTabWindow
STDMETHODIMP COverviewCallback::DeleteTabWindow()
{
BOOL fVisible = TRUE;

	DEX_IsOverViewBarVisible(fVisible);
	if (DEX_IsOverviewActive() && fVisible) {
		m_pCmdTarget -> PostEvent(WM_COMMAND, IDM_OVERVIEW);				// zerlegen
		return S_OK;
	}
	return S_FALSE;
}

// Implementation of get_MayAddTabWindow
STDMETHODIMP COverviewCallback::get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd)
{
	_ASSERTE(NULL != pfMayAdd);
	if (NULL == pfMayAdd)
		return E_POINTER;

BOOL fOverViewVisible = TRUE;
BOOL fMayOpenOverview = DEX_MayOpenOverview();

	DEX_IsOverViewBarVisible(fOverViewVisible);

	*pfMayAdd = ((DEX_IsOverviewActive() && fOverViewVisible) || fMayOpenOverview) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

