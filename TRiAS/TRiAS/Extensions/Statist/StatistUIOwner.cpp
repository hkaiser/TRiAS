// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 15.09.2001 09:19:27 
//
// @doc
// @module StatistUIOwner.cpp | Definition of the <c CStatistUIOwner> class

#include "stdafx.h"
#include "Statist.h"

#include "StatistUIOwner.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistUIOwner

STDMETHODIMP CStatistUIOwner::OnUpdateUI(ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI)
{
	if (!DEX_TestActiveProject()) {				
	// kein Projekt geöffnet
		pCmdUI -> put_IsEnabled (false);	// ToolButton passivieren
		pCmdUI -> put_CheckState (0);		// ToolButton ungedrückt lassen oder machen
		return S_OK;
	}

	_ASSERTE(NULL != m_pCmdTarget);

BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	
	pCmdUI -> put_IsEnabled(true);
	pCmdUI -> put_CheckState ((m_pCmdTarget -> IsProjectBarActive() && fVisible) ? 1 : 0);
	return S_OK;
}

STDMETHODIMP CStatistUIOwner::OnSelect(
	ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten)
{
CString strText;
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	if (m_pCmdTarget -> IsProjectBarActive() && fVisible)
		strText.LoadString(IDS_STATISTICS_ON);
	else
		strText.LoadString(ID_TOOL_STATISTICS);
	_ASSERTE(strText.GetLength() > 0);

ULONG ulToWrite = min (uiLen-1, ULONG(strText.GetLength()));

	strncpy (pBuffer, strText, ulToWrite);
	pBuffer[ulToWrite] = '\0';

	if (pulWritten)
		*pulWritten = ulToWrite;

	return S_OK;
}

STDMETHODIMP CStatistUIOwner::OnCommand(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (0 != nCode) 
		return S_FALSE;

HRESULT hr = S_OK;
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	if (m_pCmdTarget -> IsProjectBarActive() && fVisible) {
	// ausblenden gefordert
		hr = m_pCmdTarget -> FreeProjectBar() ? S_OK : E_FAIL;			// zerlegen
	}
	else {
	// einblenden gewünscht
		if (m_pCmdTarget -> IsProjectBarActive()) {
			if (!fVisible) 
				hr = m_pCmdTarget -> ShowProjectBar() ? S_OK : E_OUTOFMEMORY;		// nur wiederanzeigen
			else
				hr = S_FALSE;
		}
		else
			hr = m_pCmdTarget -> CreateProjectBar() ? S_OK : E_OUTOFMEMORY;			// neu erzeugen
	}
	return hr;
}

