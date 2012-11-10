// SuchPage4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuchPage4 dialog

class CSuchPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSuchPage4)

// Construction
public:
	CSuchPage4();
	~CSuchPage4();

// Dialog Data
	//{{AFX_DATA(CSuchPage4)
	enum { IDD = IDD_SUCH4 };
	CString	m_strName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSuchPage4)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSuchPage4)
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
