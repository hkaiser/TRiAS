// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.06.2002 09:07:17 
//
// @doc
// @module VideoPaneCallback.cpp | Definition of the <c CVideoPaneCallback> class

#include "stdafx.h"
#include "VidCtrl.h"

#include "VideoPaneCallback.h"

/////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo
STDMETHODIMP CVideoPaneCallback::InterfaceSupportsErrorInfo(REFIID riid)
{
	return riid == IID_ITabWindowCallback ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CVideoPaneCallback

// Constructor
CVideoPaneCallback::CVideoPaneCallback() :
	m_pCmdTarget(NULL)
{
}

// Destructor
CVideoPaneCallback::~CVideoPaneCallback()
{
}

///////////////////////////////////////////////////////////////////////////////
// Implementation of get_MayAddTabWindow
STDMETHODIMP CVideoPaneCallback::get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd)
{
	_ASSERTE(NULL != pfMayAdd);
	if (NULL == pfMayAdd)
		return E_POINTER;

	*pfMayAdd = VARIANT_TRUE;
	return S_OK;
}

// Implementation of AddTabWindow
STDMETHODIMP CVideoPaneCallback::AddTabWindow()
{
	if (m_pCmdTarget -> IsBarActive()) {
	BOOL fVisible = TRUE;

		DEX_IsProjectBarVisible(fVisible);
		if (!fVisible) 
			return m_pCmdTarget -> ShowBar() ? S_OK : E_OUTOFMEMORY;		// nur wieder anzeigen
		else
			return S_FALSE;		// do nothing
	} else
		m_pCmdTarget -> CreateBar();			// neu erzeugen
	return S_OK;
}

// Implementation of DeleteTabWindow
STDMETHODIMP CVideoPaneCallback::DeleteTabWindow()
{
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	if (m_pCmdTarget -> IsBarActive() && fVisible) {
		m_pCmdTarget -> FreeBar();			// zerlegen
		return S_OK;
	}
	return S_FALSE;
}

