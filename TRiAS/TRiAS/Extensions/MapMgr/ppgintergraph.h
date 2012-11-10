//{{AFX_INCLUDES()
#include "maskedit.h"
//}}AFX_INCLUDES
#if !defined(AFX_PPGINTERGRAPH_H__D2B6BCE3_1187_11D2_8F75_0060085FC1CE__INCLUDED_)
#define AFX_PPGINTERGRAPH_H__D2B6BCE3_1187_11D2_8F75_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CPpgIntergraph.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgIntergraph dialog

class CPpgIntergraph : public CPropertyPage {
	DECLARE_DYNCREATE(CPpgIntergraph)

	virtual void UpdateControls();
// Construction
public:
	CPpgIntergraph();
	~CPpgIntergraph();

// Dialog Data
	//{{AFX_DATA(CPpgIntergraph)
	enum { IDD = IDD_PPGINTERGRAPH };
	CListCtrlEx	m_matrix;
	CMaskEdit	m_origX;
	CMaskEdit	m_origY;
	CMaskEdit	m_origZ;
	CString	m_scale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgIntergraph)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgIntergraph)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdvanceFocusNextOrigx();
	afx_msg void OnAdvanceFocusNextOrigy();
	afx_msg void OnAdvanceFocusNextOrigz();
	afx_msg void OnSelchangeComboScale();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGINTERGRAPH_H__D2B6BCE3_1187_11D2_8F75_0060085FC1CE__INCLUDED_)
