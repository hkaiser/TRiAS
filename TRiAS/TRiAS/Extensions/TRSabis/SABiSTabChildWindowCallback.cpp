// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 02.06.2002 08:28:32 
//
// @doc
// @module SABiSTabChildWindowCallback.cpp | Definition of the <c SABiSTabChildWindowCallbackCallback> class

#include "stdafx.h"
#include "TRSABIS.h"

#include <ScopeVar.h>

#include "SabisTabChildWindow.h"
#include "SABiSTabChildWindowCallback.h"

/////////////////////////////////////////////////////////////////////////////
// SABiSTabChildWindowCallbackCallback
HRESULT CSABiSTabChildWindowCallback::InitTarget(CSabisTabChildWindow *pParent)
{
	m_pParent = pParent;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITabWindowCallback

// Implementation of AddTabWindow
STDMETHODIMP CSABiSTabChildWindowCallback::AddTabWindow()
{
	if (m_pParent->ItsVisibleForMe()) {
	BOOL fVisible = TRUE;

		DEX_IsSABiSBarVisible(fVisible);
		if (!fVisible) 
			m_pParent -> ReShow();		// nur wieder anzeigen
		else
			return S_FALSE;				// do nothing
	} else
		m_pParent -> CreateClientWindow();	// neu erzeugen
	return S_OK;
}

// Implementation of DeleteTabWindow
STDMETHODIMP CSABiSTabChildWindowCallback::DeleteTabWindow()
{
CScopeVar<BOOL> semDeleting(m_fIsDeleting, TRUE);

	if (!semDeleting.GetOldValue() && NULL != m_pParent) {
	BOOL fVisible = TRUE;

		DEX_IsSABiSBarVisible(fVisible);
		if (m_pParent->ItsVisibleForMe() && fVisible) {
			m_pParent -> InitiateShutDown();	// zerlegen
			m_pParent = NULL;
			return S_OK;
		}
	}
	return S_FALSE;
}

// Implementation of get_MayAddTabWindow
STDMETHODIMP CSABiSTabChildWindowCallback::get_MayAddTabWindow(VARIANT_BOOL *pfMayAdd)
{
	_ASSERTE(NULL != pfMayAdd);
	if (NULL == pfMayAdd)
		return E_POINTER;

BOOL fVisible = TRUE;
BOOL fMayOpen = TRUE;	// DEX_MayOpenSABiS();

	DEX_IsSABiSBarVisible(fVisible);
	*pfMayAdd = ((m_pParent->ItsVisibleForMe() && fVisible) || fMayOpen) ? 
		VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

