// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.10.2000 19:56:16 
//
// @doc
// @module ObjekteVereinigenDlg.h | Declaration of the <c CObjekteVereinigenDlg> class

#if !defined(_OBJEKTEVEREINIGENDLG_H__5345ADCA_6CEF_48F9_90E2_2CECA59349BA__INCLUDED_)
#define _OBJEKTEVEREINIGENDLG_H__5345ADCA_6CEF_48F9_90E2_2CECA59349BA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CObjekteVereinigenDlg dialog

class CAddAsObjectClass;

class CObjekteVereinigenDlg : 
	public CPropertyPage
{
// Construction
public:
	CObjekteVereinigenDlg(ResID uiDlg, LPCSTR pcCaption);
	~CObjekteVereinigenDlg();

	BOOL FInit (void);

// Dialog Data
	enum { IDD = IDD_OBJEKTEVEREINIGEN };

// Overrides
	void WindowInit (Event e);
	void ButtonClick (ControlEvt e);

	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	int OnSetActive (NotifyEvt e);

public:
	static CObjekteVereinigenDlg *CreateInstance (LPCSTR pcCaption);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	void SetInitialData(bool fDeleteObjs, bool fMarkObjs, bool fCopyObjs)
	{
		m_fDeleteObjs = fDeleteObjs;
		m_fMarkObjs = fMarkObjs;
		m_fCopyObjs = fCopyObjs;
	}
	bool GetDeleteObjs() { return m_fDeleteObjs; }
	bool GetMarkObjs() { return m_fMarkObjs; }
	bool GetCopyObjs() { return m_fCopyObjs; }
	
// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT PrepareResult (void);

private:
	DWORD m_dwFlags;
	bool m_fDeleteObjs;
	bool m_fMarkObjs;
	bool m_fCopyObjs;
	
	CheckBox m_cbDeleteObjs;
	CheckBox m_cbMarkObjs;
	CheckBox m_cbCopyObjs;
	FixedText m_ftComment;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_OBJEKTEVEREINIGENDLG_H__5345ADCA_6CEF_48F9_90E2_2CECA59349BA__INCLUDED_)
