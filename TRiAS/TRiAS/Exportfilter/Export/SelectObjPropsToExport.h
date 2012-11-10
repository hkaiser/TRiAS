// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 23.08.2002 09:52:38 
//
// @doc
// @module SelectObjPropsToExport.h | Declaration of the <c CSelectObjPropsToExport> class

#if !defined(_SELECTOBJPROPSTOEXPORT_H__8E572FD6_5757_4C53_82FC_05F3B23AC1F1__INCLUDED_)
#define _SELECTOBJPROPSTOEXPORT_H__8E572FD6_5757_4C53_82FC_05F3B23AC1F1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/list>

#include "Separator.h"
#include "ObjPropTree.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectObjPropsToExport dialog

class CSelectObjPropsToExport :
	public CPropertyPage
{
// Construction
public:
	CSelectObjPropsToExport();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectObjPropsToExport)
	enum { IDD = IDD_SELECTPROPSTOEXPORT };
	CObjPropTree	m_tcObjProps;
	CSeparator	m_sepDesc;
	CString	m_strDesc;
	//}}AFX_DATA

	static CSelectObjPropsToExport* CreateInstance (LPCSTR pcCaption);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectObjPropsToExport)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }

	HRESULT GetSelectedObjProps (list<os_string> &rlstObjProps)
	{ return rlstObjProps = m_lstSelObjProps, S_OK; }
	void SetSelectedObjProps(list<os_string> &rlstObjProps)
	{ m_lstSelObjProps = rlstObjProps; }
	void SetLimitCount(long lLimitCnt)
	{ m_tcObjProps.SetLimitCount(lLimitCnt); }

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectObjPropsToExport)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckStateChangedObjectproperties(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedObjectproperties(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	HRESULT GetObjectProperty (IObjectProperty **ppIObjProp);

private:
	DWORD m_dwFlags;
	list<os_string> m_lstSelObjProps;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_SELECTOBJPROPSTOEXPORT_H__8E572FD6_5757_4C53_82FC_05F3B23AC1F1__INCLUDED_)
