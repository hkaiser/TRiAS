// addfdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddFunctionDlg dialog

class CTemplateManagement;

class CAddFunctionDlg : public CDialog
{
private:
	CString m_strDeclaration;
	CString m_strTyp;
	CString m_strName;
	CString	m_strParams;
	CString	m_strComment;

	// Construction
public:
	CAddFunctionDlg(CWnd* pParent = NULL);   // standard constructor
	~CAddFunctionDlg(void);

// Dialog Data
	//{{AFX_DATA(CAddFunctionDlg)
	enum { IDD = IDD_ADDFUNCTION };
	CButton	m_chckNotification;
	CComboBox	m_cbxNotification;
	CButton	m_bttnOK;
	CButton	m_chckFunction;
	CEdit	m_ctrlTyp;
	CEdit	m_ctrlDeclaration;
	//}}AFX_DATA

	CString GetDeclaration	(void) { return m_strDeclaration; }
	CString GetType			(void) { return m_strTyp; }
	CString GetName			(void) { return m_strName; }
	CString GetParams		(void) { return m_strParams; }
	CString GetComment		(void) { return m_strComment; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddFunctionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddFunctionDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckfunction();
	afx_msg void OnChangeDeklaration();
	afx_msg void OnChangeTyp();
	afx_msg void OnChecknotification();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeCombonotification();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL	SetButtons(BOOL fCheck = false);
	HRESULT FillComboBox(void);
	HRESULT MakeTemplate(CTemplateManagement **ppTM);
	HRESULT SetTemplatePieces(void);
	HRESULT DeleteTemplates(void);
	HRESULT ValidDecl(LPCSTR lpcstr);
	void	MessageDeclError();
};
