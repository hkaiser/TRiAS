// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.03.2000 15:11:39
//
// @doc
// @module MacroIconsInTray.cpp | Funktionen, um TrayIcons für Macros zu verwalten

#include "bscriptp.hxx"

#include "bscript.h"
#include "conststr.h"

///////////////////////////////////////////////////////////////////////////////
// Messages an TrayIcon auswerten
LRESULT CMacroScriptExtension::HandleTrayMessages (UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    if (wParam == GetCurrentProcessId() && wMsg == m_uiTrayMsg) {	// GetCurrentProcessId() ist TrayId
	// Notifikation vom Icon
		switch (lParam) {
		case WM_LBUTTONDBLCLK:		// alle Macros anhalten
			return SUCCEEDED(StopAllRun());

		case WM_RBUTTONUP:			// ein bestimmtes Macro anhalten
			break;
			
		default:
			break;
		}

    } else if (wMsg == m_uiCreateTrayMsg) {
    // taskbar wurde neu erzeugt
		if (m_lCountRunning > 0)
			InitMacroTrayIcons(true);
    }
    return FALSE;
}

HRESULT CMacroScriptExtension::InitMacroTrayIcons(bool fForceReload)
{
	_ASSERTE(NULL != m_pTrayIcons);

	if (!fForceReload && InterlockedIncrement (&m_lCountRunning) > 0) {
	CString strToolTip;

		strToolTip.Format (IDS_TRAYTOOLTIP, g_cbTRiAS, m_lCountRunning+1);
		m_pTrayIcons -> SetTrayToolTip (strToolTip);
		return S_FALSE;		// nicht das erste mal
	}

	COM_TRY {
	// für alle Fälle
		m_pTrayIcons -> Stop();
		m_pTrayIcons -> Remove();

	// Icons laden	
	HICON hIcons[4];

		hIcons[0] = ::LoadIcon (_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_MACRO_SEQUENCE0));
		hIcons[1] = ::LoadIcon (_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_MACRO_SEQUENCE1));
		hIcons[2] = ::LoadIcon (_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_MACRO_SEQUENCE2));
		hIcons[3] = ::LoadIcon (_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_MACRO_SEQUENCE3));

	CString strToolTip;

		strToolTip.Format (0 == m_lCountRunning ? IDS_TRAYTOOLTIP_ONE : IDS_TRAYTOOLTIP, g_cbTRiAS, m_lCountRunning+1);
		m_pTrayIcons -> SetTrayToolTip (strToolTip);

		m_pTrayIcons -> SetTrayCallbackWindowHandle (MWind() -> GetSafeHwnd());
		m_pTrayIcons -> SetTrayCallBackMessage (m_uiTrayMsg);
		m_pTrayIcons -> SetTrayID (GetCurrentProcessId());
		m_pTrayIcons -> SetFrameIconInfo (hIcons, 4);
		
		m_pTrayIcons -> SetFrameRate(700);				// in ms
		m_pTrayIcons -> Start();

	} COM_CATCH;
	return S_OK;
}

HRESULT CMacroScriptExtension::RemoveMacroTrayIcons()
{
	if (InterlockedDecrement (&m_lCountRunning) >= 0) {
	CString strToolTip;

		strToolTip.Format (0 == m_lCountRunning ? IDS_TRAYTOOLTIP_ONE : IDS_TRAYTOOLTIP, g_cbTRiAS, m_lCountRunning+1);
		if (NULL != m_pTrayIcons)
			m_pTrayIcons -> SetTrayToolTip (strToolTip);
		return S_FALSE;		// noch nicht der letzte 
	}

	if (NULL != m_pTrayIcons) {
		m_pTrayIcons -> Stop();
		m_pTrayIcons -> Remove();
	}		 
	return S_OK;
}
