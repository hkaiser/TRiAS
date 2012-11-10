// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 12.11.2004 11:41:37
//
// @doc
// @module LoadableCommands.cpp | Implementation of the <c CLoadableCommandsExtension> class

#include "stdafx.h"

#include "LoadableCommands.h"
#include "LoadableCommandsExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules LoadableCommands
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_LoadableCommands;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLoadableCommandsExtension
#define LOADABLECOMMAND_POSITION 9
#define LOADABLECOMMAND_POSITION_ORWND 3

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CLoadableCommandsExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

	InstallMenuItem (IDM_LOADABLE_COMMAND, IDS_LOADABLECOMMAND, 
				 IMINormalMenu, EXTRA_MENU_POS, LOADABLECOMMAND_POSITION);
	InstallMenuItem (IDM_LOADABLE_COMMAND, IDS_LOADABLECOMMAND, 
				 IMIObjWnd, OR_EXTRA_MENU_POS, LOADABLECOMMAND_POSITION_ORWND);
	return TRUE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CLoadableCommandsExtension::UnLoadExtension (void)
{
	RemoveMenuItem (IDM_LOADABLE_COMMAND, IMINormalMenu, 
        EXTRA_MENU_POS, LOADABLECOMMAND_POSITION);
	RemoveMenuItem (IDM_LOADABLE_COMMAND, IMIObjWnd, OR_EXTRA_MENU_POS,
        LOADABLECOMMAND_POSITION_ORWND);
	return CTriasExtension::UnLoadExtension();
}

STDMETHODIMP_(BOOL) CLoadableCommandsExtension::MenuCommand (
    WPARAM wParam, HWND hWnd) 
{
    BOOL retval = FALSE;
    if (NULL == hWnd) {
        if (IDM_LOADABLE_COMMAND == wParam) 
            retval = SUCCEEDED(DEX_ExecuteSequence());
    }
    else {
        if (IDM_LOADABLE_COMMAND == wParam) 
            retval = SUCCEEDED(DEXOR_ExecuteSequence(hWnd));
    }
    return retval;
}

#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)

STDMETHODIMP_(BOOL) CLoadableCommandsExtension::MenuSelect (
    UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
    if (IDM_LOADABLE_COMMAND == uiMenuID) {
	CComBSTR bstr;

        USES_CONVERSION;
	    bstr.LoadString(IDS_LOADABLECOMMAND_SELECT);
	    return DEX_SetMessageString(OLE2A(bstr));
    }
    return FALSE;
}
