// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 23.04.2002 09:47:46 
//
// @doc
// @module BNAProgressDlg.h | Declaration of the <c CBNAProgressDlg> class

#if !defined(_BNAPROGRESSDLG_H__7AB614F7_DE67_44D2_B7B7_9B39E354C3C4__INCLUDED_)
#define _BNAPROGRESSDLG_H__7AB614F7_DE67_44D2_B7B7_9B39E354C3C4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

///////////////////////////////////////////////////////////////////////////////
// CBNAProgressDlg

class CBNAImportConfig;

class CBNAProgressDlg :
	public CPropertyPage
{
public:
	CBNAProgressDlg(ResID uiDlg, LPCSTR pcCaption, CBNAImportConfig *pBack);
	~CBNAProgressDlg();

// Dialog Data
	enum { IDD = IDD_PROGRESSBAR };

	static CBNAProgressDlg *CreateInstance (LPCSTR pcCaption, CBNAImportConfig *pBack);
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

protected:
// Overrides
	void WindowInit (Event e);
	void ButtonClick (ControlEvt e);

	int OnWizNext (NotifyEvt e);
	int OnWizBack (NotifyEvt e);
	int OnSetActive (NotifyEvt e);

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT PrepareResult (void);
	LRESULT Dispatch(Event e);

	BOOL FInit() { return TRUE; }

	HRESULT ParseFile(LPCSTR pcoleFile, ULONG ulAct, ULONG ulCount);		//BNA
	//KK020904
	HRESULT ParseFileDat(LPCSTR pcoleFile, ULONG ulAct, ULONG ulCount);		//DAT
	//KK020904
	HRESULT VideoFileDat(LPCSTR pcoleFile, ULONG ulAct, ULONG ulCount);

	HRESULT GCAFileDat(LPCSTR pcoleFile, ULONG ulAct, ULONG ulCount);

private:
	CBNAImportConfig *m_pBack;
	bool m_fFilesParsed;

	FixedText m_ftFilesPrompt;
	CProgressCtrl m_FilesStatus;
	FixedText m_ftFileName;
	CProgressCtrl m_Status;
	CAnimateCtrl m_aviSearch;

	bool m_fAviStarted;
};


#endif // !defined(_BNAPROGRESSDLG_H__7AB614F7_DE67_44D2_B7B7_9B39E354C3C4__INCLUDED_)
