// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 01.07.2002 11:51:30 
//
// @doc
// @module VideoUIOwner.cpp | Definition of the <c CVideoUIOwner> class

#include "stdafx.h"

#include <SidManageTabs.h>

#include "VidCtrl.h"
#include "VidCtrlExt.h"

#include "VideoUIOwner.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoUIOwner

STDMETHODIMP CVideoUIOwner::OnUpdateUI(ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI)
{
	if (!DEX_TestActiveProject()) {				
	// kein Projekt geöffnet
		pCmdUI -> put_IsEnabled (false);	// ToolButton passivieren
		pCmdUI -> put_CheckState (0);		// ToolButton ungedrückt lassen oder machen
		return S_OK;
	}

	_ASSERTE(NULL != m_pCmdTarget);

GENERICBARINFO GBI;

	INITSTRUCT(GBI, GENERICBARINFO);
	GBI.guidSid = SID_ManageVideoTabs;
	DEX_IsGenericBarVisible(GBI);
	
	pCmdUI -> put_IsEnabled(true);
	pCmdUI -> put_CheckState ((m_pCmdTarget -> IsBarActive() && GBI.fVisible) ? 1 : 0);
	return S_OK;
}

STDMETHODIMP CVideoUIOwner::OnSelect(
	ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten)
{
CString strText;
GENERICBARINFO GBI;

	INITSTRUCT(GBI, GENERICBARINFO);
	GBI.guidSid = SID_ManageVideoTabs;
	DEX_IsGenericBarVisible(GBI);

	if (m_pCmdTarget -> IsBarActive() && GBI.fVisible)
		strText.LoadString(IDS_VIDEOPANE_ON);
	else
		strText.LoadString(ID_TOOL_VIDEOPANE);
	_ASSERTE(strText.GetLength() > 0);

ULONG ulToWrite = min (uiLen-1, ULONG(strText.GetLength()));

	strncpy (pBuffer, strText, ulToWrite);
	pBuffer[ulToWrite] = '\0';

	if (pulWritten)
		*pulWritten = ulToWrite;

	return S_OK;
}

STDMETHODIMP CVideoUIOwner::OnCommand(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (0 != nCode) 
		return S_FALSE;

HRESULT hr = S_OK;
GENERICBARINFO GBI;

	INITSTRUCT(GBI, GENERICBARINFO);
	GBI.guidSid = SID_ManageVideoTabs;
	DEX_IsGenericBarVisible(GBI);

	if (m_pCmdTarget -> IsBarActive() && GBI.fVisible) {
	// ausblenden gefordert
		hr = m_pCmdTarget -> FreeBar() ? S_OK : E_FAIL;			// zerlegen
	}
	else {
	// einblenden gewünscht
		if (m_pCmdTarget -> IsBarActive()) {
			if (!GBI.fVisible) 
				hr = m_pCmdTarget -> ShowBar() ? S_OK : E_OUTOFMEMORY;	// nur wiederanzeigen
			else
				hr = S_FALSE;
		}
		else
			hr = m_pCmdTarget -> CreateBar() ? S_OK : E_OUTOFMEMORY;	// neu erzeugen
	}
	return hr;
}

