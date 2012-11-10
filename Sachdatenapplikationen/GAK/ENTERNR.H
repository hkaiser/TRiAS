// EnterNr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterNr dialog

class CEnterNr : public CDialog
{
// Construction
public:
	CString m_strExpression;
	CEnterNr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterNr)
	enum { IDD = IDD_LOOK_NR };
	CButton	m_btOk;
	CButton m_btLike;
	CErzNrEdit m_edNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterNr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iOperator;

	// Generated message map functions
	//{{AFX_MSG(CEnterNr)
	virtual void OnOK();
	afx_msg void OnChangeNumber();
	virtual BOOL OnInitDialog();
	afx_msg void OnEq();
	afx_msg void OnGr();
	afx_msg void OnGrEq();
	afx_msg void OnLess();
	afx_msg void OnLessEq();
	afx_msg void OnLike();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
