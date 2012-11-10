#if !defined(AFX_PPGMAPINFO_H__A6EEA9A4_FE40_11D1_8F55_0060085FC1CE__INCLUDED_)
#define AFX_PPGMAPINFO_H__A6EEA9A4_FE40_11D1_8F55_0060085FC1CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PpgMapInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPpgMapInfo dialog

class CPpgMapInfo : public CPropertyPage {
	DECLARE_DYNCREATE(CPpgMapInfo)
	virtual void UpdateControls();
	void FillListControl();
// Construction
public:
	CPpgMapInfo();
	~CPpgMapInfo();

// Dialog Data
	//{{AFX_DATA(CPpgMapInfo)
	enum { IDD = IDD_PPGMAPINFO };
	CListCtrlEx	m_listOfGCPs;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPpgMapInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPpgMapInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PPGMAPINFO_H__A6EEA9A4_FE40_11D1_8F55_0060085FC1CE__INCLUDED_)
