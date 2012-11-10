// GSTeilenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGSTeilenDlg dialog

class CGSTeilenDlg : public CDialog
{
// Construction
public:
	CGSTeilenDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGSTeilenDlg)
	enum { IDD = IDD_GS_TEILEN };
	CString	m_strBez1;
	CString	m_strBez2;
	CString	m_strBez3;
	CString	m_strIdent1;
	CString	m_strIdent2;
	CString	m_strIdent3;
	CString	m_strONr1;
	CString	m_strONr2;
	CString	m_strONr3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGSTeilenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGSTeilenDlg)
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
