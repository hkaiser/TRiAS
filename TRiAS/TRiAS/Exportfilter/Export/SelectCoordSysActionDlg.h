// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 02.05.2004 19:36:09
//
// @doc
// @module SelectCoordSysActionDlg.h | Declaration of the <c CSelectCoordSysActionDlg> class

#if !defined(__SELECTCOORDSYSACTIONDLG_H_)
#define __SELECTCOORDSYSACTIONDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include "CoordSystemTree.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSysActionDlg dialog

class CSelectCoordSysActionDlg : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CSelectCoordSysActionDlg)

// Construction
public:
	CSelectCoordSysActionDlg();
	~CSelectCoordSysActionDlg();

	void SetDescription (HTREEITEM hItem = NULL);

// Dialog Data
	//{{AFX_DATA(CSelectCoordSysActionDlg)
	enum { IDD = IDD_SELECTCOORDSYSACTION_OPTIONS };
	CStatic	m_ftDescText;
	CStatic	m_ftDescription;
	CCoordSystemTree	m_tvCoordSystems;
	//}}AFX_DATA
	CString m_strTcfName;			// der Name des Koordinatensystemes

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSelectCoordSysActionDlg)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CSelectCoordSysActionDlg *CreateInstance (LPCSTR pcCaption);

	HRESULT GetSelectedCS(ITRiASCS **ppICS)
	{
		if (NULL != ppICS) {
		CComPtr<ITRiASCS> CS(m_CS);

			*ppICS = CS.Detach();
			return S_OK;
		}
		return E_POINTER;
	}

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectCoordSysActionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkCoordSystems(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void AdjustSheetButtons(HTREEITEM hItem);
	BOOL GetDisableNextPage(HTREEITEM hItem);
	bool PrepareResult();

private:
	DWORD m_dwFlags;
	BOOL m_fNotEmpty;
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_CS;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__SELECTCOORDSYSACTIONDLG_H_)
