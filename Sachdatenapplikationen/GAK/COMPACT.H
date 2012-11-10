// Compact.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompactDataBase dialog

class CCompactDataBase : public CDialog
{
// Construction
public:
	CCompactDataBase(CWnd* pParent, const char *pOldDBName);   

// Dialog Data
	//{{AFX_DATA(CCompactDataBase)
	enum { IDD = IDD_COMPACT_DATABASE };
	CEdit	m_edFileName;
	CButton	m_btAsNew;
	CButton	m_btOk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompactDataBase)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iVersion;				// MDB-Version
	CString m_strOldDatabase;	// Name der alten Datenbank
	CString m_strDir;			// Verzeichnis der alten Datenbank

	// Generated message map functions
	//{{AFX_MSG(CCompactDataBase)
	afx_msg void OnFileName();
	afx_msg void OnVersion10();
	afx_msg void OnVersion11();
	afx_msg void OnVersion20();
	afx_msg void OnVersion30();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeFilename();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
