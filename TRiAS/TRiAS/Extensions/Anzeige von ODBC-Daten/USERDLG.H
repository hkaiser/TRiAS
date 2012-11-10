// UserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog

class CUserDlg : public CDialog
{
// Construction
public:
	DataSourceType m_tType;
	CString m_strDsn;

	CUserDlg(CWnd* pParent = NULL);   // standard constructor

//	DataSource setzen
	BOOL SelectDataSource (const char *pDsn);

// Dialog Data
	//{{AFX_DATA(CUserDlg)
	enum { IDD = IDD_USER_DSN };
	CButton	m_btChange;
	CComboBox	m_cbList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControlState (void);

	// Generated message map functions
	//{{AFX_MSG(CUserDlg)
	afx_msg void OnChangeDsn();
	afx_msg void OnCreateDsn();
	afx_msg void OnSelchangeDsn();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
