// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 21:47:41 
//
// @doc
// @module AddAsObjectClassDlg.h | Declaration of the <c CAddAsObjectClassDlg> class

#if !defined(_ADDASOBJECTCLASSDLG_H__E2B84C4B_B459_4E83_BCDC_F9D683D6412B__INCLUDED_)
#define _ADDASOBJECTCLASSDLG_H__E2B84C4B_B459_4E83_BCDC_F9D683D6412B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

#include <selidlvc.hxx>

/////////////////////////////////////////////////////////////////////////////
// CAddAsObjectClassDlg dialog

class CAddAsObjectClass;

class CAddAsObjectClassDlg : 
	public CPropertyPage
{
// Construction
public:
	CAddAsObjectClassDlg(CAddAsObjectClass *pParent, ResID uiDlg, LPCSTR pcCaption);
	~CAddAsObjectClassDlg();

	BOOL FInit (void);

// Dialog Data
	enum { IDD = IDD_MODIFYIDS_WIZ };

// Overrides
	void WindowInit (Event e);
	void ButtonClick (ControlEvt e);

	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	int OnSetActive (NotifyEvt e);
	void OnItemChanged (NotifyEvt e);
	void OnClick (NotifyEvt e);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CAddAsObjectClassDlg *CreateInstance (CAddAsObjectClass *pParent, LPCSTR pcCaption);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

	int SelectIdent (long lIdent, bool fSel = true);
	void SetAddToView (bool fAddToView) { m_fAddToView = fAddToView; }
	bool GetAddToView (void) { return m_fAddToView; }

	void SetSelectedIdent (long lIdent) { m_lResult = lIdent; }
	long GetSelectedIdent (void) { return m_lResult; }

// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT PrepareResult (void);

	bool GetSelectedIdent (long &rlIdent);
	int GetItemCount (void);

	friend DWORD __stdcall EnsureUnique (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData);

private:
	CAddAsObjectClass *m_pParent;
	DWORD m_dwFlags;

	LONG m_lResult;			// selektierter Ident
	bool m_fAddToView;

	CheckBox m_cbAddToView;
	PushButton m_pbDefine;
	CSelIdentListViewWindow *m_pIdents;
	FixedText m_ftAdjustIdent;
	CheckBox m_cbAdjustIdent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ADDASOBJECTCLASSDLG_H__E2B84C4B_B459_4E83_BCDC_F9D683D6412B__INCLUDED_)
