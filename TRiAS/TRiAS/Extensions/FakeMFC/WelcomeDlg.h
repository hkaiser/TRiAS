// WelcomeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDlg dialog

class CWelcomeDlg : public CDialog
{
// Construction
public:
	CWelcomeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcomeDlg)
	enum { IDD = IDD_STARTUPDLG };
	CButton	m_cbDontShowFurther;
	CButton	m_rbOpenOldProject;
	CButton	m_rbOpenLast;
	//}}AFX_DATA
	
	int m_iOpenMode;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcomeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCreateNewProject();
	afx_msg void OnOpenMruProject();
	afx_msg void OnOpenOldProject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
