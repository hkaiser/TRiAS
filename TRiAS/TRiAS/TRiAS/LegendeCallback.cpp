// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.03.2001 14:43:07 
//
// @doc
// @module LegendeCallback.cpp | Definition of the <c CLegendeCallback> class

#include "triaspre.hxx"
#include "LegendeCallback.h"

// ISupportsErrorInfo
STDMETHODIMP CLegendeCallback::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_ITabWindowCallback ? S_OK : S_FALSE;
}

// Implementation of AddTabWindow
STDMETHODIMP CLegendeCallback::AddTabWindow()
{
	if (DEX_IsLegendActive()) {
	BOOL fVisible = TRUE;

		DEX_IsProjectBarVisible(fVisible);
		if (!fVisible) 
			m_pCmdTarget -> PostEvent(WM_COMMAND, IDM_SHOWLEGENDE);		// nur wieder anzeigen
		else
			return S_FALSE;		// do nothing
	} else
		m_pCmdTarget -> PostEvent(WM_COMMAND, IDM_LEGENDE);				// neu erzeugen
	return S_OK;
}

// Implementation of DeleteTabWindow
STDMETHODIMP CLegendeCallback::DeleteTabWindow()
{
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	if (DEX_IsLegendActive() && fVisible) {
		m_pCmdTarget -> PostEvent(WM_COMMAND, IDM_LEGENDE);				// zerlegen
		return S_OK;
	}
	return S_FALSE;
}

// Implementation of get_MayAddTabWindow
STDMETHODIMP CLegendeCallback::get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd)
{
	_ASSERTE(NULL != pfMayAdd);
	if (NULL == pfMayAdd)
		return E_POINTER;

BOOL fLegendVisible = TRUE;
BOOL fMayOpenLegend = DEX_MayOpenLegend();

	DEX_IsProjectBarVisible(fLegendVisible);

	*pfMayAdd = ((DEX_IsLegendActive() && fLegendVisible) || fMayOpenLegend) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

