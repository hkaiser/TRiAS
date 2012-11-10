// afidlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAfiDlg dialog

class CAfiDlg : public CDialog
{
// Construction
public:
	CAfiDlg(CWnd* pParent);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAfiDlg)
	enum { IDD = IDD_AFI };
	CComboBox	m_cbKreise;
	CComboBox	m_cbAfis;
	CButton	m_btOk;
	CButton m_btAfis;
	BOOL	m_bOnlySA;
	BOOL	m_bOnlyNotExported;
	//}}AFX_DATA
	
	CString m_strGKZ;
	BOOL m_bType;
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CAfiDlg)
	afx_msg void OnSelchangeAfis();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeKreise();
	afx_msg void OnAfis();
	afx_msg void OnKreise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
