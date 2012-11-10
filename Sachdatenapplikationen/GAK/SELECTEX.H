// selectex.h : header file
//

#ifndef _SELECTEX_H
#define _SELECTEX_H

/////////////////////////////////////////////////////////////////////////////
// CSelectExportTables dialog
class CSelectExportTables : public CDialog
{
// Construction
public:
	CSelectExportTables(CWnd* pParent);	

// Dialog Data
	//{{AFX_DATA(CSelectExportTables)
	enum { IDD = IDD_EXPORT_TABLES };
	CButton	m_btOk;
	BOOL	m_bAbfaelle;
	BOOL	m_bErzeuger;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSelectExportTables)
	virtual BOOL OnInitDialog();
	afx_msg void OnAbfaelle();
	afx_msg void OnErzeuger();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 		// 	_SELECTEX_H
