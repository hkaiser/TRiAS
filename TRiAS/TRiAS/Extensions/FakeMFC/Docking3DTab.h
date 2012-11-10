// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.03.2001 13:33:16 
//
// @doc
// @module Docking3DTab.h | Declaration of the <c CDocking3DTab> class

#if !defined(_DOCKING3DTAB_H__1192BCA1_EADB_4C61_9B19_0F09FF62F3DF__INCLUDED_)
#define _DOCKING3DTAB_H__1192BCA1_EADB_4C61_9B19_0F09FF62F3DF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ot_dockingwindows.h>		// Objective Toolkit docking windows
#include <ot_tabwnd.h>				// Objective Toolkit tab windows

#include "Docking3DTabControl.h"

///////////////////////////////////////////////////////////////////////////////
// Daten, die an einem Tab dranhängen
DefineSmartInterface(TabWindowCallback);

class CTabData
{
public:
	bool m_fIsAttached;
	CWnd *m_pWnd;
	HWND m_hOldParentWnd;
};

/////////////////////////////////////////////////////////////////////////////
// CDocking3DTab window

class CDocking3DTab : public SEC3DTabWnd
{
    DECLARE_DYNCREATE(CDocking3DTab)

// Construction
public:
	typedef os_pair<WTabWindowCallback, UINT> CTabMapData;
	typedef map<CComBSTR, CTabMapData, less<CComBSTR> > CKnownTabs;

	CDocking3DTab();

// Attributes
public:
	int ClickedOnTab();
	SECTab *AddTab(CWnd *pWnd, LPCTSTR lpszLabel);
	int FindTab (LPCTSTR pcName);
	BOOL FindTab(const CWnd* const pWnd, int& nTab) const;
	void RemoveTab(int nIndex, bool fRemoveCallback = false);
	BOOL RenameTab(int nIndex, BSTR bstrOldName, BSTR bstrNewName);

// Operations
public:
	BOOL CreateTabCtrl(DWORD dwStyle, UINT nID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocking3DTab)
	//}}AFX_VIRTUAL
	virtual void OnExtendContextMenu(CMenu* pMenu);

// Implementation
public:
	virtual ~CDocking3DTab();

	HRESULT AddTabWindowDelayed(BSTR bstrName, ITabWindowCallback *pICallback);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDocking3DTab)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTabCommand(UINT uiID);

protected:
	void VLine3DEx(CDC* pDC, int x, int y, int nHeight);
	void HLine3DEx(CDC* pDC, int x, int y, int nWidth, BOOL bFlip = FALSE);

private:
	CKnownTabs m_Tabs;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_DOCKING3DTAB_H__1192BCA1_EADB_4C61_9B19_0F09FF62F3DF__INCLUDED_)
