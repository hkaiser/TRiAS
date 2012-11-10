// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/02/1998 09:37:15 PM
//
// @doc 
// @module JumpTable.h | Sprungverteilertabelle für TRiAS-DEX_... commands

#if !defined(_JUMPTABLE_H__710B2C37_890F_11D2_9EFB_006008447800__INCLUDED_)
#define _JUMPTABLE_H__710B2C37_890F_11D2_9EFB_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// spezielle lokale Message
#define WM_SHOWDENYLICENSEDIALOG	DEX_SHOWDENYLICDLG+1

///////////////////////////////////////////////////////////////////////////////
// vorgegebene FunktionsTabellen (compilergeneriert)
typedef LRESULT (CFakeMFCExtension::*DEXMESSAGEPROC)(HPROJECT, LPARAM);
typedef LPCSTR (CFakeMFCExtension::*DEXMSGDUMPPROC)(HPROJECT, LPARAM);

typedef struct tagDEXMESSAGEENTRY {
	WPARAM m_uiMsg;				// CommandID
	DEXMESSAGEPROC m_pProc;		// zugehörige Funktion
} DEXMESSAGEENTRY;

///////////////////////////////////////////////////////////////////////////////
// eigentliche compilergenerierte Sprungverteilertabelle
#if defined(_DEBUG)
#define EXTFCNENTRY(msg,fcn,t)			{msg,CFakeMFCExtension::fcn}
#define EXTFCNENTRY2(msg,fcn,proc,t)	{msg,CFakeMFCExtension::fcn}
#else
#define EXTFCNENTRY(msg,fcn,t)			{msg,CFakeMFCExtension::fcn}
#define EXTFCNENTRY2(msg,fcn,proc,t)	{msg,CFakeMFCExtension::fcn}
#endif // _DEBUG

const DEXMESSAGEENTRY DexMessageEntries[] = {
// Dokument erzeugen
	EXTFCNENTRY(DEX_CREATENEWGEODB, OnCreateProject, TRACE_LEVEL1),

// Dokument öffnen
	EXTFCNENTRY(DEX_PROJECTOPEN, OnOpenProject, TRACE_LEVEL1),
	EXTFCNENTRY(DEX_PROJECTOPENEX, OnOpenProject, TRACE_LEVEL1),

// Dokument schließen
	EXTFCNENTRY(DEX_PROJECTCLOSE, OnCloseProject, TRACE_LEVEL1),
	EXTFCNENTRY(DEX_PROJECTCLOSEEX, OnCloseProject, TRACE_LEVEL1),

// StatusBar aktualisieren
	EXTFCNENTRY(DEX_UPDATESTATUSBAR, OnUpdateStatusBar, TRACE_LEVEL1),

// #HK000713: Druckerdaten synchronisieren
	EXTFCNENTRY(DEX_UPDATEPRINTERSELECTION, OnUpdatePrinterSelection, TRACE_LEVEL1),

// #HK000807: StartupDialog anzeigen
	EXTFCNENTRY(DEX_SHOWSTARTUPDIALOG, OnShowStartupDialog, TRACE_LEVEL1),

// #HK001114
	EXTFCNENTRY(DEX_VERIFYLICLEVEL, OnVerifyLicenseLevel, TRACE_LEVEL1),
	EXTFCNENTRY(DEX_VERIFYLICOPTION, OnVerifyLicenseOption, TRACE_LEVEL1),
	EXTFCNENTRY(DEX_SHOWDENYLICDLG, OnShowLicenseDialog, TRACE_LEVEL1),
	EXTFCNENTRY(WM_SHOWDENYLICENSEDIALOG, OnShowLicenseDialogPost, TRACE_LEVEL1),

// #HK010315
	EXTFCNENTRY(WM_QUERYPROJECTBARACTIVE, OnQueryProjectBarActive, TRACE_LEVEL1),
	EXTFCNENTRY(WM_QUERYOVERVIEWBARACTIVE, OnQueryOverViewBarActive, TRACE_LEVEL1),

// #HK020531
	EXTFCNENTRY(WM_QUERYSABiSBARACTIVE, OnQuerySABiSBarActive, TRACE_LEVEL1),

// #HK020628
	EXTFCNENTRY(WM_QUERYGENERICBARACTIVE, OnQueryGenericBarActive, TRACE_LEVEL1),

// #HK021219
	EXTFCNENTRY(DEX_CREATECONNECTIONFILTER_DLG, OnShowCreateConnectionFilterDlg, TRACE_LEVEL1),

// #HK030107
	EXTFCNENTRY(DEX_SHOWCONNECTFILTERS, OnShowConnectionFilters, TRACE_LEVEL1),
	EXTFCNENTRY(DEX_CONNECTFILTERSSHOWN, OnConnectionFiltersShown, TRACE_LEVEL1),
};

#endif // !defined(_JUMPTABLE_H__710B2C37_890F_11D2_9EFB_006008447800__INCLUDED_)
