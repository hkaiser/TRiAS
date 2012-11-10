// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 22.04.2002 20:20:53 
//
// @doc
// @module BNAConfigDlg.h | Declaration of the <c CBNAConfigDlg> class

#if !defined(_BNACONFIGDLG_H__784A842A_5C6C_4EE3_94CA_038DB659C577__INCLUDED_)
#define _BNACONFIGDLG_H__784A842A_5C6C_4EE3_94CA_038DB659C577__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"
#include "AssociateLayersToClasses.h"

///////////////////////////////////////////////////////////////////////////////
// CBNAConfigDlg

class CBNAImportConfig;

class CBNAConfigDlg :
	public CPropertyPage
{
public:
	CBNAConfigDlg(ResID uiDlg, LPCSTR pcCaption, CBNAImportConfig *pBack);
	~CBNAConfigDlg();

// Dialog Data
	enum { IDD = IDD_ASSOCIATE_LAYERS };

	static CBNAConfigDlg *CreateInstance (LPCSTR pcCaption, CBNAImportConfig *pBack);
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

protected:
// Overrides
	void WindowInit (Event e);
	void ButtonClick (ControlEvt e);

	int OnWizBack (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	int OnSetActive (NotifyEvt e);
	bool OnNotify (NotifyEvt e);

	LRESULT Dispatch (Event e);

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT PrepareResult (void);

	BOOL FInit() { return TRUE; }

	BOOL DefineNewEntry();
	BOOL CopyBnaEntry();
	BOOL CreateNewEntry(LPCSTR pcNewClass);

private:
	CBNAImportConfig *m_pBack;
	CAssociateLayersToClasses m_lvAssocLayers;
	PushButton m_pbNewClass;
	PushButton m_pbCopyClass;
	bool m_fGcoProduction;
};


#endif // !defined(_BNACONFIGDLG_H__784A842A_5C6C_4EE3_94CA_038DB659C577__INCLUDED_)
