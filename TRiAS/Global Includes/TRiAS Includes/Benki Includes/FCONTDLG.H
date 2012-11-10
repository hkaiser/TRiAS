// FContDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFieldContentsDlg dialog

class CFieldContentsDlg : public CDialog
{
// Construction
public:
	CFieldContentsDlg(CWnd* pParent, CDatabase *pDatabase,
					  const char *pTable, const char *pField);  

// Dialog Data
	//{{AFX_DATA(CFieldContentsDlg)
	enum { IDD = IDD_FIELD_CONTENT };
	CButton	m_btOk;
	CListBox	m_lbFields;
	CString	m_strFieldName;
	CString	m_strFieldType;
	//}}AFX_DATA

private:
	CDatabase *m_pDatabase;
	CString m_strTable, m_strField;
	UINT m_uiResID;
public:
	CString m_strSelection;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFieldContentsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFieldContentsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFeldContents();
	afx_msg void OnDblclkFeldContents();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
