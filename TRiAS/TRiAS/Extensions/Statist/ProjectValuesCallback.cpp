// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 28.08.2001 22:15:20 
//
// @doc
// @module ProjectValuesCallback.cpp | Definition of the <c CProjectValuesCallback> class

#include "stdafx.h"
#include "StatistApp.h"

#if defined(_USE_PROJECTVALUES)
#include "ProjectValuesCallback.h"

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CProjectValuesCallback::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_ITabWindowCallback ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// ITabWindowCallback
STDMETHODIMP CProjectValuesCallback::AddTabWindow()
{
	if (m_pCmdTarget -> IsProjectBarActive()) {
	BOOL fVisible = TRUE;

		DEX_IsProjectBarVisible(fVisible);
		if (!fVisible) 
			return m_pCmdTarget -> ShowProjectBar() ? S_OK : E_OUTOFMEMORY;		// nur wieder anzeigen
		else
			return S_FALSE;		// do nothing
	} else
		m_pCmdTarget -> CreateProjectBar();			// neu erzeugen
	return S_OK;
}

STDMETHODIMP CProjectValuesCallback::DeleteTabWindow()
{
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	if (m_pCmdTarget -> IsProjectBarActive() && fVisible) {
		m_pCmdTarget -> FreeProjectBar();			// zerlegen
		return S_OK;
	}
	return S_FALSE;
}

// Implementation of get_MayAddTabWindow
STDMETHODIMP CProjectValuesCallback::get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd)
{
	_ASSERTE(NULL != pfMayAdd);
	if (NULL == pfMayAdd)
		return E_POINTER;

	*pfMayAdd = VARIANT_TRUE;
	return S_OK;
}

#endif // defined(_USE_PROJECTVALUES)


