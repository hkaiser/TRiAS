// InterDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterDialog dialog

class CInterDialog : public CDialog
{
// Construction
public:
	CInterDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInterDialog)
	enum { IDD = IDD_INTERDLG };
	CButton	m_btnOK;
	CString	m_strBez;
	CString	m_strPfad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInterDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
