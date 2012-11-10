// SuchPage1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchPage1 dialog

class CSuchPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuchPage1)

// Construction
public:
	CSuchPage1();
	~CSuchPage1();

// Dialog Data
	//{{AFX_DATA(CSuchPage1)
	enum { IDD = IDD_SUCH1 };
	CString	m_strIdent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuchPage1)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSuchPage1)
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
