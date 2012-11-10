// TestDialogBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntegrateDialog dialog

class CIntegrateDialog : public CDialog
{
// Construction
public:
	CIntegrateDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIntegrateDialog)
	enum { IDD = IDD_INTEGRIEREN };
	CButton	m_btnOK;
	CString	m_strBez;
	CString	m_strPfad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntegrateDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIntegrateDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
