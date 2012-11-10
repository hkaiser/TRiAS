// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 18.10.2002 21:04:15 
//
// @doc
// @module SelectCoordSys.h | Declaration of the <c CSelectCoordSys> class

#if !defined(_SELECTCOORDSYS_H__0CDBCE61_24F3_430C_B5FE_93770DAAE605__INCLUDED_)
#define _SELECTCOORDSYS_H__0CDBCE61_24F3_430C_B5FE_93770DAAE605__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "CoordSystemTree.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectCoordSys dialog

class CSelectCoordSys : 
	public CPropertyPage
{
	DECLARE_DYNCREATE(CSelectCoordSys)

// Construction
public:
	CSelectCoordSys();
	~CSelectCoordSys();

	void SetDescription (HTREEITEM hItem = NULL);
	void SetIsLast (bool fFlag) { m_fIsLast = fFlag; }

	virtual void UpdateControls();

// Dialog Data
	//{{AFX_DATA(CSelectCoordSys)
	enum { IDD = IDD_SELECT_COORDSYS };
	CStatic	m_ftDescText;
	CStatic	m_ftDescription;
	CCoordSystemTree	m_tvCoordSystems;
	//}}AFX_DATA
	CString m_strTcfName;			// der Name des Koordinatensystemes

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSelectCoordSys)
	public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	void AdjustButtons(HTREEITEM hItem = NULL);
	bool PrepareResult();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectCoordSys)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkCoordSystems(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool m_fIsLast;
	bool m_fNotEmpty;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_SELECTCOORDSYS_H__0CDBCE61_24F3_430C_B5FE_93770DAAE605__INCLUDED_)
