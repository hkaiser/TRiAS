// NewProjectAdvancedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProjectAdvancedDlg dialog

class CNewProjectAdvancedDlg : public CDialog
{
// Construction
public:
	CNewProjectAdvancedDlg(CWnd* pParent, int iIdBase);   // standard constructor

	int GetIdentBase (void) { return m_iIdBase; }
	bool GetCompatibilityMode (void) { return m_fCompatible; }

// Dialog Data
	//{{AFX_DATA(CNewProjectAdvancedDlg)
	enum { IDD = IDD_ADVANCEDPARAMS };
	CButton	m_cbCompatibility;
	CButton m_rbDezimal;
	CButton m_rbHexaDez;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectAdvancedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProjectAdvancedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDezimal();
	afx_msg void OnHexadezimal();
	afx_msg void OnCompatibilitymode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iIdBase;
	bool m_fCompatible;
};
