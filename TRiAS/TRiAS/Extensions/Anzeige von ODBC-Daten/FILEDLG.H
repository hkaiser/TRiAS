// FileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileDlg dialog

class CFileDlg : public CDialog
{
// Construction
public:
	DataSourceType m_tType;
	CFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileDlg)
	enum { IDD = IDD_FILE_DSN };
	CButton	m_btChange;
	CString	m_strDsn;
	//}}AFX_DATA

	//	DataSource setzen
	BOOL SelectDataSource (const char *pDsn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControlState (void);

	// Generated message map functions
	//{{AFX_MSG(CFileDlg)
	afx_msg void OnChangeDsn();
	virtual BOOL OnInitDialog();
	afx_msg void OnCreateDsn();
	afx_msg void OnSelectDsn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
