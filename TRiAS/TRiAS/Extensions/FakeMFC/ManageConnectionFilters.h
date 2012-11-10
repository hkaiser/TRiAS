// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 18.12.2002 11:47:23 
//
// @doc
// @module ManageConnectionFilters.h | Declaration of the <c CManageConnectionFilters> class

#if !defined(_MANAGECONNECTIONFILTERS_H__506AB455_59CC_4F05_849D_DC18D8AECB05__INCLUDED_)
#define _MANAGECONNECTIONFILTERS_H__506AB455_59CC_4F05_849D_DC18D8AECB05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// CManageConnectionFilters dialog

class CManageConnectionFilters : public CDialog
{
// Construction
public:
	CManageConnectionFilters(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CManageConnectionFilters)
	enum { IDD = IDD_MANAGE_CONNECTIONFILTERS };
	CListCtrl	m_lvConnectFilters;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageConnectionFilters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManageConnectionFilters)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedConnectfilters(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNew();
	afx_msg void OnShowconnectfilters();
	afx_msg void OnDelete();
	afx_msg void OnProperties();
	afx_msg void OnDblclkConnectfilters(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	BOOL CALLBACK EnumConnectionFilters(char *pName, BOOL, void *pData);
	BOOL CALLBACK EnumConnectionsForDetach(long hPr, BOOL, void *pData);

	void AdjustButtons();

private:
	CImageList m_ilImages;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MANAGECONNECTIONFILTERS_H__506AB455_59CC_4F05_849D_DC18D8AECB05__INCLUDED_)
