// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/02/1998 10:29:59 PM
//
// @doc 
// @module DexCommands.h | Definierte command handler

#if !defined(_DEXCOMMANDS_H__710B2C38_890F_11D2_9EFB_006008447800__INCLUDED_)
#define _DEXCOMMANDS_H__710B2C38_890F_11D2_9EFB_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// in dieser Erweiterung definierte command handler
	LRESULT OnCreateProject (HPROJECT, LPARAM);		// DEX_CREATENEWGEODB
	LRESULT OnOpenProject (HPROJECT, LPARAM);		// DEX_PROJECTOPEN, DEX_PROJECTOPENEX
	LRESULT OnCloseProject (HPROJECT, LPARAM);		// DEX_PROJECTCLOSE, DEX_PROJECTCLOSEEX
	LRESULT OnUpdateStatusBar (HPROJECT, LPARAM);	// DEX_UPDATESTATUSBAR

// #HK000713: Druckerdaten synchronisieren
	LRESULT OnUpdatePrinterSelection(HPROJECT, LPARAM);		// DEX_UPDATEPRINTERSELECTION

// #HK000807: StartupDialog anzeigen
	LRESULT OnShowStartupDialog(HPROJECT, LPARAM);	// DEX_SHOWSTARTUPDIALOG
	
// #HK001114
	LRESULT OnVerifyLicenseLevel (HPROJECT, LPARAM);	// DEX_VERIFYLICLEVEL
	LRESULT OnVerifyLicenseOption (HPROJECT, LPARAM);	// DEX_VERIFYLICOPTION
	LRESULT OnShowLicenseDialog (HPROJECT, LPARAM);		// DEX_SHOWDENYLICDLG
	LRESULT OnShowLicenseDialogPost (HPROJECT, LPARAM);	// WM_SHOWDENYLICENSEDIALOG

// #HK010315
	LRESULT OnQueryProjectBarActive (HPROJECT, LPARAM);	// WM_QUERYPROJECTBARACTIVE
	LRESULT OnQueryOverViewBarActive (HPROJECT, LPARAM);	// WM_QUERYOVERVIEWBARACTIVE

// #HK020531
	LRESULT OnQuerySABiSBarActive (HPROJECT, LPARAM);	// WM_QUERYSABiSBARACTIVE

// #HK020628
	LRESULT OnQueryGenericBarActive (HPROJECT, LPARAM);	// WM_QUERYGENERICBARACTIVE

// #HK021219
	LRESULT OnShowCreateConnectionFilterDlg (HPROJECT, LPARAM);	// DEX_CREATECONNECTIONFILTER_DLG

// #HK030107
	LRESULT OnShowConnectionFilters (HPROJECT, LPARAM);		// DEX_SHOWCONNECTFILTERS
	LRESULT OnConnectionFiltersShown (HPROJECT, LPARAM);	// DEX_CONNECTFILTERSSHOWN

#endif // !defined(_DEXCOMMANDS_H__710B2C38_890F_11D2_9EFB_006008447800__INCLUDED_)
